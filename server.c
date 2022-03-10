/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloko <lloko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:19:37 by lloko             #+#    #+#             */
/*   Updated: 2022/02/09 00:33:45 by lloko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// функция обработчик сигналов
void	sig_handler(int sig, siginfo_t *sig_info, void *context)
{
	
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

	(void)argv;
	//if (argc != 3)
	//	write(1, "Error")
	pid = getpid();
	write(1, "Server PID: ", 12);
	ft_putnbr(pid);
	ft_putchar('\n');
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = &sig_handler;
	sigemptyset(sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sig_struct, NULL);
	sigaction(SIGUSR2, &sig_struct, NULL);
	while (1)
		sleep (1);
	//return (0);
}
