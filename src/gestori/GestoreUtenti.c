/*
 * Ampere 0.1 rev. 2420 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../ricerca/MotoreRicerca.h"
#include "../gestori/GestorePlaylist.h"
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

bool isGivenUserAdmin(int id) {
	bool risultato=false;
	risultato = db.utente[ottieniPosDaID(-1, id)].admin;
	return risultato;
}

void infoUtenteConnesso() {
	int posutente = ottieniPosDaID(-1, db.utente_connesso);
	char* ruolo = malloc(20);
	if (isAdmin()==true) {
		ruolo="Amministratore";
	} else {
		ruolo="Utente normale";
	}
	printf("\n===[Informazioni Utente Connesso]===");
	printf("\nNome Utente: %s", db.utente[posutente].username);
	printf("\nRuolo Utente: %s\n", ruolo);
	free(ruolo);
}

void login() {
	printf("\nEsecuzione Login ad Ampere");
	int controllo=0, id=0;
	char *username = malloc(MAX_CHAR);
	char *password = malloc(MAX_CHAR);
	while (controllo!=-1) {
		pulisciBuffer();
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
		if (comparaStringhe(db.utente[i].username, username)==0 && strcmp(db.utente[i].password, password)==0) {
			id = db.utente[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

void registrazioneUtente() {
	pulisciBuffer();
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
	free(username); free(password);
}

void inserimentoUtenteGuidato() {
	char *username = malloc(MAX_CHAR);
	char *password = malloc(MAX_CHAR);
	printf("\nInserisci username: ");
	username = inputStringaSicuro(username);
	printf("\nInserisci password: ");
	password = inputStringaSicuro(password);
	inserisciUtente(username, password);
	free(username); free(password);
	printf("\nUtente inserito.");
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

void modificaUtente() {
	int id=0, modalita=0;
	char scelta='N';
	if (isAdmin()) {
		mostraTuttiUtenti();
		printf("\nInserisci id dell'utente da modificare: ");
		scanf("%d", &id);
		printf("\nHai scelto l'utente");
		mostraSingoloUtente(0, id);
	} else {
		mostraSingoloUtente(1,db.utente_connesso);
		id = db.utente_connesso;
	}
	pulisciBuffer();
	printf("\nSicuro di voler continuare? [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica utente]===");
		printf("\n[1] Modifica l'username");
		printf("\n[2] Modifica la password");
		if (isAdmin())
			printf("\n[3] Modifica il ruolo");
		printf("\n[0] Esci");
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &modalita);
		if (modalita!=0) {
			modificaSingoloUtente(modalita, id);
		}
	}
}

void modificaSingoloUtente(int modalita, int id) {
	db_modificato=1;
	pulisciBuffer();
	int pos = ottieniPosDaID(-1, id);
	if (modalita==1) {
		char *username = malloc(MAX_CHAR);
		printf("\nInserisci nuovo username: ");
		username = inputStringaSicuro(username);
		strcpy(db.utente[pos].username, username);
		free(username);
	} else if (modalita==2) {
		char *password_vecchia = malloc(MAX_CHAR);
		strcpy(password_vecchia, "null");
		char *password = malloc(MAX_CHAR);
		strcpy(password, "null");
		char *password2 = malloc(MAX_CHAR);
		strcpy(password2, "null2");
		if (!isAdmin()) {
			while (strcmp(password_vecchia, db.utente[pos].password)!=0) {
				printf("\nInserisci password attuale: ");
				password_vecchia = inputStringaSicuro(password_vecchia);
				if (strcmp(password_vecchia, db.utente[pos].password)!=0)
					printf("\nLa password attuale non è corretta! Riprova\n");
			}
		}
		while (strcmp(password,password2)!=0) {
			printf("\nInserisci nuova password: ");
			password=inputStringaSicuro(password);
			printf("\nInserisci nuovamente la nuova password: ");
			password2=inputStringaSicuro(password2);
			if (strcmp(password,password2)!=0) {
				printf("\nLe due password non combaciano! Riprova\n");
			}
		}
		strcpy(db.utente[pos].password,password);
		free(password_vecchia); free(password); free(password2);
	} else if (modalita==3) {
		if (isAdmin()) {
			int ruolo=1;
			printf("\nAmministratore[0] oppure Utente normale[1]? ");
			scanf("%d", &ruolo);
			if (ruolo==0) {
				db.utente[pos].admin=true;
			} else if (ruolo==1) {
				db.utente[pos].admin=false;
			}
		} else {
			printf("\nNon puoi accedere a questa funzione in quanto utente normale.");
		}
	}
}

void cancellaUtente() {
	int id=0;
	char scelta='N';
	if (isAdmin()) {
		mostraTuttiUtenti();
		printf("\nInserisci id dell'utente: ");
		scanf("%d", &id);
		printf("\nHai scelto l'utente: ");
		mostraSingoloUtente(0, id);
	} else {
		id = db.utente_connesso;
		mostraSingoloUtente(0, id);
	}
	pulisciBuffer();
	printf("\nSicuro di voler continuare? [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		cancellaSingoloUtente(id);
	}
}

void cancellaSingoloUtente(int id) {
	int n=contaNelDatabase(-1);
	int i=ottieniPosDaID(-1, id);
	while (i<n-1) {
		db.utente[i] = db.utente[i+1];
		i++;
	}
	db.utente[n-1].id = 0;

	int nplaylist=contaNelDatabase(4);
	i=0;
	while (i<nplaylist) {
		if (db.playlist[i].idUtente==id) {
			cancellaSingolaPlaylist(db.playlist[i].id);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
}

