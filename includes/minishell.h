/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:24:12 by minabe            #+#    #+#             */
/*   Updated: 2023/07/19 14:57:30 by khorike          ###   ########.fr       */
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

# include "lexer.h"
# include "parser.h"
# include "token.h"
# include "libft.h"
# include "builtins.h"

# ifndef DEBUG
#  define DEBUG 1
# endif

void	minishell(char *envp[]);

#endif