#include "btu.h"

/* Original source:
 * bluedroid <android.googlesource.com/platform/external/bluetooth/bluedroid>
 * stack/btu/btu_task.c
 */

/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/* Includes changes by muff1n1634 and for this repository (KoopTheKoopa) */

#include <stddef.h>

#include <decomp.h>

#include "bt_types.h"
#include "data_types.h"

#include "bta_sys.h"
#include "bte.h"
#include "btm_int.h"
#include "gki.h"
#include "hidh_int.h"
#include "l2c_int.h"
#include "rfc_int.h"
#include "sdp_int.h"

#include <revolution/types.h>

#define IS_BTE
#include <revolution.h>

#if !defined(NDEBUG)
# define BTU_TASK_TRACE(msg_)		\
	do								\
	{								\
		if (btu_dbg_flag == TRUE)	\
			OSReport(msg_);			\
	} while (FALSE)
#else
# define BTU_TASK_TRACE(msg_)
#endif

tBTU_CB btu_cb;

static char btu_count = 1;
static int execute_btu = 1;

static int _btu_last_timer_tick;
static int _btu_g_count;
#if !defined(NDEBUG)
static BOOL btu_dbg_flag;
#endif

#if !defined(NDEBUG)
void btu_enable_dbg(int enable)
{
	btu_dbg_flag = enable;
}
#endif

void btu_task_init(void)
{
	btu_count = 1;
	execute_btu = 1;
	_btu_g_count = 0;
	_btu_last_timer_tick = 0;

	btu_init_core();
	BTE_InitStack();
	bta_sys_init();
}

void btu_task_msg_handler(void)
{
	TIMER_LIST_ENT *p_tle;
	BT_HDR *p_msg;
	UINT8 i;
	UINT16 event;
	BOOLEAN handled;

	tBTU_TIMER_CALLBACK *p_timeout_cback;
	UINT16 mask;
	BOOLEAN messages_done;

	messages_done = FALSE;
	OSGetTime();

	++_btu_g_count;

	GKI_disable();

	if (execute_btu)
	{
		execute_btu = 0;
		btu_count = 1;
	}
	else
	{
		++btu_count;

		GKI_enable();
		return;
	}

	GKI_enable();

	event = TASK_MBOX_0_EVT_MASK | TASK_MBOX_2_EVT_MASK;

	if ((unsigned)_btu_g_count > (unsigned)_btu_last_timer_tick + 500)
	{
		event |= TIMER_0_EVT_MASK | TIMER_1_EVT_MASK;
		_btu_last_timer_tick = _btu_g_count;
	}

	while (!messages_done)
	{
		messages_done = TRUE;

		if (event & TASK_MBOX_0_EVT_MASK)
		{
			while ((p_msg = GKI_read_mbox(BTU_HCI_RCV_MBOX)))
			{
				messages_done = FALSE;

				BTU_TASK_TRACE("BTU Task got msg in MBOX0\n");

				switch (p_msg->event & 0xff00)
				{
				case 0x1100:
					l2c_rcv_acl_data(p_msg);
					break;

				case 0x1900:
					l2c_link_segments_xmitted(p_msg);
					break;

				case 0x1200:
					btm_route_sco_data(p_msg);
					break;

				case 0x1000:
					btu_hcif_process_event(p_msg);
					GKI_freebuf(p_msg);
					break;

				case 0x1600:
					btu_hcif_send_cmd(p_msg);
					break;

				default:
					i = 0;
					mask = p_msg->event & 0xff00;
					handled = FALSE;

					for (; !handled && i < BTU_MAX_REG_EVENT; ++i)
					{
						if (!btu_cb.event_reg[i].event_cb)
							continue;

						if (mask != btu_cb.event_reg[i].event_range)
							continue;

						// MWCC requires this repeated callback check.
						if (btu_cb.event_reg[i].event_cb)
						{
							(*btu_cb.event_reg[i].event_cb)(p_msg);
							handled = TRUE;
						}
					}

					if (!handled)
						GKI_freebuf(p_msg);
				}
			}
		}

		if (event & TIMER_0_EVT_MASK)
		{
			GKI_update_timer_list(&btu_cb.timer_queue, 1);
			event &= ~TIMER_0_EVT_MASK;

			while (btu_cb.timer_queue.p_first
			       && btu_cb.timer_queue.p_first->ticks == 0)
			{
				messages_done = FALSE;

				p_tle = btu_cb.timer_queue.p_first;
				GKI_remove_from_timer_list(&btu_cb.timer_queue, p_tle);

				switch (p_tle->event)
				{
				case BTU_TTYPE_BTM_DEV_CTL:
					btm_dev_timeout(p_tle);
					break;

				case BTU_TTYPE_BTM_ACL:
					btm_acl_timeout(p_tle);
					break;

				case BTU_TTYPE_L2CAP_LINK:
				case BTU_TTYPE_L2CAP_CHNL:
				case BTU_TTYPE_L2CAP_HOLD:
					l2c_process_timeout(p_tle);
					break;

				case BTU_TTYPE_SDP:
					sdp_conn_timeout((tCONN_CB *)p_tle->param);
					break;

				case BTU_TTYPE_BTM_RMT_NAME:
					btm_inq_rmt_name_failed();
					break;

				case 8:
					btm_discovery_timeout();
					break;

				case BTU_TTYPE_RFCOMM_MFC:
				case BTU_TTYPE_RFCOMM_PORT:
					rfcomm_process_timeout(p_tle);
					break;

				case BTU_TTYPE_BTU_CMD_CMPL:
					btu_hcif_cmd_timeout();
					break;

				case BTU_TTYPE_HID_HOST_REPAGE_TO:
					hidh_proc_repage_timeout(p_tle);
					break;

				case 22:
					p_timeout_cback = (tBTU_TIMER_CALLBACK *)p_tle->param;

					(*p_timeout_cback)(p_tle);
					break;

				default:
					i = 0;
					handled = FALSE;

					for (; !handled && i < BTU_MAX_REG_TIMER; ++i)
					{
						if (!btu_cb.timer_reg[i].timer_cb)
							continue;

						if (btu_cb.timer_reg[i].p_tle != p_tle)
							continue;

						(*btu_cb.timer_reg[i].timer_cb)(p_tle);
						handled = TRUE;
					}
				}
			}
		}

		if (event & TASK_MBOX_2_EVT_MASK)
		{
			while ((p_msg = GKI_read_mbox(TASK_MBOX_2)))
			{
				BTU_TASK_TRACE("BTU Task got msg in MBOX2\n");

				messages_done = FALSE;

				bta_sys_event(p_msg);
			}
		}

		if (event & TIMER_1_EVT_MASK)
		{
			event &= ~TIMER_1_EVT_MASK;
			bta_sys_timer_update();
		}

		if (event & (1 << 15))
			break;
	}

	execute_btu = 1;
}

