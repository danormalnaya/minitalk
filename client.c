/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloko <lloko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:49:58 by lloko             #+#    #+#             */
/*   Updated: 2022/03/19 18:29:30 by lloko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_mes;

static void	sender(int bit, int pid)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) < 0)
		{
			write(1, "Wrong PID\n", 11);
			exit(0);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2) < 0)
		{
			write(1, "Wrong PID\n", 11);
			exit(0);
		}
	}
}

static void	send_bit(int sig, siginfo_t *info, void *context)
{
	int	bit;
	int	pid;

	(void)context;
	pid = info->si_pid;
	if (sig == SIGUSR2)
	{
		write(1, "Message was sent!\n", 19);
		exit(0);
	}
	bit = ((g_mes.str[g_mes.numb_byte]) >> (7 - g_mes.numb_bit)) & 1;
	usleep(100);
	sender(bit, pid);
	++g_mes.numb_bit;
	if (g_mes.numb_bit == 8)
	{
		g_mes.numb_bit = 0;
		++g_mes.numb_byte;
	}
}

static void	send_message(int pid_num_serv)
{
	struct sigaction	handler;
	siginfo_t			info;

	handler.sa_sigaction = send_bit;
	handler.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &handler, NULL);
	sigaction(SIGUSR2, &handler, NULL);
	info.si_pid = pid_num_serv;
	send_bit(SIGUSR1, &info, NULL);
	while (1)
		pause();
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		g_mes.str = argv[2];
		send_message(ft_atoi(argv[1]));
	}
	else
		write(1, "Please, write: ./client [PID_NUM] [MESSAGE]\n", 45);
}
