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
#include <time.h>
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

void mostrareSingoloBrano(database *db, int id) {
	int posBrano = ottenerePosDaID(db, 0,id);
	char *tempo = convertireSecondiInTempo(db->brano[posBrano].durata);
	printf("\nIdentificativo: %d"
		   "\nTitolo: %s"
		   "\nDurata: %s", db->brano[posBrano].id, db->brano[posBrano].titolo, tempo);
	if (tempo!=NULL) {
		free(tempo); tempo=NULL;
	}
	mostrareAssociazioni(db, 0, id);
	mostrareAssociazioni(db, 1, id);
	mostrareAssociazioni(db, 2, id);
	printf("\nAnno: %d"
		   "\nAscolti: %d", db->brano[posBrano].anno, db->brano[posBrano].ascolti);
}

void mostrareAssociazioni(database *db, int modalita, int idBrano) {
	int i=0;
	if (modalita==0) { // Artisti
		printf("\nArtisti: ");
		int *posArtisti=ottenerePosAssociazioniDaID(db, 5, idBrano);
		i=0;
		do {
			int posArtista = ottenerePosDaID(db, 2, db->branoArtista[posArtisti[i]].idArtista);
			if (i!=0)
				printf(", ");
			printf("%s", db->artista[posArtista].nomeArte);
			i++;
		} while (posArtisti[i]!=0);
		if (posArtisti!=NULL) {
			free(posArtisti); posArtisti=NULL;
		}
	} else if (modalita==1) { // Album
		printf("\nAlbum: ");
		int *posAlbums=ottenerePosAssociazioniDaID(db, 6, idBrano);
		i=0;
		do {
			int posAlbum = ottenerePosDaID(db, 1, db->branoAlbum[posAlbums[i]].idAlbum);
			if (i!=0)
				printf(", ");
			printf("%s", db->album[posAlbum].titolo);
			i++;
		} while (posAlbums[i]!=0);
		if (posAlbums!=NULL) {
			free(posAlbums); posAlbums=NULL;
		}
	} else if (modalita==2) { // Generi
		printf("\nGeneri: ");
		int *posGeneri=ottenerePosAssociazioniDaID(db, 7, idBrano);
		i=0;
		do {
			int posGenere = ottenerePosDaID(db, 3, db->branoGenere[posGeneri[i]].idGenere);
			if (i!=0)
				printf(", ");
			printf("%s", db->genere[posGenere].nome);
			i++;
		} while (posGeneri[i]!=0);
		if (posGeneri!=NULL) {
			free(posGeneri); posGeneri=NULL;
		}
	}
}

