CC = g++
OBJS = Person/person.o Secretary/secretary.o Util/util.o Course/course.o Semester/semester.o
FLAGS = -Werror -Wall -Wextra -pedantic -O3
MAKE = make -s --no-print-directory

CYAN = \033[1;96m
RED = \033[1;91m
GREEN = \033[0;92m
RESET = \033[0m

main: main.o $(OBJS)
	@$(CC) $(FLAGS) -o main main.o $(OBJS)

	@printf "$(CYAN)Created: $(RESET)main \n\n"
	@printf "$(GREEN)To run the program execute: $(RESET)./main <students-file> <professors-file> <courses-file> [studying-years] [ects-required-to-graduate]\n"

help:
	@printf "$(GREEN) make $(RESET)|| $(GREEN)make main $(RESET): $(CYAN)Compile secretary program. \n"
	@printf "$(GREEN) make clean $(RESET): $(CYAN)Clean object files and execuatables.$(RESET) \n"

main.o: main.cpp
	@$(CC) $(FLAGS) -c main.cpp

	@printf "$(CYAN)Created: $(RESET)main.o \n"

Person/person.o: Person/person.cpp
	@$(MAKE) -C Person person.o

Secretary/secretary.o: Secretary/secretary.cpp
	@$(MAKE) -C Secretary secretary.o

Util/util.o: Util/util.cpp Util/util.h
	@$(MAKE) -C Util util.o

Course/course.o: Course/course.cpp
	@$(MAKE) -C Course course.o

Semester/semester.o: Semester/semester.cpp
	@$(MAKE) -C Semester semester.o

.PHONY: clean
clean:
	@rm -f main *.o
	@printf "$(RED)Deleted: $(RESET)main, main.o \n"

	@$(MAKE) -C Person clean
	@$(MAKE) -C Secretary clean
	@$(MAKE) -C Util clean
	@$(MAKE) -C Course clean
	@$(MAKE) -C Semester clean