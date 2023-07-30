NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
CFLAGS += -g -fsanitize=address

# sanitizeが有る無しで挙動が変わります。。謎

INCDIR = ./includes
INC	=	$(addprefix -I,$(INCDIR)) -I$(RL_INCDIR)

# INC 変数に-I$(RL_INCDIR)を追加
# readline.h ヘッダーファイルを見つけるためにコンパイラが
# 使用する検索パスに readline の include ディレクトリが追加されます。
# 最新版の関数rl_replace_lineが使えるようになります。

SRCSDIR = ./srcs
OBJSDIR = ./objs
SRCS	=	$(wildcard $(SRCSDIR)/*.c $(SRCSDIR)/*/*.c)
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
