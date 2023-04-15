/*
 *  Autor: Jakub Jakubowicz
 *  Data: Kwiecien 2023
 *  Plik: table.cpp
 *
 * Opis: Klasa definiujaca tablice dynamiczna
 * oraz funkcje pozwalajace na dodawanie, usuwanie,
 * wyswietlanie i wczytywanie elementow.
 */

#include "table.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "test.h"

using namespace std;

table::table() //konstruktor - wywoływany automatycznie przy tworzeniu obieku
{
    cnt = 0; // Przy deklaracji tablicy ilosc elementow bedzie wynosic 0
    tab = nullptr; // Ustalenie tablicy na wartosc null
}

table::~table() //destrukor - wywływany automatycznie przy usuwaniu obiektu
{
    delete[] tab; // Usuwanie tablicy dynamicznej
}

void table::loadFromFile(const string& FileName) // Wczytywanie danych z pliku
{
    ifstream file(FileName);

    if (file.is_open()){
        if (cnt > 0){ // Usuwanie starej tablicy dynamicznej
            delete[] tab;
            cnt = 0;
        }

        int data = 0;

        while (file >> data){
            addValue(0, data);
        }

        file.close();
    } else{
        cerr << "\nBlad otwierania pliku." << endl << endl;
    }
}

bool table::IsValueInTable(int value) // Sprawdzanie czy podana wartosc znajduje sie w tablicy
{
    if (cnt > 0){
        for (int i = 0; i < cnt; i++) {
            if (tab[i] == value) return true;
        }
    } else {
        cerr << "Tablica jest pusta." << endl << endl;
    }
    return false;
}

void table::addValue(int index, int value) // Dodawanie podanej wartosci na podany indeks tablicy
{
    if (tab && index >= 0 && index <= cnt){ // Wariant, kiedy tablica dynamiczna jest utworzona
        int *tmp;
        cnt++;
        tmp = new int[cnt];

        if (index == 0){ // Wariant, kiedy dodajemy element na poczatek tablicy dynamicznej (indeks 0)
            tmp[0] = value;

            for (int i = 1; i < cnt; ++i) {
                tmp[i] = tab[i-1];
            }
        }

        if (index == (cnt-1)){ // Wariant, kiedy dodajemy element na koniec tablicy dynamicznej
            for (int i = 0; i < cnt; i++) {
                if (i == index) tmp[i] = value;
                else tmp[i] = tab[i];
            }
        }

        if (index > 0 && index < (cnt-1)){ // Wariant, kiedy dodajemy element na pozycje inna niz poczatek i koniec
            tmp[index] = value;

            for (int i = 0; i < cnt; i++) {
                if (i < index){
                    tmp[i] = tab[i];
                }
                if (i > index){
                    tmp[i] = tab[i-1];
                }
            }
        }

        delete tab;
        tab = tmp;
    } else{
        if (index == 0){ // Wariant, kiedy chcemy dodac pierwszy element (indeks 0)
            tab = new int[1];
            tab[0] = value;
            cnt++;
        } else{ // Wariant, kiedy chcemy dodac wartosc na indeks nie istniejacej tablicy
            cerr << "Tablica jest pusta." << endl << endl;
        }
    }
}

void table::deleteFromTable(int index) // Usuwanie elementu o podanym indeksie z tablicy
{
    if (tab != nullptr){
        if (index < cnt){
            int *buf; // Tablica tymczasowa do przechowywania elementow z tablicy glownej
            buf = new int[cnt - 1]; // Stworzenie tablicy dyn. o rozmiarze cnt-1

            int counter = 0; // Licznik indeksu tablicy tymczasowej

            for (int i = 0; i < cnt; i++) {
                if (i != index){
                    buf[counter] = tab[i];
                    counter++;
                }
            }

            delete tab; // Usunwanie tablicy glownej w celu zmniejszenia jej rozmiaru
            cnt--; // Zmniejszenie ilosci elementow tablicy dyn. o jeden
            tab = new int[cnt]; // Stworzenie nowej tablicy dyn. o pomniejszonym rozmiarze

            for (int i = 0; i < cnt; i++) { // Kopiowanie wartosci z tablicy tymczasowej do glownej
                tab[i] = buf[i];
            }

            delete buf; // Usuwanie tablicy tymczasowej
        }
    } else {
        cerr << "Tablica jest pusta." << endl << endl;
    }
}

