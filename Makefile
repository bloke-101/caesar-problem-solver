SRCMODULES = cipher.c file_system_utils.c frequency_analyzer.c string_utils.c
OBJMODULES = $(SRCMODULES:%.c=bin/%.o)

CFLAGS = -Wall -std=c99 -pedantic

bin/%.o: src/%.c include/%.h
	$(CC) $(CFLAGS) -I include -c $< -o $@

caesar_problem_solver: src/main.c $(OBJMODULES)
	$(CC) $(CFLAGS) -I include $^ -o bin/$@
	
make_exec_dir: 
	mkdir -p bin

build: make_exec_dir caesar_problem_solver

clean:
	rm -rf bin/*
