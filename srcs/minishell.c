/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:16:03 by minabe            #+#    #+#             */
/*   Updated: 2023/07/11 14:59:36 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char *envp[])
{
	char	*line;
	t_token	*token;

	(void)envp;
	line = readline("minishell > ");
	if (line)
		add_history(line);
	/* "ctrl-C, -Z, -/" の処理追加する */
	token = lexer(line);

	// debug
	for (int i = 0; token->next != NULL; i++)
		printf("str: %s\n", token->data);

	clear_token(token);
}
