/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:47:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 16:04:17 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>

# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define MSG_ARGC	"./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile"
# define MSG_HDOC	"./pipex here_doc LIMITER cmd1 ... cmdn outfile"
# define MSG_CMD	"Command not found"
# define MSG_PERM	"Permission denied"
# define MSG_FLDR	"Is a directory"
# define MSG_FILE	"No such file or directory"
# define MSG_MEM	"Out of memory"
# define MSG_FORK	"Could not fork"
# define MSG_PIPE	"Could not pipe"

# define BOLD_RED	"\033[1;31m"
# define YELLOW		"\033[0;33m"
# define RESET		"\033[0m"

# define PERMS		0644

enum e_exitcodes
{
	NOERROR,
	ERR_FILE,
	ERR_SNTX,
	ERR_ARGC,
	ERR_PIPE,
	ERR_FORK,
	ERR_MEM,
	ERR_PERM = 126,
	ERR_CMD,
	ERR_SIG,
};

enum e_errors
{
	NOCMD,
	NOPERM,
	ISDIR,
	NOFILE,
	NOPATH
};

enum e_pipe
{
	RD_END,
	WR_END
};

typedef struct s_pipex
{
	int				argc;
	char			**argv;
	char			**envp;
	pid_t			*pids;
	int				exitcode;
	bool			error[5];
	int				pipe[2];
	int				inpipe;
	int				infile;
	int				outfile;
	int				index;
	int				start_pos;
	int				cmd_count;
	char			**paths;
	char			*temp;
	char			*exec;
	char			**cmd;
	bool			is_hdoc;
}	t_pipex;

void	init_pipex(int argc, char **argv, char **envp, t_pipex *ppx);
void	read_heredoc(t_pipex *ppx);
void	child_process(t_pipex *ppx);
void	wait_children(int status, t_pipex *ppx);
char	*executable_path(t_pipex *ppx);
void	close_all_fds(t_pipex *ppx);
void	self_destruct(t_pipex *ppx);
void	error_logger(char *msg1, char *msg2, char *msg3);
void	error_occured(int errcode, char *errmsg, t_pipex *ppx);

#endif
