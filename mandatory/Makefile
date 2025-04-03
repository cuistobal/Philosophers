NAME = philosophers

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -I$(INCLUDES)

INCLUDES = includes

SOURCES = \
	sources/routines/philosophers/philo_routines.c \
	sources/routines/philosophers/eating.c \
	sources/routines/philosophers/sleeping.c \
	sources/routines/philosophers/thinking.c \
	sources/routines/monitoring_routine.c \
	sources/initialisation.c \
	utilities/misc.c \
	utilities/atoi.c \
	utilities/cleanup.c \
	philosophers.c

OBJS = $(SOURCES:.c=.o)

$(NAME): $(OBJS)
	@ $(CC) $(OBJS) -o $(NAME)

%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
	@ echo "G3t r34dy t0 th1nk (:"

clean:
	@ rm -rf $(OBJS)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
