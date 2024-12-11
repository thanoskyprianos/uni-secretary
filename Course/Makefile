CC = g++
FLAGS = -Werror -Wall -Wextra -pedantic -O3

CYAN = \033[1;96m
RED=\033[1;91m
RESET=\033[0m

course.o: course.cpp
	@$(CC) $(FLAGS) -c course.cpp

	@printf "$(CYAN)Created: $(RESET)course.o \n"

.PHONY: clean
clean:
	@rm *.o
	@printf "$(RED)Deleted: $(RESET)course.o \n"