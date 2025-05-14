/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:18:28 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/13 12:37:05 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	validate_redirections(char **tokens)
{
	int	i;
	int	len;

	i = 1;
	while (tokens[i] != NULL)
	{
		if (has_quotes(tokens[i]) == 0)
		{
			if (contains_any_char(tokens[i], "<>") == 1)
			{
				len = ft_strlen(tokens[i]);
				if (len > 2 || (!tokens[i - 1] && ft_strchr(tokens[i], '>')) \
															|| !tokens[i + 1])
					return (0);
				if (contains_any_char(tokens[i + 1], "<>") == 1 && \
												has_quotes(tokens[i + 1]) == 0)
					return (0);
			}
		}
		i ++;
	}
	return (1);
}
