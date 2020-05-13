/*
 * Ampere 0.1 rev. 3000 - 13.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sys/Errore.h"
#include "../sys/Impostazioni.h"

/**
 * Tabella errori:
 * DATABASE:
 * 1: Nessun brano presente
 * 2: Nessun album presente
 *
 * 17: Quando e' impossibile creare la cartella
 * 18: Impossibile aprire il file selezionato
 * 19: Impossibile creare un file di sistema
 */
char *errore(int codice) {
	char *errore= malloc(MAX_ENORME);
	if (codice==19) {
		printf("\nImpossibile aprire il file selezionato: ");
	}
	return errore;
}

void creaLogErrore(int codice) {
	//FILE* fp=fopen("log_errore.txt", "a");

}
