/*
 * UNIBA/Ampere 0.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestoreUtenti.h"
#include "../database/Database.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"
#include "../sys/Messaggi.h"

int creareDatabaseSeNonEsiste() {
	int esito=0;
	creaCartella(cartella_database, true);
	FILE* fp = fopen(file_brani, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_albums, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_BranoArtista, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_artisti, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_BranoAlbum, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_generi, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_BranoGenere, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_playlists, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_PlaylistBrano, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	fp = fopen(file_utenti, "a");
	if (fp==NULL) esito=-1;
	fclose(fp);
	creaCartella(cartella_testi, true);
	return esito;
}

/**
 * -1: caricamento solo utente
 * 0: caricamento iniziale
 * 1: caricamento completo
 */
database ottenereDatabase(int modalita, database db) {
	// Blocco ottenimenti
	if (modalita==-1) {
		db = ottenereUtenti(db);
	} else if (modalita==0) {
		db = ottenereBrani(db);
		db = ottenereAlbums(db);
		db = ottenereArtisti(db);
		db = ottenereGeneri(db);
		db = ottenerePlaylists(db);
		// Blocco associazioni
		db = associareArtisti(db);
		db = associareAlbums(db);
		db = associareGeneri(db);
		db = associarePlaylists(db);
	} else if (modalita==1) {
		db = ottenereDatabase(-1, db);
		db = ottenereDatabase(0, db);
	}
	if (controllareSeAdmin(db))
		printf(C_VERDE"\nDatabase caricato."C_RESET);
	return db;
}

database ottenereBrani(database db) {
	db.brano = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct Brano));
	if (controllaSeFileVuoto(file_brani)==0) {
		FILE* fp=fopen(file_brani, "r");
		char temp[MAX_ENORME];
		char dati[5][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
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
			db.brano[i].anno = atoi(dati[3]);
			db.brano[i].ascolti = atoi(dati[4]);
			i++;
		}
		fclose(fp);
		if (controllareSeAdmin(db))
			printf("\n%d Brani caricati con "C_VERDE"successo."C_RESET, i);
	} else {
		inizializzareDatabase(db, 0);
		if (controllareSeAdmin(db))
			printf(C_GIALLO"\nNessun brano da caricare."C_RESET);
	}
	return db;
}

database ottenereAlbums(database db) {
	db.album = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct Album));
	if (controllaSeFileVuoto(file_albums)==0) {
		FILE* fp=fopen(file_albums, "r");
		char temp[MAX_ENORME];
		char dati[3][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
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
		if (controllareSeAdmin(db))
			printf("\n%d Album caricati con "C_VERDE"successo."C_RESET, i);
	} else {
		inizializzareDatabase(db, 1);
		if (controllareSeAdmin(db))
			printf(C_GIALLO"\nNessun album da caricare."C_RESET);
	}
	return db;
}

database ottenereArtisti(database db) {
	db.artista = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct Artista));
	if (controllaSeFileVuoto(file_artisti)==0) {
		FILE* fp=fopen(file_artisti, "r");
		char temp[MAX_ENORME];
		char dati[5][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
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
			strtok(dati[4], "\n");
			strcpy(db.artista[i].nome,dati[1]);
			strcpy(db.artista[i].cognome,dati[2]);
			strcpy(db.artista[i].nomeArte,dati[3]);
			strcpy(db.artista[i].linkBio,dati[4]);
			i++;
		}
		fclose(fp);
		if (controllareSeAdmin(db))
			printf("\n%d Artisti caricati con "C_VERDE"successo."C_RESET, i);
	} else {
		inizializzareDatabase(db, 2);
		if (controllareSeAdmin(db))
			printf(C_GIALLO"\nNessun artista da caricare."C_RESET);
	}
	return db;
}

database ottenereGeneri(database db) {
	db.genere = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct Genere));
	if (controllaSeFileVuoto(file_generi)==0) {
		FILE* fp=fopen(file_generi, "r");
		char temp[MAX_ENORME];
		char dati[2][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
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
		if (controllareSeAdmin(db))
			printf("\n%d Generi caricati con "C_VERDE"successo."C_RESET, i);
	} else {
		inizializzareDatabase(db, 3);
		if (controllareSeAdmin(db))
			printf(C_GIALLO"\nNessun genere da caricare."C_RESET);
	}
	return db;
}

database ottenerePlaylists(database db) {
	db.playlist = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct Playlist));
	if (controllaSeFileVuoto(file_playlists)==0) {
		FILE* fp=fopen(file_playlists, "r");
		char temp[MAX_ENORME];
		char dati[5][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
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
			if (strcmp(dati[4],"true")==0) {
				db.playlist[i].pubblica = true;
			} else {
				db.playlist[i].pubblica = false;
			}
			i++;
		}
		fclose(fp);
		if (controllareSeAdmin(db))
			printf("\n%d Playlist caricate con "C_VERDE"successo."C_RESET, i);
	} else {
		inizializzareDatabase(db, 4);
		if (controllareSeAdmin(db))
			printf(C_GIALLO"\nNessuna playlist da caricare."C_RESET);
	}
	return db;
}
database ottenereUtenti(database db) {
	db.utente = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct Utente));
	if (controllaSeFileVuoto(file_utenti)==0) {
		FILE* fp=fopen(file_utenti, "r");
		char temp[MAX_ENORME];
		char dati[4][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
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
		printf("\n%d Utenti caricati con "C_VERDE"successo."C_RESET, i);
	} else {
		inizializzareDatabase(db, -1);
		printf(C_GIALLO"\nNessun utente da caricare."C_RESET);
	}
	return db;
}

