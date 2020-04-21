/*
 * FabbAmp 0.1 rev. 174 - 21.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/FabbAmp/blob/master/LICENSE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Impostazioni.h"

void caricaImpostazioni() {
	printf("\nCarico le impostazioni...");
	int i=0;
	file_database = malloc(MAX_CHAR);
	dir_testi = malloc(MAX_CHAR);
	file_lingue = malloc(MAX_CHAR);
	FILE* fp = fopen("sistema\\impostazioni.ini", "r");
	char temp[MAX_TEMP];
	char dati[MAX_TEMP][MAX_TEMP];

	while(!feof(fp)) {
		fgets(temp, MAX_TEMP, fp);
		strtok(temp, "\n");
		strcpy(dati[i], temp);
		i++;
	}
	fclose(fp);

	strcpy(file_database, dati[0]);
	strcpy(dir_testi, dati[1]);
	strcpy(file_lingue, dati[2]);
	printf(" Fatto. %d impostazioni caricate con successo.", i);
}

void caricaLingue() {
	printf("\nCarico le lingue...");
	int i=0;
	FILE* fp = fopen(file_lingue, "r");
	char temp[MAX_TEMP];
	while(!feof(fp)) {
		fgets(temp, MAX_TEMP, fp);
		strtok(temp, "\n");
		strcpy(lingue[i], temp);
		i++;
	}
	fclose(fp);
	printf(" Fatto. %d lingue caricate con successo.", i);
}
