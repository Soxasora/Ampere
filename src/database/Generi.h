/*
 * Ampere 0.2 rev. 12 -01.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef DATABASE_GENERI_H_
#define DATABASE_GENERI_H_
#include "../sys/Impostazioni.h"

/**
 * Struttura 'generi' contenente
 * id: Identificativo del genere
 * nome: Nome del genere
 */
struct generi {
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

#endif /* DATABASE_GENERI_H_ */
