/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:05:49 by khorike           #+#    #+#             */
/*   Updated: 2023/07/22 14:52:03 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_directory *dir)
{
	printf("%s\n", dir->path);
	return (SUCCESS);
}

// test

// int	main(void)
// {
// 	ft_pwd();
// }
