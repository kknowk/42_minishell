/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:16:03 by minabe            #+#    #+#             */
/*   Updated: 2023/08/13 14:12:24 by khorike          ###   ########.fr       */
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
	if (getcwd(dir->path, sizeof(dir->path)) == NULL)
		exit(EXIT_FAILURE);
	env_vars = create_env_vars(envp, dir->path);
	dir->error.error_num = 0;
	dir->signal_received = 0;
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
		handle_interruption(node, &dir, &env_vars, error);
		destroy_parser(node);
		ft_free(line);
	}
}
