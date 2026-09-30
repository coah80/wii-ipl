# fa/pf_dir continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFDIR_GetSDD:
- normal path first, validation failure last: 69/69, 24 differences.
- common operation status exit: 69/69, 8 differences.
- Retained: [69, 69, 2].

PFDIR_p_fsexec_remove:
- normal path first, validation failure last: 178/176, 21 differences.
- common operation status exit: 178/176, 170 differences.
- Retained: [178, 176, 170].

PFDIR_opendir:
- Retained: [39, 39, 2].

PFDIR_p_fsnext:
- rotate independent local declarations: 193/193, 39 differences.
- normal path first, validation failure last: 192/193, 167 differences.
- common operation status exit: 193/193, 39 differences.
- Retained: [193, 193, 39].

PFDIR_p_rmdir:
- rotate independent local declarations: 203/202, 197 differences.
- normal path first, validation failure last: 202/202, 170 differences.
- common operation status exit: 203/202, 197 differences.
- Retained: [203, 202, 197].

PFDIR_p_fsexec:
- rotate independent local declarations: 207/280, 189 differences.
- normal path first, validation failure last: 207/280, 175 differences.
- common operation status exit: 207/280, 189 differences.
- Retained: [207, 280, 189].

PFDIR_p_move:
- rotate independent local declarations: 215/631, 212 differences.
- normal path first, validation failure last: 214/631, 212 differences.
- common operation status exit: 215/631, 212 differences.
- Retained: [215, 631, 212].

PFDIR_p_rename:
- rotate independent local declarations: 191/625, 182 differences.
- normal path first, validation failure last: 190/625, 184 differences.
- common operation status exit: 191/625, 182 differences.
- Retained: [191, 625, 182].

PFDIR_p_mkdir:
- rotate independent local declarations: 256/562, 254 differences.
- normal path first, validation failure last: 255/562, 243 differences.
- common operation status exit: 256/562, 254 differences.
- Retained: [256, 562, 254].

PFDIR_opendir is now instruction exact after restoring its status return type and retaining the read/open status across the handler-count update. Target r3 still holds the status at return; the former void definition allowed the count load to clobber it. No shared-header prototype changes were needed.

GetSDD additionally tried exchanging the two body increments (69/69, same two differences); compiler still schedules its derived volume-array pointer after the independent candidate pointer. Missing allocation and long-name update paths remain in mkdir, rename and move. Prior targeted three-attempt records are in fa-dir.md.
