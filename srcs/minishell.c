/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:16:03 by minabe            #+#    #+#             */
/*   Updated: 2023/07/11 14:27:40 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char *envp[])
{
	char	*line;

	(void)envp;
	line = readline("minishell > ");
	if (line)
		add_history(line);
	/* ctrl+C, +Zの処理追加する */
	lexer(line);
}
