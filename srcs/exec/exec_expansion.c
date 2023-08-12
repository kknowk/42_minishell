/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:39:48 by minabe            #+#    #+#             */
/*   Updated: 2023/08/04 17:32:49 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_empty_entries(char **cmds, t_directory *dir,
			t_env_var **env_vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		cmds[i] = expansion(cmds[i], dir, env_vars);
		if (cmds[i] && cmds[i][0] != '\0')
		{
			cmds[j++] = cmds[i];
		}
		i++;
	}
	cmds[j] = NULL;
}

int	judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	remove_empty_entries(cmds, dir, env_vars);
	if (!cmds || cmds[0] == NULL || cmds[0][0] == '\0')
	{
		return (1);
	}
	return (0);
}

char	*expansion(char *str, t_directory *dir, t_env_var **env_vars)
{
	if (is_quoted(str))
		str = quote_handle(str, dir, env_vars);
	else
		str = dollar_handle(str, dir, env_vars);
	return (str);
}
