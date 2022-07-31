#include <unistd.h>
#include <signal.h>
#include "libft/inc/ft_printf.h"

void ft_handler(int sig, siginfo_t *info, void *context)
{
    static pid_t pid;
    static int i;
    static char c;
    (void)context;

    if (pid != info->si_pid)
    {
        pid = info->si_pid;
        c = 0;
        i = 0;
    }
    if (sig == SIGUSR1)
        c |= 1;
    if (++i == 8)
    {
        write(1, &c, 1);
        c = 0;
        i = 0;
        kill(pid, SIGUSR1);
    }
    else if (sig == SIGUSR1 || sig == SIGUSR2)
        c <<= 1;
}

int main(void)
{
    pid_t pid;
    struct sigaction action;

    pid = getpid();
    action.sa_sigaction = ft_handler;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &action, 0);
    sigaction(SIGUSR2, &action, 0);
    ft_printf("PID: %d\n", pid);
    while (1)
        pause();
    return (0);
}