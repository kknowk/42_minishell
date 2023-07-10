NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INCDIR))

INCDIR = ./includes
INC	=	$(shell find $(INCDIR) -name "*.h" -type f | xargs)

SRCSDIR = ./srcs
OBJSDIR = ./objs
SRCS	=	$(shell find $(SRCDIR) -name "*.c" -type f | xargs)
OBJS	=	$(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

LIBFTDIR = ./libft
LIBFT	=	$(LIBFTDIR)/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
		$(MAKE) -C $(LIBDIR)

clean:
		$(MAKE) fclean -C $(LIBDIR)
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
