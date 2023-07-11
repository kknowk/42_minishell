/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:09:31 by minabe            #+#    #+#             */
/*   Updated: 2023/05/05 16:12:05 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#include <stdio.h>

void	*ft_realloc(void *p, size_t size)
{
	void	*new_data;

	new_data = NULL;
	if (size == 0)
		return (NULL);
	new_data = malloc(size);
	if (new_data == NULL)
		ft_error("malloc failed");
	if (p != NULL)
	{
		puts("realloc memcpy");
		ft_memcpy(new_data, p, size);
		free(p);
	}
	return (new_data);
}
