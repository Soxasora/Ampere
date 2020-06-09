/*
 * UNIBA/Ampere 1.1
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_RICERCA_MOTORERICERCA_H_
#define SRC_RICERCA_MOTORERICERCA_H_
#include "../database/Database.h"

/**
 * 	@input istanza database, numero intero identificativo brano
 * 	Provvede a stampare su schermo, tutte le informazioni del brano e tutte le informazioni associate ad esso
 * 	Utilizza ottenerePosDaID per ottenere le associazioni in base all'identificativo del brano dato in input
 */
void mostrareSingoloBrano(database db, int id);

void mostrareAssociazioni(database db, int modalita, int idBrano);

/**
 * 	@input istanza database
 * 	Provvede a stampare su schermo, attraverso un ciclo, tutte le informazioni di tutti i brani,
 * 	attraverso mostrareSingoloBrano
 * 	Ogni 5 brani, chiede all'utente se vuole continuare a visualizzare la libreria musicale, altrimenti termina
 * 	la funzione
 */
void mostrareTuttiBrani(database db);

/**
 * 	@input istanza database, numero intero identificativo album
 * 	Provvede a stampare su schermo, tutte le informazioni di un album in base all'identificativo dato in input
 * 	Utilizza ottenerePosDaID per ottenere la posizione dell'album nel database attraverso l'identificativo dato in input
 */
void mostrareSingoloAlbum(database db, int id);

/**
 * 	@input istanza database
 * 	Provvede a stampare su schermo, attraverso un ciclo, tutte le informazioni di tutti gli album,
 * 	attraverso mostrareSingoloAlbum
 * 	Ogni 5 album, chiede all'utente se vuole continuare a visualizzare gli album, altrimenti termina
 * 	la funzione
 */
void mostrareTuttiAlbum(database db);

/**
 * 	@input istanza database, numero intero identificativo artista
 * 	Provvede a stampare su schermo, tutte le informazioni di un artista in base all'identificativo dato in input
 * 	Utilizza ottenerePosDaID per ottenere la posizione dell'artista nel database attraverso l'identificativo dato in input
 */
void mostrareSingoloArtista(database db, int id);

/**
 * 	@input istanza database
 * 	Provvede a stampare su schermo, attraverso un ciclo, tutte le informazioni di tutti gli artisti,
 * 	attraverso mostrareSingoloArtista
 * 	Ogni 5 artisti, chiede all'utente se vuole continuare a visualizzare gli artisti, altrimenti termina
 * 	la funzione
 */
void mostrareTuttiArtisti(database db);

/**
 * 	@input istanza database, numero intero identificativo genere
 * 	Provvede a stampare su schermo, tutte le informazioni di un genere in base all'identificativo dato in input
 * 	Utilizza ottenerePosDaID per ottenere la posizione del genere nel database attraverso l'identificativo dato in input
 */
void mostrareSingoloGenere(database db, int id);

/**
 * 	@input istanza database
 * 	Provvede a stampare su schermo, attraverso un ciclo, tutte le informazioni di tutti i generi,
 * 	attraverso mostrareSingoloGenere
 * 	Ogni 5 generi, chiede all'utente se vuole continuare a visualizzare i generi, altrimenti termina
 * 	la funzione
 */
void mostrareTuttiGeneri(database db);

/**
 * 	@input istanza database, numero intero modalita' di esecuzione, numero intero identificativo playlist
 * 	Provvede a stampare su schermo, tutte le informazioni di una playlist in base all'identificativo dato in input
 * 	Utilizza ottenerePosDaID per ottenere la posizione della playlist nel database attraverso l'identificativo dato in input
 * 	In base alla modalita' di esecuzione (se non e' -1), chiede, inoltre, se l'utente vuole vedere anche i brani della playlist,
 * 	in quel caso chiamera' ricercareBraniPlaylistDaID
 * 	Altrimenti se la modalita' di esecuzione e' uguale a -1, non chiede all'utente se vuole vedere anche i brani.
 */
