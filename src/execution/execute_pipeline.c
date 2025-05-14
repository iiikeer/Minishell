/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:25:38 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/12 11:42:51 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	spawn_pipe_command(t_node *node, int infile_fd, int *pipe_fds, char **env)
{
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		dup2(infile_fd, STDIN_FILENO);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		execve(node->full_path, node->full_cmd, env);
		perror(node->full_cmd[0]);
		exit(126);
	}
	return (pid);
}

static int	spawn_last_pipeline_command(t_node *node, int infile_fd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		dup2(infile_fd, STDIN_FILENO);
		execve(node->full_path, node->full_cmd, env);
		perror(node->full_cmd[0]);
		exit(126);
	}
	return (pid);
}

void	execute_pipeline(t_mini *mini)
{
	int	i;
	int	infile_fd;
	int	pipe_fds[2];

	infile_fd = STDIN_FILENO;
	i = 0;
	while (mini->nodes[i + 1])
	{
		if (spawn_pipe_command(mini->nodes[i], infile_fd, pipe_fds, \
			mini->env) == -1)
			return ;
		close(pipe_fds[1]);
		if (infile_fd != STDIN_FILENO)
			close(infile_fd);
		infile_fd = pipe_fds[0];
		i++;
	}
	if (spawn_last_pipeline_command(mini->nodes[i], infile_fd, mini->env) == -1)
		return ;
	if (infile_fd != STDIN_FILENO)
		close(infile_fd);
	while (wait(&g_status) > 0)
		update_exit_status(mini);
}
