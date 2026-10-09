#include <decomp.h>

#include <revolution/cdb/CDBDate.h>
#include <revolution/os/OSTime.h>

#define IPL_UTILITY_CALENDAR_H

namespace ipl {
    namespace utility {
        class Date {
        public:
            typedef enum {
                NO_INIT = 0,
            } HackF;

            Date(HackF flag) {}

            Date() : year(MIN_YEAR), month(MIN_MONTH), day(MIN_DAY) {}
            Date(int myYear, int myMonth, int myDay) : year(myYear), month(myMonth), day(myDay) {}
            Date(const OSCalendarTime& cal) : year(cal.year), month(cal.mon + 1), day(cal.mday) {}
            Date(const Date& date) : year(date.year), month(date.month), day(date.day) {}

            static Date getMaxDate() {
                utility::Date date(MAX_YEAR, MAX_MONTH, MAX_DAY);
                return date;
            }
            static Date getMinDate() {
                utility::Date date(MIN_YEAR, MIN_MONTH, MIN_DAY);
                return date;
            }

            CDBDate cdbDateBegin() { return CDBMakeCDBDate(year, month - 1, day, 0, 0, 0); }
            CDBDate cdbDateEnd() { return CDBMakeCDBDate(year, month - 1, day, 23, 59, 59); }

            bool operator==(const Date& rhs) const { return year == rhs.year && month == rhs.month && day == rhs.day; }

            bool operator>(const Date& rhs) const {
                bool result = false;
                if (year > rhs.year) {
                    result = true;
                } else if (year == rhs.year) {
                    if (month > rhs.month) {
                        result = true;
                    } else if (month == rhs.month) {
                        if (day > rhs.day) {
                            result = true;
                        }
                    }
                }

                return result;
            }

            bool operator<(const Date& rhs) const {
                bool result = false;
                if (year < rhs.year) {
                    result = true;
                } else if (year == rhs.year) {
                    if (month < rhs.month) {
                        result = true;
                    } else if (month == rhs.month) {
                        if (day < rhs.day) {
                            result = true;
                        }
                    }
                }

                return result;
            }

            bool operator!=(const Date& rhs) const NO_INLINE { return year != rhs.year || month != rhs.month || day != rhs.day; }

            int year;
            int month;
            int day;
        };

        class Calendar {
        public:
            static void setCalendarTime(OSCalendarTime* newCalendar);
            static void getTomorrow(const Date& src, Date* dest);
            static void getYesterday(const Date& src, Date* dest);
            static int getDays(int year, int month);

            static int getWeek(const Date& date) NO_INLINE {
                int month, year, day;
                month = date.month;
                day = date.day;
                year = date.year;
                if (month <= 2) {
                    year--;
                    month += MAX_MONTH;
                }
                return (day + (((month * 13) + 8) / 5) + ((year / 400) + ((year + (year / 4)) - (year / 100)))) % 7;
            }

            static int getWeek(int year, int month, int day) NO_INLINE {
                if (month <= 2) {
                    year--;
                    month += MAX_MONTH;
                }
                return (day + (((month * 13) + 8) / 5) + ((year / 400) + ((year + (year / 4)) - (year / 100)))) % 7;
            }

            static void getNextMonth(const Date& src, Date* dest) NO_INLINE {
                *dest = src;
                dest->month++;
                if (dest->month > MAX_MONTH) {
                    dest->month = MIN_MONTH;
                    dest->year++;
                }
                dest->day = MIN_DAY;
            }

            static void getLastMonth(const Date& src, Date* dest) NO_INLINE {
                *dest = src;
                dest->month--;
                if (dest->month <= 0) {
                    dest->month--;
                    if (dest->month <= 0) {
                        dest->month = MAX_MONTH;
                        dest->year--;
                    }
                }
                dest->day = getDays(dest->year, dest->month);
            }
        };
    }
}

#include "scene/board/iplBoard.h"

#include "scene/button/iplButton.h"
#include "scene/calendar/iplCalendar.h"

#include "iplSound.h"
#include "iplSystem.h"

namespace ipl {
    namespace scene {
#define DATE_COUNT 42

        utility::Date Calendar::mscMinDate(MIN_YEAR, MIN_MONTH, MIN_DAY);
        utility::Date Calendar::mscMaxDate(MAX_YEAR, MAX_MONTH, MAX_DAY);

