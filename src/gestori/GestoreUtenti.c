/*
 * UNIBA/Ampere 1.0
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
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
#include "../sys/Messaggi.h"
#include "../Ampere.h"

bool controllareSeAdmin(database db) {
	bool risultato=false;
	int pos=ottenerePosDaID(db, -1,db.utenteCorrente);
	risultato = db.utente[pos].admin;
	return risultato;
}

bool controllareSeAdminUtente(database db, int id) {
	bool risultato=false;
	risultato = db.utente[ottenerePosDaID(db, -1, id)].admin;
	return risultato;
}

bool controllareSePrescelto(database db) {
	bool risultato=false;
	if (contareNelDatabase(db, -1)==0) {
		risultato=true;
	}
	return risultato;
}

void infoUtenteConnesso(database db) {
	int posUtente = ottenerePosDaID(db, -1, db.utenteCorrente);
	printf("\n===[Informazioni Utente Connesso]==="
		   "\nNome Utente: %s"
		   "\nRuolo Utente: ", db.utente[posUtente].username);
	if (controllareSeAdmin(db)==true) {
		printf(COLOR_ADMIN"\n");
	} else {
		printf(COLOR_UTENTE"\n");
	}
}

database loginUtente(database db) {
	printf("\nEsecuzione Login ad Ampere");
	int controllo=0, id=0;
	char *username;
	char *password;
	while (controllo!=-1) {
		
		if ((username = calloc(MAX_MEDIO, sizeof(char)))) {
			printf("\nInserisci "C_GIALLO"username: "C_RESET);
			username = inputStringa(MAX_MEDIO,username);
		}
		if ((password = calloc(MAX_MEDIO, sizeof(char)))) {
			printf("\nInserisci "C_GIALLO"password: "C_RESET);
			password = inputStringa(MAX_MEDIO,password);
		}
		id = controllareDatiUtente(db, username, password);
		if (strcmp(username, "N/A")==0||strcmp(password, "N/A")==0) {
			attenzione(2);
		} else if (id!=0) {
			db.utenteCorrente = id;
			printf("\n"C_VERDE"Accesso consentito."C_RESET" Bentornato su Ampere, %s.", db.utente[ottenerePosDaID(db, -1, db.utenteCorrente)].username);
			controllo=-1;
		} else {
			attenzione(1);
		}
		free(username); username=NULL;
		free(password); password=NULL;
	}
	return db;
}

int controllareDatiUtente(database db, char username[], char password[]) {
	int n = contareNelDatabase(db,-1), i=0, controllo=0, id=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.utente[i].username, username)==0 && strcmp(db.utente[i].password, password)==0) {
			id = db.utente[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

database registrareUtente(database db) {
	
	char scelta='a';
	int ruolo=-1;
	bool admin = false;
	if (controllareSePrescelto(db)) {
		printf("\nSei il primo utente di Ampere."
			   "\nAvrai poteri sovrannaturali: potrai creare, trasformare e distruggere il database."
			   "\nProcediamo alla creazione del tuo profilo, "COLOR_ADMIN".");
		admin = true;
	} else if (!controllareSeAdmin(db)||db.utenteCorrente==0) {
		printf("\n===[Registrazione guidata di un utente]===");
		printf("\nBenvenuto su Ampere. Procediamo alla creazione del tuo profilo.");
	}
	do {
		
		char *username;
		char *password;
		if ((username = calloc(MAX_MEDIO, sizeof(char)))) {
			printf("\nInserisci "C_GIALLO"username: "C_RESET);
			username = inputStringa(MAX_MEDIO,username);
		}
		if ((password = calloc(MAX_MEDIO, sizeof(char)))) {
			printf("\nInserisci "C_GIALLO"password: "C_RESET);
			password = inputStringa(MAX_MEDIO,password);
		}
		if (strcmp(username,"N/A")==0||strcmp(password,"N/A")==0) {
			attenzione(2);
			db.ultimoEsito=-1;
		} else if (controllareEsistenzaUtente(db, username)==false) {
			if (controllareSeAdmin(db)) {
				while (ruolo<0||ruolo>1) {
					printf("\nRuolo normale[0] o admin[1]? ");
					ruolo = inputNumero();
				}
				if (ruolo==0) {
					admin=false;
				} else {
					admin=true;
				}
			}
			struct Utente nuovoUtente = creareUtente(username, password, admin);
			mostrareAnteprimaUtente(nuovoUtente);
			scelta = richiesta(0);
			if (scelta=='Y'||scelta=='y') {
				db = inserireUtente(db, nuovoUtente);
				if (admin) {
					inserireUtenteSuFile(db.utente[contareNelDatabase(db,-1)-1], "true");
				} else {
					inserireUtenteSuFile(db.utente[contareNelDatabase(db,-1)-1], "false");
				}
				db.ultimoEsito = 0;
			} else {
				db.ultimoEsito = -1;
			}
		} else {
			attenzione(0);
			db.ultimoEsito = -1;
		}
		free(username); username=NULL;
		free(password); password=NULL;
	} while (db.ultimoEsito!=0);
	if (!controllareSeAdmin(db)||db.utenteCorrente==0) {
		db = loginUtente(db);
	}
	return db;
}

struct Utente creareUtente(char username[], char password[], bool admin) {
	struct Utente nuovoUtente;
	nuovoUtente.id = -1;
	strcpy(nuovoUtente.username, username);
	strcpy(nuovoUtente.password, password);
	nuovoUtente.admin = admin;
	return nuovoUtente;
}

void mostrareAnteprimaUtente(struct Utente nuovoUtente) {
	printf("\nStai per registrare un utente con questi dettagli:"
		   "\nNome Utente: %s"
		   "\nPassword: %s", nuovoUtente.username, nuovoUtente.password);
	if (nuovoUtente.admin) {
		printf("\nRuolo: Amministratore");
	} else {
		printf("\nRuolo: Utente normale");
	}
}

database inserireUtente(database db, struct Utente nuovoUtente) {
	db_modificato=1;
	nuovoUtente.id = trovareUltimoId(db, -1)+1;
	int n=contareNelDatabase(db,-1);
	db.utente[n] = nuovoUtente;
	successo(0);
	return db;
}

bool controllareEsistenzaUtente(database db, char username[]) {
	int i=0, n=contareNelDatabase(db,-1), controllo=0;
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

void inserireUtenteSuFile(struct Utente utente, char admin[]) {
	FILE* fp=fopen(file_utenti, "a");
	if (controllaSeFileVuoto(file_utenti)==1) {
		fprintf(fp, "%d|%s|%s|%s", utente.id, utente.username, utente.password, admin);
	} else {
		fprintf(fp, "\n%d|%s|%s|%s", utente.id, utente.username, utente.password, admin);
	}
	fclose(fp);
}

database modificareUtenteGuidato(database db) {
	int id=0, campo=-1, esiste=0;
	char scelta='a';
	if (controllareSeAdmin(db)) {
		do {
			esiste = mostraInfo(db, 4);
			if (esiste==0) {
				attenzione(101);
			}
		} while (esiste==0);
		while (ottenerePosDaID(db, -1,id)==-1) {
			printf("\n\nInserisci id dell'utente da modificare: ");
			id = inputNumero();
			if (ottenerePosDaID(db, -1,id)==-1) {
				printf("\nNessun utente trovato, riprovare");
			}
		}
		printf("\nHai scelto l'utente");
		mostraSingoloUtente(db, 0, id);
	} else {
		mostraSingoloUtente(db, 1,db.utenteCorrente);
		id = db.utenteCorrente;
	}
	
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		do {
			printf("\n===[Sistema di modifica utente]===");
			printf("\n[1] Modifica l'username");
			printf("\n[2] Modifica la password");
			if (controllareSeAdmin(db))
				printf("\n[3] Modifica il ruolo");
			printf("\n[0] Esci");
			while (campo<0||campo>3) {
				printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
				campo = inputNumero();
			}
			if (campo!=0) {
				db = creareUtenteModificato(db, campo, id);
				if (db.ultimoEsito==0) {
					printf("\nUtente modificato.");
				}
			} else {
				db.ultimoEsito=-2;
			}
		} while (db.ultimoEsito==-1);
	}
	return db;
}

database creareUtenteModificato(database db, int campo, int id) {
	char scelta='a';
	int pos = ottenerePosDaID(db, -1, id);
	struct Utente utenteModificato = db.utente[pos];
	do {
		
		if (campo==1) {
			char *username = calloc(MAX_MEDIO, sizeof(char));
			printf("\nInserisci nuovo username: ");
			username = inputStringa(MAX_MEDIO,username);
			strcpy(utenteModificato.username, username);
			free(username);
		} else if (campo==2) {
			char *passwordVecchia = calloc(MAX_MEDIO, sizeof(char));
			strcpy(passwordVecchia, "null");
			char *password = calloc(MAX_MEDIO, sizeof(char));
			strcpy(password, "null");
			char *password2 = calloc(MAX_MEDIO, sizeof(char));
			strcpy(password2, "null2");
			if (!controllareSeAdmin(db)) {
				while (strcmp(passwordVecchia, utenteModificato.password)!=0) {
					printf("\nInserisci password attuale: ");
					passwordVecchia = inputStringa(MAX_MEDIO,passwordVecchia);
					if (strcmp(passwordVecchia, utenteModificato.password)!=0)
						printf("\nLa password attuale non è corretta! Riprova\n");
				}
			}
			while (strcmp(password,password2)!=0) {
				printf("\nInserisci nuova password: ");
				password=inputStringa(MAX_MEDIO,password);
				printf("\nInserisci nuovamente la nuova password: ");
				password2=inputStringa(MAX_MEDIO,password2);
				if (strcmp(password,password2)!=0) {
					printf("\nLe due password non combaciano! Riprova\n");
				}
			}
			strcpy(utenteModificato.password,password);
		} else if (campo==3) {
			if (controllareSeAdmin(db)) {
				int ruolo=1;
				while (ruolo<0||ruolo>1) {
					printf("\nAmministratore[0] oppure Utente normale[1]? ");
					ruolo = inputNumero();
				}
				if (ruolo==0) {
					utenteModificato.admin=true;
				} else if (ruolo==1) {
					utenteModificato.admin=false;
				}
			} else {
				errore(16);
			}
		}
		printf("\nUtente ORIGINALE: ");
		mostraSingoloUtente(db, -1, id);
		printf("\n");
		mostrareAnteprimaUtente(utenteModificato);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			db = modificareUtente(db, id, utenteModificato);
			db.ultimoEsito=0;
		} else {
			scelta = richiesta(3);
			if (scelta=='Y'||scelta=='y') {
				db.ultimoEsito=-2;
			} else {
				db.ultimoEsito=-1;
			}
		}
	} while (db.ultimoEsito==-2);
	return db;
}

database modificareUtente(database db, int idUtente, struct Utente utenteModificato) {
	int posUtente = ottenerePosDaID(db, -1, idUtente);
	db.utente[posUtente] = utenteModificato;
	db_modificato=1;
	return db;
}

database cancellareUtenteGuidato(database db) {
	int id=0;
	char scelta='a';
	if (controllareSeAdmin(db)) {
		mostraTuttiUtenti(db);
		while (ottenerePosDaID(db, -1,id)==-1) {
			printf("\n\nInserisci id dell'utente: ");
			id = inputNumero();
			if (ottenerePosDaID(db, -1,id)==-1) {
				printf("\nNessun utente trovato, riprovare");
			}
		}
		printf("\nHai scelto l'utente: ");
		mostraSingoloUtente(db, 0, id);
	} else {
		id = db.utenteCorrente;
		mostraSingoloUtente(db, 0, id);
	}
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		db = cancellareUtente(db, id);
		printf("\nPer rendere effettive le modifiche, ora chiudero' Ampere.");
		aspetta();
		terminazione(db);
		exit(0);
	} else {
		printf("\nNessuna modifica effettuata.");
	}
	return db;
}

database cancellareUtente(database db, int id) {
	int n=contareNelDatabase(db,-1);
	int i=ottenerePosDaID(db, -1, id);
	while (i<n-1) {
		db.utente[i] = db.utente[i+1];
		i++;
	}
	db.utente[n-1].id = 0;

	int nPlaylist=contareNelDatabase(db,4);
	i=0;
	while (i<nPlaylist) {
		if (db.playlist[i].idUtente==id) {
			db = cancellaSingolaPlaylist(db, db.playlist[i].id);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
	return db;
}

