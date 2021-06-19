/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisend_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:32:01 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/19 14:49:35 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "minitalk_client_bonus.h"
#include "../../libft/libft.h"

int	g_flg_ack;

static void	handlesig(int signum)
{
	if (signum == SIGUSR1)
		g_flg_ack = 1;
	else
		g_flg_ack = 0;
}

static int	sendchar(pid_t pid, const char c, useconds_t interval)
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
		if (ret == -1)
			return (MINITALK_EKILL);
		usleep(interval);
		++i;
	}
	return (0);
}

static int	connect(pid_t pid)
{
	if (pid < 1)
		return (MINITALK_EINVAL);
	if (signal(SIGUSR1, handlesig) == SIG_ERR
		|| signal(SIGUSR2, handlesig) == SIG_ERR)
		return (MINITALK_ESIGNAL);
	if (kill(pid, SIGUSR1) == -1)
		return (MINITALK_EKILL);
	usleep(MINITALK_ESIGNAL);
	if (g_flg_ack == 0)
		return (MINITALK_ECONN);
	g_flg_ack = 0;
	return (MINITALK_OK);
}

static int	closeconn(pid_t pid)
{
	sendchar(pid, '\4', MINITALK_INTERVAL_US);
	usleep(MINITALK_LONG_INTERVAL_US);
	if (g_flg_ack)
		return (0);
	while (g_flg_ack == 0)
	{
		kill(pid, SIGUSR2);
		usleep(MINITALK_LONG_INTERVAL_US);
		sendchar(pid, '\4', MINITALK_LONG_INTERVAL_US);
	}
	return (MINITALK_ESEND);
}

int	minisend(pid_t pid, const char *msg)
{
	int	ret;

	ret = connect(pid);
	if (ret != MINITALK_OK)
		return (ret);
	ft_putstr_fd("[minitalk client] connected\n", STDOUT_FILENO);
	ft_putstr_fd("[minitalk client] sending message \"", STDOUT_FILENO);
	ft_putstr_fd((char *)msg, STDOUT_FILENO);
	ft_putstr_fd("\"\n", STDOUT_FILENO);
	while (*msg)
	{
		ret = sendchar(pid, *msg, MINITALK_INTERVAL_US);
		if (ret != MINITALK_OK)
			return (ret);
		++msg;
	}
	ft_putstr_fd("[minitalk client] closing connection\n", STDOUT_FILENO);
	ret = closeconn(pid);
	if (ret != MINITALK_OK)
		return (ret);
	ft_putstr_fd("[minitalk client] success to send\n", STDOUT_FILENO);
	return (MINITALK_OK);
}
