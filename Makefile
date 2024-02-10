# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 15:32:20 by jmertane          #+#    #+#              #
#    Updated: 2024/02/10 23:06:19 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
BONUSBIN	=	pipex
DEBUGBIN	=	pipex
BNSSUFFIX	=	_bonus
BONUSDIR	=	bonus
LIBFTDIR	=	libft
LIBFTBIN	=	libft.a
ERRORTXT	=	error.txt
BONUSFLG	=	.bonus
DEBUGFLG	=	.debug

RM			=	rm -rf
AR			=	ar -rcs
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g
SCREENCLR	=	@printf "\033c"
SLEEP		=	@sleep .25

FILES		:=	pipex \
				init \
				exec \
				wait \
				path \
				free \
				error

FILES_BNS	:=	hdoc

SRCS		:=	$(addsuffix .c, $(FILES))
SRCS_BNS	:=	$(addsuffix $(BNSSUFFIX).c, $(FILES) $(FILES_BNS))
SRCS_BNS	:=	$(addprefix $(BONUSDIR)/, $(SRCS_BNS))
SRCS_DEBUG	:=	$(SRCS)

OBJSDIR		=	build
DEPSDIR		=	.deps
OBJSDIR_BNS	=	$(DEPSDIR)/$(BONUSDIR)
DEPSDIR_BNS	=	$(OBJSDIR)/$(BONUSDIR)
DEPS		=	$(SRCS:%.c=$(DEPSDIR)/%.d)
OBJS		=	$(SRCS:%.c=$(OBJSDIR)/%.o)
OBJS_BNS	=	$(SRCS_BNS:%.c=$(OBJSDIR)/%.o)
OBJS_DEBUG	=	$(SRCS_DEBUG:%.c=$(OBJSDIR)/%.o)
DEPFLAGS	=	-c -MT $@ -MMD -MP -MF $(DEPSDIR)/$*.d
DEBUGFLAGS	=	-g -fsanitize=address,undefined,integer \
				-fdiagnostics-color=always -fansi-escape-codes
NORMC		=	norminette -R CheckForbiddenSourceHeader
NORMH		=	norminette -R CheckDefine

F		=	=================================================
B		=	\033[1m		# bold
T		=	\033[0m		# reset
G		=	\033[32m	# green
V		=	\033[35m	# violet
C		=	\033[36m	# cyan
R		=	\033[31m	# red
Y		=	\033[33m	# yellow

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) $^ $(LIBFTDIR)/$(LIBFTBIN) -o $@
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n"
	$(SLEEP)
	@echo "$(V)Compiled $(G)$(SUCCESS)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$(NAME)$(T)\n"

$(OBJSDIR)/%.o: %.c | $(OBJSDIR) $(DEPSDIR) $(OBJSDIR_BNS) $(DEPSDIR_BNS)
	@if ! $(CC) $(CFLAGS) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		echo "$(R)$(B)\nMAKEFILE TERMINATED!\n$(F)$(T)\n"; \
		echo "$(V)Unable to create object file: $(R)$(B)$@$(T)\n"; \
		echo "$(R)$(B)ERROR\t>>>>>>>>$(T)$(Y)\n"; \
		sed '$$d' $(ERRORTXT); \
		echo "$(R)$(B)\n$(F)\nExiting...$(T)\n"; \
		exit 1; fi
	@if [ $(SUCCESS) ]; then \
		$(eval SUCCESS=$(shell echo $$(($(SUCCESS)+1)))) \
		echo "$(T)$(V) $<$(T)\t$(C)>>>>>>>>\t$(G)$(B)$@$(T)"; else \
		echo "$(C)$(B)MAKE START!$(T)\n$(G)$(B)$(F)$(T)\n"; \
		echo "$(T)$(V) $<$(T)\t$(C)>>>>>>>>\t$(G)$(B)$@$(T)"; fi

bonus: $(BONUSFLG)

$(BONUSFLG): $(OBJS_BNS)
	@make -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) $^ $(LIBFTDIR)/$(LIBFTBIN) -o $(BONUSBIN)
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n"
	$(SLEEP)
	@echo "$(V)Compiled $(G)$(SUCCESS)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags $(G)$(CFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$(BONUSBIN)$(T)\n"
	@touch $(BONUSFLG)

debug: $(DEBUGFLG)

$(DEBUGFLG): $(OBJS_DEBUG)
	@make -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) $^ $(LIBFTDIR)/$(LIBFTBIN) -o $(DEBUGBIN)
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n"
	$(SLEEP)
	@echo "$(V)Compiled $(G)$(SUCCESS)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags $(G)$(CFLAGS) $(DEBUGFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$(DEBUGBIN)$(T)\n"
	@touch $(DEBUGFLG)

clean:
	$(SCREENCLR)
	@echo "$(C)$(B)\nCLEAN START!\n$(G)$(F)$(T)\n"
	@echo "$(V)Removing object and dependency file(s) for $(G)$(B)$(LIBFTBIN)$(T)"
	@make --quiet -C $(LIBFTDIR) clean
	@echo "\n$(V)Removing object and dependency file(s) for $(G)$(B)$(NAME)$(T)\n"
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRORTXT) $(BONUSFLG) $(DEBUGFLG)
	@echo "$(G)$(B)$(F)$(C)\nFINISHED!$(T)\n"
	$(SLEEP)

fclean: clean
	@echo "$(C)$(B)\nFCLEAN START!\n$(G)$(F)$(T)\n"
	@echo "$(V)Removing all binary file(s) for $(G)$(B)$(LIBFTBIN)$(T)\n"
	@echo "$(V)Removing all binary file(s) for $(G)$(B)$(NAME)$(T)"
	@$(RM) $(NAME) $(BONUSBIN) $(DEBUGBIN) $(LIBFTDIR)/$(LIBFTBIN)
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)"
	$(SLEEP)

re: fclean all

reb: fclean bonus

nm:
	@$(NORMC) $(SRCS) $(SRCS_BNS)
	@$(NORMH) $(NAME).h $(BONUSDIR)/$(NAME)$(BNSSUFFIX).h

$(OBJSDIR) $(DEPSDIR) $(OBJSDIR_BNS) $(DEPSDIR_BNS):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

.PHONY: all bonus debug clean fclean re reb nm
