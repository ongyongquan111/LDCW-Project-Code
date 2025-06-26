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
#include <cmath>
#include <string>
#include <limits>
#include <windows.h>
#include <algorithm>
using namespace std;

// Color constants - Green City theme
const int DARK_GREEN = 2;
const int BRIGHT_GREEN = 10;
const int EARTH_BROWN = 6;
const int SKY_BLUE = 11;
const int SUN_YELLOW = 14;
const int LEAF_GREEN = 10;
const int ERROR_RED = 12;
const int RESET = 7;

// Function to set text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function prototypes
void showWelcome();
float getValidNumber(const string& prompt, float min, float max);
string getValidTransport();
float calculateTransportEmission();
float calculateElectricityEmission();
void showSustainabilityTips(float totalEmission);
void displayCarbonComparison(float userEmission);
void printBanner();
void printSectionHeader(const string& text);

int main() {
    printBanner();
    showWelcome();
    
    //Get user inputs with validation
    float transportEmission = calculateTransportEmission();
    float electricityEmission = calculateElectricityEmission();
    float totalEmission = transportEmission + electricityEmission;
    
    // Display results
    setColor(SKY_BLUE);
    cout << fixed << setprecision(2);
    cout << "\n=== CARBON FOOTPRINT SUMMARY ===" << endl;
    setColor(BRIGHT_GREEN);
    cout << "Transportation: " << transportEmission << " kg CO2" << endl;
    cout << "Electricity:    " << electricityEmission << " kg CO2" << endl;
    setColor(SUN_YELLOW);
    cout << "TOTAL DAILY:    " << totalEmission << " kg CO2" << endl;
    cout << "ANNUAL IMPACT:  " << totalEmission * 365 << " kg CO2" << endl;
    
    // Show feedback
    showSustainabilityTips(totalEmission);
    displayCarbonComparison(totalEmission);
    
    setColor(LEAF_GREEN);
    cout << "\nExplore sustainable living solutions: ";
    cout << "https://ecosmartcity.shorthandstories.com/" << endl;
    
    setColor(RESET);
    return 0;
}

void printBanner() {
    setColor(DARK_GREEN);
    cout << "  ______          _    _                                        \n";
    cout << " |  ____|        | |  | |                                       \n";
    cout << " | |__   ___ ___ | |__| | __ _ _ __ _ __ ___   ___  _ __  _   _ \n";
    cout << " |  __| / __/ _ \\|  __  |/ _` | '__| '_ ` _ \\ / _ \\| '_ \\| | | |\n";
    cout << " | |___| (_| (_) | |  | | (_| | |  | | | | | | (_) | | | | |_| |\n";
    cout << " |______\\___\\___/|_|  |_|\\__,_|_|  |_| |_| |_|\\___/|_| |_|\\__, |\n";
    cout << "                                                          __/ |\n";
    cout << "                                                         |___/ \n" << endl;
}

void showWelcome() {
    setColor(BRIGHT_GREEN);
    cout << "============================================\n";
    setColor(EARTH_BROWN);
    cout << "   GREEN CITY SMART LIVING - ECO CALCULATOR\n";
    setColor(BRIGHT_GREEN);
    cout << "============================================\n\n";
    setColor(SKY_BLUE);
    cout << "Calculate your carbon footprint and discover\n";
    cout << "ways to contribute to sustainable urban living!\n\n";
    setColor(RESET);
}

void printSectionHeader(const string& text) {
    setColor(DARK_GREEN);
    cout << "\n" << text << "\n";
    setColor(BRIGHT_GREEN);
    cout << string(text.length(), '=') << "\n";
    setColor(RESET);
}

// Universal number validator
float getValidNumber(const string& prompt, float min, float max) {
    float value;
    while (true) {
        setColor(SKY_BLUE);
        cout << prompt;
        setColor(SUN_YELLOW);
        cin >> value;
        
        if (cin.fail()) { // Handle non-numeric input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            setColor(ERROR_RED);
            cout << "Invalid input. Please enter a number.\n";
        } 
        else if (value < min || value > max) { // Handle out-of-range
            setColor(ERROR_RED);
            cout << "Please enter a value between " << min << " and " << max << ".\n";
        }
        else {
            cin.ignore(); // Clear input buffer
            return value;
        }
        setColor(RESET);
    }
}

