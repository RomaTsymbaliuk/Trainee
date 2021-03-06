#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Client.h"


int main(int argc, char *argv[])
{
	int choice;
	struct client *cli;
	int c;
	int size;
	int option_index;
	int port;

	static struct option long_options[] = 
	{
		{"tcp", required_argument, 0, 't'},
		{"udp", required_argument, 0, 'u'},
		{"ntp", required_argument, 0, 'n'},
		{"dns", required_argument, 0, 'd'},
		{"help", required_argument, 0, 'h'},
		{"ip", required_argument, 0, 'i'},
		{0, 0, 0, 0}
	};

	while(1) {
		option_index = 0;
		c = getopt_long(argc, argv, "p:", long_options, &option_index);
		if (c == -1) {
			break;
		}
		switch(c) {
		case 't':
			if (optarg) {
				cli = &tcp_obj;
				port = atoi(optarg);
				if (port < MIN_PORT || port > MAX_PORT) {
					printf("Port doesn`t match the limits\n");
					return ERR_OPTION;
				}
			} else {
				printf("No Port specified!\n");
				return ERR_OPTION;
			}
			break;
		case 'i':
			if (optarg && cli) {
				printf("Interface choosen %s\n", optarg);
				strncpy(cli->interface, optarg, strlen(optarg) > 20 ? 20 : strlen(optarg));
			} else {
				printf("Specify client type first and then ip address");
				return ERR_OPTION;
			}
			break;
		case 'u':
			if (optarg) {
				cli = &udp_obj;
				port = atoi(optarg);
				if (port < MIN_PORT || port > MAX_PORT) {
					printf("Port doesn`t match the limits\n");
					return ERR_OPTION;
				}
			} else {
				printf("No Port specified\n");
				return ERR_OPTION;
			}
			break;
		case 'n':
			break;
		case 'd':
			break;
		case 'h':
			printf(HELP);
			return ERR_OPTION;
		case '?':
		default:
			printf("\n\nNo options specified. Abort\n\n");
			printf(HELP);
			return ERR_OPTION;
		}
	}

	if (cli->client_connect(cli, port) != SUCCESS) {
		printf("Connect failed. Try again\n");
		sleep(2);
		return ERR_CONNECT;
	}

	while(1) {
		if (cli->client_receive(cli) != SUCCESS) {
			printf("Read error\n");
			return ERR_READ;
		}
	}


	close(cli->sockfd);

	return SUCCESS;
}