/*
 * Ampere 0.2.1 rev.1 - 04.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestorePlaylist.h"
#include "../gestori/GestoreUtenti.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreGeneri.h"
#include "../ricerca/MotoreRicerca.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Messaggi.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void mostraSingoloBrano(database db, int id) {
	int posBrano = ottenerePosDaID(db, 0,id);
	printf("\nIdentificativo: %d"
		   "\nTitolo: %s"
		   "\nDurata: %s", db.brano[posBrano].id, db.brano[posBrano].titolo, convertiSecondiInTempo(db.brano[posBrano].durata));
	mostrareAssociazioni(db, 0, id);
	mostrareAssociazioni(db, 1, id);
	mostrareAssociazioni(db, 2, id);
	printf("\nAnno: %d"
		   "\nAscolti: %d", db.brano[posBrano].anno, db.brano[posBrano].ascolti);
}

void mostrareAssociazioni(database db, int modalita, int idBrano) {
	int i=0;
	if (modalita==0) { // Artisti
		printf("\nArtisti: ");
		int *posArtisti=ottenerePosAssociazioniDaID(db, 5, idBrano);
		i=0;
		do {
			int posArtista = ottenerePosDaID(db, 2, db.branoArtista[posArtisti[i]].idArtista);
			if (i!=0)
				printf(", ");
			printf("%s", db.artista[posArtista].nomeArte);
			i++;
		} while (posArtisti[i]!=0);
	} else if (modalita==1) { // Album
		printf("\nAlbum: ");
		int *posAlbums=ottenerePosAssociazioniDaID(db, 6, idBrano);
		i=0;
		do {
			int posAlbum = ottenerePosDaID(db, 1, db.branoAlbum[posAlbums[i]].idAlbum);
			if (i!=0)
				printf(", ");
			printf("%s", db.album[posAlbum].titolo);
			i++;
		} while (posAlbums[i]!=0);
	} else if (modalita==2) { // Generi
		printf("\nGeneri: ");
		int *posGeneri=ottenerePosAssociazioniDaID(db, 7, idBrano);
		i=0;
		do {
			int posGenere = ottenerePosDaID(db, 3, db.branoGenere[posGeneri[i]].idGenere);
			if (i!=0)
				printf(", ");
			printf("%s", db.genere[posGenere].nome);
			i++;
		} while (posGeneri[i]!=0);
	}
}

void mostraTuttiBrani(database db) {
	int nBrani = contareNelDatabase(db,0);
	int i=0, controllo=0;
	if (nBrani==0) {
		printf("\nNessun brano presente nel database.");
	} else {
		while (i<nBrani&&controllo!=-1) {
			printf("\n");
			mostraSingoloBrano(db, db.brano[i].id);
			if ((nBrani+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				scelta = richiesta(8);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			i++;
		}
	}
}

void mostraSingoloAlbum(database db, int id) {
	int posAlbum = ottenerePosDaID(db, 1, id);
	printf("\nIdentificativo: %d", db.album[posAlbum].id);
	printf("\nTitolo: %s", db.album[posAlbum].titolo);
	printf("\nAnno di uscita: %d", db.album[posAlbum].anno);
}

void mostraTuttiAlbum(database db) {
	int i=0, nAlbum=contareNelDatabase(db,1), controllo=0;
	if (nAlbum==0) {
		printf("\nNessun album presente nel database.");
	} else {
		while(i<nAlbum&&controllo!=-1) {
			printf("\n");
			mostraSingoloAlbum(db, db.album[i].id);
			if ((nAlbum+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				scelta = richiesta(9);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			i++;
		}
	}
}

void mostraSingoloArtista(database db, int id) {
	int posArtista = ottenerePosDaID(db, 2, id);
	printf("\nIdentificativo: %d", db.artista[posArtista].id);
	printf("\nNome: %s", db.artista[posArtista].nome);
	printf("\nCognome: %s", db.artista[posArtista].cognome);
	printf("\nNome d'arte: %s", db.artista[posArtista].nomeArte);
	printf("\nLink biografia: %s", db.artista[posArtista].linkBio);
}

void mostraTuttiArtisti(database db) {
	int i=0, nArtisti=contareNelDatabase(db,2), controllo=0;
	if (nArtisti==0) {
		printf("\nNessun artista presente nel database.");
	} else {
		while(i<nArtisti&&controllo!=-1) {
			printf("\n");
			mostraSingoloArtista(db, db.artista[i].id);
			if ((nArtisti+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				scelta = richiesta(10);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			i++;
		}
	}
}

void mostraSingoloGenere(database db, int id) {
	int posGenere = ottenerePosDaID(db, 3, id);
	printf("\nIdentificativo: %d", db.genere[posGenere].id);
	printf("\nNome: %s", db.genere[posGenere].nome);
}

void mostraTuttiGeneri(database db) {
	int i=0, nGeneri=contareNelDatabase(db,3), controllo=0;
	if (nGeneri==0) {
		printf("\nNessun genere presente nel database.");
	} else {
		while(i<nGeneri&&controllo!=-1) {
			printf("\n");
			mostraSingoloGenere(db, db.genere[i].id);
			if ((nGeneri+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				scelta = richiesta(11);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			i++;
		}
	}
}

void mostraSingolaPlaylist(database db, int modalita, int id) {
	int posPlaylist = ottenerePosDaID(db, 4,id);
	int posUtente = ottenerePosDaID(db, -1,db.playlist[posPlaylist].idUtente);
	printf("\nIdentificativo: %d", db.playlist[posPlaylist].id);
	printf("\nAutore: %s", db.utente[posUtente].username);
	printf("\nNome: %s", db.playlist[posPlaylist].nome);
	printf("\nDescrizione: %s", db.playlist[posPlaylist].descrizione);
	if (db.playlist[posPlaylist].pubblica==false) {
		printf("\nPrivacy: Privata");
	} else {
		printf("\nPrivacy: Pubblica");
	}
	if (modalita!=-1) {
		char scelta='y';
		scelta = richiesta(13);
		if (scelta=='Y'||scelta=='y') {
			mostraBraniPlaylistDaID(db, id);
		}
	}
}

void mostraPlaylistUtente(database db, int modalita, int idUtente) {
	int i=0, j=0, n=contareNelDatabase(db,4), nPlaylistUtente=contaPlaylistUtente(db, idUtente), controllo=0;
	while (i<n && controllo!=-1) {
		if (db.playlist[i].idUtente==idUtente) {
			printf("\n");
			mostraSingolaPlaylist(db, modalita,db.playlist[i].id);
			if ((nPlaylistUtente+1)>5 && (j+1)%5==0) {
				char scelta='Y';
				scelta = richiesta(12);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			j++;
		}
		i++;
	}
}

void mostraTuttePlaylist(database db, int modalita) {
	int i=0, n=contareNelDatabase(db,4), controllo=0;
	while (i<n&&controllo!=-1) {
		printf("\n");
		mostraSingolaPlaylist(db, modalita,db.playlist[i].id);
		if ((n+1)>5 && (i+1)%5==0) {
			char scelta='Y';
			scelta = richiesta(12);
			if(scelta=='N'||scelta=='n') {
				controllo=-1;
			}
		}
		i++;
	}
}

void mostraTuttePlaylistPubbliche(database db, int modalita) {
	int i=0, n=contareNelDatabase(db,4), controllo=0;
	while(i<n&&controllo!=-1) {
		if (isPublicPlaylist(db, db.playlist[i].id)) {
			printf("\n");
			mostraSingolaPlaylist(db, modalita,db.playlist[i].id);
			if ((n+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				scelta = richiesta(12);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
		}
		i++;
	}
}

void mostraSingoloUtente(database db, int modalita, int idUtente) {
	int posUtente = ottenerePosDaID(db, -1, idUtente);
	char* ruolo;
	if (controllareSeAdminUtente(db, idUtente)==true) {
		ruolo="Amministratore";
	} else {
		ruolo="Utente normale";
	}
	printf("\nIdentificativo: %d", db.utente[posUtente].id);
	printf("\nUsername: %s", db.utente[posUtente].username);
	if (controllareSeAdmin(db)) {
		if (modalita==1)
			printf("\nPassword: %s", db.utente[posUtente].password);
		else
			printf("\nPassword: *REDATTO*");
	} else {
		printf("\nPassword: *REDATTO*");
	}
	printf("\nRuolo: %s", ruolo);
}

void mostraTuttiUtenti(database db) {
	int i=0, n=contareNelDatabase(db,-1), controllo=0, modalita=-1, controllo2=0;
	//pulisciBuffer();
	while(modalita<0||modalita>1) {
		printf("\nMostrare anche le password degli utenti? [0/1]: ");
		modalita = inputNumero();
	}
	while (i<n&&controllo!=-1) {
		printf("\n");
		mostraSingoloUtente(db, modalita,db.utente[i].id);
		if ((n+1)>5 && (i+1)%5==0) {
			char scelta='a';
			scelta = richiesta(0);
			if(scelta=='N'||scelta=='n') {
				controllo=-1;
			}
		}
		i++;
	}
}

/*
 * 0 == per Artista
 * 1 == per Album
 * 2 == per Genere
 * 3 == per Playlist
 * 4 == per Utente
 */
