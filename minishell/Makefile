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

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes
LDFLAGS = -lreadline

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = $(SRCS_DIR)/minishell.c \
	   $(SRCS_DIR)/init.c \
	   $(SRCS_DIR)/env.c \
	   $(SRCS_DIR)/process_input.c \
	   $(SRCS_DIR)/lexer/lexer.c \
	   $(SRCS_DIR)/lexer/lexer_utils.c \
	   $(SRCS_DIR)/parser/parser.c \
	   $(SRCS_DIR)/parser/parser_utils.c \
	   $(SRCS_DIR)/parser/expansion.c \
	   $(SRCS_DIR)/execution/execute.c \
	   $(SRCS_DIR)/execution/execute_utils.c \
	   $(SRCS_DIR)/execution/heredoc.c \
	   $(SRCS_DIR)/builtins/echo.c \
	   $(SRCS_DIR)/builtins/cd.c \
	   $(SRCS_DIR)/builtins/pwd.c \
	   $(SRCS_DIR)/builtins/export.c \
	   $(SRCS_DIR)/builtins/unset.c \
	   $(SRCS_DIR)/builtins/env.c \
	   $(SRCS_DIR)/builtins/exit.c \
	   $(SRCS_DIR)/utils/string_utils1.c \
	   $(SRCS_DIR)/utils/string_utils2.c \
	   $(SRCS_DIR)/utils/other_utils.c

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/lexer
	mkdir -p $(OBJS_DIR)/parser
	mkdir -p $(OBJS_DIR)/execution
	mkdir -p $(OBJS_DIR)/builtins
	mkdir -p $(OBJS_DIR)/utils

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re