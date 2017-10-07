#include "kill_child_on_exit.h"
#include "test_helpers.h"

#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#ifndef kTRUTHY_RET_VAL
#define kTRUTHY_RET_VAL 0
#define kINVAL_PARAM 1337
#define kNON_EXISTENT_PROCESS -1
#endif

int32_t main(const int32_t argc, const char *argv[]) {
    pid_t child = fork();

    if (!child) {
        uid_t uid = getuid();
        uid_t euid = geteuid();
        pid_t parent = getppid();
        
        /* check privilege context */
        if (uid == 0 && euid == 0) {
            X_DESCRIBE("syscall su tests") {
                /* su unit test context */
                X_IT("should return truthy value with valid flag param as 1") {
                    const long result = kill_child_on_exit(parent, 1);

                    assert(result == 0);
                }

                X_IT("should return truthy value with valid flag param as 0") {
                    const long result = kill_child_on_exit(parent, 0);

                    assert(result == 0);
                }

                X_IT("should return EINVAL when flag value is invalid") {
                    const long result = kill_child_on_exit(parent, kINVAL_PARAM);

                    assert(result == EINVAL);
                }

                X_IT("should return ESRCH when process with given pid does not exist") {
                    const long result = kill_child_on_exit(-1, 0);

                    assert(result == ESRCH);
                } 
            }
        } else {
            X_DESCRIBE("syscall u tests") {
                X_IT("should return EACCES if user has no root privileges") {
                    const long result = kill_child_on_exit(parent, 1);

                    assert(result == EACCES);
                }
            }
        }
        
        exit(EXIT_SUCCESS);
    } else {
        /* parent waiting for child */
        wait(NULL);

        exit(EXIT_SUCCESS);
    }
}
