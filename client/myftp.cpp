#include <iostream>
#include <sys/socket.h>
#include <sstream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unordered_set>

using namespace std;

// Function to check if a command is valid
bool isValidCommand(const string& command) {
    static const unordered_set<string> validCommands = {"get", "put", "ls", "cd", "terminate", "delete", "mkdir", "pwd", "quit"};
    istringstream iss(command);
    string cmd;
    iss >> cmd;
    return validCommands.count(cmd) > 0;
} // isValidCommand

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <server_ip> <nport> <tport>" << endl;
        return 1;
    } // if
    
    // Extract command-line arguments
    string server_ip = argv[1];
    int nport = stoi(argv[2]);
    int tport = stoi(argv[3]);

    // Create client socket for normal commands
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating client socket.");
        return 1;
    } // if

    // Create client socket for termination commands
    int termSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (termSocket == -1) {
        perror("Error creating termination socket.");
        close(clientSocket);
        return 1;
    } // if

    // Initialize server address structures
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(nport);
    inet_pton(AF_INET, server_ip.c_str(), &(serverAddress.sin_addr));

    sockaddr_in termAddress{};
    termAddress.sin_family = AF_INET;
    termAddress.sin_port = htons(tport);
    inet_pton(AF_INET, server_ip.c_str(), &(termAddress.sin_addr));;

    // Connect to the server for normal commands
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to the server for normal commands.");
        close(clientSocket);
        close(termSocket);
        return 1;
    } // if

    // Connect to the server for termination commands
    if (connect(termSocket, (struct sockaddr*)&termAddress, sizeof(termAddress)) == -1) {
        perror("Error connecting to the server for termination commands.");
        close(clientSocket);
        close(termSocket);
        return 1;
    } // if

    // Start handling user commands
    while (true) {
        // Prompt user for command input
        cout << "myftp> ";
        string command;
        getline(cin, command);
        
        // Check if the command is valid
        if (!isValidCommand(command)) {
            cout << "Error: Invalid command. Try again." << endl;
            continue;
        } // if

        // Send the command to the server
        int bytesSent = send(clientSocket, command.c_str(), command.length(), 0);
        if (bytesSent == -1) {
            perror("Error sending command to server.");
            close(clientSocket);
            close(termSocket);
            return 1;
        } // int

        // Check if the user entered the quit command
        if (command == "quit") {
            close(clientSocket);
            close(termSocket);
            return 0;
        } // if
        
        // Receive response from the server
        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == -1) {
            perror("Error receiving response from server.");
            close(clientSocket);
            close(termSocket);
            return 1;
        } // if

        // Display response received from the server
        buffer[bytesReceived] = '\0';

        // Check if the command is "get"
        istringstream iss(command);
        string cmd;
        iss >> cmd;
        
        int commandID;

        if (cmd == "get") {
            char* commandIDString = strtok(buffer, "\n");
            char* fileContent = strtok(NULL, "");
            
            // Convert commandIDString to integer
            commandID = atoi(commandIDString);
            cout << "Received command ID: " << commandIDString << endl;
            cout << "Received command ID: " << commandID << endl;
        
            // Extract the file name from the command
            string fileName;
            iss >> fileName;
            
            // Open a new file to write the received content
            ofstream outputFile(fileName, ios::binary);
            if (!outputFile.is_open()) {
                cerr << "Error: Unable to create file " << fileName << " for writing." << endl;
                continue;
            } // if
            
            // Write the received content into the file, including the command ID
            outputFile.write(fileContent, strlen(fileContent));
            outputFile.close();
        } else {
            cout << buffer << endl;
        } // if
    } // while

    close(clientSocket);
    close(termSocket);
    return 0;
} // main