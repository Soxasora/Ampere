/*
 * Ampere 0.0.1 rev. 1000 - 02.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/XX/blob/master/LICENSE
 */

#ifndef DATABASE_ALBUMS_H_
#define DATABASE_ALBUMS_H_
#include "../sys/Impostazioni.h"

typedef struct albums {
	int id;
	char titolo[MAX_CHAR];
	int anno;
};

typedef struct collezione {
	int idAlbum;
	int idBrano;
};

#endif /* DATABASE_ALBUMS_H_ */
