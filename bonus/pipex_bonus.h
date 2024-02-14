/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:47:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 16:04:03 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"

# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define MSG_ARGC		"./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile"
# define MSG_HDOC		"./pipex here_doc LIMITER cmd1 ... cmdn outfile"
# define MSG_CMD		"command not found"
# define MSG_PERM		"Permission denied"
# define MSG_FLDR		"Is a directory"
# define MSG_FILE		"No such file or directory"
# define MSG_MEM		"Could not allocate memory"
# define MSG_FORK		"Could not fork"
# define MSG_PIPE		"Could not pipe"

# define MSG_SIGQUIT	"Interrupted"
# define MSG_SIGPIPE	"Pipe broken"
# define MSG_SIGCHLD	"Child terminated"
# define MSG_SIGSEGV	"Segmentation fault"
# define MSG_SIGBUS		"Bus error"
# define MSG_SIGKILL	"Killed"
# define MSG_SIGABRT	"Abort"
# define MSG_SIGTERM	"Terminated"
# define MSG_SIGOTHR	"Unhandled signal"

# define BOLD_RED		"\033[1;31m"
# define YELLOW			"\033[0;33m"
# define RESET			"\033[0m"

# define PERMISSIONS	0644

enum e_errcodes
{
	NOERROR,
	ERR_FILE,
	ERR_ARGC,
	ERR_PIPE,
	ERR_FORK,
	ERR_MEM,
	ERR_PERM = 126,
	ERR_CMD,
	ERR_SIG,
};

enum e_pipe
{
	RD_END,
	WR_END
};

typedef struct s_parse
{
	char			*content;
	struct s_parse	*next;
}	t_parse;

typedef struct s_pipex
{
	int				argc;
	char			**argv;
	char			**envp;
	pid_t			*pids;
	int				ecode;
	int				wstat;
	int				error[5];
	int				pipe[2];
	int				pipeout;
	int				infile;
	int				outfile;
	int				idx;
	int				stt;
	int				cmds;
	bool			hdoc;
	int				len;
	char			*lmtr;
	char			**cmd;
	char			**paths;
	char			*exec;
	char			*temp;
	struct s_parse	*args;
}	t_pipex;

void	init_pipex(int argc, char **argv, char **envp, t_pipex *ppx);
void	read_heredoc(t_pipex *ppx);
void	child_process(t_pipex *ppx);
void	wait_children(int status, t_pipex *ppx);
void	parse_argument(char *argv, t_pipex *ppx);
void	join_arguments(char c, t_pipex *ppx);
char	*executable_path(t_pipex *ppx);
void	close_all_fds(t_pipex *ppx);
void	self_destruct(t_pipex *ppx);
void	error_logger(char *msg1, char *msg2, char *msg3);
void	error_occured(int errcode, char *errmsg, t_pipex *ppx);

#endif
