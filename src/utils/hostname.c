/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:13:11 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/07 13:13:21 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	build_hostname(char *name, char *user, char *cwd, char *home)
{
	ft_strcpy(name, user);
	ft_strcat(name, "@minishell:");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		ft_strcat(name, "~");
		ft_strcat(name, cwd + ft_strlen(home));
	}
	else
		ft_strcat(name, cwd);
	ft_strcat(name, "$ ");
}

char	*hostname(void)
{
	static char	*name;
	char		*user;
	char		*home;
	char		cwd[1024];
	size_t		size;

	if (name)
		free(name);
	name = NULL;
	user = getenv("USER");
	home = getenv("HOME");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("Error getting current working directory"), NULL);
	size = ft_strlen(user) + ft_strlen("minishell") + ft_strlen(cwd) + 4;
	if (name == NULL)
	{
		name = malloc(size);
		if (name == NULL)
			return (perror("Error allocating memory for hostname"), NULL);
	}
	build_hostname(name, user, cwd, home);
	return (name);
}
