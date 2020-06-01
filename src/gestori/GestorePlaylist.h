/*
 * Ampere 0.2 rev. 12 -01.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */


#ifndef GESTORI_GESTOREPLAYLIST_H_
#define GESTORI_GESTOREPLAYLIST_H_
#include <stdbool.h>
#include "../database/Database.h"

/**
 * 	@input istanza database, identificativo della playlist, identificativo dell'utente
 *	Serve a controllare se la playlist data in input appartiene all'utente dato in input
 *	Restituisce vero se la playlist e' dell'utente, altrimenti falso
 *	Si avvale di ottenerePosDaID per ottenere la posizione dell'identificativo playlist dato in input
 *	@output risultato booleano
 */
bool isUserPlaylist(database db, int idPlaylist, int idUtente);

/**
 *	@input istanza database, identificativo della playlist
 *	Serve a controllare se la playlist data in input, ha privacy pubblica
 *	Restituisce vero se la playlist e' pubblica, altrimenti falso
 *	Si avvale di ottenerePosDaID per ottenere la posizione dell'identificativo playlist dato in input
 *	@output risultato booleano
 */
bool isPublicPlaylist(database db, int idPlaylist);

/**
 *	@input istanza database, identificativo dell'utente
 *	Serve a conteggiare le playlist appartenenti all'utente dato in input
 *	Restituisce il numero intero di playlist trovate
 *	Si avvale di contareNelDatabase per far funzionare il ciclo atto al controllo
 *	@ouput numero intero conta
 */
int contaPlaylistUtente(database db, int idUtente);

/**
 *	@input istanza database, identificativo della playlist
 *	Serve a conteggiare quanti brani sono presenti nella playlist data in input
 *	Restituisce il numero intero di brani trovati all'interno della playlist
 *	Si avvale di contareNelDatabase per far funzionare il ciclo atto al controllo
 *	@ouput numero intero conta
 */
int contaBraniPlaylist(database db, int idPlaylist);

/**
 * 	@input istanza database, numero intero identificativo utente,
 * 	stringa nome playlist, descrizione, booleano status privacy "pubblica"
 *	Funzione logica per la creazione di un record "playlists", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record playlist compilato
 */
struct playlists crearePlaylist(int idUtente, char nome[], char descrizione[], bool pubblica);

void mostrareAnteprimaPlaylist(struct playlists nuovaPlaylist);

/**
 *	@input istanza database, record playlists playlist
 *	Ottiene in input il record playlist gia' compilato con crearePlaylist e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserirePlaylist(database db, struct playlists playlist);

/**
 * 	@input istanza database
 *	Interfaccia utente stand-alone per la creazione di una playlist, può essere chiamata
 *	senza dipendere da altre funzioni
 *	Dopo la creazione della playlist, chiede anche all'utente se vuole inserire dei brani in essa
 *	Crea la playlist con crearePlaylist e la passa ad inserirePlaylist
 *	Se l'utente vuole aggiungere brani, chiama anche inserimentoBraniPlaylistGuidato
 *	@output database modificato
 */
database crearePlaylistGuidato(database db);

/**
 * 	TODO: Scorporare funzione, migliorare funzione
 * 	@input istanza database
 *	Interfaccia utente stand-alone per l'inserimento di brani in una playlist, può essere chiamata
 *	senza dipendere da altre funzioni
 *	Operazioni di ricerca della playlist nella quale si vogliono aggiungere brani
 *	Esegue operazioni di inserimento dei brani in una playlist attraverso l'associazione playlist-brano
 *	@output database modificato
 */
database inserimentoBraniPlaylistGuidato(database db);

/**
 *	@input struct playlists playlist, booleano status privacy "pubblica"
 *	Scrive sul file "file_playlists", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserisciPlaylistSuFile(struct playlists playlist, char pubblica[]);

/**
 * 	TODO: Migliorare funzione, potrebbe esserci piu' di un'occorrenza
 *	@input istanza database, stringa nome della playlist
 *	Cerca all'interno del database, attraverso un ciclo, almeno un'occorrenza del nome
 *	della playlist data in input e se esiste allora esce dal ciclo dando in output l'identificativo di esso
 *	@output identificativo playlist
 */
int controlloEsistenzaPlaylist(database db, char playlist[]);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per modificare informazioni della playlist presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di essa attraverso l'identificativo
 *	Se la playlist e' presente ed e' dell'utente oppure ad eseguire la funzione e' un admin,
 *	procede alla modifica dell'informazione scelta con modificaSingolaPlaylist
 *	@output database modificato
 */
database modificaPlaylist(database db);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database, numero intero modalita' di esecuzione, numero intero identificativo
 *	In base alla modalita' scelta e data in input da modificaPlaylist, chiede all'utente la nuova informazione
 *	da inserire al posto della vecchia, sovrascrivendola
 *	Presenta una modalita' utilizzabile unicamente da un amministratore,
 *	ovvero la modifica dell'autore della playlist
 *	Successivamente procede a mostrare all'utente il risultato delle modifiche effettuate
 *	@output database modificato
 */
database modificaSingolaPlaylist(database db, int modalita, int id);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per la cancellazione di una playlist presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di essa attraverso l'identificativo
 *	Se la playlist e' presente ed e' dell'utente oppure ad eseguire la funzione e' un admin,
 *	procede alla cancellazione della playlist con cancellaSingolaPlaylist
 *	@output database modificato
 */
database cancellaPlaylist(database db);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database, numero intero identificativo playlist
 *	Operazioni per la cancellazione della playlist all'interno del database presente in memoria
 *	Scala il database di n=1 posizione indietro e lo spazio rimanente alla fine assume valore zero,
 *	effettivamente causando la cancellazione della playlist all'interno del database presente in memoria.
 *	La cancellazione della playlist provvede anche a cancellare le associazioni playlist-brano
 *	avvalendosi di cancellaAssociazionePlaylist
 *	@output database modificato
 */
database cancellaSingolaPlaylist(database db, int id);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database, numero intero identificativo playlist
 *	Operazioni per la cancellazione delle associazioni della playlist (dunque i dati collegati ad essa) dal database
 *	@output database modificato
 */
database cancellaAssociazionePlaylist(database db, int id);

#endif /* GESTORI_GESTOREPLAYLIST_H_ */
