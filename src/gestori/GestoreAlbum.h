/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREALBUM_H_
#define SRC_GESTORI_GESTOREALBUM_H_
#include "../database/Database.h"

database inserimentoAlbumGuidato(database db);
database creaAlbumGuidato(database db, char titolo_album[]);
database creaAlbumSeNonEsiste(database db, char titolo_album[]);
struct albums creaAlbum(database db, char titolo[], int anno);
database inserireAlbum(database db, struct albums album);
void inserisciAlbumSuFile(char id[], char titolo[], char anno[]);
void inserisciCollezioneSuFile(char idalbum[], char idbrano[]);
int controlloEsistenzaAlbum(database db, char album[]);
database modificaAlbum(database db);
database modificaSingoloAlbum(database db, int modalita, int id);
database cancellaAlbum(database db);
database cancellaSingoloAlbum(database db, int id);

#endif /* SRC_GESTORI_GESTOREALBUM_H_ */
