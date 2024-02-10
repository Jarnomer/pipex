/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:06:13 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/10 22:36:43 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	receive_signal(t_pipex *ppx)
{
	if (WTERMSIG(ppx->wstat) == SIGINT
		|| WTERMSIG(ppx->wstat) == SIGQUIT)
		error_logger(MSG_SIGQUIT, "", "");
	else if (WTERMSIG(ppx->wstat) == SIGPIPE)
		error_logger(MSG_SIGPIPE, "", "");
	else if (WTERMSIG(ppx->wstat) == SIGCHLD)
		error_logger(MSG_SIGCHLD, "", "");
	else if (WTERMSIG(ppx->wstat) == SIGSEGV)
		error_logger(MSG_SIGSEGV, "", "");
	else if (WTERMSIG(ppx->wstat) == SIGBUS)
		error_logger(MSG_SIGBUS, "", "");
	else if (WTERMSIG(ppx->wstat) == SIGKILL)
		error_logger(MSG_SIGKILL, "", "");
	else if (WTERMSIG(ppx->wstat) == SIGABRT)
		error_logger(MSG_SIGABRT, "", "");
	else
		error_logger(MSG_SIGOTHR, "", "");
	return (ERR_SIG + WTERMSIG(ppx->wstat));
}

static int	update_exitcode(t_pipex *ppx)
{
	if (WIFSIGNALED(ppx->wstat) != 0)
		return (receive_signal(ppx));
	return (WEXITSTATUS(ppx->wstat));
}

void	wait_children(int status, t_pipex *ppx)
{
	if (status != NOERROR)
		ppx->idx--;
	while (ppx->idx >= 0)
	{
		waitpid(ppx->pids[ppx->idx], &ppx->wstat, 0);
		if (ppx->idx == ppx->cmds)
			ppx->ecode = update_exitcode(ppx);
		ppx->idx--;
	}
	if (ppx->ecode > 255)
		ppx->ecode = 255;
}
