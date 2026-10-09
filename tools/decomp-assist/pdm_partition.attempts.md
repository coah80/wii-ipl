
## w1011/struct2 wave-2 verification

- is_master_boot_sector residual re-decoded: both objects emit the SAME
  add tree ((b0 + b2<<16) + (b1<<8 + b3<<24)) for read_partition_u32 —
  the + macro form is correct. All 7 residual lines are the load/shift
  INTERLEAVE order (base loads b3,b2,b0 then shifts; mine b3,b2,b1).
  Pure scheduler tie — scheduling pragmas previously probed, no lever.
