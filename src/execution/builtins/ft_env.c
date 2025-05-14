/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:08:35 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/08 11:09:29 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_env(t_node *node, char **env)
{
	size_t	i;

	if (node->full_cmd[1])
	{
		printf("env: ‘%s’: No such file or directory\n", node->full_cmd[1]);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
