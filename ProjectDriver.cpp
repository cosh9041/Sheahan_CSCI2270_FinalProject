#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "weatherdata.h"

using namespace std;

void printMenu() {
    cout << "====Main Menu====" << endl;
    cout << "1. Add city" << endl;
    cout << "2. Delete city" << endl;
    cout << "3. Print all cities" << endl;
    cout << "4. Get Weather info" << endl;
    cout << "8. Quit" << endl;
}
/*
void weather Menu(WeatherData * ws) {
	cout << "Which city do you want information about? << endl;
	cin.ignore();
	string cityName;
	cin >> cityName;
	if (ws->foundCity(cityName)) {
	//	
}*/
void inputCity(string city, WeatherData * ws) {
    //Set command argument to pass to system command line to call python file that gets weather data.
    string filename = "./getWeatherData.py";
    string baseCommand = "python3.4 ";
    baseCommand += filename;

    string command = baseCommand + " " + "\"" + city + "\"";
    system(command.c_str());
    ifstream fileReader;
    fileReader.open((city + ".txt").c_str());

    string temp;
    string cityInfo;
    while(getline(fileReader, temp)) {
        cityInfo += temp;
    }
    remove((city + ".txt").c_str());
    if (cityInfo.length() < 600 ) 
		cout << city + " not found. Please enter a valid city." << endl;
	else ws->addCity(cityInfo);
}

int main() {

    WeatherData  * ws = new WeatherData();
    cout << "Adding initial cities to network..." << endl;
    inputCity("Denver", ws);
    inputCity("New York", ws);
    inputCity("Los Angeles", ws);
    inputCity("Portland", ws);
    inputCity("New Orleans", ws);
    inputCity("Miami", ws);
    inputCity("Washington, D.C.", ws);
    inputCity("Seattle", ws);
    inputCity("San Diego", ws);
    inputCity("San Francisco", ws);
    inputCity("Chicago", ws);
    inputCity("Atlanta", ws);
    inputCity("Boston", ws);
    inputCity("Cincinnati", ws);
    inputCity("Dallas", ws);
    inputCity("Salt Lake City", ws);
    
    int userArg;
    printMenu();

    while (cin >> userArg) {
        if (userArg == 1) {
            cout << "Enter city name:" << endl;
            cin.ignore();
            string city;
            getline(cin, city);
            inputCity(city, ws);
        }
        if (userArg == 2) {
            cout << "deleting city..." << endl;
        }
        if (userArg == 3) {
			ws->printCitiesByName();
		}
        if (userArg == 8) {
            cout << "Goodbye!" << endl;
            break;
        }
        printMenu();
    }
    delete ws;
}
