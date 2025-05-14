/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:12:02 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/08 14:14:09 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*check_path(char *cmd, char *path_prefix)
{
	char	*temp_path;
	char	*cmd_path;

	temp_path = ft_strjoin(path_prefix, "/");
	if (!temp_path)
		return (NULL);
	cmd_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

static void	set_cmd_paths(t_node *node, char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = check_path(cmd, paths[i]);
		if (cmd_path)
		{
			if (node->full_path)
				free(node->full_path);
			node->full_path = cmd_path;
			return ;
		}
		i++;
	}
	node->is_exec = 0;
}

void	set_paths(t_node *node, char **env, int i)
{
	char	**paths;

	paths = NULL;
	if (access(node->full_cmd[0], X_OK) == 0)
	{
		node->full_path = ft_strdup(node->full_cmd[0]);
		return ;
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0 && ft_strlen(env[i]) > 5)
		{
			paths = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!paths)
	{
		node->is_exec = 0;
		return ;
	}
	set_cmd_paths(node, node->full_cmd[0], paths);
	free_array(paths);
}
