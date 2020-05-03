/*
 * GestoreArtisti.h
 *
 *  Created on: 3 mag 2020
 *      Author: Simone
 */

#ifndef SRC_GESTORI_GESTOREARTISTI_H_
#define SRC_GESTORI_GESTOREARTISTI_H_

void inserimentoArtistaGuidato();
int creaArtistaGuidato(char nomearte[]);
int creaArtistaSeNonEsiste(char artista[]);
int inserisciArtista(char nome[], char cognome[], char nomearte[]);
void inserisciArtistiSuFile(char id[], char nome[], char cognome[], char nomearte[]);
void inserisciAssociazioneArtistiSuFile(char idbrano[], char idartista[]);

#endif /* SRC_GESTORI_GESTOREARTISTI_H_ */
