/*Compilar used: Dev-C++ 5.11  |  TDM-GCC 4.9.2 64-bit release
Group 12
Group Leader: Ho Yen Hong 242UT 241BT
Group Members: Joel Prakash Noel Francisco 242UT2443B
               Akmal Muqry Bin Ainuddin 243UT246WP
               Ma Zheng Yuan 243UT241CG
               Ong Yong Quan 243UT246XG
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <windows.h>
using namespace std;

const int GREEN = 10;
const int YELLOW = 14;
const int RED = 12;
const int RESET = 7;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void showWelcome() {
    setColor(GREEN);
    cout << "================================\n";
    cout << "   CARBON FOOTPRINT CALCULATOR\n";
    cout << "================================\n\n";
    setColor(RESET);
}

float getValidNumber(string prompt, float min, float max) {
    float value;
    while (true) {
        setColor(GREEN);
        cout << prompt;
        setColor(YELLOW);
        cin >> value;
        
        if (cin.fail() || value < min || value > max) {
            setColor(RED);
            cout << "Invalid input! Please enter between " << min << " and " << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore();
            return value;
        }
    }
}

string getValidTransport() {
    string transport;
    string valid[] = {"car", "bus", "train", "bicycle", "ev", "walk"};
    int count = 6;
    
    while (true) {
        cout << "Transport (car/bus/train/bicycle/ev/walk): ";
        cin >> transport;
        
        // Convert to lowercase
        for (size_t i = 0; i < transport.length(); ++i)
    		transport[i] = tolower(transport[i]);
        
        // Check validity
        bool validTransport = false;
        for (int i = 0; i < count; i++) {
            if (transport == valid[i]) {
                validTransport = true;
                break;
            }
        }
        
        if (validTransport) return transport;
        cout << "Invalid option! Please choose from the list.\n";
    }
}

int main() {
    showWelcome();
    
    // Transportation
    string transport = getValidTransport();
    float distance = getValidNumber("Daily distance (km): ", 0, 1000);
    
    float transportEmission = 0;
    if (transport == "car") transportEmission = distance * 0.271;
    else if (transport == "bus") transportEmission = distance * 0.105;
    else if (transport == "train") transportEmission = distance * 0.077;
    else if (transport == "ev") transportEmission = distance * 0.05;

    // Electricity
    float electricity = getValidNumber("Daily electricity (kWh): ", 0, 200);
    float renewable = getValidNumber("% from renewable sources: ", 0, 100);
    
    float electricityEmission = electricity * 0.475 * (1 - renewable/100.0);
    float total = transportEmission + electricityEmission;

    // Results
    setColor(GREEN);
    cout << fixed << setprecision(2);
    cout << "\n=== SUMMARY ===" << endl;
    setColor(YELLOW);
    cout << "Transportation: " << transportEmission << " kg CO2" << endl;
    cout << "Electricity:    " << electricityEmission << " kg CO2" << endl;
    setColor(GREEN);
    cout << "TOTAL DAILY:    " << total << " kg CO2" << endl;
    
    setColor(RESET);
    return 0;
}
