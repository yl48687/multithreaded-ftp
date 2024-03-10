# Multithreaded FTP
The project extends a basic FTP system to support concurrent command execution. Both the client and server are multithreaded, allowing multiple clients to connect simultaneously. Additionally, the project introduces a new "terminate" command for stopping long-running client commands.

## Design Overview
The project implements a multithreaded FTP client-server system using TCP sockets. The server program, `myftpserver.cpp`, accepts two command-line parameters: one for normal commands and another for terminate commands. It creates separate threads for handling client commands and termination requests. Each client connection spawns a new thread, ensuring proper concurrency control and consistency during command execution.

The client program, `myftp.cpp`, accepts three command-line parameters: server machine name, port number for normal commands, and port number for terminate commands. It interacts with the server to execute commands, displaying a prompt for user input and supporting sequential or concurrent command execution.

## Functionality
`myftpserver.cpp`:
- Listens for client connections on normal and terminate ports.
- Creates threads to handle client commands and termination requests concurrently.
- Parses and executes FTP commands, including the new "terminate" command.
- Ensures concurrency control and consistency during command execution.

`myftp.cpp`:
- Accepts server machine name and port numbers as command-line parameters.
- Executes FTP commands sequentially or concurrently based on user input.
- Communicates with the server to execute commands and handle termination requests.

## File Structure and Content
```
multithreaded-ftp/
├── client/
│   ├── Makefile
│   └── myftp.cpp
├── README.md
└── server/
    ├── Makefile
    └── myftpserver.cpp
```