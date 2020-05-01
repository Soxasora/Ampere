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
#include "../gestore/GestoreBrani.h"
#include "../database/Database.h"
#include "../Ampere.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

// Funzione di controllo e creazione del database
void creaDatabase() {
	FILE* fp = fopen(file_database, "ab+");
	fclose(fp);
	printf("\nDatabase creato da zero, ti conviene inserire dei brani! Riprendo...");
	ottieniDatabase();
}

db* new_ottieniDatabase() {
	printf("\nOttengo il database...");
	db database;
	//TODO
	//TODO
	//TODO
	//TODO
	//TODO
	return database;
}

db* ottieniBrani(db database) {
	printf("\nOttengo i brani...");
	FILE* fp=fopen(file_database, "r");
	if (fp==NULL) {
		printf("\n/!\\ Database file-based non trovato, procedo alla creazione...");
		creaDatabase();
	} else {
		*database.brano = malloc((MAX_CHAR*MAX_CHAR)*sizeof(database.brano));
		char temp[MAX_TEMP];
		char dati[MAX_TEMP][MAX_TEMP];
		char spaziatore[] = ",";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_TEMP, fp);
			char *ptr = strtok(temp, spaziatore);
			j=0;
			while(ptr!=NULL) {
				strcpy(dati[j], ptr);
				ptr=strtok(NULL, spaziatore);
				j++;
			}
			//TODO
		}
	}
}

// Funzione per trasferire in memoria il database file-based velocizzando la sua lettura.
// TODO: Rendere disponibile lo struct riempito a tutto il programma per evitare inutili ri-accessi
database* ottieniDatabase() {
	printf("\nOttengo il database...");
	//TODO: Trovare un metodo migliore per allocare dinamicamente
	FILE* fp=fopen(file_database, "r"); // Apro database
	if (fp==NULL) {
		printf("\n/!\\ Database file-based non trovato, procedo alla creazione...");
		creaDatabase();
	} else {
		if (controllaSeDatabaseVuoto()==0) {
			database *brani = malloc((MAX_CHAR*MAX_CHAR)*sizeof(database));
			// TODO: Allora questo, questo è da cambiare assolutamente
			char temp[MAX_TEMP]; // [DA CAMBIARE] Variabile temporanea per ottenere i dati
			char dati[MAX_TEMP][MAX_TEMP]; // [DA CAMBIARE] Array temporaneo per trasportare i dati
			char spaziatore[] = ","; // Il database divide i dati utilizzando lo spaziatore ,
			int i, j;
			i=0;
			// TODO: Trovare metodo migliore se esistente
			while(!feof(fp)) { // Fino a quando non arriva alla fine del file
				fgets(temp, MAX_TEMP, fp); // Ottiene la linea
				char *ptr = strtok(temp, spaziatore); // Imposta lo spaziatore
				j=0;
				while(ptr!=NULL) { // Fino a quando il puntatore non ha piu' niente da trasportare
					strcpy(dati[j], ptr); // Copia informazione nel punto i dell'array temporaneo
					ptr=strtok(NULL, spaziatore); // Passa al prossimo spaziatore
					j++;
				}
				// Blocco di organizzazione dei dati dall'array temporaneo allo struct finale
				brani[i].id = atoi(dati[0]);
				strcpy(brani[i].titolo, dati[1]);
				strcpy(brani[i].artista, dati[2]);
				strcpy(brani[i].feat, dati[3]);
				strcpy(brani[i].produttore, dati[4]);
				strcpy(brani[i].scrittore, dati[5]);
				strcpy(brani[i].album, dati[6]);
				strcpy(brani[i].durata, dati[7]);
				brani[i].anno = atoi(dati[8]); // Conversione da char a int del valore Anno
				brani[i].lingua = atoi(dati[9]);
				brani[i].ascolti = atoi(dati[10]);
				brani[i].gradimento = atof(dati[11]);
				i++;
			}
			fclose(fp);
			printf(" Fatto. %d brani caricati con successo.", i);
			return brani;
		} else {
			fclose(fp);
			printf(" Fatto. Nessun brano presente nel database file-based.");
		}
	}
	fclose(fp);
	return brani;
}

// Funzione per trasferire su file il database presente in memoria salvando così le modifiche.
void aggiornaDatabase() {
	printf("\nSalvando le modifiche effettuate al database...");
	backupDatabase("temp_db.txt");
	remove(file_database);
	int i=0;
	int nbrani=conteggiaBrani();
	while (i<nbrani) {
		char id[MAX_CHAR], anno[5], lingua[3], ascolti[MAX_CHAR], gradimento[MAX_CHAR];
		// Investigare su sprintf
		sprintf(id, "%d", brani[i].id);
		sprintf(anno, "%d", brani[i].anno);
		sprintf(lingua, "%d", brani[i].lingua);
		sprintf(ascolti, "%d", brani[i].ascolti);
		sprintf(gradimento, "%.1f", brani[i].gradimento);
		inserisciBranoGuidato(1, id, brani[i].titolo, brani[i].artista, brani[i].feat, brani[i].produttore, brani[i].scrittore, brani[i].album, brani[i].durata, anno, lingua, ascolti, gradimento);
		i++;
	}
	remove("temp_db.txt");
	printf("\nModifiche salvate.");
}
