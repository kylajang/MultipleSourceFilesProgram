CC := g++
CFLAGS := -Wall -pedantic -g --std=c++17 -I.

# My Variables
	PART1_EXE_NAME := lab12.bin
	PART1_EXE_PATH := ./$(PART1_EXE_NAME)
	INPUT_FILE := in.txt
	OUTPUT_FILE := out.txt

# Targets
default:	lab12

lab12:	$(PART1_EXE_PATH)
	@echo "Building $@"
	$(PART1_EXE_PATH) $(INPUT_FILE) $(OUTPUT_FILE)

$(PART1_EXE_PATH):	main professor-lib
	@echo "Compiling $@"
	$(CC) $(CFLAGS) main.o professor_lib.o -o $@ \
		&& chmod +x $@

main:
	g++ $(CFLAGS) -c main.cpp -o main.o

professor-lib:
	g++ $(CFLAGS) -c professor_lib.cpp -o professor_lib.o

clean:
	rm $(PART1_EXE_PATH) *.o
