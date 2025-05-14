/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:04:41 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/12 12:11:14 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**get_node(char **tokens, char ***next)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new[j] = ft_strdup(tokens[j]);
		j++;
	}
	new[j] = NULL;
	tokens += i;
	if (*tokens && ft_strcmp(*tokens, "|") == 0)
		tokens++;
	*next = tokens;
	return (new);
}

static int	count_nodes(char *input)
{
	int	i;
	int	count;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	count = 1;
	while (input[i] != '\0')
	{
		open_quotes(input[i], &sq, &dq);
		if (input[i] == '|' && sq == 0 && dq == 0)
			count++;
		i++;
	}
	return (count);
}

void	create_nodes(t_mini *mini)
{
	t_node	**nodes;
	char	**tmp;
	char	**next;
	int		i;

	mini->nbr_nodes = count_nodes(mini->input);
	nodes = malloc(sizeof(t_node *) * (mini->nbr_nodes + 1));
	if (!nodes)
		return ;
	tmp = mini->tokens;
	i = 0;
	while (i < mini->nbr_nodes)
	{
		tmp = get_node(tmp, &next);
		nodes[i] = new_node(mini, tmp);
		free_array(tmp);
		tmp = next;
		i++;
	}
	nodes[i] = NULL;
	mini->nodes = nodes;
}
