/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:24:12 by minabe            #+#    #+#             */
/*   Updated: 2023/07/25 21:15:31 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <pthread.h>
# include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <errno.h>

# include "libft.h"
# include "token.h"
# include "lexer.h"
# include "parser.h"
# include "builtins.h"
# include "exec.h"
# include "expansion.h"

# ifndef DEBUG
#  define DEBUG 1
# endif

// typedef struct	s_shell
// {
// 	volatile sig_atomic_t	interrupted;
// 	int						syntax_error;
// 	// t_directory				dir;
// 	int						exit_error;
// }	 t_shell;

// extern t_shell	g_shell;

void	minishell(char *envp[]);

#endif