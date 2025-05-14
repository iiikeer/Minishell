/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 08:53:06 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/12 11:42:51 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_special_token(t_mini *mini)
{
	if (ft_strcmp(mini->tokens[0], "$?") == 0)
	{
		printf("%d: command not found\n", g_status);
		g_status = 127;
		return (1);
	}
	return (0);
}

static int	validate_command(t_mini *mini)
{
	if (mini->nodes[0]->is_exec == 0)
	{
		printf("%s: command not found\n", mini->tokens[0]);
		g_status = 127;
		return (0);
	}
	return (1);
}

void	execution(t_mini *mini)
{
	if (ft_strchr(mini->input, '|'))
		execute_multiple_cmds(mini);
	else
	{
		if (handle_special_token(mini) && !validate_command(mini))
			return ;
		execute_cmd(mini, mini->nodes[0]);
	}
}
