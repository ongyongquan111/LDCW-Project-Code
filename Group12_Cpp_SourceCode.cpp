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
using namespace std;

int main() {
    // Transportation
    string transport;
    float distance;
    cout << "Transport (car/bus/train/bicycle/ev/walk): ";
    cin >> transport;
    cout << "Distance (km): ";
    cin >> distance;
    
    float transportEmission = 0;
    if (transport == "car") transportEmission = distance * 0.271;
    else if (transport == "bus") transportEmission = distance * 0.105;
    else if (transport == "train") transportEmission = distance * 0.077;
    else if (transport == "ev") transportEmission = distance * 0.05;

    // Electricity
    float electricity, renewable;
    cout << "Electricity (kWh): ";
    cin >> electricity;
    cout << "Renewable (%): ";
    cin >> renewable;
    
    float electricityEmission = electricity * 0.475 * (1 - renewable/100.0);
    float total = transportEmission + electricityEmission;

    // Results
    cout << fixed << setprecision(2);
    cout << "\nTRANSPORT: " << transportEmission << " kg CO2" << endl;
    cout << "ELECTRICITY: " << electricityEmission << " kg CO2" << endl;
    cout << "TOTAL DAILY: " << total << " kg CO2" << endl;
    
    return 0;
}
