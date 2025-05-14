/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:57:14 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/12 11:56:06 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status = 0;

void	mini_loop(t_mini *mini)
{
	while (1)
	{
		init_input(mini);
		create_nodes(mini);
		execution(mini);
		free_mini(mini);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	(void)argv;
	if (argc != 1)
	{
		write(2, "\033[31mError: Incorrect number of arguments\n\033[0m", 47);
		return (EXIT_FAILURE);
	}
	mini = malloc(sizeof(t_mini));
	if (!mini)
	{
		write(2, "\033[31mError: Memory allocation failed\n\033[0m", 42);
		return (EXIT_FAILURE);
	}
	print_minishell();
	init_mini(mini);
	mini->env = copy_env(env);
	handle_signals();
	mini_loop(mini);
	return (EXIT_SUCCESS);
}
