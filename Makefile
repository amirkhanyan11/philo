NAME = philo
COCOBOLO = ./cocobolo/
COCOBOLOLIB = $(COCOBOLO)cocobolo.a

SRCSPATH = ./src/
INCPATH = ./includes/ $(COCOBOLO)includes/
OBJSPATH = ./objs/

SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst $(SRCSPATH)%.c, $(OBJSPATH)%.o, $(SRCS))


CC = gcc
DEBUG = #-fsanitize=thread
WFLAGS = -Wall -Wextra -Werror
CFLAGS =  $(foreach H,$(INCPATH),-I$(H)) $(DEBUG)  $(WFLAGS)

all : $(OBJSPATH) $(NAME)

$(OBJSPATH) :
	mkdir -p objs

$(NAME) : $(COCOBOLOLIB) $(OBJS)
	$(CC) $(CFLAGS) $(COCOBOLOLIB) $(OBJS) -o $@

$(OBJSPATH)%.o : $(SRCSPATH)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(COCOBOLOLIB) :
	make -C $(COCOBOLO) all

clean :
	make -C $(COCOBOLO) clean
	rm -rf $(OBJSPATH) $(OPTIONALOBJS)

fclean : clean
	make -C $(COCOBOLO) fclean
	rm -f $(NAME)

re : fclean all

push :

	make fclean
	git add .
	git commit -m "."
	git push origin master


.PHONY : all clean fclean re

