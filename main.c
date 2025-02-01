#include <stdio.h> // For snprintf, fprintf, stderr, printf
#include <stdlib.h> // For atof
#include <unistd.h> // For getopt, sleep
#include <signal.h> // For signal handling
#include <syslog.h> // For syslog
#include <getopt.h> // For long options
#include "disk_usage.h"

volatile sig_atomic_t keep_running = 1;

void handle_signal(int signal) {
    keep_running = 0;
}

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s --path <path> --threshold <threshold> --interval <interval> [-h]\n", prog_name);
}

void send_syslog_emergency(const char *message) {
    openlog("disk_pressure_monitor", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    syslog(LOG_EMERG, "%s", message);
    closelog();
}

int main(int argc, char *argv[]) {
    const char *path = "/";
    double threshold = 80.0;
    int interval = 1;

    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    struct option long_options[] = {
        {"path", required_argument, 0, 'p'},
        {"threshold", required_argument, 0, 't'},
        {"interval", required_argument, 0, 'i'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "p:t:i:h", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'p':
                path = optarg;
                printf("Path: %s\n", path);
                break;
            case 't':
                threshold = atof(optarg);
                printf("Threshold: %.2f\n", threshold);
                break;
            case 'i':
                interval = atoi(optarg);
                printf("Interval: %d\n", interval);
                break;
            case 'h':
            default:
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }

    while (keep_running) {
        DiskUsage usage = get_disk_usage(path);

        printf("Current disk usage: %.2f%%\n", usage.percent_used);

        if (is_disk_pressure(usage, threshold)) {
            char message[100];
            snprintf(message, sizeof(message), "Disk usage is at %.2f%%", usage.percent_used);
            printf("Disk pressure detected: %s\n", message);
            send_syslog_emergency(message);
        }

        sleep(interval); // Wait for the specified interval before checking again
    }

    printf("Shutting down...\n");
    return 0;
}
