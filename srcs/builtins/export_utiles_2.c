/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utiles_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:11:00 by khorike           #+#    #+#             */
/*   Updated: 2023/08/03 22:42:54 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_existing_val(t_env_var *existing_node,
	char *value, char **split_result, char *key)
{
	ft_free(existing_node->values);
	existing_node->values = ft_split(value, ':');
	if (!existing_node->values)
		exit(EXIT_FAILURE);
	existing_node->num_values = ft_count_values(existing_node->values);
	ft_free(value);
	ft_free(split_result);
	ft_free(key);
	return (SUCCESS);
}
