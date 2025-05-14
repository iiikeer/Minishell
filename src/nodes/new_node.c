/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:39:39 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/12 12:11:49 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*new_node(t_mini *mini, char **tokens)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		write(2, "\033[31mError: Memory allocation failed\n\033[0m", 42);
		exit (EXIT_FAILURE);
	}
	init_node(node);
	node->full_cmd = set_cmd(tokens, 0, 0, 0);
	if (!is_builtin(node->full_cmd[0]))
		set_paths(node, mini->env, 0);
	if (set_in_out_file(node, tokens, STDIN_FILENO, STDOUT_FILENO) == 0)
		node->is_exec = 0;
	else
		node->is_exec = 1;
	return (node);
}
