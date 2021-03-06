#ifndef ERRORS_H
#define ERRORS_H

enum {SUCCESS, WAIT_CONDITION, MEMORY_ALLOCATION_ERROR, FILE_NOT_EXISTS_ERROR, PARSING_INPUT_ERROR, 
	  ERR_LISTEN, ERR_ACCEPT, ERR_UNKNOWN, ERR_CHOICE, ERR_BIND, ERR_WRITE, ERR_FORK, ERR_COMMAND,
	  ERR_CREATE_SOCKET, ERR_CONNECT, ERR_TIMEOUT, ERR_SEND,
	  ERR_OPTION, ERR_READ, ERR_PARSE, ERR_INIT, ERR_MENU, ERR_DISCONNECT, ERR_EXPLOIT, ERR_UPLOAD};

int user_error(int err); 

#endif /* ERRORS_H */