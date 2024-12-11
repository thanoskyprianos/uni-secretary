CC = g++
FLAGS = -Werror -Wall -Wextra -pedantic -O3

CYAN = \033[1;96m
RED = \033[1;91m
RESET = \033[0m

util.o: util.cpp util.h
	@$(CC) $(FLAGS) -c util.cpp

	@printf "$(CYAN)Created: $(RESET)util.o \n"

.PHONY: clean
clean:
	@rm -f *.o

	@rm -f main *.o
	@printf "$(RED)Deleted: $(RESET)util.o \n"