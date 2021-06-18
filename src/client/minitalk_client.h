/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:30:06 by dnakano           #+#    #+#             */
/*   Updated: 2021/06/18 14:50:09 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_CLIENT_H
# define MINITALK_CLIENT_H

# define MINITALK_INTERVAL_US 100
# define MINITALK_LONG_INTERVAL_US 10000

# define MINITALK_OK 0
# define MINITALK_EINVAL -1
# define MINITALK_ESIGNAL -2
# define MINITALK_EKILL -3
# define MINITALK_ECONN -4
# define MINITALK_ESEND -5

int	minisend(pid_t pid, const char *msg);

#endif
