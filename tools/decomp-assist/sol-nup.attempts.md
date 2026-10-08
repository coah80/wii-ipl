# sol-nup shape trials

Base f49f337c, branch agent/w1008/data-d4-h. Baseline pools identical: nup 28/28, www_wiisetting 72/72. Baseline differing counts: 66/452 and 14/609, equal sizes. Unrelated pre-existing untracked files retained.

- www/function-i: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-210942. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers.
- nup/helper-named-lengths: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-211223. simulator reproduces 182/182 virtual registers; best: 74/92 wanted registers.
- www/eur-outer-i: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-211301. simulator reproduces 312/312 virtual registers; best: 157/159 wanted registers.

Tracing adjustment: canceled the queued duplicate baseline Getter capture and queued named-next/dummy-outer captures. Remaining trials use private /tmp/sol-nup-mwdbg-fast.py and /tmp/sol-nup-gc3-fast.py, with the same pinned compiler, arguments, shared debugger lock, GPR before-simplify/final graphs, priority and PCode before/after/scheduling dumps. Per-event coalescing/color chatter and non-GPR allocation snapshots omitted. Every captured object must equal the normal Ninja object SHA256. /tmp/sol-nup-regsim.py additionally restricts permutation to source locals and accepts virtual IDs, excluding @ temporaries and fixed parameters. Initial function-i source-only check reaches 2/5 critical wants, not the unrestricted 159/159.

- www/dummy-outer-i: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-211905. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers.
- nup/helper-named-next: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-211905. simulator reproduces 173/173 virtual registers; best: 74/92 wanted registers.
- www/security-outer-i: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-212035. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers.
Trace queue isolation: private driver binds its stock emulator debugger socket to 9002 for nup and 9003 for Getter with /tmp/sol-nup-port.so, a bind-only LD_PRELOAD wrapper. The emulator and pinned compiler binaries remain unchanged; GDB uses the corresponding port and a private /tmp lock. Traced objects continue to require equality with Ninja objects.
- nup/helper-const-param-start: 434/452, size changed, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-212212. simulator reproduces 151/151 virtual registers.
- nup/helper-const-param-end: 434/452, size changed, pool FIRST DIVERGENCE at index 5
    3 mine=0x40     base=0x40
      M 'downloading content from server'
      B 'downloading content from server'
    4 mine=0x60     base=0x60
      M 'an error occurred'
      B 'an error occurred'
*   5 mine=0x90     base=0x90
      M '<Version>'
      B '</Version>'
*   6 mine=0x9c     base=0x9c
      M '</Version>'
      B '<Version>'
*   7 mine=0xa8     base=0xa8
      M '<DeviceId>'
      B '</DeviceId>'
*   8 mine=0xb4     base=0xb4
      M '</DeviceId>'
      B '<DeviceId>'
*   9 mine=0xc0     base=0xc0
      M '<MessageId>'
      B '</MessageId>'

