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
#include "../gestori/GestoreAssociazioni.h"
#include "../gestori/GestorePlaylist.h"
#include "../gestori/GestoreUtenti.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreGeneri.h"
#include "../ricerca/RicercaGenerale.h"
#include "../ricerca/MotoreRicerca.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"
#include "../sys/Messaggi.h"

bool isUserPlaylist(database db, int idPlaylist, int idUtente) {
	int posPlaylist=ottenerePosDaID(db, 4, idPlaylist);
	bool risultato=false;
	if (posPlaylist!=-1) {
		if (db.playlist[posPlaylist].idUtente==idUtente)
			risultato=true;
		else
			risultato=false;
	}
	return risultato;
}

bool isPublicPlaylist(database db, int idPlaylist) {
	int posPlaylist = ottenerePosDaID(db, 4, idPlaylist);
	bool risultato=false;
	if (db.playlist[posPlaylist].pubblica==true) {
		risultato=true;
	} else {
		risultato=false;
	}
	return risultato;
}

int contaPlaylistUtente(database db, int idUtente) {
	int i=0, n=contareNelDatabase(db,4), conta=0;
	while (i<n) {
		if (db.playlist[i].idUtente==idUtente) {
			conta++;
		}
		i++;
	}
	return conta;
}

int contaBraniPlaylist(database db, int idPlaylist) {
	int i=0, n=contareNelDatabase(db,8), conta=0;
	while (i<n) {
		if (db.playlistBrano[i].idPlaylist==idPlaylist) {
			conta++;
		}
		i++;
	}
	return conta;
}

struct Playlist crearePlaylist(int idUtente, char nome[], char descrizione[], bool pubblica) {
	struct Playlist nuovaPlaylist;
	nuovaPlaylist.idUtente = idUtente;
	strcpy(nuovaPlaylist.nome, nome);
	strcpy(nuovaPlaylist.descrizione, descrizione);
	nuovaPlaylist.pubblica = pubblica;
	return nuovaPlaylist;
}

void mostrareAnteprimaPlaylist(struct Playlist nuovaPlaylist) {
	printf("\nLa playlist che stai per inserire ha questi dettagli:"
		   "\nNome: %s"
		   "\nDescrizione: %s"
		   "\nPrivacy: ", nuovaPlaylist.nome, nuovaPlaylist.descrizione);

	if (!nuovaPlaylist.pubblica) {
		printf("Privata");
	} else if (nuovaPlaylist.pubblica) {
		printf("Pubblica");
	}
}

database inserirePlaylist(database db, struct Playlist nuovaPlaylist) {
	db_modificato=1;
	nuovaPlaylist.id = trovareUltimoId(db,4)+1;
	int n=contareNelDatabase(db,4);
	db.playlist[n] = nuovaPlaylist;
	return db;
}

database crearePlaylistGuidato(database db) {
	char scelta='a';
	int idUtente = db.utenteCorrente;
	char *nome;
	char *descrizione;
	int pubblica=-1;
	do {
		printf("\n===[Creazione guidata di una playlist]===");
			do {
				if ((nome = malloc(MAX_MEDIO))) {
					printf("\nInserisci nome della playlist: ");
					nome = inputStringa(MAX_MEDIO,nome);
				}
				if (strcmp(nome, "N/A")==0) {
					attenzione(2);
				}
			} while (strcmp(nome, "N/A")==0);
			if ((descrizione = malloc(MAX_GRANDE))) {
				printf("\nInserisci descrizione della playlist: ");
				descrizione = inputStringa(MAX_GRANDE,descrizione);
				if (strcmp(descrizione, "N/A")==0) {
					strcpy(descrizione, "Playlist creata con Ampere");
				}
			}
			while (pubblica<0||pubblica>1) {
				printf("\nLa playlist e' privata[0] o pubblica[1]? ");
				pubblica = inputNumero();
			}
			struct Playlist nuovaPlaylist;
			if (pubblica==0) {
				nuovaPlaylist = crearePlaylist(idUtente, nome, descrizione, false);
			} else {
				nuovaPlaylist = crearePlaylist(idUtente, nome, descrizione, true);
			}
			free(nome); nome=NULL;
			free(descrizione); descrizione=NULL;
			//TODO
			mostrareAnteprimaPlaylist(nuovaPlaylist);
			scelta = richiesta(0);
			if (scelta=='Y'||scelta=='y') {
				db = inserirePlaylist(db, nuovaPlaylist);
				scelta = richiesta(7);
				if (scelta=='Y'||scelta=='y') {
					db = inserimentoBraniPlaylistGuidato(db);
				}
				db.ultimoEsito=0;
			} else {
				db.ultimoEsito=-1;
			}

	} while (db.ultimoEsito!=0);

	return db;
}

