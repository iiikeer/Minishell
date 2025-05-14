/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:49:11 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/08 13:15:30 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_redir(char *token)
{
	if (ft_strncmp(token, "'|'", 3) == 0)
		return (1);
	else if (ft_strncmp(token, "\"|\"", 3) == 0)
		return (1);
	else if (ft_strncmp(token, "'<'", 3) == 0)
		return (1);
	else if (ft_strncmp(token, "\"<\"", 3) == 0)
		return (1);
	else if (ft_strncmp(token, "'>'", 3) == 0)
		return (1);
	else if (ft_strncmp(token, "\">\"", 3) == 0)
		return (1);
	else if (ft_strncmp(token, "'>>'", 4) == 0)
		return (1);
	else if (ft_strncmp(token, "\">>'", 4) == 0)
		return (1);
	else if (ft_strncmp(token, "'<<'", 4) == 0)
		return (1);
	else if (ft_strncmp(token, "\"<<\"", 4) == 0)
		return (1);
	return (0);
}

static void	remove_quotes(char *token)
{
	char	q;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(token);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			q = token[i];
			i++;
			while (i < len && token[i] != q)
				token[j++] = token[i++];
			i++;
		}
		else
			token[j++] = token[i++];
	}
	token[j] = '\0';
}

void	quotes_remover(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (has_quotes(tokens[i]) == 1)
		{
			if (is_redir(tokens[i]) == 0)
				remove_quotes(tokens[i]);
		}
		i ++;
	}
}
