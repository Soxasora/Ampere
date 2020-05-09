/*
 * Ampere 0.1 rev. 2930 - 10.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_SYS_UTILS_H_
#define SRC_SYS_UTILS_H_

void info();
void aspetta();
void cercaSuWikipedia(char interrogazione[]);
void creaCartella(char nome[], bool silenzioso);
char* inputStringaSicuro(char stringa[]);
int comparaStringhe(const char *s1, const char *s2);
bool comparaStringheParziale(const char *s1, const char *s2);
char *chiediFile();
void pulisciBuffer();
int controllaSeFileVuoto(char *file);
void backupFile(char *file1, char *file2);

#endif /* SRC_SYS_UTILS_H_ */
