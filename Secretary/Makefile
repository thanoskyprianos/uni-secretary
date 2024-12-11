CC = g++
FLAGS = -Werror -Wall -Wextra -pedantic -O3

CYAN = \033[1;96m
RED=\033[1;91m
RESET=\033[0m

secretary.o: secretary.cpp
	@$(CC) $(FLAGS) -c secretary.cpp

	@printf "$(CYAN)Created: $(RESET)secretary.o \n"

.PHONY: clean
clean:
	@rm *.o
	@printf "$(RED)Deleted: $(RESET)secretary.o \n"