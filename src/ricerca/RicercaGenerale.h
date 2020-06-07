/*
 * UNIBA/Ampere 0.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef RICERCA_RICERCAGENERALE_H_
#define RICERCA_RICERCAGENERALE_H_
#include "../database/Database.h"

void ricerca(database db, int modalita, char interrogazione[], bool light);
void eseguiRicerca(database db);

#endif /* RICERCA_RICERCAGENERALE_H_ */