void btu_start_timer(TIMER_LIST_ENT *p_tle, UINT16 type, UINT32 timeout)
{
	GKI_remove_from_timer_list(&btu_cb.timer_queue, p_tle);

	p_tle->event = type;
	p_tle->ticks = timeout;

	GKI_add_to_timer_list(&btu_cb.timer_queue, p_tle);
}

void btu_stop_timer(TIMER_LIST_ENT *p_tle)
{
	GKI_remove_from_timer_list(&btu_cb.timer_queue, p_tle);
}

void btu_register_timer(TIMER_LIST_ENT *p_tle, UINT16 type, UINT32 timeout,
                        tBTU_TIMER_CALLBACK *timer_cb)
{
	INT8 i = 0;
	INT8 first = -1;

	for (; i < BTU_MAX_REG_TIMER; ++i)
	{
		if (!btu_cb.timer_reg[i].p_tle && first < 0)
			first = i;

		if (btu_cb.timer_reg[i].p_tle == p_tle)
		{
			btu_cb.timer_reg[i].timer_cb = timer_cb;
			btu_start_timer(p_tle, type, timeout);

			first = -1;
			break;
		}
	}

	if (first >= 0 && first < BTU_MAX_REG_TIMER)
	{
		btu_cb.timer_reg[first].timer_cb = timer_cb;
		btu_cb.timer_reg[first].p_tle = p_tle;
		btu_start_timer(p_tle, type, timeout);
	}
}

void btu_deregister_timer(TIMER_LIST_ENT *p_tle)
{
	UINT8 i = 0;

	for (; i < BTU_MAX_REG_TIMER; ++i)
	{
		if (btu_cb.timer_reg[i].p_tle == p_tle)
		{
			btu_stop_timer(p_tle);
			btu_cb.timer_reg[i].timer_cb = NULL;
			btu_cb.timer_reg[i].p_tle = NULL;

			break;
		}
	}
}

void btu_register_event_range(UINT16 start, tBTU_EVENT_CALLBACK *event_cb)
{
	INT8 i = 0;
	INT8 first = -1;

	for (; i < BTU_MAX_REG_EVENT; ++i)
	{
		if (!btu_cb.event_reg[i].event_cb && first < 0)
			first = i;

		if (btu_cb.event_reg[i].event_range == start)
		{
			btu_cb.event_reg[i].event_cb = event_cb;

			if (!event_cb)
				btu_cb.event_reg[i].event_range = 0;

			first = -1;
		}
	}

	if (event_cb && first >= 0 && first < BTU_MAX_REG_EVENT)
	{
		btu_cb.event_reg[first].event_range = start;
		btu_cb.event_reg[first].event_cb = event_cb;

		if (!event_cb)
		{
			// NOTE: never reached, as event_cb must be both non-null and null
			btu_cb.event_reg[first].event_range = 0;
		}
	}
}

void btu_deregister_event_range(UINT16 range)
{
	btu_register_event_range(range, NULL);
}