database inserimentoBraniPlaylistGuidato(database db) {
	
	int id=0, i=0, j=0, branoscelto=0, controllo=0, esito=0;
	char scelta='a';
	int nBrani = contareNelDatabase(db,0);
	printf("\n===[Inserimento guidato di brani in una playlist]==="
		   "\nScegli la playlist da modificare: ");
	mostraPlaylistUtente(db, -1,db.utenteCorrente);
	do {
		printf("\nInserisci id della playlist: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 4,id)==-1) {
			printf("\nNessuna playlist trovata, riprovare");
			esito=-1;
		} else if (isUserPlaylist(db, id, db.utenteCorrente)==false) {
			printf("\nL'identificativo che hai dato punta ad una playlist che non ti appartiene, riprova.");
			esito=-1;
		}
	} while (esito==-1);

	printf("\nInserisci fino a %d brani nella playlist %s", nBrani, db.playlist[ottenerePosDaID(db, 4,id)].nome);
	int* idbrani = calloc(nBrani, sizeof(int));

	i=0;
	do {
		branoscelto=0;
		db = moduloRicercaBrani(db);
		if (db.ultimoEsito==-1) {
			scelta = richiesta(1);
			if (scelta=='Y'||scelta=='y') {
				printf("\nContinuo con l'inserimento dei brani.");
				db.ultimoEsito=0;
			} else {
				printf("\nUscito dall'inserimento dei brani.");
			}
		}
		if (db.ultimoEsito==1) {
			do {
				printf("\nInserire l'identificativo del brano da inserire nella playlist, altrimenti [-1] per cercare di nuovo: ");
				branoscelto = inputNumero();
				if (branoscelto==-1) {
					db.ultimoEsito=2;
				} else {
					if (ottenerePosDaID(db, 0, branoscelto)==-1) {
						printf("\nBrano non trovato, riprova");
						db.ultimoEsito=0;
					} else {
						int n = contareNelDatabase(db, 8);
						j=0, controllo=0;
						while (j<n&&controllo!=-1) {
							if (db.playlistBrano[j].idPlaylist==id && db.playlistBrano[j].idBrano==branoscelto) {
								printf("\nBrano gia' presente nella playlist, riprova");
								controllo=-1;
								db.ultimoEsito=0;
							} else {
								db.ultimoEsito=1;
							}
							j++;
						}
					}
				}
				if (db.ultimoEsito==1) {
					idbrani[i] = branoscelto;
					i++;
				}
			} while (db.ultimoEsito==0);
		}
	} while (i<nBrani&&db.ultimoEsito!=-1);


	if (idbrani[0]==0) {
		printf("\nNessun brano inserito.");
	} else {
		i=0;
		while(idbrani[i]!=0) {
			db = inserireAssociazionePlaylist(db, creaAssociazionePlaylist(id, idbrani[i]));
			i++;
		}
		printf("\nBrani inseriti nella playlist %s", db.playlist[ottenerePosDaID(db, 4, id)].nome);
	}
	return db;
}

void inserisciPlaylistSuFile(struct Playlist playlist, char pubblica[]) {
	FILE* fp=fopen(file_playlists,"a");
	if (controllaSeFileVuoto(file_playlists)==1) {
		fprintf(fp, "%d|%d|%s|%s|%s", playlist.id, playlist.idUtente, playlist.nome, playlist.descrizione, pubblica);
	} else {
		fprintf(fp, "\n%d|%d|%s|%s|%s", playlist.id, playlist.idUtente, playlist.nome, playlist.descrizione, pubblica);
	}
	fclose(fp);
}


