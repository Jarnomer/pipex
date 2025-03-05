/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/02 12:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	advance_token(char *cmd, t_parse *parser)
{
	int	i;

	i = 0;
	ft_bzero(parser, sizeof(t_parse));
	while (cmd[i] && !is_delimiter(cmd[i], parser))
		i += handle_meta(&cmd[i], parser);
	return (i);
}

static void	copy_token(char *dst, char *src, t_parse *parser)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	advance_parser(NULL, 0, 0, parser);
	while (src[i] && !is_delimiter(src[i], parser))
	{
		if (src[i] == '\\' && src[i + 1])
		{
			dst[j++] = src[i + 1];
			i += 2;
		}
		else if ((src[i] == '\'' || src[i] == '\"') && !parser->quoted)
			i += advance_parser(src, i, 1, parser);
		else if (parser->quoted && src[i] == parser->meta)
			i += advance_parser(NULL, 0, 1, parser);
		else
			dst[j++] = src[i++];
	}
}

static int	token_length(char *cmd, t_parse *parser)
{
	int	i;

	i = 0;
	advance_parser(NULL, 0, 0, parser);
	while (cmd[i] && !is_delimiter(cmd[i], parser))
	{
		if (cmd[i] == '\\' && cmd[i + 1])
		{
			parser->len++;
			i += 2;
		}
		else if ((cmd[i] == '\'' || cmd[i] == '\"') && !parser->quoted)
			i += advance_parser(cmd, i, 1, parser);
		else if (parser->quoted && cmd[i] == parser->meta)
			i += advance_parser(NULL, 0, 1, parser);
		else
			parser->len = ++i;
	}
	return (parser->len);
}

char	*extract_token(char **cmd_ptr, t_parse *parser)
{
	char	*token;
	char	*cmd;
	int		len;

	cmd = *cmd_ptr;
	while (*cmd && is_delimiter(*cmd, parser))
		cmd++;
	len = token_length(cmd, parser);
	token = ft_calloc(len + 1, sizeof(char));
	if (!token)
		return (NULL);
	copy_token(token, cmd, parser);
	*cmd_ptr = cmd + advance_token(cmd, parser);
	return (token);
}
