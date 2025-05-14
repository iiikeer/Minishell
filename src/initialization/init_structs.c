/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:04:35 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/08 10:37:13 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_node(t_node *node)
{
	if (!node)
		return ;
	node->full_cmd = NULL;
	node->full_path = NULL;
	node->infile = -1;
	node->outfile = -1;
	node->is_exec = 0;
	node->pid = -1;
}

void	init_mini(t_mini *mini)
{
	if (!mini)
		return ;
	mini->input = NULL;
	mini->tokens = NULL;
	mini->nodes = NULL;
	mini->nbr_nodes = 0;
}