// Validato Transport mode
string getValidTransport() {
    string transport;
    string validOptions[] = {"car", "bus", "train", "bicycle", "ev", "walk"};
    const int NUM_OPTIONS = 6;
    
    while (true) {
        printSectionHeader("=== TRANSPORTATION ===");
        setColor(SKY_BLUE);
        cout << "Valid modes: car, bus, train, bicycle, ev, walk\n";
        cout << "Enter your primary transport: ";
        setColor(SUN_YELLOW);
        cin >> transport;
        
        // Convert to lowercase
        for (size_t i = 0; i < transport.length(); ++i) {
            transport[i] = tolower(transport[i]);
        }
        
        // Check against valid options
        bool valid = false;
        for (int i = 0; i < NUM_OPTIONS; ++i) {
            if (transport == validOptions[i]) {
                valid = true;
                break;
            }
        }
        
        if (valid) return transport;
        
        setColor(ERROR_RED);
        cout << "Invalid transport option! Please choose from the list.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        setColor(RESET);
    }
}

float calculateTransportEmission() {
    string transport = getValidTransport();
    float distance = getValidNumber("Daily distance (km): ", 0, 1000);
    
    if (transport == "car") return distance * 0.271;
    if (transport == "bus") return distance * 0.105;
    if (transport == "train") return distance * 0.077;
    if (transport == "ev") return distance * 0.05;
    return 0; // bicycle and walk
}

float calculateElectricityEmission() {
    printSectionHeader("=== ELECTRICITY USAGE ===");
    float electricity = getValidNumber("Daily electricity (0-200kWh): ", 0, 200);
    float renewable = getValidNumber("% from renewable sources (0-100): ", 0, 100);
    
    //Based on renewable percentage then adjust emission
    float emissionFactor = 0.475 * (1 - renewable/100.0);
    return electricity * emissionFactor;
}

void showSustainabilityTips(float totalEmission) {
    printSectionHeader("=== SUSTAINABILITY ANALYSIS ===");
    
    if (totalEmission < 3) {
        setColor(LEAF_GREEN);
        cout << "Excellent! You're a sustainability leader!\n";
        setColor(BRIGHT_GREEN);
        cout << "Maintain your green habits and inspire others.\n";
        cout << "- Share your practices on community forums\n";
        cout << "- Advocate for green policies in your workplace\n";
    }
    else if (totalEmission < 8) {
        setColor(SUN_YELLOW);
        cout << "Moderate impact - room for improvement\n";
        setColor(BRIGHT_GREEN);
        cout << "- Consider public transport 2+ days/week\n";
        cout << "- Install LED lighting at home\n";
        cout << "- Set thermostat 1C higher in summer\n";
        cout << "- Start a small herb garden on your balcony\n";
    }
    else {
        setColor(ERROR_RED);
        cout << "High environmental impact - action needed!\n";
        setColor(BRIGHT_GREEN);
        cout << "- Audit home energy usage\n";
        cout << "- Explore solar panel options\n";
        cout << "- Try meat-free days to reduce food emissions\n";
        cout << "- Join a local tree planting initiative\n";
    }
    setColor(RESET);
}

void displayCarbonComparison(float userEmission) {
    printSectionHeader("=== GLOBAL COMPARISON ===");
    setColor(SKY_BLUE);
    cout << "Your daily footprint: " << userEmission << " kg CO2\n";
    setColor(SUN_YELLOW);
    cout << "Global average:       ~14 kg CO2\n";
    cout << "Paris Agreement goal:  <5 kg CO2\n\n";
    
    float treesNeeded = ceil(userEmission * 365 / 21.77);
    setColor(LEAF_GREEN);
    cout << "You would need to plant " << treesNeeded << " trees\n";
    cout << "annually to offset your carbon footprint\n";
    
    // Additional eco facts
    setColor(EARTH_BROWN);
    cout << "\nDid you know?\n";
    cout << "- 1 tree absorbs ~22kg CO2 per year\n";
    cout << "- A solar panel reduces emissions by 1 ton CO2/year\n";
    cout << "- Cycling 10km daily saves 700kg CO2/year\n";
    setColor(RESET);
}
