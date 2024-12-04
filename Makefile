# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 15:32:20 by jmertane          #+#    #+#              #
#    Updated: 2024/02/15 11:04:37 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#    VARIABLES
# **************************************************************************** #

NAME = pipex

SOURCEDIR := sources
HEADERDIR := include
BUILDDIR  := build
BUILDLOG  := build.log

LIBFTDIR  := ./libft
LIBFTBIN  := libft.a

OUTFILE   := outf
TESTCASE  := ./$(NAME) "Makefile" cat cat 'wc -l' $(OUTFILE)

# **************************************************************************** #
#    COMMANDS
# **************************************************************************** #

RM          := rm -rf
SCREENCLEAR := printf "\033c"

# **************************************************************************** #
#    COMPILATION
# **************************************************************************** #

CC         := cc
CFLAGS     := -Wall -Werror -Wextra
CPPFLAGS   := -c -MMD -MP
DEBUGFLAGS := -g -fsanitize=address
MAKEFLAGS  += --no-print-directory -j4

# **************************************************************************** #
#    VALGRIND
# **************************************************************************** #

LEAKSLOG := leaks.log
VLGFLAGS := --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --track-fds=yes \
            --trace-children=yes \
            --log-file=$(LEAKSLOG) \
            --verbose \
            --quiet

# **************************************************************************** #
#    SOURCES
# **************************************************************************** #

SOURCES := main \
           init \
		   hdoc \
           child \
           wait \
           path \
           free \
           error

SOURCES := $(addsuffix .c, $(SOURCES))

OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:.c=.o))

INCS := $(addprefix -I, $(HEADERDIR) $(LIBFTDIR)/$(HEADERDIR))

DEPS := $(OBJECTS:.o=.d)

vpath %.c $(SOURCEDIR)

# **************************************************************************** #
#    RULES
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LIBFTDIR)/$(LIBFTBIN) -o $@
	printf "$(V)$(B)Binary:$(T)$(Y) $(NAME) $(T)\n"

$(OBJECTS): $(LIBFTDIR)/$(LIBFTBIN)

libft: $(LIBFTDIR)/$(LIBFTBIN)

$(LIBFTDIR)/$(LIBFTBIN): 
	@make -C $(LIBFTDIR) all

run: all
	$(SCREENCLEAR)
	$(TESTCASE)
	cat $(OUTFILE) && $(RM) $(OUTFILE)

re: fclean
	make all

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

nm:
ifneq ($(shell command -v norminette >/dev/null 2>&1 && echo 1 || echo 0), 1)
	@printf "$(R)$(B)Error: norminette: $(Y)command not found$(T)\n"; exit 1
endif
	$(foreach h, $(HEADERDIR), norminette -R CheckDefine $(h))
	$(foreach s, $(SOURCEDIR), norminette -R CheckForbiddenSourceHeader $(s))

leaks: all
ifneq ($(shell command -v valgrind >/dev/null 2>&1 && echo 1 || echo 0), 1)
	@printf "$(R)$(B)Error: valgrind: $(Y)command not found$(T)\n"; exit 1
endif
	valgrind $(VLGFLAGS) $(TESTCASE)
	$(RM) -rf $(OUTFILE)
	$(call report_cmd, $(LEAKSLOG))

define report_cmd
	$(SCREENCLEAR)
	cat $1 | tail -n +4 | cut --complement -d' ' -f1
endef

# **************************************************************************** #
#    BUILD
# **************************************************************************** #

define build_cmd
$1/%.o: %.c | $(BUILDDIR)
	if ! $(CC) $(CFLAGS) $(CPPFLAGS) $(INCS) $$< -o $$@ 2> $(BUILDLOG); then \
		printf "$(R)$(B)\nError: \
		$(V)Unable to create object file: \
		$(R)$(B)$$@$(Y)\n\n"; \
		sed '$$d' $(BUILDLOG); exit 1 ; \
	else \
		printf "$(C)$(B)Object: $(G)$$@ $(T)\n"; \
	fi
endef

# **************************************************************************** #
#    CLEAN
# **************************************************************************** #

clean:
	@make -C $(LIBFTDIR) fclean
	$(call delete_cmd, $(BUILDDIR), $(BUILDLOG), $(LEAKSLOG))

fclean: clean
	$(call delete_cmd, $(NAME))

define delete_cmd
	printf "$(R)$(B)Delete:$(T)$(Y)$1$2$3$4$5$(T)\n"
	$(RM) $1 $2 $3 $4 $5
endef

# **************************************************************************** #
#    COLORS
# **************************************************************************** #

T = \033[0m
B = \033[1m
G = \033[32m
V = \033[35m
C = \033[36m
Y = \033[33m
R = \033[31m

# **************************************************************************** #
#    UTILS
# **************************************************************************** #

-include $(DEPS)

$(BUILDDIR):
	mkdir -p $@

$(foreach build, $(BUILDDIR), $(eval $(call build_cmd, $(build))))

# **************************************************************************** #
#    PHONY
# **************************************************************************** #

.PHONY: all libft re
.PHONY: debug leaks run nm
.PHONY: clean fclean

.SILENT:
