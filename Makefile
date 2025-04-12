NAME = philo
NAME_BONUS = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I$(INCLUDES)

INCLUDES = includes

SOURCES = \
	utilities/misc.c \
	utilities/atoi.c \
	utilities/cleanup.c

SOURCES_MAN = \
	mandatory/sources/philo_routines.c \
	mandatory/sources/philo_sub_routines.c \
	mandatory/sources/philo_sub_routines2.c \
	mandatory/sources/monitoring_routine.c \
	mandatory/sources/initialisation.c \
	mandatory/philosophers.c

SOURCES_BONUS = \


OBJS = $(SOURCES:.c=.o)
OBJS_MAN = $(SOURCES_MAN:.c=.o)
OBJS_BON = $(SOURCES_BON:.c=.o)


$(NAME): $(OBJS) $(OBJS_MAN)
	@ $(CC) $(OBJS) $(OBJS_MAN) -o $(NAME)

$(NAME_BONUS): $(OBJS) $(OBJS_BON)
	@ $(CC) $(OBJS) $(OBJS_BON) -o $(NAME_BONUS)

%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

all: fclean $(NAME) $(MANDATORY)
	@ echo "G3t r34dy t0 th1nk (:"

bonus: fclean $(NAME_BONUS) $(BONUS)
	@ echo "G3t r34dy t0 b0nu5 th1nk (:"

clean:
	@ rm -rf $(OBJS)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
