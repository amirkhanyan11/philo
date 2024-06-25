NAME = cocobolo.a
ROOT = ./
OBJSPATH = ./objs/
SRCSPATH = ./src/
INCPATH = ./includes/

SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst $(SRCSPATH)%.c, $(OBJSPATH)%.o, $(SRCS))

OPTIONAL = ./optional/

CC = gcc
CFLAGS = $(foreach H,$(INCPATH),-I$(H)) -Wall -Wextra -Werror

all : $(OBJSPATH) $(NAME)

$(OBJSPATH) :
	mkdir -p objs

$(NAME) : $(OBJS)
	make -C $(OPTIONAL) all
	ar -rcs $(NAME) $(OBJSPATH)*.o

$(OBJSPATH)%.o : $(SRCSPATH)%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJSPATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

push :
	make fclean
	git add .
	git commit -m "updated cocobolo library"
	git push origin master

.PHONY : all clean fclean re push

