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

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string ERROR_MESSAGE = "Non valide";
/**
 @brief Function that puts every character of a sting to uppercase

 @param[in,out]     string& string String to convert to uppercase
 */
void strToUpper(string& string) {
    for (size_t i = 0; i < string.length(); ++i) {
        string[i] = toupper(string[i]);
    }
}

/**
 @brief Function that converts a roman char to its arabic number equivalent

 @param[in] char romanLetter    Letter of the roman numeration system
 @return unsigned int           Value in arabic numbers
 */

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

/**
 @brief Function checking if a given string contains only roman letters of the numeration system
        (i.e. only M, D, C, L, X, V and I)
 @param[in] const string& romanNumber   String of letters supposedly roman
 @return bool areRomanLetters           Boolean returning true if every character in the string are roman letters
 */
bool areRomanLetters(const string& romanNumber) {
    bool areRomanLetters = true;
    for (size_t i = 0; i < romanNumber.length(); ++i) {
        if (convertRomanLetterToInt(romanNumber[i])) {
            areRomanLetters = true;
        } else {
            areRomanLetters = false;
            break;
        }
    }

    if (areRomanLetters) {
        return true;
    } else {
        return false;
    }
}

bool isPower(int powerOf, long int number) {
    if (powerOf == 1)
        return (number == 1);

    long int result = 1;
    while (result < number) {
        result *= powerOf;
    }
    return (result == number);
}

unsigned int convertArabicToRoman(string number) {
    return 0;
}

unsigned int convertRomanToArabic(string number) {
    bool invalid = false;
    unsigned int result = 0;

    for (unsigned int i = 0; i < number.length(); i++) {
        char previous = number[i - 1];
        char current = number[i];
        char next = number[i + 1];
        char afterNext = number[i + 2];

        unsigned int previousNumber = i == 0 ? 0 : convertRomanLetterToInt(previous);
        unsigned int currentNumber = convertRomanLetterToInt(current);
        unsigned int nextNumber = i == number.length() - 1 ? 0 : convertRomanLetterToInt(next);
        unsigned int afterNextNumber = i == number.length() - 1 ? 0 : convertRomanLetterToInt(afterNext);
        unsigned int temp = 0;

        if (nextNumber != 0) {
            if (currentNumber > nextNumber && nextNumber >= afterNextNumber) {
                result += previousNumber == 0 ? currentNumber + nextNumber : nextNumber;
            } else if (nextNumber < afterNextNumber) {
                temp = currentNumber;

            } else if (((current == 'I' || current == 'X' || current == 'C') && currentNumber < nextNumber) &&
                       currentNumber != previousNumber && (!isPower(10, currentNumber) || !isPower(10, nextNumber) || currentNumber * 10 == nextNumber)) {
                result += nextNumber - currentNumber;
            } else {
                invalid = true;
                break;
            }
            result += temp;
        }
    }
    /*
    if (convertArabicToRoman(number) == result) {
        invalid = false;
    } else {
        cout << "Non valide";
        invalid = true;
    }
    */
    return (invalid ? 0 : result);
}

/**
 @brief Function displaying the result of a conversion

 @param[in] unsigned int result     Value in arabic numbers
 @return string                     Empty value if the arabic number is null
 */
void displayIntResult(unsigned int result) {
    if (result != 0) {
        cout << result << endl;
    } else {
        cout << ERROR_MESSAGE << endl;
    }
}

int main() {
    string rawUserInput;
    stringstream SSuserInput("");
    int arabicNumber = 0;
    string romanNumber = "";
    bool inputError = false;

    do {
        // Totally clear the variables for the next use
        SSuserInput.clear();
        SSuserInput.str("");
        arabicNumber = 0;
        romanNumber = "";
        inputError = false;

        getline(cin, rawUserInput);
        SSuserInput.str(rawUserInput);

        // Is a roman number
        if (!(SSuserInput >> arabicNumber)) {
            romanNumber = SSuserInput.str();
            strToUpper(romanNumber);

            if (romanNumber.length() > 10 || !areRomanLetters(romanNumber))
                inputError = true;
            if (romanNumber.empty())
                break;
            if (!inputError)
                displayIntResult(convertRomanToArabic(romanNumber));
        }

        // Is an arabic number
        else {
            // If there's someting we don't want after the numbers (-> input error)
            unsigned short intPartSize = log10(arabicNumber) + 1;
            if (rawUserInput.length() > intPartSize)
                inputError = true;

            if (!inputError) {
                string strArabicNumber = to_string(arabicNumber);
                convertArabicToRoman(strArabicNumber);
            }
        }

        if (inputError) {
            cout << ERROR_MESSAGE << endl;
            continue;
        }
    } while (!rawUserInput.empty());

    return 0;
}