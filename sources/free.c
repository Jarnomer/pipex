/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:58:43 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 15:55:06 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	close_all_fds(t_pipex *ppx)
{
	if (!ppx)
		return ;
	if (ppx->pipe[WR_END] != -1)
		close(ppx->pipe[WR_END]);
	if (ppx->pipe[RD_END] != -1)
		close(ppx->pipe[RD_END]);
	if (ppx->inpipe != -1)
		close(ppx->inpipe);
	if (ppx->infile != -1)
		close(ppx->infile);
	if (ppx->outfile != -1)
		close(ppx->outfile);
}

void	self_destruct(t_pipex *ppx)
{
	if (!ppx)
		return ;
	if (ppx->cmd != NULL)
		ft_free_double((void ***)&ppx->cmd);
	if (ppx->paths != NULL)
		ft_free_double((void ***)&ppx->paths);
	if (ppx->exec != NULL)
		ft_free_single((void **)&ppx->exec);
	if (ppx->temp != NULL)
		ft_free_single((void **)&ppx->temp);
	if (ppx->pids != NULL)
		ft_free_single((void **)&ppx->pids);
}