        // clang-format off
        static const Calendar::AnmFrame scAnmFrame[Calendar::IDANIM_MAX] = {
            { 1000.0f, 1040.0f },
            { 1040.0f, 1040.0f },
            { 2000.0f, 2030.0f },
            { 3000.0f, 3030.0f },
            { 4000.0f, 4020.0f },
        };

        static const Calendar::DayToMsgId scJapanDayToMessageID[] = {
            { "TextBox_00", MESG_CALENDAR_SUNDAY },
            { "TextBox_01", MESG_CALENDAR_MONDAY },
            { "TextBox_02", MESG_CALENDAR_TUESDAY },
            { "TextBox_03", MESG_CALENDAR_WEDNESDAY },
            { "TextBox_04", MESG_CALENDAR_THURSDAY },
            { "TextBox_05", MESG_CALENDAR_FRIDAY },
            { "TextBox_06", MESG_CALENDAR_SATURDAY },
            { "TextBox_08", MESG_CALENDAR_SUNDAY },
            { "TextBox_09", MESG_CALENDAR_MONDAY },
            { "TextBox_10", MESG_CALENDAR_TUESDAY },
            { "TextBox_11", MESG_CALENDAR_WEDNESDAY },
            { "TextBox_12", MESG_CALENDAR_THURSDAY },
            { "TextBox_13", MESG_CALENDAR_FRIDAY },
            { "TextBox_07", MESG_CALENDAR_SATURDAY },
            { "TextBox_16", MESG_CALENDAR_SUNDAY },
            { "TextBox_17", MESG_CALENDAR_MONDAY },
            { "TextBox_18", MESG_CALENDAR_TUESDAY },
            { "TextBox_19", MESG_CALENDAR_WEDNESDAY },
            { "TextBox_20", MESG_CALENDAR_THURSDAY },
            { "TextBox_14", MESG_CALENDAR_FRIDAY },
            { "TextBox_15", MESG_CALENDAR_SATURDAY },
        };

        static const Calendar::DayToMsgId scWorldDayToMessageID[] = {
            { "TextBox_00", MESG_CALENDAR_MONDAY },
            { "TextBox_01", MESG_CALENDAR_TUESDAY },
            { "TextBox_02", MESG_CALENDAR_WEDNESDAY },
            { "TextBox_03", MESG_CALENDAR_THURSDAY },
            { "TextBox_04", MESG_CALENDAR_FRIDAY },
            { "TextBox_05", MESG_CALENDAR_SATURDAY },
            { "TextBox_06", MESG_CALENDAR_SUNDAY },
            { "TextBox_08", MESG_CALENDAR_MONDAY },
            { "TextBox_09", MESG_CALENDAR_TUESDAY },
            { "TextBox_10", MESG_CALENDAR_WEDNESDAY },
            { "TextBox_11", MESG_CALENDAR_THURSDAY },
            { "TextBox_12", MESG_CALENDAR_FRIDAY },
            { "TextBox_13", MESG_CALENDAR_SATURDAY },
            { "TextBox_07", MESG_CALENDAR_SUNDAY },
            { "TextBox_16", MESG_CALENDAR_MONDAY },
            { "TextBox_17", MESG_CALENDAR_TUESDAY },
            { "TextBox_18", MESG_CALENDAR_WEDNESDAY },
            { "TextBox_19", MESG_CALENDAR_THURSDAY },
            { "TextBox_20", MESG_CALENDAR_FRIDAY },
            { "TextBox_14", MESG_CALENDAR_SATURDAY },
            { "TextBox_15", MESG_CALENDAR_SUNDAY },
        };

        static const u32 scMonthToMessageID[] = {
            MESG_CALENDAR_JAN,
            MESG_CALENDAR_FEB,
            MESG_CALENDAR_MAR,
            MESG_CALENDAR_APR,
            MESG_CALENDAR_MAY,
            MESG_CALENDAR_JUN,
            MESG_CALENDAR_JUL,
            MESG_CALENDAR_AUG,
            MESG_CALENDAR_SEP,
            MESG_CALENDAR_OCT,
            MESG_CALENDAR_NOV,
            MESG_CALENDAR_DEC,
        };

        static const char* scPaneName_T_CalMonth[] = {
            "T_CalMonth_a",
            "T_CalMonth_b",
            "T_CalMonth_c",
        };

