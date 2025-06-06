/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:06:19 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 18:23:45 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	log_command_error(t_pipex *ppx)
{
	if (ppx->error[NOCMD])
		error_logger(ppx->argv[ppx->start_pos + ppx->index], ": ", MSG_CMD);
	else if (ppx->error[ISDIR])
		error_logger(ppx->exec, ": ", MSG_FLDR);
	else if (ppx->error[NOPERM])
		error_logger(ppx->exec, ": ", MSG_PERM);
	else if (ppx->error[NOFILE])
		error_logger(*ppx->cmd, ": ", MSG_FILE);
	else
		error_logger(*ppx->cmd, ": ", MSG_CMD);
}

static void	check_executable(t_pipex *ppx)
{
	int	fd;

	fd = -1;
	fd = open(ppx->exec, O_DIRECTORY);
	if (fd != -1)
		ppx->error[ISDIR] = true;
	else if (access(ppx->exec, F_OK) == 0
		&& access(ppx->exec, X_OK) == -1)
		ppx->error[NOPERM] = true;
	else if (ft_strchr(ppx->exec, '/'))
		ppx->error[NOFILE] = true;
	if (fd != -1)
		close(fd);
}

static int	command_error(t_pipex *ppx)
{
	if (!ppx->cmd || !*ppx->cmd)
		ppx->error[NOCMD] = true;
	else if (ppx->exec)
		check_executable(ppx);
	log_command_error(ppx);
	if (ppx->error[ISDIR] || ppx->error[NOPERM])
		return (ERR_PERM);
	return (ERR_CMD);
}

void	error_logger(char *msg1, char *msg2, char *msg3)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(BOLD_RED, STDERR_FILENO);
	ft_putstr_fd(msg1, STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	ft_putstr_fd(YELLOW, STDERR_FILENO);
	ft_putendl_fd(msg3, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

void	error_occured(int errcode, char *errmsg, t_pipex *ppx)
{
	if (errmsg != NULL)
	{
		if (errcode == ERR_ARGC)
		{
			error_logger("Bad arguments", ": ", MSG_ARGC);
			error_logger("with here_doc", ": ", MSG_HDOC);
		}
		else if (errcode == ERR_CMD)
			errcode = command_error(ppx);
		else
			error_logger(errmsg, ": ", strerror(errno));
	}
	if (errcode == ERR_PIPE || errcode == ERR_FORK)
		wait_children(EXIT_FAILURE, ppx);
	if (!ppx)
		exit(EXIT_FAILURE);
	close_all_fds(ppx);
	self_destruct(ppx);
	exit(errcode);
}
