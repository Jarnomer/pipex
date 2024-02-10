# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 10:37:44 by jmertane          #+#    #+#              #
#    Updated: 2024/02/08 17:26:53 by jmertane         ###   ########.fr        #
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

FILL		=	=================================================
BOLD		=	\033[1m
RESET		=	\033[0m
GREEN		=	\033[32m
VIOLET		=	\033[35m
CYAN		=	\033[36m
RED			=	\033[31m
YELLOW		=	\033[33m

all: $(NAME)

$(NAME): start $(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(OBJSDIR)/%.o: %.c | $(OBJSDIR) $(DEPSDIR)
	@if ! $(CC) $(CFLAGS) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		echo "$(RED)$(BOLD)\nMAKEFILE TERMINATED!\n$(FILL)$(RESET)\n"; \
		echo "$(VIOLET)Unable to create object file: $(RED)$(BOLD)$@$(RESET)\n"; \
		echo "$(RED)$(BOLD)ERROR>>>>>>>>>>>>>>>$(RESET)$(YELLOW)\n"; \
		sed '$$d' $(ERRORTXT); \
		echo "$(RED)$(BOLD)\n$(FILL)\nExiting...$(RESET)\n"; \
		exit 1; fi

start:
ifneq ("$(wildcard $(OBJSDIR)/*.o)","")
	@echo "\n$(GREEN)$(BOLD)$(NAME)$(RESET)$(VIOLET) is up to date!$(RESET)"
else
	@echo "\n$(VIOLET)Building $(GREEN)$(BOLD)$(NAME)$(RESET)$(VIOLET) binary...$(RESET)"
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
