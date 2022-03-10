/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloko <lloko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:49:58 by lloko             #+#    #+#             */
/*   Updated: 2022/02/08 14:31:43 by lloko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

struct sigaction	sig_struct;
{
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = ft_sighandler;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
};

typedef struct
{
	int		si_signo;
	int		si_code;
	union sigval	si_value;
	int		si_errno;
	pid_t	si_pid;
	uid_t	si_uid;
	void	*si_addr;
	int		si_status;
	int		si_band;	
}			siginfo_t;

// функция обработчика сигналов
void	ft_sighandler(int signum, siginfo_t *sig, void *context)
{
}
