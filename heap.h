/*
 *  Autor: Jakub Jakubowicz
 *  Data: Kwiecien 2023
 *  Plik: head.h
 *
 * Opis: Klasa definiujaca
 * funkcje pozwalajace na dodawanie, usuwanie,
 * wyswietlanie i wczytywanie elementow kopca binarnego.
 */

#ifndef SDIZO_PROJEKT_NR_1_HEAP_H
#define SDIZO_PROJEKT_NR_1_HEAP_H
#include <iostream>

using namespace std;

class heap {
    int *tab; // Tablica przechowujaca wartosci wezlow
    int size; // Rozmiar kopca / Liczba wezlow kopca

public:

    heap(); // Konstruktor kopca binarnego

    ~heap(); // Destruktor kopca binarnego

    void loadFromFile(const string& FileName); // Wczytywanie danych z pliku

    bool IsValueInHeap(int value); // Sprawdzanie czy podana wartosc znajduje sie w kopcu binarnym

    void push(int val); // Dodawanie elementu do kopca binarnego

    void pop(); // Usuwanie korzenia kopca binarnego

    void display(); // Wyswietlanie kopca binarnego

    void generateHeap(int size); // Generowanie kopca binarnego o podanym rozmiarze

    void repairHeap(); // Naprawianie struktury, tak aby spelniala warunki kopca binarnego
};


#endif //SDIZO_PROJEKT_NR_1_HEAP_H
