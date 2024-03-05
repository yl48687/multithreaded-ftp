# Compiler
CC=g++

# Compiler flags
CFLAGS=-c -Wall

# Linker flags
LDFLAGS=-pthread

# Source files
CLIENT_SOURCE=myftp.cpp

# Object files
CLIENT_OBJECT=$(CLIENT_SOURCE:.cpp=.o)

# Executable
CLIENT_EXECUTABLE=myftp

all: $(CLIENT_EXECUTABLE)

$(CLIENT_EXECUTABLE): $(CLIENT_OBJECT)
	$(CC) $(LDFLAGS) $(CLIENT_OBJECT) -o $@

$(CLIENT_OBJECT): $(CLIENT_SOURCE)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(CLIENT_OBJECT) $(CLIENT_EXECUTABLE)