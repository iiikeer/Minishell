/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:50:04 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/16 08:47:44 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_status(char *var, int i[2])
{
	char	*status_str;

	status_str = ft_itoa(g_status);
	ft_strcpy(&var[i[1]], status_str);
	i[1] += ft_strlen(status_str);
	i[0] += 2;
	free(status_str);
}

static int	handle_variable(const char *input, int i[2], char *var, char **env)
{
	int		start;
	char	*name;
	char	*value;

	if (input[i[0] + 1] == '?')
		return (expand_status(&var[i[1]], i), 1);
	else
		(*i)++;
	start = i[0];
	while (input[i[0]] && (ft_isalnum(input[i[0]]) || input[i[0]] == '_'))
		i[0]++;
	name = ft_strndup(input + start, i[0] - start);
	value = get_value(name, env);
	if (value)
	{
		ft_strcpy(&var[i[1]], value);
		i[1] += ft_strlen(value);
		free(name);
		return (1);
	}
	else
		return (0);
}

static char	*expand_var(char *token, char **env)
{
	int		i[2];
	char	*var;

	i[0] = 0;
	i[1] = 0;
	var = malloc(sizeof(char) * (ft_strlen(token) + 4096));
	if (!var)
		return (NULL);
	while (token[i[0]] != '\0')
	{
		if (token[i[0]] == '$')
		{
			if (handle_variable(token, i, var, env) == 1)
				continue ;
			else
				var[i[1]++] = token[i[0]];
		}
		else
			var[i[1]++] = token[i[0]++];
	}
	var[i[1]] = '\0';
	free(token);
	return (var);
}

void	expand_tokens(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->tokens[i] != NULL)
	{
		if (ft_strchr(mini->tokens[i], '$') != NULL)
		{
			if (mini->tokens[i][0] == '\'')
				break ;
			if (ft_strcmp(mini->tokens[i], "$") == 0)
				break ;
			mini->tokens[i] = expand_var(mini->tokens[i], mini->env);
		}
		i++;
	}
}
