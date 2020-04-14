/*
 * Spotifabba 0.1 rev.84 - 14.04.2020
 * Copyright (c) 2020, Simone Cervino.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Spotifabba.h"
#include "MotoreRicerca.h"
#include "Database.h"
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
	}
}

// Funzione di elencazione di tutte le informazioni di un brano
void elencaSingoloBrano(int pos) {
	printf("\nTitolo: %s\n", brani[pos].titolo);
	printf("Artista: %s\n", brani[pos].artista);
	printf("Album: %s\n", brani[pos].album);
	printf("Durata: %s\n", brani[pos].durata);
	printf("Anno: %d\n", brani[pos].anno);
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
