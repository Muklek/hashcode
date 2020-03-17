CC = g++

ROOT = .
MAIN_DIR = src
OUTPUT = $(ROOT)/output
MODEL_OUTPUT = $(ROOT)/model-output

_DEPS = readfile.hpp, writefile.hpp, booksorter.hpp
DEPS = $(patsubst %,$(MAIN_DIR)/%,$(_DEPS))

_OBJ = readfile.o writefile.o booksorter.o init.o
OBJ = $(patsubst %,$(MAIN_DIR)/%,$(_OBJ))


%.o: $(DEPS)
	$(CC) -c $^

init: $(OBJ)
	$(CC) -o $@ $^
	mkdir -p $(MAIN_DIR)/bin
	mv $(MAIN_DIR)/*.o $(MAIN_DIR)/bin/


.PHONY: clean
clean: $(OUTPUT) $(MODEL_OUTPUT) init
	rm $(MAIN_DIR)/bin/*.o && rm init && cp $(MODEL_OUTPUT)/*.txt $(OUTPUT) -r

