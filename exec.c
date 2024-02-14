/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:35:34 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 18:24:07 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_cmd(t_pipex *ppx)
{
	parse_argument(ppx->argv[ppx->stt + ppx->idx], ppx);
	ppx->exec = executable_path(ppx);
	if (!ppx->cmd || !*ppx->cmd || !ppx->exec
		|| execve(ppx->exec, ppx->cmd, ppx->envp) == -1)
		error_occured(ERR_CMD, MSG_CMD, ppx);
}

static void	replace_io(int input, int output, t_pipex *ppx)
{
	if (dup2(input, STDIN_FILENO) == -1
		|| (dup2(output, STDOUT_FILENO) == -1))
		error_occured(ERR_FILE, NULL, ppx);
}

static void	redirect_fds(t_pipex *ppx)
{
	if (!ppx->idx)
		replace_io(ppx->infile, ppx->pipe[WR_END], ppx);
	else if (ppx->idx != ppx->cmds)
		replace_io(ppx->pipeout, ppx->pipe[WR_END], ppx);
	else if (ppx->idx == ppx->cmds)
		replace_io(ppx->pipeout, ppx->outfile, ppx);
}

static void	prep_next_pipe(t_pipex *ppx)
{
	close(ppx->pipe[WR_END]);
	if (ppx->pipeout != -1)
		close(ppx->pipeout);
	ppx->pipeout = dup(ppx->pipe[RD_END]);
	close(ppx->pipe[RD_END]);
}

void	child_process(t_pipex *ppx)
{
	if (ppx->idx != ppx->cmds
		&& pipe(ppx->pipe) == -1)
		error_occured(ERR_PIPE, MSG_PIPE, ppx);
	ppx->pids[ppx->idx] = fork();
	if (ppx->pids[ppx->idx] == -1)
		error_occured(ERR_FORK, MSG_FORK, ppx);
	else if (ppx->pids[ppx->idx] != 0)
		prep_next_pipe(ppx);
	else if (ppx->pids[ppx->idx] == 0)
	{
		redirect_fds(ppx);
		close_all_fds(ppx);
		execute_cmd(ppx);
	}
}
