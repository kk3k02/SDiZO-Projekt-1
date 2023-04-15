/*
 *  Autor: Jakub Jakubowicz
 *  Data: Kwiecien 2023
 *  Plik: test.cpp
 *
 * Opis: Klasa zawierajaca funkcje pozwalajace
 * na mierzenie czasu wykonywania roznych operacji
 * na zadeklarowanych strukturach
 */

#include "test.h"
#include <windows.h>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace  std;

test::test(){ // Konstruktor - wywoływany automatycznie przy tworzeniu obieku
    results = nullptr; // Ustawienie wartosci z wynikami pomiarow na null
    cnt = 0;
    startTime = 0; // Ustawienie czasu startu na wartosc 0
}
test::~test(){ // Destrukor - wywoływany automatycznie przy usuwaniu obiektu
    delete[] results; // Usuwanie tablicy z wynikami
    cout << "\n\nZakonczenie testowania." << endl << endl;
}

long long int test::read_QPC(){ // Pomiar czasu
    LARGE_INTEGER count;

    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
}

void test::start(const string& message){ // Rozpoczecie pomiaru czasu
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    startTime = read_QPC();
    testName = message;
}

void test::end(){ // Zakonczenie pomiaru czasu
    long long int elapsed; // Zmienna do przechowywania wyniku pomiaru
    elapsed = read_QPC() - startTime;
    float result = (float)elapsed / frequency;


    // Dodawanie wyniku do tablicy wynikow
    if (results == nullptr){ // Wariant, kiedy pomiar jest pierwszy
        results = new float[1]; // Utworzenie jednoelementowej tablicy wynikow
        cnt++; // Zwiekszenie ilosci elementow w tablicy wynikow o 1
        results[0] = result; // Dodanie wyniku do tablicy
    } else{ // Wariant, kiedy pomiar nie jest pierwszym
        float *tmp; // Tymczasowa tablica dynamiczna do przechowywania wynikow
        tmp = new float[cnt+1];

        tmp[cnt] = result; // Dodanie wyniku do tablicy tymczasowej

        for (int i = 0; i < cnt; i++) { // Kopiowanie glownej tablicy do tymczasowej
            tmp[i] = results[i];
        }

        delete[] results; // Usuwanie starej tablicy w celu stworznia nowej zwiekszonej o 1
        cnt++; // Inkrementacja ilosci elementow w tablicy
        results = tmp;
    }

    avg = avg + result; // Dodanie wartosci do sredniej
}

void test::saveToFile(const string& FileName){ // Zapisywanie wynikow do pliku
    ofstream file;

    file.open(FileName, ios::in | ios::app);

    file << testName << "\n";

    for (int i = 0; i < cnt; i++) {
        file << results[i] << "\n";
    }

    file << "AVG: " << avg / cnt << endl;

    file.close();

    results = nullptr; // Czyszczenie tablicy wnikow
    cnt = 0; // Ustawianie ilosci elementow na 0
    avg = 0; // Ustawianie wartosci sredniej na 0
}

void test::display(){ // Wyswietlanie zawartosci tablicy z wynikami

    if (results != nullptr){
        for (int i = 0; i < cnt; i++) {
            cout << "[" << i + 1 << "] pomiar: " << results[i] << endl;
        }

        cout << "Wartosc srednia pomiarow: " << avg / cnt << endl;
    } else{
        cerr << "Brak danych do wyswietlenia." << endl << endl;
    }
}

