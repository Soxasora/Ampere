/*
 * UNIBA/Ampere 1.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ricerca/MotoreRicerca.h"
#include "../gestori/GestoreAssociazioni.h"
#include "../gestori/GestoreFile.h"
#include "../gestori/GestoreBrani.h"

#include "../database/Brano.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Messaggi.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void inserireBranoGuidato(database *db) {
	char scelta='a';
	int i=0, nArtisti=0, nAlbum=0, nGeneri=0;
	int* idArtisti = calloc(MAX_MEDIO, sizeof(int));
	int* idAlbum = calloc(MAX_MEDIO, sizeof(int));
	int* idGeneri = calloc(MAX_MEDIO, sizeof(int));
	char *titolo, *artista, *album, *genere;
	int durata=0, anno=0, ascolti=0;
	// Registrazione
	do {
		if ((titolo=calloc(MAX_MEDIO, sizeof(char)))) {
			printf("\nInserisci titolo: ");
			titolo = inputStringa(MAX_MEDIO,titolo);
		}
		do {
			printf("\nQuanti artisti hanno lavorato su questo brano? ");
			nArtisti = inputNumero();
		} while (nArtisti<1||nArtisti>MAX_MEDIO);
		i=0;
		while (i<nArtisti) {
			do {
				if ((artista=calloc(MAX_MEDIO, sizeof(char)))) {
					
					printf("\nInserisci nome artista n.%d: ", i+1);
					artista = inputStringa(MAX_MEDIO,artista);
					creareArtistaSeNonEsiste(db, artista);
				}
			} while (db->ultimoEsito!=0);
			idArtisti[i] = controllareEsistenzaArtista(db, artista);
			if (artista!=NULL) {
				free(artista);
				artista=NULL;
			}
			i++;
		}
		do {
			printf("\nDi quanti album fa parte questa canzone? ");
			nAlbum = inputNumero();
		} while (nAlbum<1||nAlbum>MAX_MEDIO);
		i=0;
		while (i<nAlbum) {
			do {
				if ((album=calloc(MAX_MEDIO, sizeof(char)))) {
					
					printf("\nInserisci nome album n.%d: ", i+1);
					album = inputStringa(MAX_MEDIO,album);
					creareAlbumSeNonEsiste(db, album);
				}
			} while (db->ultimoEsito!=0);
			idAlbum[i] = controllareEsistenzaAlbum(db, album);
			if (album!=NULL) {
				free(album);
				album=NULL;
			}
			i++;
		}
		do {
			printf("\nQuanti generi ha questa canzone? ");
			nGeneri = inputNumero();
		} while (nGeneri<1||nGeneri>MAX_MEDIO);
		i=0;
		while (i<nGeneri) {
			do {
				if ((genere=calloc(MAX_MEDIO, sizeof(char)))) {
					
					printf("\nInserisci genere n.%d del brano: ", i+1);
					genere = inputStringa(MAX_MEDIO,genere);
					creareGenereSeNonEsiste(db, genere);
				}
			} while (db->ultimoEsito!=0);
			idGeneri[i] = controllareEsistenzaGenere(db, genere);
			if (genere!=NULL) {
				free(genere);
				genere=NULL;
			}
			i++;
		}
		
		do {
			printf("\nInserisci durata del brano in secondi: ");
			durata = inputNumero();
		} while (durata<=0);
		do {
			printf("\nInserisci anno d'uscita del brano: ");
			anno = inputNumero();
		} while (anno<1950);
		do {
			printf("\nInserisci numero d'ascolti del brano: ");
			ascolti = inputNumero();
		} while (ascolti<=0);
		struct Brano nuovoBrano = creareBrano(titolo, durata, anno, ascolti);
		if (titolo!=NULL) {
			free(titolo);
			titolo=NULL;
		}
		// Mostra anteprima del brano
		mostrareAnteprimaBrano(db, nuovoBrano, idArtisti, idAlbum, idGeneri);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			// Ricerca similitudini
			controllareSimilitudineBrano(db, nuovoBrano);
			if (db->ultimoEsito==0) {
				inserireBrano(db, nuovoBrano, idArtisti, idAlbum, idGeneri);
			}
			db->ultimoEsito=0;
		} else {
			db->ultimoEsito=-1;
		}
		if (idArtisti!=NULL) {
			free(idArtisti);
			idArtisti=NULL;
		}
		if (idAlbum!=NULL) {
			free(idAlbum);
			idAlbum=NULL;
		}
		if (idGeneri!=NULL) {
			free(idGeneri);
			idGeneri=NULL;
		}
	} while (db->ultimoEsito!=0);
	
}

struct Brano creareBrano(char titolo[], int durata, int anno, int ascolti) {
	struct Brano nuovoBrano;
	nuovoBrano.id = -1;
	strcpy(nuovoBrano.titolo,titolo);
	nuovoBrano.durata = durata;
	nuovoBrano.anno = anno;
	nuovoBrano.ascolti = ascolti;
	return nuovoBrano;
}

void mostrareAnteprimaBrano(database *db, struct Brano nuovoBrano, int* idArtisti, int* idAlbum, int* idGeneri) {
	int i=0;
	int posAlbum = 0, posArtista = 0, posGenere = 0;
	char *tempo = convertireSecondiInTempo(nuovoBrano.durata);
	printf("\nIl brano che stai per inserire ha questi dettagli:"
		   "\nTitolo: %s"
		   "\nDurata: %s"
		   "\nArtisti: ", nuovoBrano.titolo, tempo);
	if (tempo!=NULL) {
		free(tempo); tempo=NULL;
	}
	i=0;
	while (idArtisti[i]!=0) {
		posArtista = ottenerePosDaID(db, 2, idArtisti[i]);
		if (i!=0)
			printf(", ");
		printf("%s", db->artista[posArtista].nomeArte);
		i++;
	}
	printf("\nAlbum: ");
	i=0;
	while (idAlbum[i]!=0) {
		posAlbum = ottenerePosDaID(db, 1, idAlbum[i]);
		if (i!=0)
			printf(", ");
		printf("%s", db->album[posAlbum].titolo);
		i++;
	}
	printf("\nGeneri: ");
	i=0;
	while (idGeneri[i]!=0) {
		posGenere = ottenerePosDaID(db, 3, idGeneri[i]);
		if (i!=0)
			printf(", ");
		printf("%s", db->genere[posGenere].nome);
		i++;
	}
	printf("\nAnno: %d"
		   "\nAscolti: %d", nuovoBrano.anno, nuovoBrano.ascolti);
}

void inserireBrano(database *db, struct Brano nuovoBrano, int idArtisti[], int idAlbum[], int idGeneri[]) {
	cPrintf(C_VERDE, "\nInserimento del brano in corso... potrebbe esserci piu' di una associazione.");
	int i=0;
	int n=contareNelDatabase(db,0);
	nuovoBrano.id = trovareUltimoId(db, 0)+1;
	db->brano[n] = nuovoBrano;
	// Associazioni
	i=0;
	while (idArtisti[i]!=0) {
		inserireAssociazioneArtista(db,creareAssociazioneArtista(nuovoBrano.id, idArtisti[i]));
		i++;
	}
	i=0;
	while (idAlbum[i]!=0) {
		inserireAssociazioneAlbum(db,creareAssociazioneAlbum(nuovoBrano.id, idAlbum[i]));
		i++;
	}
	i=0;
	while (idGeneri[i]!=0) {
		inserireAssociazioneGenere(db,creareAssociazioneGenere(nuovoBrano.id, idGeneri[i]));
		i++;
	}
	successo(1);
	if (salvataggioDiretto) {
		salvareBraniSuFile(db);
	} else {
		db->modificato=true;
	}
	
}

void controllareSimilitudineBrano(database *db, struct Brano nuovoBrano) {
	cPrintf(C_CIANO,"\nRicerco eventuali similitudini con i brani gia' presenti...");
	char scelta='a';
	int occorrenze=0, i=0, n=contareNelDatabase(db, 0);
	bool trovato=false;
	while (i<n) {
		occorrenze=0;
		if (comparareStringhe(db->brano[i].titolo, nuovoBrano.titolo)==0) {
			occorrenze++;
			if (db->brano[i].anno == nuovoBrano.anno) {
				occorrenze++;
			}
			if (db->brano[i].durata == nuovoBrano.durata) {
				occorrenze++;
			}
		}
		if (occorrenze>0) {
			printf("\n\n");
			informazione(300);
			cPrintf(C_CIANO,"\nBrano simile: ");
			mostrareSingoloBrano(db, db->brano[i].id);
			trovato=true;
		}
		i++;
	}

	if (trovato) {
		scelta = richiesta(6);
		if (scelta=='N'||scelta=='n') {
			db->ultimoEsito=-1;
		} else {
			db->ultimoEsito=0;
		}
	} else {
		successo(300);
		db->ultimoEsito=0;
	}
	
}

void inserireBranoSuFile(struct Brano brano) {
	FILE* fp=fopen(file_brani, "a");
	if (controllareSeFileVuoto(file_brani)==1) {
		fprintf(fp, "%d|%s|%d|%d|%d", brano.id, brano.titolo, brano.durata, brano.anno, brano.ascolti);
	} else {
		fprintf(fp, "\n%d|%s|%d|%d|%d", brano.id, brano.titolo, brano.durata, brano.anno, brano.ascolti);
	}
	fclose(fp);
}

void modificareBranoGuidato(database *db) {
	int id=0, campo=-1;
	char scelta='a';
	moduloRicercaBrani(db);
	while (ottenerePosDaID(db, 0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da modificare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 0,id)==-1) {
			attenzione(211);
		}
	}
	printf("\nHai scelto il brano:");
	mostrareSingoloBrano(db, id);
	
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		do {
			printf("\n===[Sistema di "C_GIALLO"modifica brani"C_RESET"]===");
			printf("\n[1] Modifica il "C_CIANO"Titolo"C_RESET);
			printf("\n[2] Modifica la "C_CIANO"Durata"C_RESET);
			printf("\n[3] Modifica "C_CIANO"l'Anno"C_RESET);
			printf("\n[4] Modifica gli "C_CIANO"Ascolti"C_RESET);
			printf("\n[5] Modifica gli "C_CIANO"artisti d'appartenenza"C_RESET);
			printf("\n[6] Modifica gli "C_CIANO"album d'appartenenza"C_RESET);
			printf("\n[7] Modifica i "C_CIANO"generi d'appartenenza"C_RESET);
			printf("\n[0] Esci");
			while (campo<0||campo>7) {
				printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
				campo = inputNumero();
			}
			if (campo!=0) {
				creareBranoModificato(db, campo, id);
			} else {
				db->ultimoEsito=-2;
			}
		} while (db->ultimoEsito==-1);
	}
	
}

void creareBranoModificato(database *db, int campo, int id) {
	char scelta='a';
	int pos = ottenerePosDaID(db, 0, id);
	struct Brano branoModificato = db->brano[pos];
	int* idAssociazioni = calloc(MAX_MEDIO, sizeof(int));
	do {
		
		if (campo==1) {
			char *titolo = calloc(MAX_MEDIO, sizeof(char));
			printf("\nInserisci nuovo titolo: ");
			titolo = inputStringa(MAX_MEDIO,titolo);
			strcpy(branoModificato.titolo, titolo);
			if (titolo!=NULL) {
				free(titolo);
				titolo=NULL;
			}
		} else if (campo==2) {
			int durata=0;
			while (durata<1) {
				printf("\nInserisci nuova durata (in secondi): ");
				durata = inputNumero();
			}
			branoModificato.durata = durata;
		} else if (campo==3) {
			int anno=0;
			while (anno<1950) {
				printf("\nInserisci nuovo anno: ");
				anno = inputNumero();
			}
			branoModificato.anno = anno;
		} else if (campo==4) {
			int ascolti=0;
			while (ascolti<=0) {
				printf("\nInserisci nuovi ascolti: ");
				ascolti = inputNumero();
			}
			branoModificato.ascolti = ascolti;
		} else if (campo==5) {
			char *artista;
			int i=0, nArtisti=0;
			idAssociazioni = calloc(MAX_MEDIO, sizeof(int));
			printf("\nQuanti artisti ha il brano? ");
			nArtisti = inputNumero();
			i=0;
			while (i<nArtisti) {
				do {
					if ((artista = calloc(MAX_MEDIO, sizeof(char)))) {
						printf("\nInserisci nome d'arte artista n.%d: ", i+1);
						artista = inputStringa(MAX_MEDIO,artista);
						creareArtistaSeNonEsiste(db, artista);
						idAssociazioni[i] = controllareEsistenzaArtista(db, artista);
					}
				} while (db->ultimoEsito!=0);
				if (artista!=NULL) {
					free(artista);
					artista=NULL;
				}
				i++;
			}
		} else if (campo==6) {
			char *album;
			int i=0, nAlbum=0;
			idAssociazioni = calloc(MAX_MEDIO, sizeof(int));
			printf("\nQuanti album ha il brano? ");
			nAlbum = inputNumero();
			i=0;
			while (i<nAlbum) {
				do {
					if ((album = calloc(MAX_MEDIO, sizeof(char)))) {
						printf("\nInserisci nome album n.%d: ", i+1);
						album = inputStringa(MAX_MEDIO,album);
						creareAlbumSeNonEsiste(db, album);
						idAssociazioni[i] = controllareEsistenzaAlbum(db, album);
					}
				} while (db->ultimoEsito!=0);
				if (album!=NULL) {
					free(album);
					album=NULL;
				}
				i++;
			}
		} else if (campo==7) {
			char *genere;
			int i=0, nGeneri=0;
			idAssociazioni = calloc(MAX_MEDIO, sizeof(int));
			printf("\nQuanti generi ha il brano? ");
			nGeneri = inputNumero();
			i=0;
			while (i<nGeneri) {
				do {
					if ((genere = calloc(MAX_MEDIO, sizeof(char)))) {
						printf("\nInserisci nome del genere n.%d: ", i+1);
						genere = inputStringa(MAX_MEDIO, genere);
						creareGenereSeNonEsiste(db, genere);
						idAssociazioni[i] = controllareEsistenzaGenere(db, genere);
					}
				} while (db->ultimoEsito!=0);
				if (genere!=NULL) {
					free(genere);
					genere=NULL;
				}
				i++;
			}
		}
		mostrareAnteprimaModificaBrano(db, id, campo, branoModificato, idAssociazioni);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			modificareBrano(db, id, campo, branoModificato, idAssociazioni);
			db->ultimoEsito=0;
		} else {
			scelta = richiesta(3);
			if (scelta=='Y'||scelta=='y') {
				db->ultimoEsito=-2;
			} else {
				db->ultimoEsito=-1;
			}
		}
		if (idAssociazioni!=NULL) {
			free(idAssociazioni);
			idAssociazioni=NULL;
		}
	} while (db->ultimoEsito==-2);
	
}

void mostrareAnteprimaModificaBrano(database *db, int idBrano, int campo, struct Brano branoModificato, int idAssociazioni[]) {
	printf("\n===[Brano ORIGINALE]===");
	mostrareSingoloBrano(db, idBrano);
	printf("\n\n===[Brano MODIFICATO]===");
	char *tempo = convertireSecondiInTempo(branoModificato.durata);
	int i=0;
	printf("\nTitolo: %s"
		   "\nDurata: %s", branoModificato.titolo, tempo);
	if (tempo!=NULL) {
		free(tempo); tempo=NULL;
	}
	if (campo==5) {
		printf(C_VERDE"\n[MODIFICATO]"C_RESET" Artisti: ");
		int posArtista=0;
		while (idAssociazioni[i]!=0) {
			posArtista = ottenerePosDaID(db, 2, idAssociazioni[i]);
			if (i!=0)
				printf(", ");
			printf("%s", db->artista[posArtista].nomeArte);
			i++;
		}
	} else {
		mostrareAssociazioni(db, 0, idBrano);
	}
	if (campo==6) {
		printf(C_VERDE"\n[MODIFICATO]"C_RESET" Album: ");
		int posAlbum = 0;
		while (idAssociazioni[i]!=0) {
			posAlbum = ottenerePosDaID(db, 1, idAssociazioni[i]);
			if (i!=0)
				printf(", ");
			printf("%s", db->album[posAlbum].titolo);
			i++;
		}
	} else {
		mostrareAssociazioni(db, 1, idBrano);
	}
	if (campo==7) {
		printf(C_VERDE"\n[MODIFICATO]"C_RESET" Generi: ");
		int posGenere = 0;
		while (idAssociazioni[i]!=0) {
			posGenere = ottenerePosDaID(db, 3, idAssociazioni[i]);
			if (i!=0)
				printf(", ");
			printf("%s", db->genere[posGenere].nome);
			i++;
		}
	} else {
		mostrareAssociazioni(db, 2, idBrano);
	}
	printf("\nAnno: %d"
		   "\nAscolti: %d", branoModificato.anno, branoModificato.ascolti);
}

void modificareBrano(database *db, int idBrano, int campo, struct Brano branoModificato, int idAssociazioni[]) {
	int posBrano = ottenerePosDaID(db, 0, idBrano);
	db->brano[posBrano] = branoModificato;
	// Associazioni
	int i=0;
	if (campo==5) {
		cancellareAssociazioniArtisti(db, idBrano);
		i=0;
		while (idAssociazioni[i]!=0) {
			inserireAssociazioneArtista(db,creareAssociazioneArtista(branoModificato.id, idAssociazioni[i]));
			i++;
		}
	} else if (campo==6) {
		cancellareAssociazioniAlbum(db, idBrano);
		i=0;
		while (idAssociazioni[i]!=0) {
			inserireAssociazioneAlbum(db,creareAssociazioneAlbum(branoModificato.id, idAssociazioni[i]));
			i++;
		}
	} else if (campo==7) {
		cancellareAssociazioniGenere(db, idBrano);
		i=0;
		while (idAssociazioni[i]!=0) {
			inserireAssociazioneGenere(db,creareAssociazioneGenere(branoModificato.id, idAssociazioni[i]));
			i++;
		}
	}
	successo(7);
	if (salvataggioDiretto) {
		salvareBraniSuFile(db);
	} else {
		db->modificato=true;
	}
	
}

void cancellareBranoGuidato(database *db) {
	int id=0;
	char scelta='a';
	moduloRicercaBrani(db);
	while (ottenerePosDaID(db, 0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da cancellare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 0,id)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
	printf("\nHai scelto il brano:");
	mostrareSingoloBrano(db, id);
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		cancellareBrano(db, id);
	}
	
}

void cancellareBrano(database *db, int id) {
	int n = contareNelDatabase(db,0);
	int i = ottenerePosDaID(db, 0, id);
	while (i<n-1) {
		db->brano[i] = db->brano[i+1];
		i++;
	}
	db->brano[n-1].id = 0;
	cancellareAssociazioniBrano(db, id);
	successo(13);
	if (salvataggioDiretto) {
		salvareBraniSuFile(db);
	} else {
		db->modificato=true;
	}
	
}



// TESTI

void apriTesto(int idBrano) {
	char *posizione_testo = calloc(MAX_ENORME, sizeof(char));
	char *comando = calloc(MAX_ENORME+10, sizeof(char));
	FILE *fp;
	if(os==0) {
		sprintf(posizione_testo, "%s/%d%s", cartella_testi, idBrano, ".txt");
		fp=fopen(posizione_testo, "r");
		if (fp==NULL) {
			printf("\nIl brano scelto non possiede al momento del testo.");
		} else {
			system(posizione_testo);
		}
		fclose(fp);
	} else if (os==1) {
		sprintf(posizione_testo, "%s/%d%s", cartella_testi, idBrano, ".txt");
		fp=fopen(posizione_testo, "r");
		if (fp==NULL) {
			printf("\nIl brano scelto non possiede al momento del testo.");
		} else {
			strcpy(comando, "open ");
			strcat(comando, posizione_testo);
			system(comando);
		}
		fclose(fp);
	} else if (os==2) {
		sprintf(posizione_testo, "%s/%d%s", cartella_testi, idBrano, ".txt");
		fp=fopen(posizione_testo, "r");
		if (fp==NULL) {
			printf("\nIl brano scelto non possiede al momento del testo.");
		} else {
			strcpy(comando, "nano ");
			strcat(comando, posizione_testo);
			system(comando);
		}
		fclose(fp);
	}
	if (posizione_testo!=NULL) {
		free(posizione_testo);
		posizione_testo=NULL;
	}
	if (comando!=NULL) {
		free(comando);
		comando=NULL;
	}
}

void apriTestoDaRicerca(database *db) {
	int scelta=-1, idBrano=0;
	do {
		printf("\nCerca brano del quale si vuole aprire il testo");
		moduloRicercaBrani(db);
		if (db->ultimoEsito==-1) {
			scelta = richiesta(2);
			if (scelta=='Y'||scelta=='y') {
				printf("\nContinuo con l'apertura del testo.");
				db->ultimoEsito=0;
			} else {
				printf("\nUscito dall'apertura del testo.");
			}
		} else if (db->ultimoEsito==1) {
			do {
				
				printf("\nInserisci id del brano selezionato, altrimenti [-1] per cercare di nuovo: ");
				idBrano = inputNumero();
				if (idBrano==-1) {
					db->ultimoEsito=2;
				} else {
					if (ottenerePosDaID(db, 0,idBrano)==-1) {
						printf("\nBrano non trovato, riprovare");
						db->ultimoEsito=0;
					} else {
						apriTesto(idBrano);
						db->ultimoEsito=-1;
					}
				}
			} while (db->ultimoEsito==0);
		}
	} while (db->ultimoEsito!=-1);

}

