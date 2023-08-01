/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:16:03 by minabe            #+#    #+#             */
/*   Updated: 2023/07/31 18:47:49 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_env_var	*init_minishell(char *envp[], t_directory *dir)
{
	t_env_var			*env_vars;

	setup_signals();
	env_vars = create_env_vars(envp);
	if (getcwd(dir->path, sizeof(dir->path)) == NULL || !env_vars)
		exit(1);
	dir->error.error_num = 0;
	return (env_vars);
}

void	minishell(char *envp[], int *error)
{
	char				*line;
	t_token				*token;
	t_node				*node;
	t_directory			dir;
	t_env_var			*env_vars;

	env_vars = init_minishell(envp, &dir);
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			ft_exit();
		else
			add_history(line);
		token = lexer(line, error);
		node = parser(token);
		handle_interruption(node, &dir, env_vars, error);
		destroy_parser(node);
		ft_free(line);
	}
}
