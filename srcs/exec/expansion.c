/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:39:48 by minabe            #+#    #+#             */
/*   Updated: 2023/08/01 16:59:53 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expansion(char *str, t_directory *dir, t_env_var **env_vars);

int	judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int	j;

	if (cmds[0] == NULL)
		return (1);
	j = 0;
	while (cmds[j])
	{
		cmds[j] = expansion(cmds[j], dir, env_vars);
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

void	expand_filename(t_redirects *redir,
			t_directory *dir, t_env_var **env_vars)
{
	while (redir != NULL)
	{
		redir->filename = expansion(redir->filename, dir, env_vars);
		redir = redir->next;
	}
}

static char	*expansion(char *str, t_directory *dir, t_env_var **env_vars)
{
	if (is_quoted(str))
		str = quote_handle(str, dir, env_vars);
	else
		str = dollar_handle(str, dir, env_vars);
	return (str);
}
