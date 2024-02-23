NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -g3 -I./inc

SRCDIR = ./src
OBJDIR = ./obj

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

$(NAME) : $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all