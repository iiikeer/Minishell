/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipes_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:59:53 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/12 11:42:51 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**change_tokens(char **tokens)
{
	int		i;
	int		count;
	char	**new_tokens;

	count = 0;
	while (tokens[count])
		count ++;
	new_tokens = malloc(sizeof(char *) * (count + 2));
	if (!new_tokens)
		return (NULL);
	i = 0;
	new_tokens[i] = NULL;
	while (tokens[i])
	{
		new_tokens[i + 1] = ft_strdup(tokens[i]);
		i ++;
	}
	i ++;
	new_tokens[i] = NULL;
	return (new_tokens);
}

static void	free_tmp(char **arr, int i)
{
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	validate_pipes_redir(t_mini *mini)
{
	char	**tokens;

	tokens = change_tokens(mini->tokens);
	if (validate_redirections(tokens) == 0)
	{
		g_status = 2;
		printf("Invalid redirections\n");
		free(mini->input);
		free_array(mini->tokens);
		free_tmp(tokens, 1);
		mini_loop(mini);
	}
	if (validate_pipes(tokens) == 0)
	{
		g_status = 2;
		printf("Invalid pipes\n");
		free(mini->input);
		free_array(mini->tokens);
		free_tmp(tokens, 1);
		mini_loop(mini);
	}
	free_tmp(tokens, 1);
}
