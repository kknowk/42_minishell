/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:23:57 by khorike           #+#    #+#             */
/*   Updated: 2023/08/13 14:50:50 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_signals(void)
{
	if (signal(SIGINT, handle_exec_signal) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, handle_exec_signal) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
}