        static const char* scPaneName_N_Cal[] = {
            "N_Cal_a1",
            "N_Cal_b1",
            "N_Cal_c1",
        };

        static const char* scPaneName_N_CalPos[] = {
            "N_CalPos_a",
            "N_CalPos_b",
            "N_CalPos_c",
        };
        // clang-format on

        Calendar::Calendar(EGG::Heap* heap)
            : FaderSceneBase(heap), ButtonEventHandlerBase(), mState(STATE_NORMAL), mPrevState(STATE_NORMAL), mpLayout(NULL), mpLayoutFile(NULL),
              mpGroupAnim(NULL), mpInitAnim(NULL), mpBoardDate(NULL), mpSelectDate(NULL), mbScrolling(false), mbSearchTaskRunning(FALSE), mbTaskCanceled(FALSE),
              mbBackToBoardAlt(FALSE) {
            nw4r::ut::List_Init(&mDateList, offsetof(Date, mNode1));
            nw4r::ut::List_Init(&mDrawList, offsetof(Date, mNode2));

            mbAsian = System::getRegion() == SC_PRODUCT_AREA_JPN || (u32)System::getRegion() == SC_PRODUCT_AREA_KOR ||
                      (u32)System::getRegion() == SC_PRODUCT_AREA_CHN;
            mbUSA = System::getRegion() == SC_PRODUCT_AREA_USA;
        }

        void Calendar::prepare() {
            mpLayoutFile = System::getNandManager()->readLayoutAsync(getSceneHeap(), "calendar.ash");
        }

        void Calendar::create() {
            mpLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", "my_IplTop_g.brlyt");

            mpGroupAnim = mpLayout->bindToGroup("my_IplTop_g.brlan", "G_All", false);
            mpInitAnim = mpLayout->bindToGroup("my_IplTop_g.brlan", "G_Yobi");
            doAnim(IDANIM_0);
            mpLayout->calc();
            mpLayout->finishBinding();

            for (int i = 0; i < (DATE_COUNT * 2); i++) {
                Date* date = new Date(getSceneHeap(), mpLayoutFile, "arc", "my_IplTop_f.brlyt");
                if (i < DATE_COUNT) {
                    nw4r::ut::List_Append(&mDrawList, date);
                }
                nw4r::ut::List_Append(&mDateList, date);
            }

            set_date_pos(1);
            set_date_pos(2);

            Date* date = NULL;
            while ((date = (Date*)nw4r::ut::List_GetNext(&mDateList, date)) != NULL) {
                date->calc();
            }

            mpBoardDate = new utility::Date(static_cast<Board*>(getParent())->getDate());

            set_textbox_day();
            set_textbox_month();
            set_textbox_date(1, *mpBoardDate);
            exec_search_task();

            mpInitAnim->initAnmFrame(!mbAsian && !mbUSA ? 1 : 0);
        }

        void Calendar::calcCommon() {
            mpLayout->calc();
            set_date_pos(1);

            switch (mState) {
                case STATE_SCROLL_RIGHT: {
                    set_date_pos(2);
                    break;
                }
                case STATE_SCROLL_LEFT: {
                    set_date_pos(0);
                    break;
                }
                default: {
                    break;
                }
            }

            Date* date = NULL;
            while ((date = (Date*)nw4r::ut::List_GetNext(&mDateList, date)) != NULL) {
                date->calc();
            }
        }

        FaderSceneCommand Calendar::calcFadein() {
            Button* button;
            FaderSceneCommand result = FADER_SCN_CONTINUE;

            if (!mpLayout->isPlaying(IDANIM_0)) {
                button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                if (button != NULL) {
                    button->setEventHandler(this);

                    if (!is_lower_limit()) {
                        button->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                    }
                    if (!is_upper_limit()) {
                        button->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    }

                    result = FADER_SCN_NEXT;
                }
            }

            return result;
        }

        FaderSceneCommand Calendar::calcNormal() {
            switch (mState) {
                case STATE_NORMAL: {
                    on_normal();
                    break;
                }
                case STATE_SCROLL_RIGHT: {
                    on_scroll();
                    break;
                }
                case STATE_SCROLL_LEFT: {
                    on_scroll();
                    break;
                }
                case STATE_WAIT_TASK: {
                    on_wait_task();
                    break;
                }
                case STATE_WAIT_EXIT: {
                    on_wait_exit();
                    break;
                }
            }

            return mState == STATE_DONE ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
        }

