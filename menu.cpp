/*
 * Autor: Jakub Jakubowicz
 * Data: Kwiecien 2023
 * Plik: menu.cpp
 *
 * Opis: Klasa definiujaca menu glowne
 * sluzace do sterowania programem.
 */

#include<string>
#include<iostream>
#include "table.h"
#include "list.h"
#include "heap.h"

using namespace std;

void displayMenu(string info) // Glowne menu programu
{
    cout << endl << endl;
    cout << info << endl;
    cout << "1.Wczytaj z pliku" << endl;
    cout << "2.Usun" << endl;
    cout << "3.Dodaj" << endl;
    cout << "4.Znajdz" << endl;
    cout << "5.Utworz losowo" << endl;
    cout << "6.Wyswietl" << endl;
    cout << "7.Test (pomiary)" << endl;
    cout << "0.Powrot do menu" << endl;
    cout << "Podaj opcje:";
}



table myTab; // Deklaracja nowej tablicy dynamicznej

void menu_table() // Menu do zarzadzania tablica dynamiczna
{
    int option = 1, index, value; // Wybor, indeks, wartosc/rozmiar
    string fileName; // Nazwa pliku do wczytywania danych

    while (option){
        displayMenu("=====TABLICA=====");
        cin >> option;

        switch (option) {
            case 1: // Wczytywanie danych z pliku
                cout << "\nPodaj nazwe pliku: ";
                cin >> fileName;
                cout << endl << endl;
                myTab.loadFromFile(fileName);
                break;
            case 2: // Usuwanie elementu tablicy o podanym indeksie
                cout << "\nPodaj indeks elementu do usuniecia: ";
                cin >> index;
                cout << endl << endl;
                myTab.deleteFromTable(index);
                break;
            case 3: // Dodawanie do tablicy elementu o podanej wartosci i indeksie
                cout << "\nPodaj wartosc elementu do dodania: ";
                cin >> value;
                cout << "\nPodaj indeks do dodania: ";
                cin >> index;
                cout << endl << endl;
                myTab.addValue(index, value);
                break;
            case 4: // Sprawdzanie czy w tablicy wystepuje podana wartosc
                cout << "\nPodaj szukana wartosc: ";
                cin >> value;
                cout << endl << endl;
                if (myTab.IsValueInTable(value)) cout << "Podana wartosc znajduje sie w tablicy.";
                else cout << "Podana wartosc NIE znajduje sie w tablicy.";
                cout << endl << endl;
                break;
            case 5: // Generowanie tablicy o podanym rozmiarze wypelnionej pseudolosowymi liczbami
                cout << "\nPodaj ilosc elementow tablicy do wygenerowania: ";
                cin >> value;
                cout << endl << endl;
                myTab.generateTable(value);
                break;
            case 6: // Wyswietlanie wszystkich elementow tablicy
                cout << endl;
                myTab.display();
                cout << endl << endl;
                break;
            case 7: // Testowanie tablicy dynamicznej
                cout << "\nPOMIARY";
                // TUTAJ FUNKCJA DO TESTOWNIA TAB DYN.
                cout << endl << endl;
                break;
            case 0:
                break;
            default:
                cerr << "\nPodano nieprawidlowy numer." << endl << endl;
                break;
        }
    }
}

list myList; // Deklaracja nowej listy jednokierunkowej

