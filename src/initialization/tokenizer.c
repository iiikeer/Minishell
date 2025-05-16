/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:17:52 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/16 10:02:06 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char	*token(char *line, int sq, int dq, int reset)
{
	static int	i;
	char		*str;
	int			j;

	j = 0;
	if (reset == 1)
		i = 0;
	while (ft_isspace(line[i]) == 1)
		i++;
	if (line[i] == '\0')
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(&line[i]) + 1));
	if (str == NULL)
	{
		write(2, "Error: Memory allocation failed for token\n", 42);
		return (NULL);
	}
	while ((line[i] != ' ' || sq == 1 || dq == 1) && line[i] != '\0')
	{
		open_quotes(line[i], &sq, &dq);
		str[j++] = line[i++];
	}
	str[j] = '\0';
	return (str);
}

static int	count_tokens(char *line)
{
	int	count;
	int	sq;
	int	dq;
	int	i;

	count = 0;
	sq = 0;
	dq = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' || line[i] == '\'')
			open_quotes(line[i], &sq, &dq);
		else if (ft_isspace(line[i]) == 1 && sq == 0 && dq == 0)
			count++;
		i++;
	}
	if (line[i - 1] != ' ' && line[i - 1] != '\0')
		count++;
	return (count);
}

void	tokenizer(t_mini *mini, char *line)
{
	char	**toks;
	int		reset;
	int		sq;
	int		dq;
	int		i;

	if (!line)
		ft_error_tok(mini);
	toks = malloc(sizeof(char *) * (count_tokens(line) + 1));
	if (!toks)
		return ;
	reset = 1;
	sq = 0;
	dq = 0;
	i = 0;
	while (1)
	{
		toks[i] = token(line, sq, dq, reset);
		reset = 0;
		if (toks[i] == NULL || toks[i][0] == '\0')
			break ;
		i++;
	}
	toks[i] = NULL;
	mini->tokens = toks;
}
