/*
 * Autor: Jakub Jakubowicz
 * Data: Kwiecien 2023
 * Plik: list.cpp
 *
 * Opis: Klasa definiujaca liste jednoelementowa
 * oraz funkcje pozwalajace na dodawanie, usuwanie,
 * wyswietlanie i wczytywanie elementow.
 */

#include "list.h"
#include <iostream>
#include <cstdlib>
#include "test.h"

using namespace std;

static list *start = nullptr; // Wskaznik na poczatek listy

list::list(){ //konstruktor - wywoływany automatycznie przy tworzeniu obieku
    value = 0; // Ustawienie wartosci poczatkowej elementu listy na 0
    ptr = nullptr; // Ustawienie wskaznika na nastepny elelemnt na wartosc null
}
list::~list(){ //destrukor - wywoływany automatycznie przy usuwaniu
}

void list::loadFromFile(const string& FileName){ // Wczytywanie danych z pliku
    ifstream file(FileName);

    if (file.is_open()){
        if (start != nullptr){ // Usuwanie starej listy
            list *tmp;

            while (start){
                tmp = start -> ptr;
                delete start;
                start = tmp;
            }
        }

        int data = 0;

        while (file >> data){
            addElement(data, 1, -1);
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
        tmp = tmp -> ptr;
        counter++;
    }

    return -1;
}

void list::addElement(int val, int opt, int index){ // Dodawanie elementu o podanej wartosci
    // W przypadku kiedy chcemy dodac element na poczatek lub koniec, ustawiamy index na wartosc -1

    if (opt == 1){ // Dodawanie na poczatek listy
        if (start == nullptr){ // Wariant kiedy lista jest pusta a chcemy dodac wartosc na jej poczatek
            start = new list;
            start -> value = val;
        } else {
            list *tmp;

            tmp = start;

            start = new list;

            start -> value = val;
            start -> ptr = tmp;
        }
    }

    if (opt == 3 && index != -1){ // Dodawanie na podany indeks

        if (start == nullptr){ // Wariant kiedy lista jest pusta a chcemy dodac wartosc na indeks 0
            if (index == 0){
                start = new list;
                start -> value = val;
            } else{
                cerr << "\nBrak elementow w liscie." << endl << endl;
            }
        } else{
            list *tmp;
            tmp = start;

            if (index == 0) {
                addElement(val, 1, -1); // Korzystanie z wczesniej zdefiniowanej metody do dodawania na poczatek listy
            } else {
                for (int i = 0; i < index; i++) {
                    if (i == (index-1)){
                        list *element;
                        element = new list;

                        element -> ptr = tmp -> ptr;
                        element -> value = val;

                        tmp -> ptr = element;
                    } else{
                        tmp = tmp -> ptr;
                    }
                }
            }
        }
    }

    if (opt == 2){ // Dodawanie na koniec listy
        addElement(val, 3, countList()); // Korzystanie z wczesniej zadeklarowanej metody
    }

    if(opt != 1 && opt != 2 && opt != 3){ // Wybranie opcji innej niz 1/2/3
        cerr << "\nNieprawidlowy wybor." << endl << endl;
    }
}

void list::deleteElement(int opt, int index){ // Usuwanie elementu z listy
    // W przypadku kiedy chcemy usunac element z poczatku lub konca, ustawiamy index na wartosc -1

    if (start){
        list *tmp;
        tmp = start;

        if (opt == 1){ // Usuwanie z poczatku
            start = start -> ptr;
            delete tmp;
        }
        if (opt == 2){ // Usuwanie z konca listy
            deleteElement(3, countList()); // Korzystanie z wczesniej zadeklarowanej funkcji
        }
        if (opt == 3 && index != -1){ // Usuwanie z miejsca o podanym indeksie

            if (index >= 0 && index < countList()){
                if (index == 0){ // Wariant, w ktorym usuwamy pierwszy element
                    deleteElement(1, -1); // Korzystamy z wczesniej zdefiniowanej metody do usuwania z poczatku listy
                } else{
                    for (int i = 0; i < index; i++) {
                        if (i == (index-1)){
                            list *del;
                            del = tmp -> ptr;
                            tmp -> ptr = del -> ptr;
                            delete del;
                        } else{
                            tmp = tmp -> ptr;
                        }
                    }
                }
            }
        }
    } else {
        cerr << "Lista jest pusta." << endl << endl;
    }

    if(opt != 1 && opt != 2 && opt != 3){ // Wybranie opcji innej niz 1/2/3
        cerr << "\nNieprawidlowy wybor." << endl << endl;
    }
}

void list::display(){ // Wyswietlanie wszystkich elementow listy
    if (start != nullptr){
        int counter = 0; // Zmienna sluzaca do liczenia wypisywanych elementow zmiennych

        list *tmp;

        tmp = start;

        while (tmp){
            cout << "[" << counter << "] Wartosc: " << tmp -> value << "; Adres: " << tmp;
            cout << "; Nastepny element: " << tmp -> ptr << endl << endl;
            tmp = tmp -> ptr;
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
                tmp = start -> ptr;
                delete start;
                start = tmp;
            }
        }

        srand(time(nullptr)); // Ustawianie maszyny generujacej liczby pseudolosowe

        list *tmp; // Wskaznik typu list sluzacy do przechowywania tymczasowych danych

        for (int i = 0; i < size; i++) {
            tmp = new list;
            tmp->value = rand();
            tmp-> ptr = start;
            start = tmp;
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
        tmp = tmp -> ptr;
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

        srand(time(nullptr)); // Konfiguracja maszyny losujacej liczby calkowite

        for (int i = 0; i < repeat; i++) { // Dodawanie na poczatek listy
            generateList(testSize);
            myTest.start("[Lista jednokierunkowa][Dodawanie/Poczatek][Rozmiar: " + to_string(testSize) + "]");
            addElement(rand(), 1, -1);
            myTest.end();
        }
        cout << "\n[Dodawanie elementu na poczatek listy jednokierunkowej]\n";
        myTest.saveToFile("list_test.txt");

        for (int i = 0; i < repeat; i++) { // Dodawanie do polowy listy
            generateList(testSize);
            myTest.start("[Lista jednokierunkowa][Dodawanie/Polowa][Rozmiar: " + to_string(testSize) + "]");
            addElement(rand(), 3, testSize/2);
            myTest.end();
        }
        cout << "\n[Dodawanie elementu w dowolne miejsce listy jednokierunkowej]\n";
        myTest.saveToFile("list_test.txt");

        for (int i = 0; i < repeat; i++) { // Dodawanie na koniec listy
            generateList(testSize);
            myTest.start("[Lista jednokierunkowa][Dodawanie/Koniec][Rozmiar: " + to_string(testSize) + "]");
            addElement(rand(), 2, -1);
            myTest.end();
        }
        cout << "\n[Dodawanie elementu na koniec listy jednokierunkowej]\n";
        myTest.saveToFile("list_test.txt");



        // USUWANIE

        for (int i = 0; i < repeat; i++) { // Usuwanie z poczatku listy
            generateList(testSize);
            myTest.start("[Lista jednokierunkowa][Usuwanie/Poczatek][Rozmiar: " + to_string(testSize) + "]");
            deleteElement(1, -1);
            myTest.end();
        }
        cout << "\n[Usuwanie elementu z poczatku listy jednokierunkowej]\n";
        myTest.saveToFile("list_test.txt");

        for (int i = 0; i < repeat; i++) { // Usuwanie z polowy listy
            generateList(testSize);
            myTest.start("[Lista jednokierunkowa][Usuwanie/Polowa][Rozmiar: " + to_string(testSize) + "]");
            deleteElement(3, testSize/2);
            myTest.end();
        }
        cout << "\n[Usuwanie elementu z dowolnego miejsca listy jednokierunkowej]\n";
        myTest.saveToFile("list_test.txt");

        for (int i = 0; i < repeat; i++) { // Usuwanie z konca listy
            generateList(testSize);
            myTest.start("[Lista jednokierunkowa][Usuwanie/Koniec][Rozmiar: " + to_string(testSize) + "]");
            deleteElement(2, -1);
            myTest.end();
        }
        cout << "\n[Usuwanie elementu z konca listy jednokierunkowej]\n";
        myTest.saveToFile("list_test.txt");
    } else{
        cerr << "\nPodano bledny rozmiar tablicy." << endl << endl;
    }
}