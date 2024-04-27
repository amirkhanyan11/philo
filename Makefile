NAME = philo

SRCSPATH = ./src/
INCPATH = ./includes/

SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

CC = cc
DEBUG = -fsanitize=address
WFLAGS = -Wall -Wextra -Werror
CFLAGS =  $(foreach H,$(INCPATH),-I$(H)) #$(DEBUG) # $(WFLAGS)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  -o $@


$(SRCSPATH)%.o : $(SRCSPATH)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean :

	rm -f $(OBJS)

fclean : clean

	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

