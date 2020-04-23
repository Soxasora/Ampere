/*
 * Ampere 0.1 rev. 180 - 23.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ampere.h"
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

	printf("\nAmpere terminato.\n");
	aspetta();
	return 0;
}

void inizializzazione() {
	// Visualizza informazioni su Ampere
	info();
	printf("\nBenvenuto su Ampere.");
	printf("\nInizializzazione in corso...");
	printf("\n----------------------------------------");
	// Carica le impostazioni di Ampere
	caricaImpostazioni();
	// Carica le lingue disponibili per i brani
	caricaLingue();
	// Crea database se esso non e' presente nella cartella.
	creaDatabaseSeNonEsiste();
	// Trasferimento in memoria del database file-based
	brani = ottieniDatabase();
	printf("\n----------------------------------------");
	printf("\nAmpere Pronto.");
}

