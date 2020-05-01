/*
 * Artisti.h
 *
 *  Created on: 1 mag 2020
 *      Author: Simone
 */

#ifndef DATABASE_ARTISTI_H_
#define DATABASE_ARTISTI_H_
#include "../sys/Impostazioni.h"

typedef struct artisti {
	int id;
	char nome[MAX_CHAR];
	char cognome[MAX_CHAR];
	char nomearte[MAX_CHAR];
};


#endif /* DATABASE_ARTISTI_H_ */
