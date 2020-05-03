/*
 * Utenti.h
 *
 *  Created on: 1 mag 2020
 *      Author: Simone
 */

#ifndef DATABASE_UTENTI_H_
#define DATABASE_UTENTI_H_
#include "../sys/Impostazioni.h"

typedef struct utenti {
	int id;
	char username[MAX_CHAR];
	char password[MAX_CHAR];
};

typedef struct preferiti {
	int idUtente;
	int idBrano;
};


#endif /* DATABASE_UTENTI_H_ */