mine has 28 strings, base has 28. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-212557. simulator reproduces 151/151 virtual registers.
- nup/helper-param-copy-tags: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-212637. simulator reproduces 162/162 virtual registers; best: 71/92 wanted registers.
- nup/helper-startlen-before-end: 477/496, size changed, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-212717. simulator reproduces 171/171 virtual registers.
- www/dummy-body-inc: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-212404. simulator reproduces 311/311 virtual registers; best: 158/159 wanted registers.
- nup/helper-length-return-expr: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-212758. simulator reproduces 173/173 virtual registers; best: 72/92 wanted registers.
- nup/helper-const-response: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-212839. simulator reproduces 162/162 virtual registers; best: 71/92 wanted registers.
- www/dummy-while: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-212830. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers.
- nup/call-result-blocks: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-212928. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/eur-while: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-212933. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers.
- nup/call-result-blocks-separate: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213008. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/parser-all-pointer-locals: 74/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213049. simulator reproduces 162/162 virtual registers; best: 64/92 wanted registers; source-only best: 67/92 wanted registers.
- www/eur-do: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-213035. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers.
- nup/parser-c89-locals: 74/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213127. simulator reproduces 162/162 virtual registers; best: 63/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/parser-c89-block-results: 74/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213211. simulator reproduces 162/162 virtual registers; best: 63/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/nested-SkipTag: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213250. simulator reproduces 173/173 virtual registers; best: 70/92 wanted registers; source-only best: 67/92 wanted registers.
- www/mask-helper-return: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-213238. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 157/159 wanted registers.
- nup/nested-SkipTagConst: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213330. simulator reproduces 173/173 virtual registers; best: 70/92 wanted registers; source-only best: 67/92 wanted registers.
- www/mask-return-eur-helper: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-213344. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 157/159 wanted registers.
- nup/nested-TagSpan: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213418. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/nested-TagSpanRef: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213457. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/mask-helper-ref: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-213442. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-03124: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213537. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/mask-ref-eur-helper: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-213539. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-03412: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213631. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/mask-helper-ptr: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-213650. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-04312: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213710. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/params-01243: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213754. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/mask-ptr-eur-helper: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-213753. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-04123: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213830. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/eur-helper-ref: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-213847. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-30124: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213905. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/params-30412: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-213942. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/eur-helper-ptr: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-213942. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-40312: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214017. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/dummy-front: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214036. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-40123: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214054. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/params-34012: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214131. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/dummy-after-ret: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214130. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-43012: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214207. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/params-12034: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214247. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/dummy-after-prop: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214226. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-12043: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214324. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/eur-front: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214326. simulator reproduces 312/312 virtual registers; best: 157/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-31204: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214400. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/eur-after-ret: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214419. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/params-12304: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214437. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/params-12403: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214514. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/eur-after-prop: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214513. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- www/security-front: compile failed. /tmp/sol-nup-www-security-front.build.txt
- www/security-after-ret: compile failed. /tmp/sol-nup-www-security-after-ret.build.txt
- www/security-after-prop: compile failed. /tmp/sol-nup-www-security-after-prop.build.txt
- nup/tag-types-char-cchar: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214549. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/tag-types-cchar-char: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214624. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/dummy-eur-front: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214609. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/tag-types-char-char: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214659. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/dummy-eur-after-ret: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214703. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/helper-unsigned-length: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214735. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/helper-param-value-ref: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214810. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/dummy-eur-after-prop: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214756. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 156/159 wanted registers.
- www/all-front: compile failed. /tmp/sol-nup-www-all-front.build.txt
- www/all-after-ret: compile failed. /tmp/sol-nup-www-all-after-ret.build.txt
- www/all-after-prop: compile failed. /tmp/sol-nup-www-all-after-prop.build.txt
- nup/helper-param-length-ref: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214845. simulator reproduces 162/162 virtual registers; best: 67/92 wanted registers; source-only best: 67/92 wanted registers.
- www/key-length-ref: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214853. simulator reproduces 313/313 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/title-count-helper: 66/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214922. simulator reproduces 162/162 virtual registers; best: 72/92 wanted registers; source-only best: 67/92 wanted registers.
- nup/caller-tags-function-assign: 97/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-214959. simulator reproduces 162/162 virtual registers; best: 65/92 wanted registers; source-only best: 56/92 wanted registers.
- www/key-length-ref-eur: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-214948. simulator reproduces 313/313 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/caller-tags-function-const: 97/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-215036. simulator reproduces 162/162 virtual registers; best: 65/92 wanted registers; source-only best: 56/92 wanted registers.
- www/key-length-ptr: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215043. simulator reproduces 313/313 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- nup/caller-tags-block-assign: 100/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-215112. simulator reproduces 162/162 virtual registers; best: 63/92 wanted registers; source-only best: 56/92 wanted registers.
- nup/caller-tags-block-const: 100/452, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/__nupParseServerInfo__FP14NUPContextInfoPcPcUx-20261008-215150. simulator reproduces 162/162 virtual registers; best: 63/92 wanted registers; source-only best: 56/92 wanted registers.
- www/key-length-ptr-eur: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215138. simulator reproduces 313/313 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.

NUP round finished: 44 compiled source trials, no exact candidate. Best 66/452, equal size and identical pool. Argument-order and output-type variants reproduce the baseline 162-vreg graph and cannot remove 25 target coloring misses through source-local reorder. Const tag parameters fold strlen and fail equal-size/pool criteria. Best diff saved outside the repository at /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-nup.nup.diff. Restored nup.cpp to HEAD and rebuilt; restored differing count 66/452 and pool 28/28 identical.

