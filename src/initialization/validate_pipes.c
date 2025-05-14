/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:59:11 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/08 13:45:50 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	validate_pipes(char **tokens)
{
	int	i;
	int	len;

	i = 1;
	while (tokens[i] != NULL)
	{
		if (has_quotes(tokens[i]) == 0)
		{
			if (ft_strchr(tokens[i], '|') != NULL)
			{
				len = ft_strlen(tokens[i]);
				if (len > 1 || !tokens[i - 1] || !tokens[i + 1])
					return (0);
				if (contains_any_char(tokens[i + 1], "<>") == 1 && \
												has_quotes(tokens[i + 1]) == 0)
					return (0);
				if (contains_any_char(tokens[i - 1], "<>") == 1 && \
												has_quotes(tokens[i - 1]) == 0)
					return (0);
			}
		}
		i ++;
	}
	return (1);
}
