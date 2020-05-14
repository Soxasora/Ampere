/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
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

bool isAdmin(database db) {
	bool risultato=false;
	int pos=ottieniPosDaID(db, -1,db.utenteCorrente);
	risultato = db.utente[pos].admin;
	return risultato;
}

bool isGivenUserAdmin(database db, int id) {
	bool risultato=false;
	risultato = db.utente[ottieniPosDaID(db, -1, id)].admin;
	return risultato;
}

void infoUtenteConnesso(database db) {
	int posutente = ottieniPosDaID(db, -1, db.utenteCorrente);
	char* ruolo = malloc(20);
	if (isAdmin(db)==true) {
		ruolo="Amministratore";
	} else {
		ruolo="Utente normale";
	}
	printf("\n===[Informazioni Utente Connesso]===");
	printf("\nNome Utente: %s", db.utente[posutente].username);
	printf("\nRuolo Utente: %s\n", ruolo);
	free(ruolo);
}

database login(database db) {
	printf("\nEsecuzione Login ad Ampere");
	int controllo=0, id=0;
	char *username = malloc(MAX_MEDIO);
	char *password = malloc(MAX_MEDIO);
	while (controllo!=-1) {
		pulisciBuffer();
		printf("\nInserisci username: ");
		username = inputStringaSicuro(MAX_MEDIO,username);
		printf("\nInserisci password: ");
		password = inputStringaSicuro(MAX_MEDIO,password);
		id = controllaDatiUtente(db, username, password);
		if (id!=0) {
			printf("\nAccesso consentito. Bentornato su Ampere, %s.", username);
			db.utenteCorrente = id;
			controllo=-1;
		} else {
			printf("\nCombinazione username/password sbagliata. Riprovare.");
		}
	}
	free(username); free(password);
	return db;
}

int controllaDatiUtente(database db, char username[], char password[]) {
	int n = contaNelDatabase(db,-1), i=0, controllo=0, id=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.utente[i].username, username)==0 && strcmp(db.utente[i].password, password)==0) {
			id = db.utente[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

database registrazioneUtente(database db) {
	pulisciBuffer();
	int controllo=0;
	char *username = malloc(MAX_MEDIO);
	char *password = malloc(MAX_MEDIO);
	printf("\n===[Registrazione guidata di un utente]===");
	printf("\nBenvenuto su Ampere. Procediamo alla creazione del tuo profilo.");
	while (controllo!=-1) {
		printf("\n\nInserisci username: ");
		username = inputStringaSicuro(MAX_MEDIO,username);
		if (controllaEsistenzaUtente(db, username)==false) {
			printf("\nInserisci password: ");
			password = inputStringaSicuro(MAX_MEDIO,password);
			db = inserireUtente(db, creaUtente(db, username, password));
			printf("\nUtente inserito correttamente!");
			controllo=-1;
		} else {
			printf("\nQuesto utente esiste gia'! Scegline un altro.");
		}
	}
	db = login(db);
	free(username); free(password);
	return db;
}

database inserimentoUtenteGuidato(database db) {
	char *username = malloc(MAX_MEDIO);
	char *password = malloc(MAX_MEDIO);
	printf("\nInserisci username: ");
	username = inputStringaSicuro(MAX_MEDIO,username);
	printf("\nInserisci password: ");
	password = inputStringaSicuro(MAX_MEDIO,password);
	db = inserireUtente(db, creaUtente(db, username, password));
	free(username); free(password);
	printf("\nUtente inserito.");
	return db;
}

struct utenti creaUtente(database db, char username[], char password[]) {
	struct utenti utente;
	utente.id = trovaUltimoId(db, -1)+1;
	strcpy(utente.username, username);
	strcpy(utente.password, password);
	return utente;
}

database inserireUtente(database db, struct utenti utente) {
	db_modificato=1;
	int n=contaNelDatabase(db,-1);
	db.utente[n] = utente;
	return db;
}

bool controllaEsistenzaUtente(database db, char username[]) {
	int i=0, n=contaNelDatabase(db,-1), controllo=0;
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
		fprintf(fp, "%s|%s|%s|%s", id, username, password, admin);
	} else {
		fprintf(fp, "\n%s|%s|%s|%s", id, username, password, admin);
	}
	fclose(fp);
}

database modificaUtente(database db) {
	int id=0, modalita=-1, controllo=0;
	char scelta='a';
	if (isAdmin(db)) {
		mostraTuttiUtenti(db);
		while (ottieniPosDaID(db, -1,id)==-1) {
			printf("\nInserisci id dell'utente da modificare: ");
			scanf("%d", &id);
			if (ottieniPosDaID(db, -1,id)==-1) {
				printf("\nNessun utente trovato, riprovare");
			}
		}
		printf("\nHai scelto l'utente");
		mostraSingoloUtente(db, 0, id);
	} else {
		mostraSingoloUtente(db, 1,db.utenteCorrente);
		id = db.utenteCorrente;
	}
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica utente]===");
		printf("\n[1] Modifica l'username");
		printf("\n[2] Modifica la password");
		if (isAdmin(db))
			printf("\n[3] Modifica il ruolo");
		printf("\n[0] Esci");
		while (modalita<0||modalita>3) {
			printf("\nInserisci la tua scelta: ");
			scanf("%d", &modalita);
		}
		if (modalita!=0) {
			db = modificaSingoloUtente(db, modalita, id);
		}
	}
	return db;
}