void mostrareSingolaPlaylist(database db, int modalita, int id);

/**
 * 	@input istanza database, numero intero modalita' di esecuzione, numero intero identificativo utente
 * 	Provvede a stampare su schermo, attraverso un ciclo, tutte le informazioni di tutte le playlist associate all'utente dato
 * 	in input attraverso mostrareSingolaPlaylist, passa ad esso anche la modalita' di esecuzione per la visualizzazione dei brani associati
 * 	Ogni 5 playlist, chiede all'utente se vuole continuare a visualizzare le playlist, altrimenti termina la funzione
 */
void mostrarePlaylistUtente(database db, int modalita, int idUtente);

/**
 * 	@input istanza database, numero intero modalita' di esecuzione
 * 	Funzione riservata agli admin
 * 	Provvede a stampare su schermo, attraverso un ciclo, tutte le informazioni di tutte le playlist presenti nel database
 * 	attraverso mostrareSingolaPlaylist, passa ad esso anche la modalita' di esecuzione per la visualizzazione dei brani associati
 * 	Ogni 5 playlist, chiede all'utente se vuole continuare a visualizzare le playlist, altrimenti termina la funzione
 */
void mostrareTuttePlaylist(database db, int modalita);

/**
 * 	@input istanza database, numero intero modalita' di esecuzione
 * 	Provvede a stampare su schermo, attraverso un ciclo, tutte le informazioni di tutte le playlist PUBBLICHE presenti nel database
 * 	attraverso mostrareSingolaPlaylist, passa ad esso anche la modalita' di esecuzione per la visualizzazione dei brani associati
 * 	Ogni 5 playlist, chiede all'utente se vuole continuare a visualizzare le playlist, altrimenti termina la funzione
 */
void mostrareTuttePlaylistPubbliche(database db, int modalita);

/**
 * 	@input istanza database, numero intero modalita' di esecuzione, numero intero identificativo utente
 * 	Provvede a stampare su schermo, tutte le informazioni di un genere in base all'identificativo dato in input
 * 	In base alla modalita' di esecuzione, esclusiva per gli admin, data in input, mostra le password.
 * 	Utilizza ottenerePosDaID per ottenere la posizione del genere nel database attraverso l'identificativo dato in input
 */
void mostrareSingoloUtente(database db, int modalita, int id);

/**
 * 	@input istanza database, numero intero modalita' di esecuzione
 * 	Funzione riservata agli admin
 * 	Provvede a stampare su schermo, attraverso un ciclo, tutte le informazioni di tutti gli utenti presenti nel database
 * 	attraverso mostrareSingoloUtente, ed in base alla scelta dell'admin, passa anche la modalita' di esecuzione per la
 * 	visualizzazione delle password.
 * 	Ogni 5 utenti, chiede all'admin se vuole continuare a visualizzare gli utenti, altrimenti termina la funzione
 */
void mostrareTuttiUtenti(database db);


//TODO RISERVATO PER FUTURI CAMBIAMENTI ED ADEGUAMENTO ALLE SPECIFICHE
/**
 *
 */
database moduloRicercaBrani(database db);

/**
 *
 */
int ricercareInfo(database db, int modalita);

/**
 *
 */
int ricercareBrani(database db, int modalita);

/**
 *
 */
int ricercareBraniArtista(database db);

/**
 *
 */
int ricercareBraniAlbum(database db);

/**
 *
 */
int ricercareBraniGenere(database db);

/**
 *
 */
int ricercareBraniPlaylist(database db);

/**
 *
 */
int ricercarePlaylistUtenteGuidato(database db);

/**
 *
 */
void ricercareBraniPlaylistDaID(database db, int id);

void stampareBraniGuidato(database db);
void stampareSingoloBrano(database db, FILE* fp, int pos);
void stampareListaBrani(database db, int idBrani[]);

#endif /* SRC_RICERCA_MOTORERICERCA_H_ */
