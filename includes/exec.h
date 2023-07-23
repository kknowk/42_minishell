/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:18:14 by minabe            #+#    #+#             */
/*   Updated: 2023/07/23 17:20:06 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"
# include "minishell.h"

typedef struct s_directory	t_directory;
typedef struct s_env_var	t_env_var;

void	select_builtin(char **cmds, t_directory *dir, t_env_var **env_vars);
int		judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars);
void	exec_from_bin(char **cmds, t_directory *dir);

#endif