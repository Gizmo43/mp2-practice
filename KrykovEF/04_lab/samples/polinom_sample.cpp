#include <iostream>
#include <string>
#include "Polinom.h"

using namespace std;

void printMenu() {
    cout << "\nSelect an option" << endl;
    cout << "1. Enter a polynom" << endl;
    cout << "2. Output the current polynom" << endl;
    cout << "3. Calculate the value of the polynom" << endl;
    cout << "4. Add another polynom" << endl;
    cout << "5. Subtract another polynom" << endl;
    cout << "6. Multiply by another polynom" << endl;
    cout << "7. Add monom" << endl;
    cout << "8. Subtract a monom" << endl;
    cout << "9. Multiply by monom" << endl;
    cout << "10. Multiply by a number" << endl;
    cout << "11. Reset the current polynom" << endl;
    cout << "0. Exit" << endl;
    cout << "Select: ";
}

Polinom inputPolinom() {
    string str;
    cout << "Enter polinom  (format: 2x1y2z3+x3z4-7.5): ";
    cin.ignore(); 
    getline(cin, str);
    return Polinom(str);
}

Monom inputMonom() {
    string str;
    cout << "Enter monom (Format: 3x1y2): ";
    cin.ignore();
    getline(cin, str);
    return Monom(str);
}

void evaluatePolinom(const Polinom& p) {
    double x, y, z;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;
    cout << "Enter z: ";
    cin >> z;

    double result = p(x, y, z);
    cout << "Result: " << result << endl;
}

int main() {
    Polinom currentPoly;
    bool hasPoly = false;
    int choice;
    do {
        printMenu();
        cin >> choice;

        try {
            switch (choice) {
            case 1: {
                currentPoly = inputPolinom();
                hasPoly = true;
                cout << "Polynom set: " << currentPoly << endl;
                break;
            }
            case 2: {
                if (!hasPoly) {
                    cout << "No Source Polinom" << endl;
                    break;
                }
                cout << "The current polynom: " << currentPoly << endl;
                break;
            }
            case 3: {
                if (!hasPoly) {
                    cout << "No Source Polinom" << endl;
                    break;
                }
                evaluatePolinom(currentPoly);
                break;
            }
            case 4: {
                if (!hasPoly) {
                    cout << "No Source Polinom" << endl;
                    break;
                }
                Polinom p2 = inputPolinom();
                currentPoly = currentPoly + p2;
                cout << "Add result: " << currentPoly << endl;
                break;
            }
            case 5: {
                if (!hasPoly) {
                    cout << "No Source Polinom" << endl;
                    break;
                }
                Polinom p2 = inputPolinom();
                currentPoly = currentPoly - p2;
                cout << "Subtract result: " << currentPoly << endl;
                break;
            }
            case 6: {
                if (!hasPoly) {
                    cout << "No Source Polinom" << endl;
                    break;
                }
                Polinom p2 = inputPolinom();
                currentPoly = currentPoly * p2;
                cout << "Multiply result: " << currentPoly << endl;
                break;
            }
            case 7: {
                if (!hasPoly) {
                    cout << "No Source Polinom" << endl;
                    break;
                }
                Monom m = inputMonom();
                currentPoly = currentPoly + m;
                cout << "Add result: " << currentPoly << endl;
                break;
            }
            case 8: {
                if (!hasPoly) {
                    cout << "No Source Polinom" << endl;
                    break;
                }
                Monom m = inputMonom();
                currentPoly = currentPoly - m;
                cout << "Subtract result: " << currentPoly << endl;
                break;
            }
            case 9: {
                if (!hasPoly) {
                    cout << "No Source Polinom" << endl;
                    break;
                }
                Monom m = inputMonom();
                currentPoly = currentPoly * m;
                cout << "Multiply result: " << currentPoly << endl;
                break;
            }
            case 10: {
                if (!hasPoly) {
                    cout << "No Source Polinom" << endl;
                    break;
                }
                double num;
                cout << "Enter number: ";
                cin >> num;
                currentPoly = currentPoly * num;
                cout << "Multiply result: " << currentPoly << endl;
                break;
            }
            case 11: {
                currentPoly = Polinom();
                hasPoly = false;
                cout << "Polinom reset complete" << endl;
                break;
            }
            case 0: {
                break;
            }
            default: {
                cout << "Wrong Input" << endl;
                break;
            }
            }
        }
        catch (const exception& e) {
            cout << "Error" << endl;
        }

    } while (choice != 0);

    return 0;
}