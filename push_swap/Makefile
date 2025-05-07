# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claude            #+#  +:+       #+#         #+#    #+#              #
#                                                   #+#    #+#                 #
#    Created: 2025/05/07 12:00:00 by claude           #+#    #+#              #
#    Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = $(SRCS_DIR)/push_swap.c \
	   $(SRCS_DIR)/stack_utils.c \
	   $(SRCS_DIR)/operations.c \
	   $(SRCS_DIR)/operations2.c \
	   $(SRCS_DIR)/operations3.c \
	   $(SRCS_DIR)/parser.c \
	   $(SRCS_DIR)/sorting.c \
	   $(SRCS_DIR)/utils.c

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re