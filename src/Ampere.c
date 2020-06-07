/*
 * UNIBA/Ampere 0.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ampere.h"
#include "gestori/GestoreUtenti.h"
#include "gestori/GestoreFile.h"
#include "database/Database.h"
#include "sys/Messaggi.h"
#include "sys/Menu.h"
#include "sys/Utils.h"
#include "sys/Impostazioni.h"

int main() {
	// Creo database
	database db;
	db = inizializzazione(db);
	infoUtenteConnesso(db);
	db = menu(db);
	db = terminazione(db);
	aspetta();
	
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
	cPrintf(C_CIANO,"\nInizializzazione di Ampere in corso...");
	printf(DIVISORE);

	// Carico il database
	int esito = creareDatabaseSeNonEsiste();
	if (esito!=0) {
		errore(-1);
		errore(20);
	} else {
		// Ottengo il database degli utenti prima di caricare completamente il database
		db = ottenereDatabase(-1,db);

		// Effettuo il login
		db = menuLogin(db);

		// Ottengo il resto del database e tutti i sotto database con esso
		db = ottenereDatabase(0,db);
		successo(111);
		printf(DIVISORE"\n");
	}
	return db;
}

database terminazione(database db) {
	attenzione(100);
	if (db_modificato==1) {
		printf("\nUn momento, sto salvando i dati... ");
		cPrintf(C_ROSSO,"Non chiudere Ampere in questo momento.");
		salvaModificheSuFile(db);
		cPrintf(C_VERDE," Fatto.");
	}
	db = liberareDatabase(db);
	successo(112);
	return db;
}
