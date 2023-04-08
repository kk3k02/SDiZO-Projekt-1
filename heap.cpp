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

heap::heap() {
    tab = nullptr;
    size = 0;
}

heap::~heap() {
    if (size > 0) {
        delete[] tab;
    }
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
    // TODO DODAWANIE ELEMENTU DO KOPCA
}

void heap::pop() { // Usuwanie korzenia kopca binarnego
    // TODO USUWANIE KORZENIA KOPCA
}

void heap::display(){ // Wyswietlanie kopca binarnego
    // TODO WYSWIETLANIE KOPCA
}

void heap::generateHeap(int size){ // Generowanie kopca binarnego o podanym rozmiarze
    // TODO GENEROWANIE LOSOWEGO KOPCA
}

void heap::repairHeap(){ // Naprawianie struktury, tak aby spelniala warunki kopca binarnego
    // TODO NAPRAWA KOPCA
}