void table::display() // Wyswietlanie wszystkich elementow tablicy
{
    if(cnt > 0){
        for (int i = 0; i < cnt; i++) {
            cout << "[" << i << "] element: " << tab[i] << endl;
        }
    } else {
        cerr << "\nBrak elementow do wyswietlenia." << endl << endl;
    }
}

void table::generateTable(int size) // Generowanie tablicy o okreslonym rozmiarze z losowymi wartosciami
{
    if (size > 0){
        delete tab; // Usuwanie starej tablicy dynamicznej
        cnt = size; // Ustawianie ilosci elementow tablicy na podst. podanego rozmiaru

        tab = new int[size]; // Tworzenie tablicy dynamicznej o podanym rozmiarze

        srand(time(nullptr)); // Konfiguracja maszyny losujacej liczby calkowite

        for (int i = 0; i < size; i++) { // Wypelnianie tablicy losowymi liczbami
            tab[i] = rand();
        }
    } else {
        cerr << "Podany rozmiar jest nieprawidlowy." << endl << endl;
    }
}

void table::testing(){ // Pomiary czasu wykonywania operacji na tablicy dynamicznej
    test myTest; // Deklaracja obiektu typu test
    int testSize; // Rozmiar testowanej tablicy dynamicznej
    int repeat = 15; // Ilosc wykonywanych testow

    cout << "\n\nPodaj rozmiar tablicy: ";
    cin >> testSize;

    if (testSize > 0){
        // DODAWANIE

        srand(time(nullptr)); // Konfiguracja maszyny losujacej liczby calkowite

        for (int i = 0; i < repeat; i++) { // Dodawanie losowego elementu na poczatek tablicy
            generateTable(testSize);
            myTest.start("[Tablica Dynamiczna][Dodawanie/Poczatek][Rozmiar: " + to_string(testSize) + "]");
            addValue(0, rand());
            myTest.end();
        }
        cout << "\n[Dodawanie elementu na poczatek tablicy dynamicznej]\n";
        myTest.saveToFile("table_test.txt");

        for (int i = 0; i < repeat; i++) { // Dodawanie losowego elementu na indeks rowny polowie ilosci elementow
            generateTable(testSize);
            myTest.start("[Tablica Dynamiczna][Dodawanie/Polowa][Rozmiar: " + to_string(testSize) + "]");
            addValue(testSize/2, rand());
            myTest.end();
        }
        cout << "\n[Dodawanie elementu na dowolne miejsce w tablicy dynamicznej]\n";
        myTest.saveToFile("table_test.txt");

        for (int i = 0; i < repeat; i++) { // Dodawanie losowego elementu na koniec tablicy
            generateTable(testSize);
            myTest.start("[Tablica Dynamiczna][Dodawanie/Koniec][Rozmiar: " + to_string(testSize) + "]");
            addValue(cnt, rand());
            myTest.end();
        }
        cout << "\n[Dodawanie elementu na koniec tablicy dynamicznej]\n";
        myTest.saveToFile("table_test.txt");



        // USUWANIE

        for (int i = 0; i < repeat; i++) { // Usuwanie  elementu z poczatku tablicy
            generateTable(testSize);
            myTest.start("[Tablica Dynamiczna][Usuwanie/Poczatek][Rozmiar: " + to_string(testSize) + "]");
            deleteFromTable(0);
            myTest.end();
        }
        cout << "\n[Usuwanie elementu z poczatku tablicy dynamicznej]\n";
        myTest.saveToFile("table_test.txt");

        for (int i = 0; i < repeat; i++) { // Usuwanie  elementu z polowy tablicy
            generateTable(testSize);
            myTest.start("[Tablica Dynamiczna][Usuwanie/Polowa][Rozmiar: " + to_string(testSize) + "]");
            deleteFromTable(testSize/2);
            myTest.end();
        }
        cout << "\n[Usuwanie elementu dowolnego miejsca tablicy dynamicznej]\n";
        myTest.saveToFile("table_test.txt");

        for (int i = 0; i < repeat; i++) { // Usuwanie  elementu z konca tablicy
            generateTable(testSize);
            myTest.start("[Tablica Dynamiczna][Usuwanie/Koniec][Rozmiar: " + to_string(testSize) + "]");
            deleteFromTable(cnt-1);
            myTest.end();
        }
        cout << "\n[Usuwanie elementu z konca tablicy dynamicznej]\n";
        myTest.saveToFile("table_test.txt");
    } else{
        cerr << "\nPodano bledny rozmiar tablicy." << endl << endl;
    }
}
