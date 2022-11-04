/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:45:14 by amarzana          #+#    #+#             */
/*   Updated: 2022/11/04 08:03:04 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_function.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <signals.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	rl_replace_line(const char *text, int clear_undo);

void	signal_handler(int num)
{
	(void)num;
	if (rl_on_new_line() == -1)
		exit(-1);
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ft_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_in_cat(int num)
{
	if (num == SIGINT)
		write(2, "\n", 1);
	if (num == SIGQUIT)
		write(2, "^\\Quit: 3\n", 10);
}

void	ft_signals_in_cat(void)
{
	signal(SIGINT, signal_handler_in_cat);
	signal(SIGQUIT, signal_handler_in_cat);
}
