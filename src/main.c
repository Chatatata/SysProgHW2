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
#include <sys/resource.h>
#include <errno.h>

#ifndef kTRUTHY_RET_VAL
#define kTRUTHY_RET_VAL 0
#define kINVAL_PARAM 1337
#define kNON_EXISTENT_PROCESS -1
#endif

int32_t main(const int32_t argc, const char *argv[]) {
    pid_t child = fork();

    if (!child) {
        int which = PRIO_PROCESS;
        int ret;
        id_t pid = getpid();
        uid_t uid = getuid();
        uid_t euid = geteuid();
        pid_t parent = getppid();
        
        errno = 0;

        ret = getpriority(which, pid);

        assert(errno == 0);
        
        /* check privilege context */
        if (ret > 10 && argc == 2) {
            /* su \w nice unit test context */
            X_ONLY_BEGIN_IT("should kill its children processes upon exit with flag set", 0)
                const long __attribute__((unused)) result = kill_child_on_exit((pid_t)pid, 1);

                if (fork()) {
                    exit(EXIT_SUCCESS);
                } else {
                    sleep(10);

                    assert(NULL);
                }
            X_ONLY_END_IT()

            X_ONLY_BEGIN_IT("should not kill its children processes if flag is not set", 1)
                if (fork()) {
                    exit(EXIT_SUCCESS);
                } else {
                    sleep(1);

                    assert(!NULL);
                }
            X_ONLY_END_IT()
        } else if (uid == 0 && euid == 0) {
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

                X_IT("should kill its children when appropriate nice value is set")  
            }
        } else {
            X_DESCRIBE("syscall u tests") {
                /* u unit test context */
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
