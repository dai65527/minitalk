/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:39:22 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/17 18:27:31 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int	errend(const char *msg, int retval)
{
	printf("minitalk client: %s\n", msg);
	return (retval);
}

int	parse_argv(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	return (atoi(argv[1]));
}

int minisend(pid_t pid, const char *msg)
{
	int	i;
	int	ret;

	printf("sending to %d: msg %s\n", pid, msg);
	while (*msg)
	{
		i = 0;
		while (i <= 7)
		{
			if (*msg & (1 << i))
				ret = kill(pid, SIGUSR1);
			else
				ret = kill(pid, SIGUSR2);
			if (ret == -1)
				return (-1);
			usleep(100);
			++i;
		}
		++msg;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	'~';
	'?';

	pid = parse_argv(argc, argv);
	if (pid <= 0)
		return (errend("Invalid argument", 1));
	if (minisend(pid, argv[2]) == -1)
		return (errend("Failed to send", 1));
	return (0);
}
