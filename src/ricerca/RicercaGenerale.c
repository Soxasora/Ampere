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

void ricerca(int modalita, char interrogazione[]) {
	int i=0, n=0;
	if (modalita==0) {
		printf("\n\nBrani:");
		n = contaNelDatabase(0);
		while (i<n) {
			if (strstr(db.brano[i].titolo, interrogazione)) {
				printf("\nTitolo: %s", db.brano[i].titolo);
			}
			i++;
		}
	} else if (modalita==1) {
		printf("\n\nAlbum:");
		n = contaNelDatabase(1);
		while (i<n) {
			if (strstr(db.album[i].titolo, interrogazione)) {
				mostraSingoloAlbum(db.album[i].id);
			}
			i++;
		}
	} else if (modalita==2) {
		printf("\n\nArtisti:");
		n = contaNelDatabase(2);
		while (i<n) {
			if (strstr(db.artista[i].nome, interrogazione)
				||strstr(db.artista[i].cognome, interrogazione)
				||strstr(db.artista[i].nomearte, interrogazione)) {
				mostraSingoloArtista(db.artista[i].id);
			}
			i++;
		}
	} else if (modalita==3) {
		printf("\n\nGeneri:");
		n = contaNelDatabase(3);
		while (i<n) {
			if (strstr(db.genere[i].nome, interrogazione)) {
				mostraSingoloGenere(db.genere[i].id);
			}
			i++;
		}
	}

}

void eseguiRicerca() {
	char *interrogazione = malloc(MAX_CHAR);
	printf("\n===[Ricerca Generale]===");
	pulisciBuffer();
	printf("\nCerca nel database: ");
	interrogazione = inputStringaSicuro(interrogazione);
	ricerca(0,interrogazione);
	printf("\nApprofondisci ricerca brani [0]");
	ricerca(1,interrogazione);
	printf("\nApprofondisci ricerca album [1]");
	ricerca(2,interrogazione);
	printf("\nApprofondisci ricerca artisti [2]");
	ricerca(3,interrogazione);
	printf("\nApprofondisci ricerca generi [3]");
	free(interrogazione);
}

