/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:30:19 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/16 10:03:48 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error_tok(t_mini *mini)
{
	free(mini->input);
	mini_loop(mini);
}

void	ft_error(t_mini *mini)
{
	free_mini(mini);
	mini_loop(mini);
}
