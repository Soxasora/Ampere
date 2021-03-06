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

void ricercare(database *db, int modalita, char interrogazione[], bool light) {
	int i=0, n=0, conta=0;
	if (modalita==0) {
		printf("\nBrani:");
		n = contareNelDatabase(db,0);
		while (i<n) {
			if (comparareStringheParziale(db->brano[i].titolo, interrogazione)
				||comparareStringheParziale(db->album[ottenerePosDaID(db, 1,db->branoAlbum[ottenerePosDaID(db, 6, db->brano[i].id)].idAlbum)].titolo, interrogazione)
				||comparareStringheParziale(db->artista[ottenerePosDaID(db, 2,db->branoArtista[ottenerePosDaID(db, 5, db->brano[i].id)].idArtista)].nomeArte, interrogazione)
				||db->brano[i].anno==atoi(interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Titolo: %s", conta+1, db->brano[i].titolo);
					}
				} else {
					printf("\n");
					mostrareSingoloBrano(db, db->brano[i].id);
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
			if (comparareStringheParziale(db->album[i].titolo, interrogazione)
				||db->album[i].anno==atoi(interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Titolo: %s", conta+1, db->album[i].titolo);
					}
				} else {
					printf("\n");
					mostrareSingoloAlbum(db, db->album[i].id);
					char scelta = 'N';
					scelta = richiesta(14);
					if (scelta=='Y'||scelta=='y') {
						ricercareBraniAlbum(db);
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
			if (comparareStringheParziale(db->artista[i].nome, interrogazione)
				||comparareStringheParziale(db->artista[i].cognome, interrogazione)
				||comparareStringheParziale(db->artista[i].nomeArte, interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Nome d'Arte: %s", conta+1, db->artista[i].nomeArte);
					}
				} else {
					printf("\n");
					mostrareSingoloArtista(db, db->artista[i].id);
					char scelta = 'N';
					scelta = richiesta(15);
					if (scelta=='Y'||scelta=='y') {
						ricercareBraniArtista(db);
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
			if (comparareStringheParziale(db->genere[i].nome, interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Nome: %s", conta+1, db->genere[i].nome);
					}
				} else {
					printf("\n");
					mostrareSingoloGenere(db, db->genere[i].id);
					char scelta = 'N';
					scelta = richiesta(16);
					if (scelta=='Y'||scelta=='y') {
						ricercareBraniGenere(db);
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
			if (comparareStringheParziale(db->playlist[i].nome, interrogazione)) {
				if (controllareSePlaylistPubblica(db, db->playlist[i].id)||controllareSePlaylistUtente(db, db->playlist[i].id, db->utenteCorrente)) {
					if (light) {
						if (conta<3) {
							printf("\n%d. Nome: %s", conta+1, db->playlist[i].nome);
							printf("\n   Autore: %s", db->utente[ottenerePosDaID(db, -1,db->playlist[i].idUtente)].username);
						}
					} else {
						printf("\n");
						mostrareSingolaPlaylist(db, -1, db->playlist[i].id);
						char scelta = 'N';
						scelta = richiesta(17);
						if (scelta=='Y'||scelta=='y') {
							ricercareBraniPlaylist(db);
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
			if (comparareStringheParziale(db->utente[i].username, interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Nome utente: %s", conta+1, db->utente[i].username);
					}
				} else {
					printf("\n");
					mostrareSingoloUtente(db, -1,db->utente[i].id);
					char scelta = 'N';
					scelta = richiesta(18);
					if (scelta=='Y'||scelta=='y') {
						ricercarePlaylistUtenteGuidato(db);
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

void eseguireRicerca(database *db) {
	int scelta=-1;
	bool ripeti=false;
	char *interrogazione;
	printf("\n===[Ricerca Generale]===");
	do {
		if ((interrogazione=calloc(MAX_MEDIO, sizeof(char)))) {
			
			printf("\nCerca nel database: ");
			interrogazione = inputStringa(MAX_MEDIO,interrogazione);
		}
		if (comparareStringheParziale("N/A", interrogazione)) {
			attenzione(2);
			ripeti=true;
		} else {
			ripeti=false;
		}
	} while (ripeti==true);
	ricercare(db,0,interrogazione, true);
	ricercare(db,1,interrogazione, true);
	ricercare(db,2,interrogazione, true);
	ricercare(db,3,interrogazione, true);
	ricercare(db,4,interrogazione, true);
	ricercare(db,5,interrogazione, true);
	printf("\n\nEsci dalla ricerca [0]");
	while (scelta<0||scelta>6) {
		printf("\nInserisci scelta: ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		ricercare(db,0,interrogazione, false);
	} else if (scelta==2) {
		ricercare(db,1,interrogazione, false);
	} else if (scelta==3) {
		ricercare(db,2,interrogazione, false);
	} else if (scelta==4) {
		ricercare(db,3,interrogazione, false);
	} else if (scelta==5) {
		ricercare(db,4,interrogazione, false);
	} else if (scelta==6) {
		ricercare(db,5,interrogazione, false);
	}
	if (interrogazione!=NULL) {
		free(interrogazione);
		interrogazione=NULL;
	}
}

