/*
 * Autor: Jakub Jakubowicz
 * Data: Kwiecien 2023
 * Plik: list.cpp
 *
 * Opis: Klasa definiujaca liste dwukierunkowa
 * oraz funkcje pozwalajace na dodawanie, usuwanie,
 * wyswietlanie i wczytywanie elementow.
 */

#include "list.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include "test.h"

using namespace std;

static list *start = nullptr; // Wskaznik na poczatek listy

list::list(){ //konstruktor - wywoływany automatycznie przy tworzeniu obieku
    value = 0; // Ustawienie wartosci poczatkowej elementu listy na 0
    next = nullptr; // Ustawienie wskaznika na nastepny elelemnt na wartosc null
    previous = nullptr; // Ustawienie wskaznika na nastepny elelemnt na wartosc null
}
list::~list(){ //destrukor - wywoływany automatycznie przy usuwaniu
}

void list::loadFromFile(const string& FileName){ // Wczytywanie danych z pliku
    ifstream file(FileName);

    if (file.is_open()){
        if (start != nullptr){ // Usuwanie starej listy
            list *tmp;

            while (start){
                tmp = start -> next;
                delete start;
                start = tmp;
            }
        }

        int data = 0;

        while (file >> data){
            addElement(data, 0);
        }

        file.close();
    } else{
        cerr << "\nBlad otwierania pliku." << endl << endl;
    }
}
int list::IsValueInList(int value){ // Sprawdzanie czy podana wartosc znajduje sie w liscie
    int counter = 0; // Licznik indeksu, na ktorym znajduje sie element o podanej wartosci

    list *tmp;

    tmp = start;

    while (tmp){
        if(tmp -> value == value) return counter;
        tmp = tmp -> next;
        counter++;
    }

    return -1;
}

void list::addElement(int val, int index){ // Dodawanie elementu o podanej wartosci
    if (index <= countList()){
        if (index == 0) { // Dodawanie na poczatek listy
            list *element = new list;

            element -> value = val;
            element -> next = start;

            if (start) {
                start -> previous = element;
            }

            start = element;

            return;
        }

        list *tmp = start;

        int i = 0;

        while (tmp && i < index - 1) {
            tmp = tmp -> next;
            i++;
        }

        if (tmp) {
            list *element = new list;

            element -> value = val;
            element -> next = tmp -> next;
            element -> previous = tmp;

            if (tmp -> next) {
                tmp -> next -> previous = element;
            }

            tmp -> next = element;
        }
    } else{
        cerr << "Nieprawidlowy indeks." << endl << endl;
    }
}

void list::deleteElement(int index){ // Usuwanie elementu z listy
    if (index < countList() && start != nullptr){
        if (index == 0){ // Usuwanie z poczatku listy
            if (countList() > 1){
                list *tmp;
                tmp = start -> next;

                delete start;

                start = tmp;
                start -> previous = nullptr;
            } else{
                delete start;
                start -> previous = nullptr;
                start -> next = nullptr;
            }
        } else if (index == (countList()-1)){ // Usuwanie ostatniego elementu listy
            list *tmp;
            tmp = start;

            for (int i = 0; i < index-1; i++) {
                tmp = tmp -> next;
            }

            delete tmp -> next;
            tmp -> next = nullptr;
        } else{ // Usuwanie dowolnego elementu oprocz pierwszego i ostatniego
            list *tmp;
            tmp = start;

            for (int i = 0; i < index; ++i) {
                tmp = tmp -> next;
            }

            tmp -> previous -> next = tmp -> next;
            tmp -> next -> previous = tmp -> previous;

            delete tmp;
        }
    } else{
        cerr << "\nPodano bledny indeks." << endl << endl;
    }
}

void list::display(){ // Wyswietlanie wszystkich elementow listy
    if (start != nullptr){
        int counter = 0; // Zmienna sluzaca do liczenia wypisywanych elementow zmiennych

        list *tmp;

        tmp = start;

        while (tmp){
            cout << "[" << counter << "] Wartosc: " << tmp -> value << "; Adres: " << tmp;
            cout << "; Nastepny element: " << tmp -> next << endl << endl;
            tmp = tmp -> next;
            counter++;
        }

        cout << "Ilosc elementow w liscie: " << countList();
    } else {
        cerr << "\nLista jest pusta" << endl << endl;
    }
}

void list::generateList(int size){ // Generowanie listy o podanym rozmiarze wypelnionej losowymi wartosciami

    if (size > 0){

        if (start != nullptr){ // Usuwanie starej listy
            list *tmp;

            while (start){
                tmp = start -> next;
                delete start;
                start = tmp;
            }
        }

        // Ustawianie maszyny generujacej liczby pseudolosowe z zakresu 0-(INT_MAX-1)
        random_device seed;
        uniform_int_distribution<int> randomInt(0, INT_MAX-1);

        for (int i = 0; i < size; i++) { // Dodawanie losowych elementow do listy
            addElement(randomInt(seed), 0);
        }
    } else {
        cerr << "\nPodano bledny rozmiar." << endl << endl;
    }
}

