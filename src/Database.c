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
#include "GestoreBrani.h"
#include "Database.h"

#include "FabbAmp.h"
#include "Utils.h"

// Funzione di controllo e creazione del database
void creaDatabaseSeNonEsiste() {
	FILE* fp;
	char* file = "database.txt";
	fp=fopen(file, "ab+");
	// Se non ha i permessi per scrivere nella cartella:
	if(fp == NULL)
		printf("Impossibile aprire e/o creare il database.");
	fclose(fp);
}

// Funzione per trasferire in memoria il database file-based velocizzando la sua lettura.
// TODO: Rendere disponibile lo struct riempito a tutto il programma per evitare inutili ri-accessi
database* ottieniDatabase() {
	printf("\nOttengo il database...");
	//TODO: Trovare un metodo migliore per allocare dinamicamente
	FILE* fp=fopen("database.txt", "r"); // Apro database
	database *brani = malloc((MAX_CHAR*7)*sizeof(database));
	// TODO: Allora questo, questo è da cambiare assolutamente
	char temp[1000]; // [DA CAMBIARE] Variabile temporanea per ottenere i dati
	char dati[1000][1000]; // [DA CAMBIARE] Array temporaneo per trasportare i dati
	char spaziatore[] = ","; // Il database divide i dati utilizzando lo spaziatore ,
	int i, j;
	i=0;
	// TODO: Trovare metodo migliore se esistente
	while(!feof(fp)) { // Fino a quando non arriva alla fine del file
		fgets(temp, 1000, fp); // Ottiene la linea
		char *ptr = strtok(temp, spaziatore); // Imposta lo spaziatore
		j=0;
		while(ptr!=NULL) { // Fino a quando il puntatore non ha piu' niente da trasportare
			strcpy(dati[j], ptr); // Copia informazione nel punto i dell'array temporaneo
			ptr=strtok(NULL, spaziatore); // Passa al prossimo spaziatore
			j++;
		}
		// Blocco di organizzazione dei dati dall'array temporaneo allo struct finale
		strcpy(brani[i].titolo, dati[0]);
		strcpy(brani[i].artista, dati[1]);
		strcpy(brani[i].album, dati[2]);
		strcpy(brani[i].durata, dati[3]);
		brani[i].anno = atoi(dati[4]); // Conversione da char a int del valore Anno
		brani[i].ascolti = atoi(dati[5]);
		brani[i].gradimento = atof(dati[6]);
		i++;
	}
	numero_brani=i; // TODO: Trovare un metodo migliore per far sapere al programma il numero dei brani
	fclose(fp);
	printf(" Fatto.\n%d brani caricati con successo.\n", numero_brani);
	return brani;
}

// Funzione per trasferire su file il database presente in memoria salvando così le modifiche.
void aggiornaDatabase() {
	printf("\nSalvando le modifiche effettuate al database...");
	backupDatabase("temp_db.txt");
	remove("database.txt");
	int i=0;
	while (i<numero_brani) {
		char anno[5], ascolti[MAX_CHAR], gradimento[MAX_CHAR];
		// Investigare su sprintf
		sprintf(anno, "%d", brani[i].anno);
		sprintf(ascolti, "%d", brani[i].ascolti);
		sprintf(gradimento, "%.1f", brani[i].gradimento);
		inserisciBranoGuidato(1, brani[i].titolo, brani[i].artista, brani[i].album, brani[i].durata, anno, ascolti, gradimento);
		i++;
	}
	remove("temp_db.txt");
	printf("\nModifiche salvate.");

}
