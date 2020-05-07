/*
 * Ampere 0.1 rev. 2377 - 07.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef DATABASE_GENERI_H_
#define DATABASE_GENERI_H_
#include "../sys/Impostazioni.h"

struct generi {
	int id;
	char nome[MAX_CHAR];
};

struct tipoBrano {
	int idBrano;
	int idGenere;
};

#endif /* DATABASE_GENERI_H_ */
