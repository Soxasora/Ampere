/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_DATABASE_DATABASEUTILS_H_
#define SRC_DATABASE_DATABASEUTILS_H_
#include "../database/Database.h"
/**
 *
 */
int contaNelDatabase(database db,int modalita);

/**
 *
 */
int trovaUltimoId(database db, int modalita);

/**
 *
 */
int ottieniPosDaID(database db, int modalita, int id);
/**
 *
 */
void backupDatabase();

/**
 *
 */
database ripristinaDatabase(database db);

#endif /* SRC_DATABASE_DATABASEUTILS_H_ */
