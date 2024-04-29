# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 17:12:44 by jrocha-v          #+#    #+#              #
#    Updated: 2024/04/29 19:16:11 by jrocha-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

RESET	= \033[0m
BOLD	= \033[1m
FAINT	= \033[2m
ITALIC	= \033[3m
ULINE	= \033[4m
SBLINK	= \033[5m
FBLINK	= \033[6m
REVCOL	= \033[7m
HIDDEN	= \033[8m
CROSS	= \033[9m
BLACK   = \033[1;30m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
PURPLE  = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m

SRCS_DIR		= src

OBJS_DIR		= objs

INCLUDES		= includes

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
TH_FLAGS		= -lpthread #-fsanitize=thread
RM				= rm -rf

SRCS			= 	philo_main.c \
					philo_input.c \
					philo_start.c \
					philo_setup.c \
					philo_monitor.c \
					philo_actions.c \
					philo_handlers.c \
					philo_get_set.c \
					philo_utils.c \
					philo_errors.c

# Substitute .c with .o 
OBJS			= $(SRCS:%.c=$(OBJS_DIR)/%.o)

.SILENT:

#default target
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(TH_FLAGS) $(OBJS) -o $(NAME)
	#@echo "$(GREEN)./philo executable is ready!$(RESET)"

#create .o fies
# $< first prerequisite aka .c; $@ output/target file aka .o
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@

#remove .o files
clean:
	$(RM) $(OBJS_DIR)
	@echo "$(RED)Object files have been deleted!$(RESET)"

fclean: clean
	$(RM) $(NAME)

#reset environment - remove everything and recompile
re: fclean
	$(MAKE) all

#targets declared as .PHONY will force the command even if there is a subdirectory or file with it's name
.PHONY: all clean fclean re
