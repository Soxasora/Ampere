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
#include "../ricerca/RicercaGenerale.h"
#include "../ricerca/MotoreRicerca.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Messaggi.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void ricerca(database db, int modalita, char interrogazione[], bool light) {
	int i=0, n=0, conta=0;
	if (modalita==0) {
		printf("\nBrani:");
		n = contareNelDatabase(db,0);
		while (i<n) {
			if (comparaStringheParziale(db.brano[i].titolo, interrogazione)
				||comparaStringheParziale(db.album[ottenerePosDaID(db, 1,db.branoAlbum[ottenerePosDaID(db, 6, db.brano[i].id)].idAlbum)].titolo, interrogazione)
				||comparaStringheParziale(db.artista[ottenerePosDaID(db, 2,db.branoArtista[ottenerePosDaID(db, 5, db.brano[i].id)].idArtista)].nomeArte, interrogazione)
				||db.brano[i].anno==atoi(interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Titolo: %s", conta+1, db.brano[i].titolo);
					}
				} else {
					printf("\n");
					mostraSingoloBrano(db, db.brano[i].id);
				}
				conta++;
			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca brano [1]", conta-3);
			} else if (conta>0) {
				printf("\nApprofondisci ricerca brano [1]");
			}
		}
		if (conta==0) {
			printf("\nNessun brano trovato");
		}
	} else if (modalita==1) {
		printf("\n\nAlbum:");
		n = contareNelDatabase(db,1);
		while (i<n) {
			if (comparaStringheParziale(db.album[i].titolo, interrogazione)
				||db.album[i].anno==atoi(interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Titolo: %s", conta+1, db.album[i].titolo);
					}
				} else {
					printf("\n");
					mostraSingoloAlbum(db, db.album[i].id);
					char scelta = 'N';
					pulisciBuffer();
					printf("\nVuoi mostrare i brani di un album? [Y/N]: ");
					scanf("%c", &scelta);
					if (scelta=='Y'||scelta=='y') {
						mostraBraniAlbum(db);
					}
				}
				conta++;
			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca album [2]", conta-3);
			} else if (conta>0) {
				printf("\nApprofondisci ricerca album [2]");
			}
		}
		if (conta==0) {
			printf("\nNessun album trovato");
		}
	} else if (modalita==2) {
		printf("\n\nArtisti:");
		n = contareNelDatabase(db,2);
		while (i<n) {
			if (comparaStringheParziale(db.artista[i].nome, interrogazione)
				||comparaStringheParziale(db.artista[i].cognome, interrogazione)
				||comparaStringheParziale(db.artista[i].nomeArte, interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Nome d'Arte: %s", conta+1, db.artista[i].nomeArte);
					}
				} else {
					printf("\n");
					mostraSingoloArtista(db, db.artista[i].id);
					char scelta = 'N';
					pulisciBuffer();
					printf("\nVuoi mostrare i brani di un artista? [Y/N]: ");
					scanf("%c", &scelta);
					if (scelta=='Y'||scelta=='y') {
						mostraBraniArtista(db);
					}
				}
				conta++;
			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca artisti [3]", conta-3);
			} else if (conta>0) {
				printf("\nApprofondisci ricerca artisti [3]");
			}
		}
		if (conta==0) {
			printf("\nNessun artista trovato");
		}
	} else if (modalita==3) {
		printf("\n\nGeneri:");
		n = contareNelDatabase(db,3);
		while (i<n) {
			if (comparaStringheParziale(db.genere[i].nome, interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Nome: %s", conta+1, db.genere[i].nome);
					}
				} else {
					printf("\n");
					mostraSingoloGenere(db, db.genere[i].id);
					char scelta = 'N';
					pulisciBuffer();
					printf("\nVuoi mostrare i brani di un genere? [Y/N]: ");
					scanf("%c", &scelta);
					if (scelta=='Y'||scelta=='y') {
						mostraBraniGenere(db);
					}
				}
				conta++;
			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca generi [4]", conta-3);
			} else if (conta>0) {
				printf("\nApprofondisci ricerca generi [4]");
			}
		}
		if (conta==0) {
			printf("\nNessun genere trovato");
		}
	} else if (modalita==4) {
		printf("\n\nPlaylists:");
		n = contareNelDatabase(db,4);
		while (i<n) {
			if (comparaStringheParziale(db.playlist[i].nome, interrogazione)) {
				if (isPublicPlaylist(db, db.playlist[i].id)||isUserPlaylist(db, db.playlist[i].id, db.utenteCorrente)) {
					if (light) {
						if (conta<3) {
							printf("\n%d. Nome: %s", conta+1, db.playlist[i].nome);
							printf("\n   Autore: %s", db.utente[ottenerePosDaID(db, -1,db.playlist[i].idUtente)].username);
						}
					} else {
						printf("\n");
						mostraSingolaPlaylist(db, -1, db.playlist[i].id);
						char scelta = 'N';
						pulisciBuffer();
						printf("\nVuoi mostrare i brani di una playlist? [Y/N]: ");
						scanf("%c", &scelta);
						if (scelta=='Y'||scelta=='y') {
							mostraBraniPlaylist(db);
						}
					}
					conta++;
				}
			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca playlist [5]", conta-3);
			} else if (conta>0) {
				printf("\nApprofondisci ricerca playlist [5]");
			}
		}
		if (conta==0) {
			printf("\nNessuna playlist trovata");
		}
	} else if (modalita==5) {
		printf("\n\nUtenti:");
		n = contareNelDatabase(db,-1);
		while (i<n) {
			if (comparaStringheParziale(db.utente[i].username, interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Nome utente: %s", conta+1, db.utente[i].username);
					}
				} else {
					printf("\n");
					mostraSingoloUtente(db, -1,db.utente[i].id);
					char scelta = 'N';
					pulisciBuffer();
					printf("\nVuoi mostrare le playlist di un utente? [Y/N]: ");
					scanf("%c", &scelta);
					if (scelta=='Y'||scelta=='y') {
						mostraPlaylistUtenteGuidato(db);
					}
				}
				conta++;
			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca utenti [6]", conta-3);
			} else if (conta>0) {
				printf("\nApprofondisci ricerca utenti [6]");
			}
		}
		if (conta==0) {
			printf("\nNessun utente trovato");
		}
	}
}

