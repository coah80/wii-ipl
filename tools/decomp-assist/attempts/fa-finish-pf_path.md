# fa/pf_path continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFPATH_parseShortName:
- rotate independent local declarations: 466/466, 102 differences.
- common operation status exit: 466/466, 2 differences.
- reverse independent local declarations: 466/466, 166 differences.
- Retained: [466, 466, 2].

PFPATH_getShortName:
- common operation status exit: 148/148, 2 differences.
- split local declaration from initialization: compile failed: h.c
# --------------------------------------
#     598:     pf_s32 nLen = -1; 
#   Error:     ^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
.
- explicit increment assignment: compile failed:     617:             *short_name += 1 = pDirEntry[i]; 
#   Error:                                            ^
#   (10142) not an lvalue
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
.
- Retained: [148, 148, 2].

PFPATH_MatchFileNameWithPattern:
- rotate independent local declarations: 192/199, 148 differences.
- common operation status exit: 192/199, 148 differences.
- reverse independent local declarations: 192/199, 157 differences.
- Retained: [192, 199, 148].

PFPATH_cmpNameImpl:
- rotate independent local declarations: 195/218, 181 differences.
- common operation status exit: 195/218, 181 differences.
- reverse independent local declarations: 195/218, 180 differences.
- Retained: [195, 218, 181].

Targeted cmpNameImpl attempts: separate pattern/name fullwidth conversion and a wildcard switch (202/218); advance names for wildcard question marks and before recursive comparisons (226/218); share the character-read temporary and retain recursive error status (222/218). Retained the third corrected wildcard flow. Register allocation and four extra instructions remain.

Targeted MatchFileNameWithPattern attempts: replace manually assigned signature bytes with the existing signature-check helper (196/199, fourteen differences); retain the second signature check result and use the target non-wildcard extended-name check (196/199, identical prefix); retained this version. The target symbol includes three instructions from the following outlined iterator body after its return; no padding or symbol-size adjustment was added.

getShortName and parseShortName are already objdiff exact; their raw ctxdiff differences are relocation-dependent conditional branches to shared outlined code. These are not source regressions.
