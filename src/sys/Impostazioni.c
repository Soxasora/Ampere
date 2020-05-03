/*
 * Impostazioni.c
 *
 *  Created on: 2 mag 2020
 *      Author: Simone
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sys/Impostazioni.h"

// 0==Windows | 1==Linux | 2==macOS | 3==Altri Sistemi Operativi UNIX-based
int rivelaOS() {
	int os=0;

	#ifdef _WIN32
		os=0;
	#elif __linux__
		os=1;
	#elif __APPLE__
		os=2;
	#elif __unix__
		os=3;
	#endif

	return os;
}
