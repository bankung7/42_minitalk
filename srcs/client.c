/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 21:41:01 by vnilprap          #+#    #+#             */
/*   Updated: 2022/08/04 22:37:33 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft.h"

int	ft_send(pid_t pid, char c, int j)
{
	static int	ack;
	static int	i;

	if (pid == 0 && c == 0 && j == 0)
	{
		ack++;
		return (ack);
	}
	if (c >> j & 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	while (1)
	{
		while (ack == i)
			pause();
		i++;
		usleep(100);
		return (0);
	}
}

void	ft_moss(pid_t pid, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 7;
		while (j >= 0)
			ft_send(pid, str[i], j--);
		i++;
	}
}

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		ft_send(0, 0, 0);
}

int	main(int argc, char **argv)
{
	struct sigaction	action;

	if (argc != 3)
		return (0);
	action.sa_sigaction = ft_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, 0);
	if (ft_strlen(argv[2]) == 0)
	{
		ft_putstr_fd("no file to send\n", 1);
		return (0);
	}
	ft_moss(ft_atoi(argv[1]), argv[2]);
	if (ft_send(0, 0, 0) - 1 == (int)ft_strlen(argv[2]) * 8)
		ft_putstr_fd("server received\n", 1);
	return (0);
}
