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

string convertArabicToRoman(string value) { 
    int tenthPower = value.length(); 
    stringstream SSstring(value); 
    int number = 0; 
    SSstring >> number;

    string result;
    int tenthPowerLoop = tenthPower-1;
 
    char current = 'M';
    char middle = 'D';
    char smaller = 'C';

    for(int i = 0; i <= tenthPowerLoop; ++i) {

    // Thousand
    if(tenthPower == 4 && value[i] != 0) {
        current = 'e';
        middle = 'e';
        smaller = 'M';
    }

    // Hundreds
    if(tenthPower == 3 && value[i] != 0) {
        current = 'M';
        middle = 'D';
        smaller = 'C';
    }

    // Dozens
    if(tenthPower == 2 && value[i] != 0) {
        current = 'C';
        middle = 'L';
        smaller = 'X';
    }

    // Units
    if(tenthPower == 1 && value[i] != 0) {
        current = 'X';
        middle = 'V';
        smaller = 'I';
    }

    if(value[i]-'0' >= 5 && value[i]-'0' <= 8) {
       result += middle;
    }
    if(value[i]-'0' == 4) {
        if(tenthPower == 4) {
            result = result + smaller + smaller + smaller + smaller;
        } else { 
            result = result + smaller + middle;
        }
    }
    if(value[i]-'0' == 9) {
        result = result + smaller + current;
    }

    if(value[i]-'0' > 0 && value[i]-'0' < 4 || value[i]-'0' > 5 && value[i]-'0' < 9) {
        if(value[i]-'0' > 5 && value[i]-'0' < 9) {
            value[i] -= 5;
        }
        for(int j = 0; j < (value[i]-'0'); ++j) {
            result += smaller;
            }
        }
        tenthPower--; 
    }

    //cout << "result "<< result << endl;
    return result;
}

/*
 @brief Function who convert Roman letters to indo-arabic numeral system
 @param[in] string romanNumber String of letters supposedly roman
 @return unsigned int Roman letter number converted into indo-arabic numeral system
 */
string convertRomanToArabic(string romanNumber) {
    bool invalid = false;
    unsigned int result = 0;

    for (unsigned int i = 0; i < romanNumber.length(); i++) {
        char previous = romanNumber[i - 1];
        char current = romanNumber[i];
        char next = romanNumber[i + 1];
        char afterNext = romanNumber[i + 2];
        unsigned int resultSub = 0;
        unsigned int resultAdd = 0;

        unsigned int previousNumber = i == 0 ? 0 : convertRomanLetterToInt(previous);
        unsigned int currentNumber = i == romanNumber.length() - 1 ? 0 : convertRomanLetterToInt(current);
        unsigned int nextNumber = i == romanNumber.length() - 1 ? 0 : convertRomanLetterToInt(next);
        unsigned int afterNextNumber = i == romanNumber.length() - 1 ? 0 : convertRomanLetterToInt(afterNext);
        unsigned int carry = 0;
        // if we're not at the end of the string
        if (nextNumber != 0) {
            // If the next numbers are in descending order, we'll add them
            if (currentNumber >= nextNumber) {
                // If no substraction are awaiting
                if (nextNumber >= afterNextNumber) {
                    resultAdd += (previousNumber == 0) ? currentNumber + nextNumber : nextNumber;
                    // IF a substraction follows next
                } else if (previousNumber > currentNumber || previousNumber == 0) {
                    carry += currentNumber;
                }
                // if the next numbers are in ascending order, we'll substract them
            } else if (((current == 'I' || current == 'X' || current == 'C') && currentNumber < nextNumber) &&
                       currentNumber != previousNumber && (!isPower(10, currentNumber) || !isPower(10, nextNumber) || currentNumber * 10 == nextNumber)) {
                resultSub += nextNumber - currentNumber;

            } else {
                invalid = true;
                break;
            }
            result += resultSub + resultAdd + carry;
            // if there is only one letter, we don't have to process the above
            //  An we can simply call the function for converting letter
        } else if (romanNumber.length() == 1) {
            result += convertRomanLetterToInt(current);
        }
    }
    
    if (convertArabicToRoman(to_string(result)) == romanNumber) {
        invalid = false;
    // If the result of the algorithm doesn't match the way we would 
    //write it in indo-arabic number, it's invalid
    } else {
        invalid = true;
    }
    
    return (invalid ? 0 : to_string(result));
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

            if (romanNumber.length() > 12 || !areRomanLetters(romanNumber))
                inputError = true;
            if (romanNumber.empty())
                break;
            if (!inputError)
                displayStrResult(convertRomanToArabic(romanNumber));

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