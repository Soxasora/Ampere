/*
 * Ampere 0.2 rev. 17 - 02.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SYS_MENU_H_
#define SYS_MENU_H_
#include "../database/Database.h"

database menuLogin(database db);
database menu(database db);
database menuAccount(database db);
database menuPlaylist(database db);
database menuDatabase(database db);
database menuDBInserimento(database db);
database menuDBModifica(database db);
database menuDBCancella(database db);
void menuRicercaAvanzata(database db);
void menuRicercaInfo(database db);
void menuRicercaBraniCriterio(database db);
void menuRicercaInfoCriterio(database db);
database menuDebug(database db);

#endif /* SYS_MENU_H_ */
