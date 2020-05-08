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

void mostraSingoloBrano(int id) {
	int posbrano = ottieniPosDaID(0,id);
	int posalbum = ottieniPosDaID(1,db.brano[posbrano].album);
	int posassociazioneartista = ottieniPosDaID(5,db.brano[posbrano].id);
	int posartista = ottieniPosDaID(2,db.artistaBrano[posassociazioneartista].idArtista);
	int postipobrano = ottieniPosDaID(7,db.brano[posbrano].id);
	int posgenere = ottieniPosDaID(3,db.branoGenere[postipobrano].idGenere);

	printf("\nIdentificativo: %d", db.brano[posbrano].id);
	printf("\nTitolo: %s", db.brano[posbrano].titolo);
	printf("\nDurata in secondi: %d", db.brano[posbrano].durata);
	printf("\nArtista: %s", db.artista[posartista].nomearte);
	printf("\nAlbum: %s", db.album[posalbum].titolo);
	printf("\nGenere: %s", db.genere[posgenere].nome);
	printf("\nAnno: %d", db.brano[posbrano].anno);
	printf("\nAscolti: %d", db.brano[posbrano].ascolti);
}

void mostraTuttiBrani() {
	int nbrani = contaNelDatabase(0);
	int i=0, controllo=0;
	if (nbrani==0) {
		printf("\nNessun brano presente nel database.");
	} else {
		while (i<nbrani&&controllo!=-1) {
			printf("\n");
			mostraSingoloBrano(db.brano[i].id);
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

void mostraSingoloAlbum(int id) {
	int posalbum = ottieniPosDaID(1, id);
	printf("\nIdentificativo: %d", db.album[posalbum].id);
	printf("\nTitolo: %s", db.album[posalbum].titolo);
	printf("\nAnno di uscita: %d", db.album[posalbum].anno);
}

void mostraTuttiAlbum() {
	int i=0, nalbum=contaNelDatabase(1), controllo=0;
	if (nalbum==0) {
		printf("\nNessun album presente nel database.");
	} else {
		while(i<nalbum&&controllo!=-1) {
			printf("\n");
			mostraSingoloAlbum(db.album[i].id);
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

void mostraSingoloArtista(int id) {
	int posartista = ottieniPosDaID(2, id);
	printf("\nIdentificativo: %d", db.artista[posartista].id);
	printf("\nNome: %s", db.artista[posartista].nome);
	printf("\nCognome: %s", db.artista[posartista].cognome);
	printf("\nNome d'arte: %s", db.artista[posartista].nomearte);
}

void mostraTuttiArtisti() {
	int i=0, nartisti=contaNelDatabase(2), controllo=0;
	if (nartisti==0) {
		printf("\nNessun artista presente nel database.");
	} else {
		while(i<nartisti&&controllo!=-1) {
			printf("\n");
			mostraSingoloArtista(db.artista[i].id);
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

void mostraSingoloGenere(int id) {
	int posgenere = ottieniPosDaID(3, id);
	printf("\nIdentificativo: %d", db.genere[posgenere].id);
	printf("\nNome: %s", db.genere[posgenere].nome);
}

void mostraTuttiGeneri() {
	int i=0, ngeneri=contaNelDatabase(3), controllo=0;
	if (ngeneri==0) {
		printf("\nNessun genere presente nel database.");
	} else {
		while(i<ngeneri&&controllo!=-1) {
			printf("\n");
			mostraSingoloGenere(db.genere[i].id);
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

void mostraSingolaPlaylist(int modalita, int id) {
	int posplaylist = ottieniPosDaID(4,id);
	int posutente = ottieniPosDaID(-1,db.playlist[posplaylist].idUtente);
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
			int i=0, j=0, n=contaNelDatabase(8), controllo=0, nbraniplaylist=(contaBraniPlaylist(id));
			while (i<n&&controllo!=-1) {
				if (db.playlistBrano[i].idPlaylist==id) {
					printf("\n");
					mostraSingoloBrano(db.playlistBrano[i].idBrano);
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
	}
}

void mostraPlaylistUtente(int modalita, int idUtente) {
	int i=0, j=0, n=contaNelDatabase(4), nplaylistutente=contaPlaylistUtente(idUtente), controllo=0;
	while (i<n && controllo!=-1) {
		if (db.playlist[i].idUtente==idUtente) {
			printf("\n");
			mostraSingolaPlaylist(modalita,db.playlist[i].id);
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

void mostraTuttePlaylist(int modalita) {
	int i=0, n=contaNelDatabase(4), controllo=0;
	while (i<n&&controllo!=-1) {
		printf("\n");
		mostraSingolaPlaylist(modalita,db.playlist[i].id);
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

void mostraTuttePlaylistPubbliche(int modalita) {
	int i=0, n=contaNelDatabase(4), controllo=0;
	while(i<n&&controllo!=-1) {
		if (db.playlist[i].pubblica==true) {
			printf("\n");
			mostraSingolaPlaylist(modalita,db.playlist[i].id);
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

void mostraSingoloUtente(int modalita, int idUtente) {
	int posutente = ottieniPosDaID(-1, idUtente);
	char* ruolo = malloc(20);
	if (isGivenUserAdmin(idUtente)==true) {
		ruolo="Amministratore";
	} else {
		ruolo="Utente normale";
	}
	printf("\nIdentificativo: %d", db.utente[posutente].id);
	printf("\nUsername: %s", db.utente[posutente].username);
	if (isAdmin()) {
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

void mostraTuttiUtenti() {
	int i=0, n=contaNelDatabase(-1), controllo=0, modalita=0;
	pulisciBuffer();
	while(modalita<0||modalita>1) {
		printf("\nMostrare anche le password degli utenti? [0/1]: ");
		scanf("%d", &modalita);
	}
	while (i<n&&controllo!=-1) {
		printf("\n");
		mostraSingoloUtente(modalita,db.utente[i].id);
		if ((n+1)>5 && (i+1)%5==0) {
			char scelta='Y';
			//pulisciBuffer();
			printf("\nElencare i prossimi 5 utenti? [Y/N]: ");
			scanf("%c", &scelta);
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
 */
void mostraInfo(int modalita) {
	if (modalita==0) {
		char *nome = malloc(MAX_CHAR);
		char *cognome = malloc(MAX_CHAR);
		char *nomearte = malloc(MAX_CHAR);
		pulisciBuffer();
		printf("\n[Premi invio per saltare] Inserisci il nome dell'artista da ricercare: ");
		nome = inputStringaSicuro(nome);
		if (comparaStringhe(nome, "N/A")==0)
			nome = "unknown";
		printf("\n[Premi invio per saltare] Inserisci il cognome dell'artista da ricercare: ");
		cognome = inputStringaSicuro(cognome);
		if (comparaStringhe(cognome, "N/A")==0)
			cognome = "unknown";
		printf("\n[Premi invio per saltare] Inserisci il nome d'arte dell'artista da ricercare: ");
		nomearte = inputStringaSicuro(nomearte);
		if (comparaStringhe(nomearte, "N/A")==0)
			nomearte = "unknown";
		int i=0, n=contaNelDatabase(2);
		while (i<n) {
			if (comparaStringhe(db.artista[i].nome,nome)==0
				||comparaStringhe(db.artista[i].cognome, cognome)==0
				||comparaStringhe(db.artista[i].nomearte, nomearte)==0) {
				printf("\n");
				mostraSingoloArtista(db.artista[i].id);
			}
			i++;
		}
		free(nome); free(cognome); free(nomearte);
	} else if (modalita==1) {
		char *titolo = malloc(MAX_CHAR);
		int anno=0;
		pulisciBuffer();
		printf("\n[Premi invio per saltare] Inserisci il titolo dell'album da ricercare: ");
		titolo = inputStringaSicuro(titolo);
		if (comparaStringhe(titolo, "N/A")==0)
			titolo = "unknown";
		printf("\n[0 per saltare] Inserisci l'anno di uscita dell'album da ricercare: ");
		scanf("%d", &anno);
		int i=0, n=contaNelDatabase(1);
		while(i<n) {
			if (comparaStringhe(db.album[i].titolo, titolo)==0||db.album[i].anno == anno) {
				printf("\n");
				mostraSingoloAlbum(db.album[i].id);
			}
			i++;
		}
		free(titolo);
	} else if (modalita==2) {
		char *nome = malloc(MAX_CHAR);
		pulisciBuffer();
		printf("\nInserisci il nome del genere: ");
		nome = inputStringaSicuro(nome);
		int i=0, n=contaNelDatabase(3);
		while (i<n) {
			if (comparaStringhe(db.genere[i].nome, nome)==0) {
				printf("\n");
				mostraSingoloGenere(db.genere[i].id);
			}
			i++;
		}
		free(nome);
	}
}

/*
 * 0 == per Titolo
 * 1 == per Anno
 */
void mostraBrani(int modalita) {
	if (modalita==0) {
		char *titolo = malloc(MAX_CHAR);
		pulisciBuffer();
		printf("\nInserisci il titolo del brano da ricercare: ");
		titolo = inputStringaSicuro(titolo);
		int i=0, n=contaNelDatabase(0);
		while (i<n) {
			if (comparaStringhe(db.brano[i].titolo,titolo)==0) {
				printf("\n");
				mostraSingoloBrano(db.brano[i].id);
			}
			i++;
		}
		free(titolo);
	} else if (modalita==1) {
		int anno = 0;
		pulisciBuffer();
		printf("\nInserisci l'anno di uscita del brano da ricercare: ");
		scanf("%d", &anno);
		int i=0, n=contaNelDatabase(0);
		while (i<n) {
			if (db.brano[i].anno == anno) {
				printf("\n");
				mostraSingoloBrano(db.brano[i].id);
			}
			i++;
		}
	}
}

void mostraBraniArtista() {
	int id=0;
	char *nomearte = malloc(MAX_CHAR);
	pulisciBuffer();
	printf("\nInserisci nome d'arte dell'artista: ");
	nomearte = inputStringaSicuro(nomearte);
	id = controlloEsistenzaArtista(nomearte);
	if (id==0) {
		printf("\nArtista non esistente");
	} else {
		int i=0, n=contaNelDatabase(5);
		printf("Artista: %s", nomearte);
		while(i<n) {
			if (db.artistaBrano[i].idArtista==id) {
				printf("\n");
				mostraSingoloBrano(db.artistaBrano[i].idBrano);
			}
			i++;
		}
	}
	free(nomearte);
}

void mostraBraniAlbum() {
	int id=0;
	char *album = malloc(MAX_CHAR);
	pulisciBuffer();
	printf("\nInserisci nome album: ");
	album = inputStringaSicuro(album);
	id = controlloEsistenzaAlbum(album);
	if (id==0) {
		printf("\nAlbum non esistente.");
	} else {
		int i=0, n=contaNelDatabase(6);
		printf("Album: %s", album);
		while(i<n) {
			if (db.albumBrano[i].idAlbum==id) {
				printf("\n");
				mostraSingoloBrano(db.albumBrano[i].idBrano);
			}
			i++;
		}
	}
	free(album);
}

void mostraBraniGenere() {
	int id=0;
	char *genere = malloc(MAX_CHAR);
	pulisciBuffer();
	printf("\nInserisci nome genere: ");
	genere = inputStringaSicuro(genere);
	id = controlloEsistenzaGenere(genere);
	if (id==0) {
		printf("\nGenere non esistente.");
	} else {
		int i=0, n=contaNelDatabase(7);
		printf("Genere: %s", genere);
		while(i<n) {
			if (db.branoGenere[i].idGenere==id) {
				printf("\n");
				mostraSingoloBrano(db.branoGenere[i].idBrano);
			}
			i++;
		}
	}
	free(genere);
}
