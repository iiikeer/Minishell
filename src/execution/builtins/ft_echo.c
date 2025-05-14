/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:57:00 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/12 11:42:51 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	check_n_option(char **tokens)
{
	int	i;

	if (!tokens[1] || tokens[1][0] != '-')
		return (0);
	i = 1;
	while (tokens[1][i] == 'n')
		i++;
	return (tokens[1][i] == '\0');
}

int	ft_echo(t_node *node)
{
	size_t	i;
	int		suppress_newline;

	i = 1;
	suppress_newline = 0;
	if (!node->full_cmd[1])
		return (printf("\n"), 0);
	if (node->full_cmd[i] && check_n_option(node->full_cmd))
	{
		suppress_newline = 1;
		i++;
	}
	if (node->full_cmd[i] && node->full_cmd[i][0] == '$' && \
					node->full_cmd[i][1] == '?' && node->full_cmd[i][2] == '\0')
		return (printf("%d\n", g_status), 0);
	while (node->full_cmd[i])
	{
		printf("%s", node->full_cmd[i]);
		if (node->full_cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!suppress_newline)
		printf("\n");
	return (0);
}
