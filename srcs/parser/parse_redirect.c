/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:06:37 by minabe            #+#    #+#             */
/*   Updated: 2023/08/14 13:44:04 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirects	*create_redirect(void)
{
	t_redirects	*redirect;

	redirect = malloc(sizeof(t_redirects));
	if (!redirect)
		exit(EXIT_FAILURE);
	redirect->type = 0;
	redirect->fd = -1;
	redirect->fd_file = -1;
	redirect->fd_backup = -1;
	redirect->heredoc_flag = 0;
	redirect->filename = NULL;
	redirect->next = NULL;
	return (redirect);
}

static t_redirect_type	judge_redir_type(t_token **token)
{
	if ((*token)->type == '<')
		return (REDIRECT_INPUT);
	else if ((*token)->type == '>')
		return (REDIRECT_OUTPUT);
	else if ((*token)->type == CHAR_D_GREATER)
		return (REDIRECT_APPEND_OUTPUT);
	else
		return (REDIRECT_HEREDOC);
}

int	set_redirect(t_node *node, t_token **token)
{
	t_redirects	*redir;
	t_redirects	*new;

	if ((*token)->next == NULL)
		return (FAILURE);
	new = create_redirect();
	new->type = judge_redir_type(token);
	new->filename = ft_strdup((*token)->next->data);
	if ((*token)->type == CHAR_LESSER)
		new->fd = STDIN_FILENO;
	else if ((*token)->type == CHAR_GREATER)
		new->fd = STDOUT_FILENO;
	else if ((*token)->type == CHAR_D_GREATER)
		new->fd = STDOUT_FILENO;
	if (node->redirects == NULL)
		node->redirects = new;
	else
	{
		redir = node->redirects;
		while (redir->next != NULL)
			redir = redir->next;
		redir->next = new;
	}
	(*token) = (*token)->next->next;
	return (SUCCESS);
}

void	destroy_redirects(t_redirects *redirects)
{
	t_redirects	*tmp;

	while (redirects != NULL)
	{
		tmp = redirects->next;
		if (redirects->filename != NULL)
			ft_free(redirects->filename);
		ft_free(redirects);
		redirects = tmp;
	}
}