int list::countList() { // Zwracanie liczby elementow w liscie
    list *tmp;

    tmp = start;

    int counter = 0; // Zmienna przechowujaca ilosc elementow w liscie

    while (tmp){
        counter++;
        tmp = tmp -> next;
    }

    return counter;
}

void list::testing(){ // Pomiary czasu wykonywania operacji na liscie jednokierunkowej
    test myTest; // Deklaracja obiektu typu test
    int testSize; // Rozmiar testowanej listy jednokierunkowej
    int repeat = 15; // Ilosc wykonywanych testow

    cout << "\n\nPodaj rozmiar listy: ";
    cin >> testSize;

    if (testSize > 0) {
        // DODAWANIE

        // Ustawianie maszyny generujacej liczby pseudolosowe z zakresu 0-(INT_MAX-1)
        random_device seed;
        uniform_int_distribution<int> randomInt(0, INT_MAX-1);

        for (int i = 0; i < repeat; i++) { // Dodawanie na poczatek listy
            generateList(testSize);
            myTest.start("[Lista dwukierunkowa][Dodawanie/Poczatek][Rozmiar: " + to_string(testSize) + "]");
            addElement(randomInt(seed), 0);
            myTest.end();
        }
        cout << "\n[Dodawanie elementu na poczatek listy dwukierunkowej]\n";
        myTest.saveToFile("list_test.txt");

        for (int i = 0; i < repeat; i++) { // Dodawanie do polowy listy
            generateList(testSize);
            myTest.start("[Lista dwukierunkowa][Dodawanie/Polowa][Rozmiar: " + to_string(testSize) + "]");
            addElement(randomInt(seed), testSize/2);
            myTest.end();
        }
        cout << "\n[Dodawanie elementu w dowolne miejsce listy dwukierunkowej]\n";
        myTest.saveToFile("list_test.txt");

        for (int i = 0; i < repeat; i++) { // Dodawanie na koniec listy
            generateList(testSize);
            myTest.start("[Lista dwukierunkowa][Dodawanie/Koniec][Rozmiar: " + to_string(testSize) + "]");
            addElement(randomInt(seed), countList());
            myTest.end();
        }
        cout << "\n[Dodawanie elementu na koniec listy dwukierunkowa]\n";
        myTest.saveToFile("list_test.txt");



        // USUWANIE

        for (int i = 0; i < repeat; i++) { // Usuwanie z poczatku listy
            generateList(testSize);
            myTest.start("[Lista dwukierunkowa][Usuwanie/Poczatek][Rozmiar: " + to_string(testSize) + "]");
            deleteElement(0);
            myTest.end();
        }
        cout << "\n[Usuwanie elementu z poczatku listy dwukierunkowej]\n";
        myTest.saveToFile("list_test.txt");

        for (int i = 0; i < repeat; i++) { // Usuwanie z polowy listy
            generateList(testSize);
            myTest.start("[Lista dwukierunkowa][Usuwanie/Polowa][Rozmiar: " + to_string(testSize) + "]");
            deleteElement(testSize/2);
            myTest.end();
        }
        cout << "\n[Usuwanie elementu z dowolnego miejsca listy dwukierunkowej]\n";
        myTest.saveToFile("list_test.txt");

        for (int i = 0; i < repeat; i++) { // Usuwanie z konca listy
            generateList(testSize);
            myTest.start("[Lista dwukierunkowa][Usuwanie/Koniec][Rozmiar: " + to_string(testSize) + "]");
            deleteElement(countList()-1);
            myTest.end();
        }
        cout << "\n[Usuwanie elementu z konca listy dwukierunkowej]\n";
        myTest.saveToFile("list_test.txt");

        // WYSZUKIWANIE ELEMENTU

        for (int i = 0; i < repeat; i++) { // Wyszukiwanie elementu, ktory nie znajduje sie w liscie
            generateList(testSize);
            myTest.start("[List dwukierunkowa][Wyszukiwanie][Rozmiar: " + to_string(testSize) + "]");
            IsValueInList(INT_MAX);
            myTest.end();
        }
        cout << "\n[Wyszukiwanie elementu, ktory znajduje sie w liscie dwukierunkowej (najbardziej niekorzystny przypadek)]\n";
        myTest.saveToFile("list_test.txt");
    } else{
        cerr << "\nPodano bledny rozmiar listy." << endl << endl;
    }
}