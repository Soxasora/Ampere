/*
 * Ampere 0.0.1 rev. 1000 - 02.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/XX/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int i=0;
	while (i<nbrani) {
		printf("\n");
		mostraSingoloBrano(db.brano[i].id);
		i++;
	}
}
