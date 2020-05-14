/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREARTISTI_H_
#define SRC_GESTORI_GESTOREARTISTI_H_
#include "../database/Database.h"

database inserimentoArtistaGuidato(database db);
database creaArtistaGuidato(database db, char nomearte[]);
database creaArtistaSeNonEsiste(database db, char nomearte[]);
struct artisti creaArtista(database db, char nome[], char cognome[], char nomearte[], char linkbio[]);
database inserireArtista(database db, struct artisti artista);
int controlloEsistenzaArtista(database db, char nomearte[]);
void inserisciArtistiSuFile(char id[], char nome[], char cognome[], char nomearte[], char linkbio[]);
void inserisciAssociazioneArtistiSuFile(char idbrano[], char idartista[]);
database modificaArtista(database db);
database modificaSingoloArtista(database db, int modalita, int id);
database cancellaArtista(database db);
database cancellaSingoloArtista(database db, int id);
void visualizzaBiografiaArtista(database db);

#endif /* SRC_GESTORI_GESTOREARTISTI_H_ */
