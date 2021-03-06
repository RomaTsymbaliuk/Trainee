#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <arpa/inet.h>
#include "Server.h"
#include "menu_objs.h"

static struct menu menus_objs[] = {
	{"exit", EXIT_HELP, shell_exit, NULL, EXIT_ID, 0, 0, FG},
	{"start_server", START_SERVER_HELP, server_connect, NULL, START_SERVER_ID, 1, 1, FG},
	{"help", SHELL_HELP, shell_help, NULL, HELP_ID, 0, 0, FG},
	{"server_disconect", SERVER_DISCONNECT_HELP, server_disconnect, NULL, DISCONNECT_ID, 0, 0, FG},
	{"clear", CLEAR_HELP, shell_clear, NULL, CLEAR_ID, 0, 0, FG},
	{"exploit", EXPLOIT_HELP, server_exploit, NULL, EXPLOIT_ID, 0, 20, FG},
	{"send_file", SEND_HELP, server_send, NULL, SEND_ID, 2, 2, FG},
	{"upload_file", UPLOAD_HELP, server_upload, NULL, UPLOAD_ID, 1, 1, FG},
	{NULL, NULL, NULL, NULL, 0, 0, 0, 0}
};

struct server *server_object;

int main(int argc, char *argv[])
{
	int choice;
	int c;
	int size;
	int option_index;
	const char *opt;

	static struct option long_options[] = 
	{
		{"tcp", no_argument, 0, 't'},
		{"udp", no_argument, 0, 'u'},
		{"ntp", no_argument, 0, 'n'},
		{"dns", no_argument, 0, 'd'},
		{"help", no_argument, 0, 'h'},
		{"ip", required_argument, 0, 'i'},
		{0, 0, 0, 0}
	};

	while(1) {

		option_index = 0;
		c = getopt_long(argc, argv, "i:tundh", long_options, &option_index);
		if (c == -1) {
			break;
		}

		switch(c) {
		case 't':
			printf("working with tcp server\n");
			server_register(TCP);
			break;
		case 'i':
			if (optarg){
				if (server_object) {
					printf("interface %s choosen strlen(optarg) : %d\n", optarg, strlen(optarg));
					strncpy(server_object->interface, optarg, strlen(optarg) > 20 ? 20 : strlen(optarg));
				} else {
					printf("First specify server type! Then specify ip");
					return ERR_OPTION;
				}
			} else {
				printf("No IP specified! Abort\n");
			}
			break;
		case 'u':
			server_register(UDP);
			break;
		case 'n':
			break;
		case 'd':
			break;
		case 'h':
			printf(SERVER_HELP);
			return ERR_OPTION;
		case '?':
		default:
			printf(SERVER_HELP);
			printf("\n\nNo options specified. Abort\n\n");
			return ERR_OPTION;
		}
	}

	shell_init();
	if (shell_menu_initializer(menus_objs, sizeof(menus_objs)/sizeof(struct menu)) != SUCCESS) {
		return ERR_MENU;
	}

	return shell_loop();

}