int mostraInfo(database db, int modalita) {
	int esiste=0;
	if (modalita==0) {
		char *nome = malloc(MAX_MEDIO);
		char *cognome = malloc(MAX_MEDIO);
		char *nomeArte = malloc(MAX_MEDIO);
		//pulisciBuffer();
		printf("\n[Premi invio per saltare] Inserisci il nome dell'artista da ricercare: ");
		nome = inputStringa(MAX_MEDIO,nome);
		printf("\n[Premi invio per saltare] Inserisci il cognome dell'artista da ricercare: ");
		cognome = inputStringa(MAX_MEDIO,cognome);
		printf("\n[Premi invio per saltare] Inserisci il nome d'arte dell'artista da ricercare: ");
		nomeArte = inputStringa(MAX_MEDIO,nomeArte);
		int i=0, n=contareNelDatabase(db,2);
		while (i<n) {
			if (comparaStringheParziale(db.artista[i].nome,nome)
				&&comparaStringheParziale(db.artista[i].cognome, cognome)
				&&comparaStringheParziale(db.artista[i].nomeArte, nomeArte)) {
				printf("\n");
				mostraSingoloArtista(db, db.artista[i].id);
				esiste=1;
			}
			i++;
		}
		if(esiste != 1){

			//Sistemare ricerche nulle
			if (comparaStringhe(nome, "N/A")==0){
				strcpy(nome, "unknown");
			}
			if (comparaStringhe(cognome, "N/A")==0){
				strcpy(cognome, "unknown");
			}
			if (comparaStringhe(nomeArte, "N/A")==0){
				strcpy(nomeArte, "unknown");
			}

			printf("\nNon e' stato trovato nessun artista che rispetti interamente i criteri cercati.");
			printf("\nArtisti con nome simile:");
			i=0;
			while (i<n) {
				if (comparaStringheParziale(db.artista[i].nome,nome)) {
					printf("\n");
					mostraSingoloArtista(db, db.artista[i].id);
					esiste=1;
				}
				i++;
			}
			printf("\nArtisti con cognome simile:");
			i=0;
			while (i<n) {
				if (comparaStringheParziale(db.artista[i].cognome,cognome)) {
					printf("\n");
					mostraSingoloArtista(db, db.artista[i].id);
					esiste=1;
				}
				i++;
			}
			printf("\nArtisti con nome d'arte simile:");
			i=0;
			while (i<n) {
				if (comparaStringheParziale(db.artista[i].nomeArte,nomeArte)) {
					printf("\n");
					mostraSingoloArtista(db, db.artista[i].id);
					esiste=1;
				}
				i++;
			}
		}
		free(nome); free(cognome); free(nomeArte);
	} else if (modalita==1) {
		char *titolo = malloc(MAX_MEDIO);
		int anno=0;
		//pulisciBuffer();
		printf("\n[Premi invio per saltare] Inserisci il titolo dell'album da ricercare: ");
		titolo = inputStringa(MAX_MEDIO,titolo);
		if (comparaStringhe(titolo, "N/A")==0)
			titolo = "unknown";
		while(anno<0||anno>3000) {
			printf("\n[0 per saltare] Inserisci l'anno di uscita dell'album da ricercare: ");
			anno = inputNumero();
		}
		int i=0, n=contareNelDatabase(db,1);
		while(i<n) {
			if (comparaStringheParziale(db.album[i].titolo, titolo)||db.album[i].anno == anno) {
				printf("\n");
				mostraSingoloAlbum(db, db.album[i].id);
				esiste=1;
			}
			i++;
		}
		free(titolo);
	} else if (modalita==2) {
		char *nome = malloc(MAX_MEDIO);
		//pulisciBuffer();
		printf("\nInserisci il nome del genere: ");
		nome = inputStringa(MAX_MEDIO,nome);
		int i=0, n=contareNelDatabase(db,3);
		while (i<n) {
			if (comparaStringheParziale(db.genere[i].nome, nome)) {
				printf("\n");
				mostraSingoloGenere(db, db.genere[i].id);
				esiste=1;
			}
			i++;
		}
		free(nome);
	} else if (modalita==3) {
		char *playlist = malloc(MAX_MEDIO);
		//pulisciBuffer();
		printf("\nInserisci il nome della playlist: ");
		playlist = inputStringa(MAX_MEDIO,playlist);
		int i=0, n=contareNelDatabase(db,4);
		while (i<n) {
			if (comparaStringheParziale(db.playlist[i].nome, playlist)) {
				if (isPublicPlaylist(db, db.playlist[i].id)||isUserPlaylist(db, db.playlist[i].id,db.utenteCorrente)||controllareSeAdmin(db)) {
					printf("\n");
					mostraSingolaPlaylist(db, 0,db.playlist[i].id);
					esiste=1;
				}
			}
			i++;
		}
		free(playlist);
	} else if (modalita==4) {
		char *username = malloc(MAX_MEDIO);
		//pulisciBuffer();
		printf("\nInserisci l'username dell'utente: ");
		username = inputStringa(MAX_MEDIO,username);
		int i=0, n=contareNelDatabase(db,-1);
		while(i<n) {
			if (comparaStringheParziale(db.utente[i].username, username)) {
				printf("\n");
				mostraSingoloUtente(db, 0, db.utente[i].id);
				esiste=1;
			}
			i++;
		}
		free(username);
	}
	return esiste;
}