database modificaSingoloUtente(database db, int modalita, int id) {
	db_modificato=1;
	pulisciBuffer();
	int pos = ottieniPosDaID(db, -1, id);
	if (modalita==1) {
		char *username = malloc(MAX_MEDIO);
		printf("\nInserisci nuovo username: ");
		username = inputStringaSicuro(MAX_MEDIO,username);
		strcpy(db.utente[pos].username, username);
		free(username);
	} else if (modalita==2) {
		char *password_vecchia = malloc(MAX_MEDIO);
		strcpy(password_vecchia, "null");
		char *password = malloc(MAX_MEDIO);
		strcpy(password, "null");
		char *password2 = malloc(MAX_MEDIO);
		strcpy(password2, "null2");
		if (!isAdmin(db)) {
			while (strcmp(password_vecchia, db.utente[pos].password)!=0) {
				printf("\nInserisci password attuale: ");
				password_vecchia = inputStringaSicuro(MAX_MEDIO,password_vecchia);
				if (strcmp(password_vecchia, db.utente[pos].password)!=0)
					printf("\nLa password attuale non è corretta! Riprova\n");
			}
		}
		while (strcmp(password,password2)!=0) {
			printf("\nInserisci nuova password: ");
			password=inputStringaSicuro(MAX_MEDIO,password);
			printf("\nInserisci nuovamente la nuova password: ");
			password2=inputStringaSicuro(MAX_MEDIO,password2);
			if (strcmp(password,password2)!=0) {
				printf("\nLe due password non combaciano! Riprova\n");
			}
		}
		strcpy(db.utente[pos].password,password);
		free(password_vecchia); free(password); free(password2);
	} else if (modalita==3) {
		if (isAdmin(db)) {
			int ruolo=1;
			while (ruolo<0||ruolo>1) {
				printf("\nAmministratore[0] oppure Utente normale[1]? ");
				scanf("%d", &ruolo);
			}
			if (ruolo==0) {
				db.utente[pos].admin=true;
			} else if (ruolo==1) {
				db.utente[pos].admin=false;
			}
		} else {
			printf("\nNon puoi accedere a questa funzione in quanto utente normale.");
		}
	}
	return db;
}

database cancellaUtente(database db) {
	int id=0, controllo=0;
	char scelta='a';
	if (isAdmin(db)) {
		mostraTuttiUtenti(db);
		while (ottieniPosDaID(db, -1,id)==-1) {
			printf("\nInserisci id dell'utente: ");
			scanf("%d", &id);
			if (ottieniPosDaID(db, -1,id)==-1) {
				printf("\nNessun utente trovato, riprovare");
			}
		}
		printf("\nHai scelto l'utente: ");
		mostraSingoloUtente(db, 0, id);
	} else {
		id = db.utenteCorrente;
		mostraSingoloUtente(db, 0, id);
	}
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		db = cancellaSingoloUtente(db, id);
	}
	return db;
}

database cancellaSingoloUtente(database db, int id) {
	int n=contaNelDatabase(db,-1);
	int i=ottieniPosDaID(db, -1, id);
	while (i<n-1) {
		db.utente[i] = db.utente[i+1];
		i++;
	}
	db.utente[n-1].id = 0;

	int nplaylist=contaNelDatabase(db,4);
	i=0;
	while (i<nplaylist) {
		if (db.playlist[i].idUtente==id) {
			db = cancellaSingolaPlaylist(db, db.playlist[i].id);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
	return db;
}

