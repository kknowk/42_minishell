/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:44:39 by khorike           #+#    #+#             */
/*   Updated: 2023/08/12 13:44:50 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	append_expanded(t_expand *exp, char **result)
{
	exp->temp = *result;
	*result = ft_strjoin(*result, exp->start);
	if (!*result)
		exit(EXIT_FAILURE);
	ft_free(exp->temp);
}
