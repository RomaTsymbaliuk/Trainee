#include "menu_processor.h"

int main(int argc, char *argv[]) {
	struct cmd **c = process_user_input(argc, argv);
	run_user_cmd(c);
	return 1;
}
