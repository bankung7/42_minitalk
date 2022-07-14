#include <unistd.h>
#include <signal.h>
#include "libft/includes/ft_printf.h"

void handler(int sig, siginfo_t *info, void *context)
{
    static int i;
    static char c;
    static pid_t c_pid;

    (void)context;
    (void)info;
    if (c_pid == 0)
        c_pid = info->si_pid;
    if (i++ < 8)
    {
        if (sig == SIGUSR1)
            c = c << 1 | 1;
        else if (sig == SIGUSR2)
            c = c << 1 | 0;
    }
    if (i == 8)
    {
        ft_putchar_fd(c, 1);
        kill(c_pid, SIGUSR1);
        i = 0;
        c = 0;
        c_pid = 0;
    }
}

int main(void)
{
    pid_t pid;
    struct sigaction action;

    pid = getpid();
    action.sa_sigaction = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    ft_printf("PID : %d\n", pid);
    while (1)
        pause();
    return (0);
}