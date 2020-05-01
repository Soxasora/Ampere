/*
 * Playlists.h
 *
 *  Created on: 1 mag 2020
 *      Author: Simone
 */

#ifndef DATABASE_PLAYLISTS_H_
#define DATABASE_PLAYLISTS_H_
#include "../sys/Impostazioni.h"

typedef struct playlists {
	int id;
	int idUtente;
	char nome[MAX_CHAR];
	char descrizione[MAX_CHAR];
};

#endif /* DATABASE_PLAYLISTS_H_ */
