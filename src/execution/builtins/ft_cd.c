/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:05:10 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/13 13:45:11 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_cd(t_node *node, char **env)
{
	char	*path;

	if (node->full_cmd[1] && node->full_cmd[2])
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	path = node->full_cmd[1];
	if (!path || ft_strcmp(path, "~") == 0)
		path = get_value("HOME", env);
	if (chdir(path) == -1)
	{
		if (node->full_cmd[1])
			printf("minishell: cd: %s: No such file or directory\n", \
															node->full_cmd[1]);
		else
			printf("minishell: cd: HOME: No such file or directory\n");
		return (1);
	}
	return (0);
}
