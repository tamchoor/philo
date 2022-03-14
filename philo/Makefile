NAME = philo

# BONUS_NAME = 

CC = cc
FLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
INCLUDES = -I$(HEADERS_DIRECTORY)

HEADER = philo.h
HEADERS_DIRECTORY = .



SOURCES = ft_atol.c ft_printf.c philo.c utils.c
# SOURCES_BONUS 

OBJECTS	=  $(SOURCES:%.c=%.o)
# OBJECTS_BONUS = $(SOURCES_BONUS:%.c=%.o) 

GREEN = \033[0;32m
RED = \033[0;31m
CROSS = \033[9m
MARK = \033[7m
RESET = \033[0m

.PHONY: all clean fclean re bonus

all: $(NAME)
# bonus: $(BONUS_NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n$(MARK) $(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(MARK) $(NAME): $(GREEN)$(NAME) was created$(RESET)"

# $(BONUS_NAME): $(LIBFT) $(OBJECTS_BONUS)
# 	$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS_BONUS) -o $(BONUS_NAME)
# 	@echo "\n $(MARK) $(BONUS_NAME): $(GREEN)object files were created$(RESET)"
# 	@echo " $(MARK) $(BONUS_NAME): $(GREEN)$(BONUS_NAME) was created$(RESET)"

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

# $(LIBFT): $(LIBFT_DIRECTORY)/*.c $(LIBFT_DIRECTORY)/*.h
# 	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
# 	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@rm -rf $(OBJECTS) $(OBJECTS_BONUS)
	@echo " $(NAME): $(RED) $(CROSS)object $(RED) files were deleted$(RESET)"

fclean: clean
	@rm -rf $(NAME) 
	@echo "$(CROSS) $(NAME) : $(RED)$(NAME) and $(BONUS_NAME) was deleted$(RESET)"

re: fclean all