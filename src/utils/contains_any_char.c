/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:56:16 by elopez-u          #+#    #+#             */
/*   Updated: 2025/04/30 10:56:16 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	contains_any_char(char *s, char *c)
{
	if (!s || !c)
		return (0);
	while (*c)
	{
		if (ft_strchr(s, *c))
			return (1);
		c++;
	}
	return (0);
}
