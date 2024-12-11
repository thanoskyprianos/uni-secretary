CC = g++
FLAGS = -Werror -Wall -Wextra -pedantic -O3

CYAN = \033[1;96m
RED=\033[1;91m
RESET=\033[0m

person.o: person.cpp
	@$(CC) $(FLAGS) -c person.cpp

	@printf "$(CYAN)Created: $(RESET)person.o \n"

.PHONY: clean
clean:
	@rm  *.o

	@printf "$(RED)Deleted: $(RESET)person.o \n"