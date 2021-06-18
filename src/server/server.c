/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:15:06 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/18 14:07:00 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "../../libft/libft.h"

#define BUFSIZE 2048

void handle_bit(int signum, siginfo_t *info, void *context)
{
	static char 	c;
	static int		idx;
	static int		cnt;
	static pid_t	pid;
	static char 	buf[BUFSIZE];

	(void)context;
	if (pid == 0)
	{
		pid = info->si_pid;
		kill(pid, SIGUSR1);
		return ;
	}
	else if (pid != info->si_pid)
	{
		kill(info->si_pid, SIGUSR2);
		return ;
	}
	if (signum == SIGUSR1)
		c |= 1 << idx;
	else if (signum == SIGUSR2)
		;
	else
		return ;
	if (idx == 7)
	{
		buf[cnt] = c;
		if (c == '\4' || cnt + 1 == BUFSIZE)
		{
			if (c == '\4')
			{
				kill(info->si_pid, SIGUSR1);
				pid = 0;
			}
			write(STDOUT_FILENO, buf, cnt);
			cnt = 0;
		}
		else
			cnt++;
		c = 0;
		idx = 0;
	}
	else
		idx++;
}

int	main(void)
{
	pid_t	pid;
	struct	sigaction act;

	pid = getpid();
	ft_putstr_fd("[minitalk server] launched on PID = ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	act.sa_sigaction = handle_bit;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
