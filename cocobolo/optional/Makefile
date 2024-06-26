ROOT = ./
OBJSPATH = ../objs/
INCPATH = ../includes/


SRCS = $(wildcard $(ROOT)*.c)
OBJS = $(patsubst $(ROOT)%.c, $(OBJSPATH)%.o, $(SRCS))

CC = gcc
CFLAGS = $(foreach H,$(INCPATH),-I$(H)) -Wall -Wextra -Werror

all : $(OBJS)

$(OBJSPATH)%.o : $(ROOT)%.c Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

