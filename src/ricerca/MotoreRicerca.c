/*
 * Ampere 0.1 rev. 4075 - 19.05.2020
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
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void mostraSingoloBrano(database db, int id) {
	int posbrano = ottieniPosDaID(db, 0,id);
	int posalbum = ottieniPosDaID(db, 1,db.brano[posbrano].album);
	int posassociazioneartista = ottieniPosDaID(db, 5,db.brano[posbrano].id);
	int posartista = ottieniPosDaID(db, 2,db.branoArtista[posassociazioneartista].idArtista);
	int postipobrano = ottieniPosDaID(db, 7,db.brano[posbrano].id);
	int posgenere = ottieniPosDaID(db, 3,db.branoGenere[postipobrano].idGenere);
	//Blocco nuovo
	printf("\nIdentificativo: %d"
		   "\nTitolo: %s"
		   "\nDurata: %s"
		   "\nArtista: %s"
		   "\nAlbum: %s"
		   "\nGenere: %s"
		   "\nAnno: %d"
		   "\nAscolti: %d",
		   db.brano[posbrano].id, db.brano[posbrano].titolo, convertiSecondiInTempo(db.brano[posbrano].durata),
		   db.artista[posartista].nomearte, db.album[posalbum].titolo, db.genere[posgenere].nome,
		   db.brano[posbrano].anno, db.brano[posbrano].ascolti);
}

void mostraTuttiBrani(database db) {
	int nbrani = contaNelDatabase(db,0);
	int i=0, controllo=0;
	if (nbrani==0) {
		printf("\nNessun brano presente nel database.");
	} else {
		while (i<nbrani&&controllo!=-1) {
			printf("\n");
			mostraSingoloBrano(db, db.brano[i].id);
			if ((nbrani+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				pulisciBuffer();
				printf("\nElencare i prossimi 5 brani? [Y/N]: ");
				scanf("%c", &scelta);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			i++;
		}
	}
}

void mostraSingoloAlbum(database db, int id) {
	int posalbum = ottieniPosDaID(db, 1, id);
	printf("\nIdentificativo: %d", db.album[posalbum].id);
	printf("\nTitolo: %s", db.album[posalbum].titolo);
	printf("\nAnno di uscita: %d", db.album[posalbum].anno);
}

void mostraTuttiAlbum(database db) {
	int i=0, nalbum=contaNelDatabase(db,1), controllo=0;
	if (nalbum==0) {
		printf("\nNessun album presente nel database.");
	} else {
		while(i<nalbum&&controllo!=-1) {
			printf("\n");
			mostraSingoloAlbum(db, db.album[i].id);
			if ((nalbum+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				pulisciBuffer();
				printf("\nElencare i prossimi 5 album? [Y/N]: ");
				scanf("%c", &scelta);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			i++;
		}
	}
}

void mostraSingoloArtista(database db, int id) {
	int posartista = ottieniPosDaID(db, 2, id);
	printf("\nIdentificativo: %d", db.artista[posartista].id);
	printf("\nNome: %s", db.artista[posartista].nome);
	printf("\nCognome: %s", db.artista[posartista].cognome);
	printf("\nNome d'arte: %s", db.artista[posartista].nomearte);
	printf("\nLink biografia: %s", db.artista[posartista].linkbio);
}

void mostraTuttiArtisti(database db) {
	int i=0, nartisti=contaNelDatabase(db,2), controllo=0;
	if (nartisti==0) {
		printf("\nNessun artista presente nel database.");
	} else {
		while(i<nartisti&&controllo!=-1) {
			printf("\n");
			mostraSingoloArtista(db, db.artista[i].id);
			if ((nartisti+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				pulisciBuffer();
				printf("\nElencare i prossimi 5 artisti? [Y/N]: ");
				scanf("%c", &scelta);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			i++;
		}
	}
}

void mostraSingoloGenere(database db, int id) {
	int posgenere = ottieniPosDaID(db, 3, id);
	printf("\nIdentificativo: %d", db.genere[posgenere].id);
	printf("\nNome: %s", db.genere[posgenere].nome);
}

void mostraTuttiGeneri(database db) {
	int i=0, ngeneri=contaNelDatabase(db,3), controllo=0;
	if (ngeneri==0) {
		printf("\nNessun genere presente nel database.");
	} else {
		while(i<ngeneri&&controllo!=-1) {
			printf("\n");
			mostraSingoloGenere(db, db.genere[i].id);
			if ((ngeneri+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				pulisciBuffer();
				printf("\nElencare i prossimi 5 generi? [Y/N]: ");
				scanf("%c", &scelta);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			i++;
		}
	}
}

void mostraSingolaPlaylist(database db, int modalita, int id) {
	int posplaylist = ottieniPosDaID(db, 4,id);
	int posutente = ottieniPosDaID(db, -1,db.playlist[posplaylist].idUtente);
	printf("\nIdentificativo: %d", db.playlist[posplaylist].id);
	printf("\nAutore: %s", db.utente[posutente].username);
	printf("\nNome: %s", db.playlist[posplaylist].nome);
	printf("\nDescrizione: %s", db.playlist[posplaylist].descrizione);
	if (db.playlist[posplaylist].pubblica==false) {
		printf("\nPrivacy: Privata");
	} else {
		printf("\nPrivacy: Pubblica");
	}
	if (modalita!=-1) {
		char scelta='y';
		pulisciBuffer();
		printf("\nMostrare i brani della playlist? [Y/N]");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y') {
			mostraBraniPlaylistDaID(db, id);
		}
	}
}

void mostraPlaylistUtente(database db, int modalita, int idUtente) {
	int i=0, j=0, n=contaNelDatabase(db,4), nplaylistutente=contaPlaylistUtente(db, idUtente), controllo=0;
	while (i<n && controllo!=-1) {
		if (db.playlist[i].idUtente==idUtente) {
			printf("\n");
			mostraSingolaPlaylist(db, modalita,db.playlist[i].id);
			if ((nplaylistutente+1)>5 && (j+1)%5==0) {
				char scelta='Y';
				pulisciBuffer();
				printf("\nElencare le prossime 5 playlist? [Y/N]: ");
				scanf("%c", &scelta);
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
	int i=0, n=contaNelDatabase(db,4), controllo=0;
	while (i<n&&controllo!=-1) {
		printf("\n");
		mostraSingolaPlaylist(db, modalita,db.playlist[i].id);
		if ((n+1)>5 && (i+1)%5==0) {
			char scelta='Y';
			pulisciBuffer();
			printf("\nElencare le prossime 5 playlist? [Y/N]: ");
			scanf("%c", &scelta);
			if(scelta=='N'||scelta=='n') {
				controllo=-1;
			}
		}
		i++;
	}
}

void mostraTuttePlaylistPubbliche(database db, int modalita) {
	int i=0, n=contaNelDatabase(db,4), controllo=0;
	while(i<n&&controllo!=-1) {
		if (isPublicPlaylist(db, db.playlist[i].id)) {
			printf("\n");
			mostraSingolaPlaylist(db, modalita,db.playlist[i].id);
			if ((n+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				pulisciBuffer();
				printf("\nElencare le prossime 5 playlist? [Y/N]: ");
				scanf("%c", &scelta);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
		}
		i++;
	}
}

void mostraSingoloUtente(database db, int modalita, int idUtente) {
	int posutente = ottieniPosDaID(db, -1, idUtente);
	char* ruolo = malloc(20);
	if (isGivenUserAdmin(db, idUtente)==true) {
		ruolo="Amministratore";
	} else {
		ruolo="Utente normale";
	}
	printf("\nIdentificativo: %d", db.utente[posutente].id);
	printf("\nUsername: %s", db.utente[posutente].username);
	if (isAdmin(db)) {
		if (modalita==1)
			printf("\nPassword: %s", db.utente[posutente].password);
		else
			printf("\nPassword: *REDATTO*");
	} else {
		printf("\nPassword: *REDATTO*");
	}
	printf("\nRuolo: %s", ruolo);
	free(ruolo);
}

void mostraTuttiUtenti(database db) {
	int i=0, n=contaNelDatabase(db,-1), controllo=0, modalita=-1, controllo2=0;
	pulisciBuffer();
	while(modalita<0||modalita>1) {
		printf("\nMostrare anche le password degli utenti? [0/1]: ");
		scanf("%d", &modalita);
	}
	while (i<n&&controllo!=-1) {
		printf("\n");
		mostraSingoloUtente(db, modalita,db.utente[i].id);
		if ((n+1)>5 && (i+1)%5==0) {
			char scelta='a';
			while (controllo2!=-1) {
				printf("\nSicuro di voler continuare? [Y/N]: ");
				scanf("%c", &scelta);
				if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
					controllo2=-1;
				}
			}
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
		char *nomearte = malloc(MAX_MEDIO);
		pulisciBuffer();
		printf("\n[Premi invio per saltare] Inserisci il nome dell'artista da ricercare: ");
		nome = inputStringaSicuro(MAX_MEDIO,nome);
		if (comparaStringhe(nome, "N/A")==0)
			nome = "unknown";
		printf("\n[Premi invio per saltare] Inserisci il cognome dell'artista da ricercare: ");
		cognome = inputStringaSicuro(MAX_MEDIO,cognome);
		if (comparaStringhe(cognome, "N/A")==0)
			cognome = "unknown";
		printf("\n[Premi invio per saltare] Inserisci il nome d'arte dell'artista da ricercare: ");
		nomearte = inputStringaSicuro(MAX_MEDIO,nomearte);
		if (comparaStringhe(nomearte, "N/A")==0)
			nomearte = "unknown";
		int i=0, n=contaNelDatabase(db,2);
		while (i<n) {
			if (comparaStringhe(db.artista[i].nome,nome)==0
				||comparaStringhe(db.artista[i].cognome, cognome)==0
				||comparaStringhe(db.artista[i].nomearte, nomearte)==0) {
				printf("\n");
				mostraSingoloArtista(db, db.artista[i].id);
				esiste=1;
			}
			i++;
		}
		free(nome); free(cognome); free(nomearte);
	} else if (modalita==1) {
		char *titolo = malloc(MAX_MEDIO);
		int anno=0;
		pulisciBuffer();
		printf("\n[Premi invio per saltare] Inserisci il titolo dell'album da ricercare: ");
		titolo = inputStringaSicuro(MAX_MEDIO,titolo);
		if (comparaStringhe(titolo, "N/A")==0)
			titolo = "unknown";
		while(anno<0||anno>3000) {
			printf("\n[0 per saltare] Inserisci l'anno di uscita dell'album da ricercare: ");
			scanf("%d", &anno);
		}
		int i=0, n=contaNelDatabase(db,1);
		while(i<n) {
			if (comparaStringhe(db.album[i].titolo, titolo)==0||db.album[i].anno == anno) {
				printf("\n");
				mostraSingoloAlbum(db, db.album[i].id);
				esiste=1;
			}
			i++;
		}
		free(titolo);
	} else if (modalita==2) {
		char *nome = malloc(MAX_MEDIO);
		pulisciBuffer();
		printf("\nInserisci il nome del genere: ");
		nome = inputStringaSicuro(MAX_MEDIO,nome);
		int i=0, n=contaNelDatabase(db,3);
		while (i<n) {
			if (comparaStringhe(db.genere[i].nome, nome)==0) {
				printf("\n");
				mostraSingoloGenere(db, db.genere[i].id);
				esiste=1;
			}
			i++;
		}
		free(nome);
	} else if (modalita==3) {
		char *playlist = malloc(MAX_MEDIO);
		pulisciBuffer();
		printf("\nInserisci il nome della playlist: ");
		playlist = inputStringaSicuro(MAX_MEDIO,playlist);
		int i=0, n=contaNelDatabase(db,4);
		while (i<n) {
			if (comparaStringhe(db.playlist[i].nome, playlist)==0) {
				if (isPublicPlaylist(db, db.playlist[i].id)||isUserPlaylist(db, db.playlist[i].id,db.utenteCorrente)) {
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
		pulisciBuffer();
		printf("\nInserisci l'username dell'utente: ");
		username = inputStringaSicuro(MAX_MEDIO,username);
		int i=0, n=contaNelDatabase(db,-1);
		while(i<n) {
			if (comparaStringhe(db.utente[i].username, username)==0) {
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

/*
 * 0 == per Titolo
 * 1 == per Anno
 */
