/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:11:00 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/12 08:54:17 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	is_numeric_string(const char *str)
{
	size_t	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_mini *mini, t_node *node, int exit_code)
{
	if (node->full_cmd[1] != NULL)
	{
		if (!is_numeric_string(node->full_cmd[1]))
		{
			printf("minishell: ");
			printf("exit: %s: numeric argument required\n", node->full_cmd[1]);
			exit(255);
		}
		exit_code = ft_atol(node->full_cmd[1]);
		if (exit_code < 0 || exit_code > 255)
			exit_code = exit_code % 256;
		if (node->full_cmd[2])
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (1);
		}
	}
	free_array(mini->env);
	free_mini(mini);
	rl_clear_history();
	write(1, "exit\n", 6);
	exit(exit_code);
	return (0);
}
