/*
 * UNIBA/Ampere 1.1
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef DATABASE_GENERE_H_
#define DATABASE_GENERE_H_
#include "../sys/Impostazioni.h"

/**
 * Struttura 'generi' contenente
 * id: Identificativo del genere
 * nome: Nome del genere
 */
struct Genere {
	int id;
	char nome[MAX_MEDIO];
};

/**
 * Serve a collegare i brani ai generi.
 * Struttura 'BranoGenere' contenente
 * idBrano: Identificativo del brano
 * idGenere: Identificativo del genere
 */
struct BranoGenere {
	int idBrano;
	int idGenere;
};

#endif /* DATABASE_GENERE_H_ */
