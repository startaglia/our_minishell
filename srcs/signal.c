/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:03:30 by dcarassi          #+#    #+#             */
/*   Updated: 2023/06/19 13:05:23 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_siginit(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
		return ;
	}
}

void	ft_signal(void)
{
	struct sigaction	signal;
	struct termios		attribute;

	tcgetattr(STDIN_FILENO, &attribute);
	attribute.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &attribute);
	signal.sa_handler = &handle_siginit;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, 0);
	sigaction(SIGQUIT, &signal, 0);
}

void	reset_sig(void)
{
	ft_reset_signal();
	sigaction(SIGINT, 0, 0);
	sigaction(SIGQUIT, 0, 0);
}

void	ft_reset_signal(void)
{
	struct sigaction	signal;
	struct termios		attribute;

	tcgetattr(STDIN_FILENO, &attribute);
	attribute.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &attribute);
	signal.sa_handler = NULL;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, 0);
	sigaction(SIGQUIT, &signal, 0);
}
