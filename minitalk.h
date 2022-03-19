/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloko <lloko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:10:50 by lloko             #+#    #+#             */
/*   Updated: 2022/03/19 18:22:45 by lloko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF 1024

struct	s_message
{
	int		numb_bit;
	int		numb_byte;
	char	*str;
	int		serv_in_to_work;
};

typedef struct s_message	t_message;

void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);

#endif