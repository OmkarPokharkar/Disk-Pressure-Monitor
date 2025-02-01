#include "disk_usage.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>

DiskUsage get_disk_usage(const char *path) {
    struct statvfs stat;
    DiskUsage usage;

    if (statvfs(path, &stat) != 0) {
        perror("statvfs");
        exit(EXIT_FAILURE);
    }

    usage.total = stat.f_blocks * stat.f_frsize;
    usage.free = stat.f_bfree * stat.f_frsize;
    usage.used = usage.total - usage.free;
    usage.percent_used = (double)usage.used / usage.total * 100;

    return usage;
}

int is_disk_pressure(DiskUsage usage, double threshold) {
    return usage.percent_used > threshold;
}
