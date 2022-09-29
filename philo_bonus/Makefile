NAME = philo_bonus

CC = cc
FLAGS = -Wall -Werror -Wextra
FLAGS_CHECK = -Wall -Werror -Wextra 
INCLUDES = -I$(HEADERS_DIRECTORY)

HEADER = philo.h
HEADERS_DIRECTORY = .

SOURCES = ft_atol.c philo.c utils.c init_and_check.c  main.c  ft_itoa.c 

OBJECTS	=  $(SOURCES:%.c=%.o)

GREEN = \033[0;32m
RED = \033[0;31m
CROSS = \033[9m
MARK = \033[7m
RESET = \033[0m

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n$(MARK) $(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(MARK) $(NAME): $(GREEN)$(NAME) was created$(RESET)"

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS) $(OBJECTS_BONUS)
	@echo " $(NAME): $(RED) $(CROSS)object $(RED) files were deleted$(RESET)"

fclean: clean
	@rm -rf $(NAME) 
	@echo "$(CROSS) $(NAME) : $(RED)$(NAME) and $(BONUS_NAME) was deleted$(RESET)"

re: fclean all