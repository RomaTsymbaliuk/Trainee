#ifndef TYPE_H
#define TYPE_H

#include <string.h>
#include "menu_objs.h"

enum {TCP = 1, UDP, NTP, DNS};

enum {FILE_EXECUTE = 1, COMMAND_EXECUTE,FILE_UPLOAD};

enum {eth, wifi, lo};

struct server {
	int sockfd;
	int server_id;
	char cli_state[20];
	void *server_type;
	char interface[20];
	int port;
	int (*server_listen)();
	int (*server_bind)(int port);
	int (*server_accept)();
	int (*server_read)();
	int (*server_disconnect)();
	int (*server_init)();
	int (*server_write)(struct menu *input);
	int (*server_send)(struct menu *input);
	int (*server_upload)(struct menu *input);
};



#endif