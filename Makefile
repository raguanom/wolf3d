NAME = drawing

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lSDL2 -o $(NAME) -I include/ -I include/SDL2/ -L ~/lib

CFILES = init.c draw.c ray_casting.c parse_map.c move_and_rot.c events_handler.c main.c

$(NAME):
	gunzip -c SDL2-2.0.5.tar.gz | tar xf -
	cd SDL2-2.0.5; \
	mkdir build; \
	cd build; \
	../configure; \
	make
	mkdir -p ~/lib/
	cp SDL2-2.0.5/build/build/.libs/libSDL2-2.0.0.dylib ~/lib/
	ln -F -s ~/lib/libSDL2-2.0.0.dylib ~/lib/libSDL2.dylib
	mkdir -p include/SDL2
	cp SDL2-2.0.5/include/*.h include/SDL2/
	$(CC) $(CFILES) $(CFLAGS)
	
all: $(NAME)

fclean:
	rm -rf $(NAME)
	rm -rf include/SDL2
	rm -rf SDL2-2.0.5

re: fclean all

run:
	$(CC) $(CFILES) $(CFLAGS)
	./$(NAME)
