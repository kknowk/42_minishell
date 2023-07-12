/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:54:35 by khorike           #+#    #+#             */
/*   Updated: 2023/07/12 13:36:17 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <pthread.h>
# include <stdint.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PATH_MAX 256
# define FAILURE 1
# define SUCCESS 0

typedef struct s_env_var
{
	char				*key;
	char				*value;
	bool				is_shell_var;
	struct s_env_var	*next;
}	t_env_var;

int	ft_echo(char **str, int max_words);
int	ft_env(char *envp[]);
int	ft_pwd(void);
int	error_failure(char *str);

#endif