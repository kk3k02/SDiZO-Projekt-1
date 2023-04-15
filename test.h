/*
 *  Autor: Jakub Jakubowicz
 *  Data: Kwiecien 2023
 *  Plik: test.h
 *
 * Opis: Klasa definiujaca funkcje pozwalajace
 * na mierzenie czasu wykonywania roznych operacji
 * na zadeklarowanych strukturach
 */

#ifndef SDIZO_PROJEKT_NR_1_TEST_H
#define SDIZO_PROJEKT_NR_1_TEST_H

#include <windows.h>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace  std;

class test {
    float *results; // Tablica sluzaca do przechowywania wynikow pomiaru

public:

    test(); // Konstruktor - wywoływany automatycznie przy tworzeniu obieku

    ~test(); // Destrukor - wywoływany automatycznie przy usuwaniu obiektu

    long long int read_QPC(); // Pomiar czasu

    void start(); // Rozpoczecie pomiaru czasu

    void end(); // Zakonczenie pomiaru czasu

    void saveToFile(const string& FileName);  // Zapisywanie wynikow do pliku
};


#endif //SDIZO_PROJEKT_NR_1_TEST_H
