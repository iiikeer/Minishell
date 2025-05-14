/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:07:59 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/08 13:59:45 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	add_spaces(char *line, char *new, int i, int j)
{
	new[j++] = ' ';
	new[j++] = line[i];
	while (line[i] == line[i + 1])
		new[j++] = line[i++];
	new[j++] = ' ';
	return (j);
}

static void	space(char *new, char c, int *count, int *j)
{
	if ((*count) % 2 != 0)
	{
		(*count)++;
		new[(*j)++] = ' ';
		new[(*j)++] = c;
	}
	else if ((*count) % 2 == 0)
	{
		(*count)++;
		new[(*j)++] = c;
		new[(*j)++] = ' ';
	}
}

static char	*add_quote_spaces(char *line, int i, int j, int count)
{
	char	*new;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	new = malloc(sizeof(char) * (ft_strlen(line) * 4 + 1));
	if (!new)
		return (NULL);
	while (line[i])
	{
		open_quotes(line[i], &sq, &dq);
		if (line[i] == '"' && !sq)
			space(new, line[i++], &count, &j);
		else if (line[i] == '\'' && !dq)
			space(new, line[i++], &count, &j);
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	free(line);
	return (new);
}

char	*spacer(char *line, int i, int j)
{
	char	*new;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	new = malloc(sizeof(char) * (ft_strlen(line) * 4 + 1));
	if (!new)
		return (NULL);
	while (line[i])
	{
		open_quotes(line[i], &sq, &dq);
		if (!sq && !dq && ft_strchr("|<>", line[i]) != NULL)
		{
			j = add_spaces(line, new, i, j);
			while (line[i] == line[i + 1])
				i ++;
			i ++;
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	new = add_quote_spaces(new, 0, 0, 1);
	return (new);
}
