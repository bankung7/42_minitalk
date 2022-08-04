/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 21:40:53 by vnilprap          #+#    #+#             */
/*   Updated: 2022/08/04 21:40:55 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft.h"

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int					i;
	static pid_t				pid;
	static unsigned char		c;

	(void)context;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		i = 0;
		c = 0;
	}
	if (sig == SIGUSR1)
		c |= 1;
	if (++i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	else
		c <<= 1;
	usleep(100);
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action;

	action.sa_sigaction = ft_handler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &action, 0);
	sigaction(SIGUSR2, &action, 0);
	ft_putstr_fd("server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