database moduloRicercaBrani(database db) {
	int scelta=-1;
	do {
		//pulisciBuffer();
		while (scelta<0||scelta>6) {
			printf("\nEffettua una ricerca per:"
				   "\n[1] Titolo"
				   "\n[2] Anno"
				   "\n[3] Artista"
				   "\n[4] Album"
				   "\n[5] Genere"
				   "\n[0] Esci dalla ricerca"
				   "\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
			scelta = inputNumero();
		}
		if (scelta==1) {
			db.ultimoEsito = mostraBrani(db, 0);
		} else if (scelta==2) {
			db.ultimoEsito = mostraBrani(db, 1);
		} else if (scelta==3) {
			db.ultimoEsito = mostraBraniArtista(db);
		} else if (scelta==4) {
			db.ultimoEsito = mostraBraniAlbum(db);
		} else if (scelta==5) {
			db.ultimoEsito = mostraBraniGenere(db);
		} else if (scelta==0) {
			printf("\nUscita dalla ricerca...\n");
			db.ultimoEsito=-1;
		}
		if (db.ultimoEsito==0) {
			printf("\nLa ricerca non ha prodotto risultati. Riprovare.");
		}
	} while (db.ultimoEsito==0);
	return db;
}

/*
 * 0 == per Titolo
 * 1 == per Anno
 */
int mostraBrani(database db, int modalita) {
	int esiste=0;
	if (modalita==0) {
		char *titolo = malloc(MAX_MEDIO);
		//pulisciBuffer();
		printf("\nInserisci il titolo del brano da ricercare: ");
		titolo = inputStringa(MAX_MEDIO,titolo);
		int i=0, n=contareNelDatabase(db,0);
		while (i<n) {
			if (comparaStringheParziale(db.brano[i].titolo,titolo)) {
				printf("\n");
				mostraSingoloBrano(db, db.brano[i].id);
				esiste=1;
			}
			i++;
		}
		free(titolo);
	} else if (modalita==1) {
		int anno = 0;
		//pulisciBuffer();
		while (anno<=1950) {
			printf("\nInserisci l'anno di uscita del brano da ricercare: ");
			anno = inputNumero();
		}
		int i=0, n=contareNelDatabase(db,0);
		while (i<n) {
			if (db.brano[i].anno == anno) {
				printf("\n");
				mostraSingoloBrano(db, db.brano[i].id);
				esiste=1;
			}
			i++;
		}
	}
	return esiste;
}

int mostraBraniArtista(database db) {
	int esiste=0;
	int id=0;
	char *nomeArte = malloc(MAX_MEDIO);
	//pulisciBuffer();
	printf("\nInserisci nome d'arte dell'artista: ");
	nomeArte = inputStringa(MAX_MEDIO,nomeArte);
	id = controlloEsistenzaArtista(db, nomeArte);
	if (id==0) {
		printf("\nArtista non esistente");
	} else {
		int i=0, n=contareNelDatabase(db,5);
		printf("Artista: %s", nomeArte);
		while(i<n) {
			if (db.branoArtista[i].idArtista==id) {
				printf("\n");
				mostraSingoloBrano(db, db.branoArtista[i].idBrano);
				esiste=1;
			}
			i++;
		}
	}
	free(nomeArte);
	return esiste;
}

int mostraBraniAlbum(database db) {
	int esiste=0;
	int id=0;
	char *album = malloc(MAX_MEDIO);
	//pulisciBuffer();
	printf("\nInserisci nome album: ");
	album = inputStringa(MAX_MEDIO,album);
	id = controlloEsistenzaAlbum(db, album);
	if (id==0) {
		printf("\nAlbum non esistente.");
	} else {
		int i=0, n=contareNelDatabase(db,6);
		printf("Album: %s", album);
		while(i<n) {
			if (db.branoAlbum[i].idAlbum==id) {
				printf("\n");
				mostraSingoloBrano(db, db.branoAlbum[i].idBrano);
				esiste=1;
			}
			i++;
		}
	}
	free(album);
	return esiste;
}

int mostraBraniGenere(database db) {
	int esiste=0;
	int id=0;
	char *genere = malloc(MAX_MEDIO);
	//pulisciBuffer();
	printf("\nInserisci nome genere: ");
	genere = inputStringa(MAX_MEDIO,genere);
	id = controllareEsistenzaGenere(db, genere);
	if (id==0) {
		printf("\nGenere non esistente.");
	} else {
		int i=0, n=contareNelDatabase(db,7);
		printf("Genere: %s", genere);
		while(i<n) {
			if (db.branoGenere[i].idGenere==id) {
				printf("\n");
				mostraSingoloBrano(db, db.branoGenere[i].idBrano);
				esiste=1;
			}
			i++;
		}
	}
	free(genere);
	return esiste;
}

int mostraBraniPlaylist(database db) {
	int esiste=0;
	int id=0;
	char *playlist = malloc(MAX_MEDIO);
	//pulisciBuffer();
	printf("\nInserisci nome playlist: ");
	playlist = inputStringa(MAX_MEDIO,playlist);
	id = controlloEsistenzaPlaylist(db, playlist);
	if (id==0) {
		printf("\nPlaylist non esistente.");
	} else {
		if (isPublicPlaylist(db, id)||isUserPlaylist(db, id, db.utenteCorrente)) {
			int i=0, n=contareNelDatabase(db,8);
			printf("\nPlaylist: %s", playlist);
			while (i<n) {
				if (db.playlistBrano[i].idPlaylist==id) {
					printf("\n");
					mostraSingoloBrano(db, db.playlistBrano[i].idBrano);
					esiste=1;
				}
				i++;
			}
		} else {
			printf("\nPlaylist privata.");
		}
	}
	free(playlist);
	return esiste;
}

int mostraPlaylistUtenteGuidato(database db) {
	int esiste=0;
	int id=0;
	char *utente = malloc(MAX_MEDIO);
	//pulisciBuffer();
	printf("\nInserisci nome utente: ");
	utente = inputStringa(MAX_MEDIO,utente);
	if (!controllareEsistenzaUtente(db, utente)) {
		printf("\nUtente non esistente.");
	} else {
		int i=0, n=contareNelDatabase(db,-1), controllo=0;
		while(i<n&&controllo!=-1) {
			if (comparaStringhe(utente, db.utente[i].username)==0) {
				id=db.utente[i].id;
				controllo=-1;
			}
		}
		printf("\nUtente: %s", utente);
		mostraPlaylistUtente(db, 0, id);
		esiste=1;
	}
	free(utente);
	return esiste;
}

void mostraBraniPlaylistDaID(database db, int id) {
	int posPlaylist = ottenerePosDaID(db,4,id);
	int i=0, j=0, n=contareNelDatabase(db,8), controllo=0, nBraniplaylist=(contaBraniPlaylist(db, id));
	printf("\n\n===[Brani Playlist %s]===", db.playlist[posPlaylist].nome);
	while (i<n&&controllo!=-1) {
		if (db.playlistBrano[i].idPlaylist==id) {
			printf("\n");
			mostraSingoloBrano(db, db.playlistBrano[i].idBrano);
			if ((nBraniplaylist+1)>5 && (j+1)%5==0) {
				char scelta='Y';
				scelta = richiesta(8);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			j++;
		}
		i++;
	}
}
