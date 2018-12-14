# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/05/04 14:58:34 by quruiz       #+#   ##    ##    #+#        #
#    Updated: 2018/11/29 16:40:11 by quruiz      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = lem-in
LIBFT = libft/libft.a
HEADER = include/lem_in.h libft/libft/libft.h libft/get_next_line/get_next_line.h
FLAG = -Werror -Wall -Wextra -ggdb
TOOLS = src/tools/del_list.c src/tools/list.c src/tools/room.c
PARSE = src/parse/room.c src/parse/tube_ant.c
ALGO = src/algo/bfs.c src/algo/find_path.c src/algo/move_ant.c
OTHER = src/main.c src/destructor.c
SRC = $(TOOLS) $(PARSE) $(ALGO) $(OTHER)
OBJ = $(SRC:.c=.o)

all: lib $(NAME)

%.o: %.c $(HEADER)
		@gcc $(FLAG) -c $< -o $@

lib:
		@make -C libft

$(NAME): $(OBJ) $(LIBFT)
		@gcc $(FLAG) $(OBJ) $(LIBFT) -o $(NAME)

clean:
		@make clean -C libft/
		@rm -f $(OBJ)

fclean: clean
		@rm -rf lem-in.dSYM/
		@make fclean -C libft/
		@rm -f $(NAME)

git: fclean
		@read -ep "Files to commit: " file && git add $$file
		@read -p "Commit message: " msg && git commit -m "$$msg"
		@git push

re: fclean all
