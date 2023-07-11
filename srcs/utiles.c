/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:08:52 by khorike           #+#    #+#             */
/*   Updated: 2023/07/11 17:07:52 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
// {
// 	void	*new_ptr;

// 	if (new_size == 0)
// 	{
// 		free(ptr);
// 		return (NULL);
// 	}
// 	else if (!ptr)
// 	{
// 		return (malloc(new_size));
// 	}
// 	else if (new_size <= old_size)
// 	{
// 		return (ptr);
// 	}
// 	else
// 	{
// 		new_ptr = malloc(new_size);
// 		if (new_ptr)
// 		{
// 			ft_memcpy(new_ptr, ptr, old_size);
// 			free(ptr);
// 		}
// 		return (new_ptr);
// 	}
// }
