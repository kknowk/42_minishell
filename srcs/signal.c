/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:15:47 by khorike           #+#    #+#             */
/*   Updated: 2023/07/31 18:53:39 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_interrupted = 0;

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_interrupted = 1;
	}
	else if (signal == SIGQUIT)
		;
}

void	setup_signals(void)
{
	struct sigaction	sa;
	struct sigaction	ss;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	ss.sa_handler = SIG_IGN;
	sigemptyset(&ss.sa_mask);
	ss.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGQUIT, &ss, NULL) == -1)
		exit(EXIT_FAILURE);
}

static void	execute_and_reset_error(t_node *node, t_directory *dir,
		t_env_var **env_vars, int *error)
{
	if (node == NULL)
	{
		if (*error == 2)
			dir->error.error_num = 2;
		if (*error == 1)
			dir->error.error_num = 1;
	}
	execution(node, dir, env_vars);
	*error = 0;
}

void	handle_interruption(t_node *node, t_directory *dir,
			t_env_var *env_vars, int *error)
{
	if (g_interrupted == 1)
	{
		*error = g_interrupted;
		dir->error.error_num = g_interrupted;
		g_interrupted = 0;
	}
	execute_and_reset_error(node, dir, &env_vars, error);
}
