NAME = philo

SRCDIR = src
OBJDIR = obj
INCDIR = includes


CC = cc
CFLAGS = -Wall -Wextra -Werror -g3


VALGRIND = valgrind
TOT = --leak-check=full --show-leak-kinds=all

SRCS = main.c 

OBJS = $(SRCS:%.c=%.o)

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

$(NAME): $(addprefix $(OBJDIR)/, $(OBJS))
	@$(CC) $(CFLAGS) -I $(INCDIR) -o $(NAME) $(addprefix $(OBJDIR)/, $(OBJS))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)Clean done!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Full clean done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
