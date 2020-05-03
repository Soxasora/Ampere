/*
 * GestoreAlbum.h
 *
 *  Created on: 3 mag 2020
 *      Author: soxas
 */

#ifndef SRC_GESTORI_GESTOREALBUM_H_
#define SRC_GESTORI_GESTOREALBUM_H_

void inserimentoAlbumGuidato();
int creaAlbumGuidato(char titolo_album[]);
int creaAlbumSeNonEsiste(char titolo_album[]);
int inserisciAlbum(char titolo[], int anno);
void inserisciAlbumSuFile(char id[], char titolo[], char anno[]);
void inserisciCollezioneSuFile(char idalbum[], char idbrano[]);

#endif /* SRC_GESTORI_GESTOREALBUM_H_ */
