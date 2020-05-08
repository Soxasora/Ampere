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
#include "../database/Database.h"
#include "../sys/Errore.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

int creaDatabaseSeNonEsiste() {
	int esito=0;
	creaCartella(cartella_database, true);
	FILE* fp = fopen(file_brani, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_albums, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_associazioneartisti, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_artisti, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_collezione, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_generi, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_tipobrano, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_playlists, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_raccolta, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_utenti, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	creaCartella(cartella_testi, true);
	return esito;
}

database ottieniDatabaseParziale() {
	ottieniUtenti();
	return db;
}

database ottieniDatabase() {
	// Blocco ottenimenti
	ottieniBrani();
	ottieniAlbums();
	ottieniArtisti();
	ottieniGeneri();
	ottieniPlaylists();
	// Blocco associazioni
	associaArtisti();
	associaAlbum();
	associaGeneri();
	associaPlaylist();
	if (isAdmin())
		printf("\nDatabase caricato con successo.");
	return db;
}

void ottieniBrani() {
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
		if (isAdmin())
			printf("\n%d Brani caricati con successo.", i);
	} else {
		inizializzaDatabase(0);
		if (isAdmin())
			printf("\nNessun brano da caricare.");
	}
}

void ottieniAlbums() {
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
		if (isAdmin())
			printf("\n%d Album caricati con successo.", i);
	} else {
		inizializzaDatabase(1);
		if (isAdmin())
			printf("\nNessun album da caricare.");
	}
}

void ottieniArtisti() {
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
		if (isAdmin())
			printf("\n%d Artisti caricati con successo.", i);
	} else {
		inizializzaDatabase(2);
		if (isAdmin())
			printf("\nNessun artista da caricare.");
	}
}

void ottieniGeneri() {
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
		if (isAdmin())
			printf("\n%d Generi caricati con successo.", i);
	} else {
		inizializzaDatabase(3);
		if (isAdmin())
			printf("\nNessun genere da caricare.");
	}
}

void ottieniPlaylists() {
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
			if (comparaStringhe(dati[4],"true")==0) {
				db.playlist[i].pubblica = true;
			} else {
				db.playlist[i].pubblica = false;
			}
			i++;
		}
		fclose(fp);
		if (isAdmin())
			printf("\n%d Playlist caricate con successo.", i);
	} else {
		inizializzaDatabase(4);
		if (isAdmin())
			printf("\nNessuna playlist da caricare.");
	}
}
void ottieniUtenti() {
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
			strtok(dati[3], "\n");
			strcpy(db.utente[i].username,dati[1]);
			strcpy(db.utente[i].password,dati[2]);
			if(comparaStringhe(dati[3],"true")==0) {
				db.utente[i].admin = true;
			} else {
				db.utente[i].admin = false;
			}
			i++;
		}
		fclose(fp);
		printf("\n%d Utenti caricati con successo.", i);
	} else {
		inizializzaDatabase(-1);
		printf("\nNessun utente da caricare.");
	}
}

void associaArtisti() {
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
		if (isAdmin())
			printf("\n%d Associazioni brano-artista effettuate.", i);
	} else {
		inizializzaDatabase(5);
		if (isAdmin())
			printf("\nNessuna associazione brano-artista da effettuare.");
	}
}

void associaAlbum() {
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
		if (isAdmin())
			printf("\n%d associazioni brano-album effettuate.", i);
	} else {
		inizializzaDatabase(6);
		if (isAdmin())
			printf("\nNessuna associazione brano-album da effettuare.");
	}
}

void associaGeneri() {
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
		if (isAdmin())
			printf("\n%d Associazioni genere-brano effettuate.", i);
	} else {
		inizializzaDatabase(7);
		if (isAdmin())
			printf("\nNessuna associazione genere-brano da effettuare.");
	}
}

void associaPlaylist() {
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
		if (isAdmin())
			printf("\n%d Associazioni brano-playlist effettuate.", i);
	} else {
		inizializzaDatabase(8);
		if (isAdmin())
			printf("\nNessuna associazione brano-playlist da effettuare.");
	}
}

/**
 * Le modalità sono le seguenti:
 * -1: Utente
 * 0: Brano
 * 1: Album
 * 2: Artista
 * 3: Genere
 * 4: Playlist
 * 5: Associazione artista-brano
 * 6: Associazione album-brano
 * 7: Associazione genere-brano
 * 8: Associazione playlist-brano
 */
void inizializzaDatabase(int modalita) {
	if (modalita==-1) {
		db.utente[0].id = 0;
		strcpy(db.utente[0].username,"0");
		strcpy(db.utente[0].password,"0");
		db.utente[0].admin = false;
	} else if (modalita==0) {
		db.brano[0].id = 0;
		strcpy(db.brano[0].titolo,"0");
		db.brano[0].durata = 0;
		db.brano[0].anno = 0;
		db.brano[0].ascolti = 0;
	} else if (modalita==1) {
		db.album[0].id = 0;
		strcpy(db.album[0].titolo,"0");
		db.album[0].anno = 0;
	} else if (modalita==2) {
		db.artista[0].id = 0;
		strcpy(db.artista[0].nome,"0");
		strcpy(db.artista[0].cognome,"0");
		strcpy(db.artista[0].nomearte,"0");
	} else if (modalita==3) {
		db.genere[0].id = 0;
		strcpy(db.genere[0].nome,"0");
	} else if (modalita==4) {
		db.playlist[0].id = 0;
		db.playlist[0].idUtente = 0;
		strcpy(db.playlist[0].nome,"0");
		strcpy(db.playlist[0].descrizione,"0");
	} else if (modalita==5) {
		db.artistaBrano[0].idArtista = 0;
		db.artistaBrano[0].idBrano = 0;
	} else if (modalita==6) {
		db.albumBrano[0].idAlbum = 0;
		db.albumBrano[0].idBrano = 0;
	} else if (modalita==7) {
		db.branoGenere[0].idGenere = 0;
		db.branoGenere[0].idBrano = 0;
	} else if (modalita==8) {
		db.playlistBrano[0].idPlaylist = 0;
		db.playlistBrano[0].idBrano = 0;
	}
}
