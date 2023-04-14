/*
 *  Autor: Jakub Jakubowicz
 *  Data: Kwiecien 2023
 *  Plik: head.cpp
 *
 * Opis: Klasa definiujaca kopiec binarny
 * oraz funkcje pozwalajace na dodawanie, usuwanie,
 * wyswietlanie i wczytywanie elementow.
 */

#include "heap.h"
#include <iostream>
#include <fstream>

using namespace std;

heap::heap() { // Konstruktor kopca binarnego
    tab = nullptr; // Ustawianie poczatkowej wartosci tablicy na NULL
    size = 0; // Ustawianie rozmiaru kopca na 0
}

heap::~heap() { // Destruktor kopca binarnego
    delete[] tab;
    cout << "Pamiec kopca zostala zwolniona." << endl << endl;
}

void heap::loadFromFile(const string& FileName){ // Wczytywanie danych z pliku
    ifstream file(FileName);

    if (file.is_open()){
        int data = 0;

        while (file >> data){
            push(data);
        }

        file.close();
    } else{
        cerr << "\nBlad otwierania pliku." << endl << endl;
    }
}

bool heap::IsValueInHeap(int value){ // Sprawdzanie czy podana wartosc znajduje sie w kopcu binarnym
    // TODO SPRAWDZANIE CZY ELEMENT ZNAJDUJE SIE W KOPCU
    return false;
}

void heap::push(int val){ // Dodawanie elementu do kopca binarnego
    size++; // Zwiekszenie ilosci elementow w tablicy

    int *tmp; // Deklaracja tymczasowej tablicy dynamicznej
    tmp = new int[size];

    for (int i = 0; i < size; i++) { // Kopiowanie zawartosci glownej tablicy do tymczasowej
        if (i == (size-1)){
            tmp[i] = val;
        } else{
            tmp[i] = tab[i];
        }
    }

    delete[] tab; // Usuwanie starej tablicy w celu stworzenia nowej o zwiekszonym rozmiarze

    tab = tmp;

    repairHeap(); // Naprawa kopca
    cout << "Element zostal dodany do kopca." << endl << endl;
}

void heap::pop() { // Usuwanie korzenia kopca binarnego
    // TODO USUWANIE KORZENIA KOPCA
}

void heap::display(){ // Wyswietlanie kopca binarnego
    if (size > 0){
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "]: " << tab[i] << endl;
        }
    } else{
        cerr << "\nBrak elementow w kopcu." << endl << endl;
    }
}

void heap::generateHeap(int size){ // Generowanie kopca binarnego o podanym rozmiarze
    // TODO GENEROWANIE LOSOWEGO KOPCA
}

void heap::repairHeap(){ // Naprawianie struktury, tak aby spelniala warunki kopca binarnego
    // TODO NAPRAWA KOPCA
}
