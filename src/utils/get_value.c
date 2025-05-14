/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:46:25 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/13 13:46:52 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_value(char *name, char **env)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0 \
											&& env[i][ft_strlen(name)] == '=')
		{
			value = ft_strchr(env[i], '=') + 1;
		}
		i ++;
	}
	return (value);
}
