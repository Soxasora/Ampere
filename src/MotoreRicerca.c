/*
 * FabbAmp 0.1 rev.99 - 17.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/FabbAmp/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MotoreRicerca.h"
#include "Database.h"
#include "FabbAmp.h"
#include "Utils.h"

// Funzione di ricerca brani in base alla loro anagrafica
void ricercaBrani(int modalita) {
	//database *brani = ottieniDatabase();
	int scelta=0;
	if (modalita==0) {
		// Flush per evitare indesiderati comportamenti dell'input
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		char *titolo = malloc(MAX_CHAR);
		printf("\nInserisci titolo: ");
		fgets(titolo, MAX_CHAR, stdin);
		strtok(titolo, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (strcmp(titolo, brani[i].titolo)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(titolo);
		printf("\nCercare un altro brano per Titolo[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(0);
		} else {
			menuRicerca();
		}
	// Ricerca per Artista
	} else if (modalita==1) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		char *artista = malloc(MAX_CHAR);
		printf("\nInserisci artista: ");
		fgets(artista, MAX_CHAR, stdin);
		strtok(artista, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (strcmp(artista, brani[i].artista)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(artista);
		printf("\nCercare un altro brano per Artista[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(1);
		} else {
			menuRicerca();
		}
	// Ricerca per Album
	} else if (modalita==2) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		char *album = malloc(MAX_CHAR);
		printf("\nInserisci album: ");
		fgets(album, MAX_CHAR, stdin);
		strtok(album, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (strcmp(album, brani[i].album)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(album);
		printf("\nCercare un altro brano per Album[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(2);
		} else {
			menuRicerca();
		}
	} else if (modalita==3) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		char *durata = malloc(MAX_CHAR);
		printf("\nInserisci durata: ");
		fgets(durata, MAX_CHAR, stdin);
		strtok(durata, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (strcmp(durata, brani[i].durata)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(durata);
		printf("\nCercare un altro brano per Durata[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(3);
		} else {
			menuRicerca();
		}
	} else if (modalita==4) {
		int anno=0;
		printf("\nInserisci anno: ");
		scanf("%d", &anno);
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (anno==brani[i].anno) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		printf("\nCercare un altro brano per Anno[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(4);
		} else {
			menuRicerca();
		}
	} else if (modalita==5) {
		int ascolti=0;
		printf("\nInserisci numero di ascolti: ");
		scanf("%d", &ascolti);
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (ascolti==brani[i].ascolti) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		printf("\nCercare un altro brano per Ascolti[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(5);
		} else {
			menuRicerca();
		}
	} else if (modalita==6) {
		float gradimento=0.0;
		printf("\nInserisci gradimento: ");
		scanf("%f", &gradimento);
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (gradimento==brani[i].gradimento) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		printf("\nCercare un altro brano per Gradimento[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(6);
		} else {
			menuRicerca();
		}
	}
}

// Funzione di elencazione di tutte le informazioni di un brano
void elencaSingoloBrano(int pos) {
	printf("\nTitolo: %s\n", brani[pos].titolo);
	printf("Artista: %s\n", brani[pos].artista);
	printf("Album: %s\n", brani[pos].album);
	printf("Durata: %s\n", brani[pos].durata);
	printf("Anno: %d\n", brani[pos].anno);
	printf("Ascolti: %d\n", brani[pos].ascolti);
	printf("Gradimento: %.1f stelle\n", brani[pos].gradimento);
}

// Funzione di elencazione di tutti i brani presenti nel database file-based
void elencaTuttiBrani() {
	//database *brani = ottieniDatabase();

	printf("Elenco dei brani:\n");
	int i=0;
	while (i<numero_brani) {
		printf("\nBrano n.%d\n", i+1);
		elencaSingoloBrano(i);
		if ((numero_brani+1)>5 && (i+1)%5==0) {
			char scelta='Y';
			pulisciBuffer();
			printf("\nElencare i prossimi 5 brani? [Y/N]: ");
			scanf("%c", &scelta);
			if (scelta=='N')
				break;
		}
		i++;
	}

}
