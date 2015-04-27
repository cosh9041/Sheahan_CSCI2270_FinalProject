#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "weatherdata.h"

using namespace std;

/* Main menu */
void printMainMenu() {
    cout << "====Main Menu====" << endl;
    cout << "1. Add city" << endl;
    cout << "2. Delete city" << endl;
    cout << "3. Print all cities" << endl;
    cout << "4. Get current weather" << endl;
    cout << "5. Get detailed weather information" << endl;
    cout << "6. Quit" << endl;
}

/* Weather menu */
void printWeatherMenu() {
	cout << "====Weather Options====" << endl;
	cout << "1. Astronomy data" << endl;
	cout << "2. Atmospheric data"<< endl;
	cout << "3. 5 Day Forecast" << endl;
	cout << "4. Location data" << endl;
	cout << "5. Wind data" << endl;
	cout << "6. All Weather data" << endl;
	cout << "7. Back to main menu" << endl;
}

/* Calls addCity in class WeatherData to add city to the database */
void inputCity(string city, WeatherData * wData) {
    //Set command argument to pass to system command line to call python file that gets weather data.
    string filename = "./getWeatherData.py";
    string baseCommand = "python3.4 ";
    baseCommand += filename;
	
	//Call Python file to get weather data.
    string command = baseCommand + " " + "\"" + city + "\"";
    system(command.c_str());
    
    //Read output file.
    ifstream fileReader;
    fileReader.open((city + ".txt").c_str());

	//Put city into weatherdata database.
    string temp;
    string cityInfo;
    while(getline(fileReader, temp)) {
        cityInfo += temp;
    }
    remove((city + ".txt").c_str());
    if (cityInfo.length() < 600 ) 
		cout << city + " not found. Please enter a valid city." << endl;
	else wData->addCity(cityInfo);
		
}

/* Called when use selects detailed weather options. */
void weatherOptions(WeatherData * wData) {
	cout << "Which city do you want information about?" << endl;
	//cin.ignore();
	string cityName;
	cin >> cityName;
	if (wData->foundCity(cityName)) {
		printWeatherMenu();
		int userArg;
		while (cin >> userArg) {
			if (userArg == 1) {
				wData->getAstronomyData(cityName);
			}
			if (userArg == 2) {
				wData->getAtmosphericData(cityName);
			}	
			if (userArg == 3) {
				wData->getForecast(cityName);
			}
			if (userArg == 4) {
				wData->getLocation(cityName);
			}
			if (userArg == 5) {
				wData->getWindData(cityName);
			}
			if (userArg == 6) {
				wData->getAllWeatherData(cityName);
			}
			if (userArg == 7) {
				break;
			}
			printWeatherMenu();
		}		
	}
	else  {
		inputCity(cityName, wData);
		printWeatherMenu();
		int userArg;
		while (cin >> userArg) {
			if (userArg == 1) {
				wData->getAstronomyData(cityName);
			}
			if (userArg == 2) {
				wData->getAtmosphericData(cityName);
			}	
			if (userArg == 3) {
				wData->getForecast(cityName);
			}
			if (userArg == 4) {
				wData->getLocation(cityName);
			}
			if (userArg == 5) {
				wData->getWindData(cityName);
			}
			if (userArg == 6) {
				wData->getAllWeatherData(cityName);
			}
			if (userArg == 7) {
				break;
			}
			printWeatherMenu();
		}
	}
}

int main() {

    WeatherData  * wData = new WeatherData();
    cout << "Adding initial cities to network..." << endl;
    inputCity("Denver", wData);
    inputCity("New York", wData);
    inputCity("Los Angeles", wData);
    inputCity("Portland", wData);
    inputCity("New Orleans", wData);
    inputCity("Miami", wData);
    inputCity("Washington, D.C.", wData);
    inputCity("Seattle", wData);
    inputCity("San Diego", wData);
    inputCity("San Francisco", wData);
    inputCity("Chicago", wData);
    inputCity("Atlanta", wData);
    inputCity("Boston", wData);
    inputCity("Cincinnati", wData);
    inputCity("Dallas", wData);
    inputCity("Salt Lake City", wData);
    
    int userArg;
    printMainMenu();

    while (cin >> userArg) {
        if (userArg == 1) {
            cout << "Enter city name:" << endl;
            cin.ignore();
            string city;
            getline(cin, city);
            if (!wData->foundCity(city))
				inputCity(city, wData);
        }
        if (userArg == 2) {
            cout << "Enter city to be removed from memory: " << endl;
            cin.ignore();
            string city;
            getline(cin, city);
            wData->deleteCity(city);
        }
        if (userArg == 3) {
			wData->printCitiesByName();
		}
		if (userArg == 4) {
			cout << "Enter city: " << endl;
			string city;
			cin.ignore();
			getline(cin, city);
			if (wData->foundCity(city)) {
				wData->getCurrentWeather(city);
			}
			else { 
				inputCity(city, wData);
				wData->getCurrentWeather(city);
			}
		}
		if (userArg == 5) {
			weatherOptions(wData);
		}
        if (userArg == 6) {
            cout << "Goodbye!" << endl;
            break;
        }
        printMainMenu();
    }
    delete wData;
}
