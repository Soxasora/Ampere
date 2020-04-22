/*
 * FabbAmp 0.1 rev. 175 - 22.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/FabbAmp/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FabbAmp.h"
#include "Database.h"
#include "GestoreBrani.h"
#include "MotoreRicerca.h"
#include "Utils.h"
#include "Impostazioni.h"

int main() {
	// Inizializza il programma
	inizializzazione();
	// Mostra il menu
	printf("\nPremere invio per andare al menu.");
	menu();

	printf("\nFabbAmp terminato.\n");
	aspetta();
	return 0;
}

void inizializzazione() {
	// Visualizza informazioni su FabbAmp
	info();
	printf("\nBenvenuto su FabbAmp.");
	printf("\nInizializzazione in corso...");
	printf("\n----------------------------------------");
	// Carica le impostazioni di FabbAmp
	caricaImpostazioni();
	// Carica le lingue disponibili per i brani
	caricaLingue();
	// Crea database se esso non e' presente nella cartella.
	creaDatabaseSeNonEsiste();
	// Trasferimento in memoria del database file-based
	brani = ottieniDatabase();
	printf("\n----------------------------------------");
	printf("\nFabbAmp Pronto.");
}

