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
#include "../database/Database.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

database ottieniDatabase() {
	printf("\nOttengo il db...");
	// Blocco ottenimenti
	ottieniBrani();
	ottieniAlbums();
	ottieniArtisti();
	ottieniGeneri();
	ottieniPlaylists();
	ottieniUtenti();
	// Blocco associazioni
	associaArtisti();
	associaAlbum();
	associaGeneri();
	associaPlaylist();
	printf("\nDatabase caricato con successo.");
	return db;
}

void ottieniBrani() {
	printf("\nOttengo i brani...");
	db.brano = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.brano));
	if (controllaSeFileVuoto(file_brani)==0) {
		FILE* fp=fopen(file_brani, "r");
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
			db.brano[i].id = atoi(dati[0]);
			strtok(dati[1], "\n");
			strcpy(db.brano[i].titolo,dati[1]);
			db.brano[i].durata = atoi(dati[2]);
			db.brano[i].album = atoi(dati[3]);
			db.brano[i].anno = atoi(dati[4]);
			db.brano[i].ascolti = atoi(dati[5]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d brani caricati con successo.", i);
	} else {
		printf(" Nessun brano da caricare.");
	}
}

void ottieniAlbums() {
	printf("\nOttengo gli album...");
	db.album = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.album));
	if (controllaSeFileVuoto(file_albums)==0) {
		FILE* fp=fopen(file_albums, "r");
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
			db.album[i].id = atoi(dati[0]);
			strtok(dati[1], "\n");
			strcpy(db.album[i].titolo,dati[1]);
			db.album[i].anno = atoi(dati[2]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d album caricati con successo.", i);
	} else {
		printf(" Nessun album da caricare.");
	}
}

void ottieniArtisti() {
	printf("\nOttengo gli artisti...");
	db.artista = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.artista));
	if (controllaSeFileVuoto(file_artisti)==0) {
		FILE* fp=fopen(file_artisti, "r");
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
			db.artista[i].id = atoi(dati[0]);
			strtok(dati[1], "\n");
			strtok(dati[2], "\n");
			strtok(dati[3], "\n");
			strcpy(db.artista[i].nome,dati[1]);
			strcpy(db.artista[i].cognome,dati[2]);
			strcpy(db.artista[i].nomearte,dati[3]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d artisti caricati con successo.", i);
	} else {
		printf(" Nessun artista da caricare.");
	}
}

void ottieniGeneri() {
	printf("\nOttengo i generi...");
	db.genere = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.genere));
	if (controllaSeFileVuoto(file_generi)==0) {
		FILE* fp=fopen(file_generi, "r");
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
			db.genere[i].id = atoi(dati[0]);
			strtok(dati[1], "\n");
			strcpy(db.genere[i].nome,dati[1]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d generi caricati con successo.", i);
	} else {
		printf(" Nessun genere da caricare.");
	}
}

void ottieniPlaylists() {
	printf("\nOttengo le playlist...");
	db.playlist = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.playlist));
	if (controllaSeFileVuoto(file_playlists)==0) {
		FILE* fp=fopen(file_playlists, "r");
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
			db.playlist[i].id = atoi(dati[0]);
			db.playlist[i].idUtente = atoi(dati[1]);
			strtok(dati[2], "\n");
			strtok(dati[3], "\n");
			strcpy(db.playlist[i].nome,dati[2]);
			strcpy(db.playlist[i].descrizione,dati[3]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d playlist caricate con successo.", i);
	} else {
		printf(" Nessuna playlist da caricare.");
	}
}
void ottieniUtenti() {
	printf("\nOttengo gli utenti...");
	db.utente = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.utente));
	if (controllaSeFileVuoto(file_utenti)==0) {
		FILE* fp=fopen(file_utenti, "r");
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
			db.utente[i].id = atoi(dati[0]);
			strtok(dati[1], "\n");
			strtok(dati[2], "\n");
			strcpy(db.utente[i].username,dati[1]);
			strcpy(db.utente[i].password,dati[2]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d utenti caricati con successo.", i);
	} else {
		printf(" Nessun utente da caricare.");
	}
}

void associaArtisti() {
	printf("\nAssocio i brani agli artisti...");
	db.artistaBrano = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.artistaBrano));
	if (controllaSeFileVuoto(file_associazioneartisti)==0) {
		FILE* fp=fopen(file_associazioneartisti, "r");
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
			db.artistaBrano[i].idBrano = atoi(dati[0]);
			db.artistaBrano[i].idArtista = atoi(dati[1]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d associazioni brano-artista effettuate.", i);
	} else {
		printf(" Nessuna associazione brano-artista da effettuare.");
	}
}

void associaAlbum() {
	printf("\nAssocio i brani agli album...");
	db.albumBrano = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.albumBrano));
	if (controllaSeFileVuoto(file_collezione)==0) {
		FILE* fp=fopen(file_collezione, "r");
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
			db.albumBrano[i].idAlbum = atoi(dati[0]);
			db.albumBrano[i].idBrano = atoi(dati[1]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d associazioni brano-album effettuate.", i);
	} else {
		printf(" Nessuna associazione brano-album da effettuare.");
	}
}

void associaGeneri() {
	printf("\nAssocio i generi ai brani...");
	db.branoGenere = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.branoGenere));
	if (controllaSeFileVuoto(file_tipobrano)==0) {
		FILE* fp=fopen(file_tipobrano, "r");
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
			db.branoGenere[i].idBrano = atoi(dati[0]);
			db.branoGenere[i].idGenere = atoi(dati[1]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d associazioni genere-brano effettuate.", i);
	} else {
		printf(" Nessuna associazione genere-brano da effettuare.");
	}
}

void associaPlaylist() {
	printf("\nAssocio i brani alle playlist...");
	db.playlistBrano = malloc((MAX_CHAR*MAX_CHAR)*sizeof(db.playlistBrano));
	if (controllaSeFileVuoto(file_raccolta)==0) {
		FILE* fp=fopen(file_raccolta, "r");
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
			db.playlistBrano[i].idPlaylist = atoi(dati[0]);
			db.playlistBrano[i].idBrano = atoi(dati[1]);
			i++;
		}
		fclose(fp);
		printf(" Fatto. %d associazioni brano-playlist effettuate.", i);
	} else {
		printf(" Nessuna associazione brano-playlist da effettuare.");
	}
}
