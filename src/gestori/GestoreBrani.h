/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREBRANI_H_
#define SRC_GESTORI_GESTOREBRANI_H_
#include "../database/Database.h"

database inserimentoBranoGuidato(database db);
struct brani creaBrano(database db, char titolo[], int id_album, int durata, int anno, int ascolti);
database inserireBrano(database db, struct brani brano, int id_artista, int id_genere);
void inserisciBranoSuFile(char id[], char titolo[], char durata[], char id_album[], char anno[], char ascolti[]);
database modificaBrano(database db);
database modificaSingoloBrano(database db, int modalita, int id);
database cancellaBrano(database db);
database cancellaSingoloBrano(database db, int id);
database cancellaAssociazioniBrano(database db, int id);
void apriTesto(int idBrano);
void apriTestoDaRicerca(database db);
void apriTestoDaID(database db);

#endif /* SRC_GESTORI_GESTOREBRANI_H_ */
