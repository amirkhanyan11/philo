NAME = philo

SRCSPATH = ./src/
INCPATH = ./includes/
OBJSPATH = ./objs/

SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst $(SRCSPATH)%.c, $(OBJSPATH)%.o, $(SRCS))

CC = cc
DEBUG = -fsanitize=address
WFLAGS = -Wall -Wextra -Werror
CFLAGS =  $(foreach H,$(INCPATH),-I$(H)) $(DEBUG)  $(WFLAGS)

all : $(NAME)

$(OBJSPATH) :
	mkdir -p objs

$(NAME) : $(OBJSPATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJSPATH)%.o : $(SRCSPATH)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJSPATH)

fclean : clean

	rm -f $(NAME)

re : fclean all

sync :

	make fclean
	git add .
	git commit -m "."
	git push origin master


.PHONY : all clean fclean re

