#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "constant.h"
#include "variable.h"

int fifo_fd[CLIENT_MAX_NUM];

void fifo_init() {

    int i;
    char fifo_path[PATH_LENGTH];

    for( i=0 ; i<CLIENT_MAX_NUM ; i++ ) {

        sprintf(fifo_path, "%sclient_%d", FIFO_PATH_DIR, i);

        if(mknod(fifo_path, S_IFIFO | 0666, 0) < 0) {
            perror("mknod");
        }
        if((fifo_fd[i] = open(fifo_path, O_NONBLOCK | O_RDONLY) ) < 0) {
            perror("open(RO)");
        }

        if(DEBUG)   fprintf(stderr, "open: fifo_path = %s\n", fifo_path);

    }
}

void fifo_close() {

    int i;
    char fifo_path[PATH_LENGTH];

    for( i=0 ; i<CLIENT_MAX_NUM ; i++ ) {

        if(close(fifo_fd[i]) < 0) {
            perror("close");
        }
        sprintf(fifo_path, "%sclient_%d", FIFO_PATH_DIR, i);

    }

}

void fifo_finalize() {

    int i;
    char fifo_path[PATH_LENGTH];

    for( i=0 ; i<CLIENT_MAX_NUM ; i++ ) {

        sprintf(fifo_path, "%sclient_%d", FIFO_PATH_DIR, i);
        if(unlink(fifo_path) < 0) {
            perror("unlink");
        }

    }
}