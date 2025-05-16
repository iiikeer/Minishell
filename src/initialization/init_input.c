/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:56:32 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/16 09:26:39 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_input(t_mini *mini)
{
	int		i;
	char	*line;
	char	*input;

	i = 0;
	line = read_input(hostname());
	if (line == NULL)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		mini_loop(mini);
	add_history(line);
	mini->input = ft_strdup(&line[i]);
	input = spacer(&line[i], 0, 0);
	free(line);
	tokenizer(mini, input);
	free(input);
	expand_tokens(mini);
	validate_pipes_redir(mini);
	quotes_remover(mini->tokens);
}
