/*
 * Ampere 0.1 rev. 420 - 26.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef RICERCA_MOTORERICERCA_H_
#define RICERCA_MOTORERICERCA_H_
#include "../gestore/Database.h"

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

#endif /* RICERCA_MOTORERICERCA_H_ */
