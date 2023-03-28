#Problem Statement

Accept a port number from the user to bind a server using TCP/IP to that port. (4 marks) The server prints its IP address and port number after binding. (2 marks)

Accept the server's IP address and the port number at the client's end. (2 marks) The client connects to the server. (4 marks)

For every client connected, the server spawns a new thread. (4 marks) The client reads a string from the terminal and sends it to the server. (2 mark) The thread, serving the client, prints its thread ID and the received string. (4 marks) This continues until the user types the string "quit" at the client's end. (2 mark)

If a client disconnects, the server terminates the corresponding thread. (2 marks) You may assume that there can be, at the most, five clients in parallel. (2 marks)


#Mandatory instructions (50% marks deducted if not followed)

The server and client codes are in separate files.

Use script command to record the compilation of the code and the executions of both processes.

Submit the source code and recorded script in a zip file. The zip file should have the filename of the format <roll_no>_<assignment_3>.zip
