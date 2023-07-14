/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:54:35 by khorike           #+#    #+#             */
/*   Updated: 2023/07/13 19:30:52 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <string.h>

# include "minishell.h"

# define PATH_MAX 1024
# define FAILURE 1
# define SUCCESS 0

typedef struct s_env_var
{
	char				*key;
	char				*value;
	bool				is_shell_var;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_directory
{
	char	path[PATH_MAX];
}	t_directory;

int			ft_echo(char **str, int max_words);
int			ft_env(t_env_var *head);
int			ft_export(t_env_var **head, char *env_str);
int			ft_unset(t_env_var **head, char *key);
int			ft_pwd(t_directory *dir);
int			ft_cd(t_directory *dir, char *path);
int			error_failure(char *str);
t_env_var	*create_env_vars(char *envp[]);

// 場所は任せた！！ by minabe
void		ft_select(t_token *token, t_directory *dir, t_env_var **env_vars);

void		execute_command(char *command);
void		ft_exit(void);

#endif