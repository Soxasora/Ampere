/*
 * Ampere 0.1 rev. 2720 - 09.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef DATABASE_UTENTI_H_
#define DATABASE_UTENTI_H_
#include <stdbool.h>
#include "../sys/Impostazioni.h"

/**
 * Struttura 'utenti' contenente
 * id: Identificativo dell'utente
 * username: Nome Utente dell'utente
 * password: Password dell'utente (in chiaro)
 * admin: Ruolo dell'utente
 */
struct utenti {
	int id;
	char username[MAX_CHAR];
	char password[MAX_CHAR];
	bool admin;
};

#endif /* DATABASE_UTENTI_H_ */
