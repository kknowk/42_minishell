/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utiles2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:25:01 by khorike           #+#    #+#             */
/*   Updated: 2023/07/14 17:32:14 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_free(char *str)
{
	if (str)
	{
		free(str);
	}
}

void	ms_cpca(char *s1, char *s2, char *s3, char *s4)
{
	ft_strcpy(s1, s2);
	ft_strcat(s1, s3);
	ft_strcat(s1, s4);
}
