/*
 * Autor: Jakub Jakubowicz
 * Data: Kwiecien 2023
 * Plik: list.h
 *
 * Opis: Klasa definiujaca liste jednoelementowa
 * oraz funkcje pozwalajace na dodawanie, usuwanie,
 * wyswietlanie i wczytywanie elementow.
 */

#ifndef SDIZO_PROJEKT_NR_1_LIST_H
#define SDIZO_PROJEKT_NR_1_LIST_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "test.h"

using namespace std;

class list {

    int value; // Zmienna typu int do przechowywania wartosci elementu listy
    list *ptr; // Wskaznik na nastepny element listy
public:

    list(); //konstruktor - wywoływany automatycznie przy tworzeniu obieku
    ~list(); //destrukor - wywływany automatycznie przy usuwaniu obiektu

    static void loadFromFile(const string& FileName); // Wczytywanie danych z pliku

    static int IsValueInList(int value); // Sprawdzanie czy podana wartosc znajduje sie w liscie

    static void addElement(int val, int opt, int index); // Dodawanie elementu o podanej wartosci

    static void deleteElement(int opt, int index); // Usuwanie elementu z listy

    static void display(); // Wyswietlanie wszystkich elementow listy

    static void generateList(int size); // Generowanie listy o podanym rozmiarze wypelnionej losowymi wartosciami

    static int countList(); // Zwracanie liczby elementow w liscie

    static void testing(); // Pomiary czasu wykonywania operacji na liscie jednokierunkowej

};

#endif //SDIZO_PROJEKT_NR_1_LIST_H
