# fa/pf_file continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFFILE_GetSFD:
- normal path first, validation failure last: 113/113, 68 differences.
- common operation status exit: 113/113, 24 differences.
- split local declaration from initialization: compile failed: --------------------
#     652:     PFFILE_SFD* first_free_sfd = PF_NULL; 
#   Error:     ^^^^^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
.
- Retained: [113, 113, 18].

PFFILE_fread:
- rotate independent local declarations: 97/67, 28 differences.
- common operation status exit: 97/67, 28 differences.
- reverse independent local declarations: 97/67, 28 differences.
- Retained: [97, 67, 28].

PFFILE_fread became instruction exact after marking the existing PFFILE_p_fread definition NO_INLINE. The target calls that independently emitted function, while the compiler's automatic inlining previously expanded it into this wrapper. Included the existing decomp utility header only in this translation unit to obtain the macro; no shared header changed. An initial build without that include rejected the undefined macro and was corrected immediately.

GetSFD's targeted pointer/index initialization, loop-order and initializer-helper variations remain recorded in fa-file.md. Its 113/113 stream still differs in eighteen register and increment instructions.
