/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:15:06 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/17 18:21:24 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
// #include "libft.h"

void handle_bit(int signal)
{
	static char c;
	static int	idx;

	// printf("received %d\n", signal);
	if (signal == SIGUSR1)
		c |= 1 << idx;
	else if (signal == SIGUSR2)
		;
	else
		return ;
	if (idx == 7)
	{
		write(STDOUT_FILENO, &c, 1);
		// printf("wrote %hhu\n", c);
		c = 0;
		idx = 0;
	}
	else
		idx++;
}

int	main(void)
{
	pid_t	pid;

	pid = getpid(); // The getpid() and getppid() functions are always successful, and no return value is reserved to indicate an error.
	printf("[minitalk server] launched: PID = %d\n", pid);

	signal(SIGUSR1, handle_bit);
	signal(SIGUSR2, handle_bit);

	while (1)
		;
	return (0);
}
