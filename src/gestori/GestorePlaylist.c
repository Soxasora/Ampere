/*
 * Ampere 0.2 rev. 12 -01.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
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
	int posplaylist=ottenerePosDaID(db, 4, idPlaylist);
	bool risultato=false;
	if (db.playlist[posplaylist].idUtente==idUtente)
		risultato=true;
	else
		risultato=false;
	return risultato;
}

bool isPublicPlaylist(database db, int idPlaylist) {
	int posplaylist = ottenerePosDaID(db, 4, idPlaylist);
	bool risultato=false;
	if (db.playlist[posplaylist].pubblica==true) {
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

struct playlists crearePlaylist(int idUtente, char nome[], char descrizione[], bool pubblica) {
	struct playlists nuovaPlaylist;
	nuovaPlaylist.idUtente = idUtente;
	strcpy(nuovaPlaylist.nome, nome);
	strcpy(nuovaPlaylist.descrizione, descrizione);
	nuovaPlaylist.pubblica = pubblica;
	return nuovaPlaylist;
}

void mostrareAnteprimaPlaylist(struct playlists nuovaPlaylist) {
	printf("\nLa playlist che stai per inserire ha questi dettagli:"
		   "\nNome: %s"
		   "\nDescrizione: %s"
		   "\nPrivacy: ", nuovaPlaylist.nome, nuovaPlaylist.descrizione);

	if (nuovaPlaylist.pubblica) {
		printf("Privata");
	} else if (!nuovaPlaylist.pubblica) {
		printf("Pubblica");
	}
}

database inserirePlaylist(database db, struct playlists nuovaPlaylist) {
	db_modificato=1;
	nuovaPlaylist.id = trovareUltimoId(db,4)+1;
	int n=contareNelDatabase(db,4);
	db.playlist[n] = nuovaPlaylist;
	return db;
}

database crearePlaylistGuidato(database db) {
	char scelta='a';
	int idUtente = db.utenteCorrente, controllo=0;
	char *nome;
	char *descrizione;
	int pubblica=-1;
	printf("\n===[Creazione guidata di una playlist]===");
	pulisciBuffer();
	if ((nome = malloc(MAX_MEDIO))) {
		printf("\nInserisci nome della playlist: ");
		nome = inputStringaSicuro(MAX_MEDIO,nome);
	}
	if ((descrizione = malloc(MAX_GRANDE))) {
		printf("\nInserisci descrizione della playlist: ");
		descrizione = inputStringaSicuro(MAX_GRANDE,descrizione);
	}
	while (pubblica<0||pubblica>1) {
		printf("\nLa playlist e' privata[0] o pubblica[1]? ");
		scanf("%d", &pubblica);
	}
	struct playlists nuovaPlaylist;
	if (pubblica==0) {
		nuovaPlaylist = crearePlaylist(idUtente, nome, descrizione, false);
	} else {
		nuovaPlaylist = crearePlaylist(idUtente, nome, descrizione, true);
	}
	free(nome); nome=NULL;
	free(descrizione); descrizione=NULL;
	//TODO
	mostrareAnteprimaPlaylist(nuovaPlaylist);
	db = inserirePlaylist(db, nuovaPlaylist);
	while (controllo!=-1) {
		pulisciBuffer();
		printf("\nVorresti inserire dei brani in questa playlist? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		db = inserimentoBraniPlaylistGuidato(db);
	}
	return db;
}

database inserimentoBraniPlaylistGuidato(database db) {
	pulisciBuffer();
	int scelta=-1, id=0, n=0, i=0, branoscelto=0, esito=0, controllo=0;
	int nbrani = contareNelDatabase(db,0);
	printf("\n===[Inserimento guidato di brani in una playlist]===");
	printf("\nScegli la playlist da modificare: ");
	mostraPlaylistUtente(db, -1,db.utenteCorrente);
	while (isUserPlaylist(db, id, db.utenteCorrente)==false||ottenerePosDaID(db, 4,id)==-1) {
		printf("\nInserisci id della playlist: ");
		scanf("%d", &id);
		if (isUserPlaylist(db, id, db.utenteCorrente)==false)
			printf("\nL'identificativo che hai dato punta ad una playlist che non ti appartiene, riprova.");
		else if (ottenerePosDaID(db, 4,id)==-1)
			printf("\nNessuna playlist trovata, riprovare");
	}
	printf("\nInserisci fino a %d brani nella playlist %s", nbrani, db.playlist[ottenerePosDaID(db, 4,id)].nome);
	while (n<1||n>nbrani) {
		printf("\nQuanti brani vuoi inserire? ");
		scanf("%d", &n);
	}
	int idbrani[n];
	i=0;
	while (i<n) {
		branoscelto=0;
		while (controllo!=-1) {
			while (scelta<0||scelta>5) {
				printf("\nCerca per titolo[0], anno[1], artista[2], album[3], genere[4] oppure id[5]: ");
				scanf("%d", &scelta);
			}
			if (scelta==0) {
				esito = mostraBrani(db, 0);
				controllo=-1;
			} else if (scelta==1) {
				esito = mostraBrani(db, 1);
				controllo=-1;
			} else if (scelta==2) {
				esito = mostraBraniArtista(db);
				controllo=-1;
			} else if (scelta==3) {
				esito = mostraBraniAlbum(db);
				controllo=-1;
			} else if (scelta==4) {
				esito = mostraBraniGenere(db);
				controllo=-1;
			} else if (scelta==5) {
				printf("\nInserimento diretto dell'id");
			}
		}
		while (ottenerePosDaID(db, 0,branoscelto)==-1&&esito==1) {
			printf("\nInserire id del brano da inserire nella playlist: ");
			scanf("%d", &branoscelto);
			if (ottenerePosDaID(db, 0,branoscelto)==-1) {
				printf("\nBrano non trovato, riprova");
			} else {
				idbrani[i] = branoscelto;
			}
		}
		i++;
	}

	i=0;
	while (i<n) {
		db = inserireAssociazionePlaylist(db, creaAssociazionePlaylist(id, idbrani[i]));
		i++;
	}

	printf("\nBrani inseriti nella playlist %s", db.playlist[ottenerePosDaID(db, 4, id)].nome);
	return db;
}

void inserisciPlaylistSuFile(struct playlists playlist, char pubblica[]) {
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

database modificaPlaylist(database db) {
	int id=0, modalita=-1, controllo=0;
	char scelta='a';
	if (controllareSeAdmin(db)) {
		mostraTuttePlaylist(db, -1);
	} else {
		mostraPlaylistUtente(db, -1, db.utenteCorrente);
	}
	while (isUserPlaylist(db, id, db.utenteCorrente)==false||ottenerePosDaID(db, 4,id)==-1) {
		printf("\nInserisci id della playlist da modificare: ");
		scanf("%d", &id);
		if (isUserPlaylist(db, id, db.utenteCorrente)==false||!controllareSeAdmin(db))
			printf("\nL'identificativo che hai dato punta ad una playlist che non ti appartiene, riprova.");
		else if (ottenerePosDaID(db, 4,id)==-1)
			printf("\nNessuna playlist trovata, riprovare");
	}
	printf("\nHai scelto la playlist");
	mostraSingolaPlaylist(db, -1, id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica playlist]===");
		printf("\n[1] Modifica il nome");
		printf("\n[2] Modifica la descrizione");
		printf("\n[3] Modifica la privacy");
		if (controllareSeAdmin(db))
			printf("\n[4] Modifica l'autore della playlist");
		printf("\n[0] Esci");
		while (modalita<0||modalita>4) {
			printf("\nInserisci la scelta: ");
			scanf("%d", &modalita);
		}
		if (modalita!=0) {
			db = modificaSingolaPlaylist(db, modalita, id);
		}
	}
	return db;
}

database modificaSingolaPlaylist(database db, int modalita, int id) {
	pulisciBuffer();
	int pos = ottenerePosDaID(db, 4,id);
	if (modalita==1) {
		char *nome = malloc(MAX_MEDIO);
		printf("\nInserisci nuovo nome: ");
		nome = inputStringaSicuro(MAX_MEDIO,nome);
		strcpy(db.playlist[pos].nome, nome);
		free(nome);
	} else if (modalita==2) {
		char *descrizione = malloc(MAX_GRANDE);
		printf("\nInserisci nuova descrizione: ");
		descrizione = inputStringaSicuro(MAX_GRANDE,descrizione);
		strcpy(db.playlist[pos].descrizione, descrizione);
		free(descrizione);
	} else if (modalita==3) {
		int pubblica=-1;
		while (pubblica<0||pubblica>1) {
			printf("\nPlaylist privata[0] o pubblica[1]? ");
			scanf("%d", &pubblica);
		}
		if (pubblica==0) {
			db.playlist[pos].pubblica = false;
		} else {
			db.playlist[pos].pubblica = true;
		}
	} else if (modalita==4) {
		if (controllareSeAdmin(db)) {
			int idutente=0;
			while (ottenerePosDaID(db, -1,idutente)==-1) {
				printf("\nInserisci id del nuovo autore: ");
				scanf("%d", &idutente);
				if (ottenerePosDaID(db, -1,idutente)==-1) {
					printf("\nNessun utente trovato, riprovare");
				}
			}
			db.playlist[pos].idUtente = idutente;
		} else {
			errore(16);
		}
	}
	db_modificato=1;
	printf("Playlist aggiornata, ecco il risultato:\n");
	mostraSingolaPlaylist(db, -1,id);
	return db;
}

database cancellaPlaylist(database db) {
	int id=0, controllo=0;
	char scelta='a';
	if (controllareSeAdmin(db)) {
		mostraTuttePlaylist(db, -1);
	} else {
		mostraPlaylistUtente(db, -1, db.utenteCorrente);
	}
	while (isUserPlaylist(db, id, db.utenteCorrente)==false||ottenerePosDaID(db, 4,id)==-1) {
		printf("\nInserisci id della playlist: ");
		scanf("%d", &id);
		if (isUserPlaylist(db, id, db.utenteCorrente)==false||!controllareSeAdmin(db))
			printf("\nL'identificativo che hai dato punta ad una playlist che non ti appartiene, riprova.");
		else if (ottenerePosDaID(db, 4,id)==-1)
			printf("\nNessuna playlist trovata");
	}
	printf("\nHai scelto la playlist: ");
	mostraSingolaPlaylist(db, -1, id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
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

	int nassociazioni = contareNelDatabase(db,8);
	i=0;
	while (i<nassociazioni) {
		if (db.playlistBrano[i].idPlaylist==id) {
			db = cancellaAssociazionePlaylist(db, id);
			i=-1;
		}
		i++;
	}

	db_modificato=1;
	printf("\nPlaylist cancellata.");
	return db;
}

database cancellaAssociazionePlaylist(database db, int id) {
	int n=contareNelDatabase(db,8);
	int i=ottenerePosDaID(db, 8, id);
	while (i<n-1) {
		db.playlistBrano[i] = db.playlistBrano[i+1];
		i++;
	}
	db.playlistBrano[n-1].idPlaylist = 0;
	db.playlistBrano[n-1].idBrano = 0;
	db_modificato=1;
	return db;
}
