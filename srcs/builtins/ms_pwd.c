/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:05:49 by khorike           #+#    #+#             */
/*   Updated: 2023/07/11 17:20:15 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd failed");
		return (FAILURE);
	}
	else
		printf("%s\n", cwd);
	return (SUCCESS);
}

// test

// int	main(void)
// {
// 	ft_pwd();
// }
