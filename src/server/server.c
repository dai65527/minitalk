/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:15:06 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/19 10:12:48 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "../../libft/libft.h"

#define BUFSIZE 10

int	checkpid(pid_t *pid, pid_t incomingpid)
{
	if (*pid == 0)
	{
		*pid = incomingpid;
		kill(incomingpid, SIGUSR1);
		return (1);
	}
	else if (*pid != incomingpid)
	{
		kill(incomingpid, SIGUSR2);
		return (1);
	}
	return (0);
}

void	handle_char(char c, int *cnt, char *buf, pid_t *pid)
{
	buf[*cnt] = c;
	if (c == '\4')
	{
		kill(*pid, SIGUSR1);
		*pid = 0;
	}
	else
		(*cnt)++;
	if (c == '\4' || *cnt == BUFSIZE)
	{
		write(STDOUT_FILENO, buf, *cnt);
		*cnt = 0;
	}
}

void	handle_bit(int signum, siginfo_t *info, void *context)
{
	static char		c;
	static int		idx;
	static int		cnt;
	static pid_t	pid;
	static char		buf[BUFSIZE];

	(void)context;
	if (checkpid(&pid, info->si_pid))
		return ;
	if (signum == SIGUSR1)
		c |= 1 << idx;
	if (idx == 7)
	{
		handle_char(c, &cnt, buf, &pid);
		c = 0;
		idx = 0;
	}
	else
		idx++;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	act;

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
