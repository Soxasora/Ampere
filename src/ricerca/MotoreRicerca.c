/*
 * MotoreRicerca.c
 *
 *  Created on: 2 mag 2020
 *      Author: soxas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void mostraSingoloBrano(int pos) {
	printf("\nIdentificativo: %d", db.brano[pos].id);
	printf("\nTitolo: %s", db.brano[pos].titolo);
	printf("\nDurata in secondi: %d", db.brano[pos].durata);
	//printf("\nArtista: %s", )
	printf("\nAlbum: %s", db.album[ottieniPosDaID(1,db.brano[pos].album)].titolo);
	printf("\nAnno: %d", db.brano[pos].anno);
	printf("\nAscolti: %d", db.brano[pos].ascolti);
}

void mostraTuttiBrani() {
	int nbrani = contaNelDatabase(0);
	int i=0;
	while (i<nbrani) {
		printf("\n");
		mostraSingoloBrano(i);
		i++;
	}
}
