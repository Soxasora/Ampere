/*
 * Ampere 0.1 rev. 2432 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef DATABASE_ARTISTI_H_
#define DATABASE_ARTISTI_H_
#include "../sys/Impostazioni.h"

/**
 * Struttura 'artista' contenente
 * id: Identificativo dell'artista
 * nome: Nome dell'artista
 * cognome: Cognome dell'artista
 * nomearte: Nome d'arte dell'artista
 */
struct artisti {
	int id;
	char nome[MAX_CHAR];
	char cognome[MAX_CHAR];
	char nomearte[MAX_CHAR];
};

/**
 * Serve a collegare i brani agli artisti
 * Struttura 'associazioneArtisti' contenente
 * idBrano: Identificativo del brano
 * idArtista: Identificativo dell'artista
 */
struct associazioneArtisti {
	int idBrano;
	int idArtista;
};


#endif /* DATABASE_ARTISTI_H_ */
