CC = g++
FLAGS = -Werror -Wall -Wextra -pedantic -O3

CYAN = \033[1;96m
RED=\033[1;91m
RESET=\033[0m

semester.o: semester.cpp
	@$(CC) $(FLAGS) -c semester.cpp

	@printf "$(CYAN)Created: $(RESET)semester.o \n"

.PHONY: clean
clean:
	@rm *.o
	@printf "$(RED)Deleted: $(RESET)semester.o \n"