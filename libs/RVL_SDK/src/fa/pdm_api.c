#include <revolution/fa.h>

extern s32 pdm_disk_init_disk_manager(s32 config, void* parameter);
extern s32 pdm_disk_add_disk(FADiskTbl* table, FADisk** disk);
extern s32 pdm_disk_del_disk(FADisk* disk);
extern s32 pdm_part_get_partition(FADisk* disk, u16 index, FAPartition** partition);
extern s32 pdm_part_release_partition(FAPartition* partition);

s32 pdm_init_diskmanager(s32 config, void* parameter) {
    return pdm_disk_init_disk_manager(config, parameter);
}

s32 pdm_open_disk(FADiskTbl* table, FADisk** disk) {
    s32 error;
    *disk = NULL;
    error = pdm_disk_add_disk(table, disk);
    return error != 0 ? error : 0;
}

s32 pdm_close_disk(FADisk* disk) {
    return pdm_disk_del_disk(disk);
}

s32 pdm_open_partition(FADisk* disk, u16 index, FAPartition** partition) {
    s32 error;
    *partition = NULL;
    error = pdm_part_get_partition(disk, index, partition);
    return error != 0 ? error : 0;
}

s32 pdm_close_partition(FAPartition* partition) {
    s32 error = pdm_part_release_partition(partition);
    return error != 0 ? error : 0;
}
