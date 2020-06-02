/*
 * Ampere 0.2 rev. 17 - 02.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include "Messaggi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sys/Impostazioni.h"

/**
 * Tabella errori critici:
 * DATABASE:
 * 1: Nessun brano presente
 * 2: Nessun album presente
 *
 * 16: Non puoi accedere a questa funzione in quanto utente normale.
 * 17: Impossibile creare la cartella.
 * 18: Impossibile aprire il file selezionato.
 * 19: Impossibile creare un file di sistema.
 * 99: Errore critico di sistema.
 */
void errore(int codice) {
	if (codice==16) {
		printf(COLOR_ERRORE" Non puoi accedere a questa funzione in quanto utente normale.");
	}
}

/**
 * 	Tabella attenzioni:
 * 	1: Combinazione username/password sbagliata
 *
 * 	Input sulle scelte dell'utente
 * 	20: Inserita scelta non riconosciuta, riprovare.
 */

void attenzione(int codice) {
	if (codice==0) {
		printf(COLOR_ATTENZIONE" Questo utente esiste gia'! Scegline un altro.");
	} else if (codice==1) {
		printf(COLOR_ATTENZIONE" Combinazione username/password sbagliata. Riprovare.");
	} else if (codice==2) {
		printf(COLOR_ATTENZIONE" Inseriti valori non validi. Riprovare.");
	} else if (codice==20) {
		printf(COLOR_ATTENZIONE" Inserita scelta non riconosciuta, riprovare.");
	}
}


/**
 * 	Tabella successi:
 * 	0: Inserimento utente
 * 	1: Inserimento brano
 * 	2: Inserimento album
 * 	3: Inserimento artista
 * 	4: Inserimento genere
 * 	5: Inserimento playlist
 *	6: Modifica utente
 *	7: Modifica brano
 *	8: Modifica album
 *	9: Modifica artista
 *	10: Modifica genere
 *	11: Modifica playlist
 *	100: Ottenimento database
 *	101: Ottenimento utenti
 *	102: Ottenimento brani
 *	103: Ottenimento albums
 *	104: Ottenimento artisti
 *	105: Ottenimento generi
 *	106: Ottenimento playlists
 *	107: Ottenimento associazioni artisti
 *	108: Ottenimento associazioni albums
 *	109: Ottenimento associazioni generi
 *	110: Ottenimento associazioni playlist
 */

void successo(int codice) {
	if (codice==0) {
		printf(COLOR_SUCCESSO" Utente inserito correttamente!");
	}
}

//void creaLogErrore(int codice) {
//	//FILE* fp=fopen("log_errore.txt", "a");
//
//}
