/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:54:35 by khorike           #+#    #+#             */
/*   Updated: 2023/08/02 15:09:43 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <string.h>
# include <ctype.h>

# include "minishell.h"
# include "directory.h"

// # define PATH_MAX 1024
# define FAILURE 1
# define SUCCESS 0
# define EXIT_ERROR 2
# define MAX_BUFFER_SIZE 4096

typedef struct s_env_var
{
	char				*key;
	char				**values;
	int					num_values;
	bool				is_shell_var;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_expand
{
	char	*start;
	char	*end;
	char	*value;
	char	*temp;
}	t_expand;

typedef enum e_parse_state
{
	STATE_NORMAL,
	STATE_IN_DQUOTE
}	t_parse_state;

typedef struct s_parse_context
{
	char		*str;
	size_t		i;
	char		*result;
	int			j;
	t_directory	*dir;
	t_env_var	**env_vars;
}	t_parse_context;

int			ft_echo(char **str, int max_words);
int			ft_env(t_env_var *head);
int			ft_export(t_env_var **head, char **cmds, int *flags);
int			ft_ms_exit(char **args);
int			ft_unset(t_env_var **head, char **keys, int *flags);
int			ft_pwd(t_directory *dir);
int			ft_cd(t_directory *dir, char *path, t_env_var **head);

int			error_failure(char *str, char **str1);
void		error_put(char *str);
int			error_str(char *str);
size_t		ft_strcspn(const char *s1r, const char *s2r);
size_t		ft_strspn(const char *s1, const char *s2);

char		**return_null_free(char *str);
void		ms_cpca(char *s1, char *s2, char *s3, char *s4);
int			is_valid_varname(char *varname);
int			has_error(char *input);

// char		*search_equal(char **cmds);
char		*search_equal(char *cmds);
char		*error_in_export(char *str);
int			ft_count_values(char **values);
char		*is_valid_name(char *name);
int			declare(t_env_var *head);
char		*get_next_var(char **cmds, char *s1);
int			type_existing_val(t_env_var *existing_node,
				char *value, char **split_result, char *key);

t_env_var	*create_env_vars(char *envp[], char *path);
void		set_initial_env_vars(t_env_var **head, char *path);

int			execute_command(char *command, char **cmds, t_env_var **env_vars);
int			execute_command_from_path(char *command_path, char **cmds);
void		ft_exit(void);
void		numeric_error_exit(void);

char		*handle_question_mark(char *str, char *tmp, t_directory *dir);
char		*handle_dollar_sign(char *str, char *tmp);
char		*handle_default(char *str, char *tmp, t_env_var **head);

char		*dollar_handle(char *str, t_directory *dir, t_env_var **head);
char		**search(t_env_var **head, char *key);
bool		is_quoted(char *cmd);
char		*expand_and_replace(char *input, t_env_var **head);

char		*search_quote(char **cmds);
int			get_var_length(const char *str);
void		change_normal_plus(t_parse_context *ctx, t_parse_state *state);
char		*quote_handle(char *str, t_directory *dir, t_env_var **env_vars);

void		process_dollar(t_parse_context *ctx);
void		process_normal_character(t_parse_context *ctx);

void		error_printf(const char *msg, const char *path);

#endif