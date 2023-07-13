/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/13 17:49:52 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

void	ft_select(t_token *token, t_directory *dir)
{
	if (!ft_strcmp(token->next->data, "pwd"))
		ft_pwd(dir);
	if (!ft_strcmp(token->next->data, "cd"))
		ft_cd(dir, token->next->next->data);
	if (!ft_strcmp(token->next->data, "exit"))
		ft_exit();
}
