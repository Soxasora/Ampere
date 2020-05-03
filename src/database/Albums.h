/*
 * Albums.h
 *
 *  Created on: 1 mag 2020
 *      Author: Simone
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
