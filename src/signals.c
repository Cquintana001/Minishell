/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:45:14 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/23 09:28:05 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <signals.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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
	{
		printf("\n");
		printf ("ft_exit con frees etc\n");
		exit (0);
	}
	if (num == SIGQUIT)
	{
		printf("^\\Quit: 3\n");
		printf ("ft_exit con frees etc\n");
		exit (0);
	}
}

void	ft_signals_in_cat(void)
{
	signal(SIGINT, signal_handler_in_cat);
	signal(SIGQUIT, signal_handler_in_cat);
}

void	ft_check_rl(char *str, t_data **data)
{
	if (str == NULL)
	{
		printf("exit\n");
		printf ("/////------>ft_exit <------\n");
		(void) data;
		exit(-1);
	}
}
