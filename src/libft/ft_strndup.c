/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:01:36 by iullibar          #+#    #+#             */
/*   Updated: 2025/03/31 13:03:56 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	dup = malloc((i + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		dup[i] = s[i];
		i ++;
	}
	dup[i] = '\0';
	return (dup);
}
