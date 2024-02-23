NAME 	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP -g3 -I. -MF $(DPSDIR)/$*.d
CLIBS	= -lreadline

SRCDIR	= ./src
OBJDIR	= ./obj
DPSDIR	= ./deps

SRC 	= $(wildcard $(SRCDIR)/*.c)
OBJ 	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))


$(NAME): $(OBJDIR) $(OBJ) $(DPSDIR)
		$(CC) $(CFLAGS) $(CLIBS) $(OBJ) -o $(NAME)


$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(DPSDIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(DPSDIR)/%.d: ;

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DPSDIR):
	mkdir -p $(DPSDIR)

all: $(NAME)

clean:
	rm -rf $(OBJDIR) $(DPSDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re