- www/mask-shared-index: 20/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215231. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 156/159 wanted registers.
- www/mask-shared-index-eur: 20/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215324. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 156/159 wanted registers.
- www/mask-buffer-function: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215419. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- www/mask-buffer-function-eur: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215512. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- www/mask-explicit-update-eur: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215606. simulator reproduces 311/311 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- www/mask-local-buffer-first: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215659. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 157/159 wanted registers.
- www/mask-local-buffer-first-eur: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215753. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 157/159 wanted registers.
- www/mask-local-index-first: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215846. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 157/159 wanted registers.
- www/mask-local-index-first-eur: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-215942. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 157/159 wanted registers.
- www/prepare-mask-buffer-first: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-220037. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 157/159 wanted registers.
- www/prepare-mask-buffer-first-eur: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-220141. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 157/159 wanted registers.
- www/prepare-mask-index-first: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-220239. simulator reproduces 312/312 virtual registers; best: 159/159 wanted registers; source-only best: 157/159 wanted registers.
- www/prepare-mask-index-first-eur: 9/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-220333. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 157/159 wanted registers.
- www/mask-reference-index-local-buffer-void: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-220507. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.
- www/mask-reference-index-local-buffer-return-buffer: 14/609, size equal, pool identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue-20261008-220636. simulator reproduces 312/312 virtual registers; best: 158/159 wanted registers; source-only best: 156/159 wanted registers.

Getter round finished: best 9/609 from mask-helper-return, equal size and identical pool. Four surviving buffer-register differences and five European-counter differences. Best diff saved outside the repository at /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-nup.www_wiisetting.diff. Scope-generator compile failures were malformed privacyIndexpl namespace replacements, not compiler limitations. No non-exact source change retained.

Restored verification:
- libs/RVL_SDK/src/nup/nup: POOL IDENTICAL up to 28 (mine=28 base=28), src size 0x710 base size 0x710, differing: 66 / 452.
- src/iplwww/www_wiisetting: POOL IDENTICAL up to 72 (mine=72 base=72), src size 0x984 base size 0x984, differing: 14 / 609.

