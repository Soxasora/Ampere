/*
 * UNIBA/Ampere 1.0.1
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_AMPERE_H_
#define SRC_AMPERE_H_
#include "database/Database.h"

/**
 *	@input istanza database
 *	Operazioni fondamentali per l'inizializzazione di Ampere, dunque per garantire un corretto
 *	funzionamento sin dall'inizio.
 *	@output database modificato
 */
database inizializzazione(database db);

/**
 *	Operazioni fondamentali per la terminazione di Ampere, dunque per garantire il salvataggio
 *	e l'integrita' dei dati inseriti durante l'esecuzione di Ampere
 */
database terminazione(database db);

#endif /* SRC_AMPERE_H_ */
