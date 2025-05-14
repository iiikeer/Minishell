/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:15:40 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/08 13:15:57 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**set_cmd(char **tokens, int count, int i, int j)
{
	char	**full_cmd;

	while (tokens[i])
	{
		if (tokens[i][0] == '<' && tokens[i][0] == '>')
			i ++;
		else
			count ++;
		i++;
	}
	full_cmd = malloc(sizeof(char *) * (count + 1));
	if (!full_cmd)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			i ++;
		else
			full_cmd[j++] = ft_strdup(tokens[i]);
		i ++;
	}
	full_cmd[j] = NULL;
	return (full_cmd);
}
