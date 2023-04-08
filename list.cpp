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

using namespace std;

static list *start = nullptr; // Wskaznik na poczatek listy

list::list(){ //konstruktor - wywoływany automatycznie przy tworzeniu obieku
    value = 0; // Ustawienie wartosci poczatkowej elementu listy na 0
    ptr = nullptr; // Ustawienie wskaznika na nastepny elelemnt na wartosc null
}
list::~list(){ //destrukor - wywływany automatycznie przy usuwaniu obiektu
    cout << "Zwolniono pamiec listy." << endl << endl;
}

void list::loadFromFile(const string& FileName){ // Wczytywanie danych z pliku
    ifstream file(FileName);

    if (file.is_open()){
        int data = 0;

        while (file >> data){
            addElement(data, 1);
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

void list::addElement(int val, int opt){ // Dodawanie elementu o podanej wartosci
    int index;

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

        cout << "Dodano element do listy." << endl << endl;
    }

    if (opt == 3){ // Dodawanie na podany indeks
        if (start != nullptr) display();

        cout << "\n Podaj indeks: ";
        cin >> index;

        if (start == nullptr){ // Wariant kiedy lista jest pusta a chcemy dodac wartosc na indeks 0
            if (index == 0){
                start = new list;
                start -> value = val;
                cout << "Dodano element do listy." << endl << endl;
            } else{
                cerr << "\nBrak elementow w liscie." << endl << endl;
            }
        } else{
            list *tmp;
            tmp = start;

            if (index == 0) {
                addElement(val, 1); // Korzystanie z wczesniej zdefiniowanej metody do dodawania na poczatek listy
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
            cout << "Dodano element do listy." << endl << endl;
        }
    }

    if (opt == 2){ // Dodawanie na koniec listy
        // Wariant kiedy lista jest pusta, wtedy dodajemy 1 element, ktory jest poczatkiem i koncem
        if (start == nullptr){
            start = new list;
            start -> value = val;
        } else{
            list *tmp, *element;
            tmp = start;
            element = new list;

            for (int i = 0; i < countList(); i++) {
                if (i == (countList()-1)){
                    tmp -> ptr = element;
                    element -> value = val;
                } else{
                    tmp = tmp -> ptr;
                }
            }
        }

        cout << "Dodano element do listy." << endl << endl;
    }

    if(opt != 1 && opt != 2 && opt != 3){ // Wybranie opcji innej niz 1/2/3
        cerr << "\nNieprawidlowy wybor." << endl << endl;
    }
}

void list::deleteElement(int opt){ // Usuwanie elementu z listy
    if (start){
        list *tmp;
        tmp = start;

        if (opt == 1){ // Usuwanie z poczatku
            start = start -> ptr;
            delete tmp;
        }
        if (opt == 2){ // Usuwanie z konca listy
            for (int i = 0; i < countList(); i++) {
                if (i == (countList()-2)){
                    delete tmp -> ptr;
                    tmp -> ptr = nullptr;
                } else{
                    tmp = tmp -> ptr;
                }
            }
        }
        if (opt == 3){ // Usuwanie z miejsca o podanym indeksie
            int index = 0; // Zmienna do okreslania indeksu elementu listy

            display();

            cout << "\n Podaj indeks: ";
            cin >> index;
            cout << endl << endl;

            if (index >= 0 && index < countList()){
                if (index == 0){ // Wariant, w ktorym usuwamy pierwszy element
                    deleteElement(1); // Korzystamy z wczesniej zdefiniowanej metody do usuwania z poczatku listy
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

        srand(time(nullptr)); // Ustawianie maszyny generujacej liczby pseudolosowe

        list *tmp; // Wskaznik typu list sluzacy do przechowywania tymczasowych danych

        for (int i = 0; i < size; i++) {
            tmp = new list;
            tmp->value = rand();
            tmp-> ptr = start;
            start = tmp;
        }

        cout << "Lista zostala utworzona." << endl << endl;
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