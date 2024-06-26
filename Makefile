NAME = philo
COCOBOLO = ./cocobolo/
COCOBOLOLIB = $(COCOBOLO)cocobolo.a

SRCSPATH = ./src/
INCPATH = ./includes/ $(COCOBOLO)includes/
OBJSPATH = ./objs/

SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst $(SRCSPATH)%.c, $(OBJSPATH)%.o, $(SRCS))

END = \x1b[0m
GREEN = \x1b[33;1m
YELLOW = \x1b[32;1m
PURPLE = \x1b[35;1m
CYAN = \x1b[1;36m
BLUE = \x1b[1;34m
YELLOW = \x1b[1;33m
GREEN = \x1b[1;32m
RED = \x1b[1;31m

CC = gcc
DEBUG = -fsanitize=thread
WFLAGS = -Wall -Wextra -Werror
CFLAGS =  $(foreach H,$(INCPATH),-I$(H)) $(WFLAGS) #$(DEBUG)

all : $(OBJSPATH) $(NAME)

$(OBJSPATH) :
	@mkdir -p objs

$(NAME) : $(COCOBOLOLIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(COCOBOLOLIB)  -o $@
	@echo "$(GREEN) philo compiled! $(END)"

$(OBJSPATH)%.o : $(SRCSPATH)%.c Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

$(COCOBOLOLIB) :
	@make -C $(COCOBOLO) all

clean :
	@make -C $(COCOBOLO) clean
	@rm -rf $(OBJSPATH) $(OPTIONALOBJS)

fclean : clean
	@make -C $(COCOBOLO) fclean
	@rm -f $(NAME)

re : fclean all

push :

	make fclean
	git add .
	git commit -m "."
	git push origin master


.PHONY : all clean fclean re

