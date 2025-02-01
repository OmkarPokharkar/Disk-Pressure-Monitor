#ifndef DISK_USAGE_H
#define DISK_USAGE_H

typedef struct {
    unsigned long total;
    unsigned long free;
    unsigned long used;
    double percent_used;
} DiskUsage;

DiskUsage get_disk_usage(const char *path);
int is_disk_pressure(DiskUsage usage, double threshold);
#endif // DISK_USAGE_H
