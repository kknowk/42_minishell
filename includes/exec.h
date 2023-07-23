/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:18:14 by minabe            #+#    #+#             */
/*   Updated: 2023/07/23 15:33:40 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"
# include "minishell.h"

typedef struct s_directory t_directory;
typedef struct s_env_var t_env_var;

void	select_builtin(char **cmds, t_directory *dir, t_env_var **env_vars);
int	judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars);

#endif