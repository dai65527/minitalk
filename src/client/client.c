/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:39:22 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/17 21:52:56 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "../../libft/libft.h"

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

int	sendchar(pid_t pid, const char c)
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
		usleep(100);
		++i;
	}
	return (0);
}

// int	connect(pid_t pid)
// {
// 	int		count;

// 	if (signal(SIGUSR1, sighandler))
// 	if (pid < 1)
// 		return (-1);
// 	if (sendchar(pid, '\6'))
// 		return (-1);
// 	while ()
// 	usleep(100000);
// 	if ()
// 	return (sendchar(pid, '\6'));
// }

int minisend(pid_t pid, const char *msg)
{
	while (*msg)
	{
		if (sendchar(pid, *msg) == -1)
			return (-1);
		++msg;
	}
	if (sendchar(pid, '\6') == -1)
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
