/*
 * FabbAmp 0.1 rev. 137 - 19.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/FabbAmp/blob/master/LICENSE
 */

#include "FabbAmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Database.h"
#include "GestoreBrani.h"
#include "MotoreRicerca.h"
#include "Utils.h"

int main() {
	// Inizializza il programma
	inizializzazione();
	// Mostra il menu
	printf("\nPremere invio per andare al menu.");
	menu();
	// Esegui le ultime funzioni di aggiornamento prima di chiudere
	//terminazione();

	printf("\nFabbAmp terminato.\n");
	aspetta();
	return 0;
}

void inizializzazione() {
	// Visualizza informazioni su FabbAmp
	info();
	printf("\nBenvenuto su FabbAmp.");
	printf("\nInizializzazione in corso...");
	// Carica le lingue disponibili per i brani
	caricaLingue();
	// Crea database se esso non e' presente nella cartella.
	creaDatabaseSeNonEsiste();
	// Trasferimento in memoria del database file-based
	brani = ottieniDatabase();
	printf("\nFabbAmp Pronto.");
}

/*void terminazione() {
	aggiornaDatabase();
}*/

