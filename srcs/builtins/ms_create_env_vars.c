/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_create_env_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:30:19 by khorike           #+#    #+#             */
/*   Updated: 2023/07/11 19:55:49 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	if (size > 0)
// 	{
// 		while (src[i] && i < size - 1)
// 		{
// 			dest[i] = src[i];
// 			i++;
// 		}
// 		dest[i] = '\0';
// 	}
// 	while (src[i])
// 		i++;
// 	return (i);
// }

// static int	count_words(char const *s, char c)
// {
// 	int	count;
// 	int	in_word;

// 	count = 0;
// 	in_word = 0;
// 	while (*s)
// 	{
// 		if (*s == c)
// 			in_word = 0;
// 		else if (!in_word)
// 		{
// 			in_word = 1;
// 			count++;
// 		}
// 		s++;
// 	}
// 	return (count);
// }

// static char	*get_word(char const **s, char c)
// {
// 	char const	*start;
// 	char		*word;
// 	int			len;

// 	start = *s;
// 	len = 0;
// 	while (**s && **s != c)
// 	{
// 		(*s)++;
// 		len++;
// 	}
// 	word = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!word)
// 		return (NULL);
// 	ft_strlcpy(word, start, len + 1);
// 	return (word);
// }

// static void	check_malloc(char **ptr, int word_count)
// {
// 	int	i;

// 	if (!ptr)
// 	{
// 		i = 0;
// 		while (i < word_count)
// 		{
// 			free(ptr[i]);
// 			i++;
// 		}
// 		free(ptr);
// 	}
// }

// static void	split_string(char const *s, char c, char **result)
// {
// 	int	i;

// 	i = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			result[i] = get_word(&s, c);
// 			if (!result[i])
// 				check_malloc(result, i);
// 			i++;
// 		}
// 		else
// 			s++;
// 	}
// 	result[i] = NULL;
// }

// static char	**ft_split(char const *s, char c)
// {
// 	char	**result;
// 	int		word_count;

// 	if (!s)
// 		return (NULL);
// 	word_count = count_words(s, c);
// 	result = (char **)malloc(sizeof(char *) * (word_count + 1));
// 	if (!result)
// 		return (NULL);
// 	split_string(s, c, result);
// 	return (result);
// }

static t_env_var	*check_split(t_env_var *head)
{
	t_env_var	*current;
	t_env_var	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	return (NULL);
}

static void	helper_env(char **split_result, t_env_var **head, t_env_var **prev)
{
	char		*key;
	char		*value;
	t_env_var	*new_var;

	key = split_result[0];
	value = split_result[1];
	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
	{
		free(split_result);
		perror("Memory allocation failed");
		exit(1);
	}
	new_var->key = key;
	new_var->value = value;
	new_var->is_shell_var = false;
	new_var->next = NULL;
	if (*prev == NULL)
		*head = new_var;
	else
		(*prev)->next = new_var;
	*prev = new_var;
	free(split_result);
}

t_env_var	*create_env_vars(char *envp[])
{
	t_env_var	*head;
	t_env_var	*prev;
	int			i;
	char		**split_result;

	i = 0;
	head = NULL;
	prev = NULL;
	while (envp[i] != NULL)
	{
		split_result = ft_split(envp[i], '=');
		if (!split_result)
			return (check_split(head));
		helper_env(split_result, &head, &prev);
		i++;
	}
	return (head);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	(void)argc;
// 	(void)argv;

// 	// 環境変数の作成
// 	t_env_var *env_vars = create_env_vars(envp);
// 	// 環境変数の表示
// 	t_env_var *current = env_vars;
// 	while (current)
// 	{
// 		printf("%s=%s\n", current->key, current->value);
// 		current = current->next;
// 	}	
// 	// 環境変数の解放
// 	current = env_vars;
// 	while (current)
// 	{
// 		t_env_var *next = current->next;
// 		free(current->key);
// 		free(current->value);
// 		free(current);
// 		current = next;
// 	}
// 	return (0);
// }

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }
