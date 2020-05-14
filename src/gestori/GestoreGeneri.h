/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREGENERI_H_
#define GESTORI_GESTOREGENERI_H_
#include "../database/Database.h"

database inserimentoGenereGuidato(database db);
database creaGenereGuidato(database db, char nome[]);
database creaGenereSeNonEsiste(database db, char nome[]);
struct generi creaGenere(database db, char nome[]);
database inserireGenere(database db, struct generi genere);
void inserisciGenereSuFile(char id[], char nome[]);
void inserisciTipiBraniSuFile(char idbrano[], char idgenere[]);
int controlloEsistenzaGenere(database db, char genere[]);
database modificaGenere(database db);
database modificaSingoloGenere(database db, int id);
database cancellaGenere(database db);
database cancellaSingoloGenere(database db, int id);
#endif /* GESTORI_GESTOREGENERI_H_ */
