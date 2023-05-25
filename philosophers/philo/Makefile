# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 14:23:57 by nachab            #+#    #+#              #
#    Updated: 2023/05/25 18:32:03 by nachab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philosophers.c utils.c init_utils.c init.c args_parser.c threads.c exit_utils.c

FLAGS = -Wall -Werror -Wextra -fsanitize=thread

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@cc -o $@ $(FLAGS) $^
	@echo "\033[32m** CREATED THE EXECUTABLE **\033[9m"
	
%.o:%.c
	@cc $(FLAGS) $< -c
	
clean :
	@rm -f *.o 

fclean : clean
	@rm -f philo
	
re : fclean all

.PHONY =  all re clean fclean