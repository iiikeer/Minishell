/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:05:16 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/08 11:56:20 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	count_env_vars(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	ft_unset(t_mini *mini, t_node *node, char **env)
{
	char	**new_env;
	char	*var;
	int		var_len;
	int		i;
	int		j;

	var = node->full_cmd[1];
	var_len = ft_strlen(var);
	i = count_env_vars(env);
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (EXIT_FAILURE);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) != 0 || env[i][var_len] != '=')
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	new_env[j] = NULL;
	free_array(mini->env);
	mini->env = new_env;
	return (0);
}
