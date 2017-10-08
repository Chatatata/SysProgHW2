#include <uapi/asm-generic/errno-base.h>

#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/pid.h>
#include <linux/printk.h>
#include <linux/sched.h>

/*
 * Sets the kill_child_on_exit flag of process with given pid.
 *
 * EXIT STATUS
 * kill_child_on_exit returns 0 on success, if caller process
 * is not given root privileges it returns EACCES, if pid is
 * not found it returns ESRCH, if flag is not 0 or 1 it returns
 * EINVAL.
 */
asmlinkage long sys_kill_child_on_exit(pid_t pid, int flag) {
    struct task_struct *t = NULL;
    struct pid *p = NULL;
    kuid_t su_kuid;

    if (!current) {
        printk(KERN_ERR "current task_struct is not read, aborting with -1\n");

        return -1;
    }

    if (!current->cred) {
        printk(KERN_ERR "current task_struct has no struct cred assoc, aborting with -1\n");

        return -1;
    }

    /* make su_kuid root kuid_t */
    memset(&su_kuid, 0, sizeof(su_kuid));

    /* check whether process has root privileges (effective) */
    if (!uid_eq(get_current_cred()->euid, su_kuid)) {
        printk(KERN_ERR "pid %d has no root privileges, aborting with %d\n", pid, EACCES);

        return EACCES;
    }

    if (!(p = find_get_pid(pid))) {
        printk(KERN_ERR "struct pid not found for pid %d, aborting with %d\n", pid, ESRCH);

        return ESRCH;
    }

    /* get the task_struct for given pid */
    if (!(t = get_pid_task(p, PIDTYPE_PID))) {
        printk(KERN_ERR "task_struct not found for pid %d upon fuzzing, aborting with %d\n", pid, ESRCH);

        return ESRCH;
    }

    /* check given parameter */
    if (flag != 0 && flag != 1) {
        printk(KERN_ERR "given flag value %d is invalid, aborting with %d\n", flag, EINVAL);

        return EINVAL;
    }

    printk(KERN_NOTICE "setting flag %d for pid %d\n", flag, pid);

    t->kill_child_on_exit = flag;

    return 0;
}
