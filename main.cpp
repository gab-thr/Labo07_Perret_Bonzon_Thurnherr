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
    Remarque(s) : - Le programme gère l'insertion de chiffres romains en minuscule
                    et en majuscule
                  -
    Compilateur : MinGW-g++ <6.3.0>
    -----------------------------------------------------------------------------------
*/

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string ERROR_MESSAGE = "Non valide";
const char ZERO = '0';
const int INT_TEN = 10;
const char THOUSAND = 'M';
const char FIVE_HUNDRED = 'D';
const char HUNDRED = 'C';
const char FIFTY = 'L';
const char TEN = 'X';
const char FIVE = 'V';
const char ONE = 'I';
const char OUT_OF_RANGE = 'e';

/**
 @brief Function that puts every character of a string to uppercase
 @param[in,out] string& string  String to convert to uppercase
 */
void strToUpper(string& string) {
    for (size_t i = 0; i < string.length(); ++i) {
        string[i] = (char)toupper(string[i]);
    }
}

/**
 @brief Function that converts a roman char to its arabic number equivalent
 @param[in] char romanLetter    Letter of the roman numeration system
 @return unsigned int           Value in arabic numbers
 */
unsigned int convertRomanLetterToInt(char romanLetter) {
    switch (romanLetter) {
        case THOUSAND:
            return 1000;
        case FIVE_HUNDRED:
            return 500;
        case HUNDRED:
            return 100;
        case FIFTY:
            return 50;
        case TEN:
            return 10;
        case FIVE:
            return 5;
        case ONE:
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

/*
 @brief This function checks if the input number is a power of ten

 @param[in] long int number     Number to check
 @return bool                   Return true if the number is a power of ten
 */
bool isPowerOfTen(long int number) {
    long int result = 1;
    while (result < number) {
        result *= INT_TEN;
    }
    return (result == number);
}

/*
 @brief Function that converts indo-arabic numerals to Roman letters
 @param[in] string value    String of numbers to convert
 @return string result      Indo-arabic numeral converted to Roman letters
 */
string convertArabicToRoman(string value) {
    string result;

    int digitsNumber = value.length();  // number of digits of the number
    int tenthPower = digitsNumber - 1;  // max tenth power of the number

    // setting variables for the current digit number to create the roman numeral
    char current = THOUSAND;
    char middle = FIVE_HUNDRED;
    char smaller = HUNDRED;

    // going through every digit to assign the correct roman letters and construct the roman numeral
    for (int i = 0; i <= tenthPower; ++i) {
        switch (digitsNumber) {
            case 4:
                current = OUT_OF_RANGE;
                middle = OUT_OF_RANGE;
                smaller = THOUSAND;
                break;
            case 3:
                current = THOUSAND;
                middle = FIVE_HUNDRED;
                smaller = HUNDRED;
                break;
            case 2:
                current = HUNDRED;
                middle = FIFTY;
                smaller = TEN;
                break;
            case 1:
                current = TEN;
                middle = FIVE;
                smaller = ONE;
                break;
            case 0:
            default:
                break;
        }

        if (value.at(i) - ZERO >= 5 && value.at(i) - ZERO <= 8) {
            result += middle;
        }
        if (value.at(i) - ZERO == 4) {
            if (digitsNumber == 4) {
                result = result + smaller + smaller + smaller + smaller;
            } else {
                result = result + smaller + middle;
            }
        }
        if (value.at(i) - ZERO == 9) {
            result = result + smaller + current;
        }
        if (((value.at(i) - ZERO > 0) && (value.at(i) - ZERO < 4)) || ((value.at(i) - ZERO > 5) && (value.at(i) - ZERO < 9))) {
            if ((value.at(i) - ZERO > 5) && (value.at(i) - ZERO < 9))
                value.at(i) = (char)(value.at(i) - 5);

            for (int j = 0; j < (value.at(i) - ZERO); ++j) {
                result += smaller;
            }
        }
        digitsNumber--;
    }
    return result;
}

/*
 @brief Function that converts Roman letters to indo-arabic numeral system
 @param[in] string romanNumber  String of letters supposedly roman
 @return unsigned int           Roman letter number converted into indo-arabic numeral system
 */
string convertRomanToArabic(string romanNumber) {
    bool invalid = false;
    unsigned int result = 0;
    char previous = char(0), current = char(0), next = char(0), afterNext = char(0);
    unsigned int previousNumber = 0, currentNumber = 0, nextNumber = 0, afterNextNumber = 0;

    for (unsigned int i = 0; i < romanNumber.length(); i++) {
        // if we're not apart from the string
        if (((i + 1) < romanNumber.length() || (i + 2) < romanNumber.length()) || i < romanNumber.length()) {
            current = romanNumber[i];
            next = romanNumber[i + 1];
            afterNext = romanNumber[i + 2];
        }        // else we week the variables in a neutral state (0)

        if (i != 0) {
            previous = romanNumber[i - 1];
        }
        // if previous variables are not equal to 0
        if (previous || current || next || afterNext) {
            previousNumber = convertRomanLetterToInt(previous);
            currentNumber = convertRomanLetterToInt(current);
            nextNumber = convertRomanLetterToInt(next);
            afterNextNumber = convertRomanLetterToInt(afterNext);
        }
        unsigned int carry = 0;
        unsigned int resultSub = 0;
        unsigned int resultAdd = 0;
        // if we're not at the end of the string
        if (nextNumber != 0) {
            // if the next numbers are in descending order, we'll add them
            if (currentNumber >= nextNumber) {
                // if no substraction are awaiting
                if (nextNumber >= afterNextNumber) {
                    resultAdd += (previousNumber == 0) ? currentNumber + nextNumber : nextNumber;
                    // if a substraction follows next
                } else if (previousNumber > currentNumber || previousNumber == 0) {
                    carry += currentNumber;
                }
                // if the next numbers are in ascending order, we'll substract them
            } else if (((current == ONE || current == TEN || current == HUNDRED) && currentNumber < nextNumber) &&
                       currentNumber != previousNumber && (!isPowerOfTen(currentNumber) || !isPowerOfTen(nextNumber) || currentNumber * 10 == nextNumber)) {
                resultSub += nextNumber - currentNumber;

            } else {
                invalid = true;
                break;
            }
            result += resultSub + resultAdd + carry;
            // if there is only one letter, we don't have to process the above
            // and we can simply call the function for converting letter

        } else if (romanNumber.length() == 1) {
            result += convertRomanLetterToInt(current);
        }
    }

    if (convertArabicToRoman(to_string(result)) == romanNumber) {
        invalid = false;
        // If the result of the algorithm doesn't match the way we would
        // write it in indo-arabic, it's invalid
    } else {
        invalid = true;
    }

    return (invalid ? "" : to_string(result));
}

/**
 @brief Function displaying the result of a conversion
 @param[in] string result   Value to display (either Roman or arabic numeral)
 */
void displayStrResult(string result) {
    if (result.empty()) {
        cout << ERROR_MESSAGE << endl;
    } else {
        cout << result << endl;
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

            if (!areRomanLetters(romanNumber))
                inputError = true;
            if (romanNumber.empty())
                break;
            if (!inputError)
                displayStrResult(convertRomanToArabic(romanNumber));
        }

        // Is an arabic number
        else {
            // If there's someting we don't want after the numbers (-> input error)
            unsigned short intPartSize = (unsigned short)(log10(arabicNumber) + 1);
            if (rawUserInput.length() > intPartSize)
                inputError = true;

            if (!inputError) {
                string strArabicNumber = to_string(arabicNumber);
                displayStrResult(convertArabicToRoman(strArabicNumber));
            }
        }

        if (inputError) {
            cout << ERROR_MESSAGE << endl;
            continue;
        }
    } while (!rawUserInput.empty());

    return 0;
}
