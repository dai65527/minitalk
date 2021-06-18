/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:39:22 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/18 13:31:01 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "../../libft/libft.h"

#define MINITALK_INTERVAL_US 100
#define MINITALK_LONG_INTERVAL_US 10000

int g_flg_ack;

int	errend(const char *msg, int retval)
{
	ft_putstr_fd("minitaik client: ", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	return (retval);
}

int	parse_argv(int argc, char **argv)
{
	if (argc != 3)
		return (-1);
	return (atoi(argv[1]));
}

int	sendchar(pid_t pid, const char c, useconds_t interval)
{
	int	i;
	int	ret;

	i = 0;
	while (i <= 7)
	{
		if (c & (1 << i))
			ret = kill(pid, SIGUSR1);
		else
			ret = kill(pid, SIGUSR2);
		if (c == -1)
			return (-1);
		usleep(interval);
		++i;
	}
	return (0);
}

void	handlesig(int signum)
{
	if (signum == SIGUSR1)
		g_flg_ack = 1;
	else
		g_flg_ack = 0;
}

int	connect(pid_t pid)
{
	if (pid < 1)
		return (-1);
	signal(SIGUSR1, handlesig);
	signal(SIGUSR2, handlesig);
	if (kill(pid, SIGUSR1) == -1)
		return (-1);
	usleep(100000);
	if (g_flg_ack == 0)
		return (-1);
	g_flg_ack = 0;
	ft_putstr_fd("[minitalk client] connected!!\n", STDOUT_FILENO);
	return (0);
}

int closeconn(pid_t pid)
{
	sendchar(pid, '\4', MINITALK_INTERVAL_US);
	usleep(MINITALK_LONG_INTERVAL_US);
	if (g_flg_ack)
		return (0);
	while (g_flg_ack == 0)
	{
		kill(pid, SIGUSR2);
		sendchar(pid, '\4', MINITALK_LONG_INTERVAL_US);
		usleep(MINITALK_LONG_INTERVAL_US);
	}
	return (-1);
}

int minisend(pid_t pid, const char *msg)
{
	if (connect(pid) == -1)
		return (-1);
	while (*msg)
	{
		if (sendchar(pid, *msg, MINITALK_INTERVAL_US) == -1)
			return (-1);
		++msg;
	}
	if (closeconn(pid) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	pid = parse_argv(argc, argv);
	if (pid <= 0)
		return (errend("Invalid argument", 1));
	if (minisend(pid, argv[2]) == -1)
		return (errend("Failed to send", 1));
	return (0);
}
