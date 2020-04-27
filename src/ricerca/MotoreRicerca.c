/*
 * Ampere 0.1 rev. 501 - 27.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ricerca/MotoreRicerca.h"
#include "../Ampere.h"
#include "../gestore/Database.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

// Funzione di ricerca brani in base alla loro anagrafica
void ricercaBrani(int modalita) {
	//database *brani = ottieniDatabase();
	int scelta=0;
	int nbrani = conteggiaBrani();
	if (modalita==0) {
		// Flush per evitare indesiderati comportamenti dell'input
		pulisciBuffer();
		char *titolo = malloc(MAX_CHAR);
		printf("\nInserisci titolo: ");
		fgets(titolo, MAX_CHAR, stdin);
		strtok(titolo, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (comparaStringhe(titolo, brani[i].titolo)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(titolo);
		printf("\nCercare un altro brano per Titolo[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(0);
		}
	// Ricerca per Artista
	} else if (modalita==1) {
		pulisciBuffer();
		char *artista = malloc(MAX_CHAR);
		printf("\nInserisci artista: ");
		fgets(artista, MAX_CHAR, stdin);
		strtok(artista, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (comparaStringhe(artista, brani[i].artista)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(artista);
		printf("\nCercare un altro brano per Artista[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(1);
		}
	} else if (modalita==2) {
		pulisciBuffer();
		char *feat = malloc(MAX_CHAR);
		printf("\nInserisci feat: ");
		fgets(feat, MAX_CHAR, stdin);
		strtok(feat, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (comparaStringhe(feat, brani[i].feat)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(feat);
		printf("\nCercare un altro brano per Feat[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(2);
		}
	} else if (modalita==3) {
		pulisciBuffer();
		char *produttore = malloc(MAX_CHAR);
		printf("\nInserisci produttore: ");
		fgets(produttore, MAX_CHAR, stdin);
		strtok(produttore, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (comparaStringhe(produttore, brani[i].produttore)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(produttore);
		printf("\nCercare un altro brano per Produttore[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(3);
		}
	} else if (modalita==4) {
		pulisciBuffer();
		char *scrittore = malloc(MAX_CHAR);
		printf("\nInserisci artista: ");
		fgets(scrittore, MAX_CHAR, stdin);
		strtok(scrittore, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (comparaStringhe(scrittore, brani[i].scrittore)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(scrittore);
		printf("\nCercare un altro brano per Scrittore[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(4);
		}
	// Ricerca per Album
	} else if (modalita==5) {
		pulisciBuffer();
		char *album = malloc(MAX_CHAR);
		printf("\nInserisci album: ");
		fgets(album, MAX_CHAR, stdin);
		strtok(album, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (comparaStringhe(album, brani[i].album)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(album);
		printf("\nCercare un altro brano per Album[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(5);
		}
	} else if (modalita==6) {
		pulisciBuffer();
		char *durata = malloc(MAX_CHAR);
		printf("\nInserisci durata: ");
		fgets(durata, MAX_CHAR, stdin);
		strtok(durata, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (comparaStringhe(durata, brani[i].durata)==0) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(durata);
		printf("\nCercare un altro brano per Durata[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(6);
		}
	} else if (modalita==7) {
		int anno=0;
		printf("\nInserisci anno: ");
		scanf("%d", &anno);
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (anno==brani[i].anno) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		printf("\nCercare un altro brano per Anno[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(7);
		}
	} else if (modalita==8) {
		pulisciBuffer();
		char *lingua = malloc(MAX_CHAR);
		printf("\nInserisci lingua: ");
		fgets(lingua, MAX_CHAR, stdin);
		strtok(lingua, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (lingue[posizioneLinguaDaStringa(lingua)].id==brani[i].lingua) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		free(lingua);
		printf("\nCercare un altro brano per Lingua[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(8);
		}
	} else if (modalita==9) {
		int ascolti=0;
		printf("\nInserisci numero di ascolti: ");
		scanf("%d", &ascolti);
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (ascolti==brani[i].ascolti) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		printf("\nCercare un altro brano per Ascolti[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(9);
		}
	} else if (modalita==10) {
		float gradimento=0.0;
		printf("\nInserisci gradimento: ");
		scanf("%f", &gradimento);
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<nbrani) {
			if (gradimento==brani[i].gradimento) {
				elencaSingoloBrano(i);
			}
			i++;
		}
		printf("\nCercare un altro brano per Gradimento [0] oppure ritornare al Menu di ricerca [1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(10);
		}
	} else if (modalita==11) {
		int id = 0;
		printf("\nInserisci identificativo: ");
		scanf("%d", &id);
		printf("\nTrovate le seguenti occorrenze:\n\n");
		elencaSingoloBrano(trovaPosizioneBranoId(id));
		printf("\nCercare un altro brano per Identificativo[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(11);
		}
	}
}

// Funzione di elencazione di tutte le informazioni di un brano
void elencaSingoloBrano(int pos) {
	printf("\nIdentificativo: %d\n", brani[pos].id);
	printf("Titolo: %s\n", brani[pos].titolo);
	printf("Artista: %s\n", brani[pos].artista);
	printf("Feat: %s\n", brani[pos].feat);
	printf("Produttore: %s\n", brani[pos].produttore);
	printf("Scrittore: %s\n", brani[pos].scrittore);
	printf("Album: %s\n", brani[pos].album);
	printf("Durata: %s\n", brani[pos].durata);
	printf("Anno: %d\n", brani[pos].anno);
	printf("Lingua: %s\n", lingue[posizioneLinguaDaId(brani[pos].lingua)].nome_umano);
	printf("Ascolti: %d\n", brani[pos].ascolti);
	printf("Gradimento: %.1f stelle\n", brani[pos].gradimento);
}

// Funzione di elencazione di tutti i brani presenti nel database file-based
void elencaTuttiBrani() {
	//database *brani = ottieniDatabase();
	printf("Elenco dei brani:\n");
	int i=0;
	int controllo=0; // Alternativa al break
	int nbrani = conteggiaBrani();
	if (nbrani==0) {
		printf("\nNessun brano presente nel database, aggiungi!");
	} else {
		while (i<nbrani&&controllo!=-1) {
			printf("\nBrano n.%d\n", i+1);
			elencaSingoloBrano(i);
			if ((nbrani+1)>5 && (i+1)%5==0) {
				char scelta='Y';
				pulisciBuffer();
				printf("\nElencare i prossimi 5 brani? [Y/N]: ");
				scanf("%c", &scelta);
				if (scelta=='N'||scelta=='n')
					controllo=-1;
			}
			i++;
		}
	}
}