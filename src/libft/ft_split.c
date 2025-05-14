/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:46:14 by iullibar          #+#    #+#             */
/*   Updated: 2025/04/25 13:06:41 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(char const *s, char c)
{
	int	in_word;
	int	count;
	int	i;

	in_word = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*ft_strcdup(const char *s, const char c)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dup[j] = s[j];
		j++;
	}
	dup[i] = '\0';
	return (dup);
}

static void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**split_string(char const *s, char c, char **split)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			split[i] = ft_strcdup(s, c);
			if (!split[i])
			{
				free_split(split);
				return (NULL);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**split;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	split = malloc(sizeof(char *) * (word_count + 1));
	if (!split)
		return (NULL);
	split = split_string(s, c, split);
	return (split);
}
