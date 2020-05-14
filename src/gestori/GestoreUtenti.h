/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREUTENTI_H_
#define GESTORI_GESTOREUTENTI_H_
#include <stdbool.h>
#include "../database/Database.h"
#include "../sys/Impostazioni.h"

bool isAdmin(database db);
bool isGivenUserAdmin(database db, int id);
void infoUtenteConnesso(database db);
database login(database db);
int controllaDatiUtente(database db, char username[], char password[]);
database registrazioneUtente(database db);
database inserimentoUtenteGuidato(database db);
struct utenti creaUtente(database db, char username[], char password[]);
database inserireUtente(database db, struct utenti utente);
bool controllaEsistenzaUtente(database db, char username[]);
void inserisciUtenteSuFile(char id[], char username[], char password[], char admin[]);
database modificaUtente(database db);
database modificaSingoloUtente(database db, int modalita, int id);
database cancellaUtente(database db);
database cancellaSingoloUtente(database db, int id);

#endif /* GESTORI_GESTOREUTENTI_H_ */
