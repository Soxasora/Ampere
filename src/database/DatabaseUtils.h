/*
 * UNIBA/Ampere 1.2
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_DATABASE_DATABASEUTILS_H_
#define SRC_DATABASE_DATABASEUTILS_H_
#include "../database/Database.h"

/**
 * Ogni funzione di analisi del void contenuto in memoria, utilizza le seguenti modalita'
 * per dettare regimi di funzionamento adeguati al lavoro richiesto
 *
 * Le modalit� sono le seguenti:
 * -1: Utente
 * 0: Brano
 * 1: Album
 * 2: Artista
 * 3: Genere
 * 4: Playlist
 * 5: Associazione artista-brano
 * 6: Associazione album-brano
 * 7: Associazione genere-brano
 * 8: Associazione playlist-brano
 */

/**
 * 	@input istanza database, modalita' di esecuzione
 * 	In base alla modalita' scelta, conta all'interno del void contenuto in memoria, quante
 * 	sono le occorrenze di, ad esempio, brani, album, artisti...
 * 	Il conteggio funziona esclusivamente sul controllo del campo id di essi o del campo idBrano
 * 	(nel caso delle associazioni), dunque non appena trovera' valore zero, si fermera' dal conteggio
 *	@output occorrenze del dato richiesto
 */
int contareNelDatabase(database *db,int modalita);

/**
 *	@input istanza database, modalita' di esecuzione
 *	In base alla modalita' scelta, individua l'ultimo identificativo utilizzato
 *	L'individuazione si basa sull'analisi del massimo numero intero trovato all'interno della parte
 *	di void scelta in base alla modalita'. Controlla inoltre se la parte di void soggetta
 *	al controllo e' vuota avvalendosi di contareNelDatabase, nel caso in cui dovesse essere vuota
 *	restituira' come id, il valore zero.
 *	@output il maggior identificativo trovato
 */
int trovareUltimoId(database *db, int modalita);

/**
 *	@input istanza database, modalita' di esecuzione, identificativo
 *	In base alla modalita' scelta, controlla, attraverso un ciclo con indice i, all'interno
 *	della parte di void coinvolta, la presenza dell'identificativo dato in input, restituendo cosi'
 *	la posizione di esso all'interno del database. Nel caso in cui non riuscisse a trovare l'identificativo
 *	dato in input, restituira' il valore negativo -1
 *	@output posizione all'interno del database
 */
int ottenerePosDaID(database *db, int modalita, int id);

int* ottenerePosAssociazioniDaID(database *db, int modalita, int id);

/**
 *	Chiede in input, all'utente, il nome del backup da generare, in base ad esso creera' una cartella
 *	all'interno della quale copiera' tutti i file del void nel loro stato originale, avvalendosi
 *	della funzione backupFile
 */
void backupDatabase();

/**
 *	@input istanza database
 *	Chiede in input, all'utente, il nome del backup da ripristinare, in base ad esso, si posizionera'
 *	sulla cartella del backup selezionato e successivamente copiera' i file all'interno di essa, nella
 *	cartella originale del database.
 *	Infine procedera' a chiamare ottenereDatabase per ricaricare in memoria il void appena ripristinato
 *	@output void ripristinato
 */
void ripristinareDatabase(database *db);

#endif /* SRC_DATABASE_DATABASEUTILS_H_ */
