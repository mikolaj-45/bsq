CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c io.c point.c algoritm.c
OBJ = $(SRC:.c=.o)
NAME = bsq

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(NAME)

test: all
	./$(NAME) testfile.txt

.PHONY: all clean test