Final requested quick gate on restored source:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/nup/nup] pool: IDENTICAL
[libs/RVL_SDK/src/nup/nup] objdiff: code 8956/10764 data 1720/1720 functions 22/23 fuzzy 99.8774 linked code 0
[libs/RVL_SDK/src/nup/nup] instruction-exact functions: 22/23
[libs/RVL_SDK/src/nup/nup]   section .data size 1592 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .rodata size 88 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .text size 10764 match 99.87737
[libs/RVL_SDK/src/nup/nup]   below 100: __nupParseServerInfo__FP14NUPContextInfoPcPcUx 99.26991
[libs/RVL_SDK/src/nup/nup] baseline: code 8956/10764 data 1720 functions 22 fuzzy 99.8774
[src/iplwww/www_wiisetting] pool: IDENTICAL
[src/iplwww/www_wiisetting] objdiff: code 3740/6176 data 3856/3856 functions 20/21 fuzzy 99.9450 linked code 0
[src/iplwww/www_wiisetting] instruction-exact functions: 20/21
[src/iplwww/www_wiisetting]   section .bss size 104 match 100.0
[src/iplwww/www_wiisetting]   section .data size 2576 match 100.0
[src/iplwww/www_wiisetting]   section .rodata size 792 match 100.0
[src/iplwww/www_wiisetting]   section .sbss size 32 match 100.0
[src/iplwww/www_wiisetting]   section .sdata size 320 match 100.0
[src/iplwww/www_wiisetting]   section .sdata2 size 32 match 100.0
[src/iplwww/www_wiisetting]   section .text size 6176 match 99.94495
[src/iplwww/www_wiisetting]   below 100: Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue 99.86043
[src/iplwww/www_wiisetting] baseline: code 3740/6176 data 3856 functions 20 fuzzy 99.9450
regressions vs baseline: 0
global matched_code_percent: 97.58331 -> 97.58331
global fuzzy_match_percent: 99.89996 -> 99.89996
global complete_code_percent: 88.95958 -> 88.95958
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d
```

Handoff: nup 44 compiled trials; Getter 50 source trials, 44 compiled and 6 generator compile failures. Exact functions unchanged: nup 22/23 -> 22/23, www_wiisetting 20/21 -> 20/21. No Matching flag changed, no source candidate retained, no push or PR. Final gate passed with 0 regressions, 0 forbidden patterns and 0 readability warnings.

## Round 2, xhigh, Getter only

HEAD d3888148; origin/main fetched, owned source unchanged upstream. Replayed saved best: 9/609, 609/609 instructions, pool 72/72 identical. Trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/sol-nup-r2-best, byte-identical Ninja object SHA256 adb513a9cfd2cd56cb17bd5aa1549c95ef0386465668922fb5c16c6ce3bd59c5. vmap2 want-list has 159 unambiguous virtuals; residual country counter and dummy-key buffer. New source trials use whole-word counter renaming to avoid the prior malformed namespace replacements.

- r2/c89-counters-False-0: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 20517c983b59.
- r2/c89-all-locals-False-0: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 20517c983b59.
- r2/c89-counters-False-1: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 20517c983b59.
- r2/c89-all-locals-False-1: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 20517c983b59.
- r2/c89-counters-True-0: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 89c900f6d5c6.
- r2/c89-all-locals-True-0: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 89c900f6d5c6.
- r2/saved-mask-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 3b8f3228dae8.
- r2/saved-and-country-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object dc2d52f3737d.
- r2/saved-helper-while: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 3b8f3228dae8.
- r2/saved-helper-while-eur: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object dc2d52f3737d.
- r2/saved-helper-do: 417/611, insns 611/609, pool identical; first [34, 40, 62, 68, 117, 121, 130, 133, 136, 140, 144, 148]; object 8b1e2a042f28.
- r2/saved-helper-do-eur: 417/611, insns 611/609, pool identical; first [34, 40, 62, 68, 117, 121, 130, 133, 136, 140, 144, 148]; object 26cd1a48a8a8.
- r2/saved-helper-body-plus: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 3b8f3228dae8.
- r2/saved-helper-body-plus-eur: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object dc2d52f3737d.
- r2/saved-helper-compound: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 3b8f3228dae8.
- r2/saved-helper-compound-eur: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object dc2d52f3737d.
- r2/saved-helper-unsigned-long: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 28f72566ec9f.
- r2/saved-helper-unsigned-long-eur: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object c9a8edfe710b.
Best-source simulator: 312/312 captured virtuals reproduced; movable locals: i, kbLang, staIdx, i, retVal | identity order: 157/159 wanted; wrong: i(v35) r25->r31, @17442(v41) r28->r25 | best locals-only order: 157/159 wanted |   order: i(v35), kbLang(v36), staIdx(v37), i(v38), retVal(v39) |   still wrong: i(v35) sim r25 want r31; @17442(v41) sim r28 want r25 |
- r2/parameter-local-obj: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object 3d23409d7baf.
- r2/parameter-local-obj-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object d1c797afa424.
- r2/parameter-local-str: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object 3d23409d7baf.
- r2/parameter-local-str-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object d1c797afa424.
- r2/parameter-local-val: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object 3d23409d7baf.
- r2/parameter-local-val-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object d1c797afa424.
- r2/parameter-local-str-val: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object 414999ec87ae.
- r2/parameter-local-str-val-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 945bbb9c116e.
- r2/parameter-local-obj-str-val: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object 106ffe65d6cc.
- r2/parameter-local-obj-str-val-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 96797c44f063.
- r2/shared-mask-format-helper: 400/609, insns 596/609, pool identical; first [34, 40, 62, 68, 117, 121, 130, 133, 136, 140, 144, 148]; object 4d95d18eae9d.
- r2/saved-and-shared-format-helper: 404/609, insns 596/609, pool identical; first [34, 40, 62, 68, 117, 121, 130, 133, 136, 140, 144, 148]; object 1ab31ade119e.
- r2/three-branches-shared-format-helper: 404/609, insns 596/609, pool identical; first [34, 40, 62, 68, 117, 121, 130, 133, 136, 140, 144, 148]; object 1632fabf27bb.
- r2/saved-complete-mask-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 3c8ebc4e3eb3.
- r2/saved-complete-and-eur-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 7d2083688556.
- r2/no-output-dummy-saved-return: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object d75f3865ce83.
- r2/no-output-dummy-saved-return-eur: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object ed4543f88d81.
- r2/no-output-dummy-saved-complete: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object eefd135fbdec.
- r2/no-output-dummy-saved-complete-eur: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 00997c2fecbf.
- r2/c89-all-callback-calendar-and-idle-False: 25/609, insns 609/609, pool identical; first [24, 38, 86, 91, 100, 217, 221, 222, 226, 228, 235, 255]; object 51da6aeb0dac.
- r2/c89-all-callback-calendar-and-idle-True: 25/609, insns 609/609, pool identical; first [24, 38, 86, 91, 100, 217, 221, 222, 226, 228, 235, 255]; object 4d7a8a250ac6.
- r2/country-not-equal-plus-saved-helper: 16/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object c3c6c8616589.
- r2/country-inclusive-plus-saved-helper: 16/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 5339cf502377.
- r2/dummy-helper-definition-after: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object 3d23409d7baf.
- r2/dummy-helper-after-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object d1c797afa424.
- r2/dummy-helper-after-country-helper: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object 09853ef54039.
- r2/settings-branch-helper-after-callback: 25/609, insns 609/609, pool identical; first [91, 92, 94, 95, 96, 97, 99, 103, 217, 221, 222, 226]; object c6803a43c8dc.
- r2/settings-branch-helper-local-params: compile failed; /tmp/sol-nup-r2-settings-branch-helper-local-params.build.txt
- r2/dummy-size-return-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 3b8f3228dae8.
- r2/dummy-size-return-country-helper: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object c9626c825d1c.
- r2/dummy-named-length-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 8bb75d5d012a.
- r2/dummy-named-length-country-helper: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object cfd64a93a33a.
- r2/dummy-named-key-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 8bb75d5d012a.
- r2/dummy-named-key-country-helper: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object cfd64a93a33a.
- r2/dummy-signed-size-counter-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 3b8f3228dae8.
- r2/dummy-signed-size-counter-country-helper: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object c9626c825d1c.
- r2/dummy-unsigned-size-counter-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 3b8f3228dae8.
- r2/dummy-unsigned-size-counter-country-helper: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object c9626c825d1c.
- r2/dummy-index-cast-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 3b8f3228dae8.
- r2/dummy-index-cast-country-helper: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object c9626c825d1c.
- r2/dummy-while-named-length-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 8bb75d5d012a.
- r2/dummy-while-named-length-country-helper: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object cfd64a93a33a.
- r2/dummy-for-comma-condition-saved-helper: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 945bbb9c116e.
- r2/dummy-for-comma-condition-country-helper: 9/609, insns 609/609, pool identical; first [255, 258, 259, 267, 578, 583, 589, 592, 593]; object a969d6389491.
- r2/pair-counter-privacy-country: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object 03ecf03594cd.
- r2/pair-counter-privacy-dummy: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object b5173e5fe1c8.
- r2/pair-counter-dummy-country: 15/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 255, 258, 259, 267, 578, 583]; object b5173e5fe1c8.
- r2/numeric-branch-helper-reference: 89/614, insns 614/609, pool identical; first [12, 34, 37, 39, 40, 62, 65, 67, 68, 84, 100, 101]; object 8622456dd751.
- r2/numeric-branch-helper-reference-c89: 89/614, insns 614/609, pool identical; first [12, 34, 37, 39, 40, 62, 65, 67, 68, 84, 100, 101]; object 8622456dd751.
- r2/numeric-branch-helper-pointer: 89/614, insns 614/609, pool identical; first [12, 34, 37, 39, 40, 62, 65, 67, 68, 84, 100, 101]; object 8622456dd751.
- r2/numeric-branch-helper-pointer-c89: 89/614, insns 614/609, pool identical; first [12, 34, 37, 39, 40, 62, 65, 67, 68, 84, 100, 101]; object 8622456dd751.
- r2/numeric-branch-helper-value: 390/623, insns 623/609, pool identical; first [0, 2, 3, 8, 11, 12, 34, 37, 39, 40, 62, 65]; object 30eb4477509f.
- r2/numeric-branch-helper-value-c89: 390/623, insns 623/609, pool identical; first [0, 2, 3, 8, 11, 12, 34, 37, 39, 40, 62, 65]; object 30eb4477509f.
- r2/callback-branch-helper-status: 573/618, insns 618/609, pool identical; first [7, 12, 13, 17, 24, 32, 33, 34, 35, 36, 37, 38]; object 55fd51e8a6ed.
- r2/callback-and-saved-branch-helper: 573/618, insns 618/609, pool identical; first [7, 12, 13, 17, 24, 32, 33, 34, 35, 36, 37, 38]; object 6e451c0643ab.
- r2/callback-and-country-branch-helper: 573/618, insns 618/609, pool identical; first [7, 12, 13, 17, 24, 32, 33, 34, 35, 36, 37, 38]; object ee034332bc70.
- r2/country-code-range-loop: 44/609, insns 608/609, pool identical; first [34, 40, 62, 68, 255, 258, 259, 267, 275, 282, 287, 537]; object 9def6ff5b014.
- r2/country-code-range-plus-saved-helper: 50/609, insns 608/609, pool identical; first [34, 40, 62, 68, 217, 221, 222, 226, 228, 235, 255, 258]; object 60d462954ea1.
- r2/settings-helper-status-last: 25/609, insns 609/609, pool identical; first [91, 92, 94, 95, 96, 97, 99, 103, 217, 221, 222, 226]; object c6803a43c8dc.
- r2/settings-helper-country-last: 25/609, insns 609/609, pool identical; first [91, 92, 94, 95, 96, 97, 99, 103, 217, 221, 222, 226]; object c6803a43c8dc.
- r2/settings-helper-buffer-first: 25/609, insns 609/609, pool identical; first [91, 92, 94, 95, 96, 97, 99, 103, 217, 221, 222, 226]; object c6803a43c8dc.

Property helper trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/sol-nup-r2-propertyhelper: identical to Ninja SHA256 c6803a43c8dccd5600fc23b14e83ed6df7211c0d200c68af4a41bffeb7d15401. movable locals:  | identity order: 154/159 wanted; wrong: @17171(v40) r26->r25, @17165(v43) r26->r31, @17161(v47) r5->r4, @17160(v48) r4->r5, @17157(v49) r28->r26 | best locals-only order: 154/159 wanted |   order:  |   still wrong: @17171(v40) sim r26 want r25; @17165(v43) sim r26 want r31; @17161(v47) sim r5 want r4; @17160(v48) sim r4 want r5; @17157(v49) sim r28 want r26 |
- r2/propertyhelper-swap-name-cursors: 17/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 252, 255, 256, 261, 263, 269]; object 4b4a5f93f187.
- r2/propertyhelper-source-first-assignments: 17/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 252, 255, 256, 261, 263, 269]; object 4b4a5f93f187.
- r2/propertyhelper-destination-first-assignments: 17/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 252, 255, 256, 261, 263, 269]; object 4b4a5f93f187.
- r2/propertyhelper-c89-counters-False: 19/609, insns 609/609, pool identical; first [91, 92, 94, 95, 96, 97, 99, 103, 252, 255, 256, 261]; object 03a252afab01.
- r2/propertyhelper-c89-cursors-False: 11/609, insns 609/609, pool identical; first [252, 255, 256, 261, 263, 269, 578, 583, 589, 592, 593]; object 57d0e4cdb981.
- r2/propertyhelper-c89-counters-True: 19/609, insns 609/609, pool identical; first [91, 92, 94, 95, 96, 97, 99, 103, 252, 255, 256, 261]; object 226a6418146c.
- r2/propertyhelper-c89-cursors-True: 11/609, insns 609/609, pool identical; first [252, 255, 256, 261, 263, 269, 578, 583, 589, 592, 593]; object d2bc1a6736c2.
- r2/propertyhelper-dummy-no-output: 25/609, insns 609/609, pool identical; first [91, 92, 94, 95, 96, 97, 99, 103, 217, 221, 222, 226]; object fe3a8873aa75.
- r2/propertyhelper-dummy-no-output-cursors: 17/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 252, 255, 256, 261, 263, 269]; object a8839ffeeb74.
- r2/propertyhelper-status-before-loop-cursors: 17/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 252, 255, 256, 261, 263, 269]; object a9598eff513d.
- r2/propertyhelper-all-loops-inline: 14/609, insns 609/609, pool identical; first [252, 255, 256, 258, 259, 261, 263, 267, 269, 578, 583, 589]; object 273f9c9bf89d.
- r2/propertyhelper-inline-mask-locals-0: 14/609, insns 609/609, pool identical; first [252, 255, 256, 258, 259, 261, 263, 267, 269, 578, 583, 589]; object 273f9c9bf89d.
- r2/propertyhelper-inline-mask-locals-1: 14/609, insns 609/609, pool identical; first [252, 255, 256, 258, 259, 261, 263, 267, 269, 578, 583, 589]; object 273f9c9bf89d.
- r2/propertyhelper-inline-mask-locals-2: 11/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 578, 583, 589, 592, 593]; object 7c2ec6e45b93.
- r2/propertyhelper-inline-mask-locals-3: 14/609, insns 609/609, pool identical; first [252, 255, 256, 258, 259, 261, 263, 267, 269, 578, 583, 589]; object 273f9c9bf89d.
- r2/propertyhelper-inline-mask-locals-4: 11/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 578, 583, 589, 592, 593]; object 7c2ec6e45b93.
- r2/propertyhelper-inline-mask-locals-5: 14/609, insns 609/609, pool identical; first [252, 255, 256, 258, 259, 261, 263, 267, 269, 578, 583, 589]; object 273f9c9bf89d.
- r2/propertyhelper-inline-mask-locals-6: 20/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 252, 255, 256, 258, 259, 261]; object a8ccb66be7f6.
- r2/propertyhelper-inline-mask-locals-7: 11/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 578, 583, 589, 592, 593]; object 7b705cfc8998.
- r2/propertyhelper-inline-mask-locals-8: 20/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 252, 255, 256, 258, 259, 261]; object 9047ddf09c18.
- r2/propertyhelper-inline-mask-locals-9: 20/609, insns 609/609, pool identical; first [217, 221, 222, 226, 228, 235, 252, 255, 256, 258, 259, 261]; object 9047ddf09c18.

Property-helper source-group diagnostic: real getSettingProperty locals v39..v43 plus getStringPropertyIdx pointer locals v47/v48 reach at most 157/159 in 30000 numbering trials. Reversing the two real name-cursor declarations compiled away all eight copy-loop differences. C89 counters then restore the saved-key loop, but dummy counter stays r28 vs r26 and country counter stays r25 vs r31, 11/609. No arbitrary optimizer temporary renumbering or allocator change is installed. Source-group diagnostic: /tmp/sol-nup-r2-helper-order.py and /tmp/sol-nup-r2-helper-order.json.
- r2/propertyhelper-counter-order-0: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/propertyhelper-counter-order-1: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/propertyhelper-counter-order-2: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/propertyhelper-counter-order-3: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object 3bbed91a5c9d.
- r2/propertyhelper-counter-order-4: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/propertyhelper-counter-order-5: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object 3bbed91a5c9d.

New clean best 5/609: propertyhelper-counter-order-0. Real getSettingProperty helper after Getter, distinct meaningful counters at its top, local buffer with no output-parameter hoist, and reordered getStringPropertyIdx cursor declarations. Instructions 609/609, pool 72/72 identical, Getter objdiff 99.95074; siblings 20/20 at 100; code 3740/6176, data 3856/3856 with every data section 100. All five differences use the European counter r26 instead of r31 (578, 583, 589, 592, 593). New best replaces the saved nine-diff file outside the repository. This is not an exact match and is not linked.

Five-diff trace /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/sol-nup-r2-five: byte-identical to native object SHA256 b5a5ef4c2cc214d53fa8bcee3abc7db77f0e24d96a291f2e6ea595cbf890f9ca. simulator reproduces 312/312 virtual registers | movable locals:  | identity order: 158/159 wanted; wrong: @17155(v42) r26->r31 | best locals-only order: 158/159 wanted |   order:  |   still wrong: @17155(v42) sim r26 want r31 |
- r2/five-country-while: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/five-country-do: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object 4cad17f96f96.
- r2/five-country-pre-inc: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/five-country-body-inc: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/five-country-no-initializer-for: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/five-country-inclusive-limit: 6/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593, 594]; object 68a70cdd5835.
- r2/five-country-not-equal-limit: 6/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593, 594]; object b7c5460aff61.
- r2/five-country-share-privacyIndex: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object 3a9b4ae9b42d.
- r2/five-country-share-maskLength: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object 3a9b4ae9b42d.
- r2/five-country-share-staIdx: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object 3a9b4ae9b42d.
- r2/five-country-scope-region: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/five-country-scope-country: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/five-country-scope-byte-property: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/five-country-scope-after-result: 5/609, insns 609/609, pool identical; first [578, 583, 589, 592, 593]; object b5a5ef4c2cc2.
- r2/five-country-lookup-helper: 0/609, insns 609/609, pool identical; first []; object b2f07c2675ff.
- link/Message-const-pointers: compiled; Message record inspected, no source retained.
- link/Message-char-const-pointers: compiled; Message record inspected, no source retained.

## Exact result and linking

Getter reached 0/609 after 120 compiled Round 2 source trials. Final source uses a real getSettingProperty helper, separate saved/dummy mask counters declared at its top, reversed source/destination cursor declarations in the existing name lookup, and a real selectEuropeanKeyboardLanguage helper. The country helper writes only when a table entry matches; the pre-existing unmatched-country behavior is unchanged. No new uninitialized local, artificial inline assembly, carrier for allocator locals, use-site volatile cast, padding, forced section, or identity helper.

First Matching flip retained native 21/21 code but failed DOL SHA1 18eda0e06fe300a1f1fb770755b0f3fb87ee916f. Native .sbss placed gDpdWaitFrm at +24, target +0. Changing its initializer alone did not reorder it. The target logging block is one 0x38-byte object with tags at +0/+12/+22 and six zero pointers at +32, with no relocation at Message[4] (+48). The old source put an emptyString pointer there and emitted an extra .sbss2 byte. A direct empty literal shifted .sdata and still failed SHA1 0cecccf88a607d9f7520cad8ddca4e174d6bbc0f. Moving the real gDpdWaitFrm definition before the header-owned statics fixed all .sbss offsets. A separate all-null Message array moved to .bss, shifting the pool by 24 bytes and leaving four instruction differences; SHA1 1357c86397d37e2dec02a1970deb0cfea41026db. Const-pointer table trials were discarded by the compiler.

Final logging reconstruction is a real ReportInfo record containing the three fixed-size tags and the six message pointers. Existing src/iplwww/www_print.cpp uses reportInfo.MessageArr in its enabled logging path, and the retail object owns exactly those 56 contiguous bytes. This is a message record, not an allocator carrier or padding object. Its first 56 data bytes and absence of relocations are identical to target. Initialized tags naturally keep the zero pointer table in .data. No header or symbols/splits file changed.

Final Matching link: Getter 609/609, ctxdiff 0, objdiff 100.0; every one of 21 functions and every owned section is 100.0; code 6176/6176 and data 3856/3856, both 100% linked. Pool 72/72 identical. Full DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Final gate follows.

Requested final quick gate, exact linked source:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/iplwww/www_wiisetting] pool: IDENTICAL
[src/iplwww/www_wiisetting] objdiff: code 6176/6176 data 3856/3856 functions 21/21 fuzzy 100.0000 linked code 6176
[src/iplwww/www_wiisetting] instruction-exact functions: 21/21
[src/iplwww/www_wiisetting]   section .bss size 104 match 100.0
[src/iplwww/www_wiisetting]   section .data size 2576 match 100.0
[src/iplwww/www_wiisetting]   section .rodata size 792 match 100.0
[src/iplwww/www_wiisetting]   section .sbss size 32 match 100.0
[src/iplwww/www_wiisetting]   section .sdata size 320 match 100.0
[src/iplwww/www_wiisetting]   section .sdata2 size 32 match 100.0
[src/iplwww/www_wiisetting]   section .text size 6176 match 100.0
[src/iplwww/www_wiisetting] baseline: code 3740/6176 data 3856 functions 20 fuzzy 99.9450
regressions vs baseline: 0
global matched_code_percent: 97.58331 -> 97.66464
global fuzzy_match_percent: 99.89996 -> 99.90007
global complete_code_percent: 88.95958 -> 89.16578
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```

Changed tracked paths: src/iplwww/www_wiisetting.cpp, configure.py, tools/decomp-assist/sol-nup.attempts.md. Pre-existing untracked files preserved. No push, PR, merge, rebase, shared-header edit, cross-worktree edit, or subagent spawn. Final best source diff refreshed outside the repository at _luna-runs/best/sol-nup.www_wiisetting.diff. Parent must rerun its independent gates before integration.
