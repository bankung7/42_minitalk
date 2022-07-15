/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 18:09:45 by vnilprap          #+#    #+#             */
/*   Updated: 2022/07/15 18:12:37 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/includes/ft_printf.h"

static int	g_ack;

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		g_ack++;
}

void	ft_squawk(pid_t pid, char **argv)
{
	int	i;
	int	j;

	j = 0;
	while (argv[2][j])
	{
		i = 8;
		while (i-- > 0)
		{
			if (argv[2][j] >> i & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(300);
		}
		usleep(100);
		j++;
	}
}

int	main(int argc, char **argv)
{
	int					len;
	pid_t				pid;
	struct sigaction	action;

	if (argc < 3)
		return (0);
	action.sa_sigaction = ft_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	ft_squawk(pid, argv);
	while (g_ack != len)
		pause();
	ft_printf("server ack %d bytes\n", len);
	return (0);
}
