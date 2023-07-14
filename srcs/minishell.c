/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:16:03 by minabe            #+#    #+#             */
/*   Updated: 2023/07/14 16:25:12 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	g_interrupted = 0;

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
	g_interrupted = 1;
}

void	minishell(char *envp[])
{
	struct sigaction	sa;
	char				*line;
	t_token				*token;
	t_directory			dir;
	t_env_var			*env_vars;

	(void)envp;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	env_vars = create_env_vars(envp);
	if (getcwd(dir.path, sizeof(dir.path)) == NULL)
		exit(1);
	rl_outstream = stderr; // defoultがstdoutのため
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			ft_exit();
		else
			add_history(line); // lineが'\0'のときは履歴に登録しない
		token = lexer(line);
		ft_select(token, &dir, &env_vars);
		if (g_interrupted == 1)
		{
			free(line);
			g_interrupted = 0;
			continue ;
		}
		// if (!ft_strcmp(token->next->data, "pwd"))
		// 	ft_pwd(&dir);
		// if (g_interrupted)
		// 	continue ;
		// debug
		for (int i = 0; token != NULL; i++, token = token->next)
			printf("#%d\tstr: %s\tlen: %zu\ttype: %d\n", i, token->data, ft_strlen(token->data), token->type);

		/* ここにpercerやエクスパンション、コマンド実行を書く */

		tokenlist_clear(token);
		free(line);
	}
}
