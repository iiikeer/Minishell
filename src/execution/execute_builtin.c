/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:57:07 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/13 13:32:37 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_builtin(t_mini *mini, t_node *node)
{
	if (ft_strcmp(node->full_cmd[0], "cd") == 0)
		g_status = ft_cd(node, mini->env);
	else if (ft_strcmp(node->full_cmd[0], "env") == 0)
		g_status = ft_env(node, mini->env);
	else if (ft_strcmp(node->full_cmd[0], "pwd") == 0)
		g_status = ft_pwd();
	else if (ft_strcmp(node->full_cmd[0], "exit") == 0)
		g_status = ft_exit(mini, node, 0);
	else if (ft_strcmp(node->full_cmd[0], "echo") == 0)
		g_status = ft_echo(node);
	else if (ft_strcmp(node->full_cmd[0], "unset") == 0)
		g_status = ft_unset(mini, node, mini->env);
	else if (ft_strcmp(node->full_cmd[0], "export") == 0)
		g_status = ft_export(mini, mini->env);
	return (0);
}