void mostrareTuttiBrani(database *db) {
	int nBrani = contareNelDatabase(db,0);
	int i=0, controllo=0;
	if (nBrani==0) {
		printf("\nNessun brano presente nel database.");
	} else {
		while (i<nBrani&&controllo!=-1) {
			printf("\n");
			mostrareSingoloBrano(db, db->brano[i].id);
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

void mostrareSingoloAlbum(database *db, int id) {
	int posAlbum = ottenerePosDaID(db, 1, id);
	printf("\nIdentificativo: %d", db->album[posAlbum].id);
	printf("\nTitolo: %s", db->album[posAlbum].titolo);
	printf("\nAnno di uscita: %d", db->album[posAlbum].anno);
}

void mostrareTuttiAlbum(database *db) {
	int i=0, nAlbum=contareNelDatabase(db,1), controllo=0;
	if (nAlbum==0) {
		printf("\nNessun album presente nel database.");
	} else {
		while(i<nAlbum&&controllo!=-1) {
			printf("\n");
			mostrareSingoloAlbum(db, db->album[i].id);
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

void mostrareSingoloArtista(database *db, int id) {
	int posArtista = ottenerePosDaID(db, 2, id);
	printf("\nIdentificativo: %d", db->artista[posArtista].id);
	printf("\nNome: %s", db->artista[posArtista].nome);
	printf("\nCognome: %s", db->artista[posArtista].cognome);
	printf("\nNome d'arte: %s", db->artista[posArtista].nomeArte);
	printf("\nLink biografia: %s", db->artista[posArtista].linkBio);
}

void mostrareTuttiArtisti(database *db) {
	int i=0, nArtisti=contareNelDatabase(db,2), controllo=0;
	if (nArtisti==0) {
		printf("\nNessun artista presente nel database.");
	} else {
		while(i<nArtisti&&controllo!=-1) {
			printf("\n");
			mostrareSingoloArtista(db, db->artista[i].id);
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

void mostrareSingoloGenere(database *db, int id) {
	int posGenere = ottenerePosDaID(db, 3, id);
	printf("\nIdentificativo: %d", db->genere[posGenere].id);
	printf("\nNome: %s", db->genere[posGenere].nome);
}

void mostrareTuttiGeneri(database *db) {
	int i=0, nGeneri=contareNelDatabase(db,3), controllo=0;
	if (nGeneri==0) {
		printf("\nNessun genere presente nel database.");
	} else {
		while(i<nGeneri&&controllo!=-1) {
			printf("\n");
			mostrareSingoloGenere(db, db->genere[i].id);
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

void mostrareSingolaPlaylist(database *db, int modalita, int id) {
	int posPlaylist = ottenerePosDaID(db, 4,id);
	int posUtente = ottenerePosDaID(db, -1,db->playlist[posPlaylist].idUtente);
	printf("\nIdentificativo: %d", db->playlist[posPlaylist].id);
	printf("\nAutore: %s", db->utente[posUtente].username);
	printf("\nNome: %s", db->playlist[posPlaylist].nome);
	printf("\nDescrizione: %s", db->playlist[posPlaylist].descrizione);
	if (db->playlist[posPlaylist].pubblica==false) {
		printf("\nPrivacy: Privata");
	} else {
		printf("\nPrivacy: Pubblica");
	}
	if (modalita!=-1) {
		char scelta='y';
		scelta = richiesta(13);
		if (scelta=='Y'||scelta=='y') {
			ricercareBraniPlaylistDaID(db, id);
		}
	}
}

void mostrarePlaylistUtente(database *db, int modalita, int idUtente) {
	int i=0, j=0, n=contareNelDatabase(db,4), nPlaylistUtente=contarePlaylistUtente(db, idUtente), controllo=0;
	while (i<n && controllo!=-1) {
		if (db->playlist[i].idUtente==idUtente) {
			printf("\n");
			mostrareSingolaPlaylist(db, modalita,db->playlist[i].id);
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

void mostrareTuttePlaylist(database *db, int modalita) {
	int i=0, n=contareNelDatabase(db,4), controllo=0;
	while (i<n&&controllo!=-1) {
		printf("\n");
		mostrareSingolaPlaylist(db, modalita,db->playlist[i].id);
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

void mostrareTuttePlaylistPubbliche(database *db, int modalita) {
	int i=0, n=contareNelDatabase(db,4), controllo=0;
	while(i<n&&controllo!=-1) {
		if (controllareSePlaylistPubblica(db, db->playlist[i].id)) {
			printf("\n");
			mostrareSingolaPlaylist(db, modalita,db->playlist[i].id);
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

void mostrareSingoloUtente(database *db, int modalita, int idUtente) {
	int posUtente = ottenerePosDaID(db, -1, idUtente);
	char* ruolo;
	if (controllareSeAdminUtente(db, idUtente)==true) {
		ruolo="Amministratore";
	} else {
		ruolo="Utente normale";
	}
	printf("\nIdentificativo: %d", db->utente[posUtente].id);
	printf("\nUsername: %s", db->utente[posUtente].username);
	if (controllareSeAdmin(db)) {
		if (modalita==1)
			printf("\nPassword: %s", db->utente[posUtente].password);
		else
			printf("\nPassword: *REDATTO*");
	} else {
		printf("\nPassword: *REDATTO*");
	}
	printf("\nRuolo: %s", ruolo);
}

void mostrareTuttiUtenti(database *db) {
	int i=0, n=contareNelDatabase(db,-1), controllo=0, modalita=-1;
	
	while(modalita<0||modalita>1) {
		printf("\nMostrare anche le password degli utenti? [0/1]: ");
		modalita = inputNumero();
	}
	while (i<n&&controllo!=-1) {
		printf("\n");
		mostrareSingoloUtente(db, modalita,db->utente[i].id);
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
int ricercareInfo(database *db, int modalita) {
	int esiste=0;
	if (modalita==0) {
		char *nome = calloc(MAX_MEDIO, sizeof(char));
		char *cognome = calloc(MAX_MEDIO, sizeof(char));
		char *nomeArte = calloc(MAX_MEDIO, sizeof(char));
		
		printf("\n[Premi invio per saltare] Inserisci il nome dell'artista da ricercare: ");
		nome = inputStringa(MAX_MEDIO,nome);
		printf("\n[Premi invio per saltare] Inserisci il cognome dell'artista da ricercare: ");
		cognome = inputStringa(MAX_MEDIO,cognome);
		printf("\n[Premi invio per saltare] Inserisci il nome d'arte dell'artista da ricercare: ");
		nomeArte = inputStringa(MAX_MEDIO,nomeArte);
		int i=0, n=contareNelDatabase(db,2);
		printf("\nDi seguito i risultati della ricerca:");
		while (i<n) {
			if (comparareStringheParziale(db->artista[i].nome,nome)
				&&comparareStringheParziale(db->artista[i].cognome, cognome)
				&&comparareStringheParziale(db->artista[i].nomeArte, nomeArte)) {
				printf("\n");
				mostrareSingoloArtista(db, db->artista[i].id);
				esiste=1;
			}
			i++;
		}
		if(esiste != 1){

			//Sistemare ricerche nulle
			if (comparareStringhe(nome, "N/A")==0){
				strcpy(nome, "unknown");
			}
			if (comparareStringhe(cognome, "N/A")==0){
				strcpy(cognome, "unknown");
			}
			if (comparareStringhe(nomeArte, "N/A")==0){
				strcpy(nomeArte, "unknown");
			}

			printf("\nNon e' stato trovato nessun artista che rispetti interamente i criteri cercati.");
			printf("\nArtisti con nome simile:");
			i=0;
			while (i<n) {
				if (comparareStringheParziale(db->artista[i].nome,nome)) {
					printf("\n");
					mostrareSingoloArtista(db, db->artista[i].id);
					esiste=1;
				}
				i++;
			}
			printf("\nArtisti con cognome simile:");
			i=0;
			while (i<n) {
				if (comparareStringheParziale(db->artista[i].cognome,cognome)) {
					printf("\n");
					mostrareSingoloArtista(db, db->artista[i].id);
					esiste=1;
				}
				i++;
			}
			printf("\nArtisti con nome d'arte simile:");
			i=0;
			while (i<n) {
				if (comparareStringheParziale(db->artista[i].nomeArte,nomeArte)) {
					printf("\n");
					mostrareSingoloArtista(db, db->artista[i].id);
					esiste=1;
				}
				i++;
			}
		}
		if (nome!=NULL) {
			free(nome);
			nome=NULL;
		}
		if (cognome!=NULL) {
			free(cognome);
			cognome=NULL;
		}
		if (nomeArte!=NULL) {
			free(nomeArte);
			nomeArte=NULL;
		}
	} else if (modalita==1) {
		char *titolo = calloc(MAX_MEDIO, sizeof(char));
		int anno=0;
		printf("\n[Premi invio per saltare] Inserisci il titolo dell'album da ricercare: ");
		titolo = inputStringa(MAX_MEDIO,titolo);
		if (comparareStringhe(titolo, "N/A")==0)
			titolo = "unknown";
		while(anno<1950) {
			printf("\n[0 per saltare] Inserisci l'anno di uscita dell'album da ricercare: ");
			anno = inputNumero();
			if (anno==0) {
				anno = 9999;
			}
		}
		int i=0, n=contareNelDatabase(db,1);
		printf("\nDi seguito i risultati della ricerca:");
		while(i<n) {
			if (comparareStringheParziale(db->album[i].titolo, titolo)||db->album[i].anno == anno) {
				printf("\n");
				mostrareSingoloAlbum(db, db->album[i].id);
				esiste=1;
			}
			i++;
		}
		if (titolo!=NULL) {
			free(titolo);
			titolo=NULL;
		}
	} else if (modalita==2) {
		char *nome = calloc(MAX_MEDIO, sizeof(char));
		printf("\nInserisci il nome del genere da ricercare: ");
		nome = inputStringa(MAX_MEDIO,nome);
		int i=0, n=contareNelDatabase(db,3);
		printf("\nDi seguito i risultati della ricerca:");
		while (i<n) {
			if (comparareStringheParziale(db->genere[i].nome, nome)) {
				printf("\n");
				mostrareSingoloGenere(db, db->genere[i].id);
				esiste=1;
			}
			i++;
		}
		if (nome!=NULL) {
			free(nome);
			nome=NULL;
		}
	} else if (modalita==3) {
		char *playlist = calloc(MAX_MEDIO, sizeof(char));
		printf("\nInserisci il nome della playlist da ricercare: ");
		playlist = inputStringa(MAX_MEDIO,playlist);
		int i=0, n=contareNelDatabase(db,4);
		printf("\nDi seguito i risultati della ricerca:");
		while (i<n) {
			if (comparareStringheParziale(db->playlist[i].nome, playlist)) {
				if (controllareSePlaylistPubblica(db, db->playlist[i].id)||controllareSePlaylistUtente(db, db->playlist[i].id,db->utenteCorrente)||controllareSeAdmin(db)) {
					printf("\n");
					mostrareSingolaPlaylist(db, 0,db->playlist[i].id);
					esiste=1;
				}
			}
			i++;
		}
		if (playlist!=NULL) {
			free(playlist);
			playlist=NULL;
		}
	} else if (modalita==4) {
		char *username = calloc(MAX_MEDIO, sizeof(char));
		printf("\nInserisci l'username dell'utente: ");
		username = inputStringa(MAX_MEDIO,username);
		int i=0, n=contareNelDatabase(db,-1);
		printf("\nDi seguito i risultati della ricerca:");
		while(i<n) {
			if (comparareStringheParziale(db->utente[i].username, username)) {
				printf("\n");
				mostrareSingoloUtente(db, 0, db->utente[i].id);
				esiste=1;
			}
			i++;
		}
		if (username!=NULL) {
			free(username);
			username=NULL;
		}
	}
	return esiste;
}

void moduloRicercaBrani(database *db) {
	int scelta=-1;
	do {
		scelta=-1;
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
			db->ultimoEsito = ricercareBrani(db, 0);
		} else if (scelta==2) {
			db->ultimoEsito = ricercareBrani(db, 1);
		} else if (scelta==3) {
			db->ultimoEsito = ricercareBraniArtista(db);
		} else if (scelta==4) {
			db->ultimoEsito = ricercareBraniAlbum(db);
		} else if (scelta==5) {
			db->ultimoEsito = ricercareBraniGenere(db);
		} else if (scelta==0) {
			printf("\nUscita dalla ricerca...\n");
			db->ultimoEsito=-1;
		}
		if (db->ultimoEsito==0) {
			printf("\nLa ricerca non ha prodotto risultati. Riprovare.");
		}
	} while (db->ultimoEsito==0);
	
}

/*
 * 0 == per Titolo
 * 1 == per Anno
 */
int ricercareBrani(database *db, int modalita) {
	int esiste=0;
	if (modalita==0) {
		char *titolo = calloc(MAX_MEDIO, sizeof(char));
		printf("\nInserisci il titolo del brano da ricercare: ");
		titolo = inputStringa(MAX_MEDIO,titolo);
		int i=0, n=contareNelDatabase(db,0);
		while (i<n) {
			if (comparareStringheParziale(db->brano[i].titolo,titolo)) {
				printf("\n");
				mostrareSingoloBrano(db, db->brano[i].id);
				esiste=1;
			}
			i++;
		}
		if (titolo!=NULL) {
			free(titolo);
			titolo=NULL;
		}
	} else if (modalita==1) {
		int anno = 0;
		
		while (anno<1950) {
			printf("\nInserisci l'anno di uscita del brano da ricercare: ");
			anno = inputNumero();
		}
		int i=0, n=contareNelDatabase(db,0);
		while (i<n) {
			if (db->brano[i].anno == anno) {
				printf("\n");
				mostrareSingoloBrano(db, db->brano[i].id);
				esiste=1;
			}
			i++;
		}
	}
	return esiste;
}

int ricercareBraniArtista(database *db) {
	int esiste=0;
	int id=0;
	char *nomeArte = calloc(MAX_MEDIO, sizeof(char));
	printf("\nInserisci nome d'arte dell'artista: ");
	nomeArte = inputStringa(MAX_MEDIO,nomeArte);
	id = controllareEsistenzaArtista(db, nomeArte);
	if (id==0) {
		printf("\nArtista non esistente");
	} else {
		int i=0, n=contareNelDatabase(db,5);
		printf("Artista: %s", nomeArte);
		while(i<n) {
			if (db->branoArtista[i].idArtista==id) {
				printf("\n");
				mostrareSingoloBrano(db, db->branoArtista[i].idBrano);
				esiste=1;
			}
			i++;
		}
	}
	if (nomeArte!=NULL) {
		free(nomeArte);
		nomeArte=NULL;
	}
	return esiste;
}

int ricercareBraniAlbum(database *db) {
	int esiste=0;
	int id=0;
	char *album = calloc(MAX_MEDIO, sizeof(char));
	printf("\nInserisci nome album: ");
	album = inputStringa(MAX_MEDIO,album);
	id = controllareEsistenzaAlbum(db, album);
	if (id==0) {
		printf("\nAlbum non esistente.");
	} else {
		int i=0, n=contareNelDatabase(db,6);
		printf("Album: %s", album);
		while(i<n) {
			if (db->branoAlbum[i].idAlbum==id) {
				printf("\n");
				mostrareSingoloBrano(db, db->branoAlbum[i].idBrano);
				esiste=1;
			}
			i++;
		}
	}
	if (album!=NULL) {
		free(album);
		album=NULL;
	}
	return esiste;
}

int ricercareBraniGenere(database *db) {
	int esiste=0;
	int id=0;
	char *genere = calloc(MAX_MEDIO, sizeof(char));
	printf("\nInserisci nome genere: ");
	genere = inputStringa(MAX_MEDIO,genere);
	id = controllareEsistenzaGenere(db, genere);
	if (id==0) {
		printf("\nGenere non esistente.");
	} else {
		int i=0, n=contareNelDatabase(db,7);
		printf("Genere: %s", genere);
		while(i<n) {
			if (db->branoGenere[i].idGenere==id) {
				printf("\n");
				mostrareSingoloBrano(db, db->branoGenere[i].idBrano);
				esiste=1;
			}
			i++;
		}
	}
	if (genere!=NULL) {
		free(genere);
		genere=NULL;
	}
	return esiste;
}

int ricercareBraniPlaylist(database *db) {
	int esiste=0;
	int id=0;
	char *playlist = calloc(MAX_MEDIO, sizeof(char));
	printf("\nInserisci nome playlist: ");
	playlist = inputStringa(MAX_MEDIO,playlist);
	id = controllareEsistenzaPlaylist(db, playlist);
	if (id==0) {
		printf("\nPlaylist non esistente.");
	} else {
		if (controllareSePlaylistPubblica(db, id)||controllareSePlaylistUtente(db, id, db->utenteCorrente)) {
			int i=0, n=contareNelDatabase(db,8);
			printf("\nPlaylist: %s", playlist);
			while (i<n) {
				if (db->playlistBrano[i].idPlaylist==id) {
					printf("\n");
					mostrareSingoloBrano(db, db->playlistBrano[i].idBrano);
					esiste=1;
				}
				i++;
			}
		} else {
			printf("\nPlaylist privata.");
		}
	}
	if (playlist!=NULL) {
		free(playlist);
		playlist=NULL;
	}
	return esiste;
}

int ricercarePlaylistUtenteGuidato(database *db) {
	int esiste=0;
	int id=0;
	char *utente = calloc(MAX_MEDIO, sizeof(char));
	printf("\nInserisci nome utente: ");
	utente = inputStringa(MAX_MEDIO,utente);
	if (!controllareEsistenzaUtente(db, utente)) {
		printf("\nUtente non esistente.");
	} else {
		int i=0, n=contareNelDatabase(db,-1), controllo=0;
		while(i<n&&controllo!=-1) {
			if (comparareStringhe(utente, db->utente[i].username)==0) {
				id=db->utente[i].id;
				controllo=-1;
			}
		}
		printf("\nUtente: %s", utente);
		mostrarePlaylistUtente(db, 0, id);
		esiste=1;
	}
	if (utente!=NULL) {
		free(utente);
		utente=NULL;
	}
	return esiste;
}

void ricercareBraniPlaylistDaID(database *db, int id) {
	int posPlaylist = ottenerePosDaID(db,4,id);
	int i=0, j=0, n=contareNelDatabase(db,8), controllo=0, nBraniplaylist=(contareBraniPlaylist(db, id));
	printf("\n\n===[Brani Playlist %s]===", db->playlist[posPlaylist].nome);
	while (i<n&&controllo!=-1) {
		if (db->playlistBrano[i].idPlaylist==id) {
			printf("\n");
			mostrareSingoloBrano(db, db->playlistBrano[i].idBrano);
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
	if (i==0) {
		printf("\nNessun brano trovato nella playlist %s", db->playlist[posPlaylist].nome);
	}
}

void stampareBraniGuidato(database *db) {
	int scelta=-1, i=0, branoscelto=0, controllo=0;
	int nBrani = contareNelDatabase(db,0);
	int *idBrani = calloc(nBrani, sizeof(int));
	printf("\n===[Stampa di un Report dei Brani]===");
	printf("\nDesideri selezionare alcuni brani[0] oppure tutti i brani[1]? ");
	while (scelta<0||scelta>1) {
		scelta = inputNumero();
	}
	if (scelta==0) {
		printf("\nSeleziona fino a %d brani da stampare", nBrani);
		i=0;
		do {
			branoscelto=0;
			moduloRicercaBrani(db);
			if (db->ultimoEsito==-1) {
				scelta = richiesta(-1);
				if (scelta=='Y'||scelta=='y') {
					printf("\nContinuo con la selezione dei brani.");
					db->ultimoEsito=0;
				} else {
					printf("\nUscito dalla selezione dei brani.");
				}
			}
			if (db->ultimoEsito==1) {
				do {
					printf("\nInserire l'identificativo del brano da selezionare e stampare, altrimenti [-1] per cercare di nuovo: ");
					branoscelto = inputNumero();
					if (branoscelto==-1) {
						db->ultimoEsito=2;
					} else {
						if (ottenerePosDaID(db, 0, branoscelto)==-1) {
							printf("\nBrano non trovato, riprova");
							db->ultimoEsito=0;
						} else {
							int j=0;
							while (idBrani[j]!=0) {
								if (idBrani[j]==branoscelto&&controllo!=-1) {
									printf("\nBrano gia' selezionato, riprova");
									controllo=-1;
									db->ultimoEsito=0;
								} else {
									db->ultimoEsito=1;
								}
								j++;
							}
						}
					}
					if (db->ultimoEsito==1) {
						idBrani[i] = branoscelto;
						i++;
					}
				} while (db->ultimoEsito==0);
			}
		} while ((i<nBrani)&&(db->ultimoEsito!=-1));
	} else {
		idBrani[0]=-1;
	}

	if (idBrani[0]==0) {
		printf("\nNessun brano selezionato");
	} else {
		stampareListaBrani(db, idBrani);
	}
	if (idBrani!=NULL) {
		free(idBrani);
		idBrani=NULL;
	}
}

void stampareSingoloBrano(database *db, FILE* fp, int id) {
	int j=0;
	int posBrano = ottenerePosDaID(db, 0,id);
	char *tempo = convertireSecondiInTempo(db->brano[posBrano].durata);
	fprintf(fp, DIVISORE
			"\nIdentificativo: %d"
			"\nTitolo: %s"
			"\nDurata: %s", db->brano[posBrano].id, db->brano[posBrano].titolo, tempo);
	if (tempo!=NULL) {
		free(tempo); tempo=NULL;
	}
	fprintf(fp, "\nArtisti: ");
	int *posArtisti=ottenerePosAssociazioniDaID(db, 5, db->brano[posBrano].id);
	j=0;
	do {
		int posArtista = ottenerePosDaID(db, 2, db->branoArtista[posArtisti[j]].idArtista);
		if (j!=0) {
			fprintf(fp, ", ");
		}
		fprintf(fp, "%s", db->artista[posArtista].nomeArte);
		j++;
	} while (posArtisti[j]!=0);
	if (posArtisti!=NULL) {
		free(posArtisti); posArtisti=NULL;
	}
	fprintf(fp, "\nAlbum: ");
	int *posAlbums=ottenerePosAssociazioniDaID(db, 6, db->brano[posBrano].id);
	j=0;
	do {
		int posAlbum = ottenerePosDaID(db, 1, db->branoAlbum[posAlbums[j]].idAlbum);
		if (j!=0)
			fprintf(fp, ", ");
		fprintf(fp, "%s", db->album[posAlbum].titolo);
		j++;
	} while (posAlbums[j]!=0);
	if (posAlbums!=NULL) {
		free(posAlbums); posAlbums=NULL;
	}
	fprintf(fp, "\nGeneri: ");
	int *posGeneri=ottenerePosAssociazioniDaID(db, 7, db->brano[posBrano].id);
	j=0;
	do {
		int posGenere = ottenerePosDaID(db, 3, db->branoGenere[posGeneri[j]].idGenere);
		if (j!=0)
			fprintf(fp, ", ");
		fprintf(fp, "%s", db->genere[posGenere].nome);
		j++;
	} while (posGeneri[j]!=0);
	if (posGeneri!=NULL) {
		free(posGeneri); posGeneri=NULL;
	}
	fprintf(fp, "\nAnno: %d"
		   "\nAscolti: %d"
			DIVISORE, db->brano[posBrano].anno, db->brano[posBrano].ascolti);
}

void stampareListaBrani(database *db, int idBrani[]) {
	srand(time(NULL));
	char *nomefile = calloc(MAX_MEDIO, sizeof(char));
	sprintf(nomefile, "report_brani_%d.txt", rand()%1000);
	FILE *fp = fopen(nomefile, "a");
	int nBrani = contareNelDatabase(db, 0), i=0;
	if (idBrani[0]==-1) {
		fprintf(fp, "%d Brani presenti nel Database attuale di Ampere", nBrani);
		i=0;
		while (i<nBrani) {
			stampareSingoloBrano(db, fp, db->brano[i].id);
			i++;
		}
		successo(151);
	} else {
		fprintf(fp, "Brani selezionati dal Database attuale di Ampere");
		i=0;
		while (idBrani[i]!=0) {
			stampareSingoloBrano(db, fp, idBrani[i]);
			i++;
		}
		successo(150);
	}
	fclose(fp);
	if (nomefile!=NULL) {
		free(nomefile);
		nomefile=NULL;
	}
}
