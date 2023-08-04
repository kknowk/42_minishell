/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:39:22 by khorike           #+#    #+#             */
/*   Updated: 2023/08/04 14:53:44 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTORY_H
# define DIRECTORY_H

# define PATH_MAX 1024

typedef struct s_error
{
	int	error_num;
	int	error_tmp;
}	t_error;

typedef struct s_directory
{
	char	path[PATH_MAX];
	t_error	error;
}	t_directory;

#endif
