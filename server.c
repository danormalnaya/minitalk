/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloko <lloko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:19:37 by lloko             #+#    #+#             */
/*   Updated: 2022/03/19 18:28:01 by lloko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_message;

static void	get_message(t_message *message)
{
	int	i;

	i = 0;
	message->serv_in_to_work = 1;
	message->numb_bit = 0;
	message->numb_byte = 0;
	while (i < BUFF)
	{
		message->str[i] = 0;
		i++;
	}
}

static void	print_message(void)
{
	int	i;

	write(1, g_message.str, g_message.numb_byte);
	i = 0;
	while (i < g_message.numb_byte)
	{
		g_message.str[i] = 0;
		i++;
	}
	g_message.numb_byte = 0;
}

static void	accept_a_bit(int sig, siginfo_t *info, void *context)
{
	int	bit;

	(void)context;
	if (sig == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	g_message.str[g_message.numb_byte] |= (bit << (7 - g_message.numb_bit));
	if (++g_message.numb_bit == 8)
	{
		if (g_message.str[g_message.numb_byte] == '\0')
		{
			g_message.serv_in_to_work = 0;
			print_message();
			kill(info->si_pid, SIGUSR2);
			write(1, "\n", 1);
			return ;
		}
		g_message.numb_bit = 0;
		g_message.numb_byte++;
		if (g_message.numb_byte == BUFF)
			print_message();
	}
	usleep(50);
	kill(info->si_pid, SIGUSR1);
}

static void	decoder(void)
{
	struct sigaction	handler;

	handler.sa_sigaction = accept_a_bit;
	handler.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &handler, NULL) < 0)
	{
		write(1, "Sigaction Error!\n", 18);
		exit(0);
	}
	if (sigaction(SIGUSR2, &handler, NULL) < 0)
	{
		write(1, "Sigaction Error!\n", 18);
		exit(0);
	}
	while (g_message.serv_in_to_work)
		pause();
}

int	main(void)
{
	int		pid;
	char	message[BUFF];

	g_message.str = message;
	pid = getpid();
	write(1, "My PID: ", 8);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	while (1)
	{
		get_message(&g_message);
		decoder();
	}
}
