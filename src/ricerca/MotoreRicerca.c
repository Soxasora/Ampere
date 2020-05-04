/*
 * Ampere 0.1 rev. 1250 - 04.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestoreGeneri.h"
#include "../gestori/GestoreAlbum.h"
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
		while (i<n) {
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
