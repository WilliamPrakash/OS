#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "system_call_interface.h"

/* purpose of this file is to safeguard system cakks */

void access_system_calls(int id, char call[10]) {
	// validate passed in id
	bool hasAccess = false;
	if(id == 21) {
		hasAccess = true;
	}

	// read call
	if(strcmp(call, "print") == 0 && hasAccess) {
		printf("print method accessed successfully by id: %d\n", id);
	}
	
}
