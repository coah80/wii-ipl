# grok-osexec OSExec

Replaced DECOMP_FORCE_ACTIVE string holders with the SDK functions that own those literals.

- __OSLaunchNextFirmware before the other functions, so "Failed to exec" (shared execFailure) and "specified game doesn't exist" emit first.
- OSLaunchDisk / OSLaunchDiskv after the linked launch helpers: three OSLaunchDisk reports, then "0000000000000000".
- IsNewApploader next: "2004/02/01".
- OSLaunchPartition / OSLaunchPartitionv last: the two partition reports.

Pool identical 17/17. All 10 linked functions odiff 0. objdiff data 864/864, fuzzy 100. Relinked DOL sha1 26116613f624061ba99c8d1a299aaa6efa85670d. Dead functions stripped (__OSInReboot stays at 0x81699040).

GATE PASS. Renamed new varargs params off arg0 so the readability scan stays clean. Volatile on DVDLowIntType is the callback flag the wait loop reloads.
