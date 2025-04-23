SRCMODULES = cipher.c file_system_utils.c frequency_analyzer.c string_utils.c
OBJMODULES = $(SRCMODULES:%.c=bin/%.o)

CFLAGS = -Wall -std=c99 -pedantic

bin/%.o: src/%.c include/%.h
	$(CC) $(CFLAGS) -I include -c $< -o $@

caesar_problem_solver: src/main.c $(OBJMODULES)
	$(CC) $(CFLAGS) -I include $^ -o bin/$@.elf
	
build: caesar_problem_solver

clean:
	rm -f bin/*
