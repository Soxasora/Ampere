/*
 * Brani.h
 *
 *  Created on: 1 mag 2020
 *      Author: Simone
 */

#ifndef DATABASE_BRANI_H_
#define DATABASE_BRANI_H_
#include "../sys/Impostazioni.h"

typedef struct brani {
	int id;
	char titolo[MAX_CHAR];
	int durata;
	int album;
	int anno;
	char testo[MAX_CHAR];
	int ascolti;
	int voti;
};

#endif /* DATABASE_BRANI_H_ */
