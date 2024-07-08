NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror  -g3 -fsanitize=thread #-fsanitize=address # #  #
SRCS = srcs/getters_setters.c  srcs/main.c  srcs/routine.c srcs/init_param.c srcs/utils.c srcs/time.c srcs/monitor.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

####./philo [nb_philos] [to_die] [to_eat] [to_sleep] -[nb_must_eat]-
test: all
	clear
	valgrind ./philo 5 300 100 100 2

test2: all
	clear
	./philo 200 410 200 200

testFile:
	@$(CC) $(CFLAGS) srcs/utils.c srcs/libft_utils.c srcs/routine.c srcs/errors.c test.c -o test
clean :
	@rm -f $(OBJS)
	@rm -f test

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
