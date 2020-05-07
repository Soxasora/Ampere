/*
 * Ampere 0.1 rev. 2377 - 07.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_DATABASE_DATABASEUTILS_H_
#define SRC_DATABASE_DATABASEUTILS_H_

int contaNelDatabase(int modalita);
int trovaUltimoId(int modalita);
int ottieniPosDaID(int modalita, int id);
void backupDatabase();
void ripristinaDatabase();

#endif /* SRC_DATABASE_DATABASEUTILS_H_ */
