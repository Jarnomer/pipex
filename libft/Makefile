# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 10:37:44 by jmertane          #+#    #+#              #
#    Updated: 2024/02/15 11:15:33 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	libft.a
ERRORTXT 	= 	error.txt

CC 			= 	cc
RM 			= 	rm -rf
AR 			= 	ar -rcs
CFLAGS 		= 	-Wall -Werror -Wextra

SRCS 		= 	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_memset.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_strlen.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_atoi.c \
				ft_itoa.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_printf.c \
				ft_printf_fmt.c \
				get_next_line.c \
				get_next_line_utils.c

OBJSDIR 	= 	build
DEPSDIR 	= 	.deps
DEPS 		= 	$(SRCS:%.c=$(DEPSDIR)/%.d)
OBJS 		= 	$(SRCS:%.c=$(OBJSDIR)/%.o)
DEPFLAGS 	=	-c -MT $@ -MMD -MP -MF $(DEPSDIR)/$*.d

F		=	=================================================
B		=	\033[1m		# bold
T		=	\033[0m		# reset
G		=	\033[32m	# green
V		=	\033[35m	# violet
C		=	\033[36m	# cyan
R		=	\033[31m	# red
Y		=	\033[33m	# yellow

all: $(NAME)

$(NAME): start $(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(OBJSDIR)/%.o: %.c | $(OBJSDIR) $(DEPSDIR)
	@if ! $(CC) $(CFLAGS) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		echo "$(R)$(B)\nMAKEFILE TERMINATED!\n$(FILL)$(T)\n"; \
		echo "$(V)Unable to create object file: $(R)$(B)$@$(T)\n"; \
		echo "$(Y)$(B)ERROR\t>>>>>>>>$(T)$(Y)\n"; sed '$$d' $(ERRORTXT); \
		echo "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; fi

start:
ifneq ("$(wildcard $(OBJSDIR)/*.o)","")
	@echo "\n$(G)$(B)$(NAME)$(T)$(V) is up to date!$(T)"
else
	@echo "\n$(V)Building $(G)$(B)$(NAME)$(T)$(V) binary...$(T)"
endif

clean:
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRORTXT)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

$(OBJSDIR) $(DEPSDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

.PHONY: all start clean fclean re
