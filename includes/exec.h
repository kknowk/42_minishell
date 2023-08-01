/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:18:14 by minabe            #+#    #+#             */
/*   Updated: 2023/08/01 19:08:38 by minabe           ###   ########.fr       */
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

void	exec_redir(t_redirects *redir, t_directory *dir, t_env_var **env_vars);

void	exec_pipe(t_node *node, t_directory *dir, t_env_var **env_vars);

void	select_builtin(char **cmds, t_directory *dir, t_env_var **env_vars);
int		judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars);

void	exec_from_bin(char **cmds, t_directory *dir, t_env_var **env_vars);
char	*expansion(char *str, t_directory *dir, t_env_var **env_vars);

int		open_redir_file(t_redirects *redir);
void	do_redirect(t_redirects *redirect);
void	restore_fd(t_redirects *redirect);

#endif