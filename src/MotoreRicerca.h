/*
 * FabbAmp 0.1 rev. 174 - 21.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/FabbAmp/blob/master/LICENSE
 */

#ifndef MOTORERICERCA_H_
#define MOTORERICERCA_H_
#include "Database.h"

/**
 * Sistema di ricerca dei brani in base alle informazioni memorizzate nello struct globale
 */
void ricercaBrani(int modalita);

/**
 * Funzione di elencazione delle informazioni di un singolo brano
 */
void elencaSingoloBrano(int pos);

/**
 * Funzione di elencazione di tutti i brani e le loro relative informazioni
 */
void elencaTuttiBrani();

#endif /* MOTORERICERCA_H_ */
