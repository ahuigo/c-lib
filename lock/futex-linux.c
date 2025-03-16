#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>

/**
 * 这个示例中，父进程和子进程共享一个变量 sharedVariable，并使用 futex 来实现同步。子进程首先等待 futexVariable 变为 1，然后增加 sharedVariable 的值。父进程先增加 sharedVariable 的值，然后将 futexVariable 设置为 1，并唤醒子进程。通过 futex 的等待和唤醒操作，父进程和子进程实现了同步，确保子进程在父进程完成操作后再执行。
 **/
int futex(int *uaddr, int futex_op, int val, const struct timespec *timeout, int *uaddr2, int val3) {
    return syscall(SYS_futex, uaddr, futex_op, val, timeout, uaddr2, val3);
}

int main() {
    int sharedVariable = 0;
    int futexVariable = 0;

    pid_t childPid = fork();

    if (childPid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0) {
        // Child process
        printf("Child process: Waiting for futexVariable to be 1...\n");

        // 使用 futex 等待 futexVariable 变为 1
        futex(&futexVariable, FUTEX_WAIT, 0, NULL, NULL, 0);

        printf("Child process: futexVariable is now 1. Incrementing sharedVariable...\n");

        // 增加 sharedVariable 的值
        sharedVariable++;

        printf("Child process: sharedVariable is now %d\n", sharedVariable);

        // 唤醒父进程
        futex(&futexVariable, FUTEX_WAKE, 1, NULL, NULL, 0);

        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent process: Incrementing sharedVariable...\n");

        // 增加 sharedVariable 的值
        sharedVariable++;

        printf("Parent process: sharedVariable is now %d\n", sharedVariable);

        printf("Parent process: Setting futexVariable to 1...\n");

        // 设置 futexVariable 的值为 1
        futexVariable = 1;

        // 唤醒子进程
        futex(&futexVariable, FUTEX_WAKE, 1, NULL, NULL, 0);

        // 等待子进程结束
        wait(NULL);

        exit(EXIT_SUCCESS);
    }
}
