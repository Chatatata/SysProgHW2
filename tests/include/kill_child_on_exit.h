#ifndef KILL_CHILD_ON_EXIT_DECL
#define KILL_CHILD_ON_EXIT_DECL

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

long kill_child_on_exit(pid_t pid, int flag);

#endif
