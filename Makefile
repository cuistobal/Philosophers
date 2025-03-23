NAME = philosophers

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -I$(INCLUDES)

INCLUDES = includes

SOURCES = \
	philosophers.c \
	utilities/atoi.c

OBJ = $(SOURCES:.c=.o)

NAME : $(OBJ)
	@ $(CC) $(OBJ) -o $(NAME)

%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)
	@ echo "G3t r34dy t0 th1nk (:"

re : fclean all

clean :
	@ rm -rf $(OBJ)

fclean : clean
	@ rm -rf $(NAME)

.PHONY: all, re, clean, fclean, bonus
