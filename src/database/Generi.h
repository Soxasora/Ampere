/*
 * Generi.h
 *
 *  Created on: 1 mag 2020
 *      Author: Simone
 */

#ifndef DATABASE_GENERI_H_
#define DATABASE_GENERI_H_
#include "../sys/Impostazioni.h"

typedef struct generi {
	int id;
	char nome[MAX_CHAR];
};

typedef struct tipoBrano {
	int idBrano;
	int idGenere;
};

#endif /* DATABASE_GENERI_H_ */
