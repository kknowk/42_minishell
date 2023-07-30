/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_waitpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:44:19 by minabe            #+#    #+#             */
/*   Updated: 2023/07/30 11:44:35 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_waitpid(pid_t pid, int *status, int options)
{
	if (waitpid(pid, status, options) == -1)
		exit(EXIT_FAILURE);
}
