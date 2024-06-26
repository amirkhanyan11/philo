NAME = cocobolo.a
ROOT = ./
OBJSPATH = ./objs/
SRCSPATH = ./src/
INCPATH = ./includes/

END = \x1b[0m
GREEN = \x1b[33;1m
YELLOW = \x1b[32;1m
PURPLE = \x1b[35;1m
CYAN = \x1b[1;36m
BLUE = \x1b[1;34m
YELLOW = \x1b[1;33m
GREEN = \x1b[1;32m
RED = \x1b[1;31m

SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst $(SRCSPATH)%.c, $(OBJSPATH)%.o, $(SRCS))

OPTIONAL = ./optional/

CC = gcc
CFLAGS = $(foreach H,$(INCPATH),-I$(H)) -Wall -Wextra -Werror

all : $(OBJSPATH) $(NAME)

$(OBJSPATH) :
	@mkdir -p objs
	@echo "$(GREEN) cocobolo compiling... $(END)"

$(NAME) : $(OBJS)
	@make -C $(OPTIONAL) all
	@ar -rcs $(NAME) $(OBJSPATH)*.o
	@echo "$(YELLOW) cocobolo compiled! $(END)"

$(OBJSPATH)%.o : $(SRCSPATH)%.c Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJSPATH)

fclean : clean
	@rm -f $(NAME)

re : fclean all

push :
	make fclean
	git add .
	git commit -m "updated cocobolo library"
	git push origin master

.PHONY : all clean fclean re push

