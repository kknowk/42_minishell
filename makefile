NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
# CFLAGS += -g -fsanitize=address

# sanitizeが有る無しで挙動が変わります。。謎

INCDIR = ./includes
INC	=	$(addprefix -I,$(INCDIR)) -I$(RL_INCDIR)

# INC 変数に-I$(RL_INCDIR)を追加
# readline.h ヘッダーファイルを見つけるためにコンパイラが
# 使用する検索パスに readline の include ディレクトリが追加されます。
# 最新版の関数rl_replace_lineが使えるようになります。

SRCSDIR = ./srcs
OBJSDIR = ./objs
SRCS	=	$(SRCSDIR)/builtins/cd.c \
			$(SRCSDIR)/builtins/create_env_vars.c \
			$(SRCSDIR)/builtins/echo.c \
			$(SRCSDIR)/builtins/env.c \
			$(SRCSDIR)/builtins/exit.c \
			$(SRCSDIR)/builtins/export.c \
			$(SRCSDIR)/builtins/export_utiles.c \
			$(SRCSDIR)/builtins/export_utiles_2.c \
			$(SRCSDIR)/builtins/pwd.c \
			$(SRCSDIR)/builtins/unset.c \
			$(SRCSDIR)/builtins/utiles.c \
			$(SRCSDIR)/builtins/utiles2.c \
			$(SRCSDIR)/builtins/utility_comand.c \
			$(SRCSDIR)/exec/builtins.c \
			$(SRCSDIR)/exec/execution.c \
			$(SRCSDIR)/exec/execute_command.c \
			$(SRCSDIR)/exec/pipe.c \
			$(SRCSDIR)/exec/redirect.c \
			$(SRCSDIR)/exec/expansion.c \
			$(SRCSDIR)/expansion/expansion.c \
			$(SRCSDIR)/expansion/handle_dollar.c \
			$(SRCSDIR)/expansion/handle_quotation.c \
			$(SRCSDIR)/expansion/helper_handle_dollar.c \
			$(SRCSDIR)/expansion/helper_handle_dquote.c \
			$(SRCSDIR)/expansion/helper_handle_quotation.c \
			$(SRCSDIR)/lexer/lexer.c \
			$(SRCSDIR)/lexer/token.c \
			$(SRCSDIR)/lexer/utils.c \
			$(SRCSDIR)/main.c \
			$(SRCSDIR)/minishell.c \
			$(SRCSDIR)/parser/parser.c \
			$(SRCSDIR)/parser/redirect.c \
			$(SRCSDIR)/parser/debug_parser.c \
			$(SRCSDIR)/lexer/debug_lexer.c \
			$(SRCSDIR)/signal.c

OBJS	=	$(patsubst $(SRCSDIR)/%.c,$(OBJSDIR)/%.o,$(SRCS))
DEPS	=	$(OBJS:.o=.d)


LIBFTDIR = ./libft
LIBFT	=	$(LIBFTDIR)/libft.a

UNAME = $(shell uname)

RL_NAME = readline
ifeq ($(UNAME),Darwin)
	RL_DIR = $(shell brew --prefix readline)
	RL_LIBDIR = $(addprefix $(RL_DIR)/,lib)
	RL_INCDIR = $(addprefix $(RL_DIR)/,include)
endif

LDFLAGS = -L $(LIBFTDIR) -lft -L $(RL_LIBDIR) -l $(RL_NAME)


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(LIBFT):
		$(MAKE) -C $(LIBFTDIR)

-include $(DEPS)

clean:
		$(MAKE) fclean -C $(LIBFTDIR)
		$(RM) $(OBJS) $(DEPS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
