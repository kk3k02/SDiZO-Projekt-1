/*
 *  Autor: Jakub Jakubowicz
 *  Data: Kwiecien 2023
 *  Plik: table.h
 *
 * Opis: Klasa definiujaca tablice dynamiczna
 * oraz funkcje pozwalajace na dodawanie, usuwanie,
 * wyswietlanie i wczytywanie elementow.
 */

#ifndef SDIZO_PROJEKT_NR_1_TABLE_H
#define SDIZO_PROJEKT_NR_1_TABLE_H


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "test.h"

using namespace std;

class table
{
    int *tab; // Wskaznik typu int na tablice dynamiczna
    int cnt; // Ilość elementów w tablicy
public:

    table(); // Konstruktor - wywoływany automatycznie przy tworzeniu obieku
    ~table(); // Destrukor - wywoływany automatycznie przy usuwaniu obiektu

    void loadFromFile(const string& FileName); // Wczytywanie danych z pliku

    bool IsValueInTable(int value); // Sprawdzanie czy podana wartosc znajduje sie w tablicy

    void addValue(int index, int value); // Dodawanie podanej wartosci na podany indeks tablicy

    void deleteFromTable(int index); // Usuwanie elementu o podanym indeksie z tablicy

    void display(); // Wyswietlanie wszystkich elementow tablicy

    void generateTable(int size); // Generowanie tablicy o okreslonym rozmiarze z losowymi wartosciami

    void testing(); // Pomiary czasu wykonywania operacji na tablicy dynamicznej

};

#endif //SDIZO_PROJEKT_NR_1_TABLE_H