int mostraBrani(database db, int modalita) {
	int esiste=0;
	if (modalita==0) {
		char *titolo = malloc(MAX_MEDIO);
		pulisciBuffer();
		printf("\nInserisci il titolo del brano da ricercare: ");
		titolo = inputStringaSicuro(MAX_MEDIO,titolo);
		int i=0, n=contaNelDatabase(db,0);
		while (i<n) {
			if (comparaStringhe(db.brano[i].titolo,titolo)==0) {
				printf("\n");
				mostraSingoloBrano(db, db.brano[i].id);
				esiste=1;
			}
			i++;
		}
		free(titolo);
	} else if (modalita==1) {
		int anno = 0;
		pulisciBuffer();
		while (anno<0||anno>3000) {
			printf("\nInserisci l'anno di uscita del brano da ricercare: ");
			scanf("%d", &anno);
		}
		int i=0, n=contaNelDatabase(db,0);
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
	char *nomearte = malloc(MAX_MEDIO);
	pulisciBuffer();
	printf("\nInserisci nome d'arte dell'artista: ");
	nomearte = inputStringaSicuro(MAX_MEDIO,nomearte);
	id = controlloEsistenzaArtista(db, nomearte);
	if (id==0) {
		printf("\nArtista non esistente");
	} else {
		int i=0, n=contaNelDatabase(db,5);
		printf("Artista: %s", nomearte);
		while(i<n) {
			if (db.branoArtista[i].idArtista==id) {
				printf("\n");
				mostraSingoloBrano(db, db.branoArtista[i].idBrano);
				esiste=1;
			}
			i++;
		}
	}
	free(nomearte);
	return esiste;
}

int mostraBraniAlbum(database db) {
	int esiste=0;
	int id=0;
	char *album = malloc(MAX_MEDIO);
	pulisciBuffer();
	printf("\nInserisci nome album: ");
	album = inputStringaSicuro(MAX_MEDIO,album);
	id = controlloEsistenzaAlbum(db, album);
	if (id==0) {
		printf("\nAlbum non esistente.");
	} else {
		int i=0, n=contaNelDatabase(db,6);
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
	pulisciBuffer();
	printf("\nInserisci nome genere: ");
	genere = inputStringaSicuro(MAX_MEDIO,genere);
	id = controlloEsistenzaGenere(db, genere);
	if (id==0) {
		printf("\nGenere non esistente.");
	} else {
		int i=0, n=contaNelDatabase(db,7);
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
	pulisciBuffer();
	printf("\nInserisci nome playlist: ");
	playlist = inputStringaSicuro(MAX_MEDIO,playlist);
	id = controlloEsistenzaPlaylist(db, playlist);
	if (id==0) {
		printf("\nPlaylist non esistente.");
	} else {
		if (isPublicPlaylist(db, id)||isUserPlaylist(db, id, db.utenteCorrente)) {
			int i=0, n=contaNelDatabase(db,8);
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
	pulisciBuffer();
	printf("\nInserisci nome utente: ");
	utente = inputStringaSicuro(MAX_MEDIO,utente);
	if (!controllaEsistenzaUtente(db, utente)) {
		printf("\nUtente non esistente.");
	} else {
		int i=0, n=contaNelDatabase(db,-1), controllo=0;
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
	int posplaylist = ottieniPosDaID(db,4,id);
	int i=0, j=0, n=contaNelDatabase(db,8), controllo=0, nbraniplaylist=(contaBraniPlaylist(db, id));
	printf("\n\n===[Brani Playlist %s]===", db.playlist[posplaylist].nome);
	while (i<n&&controllo!=-1) {
		if (db.playlistBrano[i].idPlaylist==id) {
			printf("\n");
			mostraSingoloBrano(db, db.playlistBrano[i].idBrano);
			if ((nbraniplaylist+1)>5 && (j+1)%5==0) {
				char scelta='Y';
				pulisciBuffer();
				printf("\nElencare i prossimi 5 brani? [Y/N]: ");
				scanf("%c", &scelta);
				if(scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			j++;
		}
		i++;
	}
}
