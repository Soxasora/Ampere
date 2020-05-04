/*
 * Ampere 0.1 rev. 1250 - 04.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../gestori/GestoreUtenti.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

bool isAdmin() {
	bool risultato=false;
	int pos=ottieniPosDaID(-1,db.utente_connesso);
	risultato = db.utente[pos].admin;
	return risultato;
}

void login() {
	int controllo=0, id=0;
	char *username = malloc(MAX_CHAR);
	char *password = malloc(MAX_CHAR);
	while (controllo!=-1) {
		printf("\nInserisci username: ");
		username = inputStringaSicuro(username);
		printf("\nInserisci password: ");
		password = inputStringaSicuro(password);
		id = controllaDatiUtente(username, password);
		if (id!=0) {
			printf("\nAccesso consentito. Bentornato su Ampere, %s.", username);
			db.utente_connesso = id;
			controllo=-1;
		} else {
			printf("\nCombinazione username/password sbagliata. Riprovare.");
		}
	}
	free(username); free(password);
}

int controllaDatiUtente(char username[], char password[]) {
	int n = contaNelDatabase(-1), i=0, controllo=0, id=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.utente[i].username, username)==0 && comparaStringhe(db.utente[i].password, password)==0) {
			id = db.utente[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

void registrazioneUtente() {
	int controllo=0;
	char *username = malloc(MAX_CHAR);
	char *password = malloc(MAX_CHAR);
	printf("\n===[Registrazione guidata di un utente]===");
	printf("\nBenvenuto su Ampere. Procediamo alla creazione del tuo profilo.");
	while (controllo!=-1) {
		printf("\n\nInserisci username: ");
		username = inputStringaSicuro(username);
		if (controllaEsistenzaUtente(username)==false) {
			printf("\nInserisci password: ");
			password = inputStringaSicuro(password);
			inserisciUtente(username, password);
			printf("\nUtente inserito correttamente!");
			controllo=-1;
		} else {
			printf("\nQuesto utente esiste gia'! Scegline un altro.");
		}
	}
	login();
}

void inserisciUtente(char username[], char password[]) {
	db_modificato=1;
	int n=contaNelDatabase(-1);
	db.utente[n].id = trovaUltimoId(-1)+1;
	strcpy(db.utente[n].username, username);
	strcpy(db.utente[n].password, password);
}

bool controllaEsistenzaUtente(char username[]) {
	int i=0, n=contaNelDatabase(-1), controllo=0;
	bool esistenza=false;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.utente[i].username, username)==0) {
			esistenza=true;
			controllo=-1;
		}
		i++;
	}
	return esistenza;
}

void inserisciUtenteSuFile(char id[], char username[], char password[], char admin[]) {
	FILE* fp=fopen(file_utenti, "a");
	if (controllaSeFileVuoto(file_utenti)==1) {
		fprintf(fp, "%s,%s,%s,%s", id, username, password, admin);
	} else {
		fprintf(fp, "\n%s,%s,%s,%s", id, username, password, admin);
	}
	fclose(fp);
}

