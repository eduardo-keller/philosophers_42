NAME = philo

SRCDIR = src
OBJDIR = obj
INCDIR = includes


CC = cc
CFLAGS = -Wall -Wextra -Werror -g3


VALGRIND = valgrind
TOT = --leak-check=full --show-leak-kinds=all

SRCS = main.c src/parse_args.c src/utils.c src/mutex.c src/philo_routine.c src/init.c

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))


GREEN = \033[0;32m
GREEN_B = \033[1;32m
RESET = \033[0m

all: $(OBJDIR) $(NAME)

val:
	$(VALGRIND) ./philo

val_tot:
	$(VALGRIND) $(TOT) ./philo


$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I $(INCDIR) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)Clean done!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Full clean done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
