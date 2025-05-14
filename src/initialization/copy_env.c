/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:12:24 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/12 11:14:28 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**copy_env(char **env)
{
	size_t	i;
	char	**env_copy;

	i = 0;
	while (env[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
	{
		write(2, "\033[31mError: Memory allocation failed\n\033[0m", 42);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
