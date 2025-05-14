/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:04:24 by iullibar          #+#    #+#             */
/*   Updated: 2025/03/21 08:54:11 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_nbrlen(int nbr)
{
	int		len;

	len = 0;
	if (nbr <= 0)
		len ++;
	while (nbr != 0)
	{
		nbr /= 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*num;
	int		len;

	len = ft_nbrlen(nbr);
	num = malloc(sizeof(char) * (len + 1));
	if (num == NULL)
		return (NULL);
	if (nbr < 0)
		num[0] = '-';
	num[len--] = '\0';
	if (nbr == 0)
		num[0] = '0';
	while (nbr != 0)
	{
		if ((nbr % 10) < 0)
			num[len] = ((nbr % 10) * -1) + 48;
		else
			num[len] = (nbr % 10) + 48;
		nbr = nbr / 10;
		len --;
	}
	return (num);
}
