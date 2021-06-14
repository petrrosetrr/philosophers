NAME	=	philo

SRCS	:=	$(shell find . -name '*.c')

HEAD	:=	$(shell find . -name '*.h')

GCC		= 	gcc -g -Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(GCC) $(OBJS) -o $(NAME)

clean:
			rm -rf $(OBJS)

$(OBJS):	$(HEAD)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

.c.o:
			$(GCC) -c $< -o $(<:.c=.o)