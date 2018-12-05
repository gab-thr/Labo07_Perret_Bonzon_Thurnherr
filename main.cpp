/*
    -----------------------------------------------------------------------------------
    Laboratoire : Labo07
    Fichier     : main.cpp
    Auteur(s)   : Ludovic Bonzon, Benoit Perret, Gabrielle Thurnherr
    Date        : 28.11.2018

    But         : Vous devez écrire un programme convertissant les nombres écrits avec
    le système de numérotation indo-arabe en nombres romains et vice-versa. Il lit les
    entrées ligne par ligne et détecte dans quel sens doit s'effectuer la conversion.
    Si l'entrée est non valide, il écrit "Non valide". Il s'arrête quand il reçoit une
    ligne vide. Il doit être capable de traiter au moins des nombres entre I et MMMMCMXCIX,
    donc entre 1 et 4999.
    Bien que l'usage romain varie, nous ne considérons ici comme valide que les nombres
    romains écrits sans symbole se répétant plus de 3 fois, à l'exception du M. Ainsi 4
    s'écrit IV et pas IIII, 99 s'écrit XCIX et pas LXXXXVIIII. Les nombres romains ne
    respectant pas cette règle doivent être considérés non valides.

    Remarque(s) :

    Compilateur : MinGW-g++ <6.3.0>
    -----------------------------------------------------------------------------------
    */

#include <iostream>
#include <string>

using namespace std;

unsigned int convertRomanLetterToInt(char romanLetter) {
    switch (romanLetter) {
        case 'M':
            return 1000;
            break;
        case 'D':
            return 500;
            break;
        case 'L':
            return 50;
            break;
        case 'C':
            return 100;
            break;
        case 'X':
            return 10;
            break;
        case 'V':
            return 5;
            break;
        case 'I':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}
string convertArabicToRoman(string number) {
}
string convertRomanToArabic(string number) {
    for (int i : number) {
        char current = number[i];
        unsigned int currentNumber = convertRomanLetterToInt(current);
    }
}
int main() {
    return 0;
}