/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:09:39 by khorike           #+#    #+#             */
/*   Updated: 2023/07/20 16:18:19 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*search_quot(char **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (cmds[i][j] == '\'' || cmds[i][j] == '\"')
				return (cmds[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
typedef enum e_parse_state
{
	STATE_NORMAL,
	STATE_IN_DQUOTE
}	t_parse_state;

int get_var_length(const char *str)
{
	int	len;

	len = 1;
	while (str[len] != '\0' && str[len] != '\"' && str[len] != '\'' && !isspace(str[len]))
// 	while (str[len] != '\0' && str[len] != '\"' && str[len] != '$' && !isspace(str[len]))
		len++;
	return (len);
}

void	process_dquote_state(const char *str, size_t *i, char *result, int *j,
	t_directory *dir, t_env_var **env_vars, t_parse_state *state)
{
	if (str[*i] == '\"')
	{
		*state = STATE_NORMAL;
		(*i)++;
	}
	else if (str[*i] == '$')
	{
		int var_length = get_var_length(str + *i);
		char *substring = strndup(str + *i, var_length);
		char *expanded = doru_handl(substring, dir, env_vars);
		int expanded_length = strlen(expanded);
		if (expanded_length < 1024 - *j) {
			ft_strlcpy(result + *j, expanded, expanded_length + 1);
			*j += expanded_length;
			*i += var_length;
		}
		free(expanded);
		// free(substring);
	}
	else
		result[(*j)++] = str[(*i)++];
	*state = STATE_NORMAL;
}

char	*quot_handl(char *str, t_directory *dir, t_env_var **env_vars)
{
	size_t i = 0;
	char *result = ft_calloc(4048, 1);
	int j = 0;
	t_parse_state state = STATE_NORMAL;

	while (str[i] != '\0')
	{
		if (state == STATE_NORMAL)
		{
			if (str[i] == '\'')
			{
				i++;
				while (str[i] != '\'' && str[i] != '\0')
					result[j++] = str[i++];
				if (str[i] == '\'')
					i++;
			}
			else if (str[i] == '\"')
			{
				i++;
				state = STATE_IN_DQUOTE;
			}
			else
			{
				// if (result[j] == '\0')
				// {
				// 	result[j] = str[i++];
				// 	j++;
				// }
				result[j++] = str[i++];
			}
		}
		else if (state == STATE_IN_DQUOTE)
		{
			process_dquote_state(str, &i, result, &j, dir, env_vars, &state);
		}
	}
	result[j] = '\0';
	return (result);
}
