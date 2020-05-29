/*
 * Ampere 0.2 rev. 5 - 29.05.2020
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
 * 	Tabella errori:
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

void successo(int codice) {
	if (codice==0) {
		printf(COLOR_SUCCESSO" Utente inserito correttamente!");
	}
}

//void creaLogErrore(int codice) {
//	//FILE* fp=fopen("log_errore.txt", "a");
//
//}
