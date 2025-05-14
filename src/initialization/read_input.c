/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:13:27 by iullibar          #+#    #+#             */
/*   Updated: 2025/04/25 12:50:41 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_quotes(char *input, int *sq, int *dq)
{
	int	i;

	i = 0;
	while (input[i])
	{
		open_quotes(input[i], sq, dq);
		i++;
	}
}

char	*read_input(const char *hostname)
{
	char	*input;
	char	*quote;
	char	*tmp;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	input = readline(hostname);
	if (!input)
		return (NULL);
	check_quotes(input, &sq, &dq);
	while (sq != 0 || dq != 0)
	{
		quote = readline("> ");
		if (!quote)
			return (free(input), NULL);
		check_quotes(quote, &sq, &dq);
		tmp = ft_strjoin(input, quote);
		free(input);
		free(quote);
		input = ft_strdup(tmp);
		free(tmp);
	}
	return (input);
}
