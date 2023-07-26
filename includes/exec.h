/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:18:14 by minabe            #+#    #+#             */
/*   Updated: 2023/07/25 17:09:17 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"
# include "minishell.h"

# define FILE_MODE	0644

typedef struct s_directory	t_directory;
typedef struct s_env_var	t_env_var;

void	select_builtin(char **cmds, t_directory *dir, t_env_var **env_vars);
int		judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars);
void	exec_from_bin(char **cmds, t_directory *dir);

int		open_redir_file(t_redirects *redir);
void	do_redirect(t_redirects *redirect);
void	restore_fd(t_redirects *redirect);

#endif