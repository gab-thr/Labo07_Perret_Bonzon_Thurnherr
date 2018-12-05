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
const string ERRROR_MESSAGE = "Non valide";
unsigned int convertRomanLetterToInt(char romanLetter) {
    switch (romanLetter) {
        case 'M':
            return 1000;
        case 'D':
            return 500;
        case 'C':
            return 100;
        case 'L':
            return 50;
        case 'X':
            return 10;
        case 'V':
            return 5;
        case 'I':
            return 1;
        default:
            return 0;
            break;
    }
}
string convertArabicToRoman(string number) {
}
unsigned int convertRomanToArabic(string number) {
    bool invalid = false;
    unsigned int result;

    for (unsigned int i = 0; i < number.length(); i++) {
        char previous = number[i - 1];
        char current = number[i];
        char next = number[i + 1];
        unsigned int previousNumber = i == 0 ? 0 : convertRomanLetterToInt(previous);
        unsigned int currentNumber = convertRomanLetterToInt(current);
        unsigned int nextNumber = i == number.length() - 1 ? 0 : convertRomanLetterToInt(next);
        result += (!previousNumber) ? currentNumber : 0;

        if (nextNumber != 0) {
            if (currentNumber > nextNumber) {
                result += nextNumber;

            } else if (((current == 'X' || current == 'C' || current == 'X') && currentNumber < nextNumber) &&
                       currentNumber != previousNumber && currentNumber * 10 < nextNumber) {
                result += nextNumber - currentNumber;
            } else {
                cout << "Non valide";
                invalid = true;
                break;
            }
        }
    }
    return (invalid ? 0 : result);
}
string displayResult(unsigned int result) {
    if (result != 0) {
        cout << result;
    } else {
        return "";
    }
}
int main() {
    // Invalide
    displayResult(convertRomanToArabic("LDXVI"));
    // Valide
    displayResult(convertRomanToArabic("DLXVI"));

    return 0;
}