void eseguiRicerca(database db) {
	int scelta=-1;
	bool ripeti=false;
	char *interrogazione;
	printf("\n===[Ricerca Generale]===");
	do {
		if ((interrogazione=malloc(MAX_MEDIO))) {
			pulisciBuffer();
			printf("\nCerca nel database: ");
			interrogazione = inputStringaSicuro(MAX_MEDIO,interrogazione);
		}
		if (strlen(interrogazione)==1&&interrogazione[0]==' ') {
			attenzione(2);
			ripeti=true;
		} else {
			ripeti=false;
		}
	} while (ripeti==true);
	ricerca(db,0,interrogazione, true);
	ricerca(db,1,interrogazione, true);
	ricerca(db,2,interrogazione, true);
	ricerca(db,3,interrogazione, true);
	ricerca(db,4,interrogazione, true);
	ricerca(db,5,interrogazione, true);
	printf("\n\nEsci dalla ricerca [0]");
	while (scelta<0||scelta>6) {
		scelta = inputNumeroScelta(1);
	}
	if (scelta==1) {
		ricerca(db,0,interrogazione, false);
	} else if (scelta==2) {
		ricerca(db,1,interrogazione, false);
	} else if (scelta==3) {
		ricerca(db,2,interrogazione, false);
	} else if (scelta==4) {
		ricerca(db,3,interrogazione, false);
	} else if (scelta==5) {
		ricerca(db,4,interrogazione, false);
	} else if (scelta==6) {
		ricerca(db,5,interrogazione, false);
	}
	free(interrogazione); interrogazione=NULL;
}

