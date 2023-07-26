/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:18:24 by minabe            #+#    #+#             */
/*   Updated: 2023/07/25 18:35:29 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

ssize_t	ft_putendl(char *s)
{
	ssize_t	size;

	size = ft_putstr_fd(1, s);
	size += ft_putchar('\n');
	return (size);
}
