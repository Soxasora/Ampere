/*
 * Ampere 0.1 rev. 4075 - 19.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
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
	// Creo database
	database db;
	db = inizializzazione(db);
	infoUtenteConnesso(db);
	printf("\nPremi invio per continuare.");
	db = menu(db);
	terminazione(db);
	aspetta();
	return 0;
}

database inizializzazione(database db) {
	// Mostra info su Ampere
	info();
	printf("\nBenvenuto su Ampere.");
	printf("\nInizializzazione in corso...");
	printf("\n----------------------------------------");
	// Rilevo il sistema operativo in uso al momento dell'esecuzione del programma
	os = rivelaOS();

	// Carico il database
	int esito = creaDatabaseSeNonEsiste();
	if (esito!=0) {
		printf("\nSi e' verificato un errore interno. Sto chiudendo Ampere...");
	} else {

		// Ottengo il database degli utenti prima di caricare completamente il database
		db = ottieniDatabaseParziale(db);

		printf("\nPremi invio per continuare.");
		db = menuLogin(db);

		// Ottengo il database e tutti i sotto database con esso
		db = ottieniDatabase(db);
		printf("\n\nAmpere Pronto.");
		printf("\n----------------------------------------\n");
	}
	return db;
}

void terminazione(database db) {
	printf("\nPreparazione alla chiusura in corso...");
	if (db_modificato==1) {
		printf("\nUn momento, sto salvando i dati...");
		salvaModificheSuFile(db);
		printf(" Fatto.");
	}
	printf("\nPronto per essere chiuso.");
}
