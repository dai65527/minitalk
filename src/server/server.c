/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:15:06 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/17 21:49:49 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "../../libft/libft.h"

#define BUFSIZE 2048

void handle_bit(int signal)
{
	static char c;
	static int	idx;
	static int	cnt;
	static char buf[BUFSIZE];

	if (signal == SIGUSR1)
		c |= 1 << idx;
	else if (signal == SIGUSR2)
		;
	else
		return ;
	if (idx == 7)
	{
		buf[cnt] = c;
		if (c == '\6' || cnt + 1 == BUFSIZE)
		{
			write(STDOUT_FILENO, buf, cnt);
			cnt = 0;
		}
		c = 0;
		idx = 0;
		cnt++;
	}
	else
		idx++;
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr_fd("minitalk server: launched: PID = ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	signal(SIGUSR1, handle_bit);
	signal(SIGUSR2, handle_bit);
	while (1)
		pause();
	return (0);
}
