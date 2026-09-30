#include <revolution/fa.h>

extern FADisk* gOpenDisk[26];
extern FAPartition* gOpenPartition[26];
extern s32 pfstub_detach(s8 drive);
extern s32 pdm_close_partition(FAPartition* partition);
extern s32 pdm_close_disk(FADisk* disk);

FAError FADetach(s8 drive) {
    FADisk* disk = gOpenDisk[drive - 'A'];
    FAPartition* partition = gOpenPartition[drive - 'A'];
    if (pfstub_detach(drive) != 0) {
        return -1;
    }
    if (disk != NULL && partition != NULL) {
        if (pdm_close_partition(partition) != 0) {
            return -1;
        }
        if (pdm_close_disk(disk) != 0) {
            return -1;
        }
    }
    return 0;
}
