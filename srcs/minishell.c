/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:16:03 by minabe            #+#    #+#             */
/*   Updated: 2023/07/15 14:19:04 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

volatile sig_atomic_t	g_interrupted = 0;

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
	t_directory			dir;
	t_env_var			*env_vars;

	(void)envp;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	env_vars = create_env_vars(envp);
	if (getcwd(dir.path, sizeof(dir.path)) == NULL)
		exit(1);
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
		ft_select(token, &dir, &env_vars);
		if (g_interrupted)
			continue ;
		// if (!ft_strcmp(token->next->data, "pwd"))
		// 	ft_pwd(&dir);
		if (g_interrupted)
			continue ;
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