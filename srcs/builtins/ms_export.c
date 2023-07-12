/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:47:53 by khorike           #+#    #+#             */
/*   Updated: 2023/07/12 13:38:34 by khorike          ###   ########.fr       */
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

int	ft_export(t_env_var **head, char *env_str)
{
	char		*key;
	char		*value;
	char		**split_result;
	t_env_var	*new_var;

	split_result = ft_split(env_str, '=');
	key = split_result[0];
	value = split_result[1];
	if (!split_result)
		return (error_failure("Splitting string failed"));
	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (error_failure("Memory allocation failed"));
	new_var->key = split_result[0];
	new_var->value = split_result[1];
	new_var->is_shell_var = false;
	new_var->next = NULL;
	new_var->next = *head;
	*head = new_var;
	free(split_result);
	return (SUCCESS);
}

// int	main(void)
// {
// 	t_env_var	*env_vars = NULL;
// 	char *env_str1 = "KEY1=Value1";
// 	char *env_str2 = "KEY2=Value2";

// 	ft_export(&env_vars, env_str1);
// 	ft_export(&env_vars, env_str2);
// 	t_env_var *current = env_vars;
// 	while (current != NULL)
// 	{
// 		printf("Key: %s, Value: %s\n", current->key, current->value);
// 		current = current->next;
// 	}
// 	current = env_vars;
// 	t_env_var *next;
// 	while (current != NULL)
// 	{
// 		next = current->next;
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
