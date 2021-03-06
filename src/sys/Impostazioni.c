/*
 * UNIBA/Ampere 1.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sys/Impostazioni.h"

// 0==Windows | 1==Linux | 2==macOS | 3==Altri Sistemi Operativi UNIX-based
int rilevareOS() {
	int os=0;

	#ifdef _WIN32
		os=0;
	#elif __linux__
		os=1;
	#elif __APPLE__
		os=2;
	#elif __unix__ || __APPLE__
		os=3;
	#endif

	return os;
}
