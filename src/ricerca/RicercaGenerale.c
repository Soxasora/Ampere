/*
 * Ampere 0.1 rev. 2455 - 09.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void ricerca(int modalita, char interrogazione[], bool light) {
	int i=0, n=0, conta=0;
	if (modalita==0) {
		printf("\n\nBrani:");
		n = contaNelDatabase(0);
		while (i<n) {
			if (comparaStringheParziale(db.brano[i].titolo, interrogazione)
				||comparaStringheParziale(db.album[ottieniPosDaID(1,db.brano[i].album)].titolo, interrogazione)
				||comparaStringheParziale(db.artista[ottieniPosDaID(2,db.artistaBrano[ottieniPosDaID(5, db.brano[i].id)].idArtista)].nomearte, interrogazione)
				||db.brano[i].anno==atoi(interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Titolo: %s", conta+1, db.brano[i].titolo);
					}
					conta++;
				} else {
					printf("\n");
					mostraSingoloBrano(db.brano[i].id);
				}
			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca brano [1]", conta-3);
			}
		}
	} else if (modalita==1) {
		printf("\n\nAlbum:");
		n = contaNelDatabase(1);
		while (i<n) {
			if (comparaStringheParziale(db.album[i].titolo, interrogazione)
				||db.album[i].anno==atoi(interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Titolo: %s", conta+1, db.album[i].titolo);
					}
					conta++;
				} else {
					printf("\n");
					mostraSingoloAlbum(db.album[i].id);
				}

			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca album [2]", conta-3);
			}
		}
	} else if (modalita==2) {
		printf("\n\nArtisti:");
		n = contaNelDatabase(2);
		while (i<n) {
			if (comparaStringheParziale(db.artista[i].nome, interrogazione)
				||comparaStringheParziale(db.artista[i].cognome, interrogazione)
				||comparaStringheParziale(db.artista[i].nomearte, interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Nome d'Arte: %s", conta+1, db.artista[i].nomearte);
					}
					conta++;
				} else {
					printf("\n");
					mostraSingoloArtista(db.artista[i].id);
				}
			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca artisti [3]", conta-3);
			}
		}
	} else if (modalita==3) {
		printf("\n\nGeneri:");
		n = contaNelDatabase(3);
		while (i<n) {
			if (comparaStringheParziale(db.genere[i].nome, interrogazione)) {
				if (light) {
					if (conta<3) {
						printf("\n%d. Nome: %s", conta+1, db.genere[i].nome);
					}
					conta++;
				} else {
					printf("\n");
					mostraSingoloGenere(db.genere[i].id);
				}
			}
			i++;
		}
		if (light) {
			i=0;
			if (conta>3) {
				printf("\nCi sono altri %d risultati. Approfondisci ricerca generi [4]", conta-3);
			}
		}
	}

}

void eseguiRicerca() {
	int scelta=0;
	char *interrogazione = malloc(MAX_CHAR);
	printf("\n===[Ricerca Generale]===");
	pulisciBuffer();
	printf("\nCerca nel database: ");
	interrogazione = inputStringaSicuro(interrogazione);
	ricerca(0,interrogazione, true);
	ricerca(1,interrogazione, true);
	ricerca(2,interrogazione, true);
	ricerca(3,interrogazione, true);
	while (scelta)
	printf("\nEsci dalla ricerca [0]");
	printf("\nInserisci scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		ricerca(0,interrogazione, false);
	} else if (scelta==2) {
		ricerca(1,interrogazione, false);
	} else if (scelta==3) {
		ricerca(2,interrogazione, false);
	} else if (scelta==4) {
		ricerca(3,interrogazione, false);
	}
	free(interrogazione);
}

