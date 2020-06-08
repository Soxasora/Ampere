/*
 * UNIBA/Ampere 1.0.1
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef DATABASE_ARTISTA_H_
#define DATABASE_ARTISTA_H_
#include "../sys/Impostazioni.h"

/**
 * Struttura 'artista' contenente
 * id: Identificativo dell'artista
 * nome: Nome dell'artista
 * cognome: Cognome dell'artista
 * nomeArte: Nome d'arte dell'artista
 */
struct Artista {
	int id;
	char nome[MAX_MEDIO];
	char cognome[MAX_MEDIO];
	char nomeArte[MAX_MEDIO];
	char linkBio[MAX_ENORME];
};

/**
 * Serve a collegare i brani agli artisti
 * Struttura 'BranoArtista' contenente
 * idBrano: Identificativo del brano
 * idArtista: Identificativo dell'artista
 */
struct BranoArtista {
	int idBrano;
	int idArtista;
};


#endif /* DATABASE_ARTISTA_H_ */
