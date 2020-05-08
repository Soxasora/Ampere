/*
 * Ampere 0.1 rev. 2432 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
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
