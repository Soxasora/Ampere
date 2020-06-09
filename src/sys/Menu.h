/*
 * UNIBA/Ampere 1.2.2
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SYS_MENU_H_
#define SYS_MENU_H_
#include "../database/Database.h"

void menuLogin(database *db);
void menu(database *db);
void menuAccount(database *db);
void menuPlaylist(database *db);
void menuDatabase(database *db);
void menuDBInserimento(database *db);
void menuDBModifica(database *db);
void menuDBCancella(database *db);
void menuRicercaAvanzata(database *db);
void menuRicercaInfo(database *db);
void menuRicercaBraniCriterio(database *db);
void menuRicercaInfoCriterio(database *db);
void menuDebug(database *db);

#endif /* SYS_MENU_H_ */
