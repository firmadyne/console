#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Bind a shell to a serial console (/firmadyne/ttyS1) and
// ensure the session has support for job control (e.g.,
// ctrl+c, ctrl+z)

int main(int argc, char **argv) {
    int fd;

    setsid();

    close(2);
    close(1);
    close(0);

    if ((fd = open("/firmadyne/ttyS1", O_RDWR, 0) == -1)) {
        perror("cons: Could not open \"/firmadyne/ttyS1\": ");
        return -1;
    }

    dup(fd);
    dup(fd);

    putenv("TERM=linux");
    putenv("PATH=/sbin:/bin:/usr/sbin:/usr/bin");

    return execl("/bin/sh", "/bin/sh", NULL);
}
