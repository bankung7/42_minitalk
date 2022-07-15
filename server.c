/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 18:13:43 by vnilprap          #+#    #+#             */
/*   Updated: 2022/07/15 18:15:24 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/includes/ft_printf.h"

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int		i;
	static char		c;
	static pid_t	c_pid;

	(void)context;
	if (c_pid != info->si_pid)
	{
		c_pid = info->si_pid;
		i = 0;
	}
	if (sig == SIGUSR1)
		c = c << 1 | 1;
	else
		c = c << 1;
	if (++i == 8)
	{
		ft_putchar_fd(c, 1);
		kill(c_pid, SIGUSR1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	pid = getpid();
	action.sa_sigaction = ft_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_printf("PID : %d\n", pid);
	while (1)
		pause();
	return (0);
}
