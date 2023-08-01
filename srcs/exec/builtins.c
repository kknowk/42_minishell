/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/08/01 16:54:21 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_export(char **cmds, t_env_var **env_vars, int *falgs)
{
	int		status;

	status = SUCCESS;
	if (!cmds[1])
		return (declare(*env_vars));
	status = ft_export(env_vars, cmds, falgs);
	if (status == EXIT_ERROR)
		exit(1);
	return (status);
}

static void	run_command(char **cmds, t_directory *dir,
			t_env_var **env_vars, int *flags)
{
	int	i;

	if (!ft_strcmp(cmds[0], "pwd"))
		dir->error.error_num = ft_pwd(dir);
	else if (!ft_strcmp(cmds[0], "cd"))
		dir->error.error_num = ft_cd(dir, cmds[1], env_vars);
	else if (!ft_strcmp(cmds[0], "exit"))
		dir->error.error_num = ft_ms_exit(cmds + 1);
	else if (!ft_strcmp(cmds[0], "env"))
		dir->error.error_num = ft_env(*env_vars);
	else if (!ft_strcmp(cmds[0], "echo"))
	{
		i = 0;
		while (cmds[i])
			i++;
		dir->error.error_num = ft_echo(cmds, i - 1);
	}
	else if (!ft_strcmp(cmds[0], "export"))
		dir->error.error_num = handle_export(cmds, env_vars, flags);
	else if (!ft_strcmp(cmds[0], "unset"))
		dir->error.error_num = ft_unset(env_vars, cmds, flags);
}

static int	*init_flags(char **cmds)
{
	int	i;
	int	*flags;
	int	k;

	i = 0;
	while (cmds[i])
		i++;
	flags = ft_calloc(i, sizeof(int));
	if (!flags)
		exit(1);
	k = 0;
	while (cmds[k])
	{
		if (is_quoted(cmds[k]))
			flags[k] = 1;
		k++;
	}
	return (flags);
}

void	select_builtin(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int	*flags;

	flags = init_flags(cmds);
	if (judgement_desuno(cmds, dir, env_vars))
		return ;
	run_command(cmds, dir, env_vars, flags);
	ft_free(flags);
}
