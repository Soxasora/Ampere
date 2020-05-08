/*
 * Ampere 0.1 rev. 2432 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ampere.h"
#include "gestori/GestoreUtenti.h"
#include "gestori/GestoreFile.h"
#include "database/Database.h"
#include "sys/Menu.h"
#include "sys/Utils.h"
#include "sys/Impostazioni.h"

int main() {
	int esito=0;
	esito = inizializzazione();
	if (esito==0) {
		infoUtenteConnesso();
		printf("\nPremi invio per continuare.");
		menu();
		terminazione();
	}
	aspetta();
	return 0;
}

int inizializzazione() {
	// Mostra info su Ampere
	info();
	printf("\nBenvenuto su Ampere.");
	printf("\nInizializzazione in corso...");
	printf("\n----------------------------------------");
	// Rilevo il sistema operativo in uso al momento dell'esecuzione del programma
	os = rivelaOS();
	int esito=0;
	esito = creaDatabaseSeNonEsiste();
	if (esito!=0) {
		printf("\nSi e' verificato un errore interno. Sto chiudendo Ampere...");
	} else {
		// Ottengo il database degli utenti prima di caricare completamente il database
		db = ottieniDatabaseParziale();

		printf("\nPremi invio per continuare.");
		menuLogin();

		// Ottengo il database e tutti i sotto database con esso
		db = ottieniDatabase();
		printf("\n\nAmpere Pronto.");
		printf("\n----------------------------------------\n");
	}
	return esito;
}

void terminazione() {
	printf("\nPreparazione alla chiusura in corso...");
	if (db_modificato==1) {
		printf("\nUn momento, sto salvando i dati...");
		salvaModificheSuFile();
		printf(" Fatto.");
	}
	printf("\nPronto per essere chiuso.");
}
