/*
 * Ampere 0.1 rev. 2420 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef DATABASE_BRANI_H_
#define DATABASE_BRANI_H_
#include "../sys/Impostazioni.h"

/**
 * Struttura 'brani' contenente
 * id: Identificativo del brano
 * titolo: Titolo del brano
 * durata: Durata in secondi del brano
 * album: Identificativo dell'album nel quale e' presente il brano
 * anno: Anno di uscita del brano
 * ascolti: Quante volte e' stato ascoltato il brano
 */
struct brani {
	int id;
	char titolo[MAX_CHAR];
	int durata;
	int album;
	int anno;
	int ascolti;
};

#endif /* DATABASE_BRANI_H_ */
