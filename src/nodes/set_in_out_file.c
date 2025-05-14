/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_out_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:24:28 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/12 12:14:19 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	fill_here_doc(char *limit, int *in_fd)
{
	char	*str;
	int		fd;

	fd = open(".\vtemp\th", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		fd = STDIN_FILENO;
	while (1)
	{
		str = readline(">");
		if (!str)
		{
			printf("warning: here-document delimited by");
			printf(" end-of-file (wanted `%s')\n", limit);
			break ;
		}
		if (ft_strcmp(str, limit) == 0)
			break ;
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		free(str);
	}
	free(str);
	close(fd);
	*in_fd = open(".\vtemp\th", O_RDONLY);
}

static int	in_case(char **tok, int *in_fd, int i)
{
	if (!ft_strcmp(tok[i - 1], "<"))
	{
		if (*in_fd != STDIN_FILENO && *in_fd != -1)
			close(*in_fd);
		*in_fd = open(tok[i], O_RDONLY);
		if (*in_fd == -1)
		{
			*in_fd = STDIN_FILENO;
			return (0);
		}
	}
	else
		fill_here_doc(tok[i], in_fd);
	return (1);
}

static int	out_case(char **tok, int *out_fd, int i)
{
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	if (!ft_strcmp(tok[i - 1], ">"))
		*out_fd = open(tok[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (!ft_strcmp(tok[i - 1], ">>"))
		*out_fd = open(tok[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*out_fd == -1)
		return (0);
	return (1);
}

int	set_in_out_file(t_node *node, char **tok, int in_fd, int out_fd)
{
	int	i;

	i = 0;
	while (tok[i] != NULL)
	{
		if ((!ft_strcmp(tok[i], ">") || !ft_strcmp(tok[i], ">>")) && tok[i + 1])
		{
			if (out_case(tok, &out_fd, ++i) == 0)
				return (0);
		}
		else if ((!ft_strcmp(tok[i], "<") \
									|| !ft_strcmp(tok[i], "<<")) && tok[i + 1])
		{
			if (in_case(tok, &in_fd, ++i) == 0)
				return (0);
		}
		i ++;
	}
	node->infile = in_fd;
	node->outfile = out_fd;
	return (1);
}
