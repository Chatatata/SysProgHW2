#include "kill_child_on_exit.h"

#ifndef kKILL_CHILD_ON_EXIT_SYS_CALL
#define kKILL_CHILD_ON_EXIT_SYS_CALL 355
#endif

long kill_child_on_exit(pid_t pid, int flag) {
    return syscall(kKILL_CHILD_ON_EXIT_SYS_CALL, pid, flag);
}
