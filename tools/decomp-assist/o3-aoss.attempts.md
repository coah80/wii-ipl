# o3-aoss attempts (2026-10-09)

Worktree data-d1, branch agent/w1009/o3-aoss, base origin/main dbbdc3dd.
Scope: AOSS_Init_old (src/scene/setting/AOSS.c) and AOSSi_WLANConnect
(src/scene/setting/AOSSLink.c). Scratch in /tmp/o3-aoss.

## AOSS_Init_old

Start: 1235/1584 differing, 1580/1584 instructions (97.60%).

Evidence used: the DS build of the same library (/tmp/o2-aoss/ds-aoss.s)
keeps the helper names the Wii build inlines (aoss_release, aoss_set_error,
AOSS_Disconnect, SendMessage, AstsRestartReq, SetPacketHeader(buf, 0x3000,
0, 0, 0, 0x11, seq), SendPacketUDP, aoss_IP_sta).

1. Three missing instructions: after each AOSSConnectAndAwaitHost call the
   target has `cmpwi r3,0; bne wait; bne done; lwz; lwz; cmplwi 1; beq done`.
   The DS build has the same double branch. MWCC emits exactly this for
   `state != 0 || (state == 0 && *config != 1)` (second compare CSE'd, its
   branch kept). Written as `if (failed or not linked) { wait } else break`
   in all three loops: 1580 -> 1583 instructions, 1240 -> 1061 diffs.
2. IPv4 local address: target computes the broadcast address before the
   local one (orc before or, same rank, program order). Named
   `broadcastAddress` first (aoss_IP_sta shape): orc/or order fixed.
3. Register pressure: the reconnect path reused `requestResult` for the
   SOCleanup result, which put it in a callee-saved register across the
   loop and pushed the 0x11 message type out (rematerialized `li r0,0x11`).
   The target keeps that result in r0 (DS: AOSS_Disconnect()). Static
   inline AOSSCloseSocket() at all three close sites: 1061 -> 794 diffs,
   0x11 now lives in r14 like the target.
4. Last instruction: target stores the reserved byte from a fresh
   `li r0,0` instead of the shared zero register (it is SetPacketHeader's
   separate reserved argument). A named `requestReserved = 0` next to
   `requestMessageType = 0x11`, declared before it: 1584/1584, 147 diffs.
   Declared after requestMessageType: 149 (r14 swaps to the reserved byte).

Tried without effect: inline SetPacketHeader with char parameters (the
inliner substitutes constant arguments; same code as literals),
requestMessageType placement/type (u8/int/char, function entry, case 2,
loop head), pointer views for the send-address copy.

Checkpoint 1 (77895344): 147/1584 differing, 1584/1584 instructions, pool identical,
other 20 AOSS functions unchanged. Remaining: callee-saved register order
(attemptCount r31 vs r18, connection limit, reply length, protocolState),
preheader scheduling, networkAddresses load/store order, poll block order.

5. Hoisted loads: the target's r31 (retry limit) and the connect-loop
   limits are loop-invariant loads of the wait-settings fields, numbered at
   their codegen position. Comparing against `waitSettings.halfwords.high`
   and `waitIntervals.limits.connection` directly instead of copying them
   into `attemptCount`/`initialWait` puts r22..r31 in target order:
   147 -> 123.
6. Declaration order: hill-climb over Init_old's scalar declarations with
   the real compiler (/tmp/o3-aoss/dsearch.py, 6 seeds x 1500): 123 -> 97.
7. Poll block: the bus-clock read is a pointer load ordered against the
   descriptor array stores, so its position fixes the statement order:
   descriptor 0, tick computation (from locals), descriptor 1, then the
   timeval stores: 97 -> 78.

Scheduler model: /tmp/o3-aoss/sched2.py + blk.py port MWCC's list
scheduler and 750 pipeline; with GC/3.0a5.2 memory rules found empirically
(same-object struct fields at different offsets are independent, array
elements are not; pointer accesses alias globals and arrays but not local
structs; store->store memory edges have no latency) it reproduces 228/231
pre-RA scheduled blocks of the capture.

Checkpoint 2: 78/1584 differing, 1584/1584 instructions, pool identical.
Remaining: preheader order (target reuses r0 for the gateway and IP
constants, so gateway is stored before IP is formed), the send-address copy
(lwz/stw/lwz/stw in source order: looks like an unscheduled <=2-instruction
block, lever 36), callee-saved order in the scan and connect loops, and one
in-cycle store swap in the poll block.

8. Separate countdowns: the target gives the wait countdown a different
   register in each of the four wait loops (scan r21, connect-1 r17,
   connect-2 r16, connect-3 r17), so they are separate variables. Block-
   scoped countdowns: 78 -> 64. Block-scoped locals are numbered before
   function-scope ones, in reverse order of appearance (capture o3-bw1).
9. vmap2.py (capture vreg -> target register) left the scan/connect-1
   rotation: attemptCount spans both loops (degree 37) and is colored before
   the loop temps. A separate scan counter (scanAttempt): 64 -> 50.
10. Connect-1 countdown declared at function scope before attemptCount
   (numbered above it): 50 -> 38. Declaring it after attemptCount: 50.
11. packetWords block-scoped in case 2 (numbered below requestSocket):
   38 -> 21.

Checkpoint 3: 21/1584 differing, pool identical. Remaining: preheader
(gateway/IP constants share r0 in the target; li order 0x11, 0, 8), the
send-address copy, IPv4 mask/andc registers, poll store swap.

