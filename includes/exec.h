/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:18:14 by minabe            #+#    #+#             */
/*   Updated: 2023/08/13 13:09:55 by minabe           ###   ########.fr       */
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

int		exec_redir(t_redirects *redir, t_directory *dir, t_env_var **env_vars);
void	exec_builtin(char **cmds, t_directory *dir, t_env_var **env_vars);
void	exec_from_bin(char **cmds, t_directory *dir, t_env_var **env_vars);
void	exec_pipe(t_node *node, t_directory *dir, t_env_var **env_vars);

bool	is_builtins(char *command);
bool	check_fd_or_dir(char *path, t_directory *dir);
bool	check_file_permission(char *path, t_directory *dir);

int		judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars);
char	*expansion(char *str, t_directory *dir, t_env_var **env_vars);

void	restore_fd(t_redirects *redirect);

#endif