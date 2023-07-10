NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INCDIR))

INCDIR = ./includes
INC	=	$(INCDIR)/philo.h

SRCDIR = ./srcs
SRCS	=	$(addprefix -I,$(SRCDIR))
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
