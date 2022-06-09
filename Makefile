SRC =		$(wildcard *.c)
OBJ =		$(SRC:.c=.o)
DEBUG =		false
CFLAGS =	-W -Wall -Wextra -Werror -I./include
ifeq ($(DEBUG),true)
	CFLAGS += -g3 -ggdb
endif
LDFLAGS =	-lcsfml-window -lcsfml-graphics -lcsfml-system -lcsfml-audio -lm
TARGET =	game


all: $(TARGET)
$(TARGET): $(OBJ)
	gcc -o $(TARGET) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all
