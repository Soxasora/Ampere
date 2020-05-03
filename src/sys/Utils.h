/*
 * Utils.h
 *
 *  Created on: 2 mag 2020
 *      Author: soxas
 */

#ifndef SRC_SYS_UTILS_H_
#define SRC_SYS_UTILS_H_

void info();
void aspetta();
void creaCartella(char nome[]);
char* inputStringaSicuro(char stringa[]);
int comparaStringhe(const char *s1, const char *s2);
char *chiediFile();
void pulisciBuffer();
int controllaSeFileVuoto(char *file);
void backupFile(char *file1, char *file2);
void menu();
void menuDatabase();
void menuRicerca();

#endif /* SRC_SYS_UTILS_H_ */
