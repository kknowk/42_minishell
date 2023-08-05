/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:39:22 by khorike           #+#    #+#             */
/*   Updated: 2023/08/05 12:22:35 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTORY_H
# define DIRECTORY_H

# define PATH_MAX 1024

typedef struct s_error
{
	int	error_num;
}	t_error;

typedef struct s_directory
{
	char	path[PATH_MAX];
	t_error	error;
}	t_directory;

#endif