void menu_list() // Menu do zarzadzania lista jednokierunkowa
{
    int option = 1, index, value; // Wybor, indeks, wartosc/rozmiar
    string fileName; // Nazwa pliku do wczytywania danych

    while (option){
        displayMenu("=====LISTA=====");
        cin >> option;

        switch (option) {
            case 1: // Wczytywanie danych z pliku
                cout << "\nPodaj nazwe pliku: ";
                cin >> fileName;
                cout << endl << endl;
                myList.loadFromFile(fileName);
                break;
            case 2: // Usuwanie elementu z listy
                cout << "\nWybierz opcje usuwania elementu listy: \n";
                cout << "\n[1] - pierwszy element";
                cout << "\n[2] - ostatni element";
                cout << "\n[3] - element o podanym indeksie";
                cout << "\nWybor: ";
                cin >> option;
                cout << endl << endl;
                list::deleteElement(option);
                break;
            case 3: // Dodawanie elementu do listy
                cout << "\n Podaj wartosc elementu: ";
                cin >> value;
                cout << "\nWybierz opcje dodawania elementu listy: \n";
                cout << "\n[1] - poczatek listy";
                cout << "\n[2] - koniec listy";
                cout << "\n[3] - element o podanym indeksie";
                cout << "\nWybor: ";
                cin >> option;
                cout << endl << endl;
                list::addElement(value,option);
                break;
            case 4: // Wyszukiwanie elementu w liscie
                cout << "\nPodaj szukana wartosc: ";
                cin >> value;
                cout << endl << endl;
                if (list::IsValueInList(value) != -1) cout << "Podana wartosc znajduje sie w liscie.";
                else cout << "Podana wartosc NIE znajduje sie w liscie.";
                cout << endl << endl;
                break;
            case 5: // Generowanie listy o podanym rozmiarze wypelnionej pseudolosowymi liczbami
                cout << "\nPodaj ilosc elementow listy do wygenerowania: ";
                cin >> value;
                cout << endl << endl;
                list::generateList(value);
                break;
            case 6: // Wyswietlanie wszystkich elementow listy
                cout << endl << endl;
                list::display();
                cout << endl << endl;
                break;
            case 7:
                cout << "\nPOMIARY";
                // TUTAJ FUNKCJA DO TESTOWNIA LISTY
                cout << endl << endl;
                break;
            case 0:
                break;
            default:
                cerr << "\nPodano nieprawidlowy numer." << endl << endl;
                break;
        }
    }
}

heap myHeap; // Deklaracja kopca binarnego

void menu_heap() // Menu do zarzadzania kopcem
{
    int option = 1, value; // Wybor, wartosc
    string fileName; // Nazwa pliku do wczytywania danych
    char opt; // Opcja

    while (option){
        displayMenu("=====KOPIEC=====");
        cin >> option;

        switch (option) {
            case 1: // Wczytywanie danych z pliku
                cout << "\nPodaj nazwe pliku: ";
                cin >> fileName;
                cout << endl << endl;
                myHeap.loadFromFile(fileName);
                break;
            case 2: // Usuwanie korzenia kopca binarnego
                cout << "\nCzy chcesz usunac korzen kopca binarnego?  \n";
                cout << "\n[t] - tak";
                cout << "\n[n] - nie";
                cout << "\nWybor: ";
                cin >> opt;
                cout << endl << endl;
                if (opt == 't') myHeap.pop();
                break;
            case 3: // Dodawanie elementu do kopca binarnego
                cout << "\n Podaj wartosc elementu: ";
                cin >> value;
                cout << endl << endl;
                myHeap.push(value);
                break;
            case 4: // Wyszukiwanie elementu w liscie
                cout << "\nPodaj szukana wartosc: ";
                cin >> value;
                cout << endl << endl;
                // TODO NAPRAWIC SPRAWDZANIE WARTOSCI W KOPCU BINARNYM
//                if (heap::IsValueInHeap != -1) cout << "Podana wartosc znajduje sie w kopcu binarnym.";
//                else cout << "Podana wartosc NIE znajduje sie w kopcu binarnym.";
                cout << endl << endl;
                break;
            case 5: // Generowanie kopca binarnego o podanym rozmiarze wypelnionego pseudolosowymi liczbami
                cout << "\nPodaj ilosc elementow kopca binarnego do wygenerowania: ";
                cin >> value;
                cout << endl << endl;
                myHeap.generateHeap(value);
                break;
            case 6: // Wyswietlanie wszystkich elementow listy
                cout << endl << endl;
                myHeap.display();
                cout << endl << endl;
                break;
            case 7:
                cout << "\nPOMIARY";
                // TODO TUTAJ FUNKCJA DO TESTOWNIA LISTY
                cout << endl << endl;
                break;
            case 0:
                break;
            default:
                cerr << "\nPodano nieprawidlowy numer." << endl << endl;
                break;
        }
    }
}

int main(int argc, char* argv[]) // Glowna funkcja main
{

    int option = 1;
    while(option) {
        cout << endl << endl;
        cout << "==== MENU GLOWNE ===" << endl;
        cout << "1.Tablica" << endl;
        cout << "2.Lista" << endl;
        cout << "3.Kopiec" << endl;
        cout << "0.Wyjscie" << endl;
        cout << "Podaj opcje:";
        cin >> option;
        cout << endl << endl;

        switch (option) {
            case 1:
                menu_table();
                break;

            case 2:
                menu_list();
                break;

            case 3:
                menu_heap();
                break;
        }

    }
    return 0;
}
