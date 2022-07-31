#include <unistd.h>
#include <signal.h>
#include "libft/inc/ft_printf.h"

static int g_ack;

void    ft_handler(int sig, siginfo_t *info, void *context)
{
    (void)info;
    (void)context;
    if (sig == SIGUSR1)
        g_ack--;
}

void ft_moss(pid_t pid, char *str)
{
    int i;
    int j;

    i = 0;
    while (str[i])
    {
        j = 7;
        while (j >= 0)
        {
            if (str[i] >> j & 1)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            j--;
            usleep(300);
        }
        ft_printf("send %c\n", str[i]);
        i++;
        usleep(200);
    }
}

int main(int argc, char **argv)
{
    struct sigaction    action;

    action.sa_sigaction = ft_handler;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &action, 0);
    if (argc != 3 || argv[2] == 0)
        return (0);
    g_ack = ft_strlen(argv[2]);
    ft_moss(ft_atoi(argv[1]), argv[2]);
    while (g_ack != 0)
        pause();
    ft_printf("received\n");
}