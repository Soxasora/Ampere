/*
 * GestoreBrani.h
 *
 *  Created on: 2 mag 2020
 *      Author: soxas
 */

#ifndef SRC_GESTORI_GESTOREBRANI_H_
#define SRC_GESTORI_GESTOREBRANI_H_

void inserimentoBranoGuidato();
void inserisciBrano(char titolo[], int id_artista, int id_album, int durata, int anno, int ascolti);
void inserisciBranoSuFile(char id[], char titolo[], char durata[], char id_album[], char anno[], char ascolti[]);

#endif /* SRC_GESTORI_GESTOREBRANI_H_ */
