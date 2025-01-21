#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        printf("System uptime: %ld seconds\n", info.uptime);
    }
    return 0;
}