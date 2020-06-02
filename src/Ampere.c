/*
 * Ampere 0.2 rev. 17 - 02.06.2020
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
	db = terminazione(db);
	aspetta();
	pulisciBuffer();
	return 0;
}

database inizializzazione(database db) {
	// Rilevo il sistema operativo in uso al momento dell'esecuzione del programma
	os = rivelaOS();
	// Abilito i colori se su Windows, altrimenti non serve
	if (os==0)
		abilitaColori();
	// Mostra info su Ampere
	info();
	printf("\nBenvenuto su Ampere.");
	printf("\nInizializzazione in corso...");
	printf("\n----------------------------------------");

	// Carico il database
	int esito = creareDatabaseSeNonEsiste();
	if (esito!=0) {
		printf(C_ROSSO"\nSi e' verificato un errore interno. Sto chiudendo Ampere..."C_RESET);
	} else {

		// Ottengo il database degli utenti prima di caricare completamente il database
		db = ottenereDatabase(-1,db);

		// Effettuo il login
		db = menuLogin(db);

		// Ottengo il resto del database e tutti i sotto database con esso
		db = ottenereDatabase(0,db);
		printf("\n\nAmpere Pronto.");
		printf("\n----------------------------------------\n");
	}
	return db;
}

database terminazione(database db) {
	printf(C_GIALLO"\nPreparazione alla chiusura in corso...");
	if (db_modificato==1) {
		printf("\nUn momento, sto salvando i dati... "C_ROSSO"Non chiudere Ampere in questo momento."C_RESET);
		salvaModificheSuFile(db);
		printf(" Fatto.");
	}
	db = liberareDatabase(db);
	printf(C_VERDE"\nPronto per essere chiuso."C_RESET);
	return db;
}
