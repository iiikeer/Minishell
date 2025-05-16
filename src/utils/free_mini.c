/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:02:39 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/16 09:55:16 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_mini(t_mini *mini)
{
	size_t	i;

	if (!mini)
		return ;
	if (mini->input)
		free(mini->input);
	if (mini->tokens)
		free_array(mini->tokens);
	if (mini->nodes)
	{
		i = 0;
		while (mini->nodes[i])
		{
			if (mini->nodes[i]->full_cmd)
				free_array(mini->nodes[i]->full_cmd);
			if (mini->nodes[i]->full_path)
				free(mini->nodes[i]->full_path);
			free(mini->nodes[i]);
			i++;
		}
		free(mini->nodes);
	}
	if (access(".\vtemp\th", W_OK) == 0)
		unlink(".\vtemp\th");
}
