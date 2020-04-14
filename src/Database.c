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
#include "GestoreBrani.h"
#include "Database.h"
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
	database *brani = malloc((MAX_CHAR*5)*sizeof(database));
	FILE* fp=fopen("database.txt", "r"); // Apro database
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
		i++;
	}
	numero_brani=i; // TODO: Trovare un metodo migliore per far sapere al programma il numero dei brani
	fclose(fp);
	printf(" Fatto.\n");
	return brani;
}

// Funzione per trasferire su file il database presente in memoria salvando così le modifiche.
void aggiornaDatabase() {
	printf("\nSalvando le modifiche effettuate al database...");
	backupDatabase("temp_db.txt");
	remove("database.txt");
	int i=0;
	while (i<numero_brani) {
		char anno[5];
		sprintf(anno, "%d", brani[i].anno);
		inserisciBrano(1, brani[i].titolo, brani[i].artista, brani[i].album, brani[i].durata, anno);
		i++;
	}
	remove("temp_db.txt");
	printf("\nModifiche salvate.");

}
