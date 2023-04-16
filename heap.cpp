/*
 *  Autor: Jakub Jakubowicz
 *  Data: Kwiecien 2023
 *  Plik: heap.cpp
 *
 * Opis: Klasa definiujaca kopiec binarny
 * oraz funkcje pozwalajace na dodawanie, usuwanie,
 * wyswietlanie i wczytywanie elementow.
 */

#include "heap.h"
#include "test.h"
#include <iostream>

using namespace std;

heap::heap() { // Konstruktor kopca binarnego
    tab = nullptr; // Ustawianie poczatkowej wartosci tablicy na NULL
    size = 0; // Ustawianie rozmiaru kopca na 0
}

heap::~heap() { // Destruktor kopca binarnego
    delete[] tab;
}

void heap::loadFromFile(const string& FileName){ // Wczytywanie danych z pliku
    ifstream file(FileName);

    if (file.is_open()){
        if (size > 0){ // Usuwanie starej tablicy z kopcem
            delete[] tab;
            size = 0;
        }

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
    for (int i = 0; i < size; i++) {
        if (tab[i] == value) return true;
    }
    return false;
}

void heap::push(int val){ // Dodawanie elementu do kopca binarnego
    if (size == 0){ // Wariant, w ktorym kopiec jest pusty i dodajemy element na poczatek
        size++;
        tab = new int[size];
        tab[0] = val;
    } else{ // Wariant, w ktorym kopiec nie jest pusty i dodajemy element jako ostatniego liscia
       int *tmp; // Tymczasowa tablica do przechowywania wartosci kopca powiekszona o 1
       tmp = new int[size+1];

        for (int i = 0; i < size; i++) {
            tmp[i] = tab[i];
        }

        tmp[size] = val; // Dodanie elementu o podanej wartosci na sam koniec kopca

        size++; // Inkrementacja liczby elementow w kopcu

        delete[] tab; // Usuwanie starej tablicy w celu stworzenia nowej powiekszonej

        tab = tmp;
    }

    repairHeap(1); // Naprawa kopca
}

void heap::pop() { // Usuwanie korzenia kopca binarnego
    if (size > 0){
        int *tmp; // Tymczasowa tablica do przechowywania wartosci kopca
        int root; // Zmienna do przechowywania wartosci korzenia

        root = tab[size - 1]; // Przypisanie zmiennej wartosci ostatniego liscia w kopcu

        size--; // Dekrementacja ilosci elementow w kopcu

        tmp = new int[size];

        tmp[0] = root; // Przypisanie wartosci korzenia do tablicy tymczasowej

        for (int i = 1; i < size; ++i) {
            tmp[i] = tab[i];
        }

        delete[] tab; // Usuwanie starej tablicy w celu stworzenia nowej o zwiekszonym rozmiarze
        tab = tmp;

        repairHeap(2); // Naprawa kopca po usuwaniu korzenia

    } else{
        cerr << "\nBrak elementow w kopcu binarnym." << endl << endl;
    }
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

void heap::generateHeap(int sizeToGenerate){ // Generowanie kopca binarnego o podanym rozmiarze
    if (sizeToGenerate > 0){
        if (size > 0){ // Usuwanie starego kopca
            delete[] tab; // Usuwanie starej tablicy dynamicznej
            size = 0; // Ustawianie liczby elementow kopca na 0
        }

        srand(time(nullptr)); // Konfiguracja maszyny losujacej liczby calkowite

        for (int i = 0; i < sizeToGenerate; i++) { // Wypelnianie tablicy losowymi liczbami
            push(rand());
        }
    } else {
        cerr << "Podany rozmiar jest nieprawidlowy." << endl << endl;
    }
}

void heap::repairHeap(int option){ // Naprawianie struktury, tak aby spelniala warunki kopca binarnego
    // Opcja [1] to naprawianie po dodawaniu elementu jako ostatni lisc
    // Opcja [2] to naprawianie po usuwaniu korzenia

    if (size > 0){
        if (option == 1){ // Naprawianie po dodawaniu na koniec kopca
            int parent = 1; // Zmienna przechowujaca indeks rodzica
            int counter = size - 1; // Licznik do petli while
            int tmp; // Zmienna do przechowywania przenoszonych wartosci z kopca

            if (size > 1){
                while (parent){
                    if (counter % 2 == 0){
                        parent = (counter / 2) - 1;
                    } else{
                        parent = counter / 2;
                    }

                    if (tab[counter] > tab[parent]){
                        tmp = tab[parent];
                        tab[parent] = tab[counter];
                        tab[counter] = tmp;

                        counter = parent;
                    } else{
                        break; // Wychodzenie z petli jesli warunek kopca jest spelniony po dodaniu elementu
                    }
                }
            }
        } else if (option == 2){ // Naprawianie kopca po usuwaniu korzenia
            int child1, child2; // Zmienne do przechowywania indeksow potomkow
            int parent = 0; // Zmienna do przechowywania indeksu rodzica
            int tmp; // Zmienna do przechowywania tymczasowej wartosci z kopca

            while (1){ // Sprawdzanie warunkow kopca binarnego i naprawianie go
                child1 = (2 * parent) + 1; // Ustawianie indeksu na nieparzystego potomka
                child2 = child1 + 1; // Ustawianie indeksu na parzystego potomka

                if (child1 < size && child2 < size){
                    if ((tab[parent] < tab[child1]) || (tab[parent] < tab[child2])){

                        tmp = tab[parent];

                        if (tab[child1] > tab[child2]){ // Zamiana wartosci rodzica z 1 potomkiem
                            tab[parent] = tab[child1];
                            tab[child1] = tmp;

                            parent = child1;
                        } else{ // Zamiana wartosci rodzica z 2 potomkiem
                            tab[parent] = tab[child2];
                            tab[child2] = tmp;

                            parent = child2;
                        }
                    } else{
                        break; // Przerwanie petli, gdy warunek kopca binarnego jest spelniony
                    }
                } else{
                    break; // Przerwanie petli, gdy wartosci wychodza poza rozmiar tablicy kopca
                }
            }
        }
    } else{
        cerr << "\nKopiec jest pusty." << endl << endl;
    }
}

void heap::testing(){ // Testowanie zloznosci obliczeniowej kopca binarnego
    test myTest; // Deklaracja obiektu typu test
    int testSize; // Rozmiar testowanej listy jednokierunkowej
    int repeat = 15; // Ilosc wykonywanych testow

    cout << "\n\nPodaj rozmiar kopca: ";
    cin >> testSize;

    if (testSize > 0){
        // DODAWANIE

        srand(time(nullptr)); // Konfiguracja maszyny losujacej liczby calkowite

        for (int i = 0; i < repeat; i++) { // Dodawanie elementu do kopca binarnego
            generateHeap(testSize);
            myTest.start("[Kopiec Binarny][Dodawanie][Rozmiar: " + to_string(testSize) + "]");
            push(rand());
            myTest.end();
        }
        cout << "\n[Dodawanie elementu na do kopca binarnego]\n";
        myTest.saveToFile("heap_test.txt");

        // USUWANIE

        for (int i = 0; i < repeat; i++) { // Usuwanie korzenia kopca binarnego
            generateHeap(testSize);
            myTest.start("[Kopiec Binarny][Usuwanie Korzenia][Rozmiar: " + to_string(testSize) + "]");
            pop();
            myTest.end();
        }
        cout << "\n[Usuwanie korzenia kopca binarnego]\n";
        myTest.saveToFile("heap_test.txt");

        // WYSZUKIWANIE ELEMENTU

        for (int i = 0; i < repeat; i++) { // Wyszukiwanie elementu, ktory NIE znajduje sie w kopcu binarnym
            generateHeap(testSize);
            myTest.start("[Kopiec Binarny][Wyszukiwanie/Brak Elementu][Rozmiar: " + to_string(testSize) + "]");
            IsValueInHeap(rand() * rand());
            myTest.end();
        }
        cout << "\n[Wyszukiwanie elementu, ktory NIE znajduje sie w kopcu binarnym]\n";
        myTest.saveToFile("heap_test.txt");

        for (int i = 0; i < repeat; i++) { // Wyszukiwanie elementu, ktory  znajduje sie w kopcu binarnym
            generateHeap(testSize);
            pop();
            push(1);
            myTest.start("[Kopiec Binarny][Wyszukiwanie/Sukces][Rozmiar: " + to_string(testSize) + "]");
            IsValueInHeap(1);
            myTest.end();
        }
        cout << "\n[Wyszukiwanie elementu, ktory znajduje sie w kopcu binarnym]\n";
        myTest.saveToFile("heap_test.txt");
    } else{
        cerr << "\nPodano bledny rozmiar tablicy." << endl << endl;
    }
}
