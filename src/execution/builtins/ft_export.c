/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:25:48 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/12 11:17:15 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	change_var(t_mini *mini, char **env, char *var, char **s_var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i ++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		exit(1);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], s_var[0], ft_strlen(s_var[0])) == 0 \
										&& env[i][ft_strlen(s_var[0])] == '=')
			new_env[i] = ft_strdup(var);
		else
			new_env[i] = ft_strdup(env[i]);
		i ++;
	}
	new_env[i] = NULL;
	free_array(mini->env);
	mini->env = new_env;
}

static void	add_var(t_mini *mini, char **env, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i ++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		exit(1);
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		i ++;
	}
	new_env[i] = ft_strdup(var);
	i ++;
	new_env[i] = NULL;
	free_array(mini->env);
	mini->env = new_env;
}

static char	*set_var(char *var, int i, int j)
{
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	while (var[i] && var[i - 1] != '=')
		var[j++] = var[i++];
	while ((var[i] != ' ' || sq == 1 || dq == 1) && var[i] != '\0')
	{
		if (var[i] == '\'' && !dq)
		{
			sq = !sq;
			i ++;
		}
		else if (var[i] == '"' && !sq)
		{
			dq = !dq;
			i ++;
		}
		else
			var[j++] = var[i++];
	}
	var[j] = '\0';
	return (var);
}

static void	sort_export(char **env)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
	{
		if (!env[i + 1])
			break ;
		if (ft_strcmp(env[i], env[i + 1]) > 0)
		{
			temp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = temp;
			i = 0;
		}
		else
			i ++;
	}
	i = 0;
	while (env[i])
		printf("declare -x %s\n", env[i++]);
	free_array(env);
}

int	ft_export(t_mini *mini, char **env)
{
	int		i;
	char	*var;
	char	**s_var;
	char	**env_copy;

	i = 0;
	env_copy = copy_env(env);
	if (!mini->tokens[1])
		return (sort_export(env_copy), 0);
	var = set_var(ft_strchr(mini->input, ' ') + 1, 0, 0);
	s_var = ft_split(var, '=');
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], s_var[0], ft_strlen(s_var[0])) == 0 \
										&& env[i][ft_strlen(s_var[0])] == '=')
		{
			change_var(mini, env, var, s_var);
			free_array(s_var);
			return (0);
		}
		i ++;
	}
	free_array(s_var);
	add_var(mini, env, var);
	return (0);
}
