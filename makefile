CC = g++
FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

a.exe: stack.o proc.o runner.o
	$(CC) stack.o proc.o runner.o -o a.exe $(FLAGS)

stack.o: stack.cpp stack.h
	$(CC) -c stack.cpp -o stack.o $(FLAGS)

proc.o: proc.cpp proc.h
	$(CC) -c proc.cpp -o proc.o $(FLAGS)

runner.o: runner.cpp runner.h
	$(CC) -c runner.cpp -o runner.o $(FLAGS)
