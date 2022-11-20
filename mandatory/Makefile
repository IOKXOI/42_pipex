NAME=pipex
CC=gcc
CFLAGS=-Wall -Werror -Wextra -MMD -g3
SRCDIR= srcs/
OBJSDIR=./objs/
BUILD = build
INCLUDES =./includes
LIBFT = ./libft

SRC_PARSING=$(addprefix parsing/, \
					paths_parsing.c \
					check.c)

SRC_CHAIN_LIST=$(addprefix chain_list/, \
				create_list.c)
				
SRC_EXEC=$(addprefix exec/, \
			exec.c \
			exec2.c)

SRC_FREE=$(addprefix free/, \
			error.c \
			free.c)

BONUS=$(addprefix bonus/, \
			heredoc.c)

SRC_BONUS=$(addprefix $(SRCDIR), \
			$(BONUS))
		
SRCS=$(addprefix $(SRCDIR), \
		$(SRC_PARSING) \
		$(SRC_CHAIN_LIST) \
		$(SRC_EXEC) \
		$(SRC_FREE) \
		pipex.c)

################################################################################
#                                     OBJECTS                                  #
################################################################################

OBJS := $(SRCS:%.c=$(BUILD)/%.o)
OBJ_BONUS := $(SRC_BONUS:%.c=$(BUILD)/%.o)

################################################################################
#                                     RULES                                    #
################################################################################

all: $(NAME)

-include:$(DEPS)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT) all --quiet
	$(CC) $(OBJS) -I $(INCLUDES) -L $(LIBFT) -lft -o $@

$(BUILD)/%.o: %.c ./includes/*.h
	@mkdir -p '$(@D)'
	$(CC) $(CFLAGS) -I $(INCLUDES) -L $(LIBFT) -lft -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) fclean
	rm -rf $(BUILD)

bonus: ${OBJ} ${OBJ_BONUS}
	$(MAKE) -C $(LIBFT) all --quiet
	$(CC) $(OBJS) $(OBJ_BONUS) -I $(INCLUDES) -L $(LIBFT) -lft -o $@

fclean: clean
	rm -f $(NAME)

re: fclean
	make

.PHONY: all clean fclean re bonus