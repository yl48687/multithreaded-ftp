# Compiler
CC=g++

# Compiler flags
CFLAGS=-c -Wall

# Linker flags
LDFLAGS=-pthread

# Source files
SERVER_SOURCE=myftpserver.cpp

# Object files
SERVER_OBJECT=$(SERVER_SOURCE:.cpp=.o)

# Executable
SERVER_EXECUTABLE=myftpserver

all: $(SERVER_EXECUTABLE)

$(SERVER_EXECUTABLE): $(SERVER_OBJECT)
	$(CC) $(LDFLAGS) $(SERVER_OBJECT) -o $@

$(SERVER_OBJECT): $(SERVER_SOURCE)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SERVER_OBJECT) $(SERVER_EXECUTABLE)