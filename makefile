NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INCDIR))

INCDIR = ./includes
INC	=	$(INCDIR)/$(addprefix -I,$(INCDIR))

SRCSDIR = ./srcs
OBJSDIR = ./objs
SRCS	=	$(addprefix $(SRCSDIR)/,$(SRCS))
OBJS	=	$(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

LIBFTDIR = ./libft
LIBFT	=	$(LIBFTDIR)/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
