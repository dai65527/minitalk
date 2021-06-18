/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:39:22 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/18 14:49:36 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "minitalk_client.h"
#include "../../libft/libft.h"

static int	errend(int error_number)
{
	ft_putstr_fd("minitaik client: ", STDERR_FILENO);
	if (error_number == MINITALK_EINVAL)
		ft_putstr_fd("Invalid argument\n", STDERR_FILENO);
	else if (error_number == MINITALK_ESIGNAL)
		ft_putstr_fd("Failed to set signal handler\n", STDERR_FILENO);
	else if (error_number == MINITALK_EKILL)
		ft_putstr_fd("Failed to send signal\n", STDERR_FILENO);
	else if (error_number == MINITALK_ECONN)
		ft_putstr_fd("Failed to connect server\n", STDERR_FILENO);
	else if (error_number == MINITALK_ESEND)
		ft_putstr_fd("Failed to send message\n", STDERR_FILENO);
	else
		ft_putstr_fd("Unknown error\n", STDERR_FILENO);
	return (1);
}

static int	parse_argv(int argc, char **argv)
{
	if (argc != 3)
		return (-1);
	return (atoi(argv[1]));
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		ret;

	pid = parse_argv(argc, argv);
	if (pid <= 0)
		return (errend(MINITALK_EINVAL));
	ret = minisend(pid, argv[2]);
	if (ret != MINITALK_OK)
		return (errend(ret));
	return (0);
}
