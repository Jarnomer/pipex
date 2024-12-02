/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:55:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/11 16:34:50 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv, char **envp)
{
	t_pipex	ppx;

	if (argc < 5)
		error_occured(ERR_ARGC, MSG_ARGC, NULL);
	init_pipex(argc, argv, envp, &ppx);
	while (++ppx.index <= ppx.cmd_count)
		child_process(&ppx);
	close_all_fds(&ppx);
	wait_children(NOERROR, &ppx);
	self_destruct(&ppx);
	return (ppx.exitcode);
}
