
# variaveis

CC = gcc
CFLAGS = -Wall -g -lm
OBJECT = spinning_cube.o
TARGET = spinning_cube

# main rule

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECT)

# rule to create the object files ".o"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# rule to clean object and program file "make clean"

clean:
	rm -f $(OBJECT) $(TARGET)