12. IPv4: the andc temp was colored before the mask (temps are colored
   before named locals) and took r3. A named host part declared between
   mask and network (aoss_IP_sta has the same three values): 21 -> 16.
   Declared after network: 23; mask as direct field reads: 22; inline
   helper with parameters: 21.

13. Preheader constants: LICM hoists loop-invariant `li` (named variables
   included) in loop block order, and constant propagation turns hoisted
   literal constants into copies of a dominating temp with the same value
   (a literal reply length 8 merges with the bind length r23 and loses an
   instruction). The target's reply length is a named value hoisted from
   case 2 between the header zero and the broadcast -1: setting
   replyAddressLength in case 2 and using it for the memset size too gives
   li order 0x11, 0, 8, -1, 1: 16 -> 14. Placed right before SOSendTo or
   after the address store: 16 (hoisted after the -1).

14. Scheduler model fixed (now 231/231 pre-RA blocks on five captures, post-RA
   all but a peephole block and one rematerialized-li block): an instruction
   issued to IU2 cannot take an operand forwarded from an integer-unit result
   in the same cycle, a store cannot take a value forwarded from IU2, and the
   ready-successor count only counts register edges (/tmp/o3-aoss/sched11.py).
   With it no ordering of the preheader could put the gateway store before the
   IP addi, which is what the target's shared r0 needs.
15. 0xf4/0xf8 are spill slots, not settings fields: the DS build stores the two
   constants straight into networkAddresses. Writing them in the loop lets LICM
   hoist the lis/addi pairs; RA spills them (an addi is not rematerialized) and
   reloads through r0 before each store, which is the target's
   `addi r0; stw r0, 0xf4` / `lwz r0, 0xf4; stw r0, 0x98` pattern. The fake
   gatewayAddress/ipAddress fields are gone (AOSSNetworkSettings is 0x3c, the
   size the memset clears): 14 -> 2.

16. Poll block: the DS build fills an fd set and AOSS_Select copies it into
   its own pollfd, passing one entry to SOPoll. So the two descriptors are
   separate objects, not a 2-element array: a one-element pollDescriptors
   array passed to SOPoll (an array, so the bus-clock pointer load stays
   ordered after its stores) and a separate readSet struct written after the
   tick computation (returnedEvents first): 2 -> 0. AOSS_Init_old exact.

## AOSSi_WLANConnect

Start: 2/155 (second memset `li r4; li r5; mr r3` in target).

Scheduler port (/tmp/o2-aoss/sched.py, matches MWCC Scheduler.c) shows the
target order needs either a third instruction on the address chain at
pre-RA scheduling time (removed after) or r4/r5 coming from copies emitted
before the r3 copy. Traced (mwdbg2): the pre-phase peephole retargets
single-use defs into copies, and GC/3.0a5.2 value numbering rewrites uses
of copies to the first holder, so every source-level copy collapses.

Tried, all 2 diffs: ipConfig declared/initialized in a nested block, at
the top (79), memset(&global), duplicate address computations (VN copy),
two live pointers, explicit copy variables, assignment in the argument,
casts and member-address forms of the first argument, scoped pragmas
(opt_propagation/common_subs/dead_code/lifetimes/dead_assignments/
loop_invariants/strength_reduction off, optimization_level 1-3,
ppc_iro_level 0/1) on copy variants, non-static/extern/aligned statics,
unpacked NCD types, unit flag variants (-O4,p / -O3 / inline modes).
IRO is genuinely off in the target (removing the aligned WD_Info local
makes IRO run and gives 155 diffs).

Session 2 (scheduler model and AOSSLink):
- AOSSLink is built -O4,s. Its pre-RA scheduler breaks ties by the number of
  non-call uses of the defined value before the ready-successor count
  (/tmp/o3-aoss/sched13.py reproduces all 17 pre-RA blocks of the
  WLANConnect captures; the same rule breaks four AOSS blocks, so it is
  -O4,s specific). The post-RA pass leaves almost every AOSSLink block as is.
- With that model no order of the memset block's own instructions gives the
  target `li r4; li r5; mr r3`: mr r3 always wins cycle 2 (rank 0). The
  target needs one more link on the address chain at scheduling time. A
  struct holding both NCD configs (`&s.ipConfig`) puts li r5 before mr r3 as
  predicted, but its +0x160 addi is not folded (156 instructions, 94 diffs).
  An extra copy of the address issued in cycle 2 also does it in the model
  (the second mr then sits in IU2 behind a forwarded operand), and RA would
  coalesce the copy away.
- Function-local statics (lever 35): both 2 diffs (fl1), IpConfig first or
  only IpConfig local: 8 (bss order).
- Why source copies never reach the scheduler (captures o3-as1, o3-d4,
  o3-d1w, o3-d6): the first VN pass (stage 07) turns a second computation of
  the address into `mr copy, first` and rewrites every use of the copy to the
  first holder, in later blocks and in moves too; copy propagation (stage 09)
  then deletes it. A copy only survives when its source is physical: with the
  address used by memset alone, the pre-phase retargets it into r3, VN's copy
  `mr r35, r3` survives and li r5 does move behind it (d1), but RA then keeps
  the address in r3 and the copy in r27 (`mr r27, r3`), the reverse of the
  target. Copies made by the second VN (stage 22/23, after LICM) do survive,
  but this block is not a loop preheader.
- Also 2 diffs: second pointer used for fields or only as the NCDSetIpConfig
  argument (c1-c4, d2-d8), inline fill helper (h1, h3), result = 0 before the
  memset or in its argument (r1, r3, r4). Passing the global straight to an
  inline setup helper rematerializes the address at each use (38).
