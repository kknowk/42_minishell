/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:16:03 by minabe            #+#    #+#             */
/*   Updated: 2023/07/26 12:48:39 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

t_shell	g_shell;

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		;
	g_shell.interrupted = 1;
}

void	minishell(char *envp[])
{
	struct sigaction	sa;
	char				*line;
	t_token				*token;
	t_node				*node;
	t_directory			dir;
	t_env_var			*env_vars;

	(void)envp;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	env_vars = create_env_vars(envp);
	if (getcwd(dir.path, sizeof(dir.path)) == NULL || !env_vars)
		exit(1);
	rl_outstream = stderr; // defaultがstdoutのため
	dir.error = 0;
	dir.malloc_error = 0;
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			ft_exit();
		else
			add_history(line); // lineが'\0'のときは履歴に登録しない
		token = lexer(line);
		node = parser(token);
		if (g_shell.syntax_error)
			perror("syntax error");
		execution(node, &dir, &env_vars);
		if (g_shell.interrupted == 1)
		{
			free(line);
			g_shell.interrupted = 0;
			continue ;
		}
		restore_fd(node->redirects);
		destroy_parser(node);
		ft_free(line);
	}
}
