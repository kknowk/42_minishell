/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:18:14 by minabe            #+#    #+#             */
/*   Updated: 2023/07/30 10:31:01 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"
# include "minishell.h"

# define FILE_MODE	0644
# define PIPE_READ	0
# define PIPE_WRITE	1

typedef struct s_directory	t_directory;
typedef struct s_env_var	t_env_var;

void	execution(t_node *node, t_directory *dir,
			t_env_var **env_vars);

void	exec_pipe(t_node *node, t_directory *dir, t_env_var **env_vars);

void	select_builtin(char **cmds, t_directory *dir, t_env_var **env_vars);
int		judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars);
void	exec_from_bin(char **cmds, t_directory *dir);

int		open_redir_file(t_redirects *redir);
void	do_redirect(t_redirects *redirect);
void	restore_fd(t_redirects *redirect);

#endif