/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:39:48 by minabe            #+#    #+#             */
/*   Updated: 2023/08/01 15:39:59 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int	j;

	if (cmds[0] == NULL)
		return (1);
	j = 0;
	while (cmds[j])
	{
		if (is_quoted(cmds[j]))
			cmds[j] = quote_handle(cmds[j], dir, env_vars);
		else
			cmds[j] = dollar_handle(cmds[j], dir, env_vars);
		if (!cmds[j])
			exit(1);
		j++;
	}
	if (!cmds)
		return (1);
	if (cmds[0][0] == '\0')
		return (1);
	return (0);
}