        void Calendar::initCalcFadeout() {
            if (!mbBackToBoardAlt) {
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_BACK_TO_BOARD);
            } else {
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_BACK_TO_BOARD_ALT);
            }
        }

        FaderSceneCommand Calendar::calcFadeout() {
            return !mpLayout->isPlaying(IDANIM_0) ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
        }

        void Calendar::draw() {
            if (System::onDefaultDrawLayer()) {
                utility::Graphics::setOrtho();
                mpLayout->draw();

                if (mState == STATE_SCROLL_RIGHT || mState == STATE_SCROLL_LEFT) {
                    for (int i = (DATE_COUNT * 2) - 1; i >= 0; i--) {
                        ((Date*)nw4r::ut::List_GetNth(&mDateList, i))->draw(false);
                    }
                } else {
                    for (u32 i = 0; i < DATE_COUNT; i++) {
                        ((Date*)nw4r::ut::List_GetNth(&mDrawList, i))->draw(false);
                    }
                    for (u32 i = 0; i < DATE_COUNT; i++) {
                        ((Date*)nw4r::ut::List_GetNth(&mDrawList, i))->draw(true);
                    }
                }
            }
        }

        void Calendar::doAnim(int animId) {
            mpGroupAnim->setMinFrame(scAnmFrame[animId].start);
            mpGroupAnim->setMaxFrame(scAnmFrame[animId].end);
            mpGroupAnim->setAnmType(ANIM_TYPE_FORWARD);
            mpGroupAnim->play();
        }

        void Calendar::onEventDerived(u32 compId, u32 event, const controller::Interface* con) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();

            switch (event) {
                // Pointer click on button
                case ::gui::EventHandler::ON_TRIG: {
                    if (con->downTrg(controller::BTN_INTERACT)) {
                        if (Button::cmpButtonName(paneName, Button::BTN_EXIT) == 0) {
                            mbBackToBoardAlt = FALSE;
                            start_exit();
                            snd::getSystem()->startSE("WIPL_SE_CANCEL");
                        } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_RIGHT) == 0 && !is_upper_limit()) {
                            static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_SELECT);
                            start_scroll_r();
                        } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_LEFT) == 0 && !is_lower_limit()) {
                            static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_SELECT);
                            start_scroll_l();
                        }
                    }

                    break;
                }
            }
        }

        void Calendar::onPointDate(Date* date) {
            nw4r::ut::List_Remove(&mDrawList, date);
            nw4r::ut::List_Append(&mDrawList, date);
        }

        void Calendar::onTrigDate(Date* date) {
            if (mState == STATE_NORMAL) {
                static_cast<Board*>(System::getScene(SCENE_BOARD))->updateDate(*date->mpDate /*getDate() won't match*/);
                date->doAnim(Date::IDANIM_SELECT);
                mpSelectDate = date;
                snd::getSystem()->startSE("WIPL_SE_DATE_SELECT");
                mPrevState = mState;
                mState = STATE_WAIT_EXIT;
            }
        }

        void Calendar::on_normal() {
            Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
            if (button != NULL && button->isActive()) {
                button->update();
            }

            for (u32 i = 0; i < DATE_COUNT; i++) {
                ((Date*)nw4r::ut::List_GetNth(&mDateList, i))->update();
            }

            controller::Interface* con = System::getMasterController();
            if (con->down(controller::BTN_NEXT_LEFT) && !is_lower_limit()) {
                start_scroll_l();
            } else if (con->down(controller::BTN_NEXT_RIGHT) && !is_upper_limit()) {
                start_scroll_r();
            }
        }

        void Calendar::on_scroll() {
            if (mbScrolling) {
                switch (mState) {
                    case STATE_SCROLL_RIGHT: {
                        set_textbox_date(2, *mpBoardDate);
                        break;
                    }
                    case STATE_SCROLL_LEFT: {
                        set_textbox_date(0, *mpBoardDate);
                        break;
                    }
                    default: {
                        break;
                    }
                }
                mbScrolling = false;
            }

            if (!mpLayout->isPlaying(IDANIM_0)) {
                Date* date = NULL;
                while ((date = (Date*)nw4r::ut::List_GetNext(&mDateList, date)) != NULL) {
                    date->initEvent();
                }

                set_textbox_month();
                set_textbox_date(1, *mpBoardDate);
                doAnim(IDANIM_1);
                mpLayout->calc();
                set_date_pos(1);

                for (u32 i = 0; i < DATE_COUNT; i++) {
                    Date* date = ((Date*)nw4r::ut::List_GetNth(&mDateList, i));
                    date->mbAppearMsg = false;
                    date->doAnim(Date::IDANIM_NO_MSG);
                    date->calc();
                }

                exec_search_task();

                mPrevState = mState;
                mState = STATE_NORMAL;
            }
        }

        void Calendar::on_wait_task() {
            if (!mbSearchTaskRunning) {
                switch (mPrevState) {
                    case STATE_SCROLL_RIGHT: {
                        do_scroll_r();
                        break;
                    }
                    case STATE_SCROLL_LEFT: {
                        do_scroll_l();
                        break;
                    }
                    case STATE_DONE: {
                        do_exit();
                        break;
                    }
                }
            }
        }

        void Calendar::on_wait_exit() {
            if (!mpSelectDate->mpPaneAnims[Date::ANIM_PANE_BODY]->isPlaying()) {
                mbBackToBoardAlt = TRUE;
                start_exit();
            }
        }

        void Calendar::start_scroll_r() {
            if (mState != STATE_NORMAL && mState != STATE_WAIT_TASK) {
                return;
            }

            mPrevState = mState;
            mState = STATE_SCROLL_RIGHT;
            if (mbSearchTaskRunning == TRUE) {
                mbTaskCanceled = TRUE;
                mPrevState = STATE_SCROLL_RIGHT;
                mState = STATE_WAIT_TASK;
            } else {
                do_scroll_r();
            }
        }

        void Calendar::do_scroll_r() {
            Date* date = NULL;
            while ((date = (Date*)nw4r::ut::List_GetNext(&mDateList, date)) != NULL) {
                date->initEvent();
            }

            if (!is_upper_limit()) {
                if (is_lower_limit()) {
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                } else {
                    if (mpBoardDate->year == mscMaxDate.year && mpBoardDate->month == mscMaxDate.month - 1) {
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
                    }
                }

                utility::Calendar::getNextMonth(*mpBoardDate, mpBoardDate);
                doAnim(IDANIM_2);

                snd::getSystem()->startSE("WIPL_SE_CALENDAR_SCROLL");

                mbScrolling = true;
                mPrevState = mState;
                mState = STATE_SCROLL_RIGHT;
            }
        }

        void Calendar::start_scroll_l() {
            if (mState != STATE_NORMAL && mState != STATE_WAIT_TASK) {
                return;
            }

            mPrevState = mState;
            mState = STATE_SCROLL_LEFT;
            if (mbSearchTaskRunning) {
                mbTaskCanceled = TRUE;
                mPrevState = STATE_SCROLL_LEFT;
                mState = STATE_WAIT_TASK;
            } else {
                do_scroll_l();
            }
        }

        void Calendar::do_scroll_l() {
            Date* date = NULL;
            while ((date = (Date*)nw4r::ut::List_GetNext(&mDateList, date)) != NULL) {
                date->initEvent();
            }

            if (!is_lower_limit()) {
                if (is_upper_limit()) {
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                } else {
                    if (mpBoardDate->year == mscMinDate.year && mpBoardDate->month == mscMinDate.month + 1) {
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
                    }
                }

                utility::Calendar::getLastMonth(*mpBoardDate, mpBoardDate);
                doAnim(IDANIM_3);

                snd::getSystem()->startSE("WIPL_SE_CALENDAR_SCROLL");

                mbScrolling = true;
                mPrevState = mState;
                mState = STATE_SCROLL_LEFT;
            }
        }

        void Calendar::start_exit() {
            mPrevState = mState;
            mState = STATE_DONE;

            if (mbSearchTaskRunning == TRUE) {
                OSReport("検索タスク終了要求\n");  // "Search task termination requested"
                mbTaskCanceled = TRUE;
                mPrevState = mState;
                mState = STATE_WAIT_TASK;
            } else {
                do_exit();
            }
        }

        void Calendar::do_exit() {
            doAnim(IDANIM_4);

            if (!is_upper_limit()) {
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
            }
            if (!is_lower_limit()) {
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
            }

            static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(NULL, NULL);

            mPrevState = mState;
            mState = STATE_DONE;
        }

        void Calendar::set_textbox(const char* paneName, u32 msgId) {
            nw4r::lyt::TextBox* pane = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName(paneName));
            pane->SetString(System::getMessage(msgId));
        }

        void Calendar::set_textbox_day() {
            const DayToMsgId* list = mbAsian || mbUSA ? scJapanDayToMessageID : scWorldDayToMessageID;
            for (int i = 0; i < 21; i++) {
                set_textbox(list[i].paneName, list[i].msgId);
            }
        }

        void Calendar::set_textbox_month() {
            utility::Date last;
            utility::Date next;

            utility::Calendar::getLastMonth(*mpBoardDate, &last);
            utility::Calendar::getNextMonth(*mpBoardDate, &next);

            set_textbox_month(scPaneName_T_CalMonth[0], last);
            set_textbox_month(scPaneName_T_CalMonth[1], *mpBoardDate);
            set_textbox_month(scPaneName_T_CalMonth[2], next);
        }

        void Calendar::set_textbox_month(const char* paneName, const utility::Date& date) {
            wchar_t fullStr[32] = L"";
            const wchar_t numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

            int year = date.year;
            int i = 0;
            if (mbAsian) {
                fullStr[i++] = numbers[year / 1000];
                fullStr[i++] = numbers[(year / 100) % 10];
                fullStr[i++] = numbers[(year / 10) % 10];
                fullStr[i++] = numbers[year % 10];

                const wchar_t* msg = System::getMessage(scMonthToMessageID[date.month - 1]);
                wchar_t msgCh;
                do {
                    msgCh = *msg++;
                    fullStr[i++] = msgCh;
                } while (msgCh != 0);
            } else {
                const wchar_t* msg = System::getMessage(scMonthToMessageID[date.month - 1]);
                wchar_t msgCh;
                do {
                    msgCh = *msg++;
                    fullStr[i++] = msgCh;
                } while (msgCh != 0);
                i--;

                fullStr[i++] = ' ';
                fullStr[i++] = numbers[year / 1000];
                fullStr[i++] = numbers[(year / 100) % 10];
                fullStr[i++] = numbers[(year / 10) % 10];
                fullStr[i++] = numbers[year % 10];
            }

            nw4r::lyt::TextBox* pane = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName(paneName));
            pane->SetString(fullStr);
        }

        void Calendar::set_textbox_date(int calendarIndex, const utility::Date& date) {
            // MWCC needs this query call to retain the original instruction sequence.
            System::getLanguage();
            int monthEnd;
            int maxDays;
            int firstWeekday;
            firstWeekday = utility::Calendar::getWeek(date.year, date.month, 1);
            maxDays = utility::Calendar::getDays(date.year, date.month);

            OSCalendarTime curTime = System::getCurrentTime();

            utility::Date todayDate(curTime.year, curTime.mon + 1, curTime.mday);
            utility::Date lastMonth;
            utility::Date nextMonth;

            utility::Calendar::getLastMonth(date, &lastMonth);
            utility::Calendar::getNextMonth(date, &nextMonth);

            int listIndex;
            int trailingDays;
            if (mbAsian || mbUSA) {
                trailingDays = 6 - utility::Calendar::getWeek(date.year, date.month, maxDays);
            } else {
                firstWeekday--;
                if (firstWeekday < 0) {
                    firstWeekday = 6;
                }
                trailingDays = 6 - (utility::Calendar::getWeek(date.year, date.month, maxDays) - 1);
                if (trailingDays >= 7) {
                    trailingDays = 0;
                }
            }

            listIndex = calendarIndex == 1 ? 0 : DATE_COUNT;

            utility::Date cellDate;

            u32 attr;
            int visibleCellEnd;
            int dayIndex;
            for (dayIndex = 0; dayIndex < DATE_COUNT; dayIndex++) {
                Date* dateScn = ((Date*)nw4r::ut::List_GetNth(&mDateList, listIndex));
                listIndex++;
                dateScn->setVisible(true);

                monthEnd = (maxDays + firstWeekday);
                attr = 0;
                visibleCellEnd = (trailingDays + monthEnd);
                if ((firstWeekday - dayIndex) > 0) {
                    cellDate.year = lastMonth.year;
                    cellDate.month = lastMonth.month;
                    cellDate.day = dayIndex + (lastMonth.day - firstWeekday) + 1;
                } else if ((monthEnd - dayIndex) > 0) {
                    cellDate.year = date.year;
                    cellDate.month = date.month;
                    cellDate.day = (dayIndex - firstWeekday) + 1;
                    attr |= 2;

                    if (cellDate == todayDate) {
                        attr |= 1;
                    }

                    switch (utility::Calendar::getWeek(cellDate.year, cellDate.month, cellDate.day)) {
                        case 6: {
                            attr |= 8;
                            break;
                        }
                        case 0: {
                            attr |= 4;
                            break;
                        }
                    }
                } else if ((visibleCellEnd - dayIndex) > 0) {
                    cellDate.year = nextMonth.year;
                    cellDate.month = nextMonth.month;
                    cellDate.day = ((dayIndex - maxDays) - firstWeekday) + 1;
                } else {
                    dateScn->setVisible(false);
                    continue;
                }

                dateScn->setDate(cellDate);
                dateScn->setAttribute(attr);
            }
        }

        void Calendar::set_date_pos(int calendarIndex) {
            nw4r::lyt::Pane* pane1 = mpLayout->FindPaneByName(scPaneName_N_Cal[calendarIndex]);
            nw4r::lyt::Pane* pane2 = mpLayout->FindPaneByName(scPaneName_N_CalPos[calendarIndex]);

            int dateIndex = calendarIndex == 1 ? 0 : DATE_COUNT;

            for (int i = 0; (u32)i < DATE_COUNT; i++) {
                Date* dateScn = ((Date*)nw4r::ut::List_GetNth(&mDateList, dateIndex));
                dateIndex++;

                nw4r::math::VEC3 cellPos;
                cellPos.x = ((u16)i % 7) * 0x46;
                cellPos.y = ((u16)i / 7) * -0x30;
                cellPos.z = 0.0f;

                MTXMultVec(pane2->GetGlobalMtx(), cellPos, cellPos);

                dateScn->setTranslate(cellPos);
                dateScn->setRotate(pane1->GetRotate());
            }
        }

        BOOL search_task_cb_(void* work, CDBRecord* record) {
            if (System::getScene(SCENE_CALENDAR)) {
                Date* date = static_cast<Date*>(work);

                char type[RBR_FILETYPE_LENGTH] = "";
                CDBRecordGetTypeForce(record, type);

                date->mbAppearMsg = System::getCdbManager()->isTxtValidType(type);
                if (!date->mbAppearMsg) {
                    return TRUE;
                }

                date->doAnim(Date::IDANIM_APPEAR_MSG);
                date->calc();
            }

            return FALSE;
        }

        void search_task_(void* work) {
            Calendar* calendar = static_cast<Calendar*>(System::getSceneManager()->getScene(SCENE_CALENDAR));
            if (calendar != NULL) {
                for (u32 i = 0; i < DATE_COUNT; i++) {
                    if (calendar->mbTaskCanceled == TRUE) {
                        OSReport("タスクキャンセルされた\n");  // Task canceled
                        calendar->mbTaskCanceled = FALSE;
                        break;
                    }

                    Date* dateScn = ((Date*)nw4r::ut::List_GetNth(&calendar->mDateList, i));

                    if (dateScn->getVisible()) {
                        CDBDate begin = dateScn->mpDate->cdbDateBegin();
                        CDBDate end = dateScn->mpDate->cdbDateEnd();

                        cdb::Manager* cdbManager = System::getCdbManager();
                        cdbManager->search(begin, end, CDB_SEARCH_DIRECTION_RIGHT,
                                           cdbManager->isSDMounted() ? CDB_RECORD_LOCATION_ALL : CDB_RECORD_LOCATION_NAND, 0, search_task_cb_,
                                           dateScn);
                    }
                }

                OSReport("タスク終了\n");  // Task end

                calendar->mbSearchTaskRunning = FALSE;
                calendar->mbTaskCanceled = FALSE;
            }
        }

        void Calendar::exec_search_task() {
            OSReport("検索開始\n");  // Start search
            mbSearchTaskRunning = TRUE;
            System::getTask1()->requestJam(search_task_, this, NULL);
        }

        BOOL Calendar::is_upper_limit() {
            return mpBoardDate->year == mscMaxDate.year && mpBoardDate->month == mscMaxDate.month;
        }

        BOOL Calendar::is_lower_limit() {
            return mpBoardDate->year == mscMinDate.year && mpBoardDate->month == mscMinDate.month;
        }
    }  // namespace scene
}  // namespace ipl
