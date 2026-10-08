# grok-cdbfs CDBFileSystem

Replaced DECOMP_FORCE_ACTIVE NAND logs with the helpers that owned those strings.

1. static helpers: compiler deleted them and the strings (pool 16 vs 25). differing n/a.
2. global helpers: pool identical 25/25, every existing function differing 0. CDBFSInitWiiIdPath wrote CDB_WIIID_DAT_PATH first and swapped .bss (VFF name vs wiiid path). DOL sha1 45ea54b56b135b08c766cd610d416d72ad7858ca.
3. CDBFSReportWiiIdDat only passes "nocopy/cdbwiiid.dat" to the status dump. .bss order restored. pool identical. 12/12 functions differing 0. DOL sha1 26116613f624061ba99c8d1a299aaa6efa85670d.

Linker strips the new globals. static would drop the strings again.
