NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP


INCDIR = ./includes
INC	=	$(addprefix -I,$(INCDIR))


SRCSDIR = ./srcs
OBJSDIR = ./objs
SRCS	=	$(addprefix $(SRCSDIR)/,*.c)
OBJS	=	$(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))
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

LDFLAGS = -L $(RL_LIBDIR) -I $(RL_INCDIR)/readline


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	$(CC) $(CFLAGS) -I $(RL_DIR) -c -o $@ $<

$(LIBFT):
		$(MAKE) -C $(LIBDIR)

-include $(DEPS)

clean:
		$(MAKE) fclean -C $(LIBDIR)
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