int controlloEsistenzaPlaylist(database db, char playlist[]) {
	int id=0, i=0, n=contareNelDatabase(db,4), controllo=0;
	while(i<n&&controllo!=-1) {
		if (comparaStringhe(db.playlist[i].nome, playlist)==0) {
			id = db.playlist[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

database modificarePlaylistGuidato(database db) {
	int id=0, campo=-1, esiste=0, esito=0;
	char scelta='a';
	do {
		esiste = mostraInfo(db, 3);
		if (esiste==0) {
			attenzione(101);
		}
	} while (esiste==0);
	do {
		printf("\nInserisci id della playlist da modificare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 4,id)==-1) {
			printf("\nNessuna playlist trovata, riprovare");
			esito=-1;
		} else if (isUserPlaylist(db, id, db.utenteCorrente)==false||!controllareSeAdmin(db)) {
			printf("\nL'identificativo che hai dato punta ad una playlist che non ti appartiene, riprova.");
			esito=-1;
		}
	} while (esito==-1);
	printf("\nHai scelto la playlist");
	mostraSingolaPlaylist(db, -1, id);
	
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		do {
			printf("\n===[Sistema di modifica playlist]===");
			printf("\n[1] Modifica il nome");
			printf("\n[2] Modifica la descrizione");
			printf("\n[3] Modifica la privacy");
			if (controllareSeAdmin(db))
				printf("\n[4] Modifica l'autore della playlist");
			printf("\n[0] Esci");
			while (campo<0||campo>4) {
				printf("\nInserisci la scelta: ");
				campo = inputNumero();
			}
			if (campo!=0) {
				db = crearePlaylistModificata(db, campo, id);
				if (db.ultimoEsito==0) {
					printf("\nPlaylist modificata.");
				}
			} else {
				db.ultimoEsito=-2;
			}
		} while (db.ultimoEsito==-1);
	}
	return db;
}

database crearePlaylistModificata(database db, int campo, int id) {
	
	char scelta='a';
	int pos = ottenerePosDaID(db, 4,id);
	struct Playlist playlistModificata = db.playlist[pos];
	do {
		if (campo==1) {
			char *nome = malloc(MAX_MEDIO);
			printf("\nInserisci nuovo nome: ");
			nome = inputStringa(MAX_MEDIO,nome);
			strcpy(playlistModificata.nome, nome);
			free(nome);
		} else if (campo==2) {
			char *descrizione = malloc(MAX_GRANDE);
			printf("\nInserisci nuova descrizione: ");
			descrizione = inputStringa(MAX_GRANDE,descrizione);
			strcpy(playlistModificata.descrizione, descrizione);
			free(descrizione);
		} else if (campo==3) {
			int pubblica=-1;
			while (pubblica<0||pubblica>1) {
				printf("\nPlaylist privata[0] o pubblica[1]? ");
				pubblica = inputNumero();
			}
			if (pubblica==0) {
				playlistModificata.pubblica = false;
			} else {
				playlistModificata.pubblica = true;
			}
		} else if (campo==4) {
			if (controllareSeAdmin(db)) {
				int idUtente=0, esiste=0;
				do {
					esiste = mostraInfo(db, 4);
					if (esiste==0) {
						attenzione(101);
					}
				} while (esiste==0);
				while (ottenerePosDaID(db, -1,idUtente)==-1) {
					printf("\nInserisci id del nuovo autore: ");
					idUtente = inputNumero();
					if (ottenerePosDaID(db, -1,idUtente)==-1) {
						printf("\nNessun utente trovato, riprovare");
					}
				}
				playlistModificata.idUtente = idUtente;
			} else {
				errore(16);
			}
		}
		printf("\nPlaylist ORIGINALE:");
		mostraSingolaPlaylist(db, -1, id);
		printf("\n");
		mostrareAnteprimaPlaylist(playlistModificata);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			db = modificarePlaylist(db, id, playlistModificata);
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

database modificarePlaylist(database db, int idPlaylist, struct Playlist playlistModificata) {
	int posPlaylist = ottenerePosDaID(db, 4, idPlaylist);
	db.playlist[posPlaylist] = playlistModificata;
	db_modificato=1;
	return db;
}

database cancellaPlaylist(database db) {
	int id=0, esito=0;
	char scelta='a';
	if (controllareSeAdmin(db)) {
		mostraTuttePlaylist(db, -1);
	} else {
		mostraPlaylistUtente(db, -1, db.utenteCorrente);
	}
	do {
		printf("\nInserisci id della playlist: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 4,id)==-1) {
			printf("\nNessuna playlist trovata, riprovare");
			esito=-1;
		} else if (isUserPlaylist(db, id, db.utenteCorrente)==false||!controllareSeAdmin(db)==false) {
			printf("\nL'identificativo che hai dato punta ad una playlist che non ti appartiene, riprova.");
			esito=-1;
		}
	} while (esito==-1);
	printf("\nHai scelto la playlist: ");
	mostraSingolaPlaylist(db, -1, id);
	scelta = richiesta(0);
	if(scelta=='Y'||scelta=='y') {
		db = cancellaSingolaPlaylist(db, id);
	}
	return db;
}

database cancellaSingolaPlaylist(database db, int id) {
	int n=contareNelDatabase(db,4);
	int i=ottenerePosDaID(db, 4, id);
	while (i<n-1) {
		db.playlist[i] = db.playlist[i+1];
		i++;
	}
	db.playlist[n-1].id = 0;

	int nAssociazioni = contareNelDatabase(db,8);
	i=0;
	while (i<nAssociazioni) {
		if (db.playlistBrano[i].idPlaylist==id) {
			db = cancellaAssociazioniPlaylist(db, id);
			i=-1;
		}
		i++;
	}

	db_modificato=1;
	printf("\nPlaylist cancellata.");
	return db;
}
