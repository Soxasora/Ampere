/*
 * UNIBA/Ampere 1.3
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
	inizializzazione(&db);
	infoUtenteConnesso(&db);
	menu(&db);
	terminazione(&db);
	aspetta();
	
	return 0;
}

void inizializzazione(database *db) {
	// Rilevo il sistema operativo in uso al momento dell'esecuzione del programma
	os = rilevareOS();
	// Abilito i colori se su Windows, altrimenti non serve
	if (os==0)
		abilitareColori();
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
		// Chiedo all'utente se preferisce il salvataggio dopo le modifiche o alla chiusura di Ampere
		printf("\nPreferisci salvare le modifiche alla "C_GIALLO"chiusura[0]"C_RESET" di Ampere oppure "C_VERDE"subito[1]"C_RESET"? ");
		salvataggioDiretto = inputNumero();

		// Ottengo il database degli utenti prima di caricare completamente il database
		ottenereDatabase(-1,db);

		// Effettuo il login
		menuLogin(db);

		// Ottengo il resto del database e tutti i sotto database con esso
		ottenereDatabase(0,db);
		successo(111);
		printf(DIVISORE"\n");
	}
	
}

void terminazione(database *db) {
	attenzione(100);
	if (!salvataggioDiretto&db->modificato) {
		printf("\nUn momento, sto salvando i dati... ");
		cPrintf(C_ROSSO,"Non chiudere Ampere in questo momento.");
		salvareModificheSuFile(db);
		cPrintf(C_VERDE," Fatto.");
	}
	liberareDatabase(db);
	successo(112);
	
}
