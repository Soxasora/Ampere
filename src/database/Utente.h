/*
 * UNIBA/Ampere 1.0.1
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef DATABASE_UTENTE_H_
#define DATABASE_UTENTE_H_
#include <stdbool.h>
#include "../sys/Impostazioni.h"

/**
 * Struttura 'utenti' contenente
 * id: Identificativo dell'utente
 * username: Nome Utente dell'utente
 * password: Password dell'utente (in chiaro)
 * admin: Ruolo dell'utente
 */
struct Utente {
	int id;
	char username[MAX_MEDIO];
	char password[MAX_MEDIO];
	bool admin;
};

#endif /* DATABASE_UTENTE_H_ */
