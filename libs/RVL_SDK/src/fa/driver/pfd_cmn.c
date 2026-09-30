#include <private/fa/pdm.h>
#include <private/fa/pf_volume.h>

extern PF_VOLUME_SET pf_vol_set;
extern pf_s32 pdm_part_is_attached_partition(PDM_PARTITION* partition);

pf_u8 pfd_get_media_drv_char(PDM_DISK* disk, pf_s8* drives, pf_u32 capacity) {
    pf_u32 partition_index;
    pf_u32 volume_index;
    PF_VOLUME* volume;
    pf_u8 count;
    pf_s8* next_drive;
    PDM_PARTITION* partition;
    if (drives == NULL || capacity == 0) {
        return 0;
    }
    next_drive = drives;
    count = 0;
    partition = pdm_disk_set.partition;
    for (partition_index = 0; partition_index < 26; partition_index++, partition++) {
        if (pdm_part_is_attached_partition(partition) && partition->p_disk == disk) {
            volume = pf_vol_set.volumes;
            for (volume_index = 0; volume_index < 26; volume_index++, volume++) {
                if (volume->p_part == partition) {
                    count++;
                    *next_drive++ = volume->drv_char;
                    if (count == capacity) {
                        break;
                    }
                }
            }
        }
        if (count == capacity) {
            break;
        }
    }
    return count;
}
