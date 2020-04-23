/*
 * Ampere 0.1 rev. 234 - 23.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void creaImpostazioni() {
	printf("\nPer poter garantire il funzionamento, se non sono gia' presenti, crea le seguenti cartelle, dove si trova Ampere: ");
	printf("\n\"sistema\"");
	printf("\n\"libreria\"");
	printf("\n\"testi\" all'interno dell'appena creata \"libreria\"");
	aspetta();
	char *posizione_database = malloc(MAX_TEMP);
	char *posizione_testi = malloc(MAX_TEMP);
	char *posizione_lingue = malloc(MAX_TEMP);
	pulisciBuffer();
	printf("\n\nInserire la posizione in cui si trova il database file-based (es. libreria\\brani.txt): ");
	fgets(posizione_database, MAX_TEMP, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
	strtok(posizione_database, "\n"); // In modo da evitare indesiderati newline
	printf("\nInserire la posizione in cui si trova la cartella dei testi (es. libreria\\testi): ");
	fgets(posizione_testi, MAX_TEMP, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
	strtok(posizione_testi, "\n"); // In modo da evitare indesiderati newline
	printf("\nInserire la posizione in cui si trova la lista delle lingue (es. sistema\\lingue.ini): ");
	fgets(posizione_lingue, MAX_TEMP, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
	strtok(posizione_lingue, "\n"); // In modo da evitare indesiderati newline
	FILE* fp = fopen(file_impostazioni, "a");
	fprintf(fp, "%s\n%s\n%s", posizione_database, posizione_testi, posizione_lingue);
	fclose(fp);
	free(posizione_database); free(posizione_testi); free(posizione_lingue);
	printf("\n\nImpostazioni salvate, riprendo...");
	caricaImpostazioni();
}

void caricaImpostazioni() {
	printf("\nCarico le impostazioni...");
	FILE* fp = fopen(file_impostazioni, "r");
	if(fp!=NULL) {
		int i=0;
		file_database = malloc(MAX_CHAR);
		dir_testi = malloc(MAX_CHAR);
		file_lingue = malloc(MAX_CHAR);
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
	} else if (fp==NULL) {
		printf("\n/!\\ Impostazioni non trovate, procedo alla creazione...");
		creaImpostazioni();
	}
}

void creaLingue() {
	FILE* fp = fopen(file_lingue, "a");
	int n_lingue=0, i=0;
	char *lingua = malloc(MAX_CHAR);
	printf("Quante lingue vorresti inserire? ");
	scanf("%d", &n_lingue);
	pulisciBuffer();
	while (i<n_lingue) {
		printf("\nInserisci lingua %d: ", i);
		fgets(lingua, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(lingua, "\n"); // In modo da evitare indesiderati newline
		if (i==n_lingue-1) {
			fprintf(fp, "%s", lingua);
		} else {
			fprintf(fp, "%s\n", lingua);
		}
		i++;
	}
	fclose(fp);
	free(lingua);
	printf("\nLingue salvate, riprendo...");
	caricaLingue();
}

void caricaLingue() {
	printf("\nCarico le lingue...");
	FILE* fp = fopen(file_lingue, "r");
	if (fp!=NULL) {
		int i=0;
		char temp[MAX_TEMP];
		while(!feof(fp)) {
			fgets(temp, MAX_TEMP, fp);
			strtok(temp, "\n");
			strcpy(lingue[i], temp);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d lingue caricate con successo.", i);
	} else if (fp==NULL) {
		printf("\n/!\\ Lingue non trovate, procedo alla creazione...");
		creaLingue();
	}
}
