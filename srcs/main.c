/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:26:51 by minabe            #+#    #+#             */
/*   Updated: 2023/08/12 13:37:12 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	error;

	(void)argv;
	error = 0;
	if (argc == 1)
		minishell(envp, &error);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }
