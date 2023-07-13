/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:16:03 by minabe            #+#    #+#             */
/*   Updated: 2023/07/13 16:53:29 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

void	handle_signal(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	else if (signal == SIGQUIT)
		;
	else if (signal == SIGTERM)
	{
		printf("exit\n");
		exit(0);
	}
	g_interrupted = 1;
}

void	minishell(char *envp[])
{
	struct sigaction	sa;
	char				*line;
	t_token				*token;

	(void)envp;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	rl_outstream = stderr; // defoultがstdoutのため
	while (true)
	{
		g_interrupted = 0;
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		else
			add_history(line); // lineが'\0'のときは履歴に登録しない
		token = lexer(line);
		if (g_interrupted)
			continue ;
		// debug
		for (int i = 0; token != NULL; i++, token = token->next)
			printf("#%d\tstr: %s\tlen: %zu\ttype: %d\n", i, token->data, ft_strlen(token->data), token->type);

		/* ここにpercerやエクスパンション、コマンド実行を書く */

		tokenlist_clear(token);
		free(line);
	}
}

// int main()
// {
// 	struct sigaction sa;
// 	sa.sa_handler = handle_signal;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// 	sigaction(SIGTERM, &sa, NULL);
// 	while (1)
// 	{
// 		g_interrupted = 0;
// 		printf("Shell> ");
// 		fflush(stdout);
// 		if (g_interrupted)
// 		{
// 			continue ;
// 		}	
// 	}	
// 	return (0);
// }