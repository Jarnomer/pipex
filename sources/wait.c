/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:06:13 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/12 17:48:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	update_exitcode(int wstat)
{
	if (WIFSIGNALED(wstat) != 0)
		return (ERR_SIG + WTERMSIG(wstat));
	return (WEXITSTATUS(wstat));
}

void	wait_children(int status, t_pipex *ppx)
{
	int	wstat;

	if (status != NOERROR)
		ppx->index--;
	while (ppx->index >= 0)
	{
		waitpid(ppx->pids[ppx->index], &wstat, 0);
		if (ppx->index == ppx->cmd_count)
			ppx->exitcode = update_exitcode(wstat);
		ppx->index--;
	}
}
