/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:24:12 by minabe            #+#    #+#             */
/*   Updated: 2023/07/28 12:42:58 by khorike          ###   ########.fr       */
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
# include "directory.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

void	minishell(char *envp[], int *error);

#endif