/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:09:50 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/12 11:42:51 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_exit_status(t_mini *mini)
{
	(void)mini;
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
		g_status = 128 + WTERMSIG(g_status);
	else
		g_status = 1;
}
