/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:16:03 by minabe            #+#    #+#             */
/*   Updated: 2023/07/11 17:26:55 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"
#include "builtins.h"

void	minishell(char *envp[])
{
	char	*line;
	// t_token	*token;

	(void)envp;
	rl_outstream = stderr; // defoultがstdoutのため
	while (true)
	{
		line = readline("minishell$ ");
		if (!strcmp(line, "pwd"))
			ft_pwd();
		if (line == NULL)
			break ;
		else
			add_history(line); // lineが'\0'のときは履歴に登録しない
		// token = lexer(line);
		/* "ctrl-C, -Z, -/" の処理 */
		// if (signal(SIGINT, ) == SIG_ERR)
		// {
		// 	/* 出力 */
		// 	exit(EXIT_FAILURE);
		// }
		// if (signal(SIGQUIT, ) == SIG_ERR)
		// {
		// 	/* 出力 */
		// 	exit(EXIT_FAILURE);
		// }

		// debug
		// for (int i = 0; token->next != NULL; i++)
		// 	printf("str: %s\n", token->data);

		/* ここにpercerやエクスパンション、コマンド実行を書く */

		// tokenlist_clear(token);
		free(line);
	}
}
