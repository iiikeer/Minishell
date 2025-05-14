/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:54:05 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/12 11:42:51 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_single_command(t_mini *mini, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		if (node->full_path == NULL || node->full_cmd == NULL)
		{
			printf("%s: command not found\n", node->full_cmd[0]);
			free_mini(mini);
			exit(127);
		}
		if (execve(node->full_path, node->full_cmd, mini->env) == -1)
		{
			printf("%s: command not found\n", node->full_cmd[0]);
			free_mini(mini);
			exit (127);
		}
	}
	else
	{
		waitpid(pid, &g_status, 0);
		update_exit_status(mini);
	}
}

void	execute_cmd(t_mini *mini, t_node *node)
{
	int		in_backup;
	int		out_backup;

	in_backup = dup(STDIN_FILENO);
	out_backup = dup(STDOUT_FILENO);
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			printf("Error with input file\n");
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			printf("Error with output file\n");
		close(node->outfile);
	}
	if (!is_builtin(node->full_cmd[0]))
		execute_single_command(mini, node);
	else
		execute_builtin(mini, node);
	dup2(in_backup, STDIN_FILENO);
	dup2(out_backup, STDOUT_FILENO);
	close(in_backup);
	close(out_backup);
}