database associareArtisti(database db) {
	db.branoArtista = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct BranoArtista));
	if (controllaSeFileVuoto(file_BranoArtista)==0) {
		FILE* fp=fopen(file_BranoArtista, "r");
		char temp[MAX_ENORME];
		char dati[2][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
			char *ptr = strtok(temp, spaziatore);
			j=0;
			while(ptr!=NULL) {
				strcpy(dati[j], ptr);
				ptr=strtok(NULL, spaziatore);
				j++;
			}
			db.branoArtista[i].idBrano = atoi(dati[0]);
			db.branoArtista[i].idArtista = atoi(dati[1]);
			i++;
		}
		fclose(fp);
		if (controllareSeAdmin(db))
			printf("\n%d Associazioni brano-artista "C_VERDE"effettuate."C_RESET, i);
	} else {
		inizializzareDatabase(db, 5);
		if (controllareSeAdmin(db))
			printf(C_GIALLO"\nNessuna associazione brano-artista da effettuare."C_RESET);
	}
	return db;
}

database associareAlbums(database db) {
	db.branoAlbum = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct BranoAlbum));
	if (controllaSeFileVuoto(file_BranoAlbum)==0) {
		FILE* fp=fopen(file_BranoAlbum, "r");
		char temp[MAX_ENORME];
		char dati[2][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
			char *ptr = strtok(temp, spaziatore);
			j=0;
			while(ptr!=NULL) {
				strcpy(dati[j], ptr);
				ptr=strtok(NULL, spaziatore);
				j++;
			}
			db.branoAlbum[i].idAlbum = atoi(dati[0]);
			db.branoAlbum[i].idBrano = atoi(dati[1]);
			i++;
		}
		fclose(fp);
		if (controllareSeAdmin(db))
			printf("\n%d associazioni brano-album "C_VERDE"effettuate."C_RESET, i);
	} else {
		inizializzareDatabase(db, 6);
		if (controllareSeAdmin(db))
			printf(C_GIALLO"\nNessuna associazione brano-album da effettuare."C_RESET);
	}
	return db;
}

database associareGeneri(database db) {
	db.branoGenere = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct BranoGenere));
	if (controllaSeFileVuoto(file_BranoGenere)==0) {
		FILE* fp=fopen(file_BranoGenere, "r");
		char temp[MAX_ENORME];
		char dati[2][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
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
		if (controllareSeAdmin(db))
			printf("\n%d Associazioni genere-brano "C_VERDE"effettuate."C_RESET, i);
	} else {
		inizializzareDatabase(db, 7);
		if (controllareSeAdmin(db))
			printf(C_GIALLO"\nNessuna associazione genere-brano da effettuare."C_RESET);
	}
	return db;
}

database associarePlaylists(database db) {
	db.playlistBrano = malloc((MAX_ENORME*MAX_ENORME)*sizeof(struct PlaylistBrano));
	if (controllaSeFileVuoto(file_PlaylistBrano)==0) {
		FILE* fp=fopen(file_PlaylistBrano, "r");
		char temp[MAX_ENORME];
		char dati[2][MAX_ENORME];
		char spaziatore[2] = "|";
		int i=0, j=0;
		while(!feof(fp)) {
			fgets(temp, MAX_ENORME, fp);
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
		if (controllareSeAdmin(db))
			printf("\n%d Associazioni brano-playlist "C_VERDE"effettuate."C_RESET, i);
	} else {
		inizializzareDatabase(db, 8);
		if (controllareSeAdmin(db))
			printf(C_GIALLO"\nNessuna associazione brano-playlist da effettuare."C_RESET);
	}
	return db;
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
database inizializzareDatabase(database db, int modalita) {
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
		strcpy(db.artista[0].nomeArte,"0");
	} else if (modalita==3) {
		db.genere[0].id = 0;
		strcpy(db.genere[0].nome,"0");
	} else if (modalita==4) {
		db.playlist[0].id = 0;
		db.playlist[0].idUtente = 0;
		strcpy(db.playlist[0].nome,"0");
		strcpy(db.playlist[0].descrizione,"0");
	} else if (modalita==5) {
		db.branoArtista[0].idArtista = 0;
		db.branoArtista[0].idBrano = 0;
	} else if (modalita==6) {
		db.branoAlbum[0].idAlbum = 0;
		db.branoAlbum[0].idBrano = 0;
	} else if (modalita==7) {
		db.branoGenere[0].idGenere = 0;
		db.branoGenere[0].idBrano = 0;
	} else if (modalita==8) {
		db.playlistBrano[0].idPlaylist = 0;
		db.playlistBrano[0].idBrano = 0;
	}
	return db;
}

database liberareDatabase(database db) {
	free(db.brano); db.brano=NULL;
	free(db.album); db.brano=NULL;
	free(db.artista); db.artista=NULL;
	free(db.genere); db.genere=NULL;
	free(db.playlist); db.playlist=NULL;
	free(db.utente); db.utente=NULL;
	free(db.branoAlbum); db.branoAlbum=NULL;
	free(db.branoArtista); db.branoArtista=NULL;
	free(db.branoGenere); db.branoGenere=NULL;
	free(db.playlistBrano); db.playlistBrano=NULL;
	return db;
}
