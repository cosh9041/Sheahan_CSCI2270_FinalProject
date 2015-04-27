#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <iostream>

struct Sun {
    std::string sunrise;
    std::string sunset;
};

struct Atmosphere {
    std::string humidity;
    std::string pressure;
    std::string rising;
    std::string visibility; 
};

struct Forecast {
    Forecast *next;
    std::string date;
    std::string day;
    std::string high;
    std::string low;
    std::string storm;
    
    Forecast(){
		next = NULL;
	};
};

struct Location {
    std::string cityName;
    std::string country;
    std::string region;
    std::string lat;
    std::string lon;
};

struct WindData {
    std::string chill;
    std::string direction;
    std::string speed;
};


struct WeatherDataNode {
    Sun sunData;
    Atmosphere atmosData;
    std::string currTemp;
    std::string timeOfQuery;
    std::string currWeather;
    Forecast * fore;
    Location loc;
    WindData wind;
    
    bool isRed;

    WeatherDataNode * parent;
    WeatherDataNode * leftChild;
    WeatherDataNode * rightChild;
    
    WeatherDataNode(){
		fore = NULL;
		parent = NULL;
		leftChild = NULL;
		rightChild = NULL;
		isRed = true;
	};


};

class WeatherData {



public:
    WeatherData();
    virtual ~WeatherData();
    void addCity(std::string cityInfo);
    void deleteCity(std:: string city);
    void printCitiesByName();
    void getCurrentWeather(std::string city);
    void getAstronomyData(std::string city);
    void getAtmosphericData(std::string city);
    void getForecast(std::string city);
    void getWindData(std::string city);
    void getAllWeatherData(std::string city);
    void getLocation(std::string city);
    bool foundCity(std::string name);


private:
    void DeleteAll(WeatherDataNode * node);
    void rbAddFixup(WeatherDataNode * node);
    void leftRotate(WeatherDataNode * x);
    void rightRotate(WeatherDataNode * x);
    void rbDelete(WeatherDataNode * z);
    void rbDeleteFixup(WeatherDataNode * node);
    void rbTransplant(WeatherDataNode * u, WeatherDataNode * v);
    int rbValid(WeatherDataNode * node);
    void printCitiesByName(WeatherDataNode * node);
    void DeleteForecasts(Forecast * node);
    WeatherDataNode *searchWeatherTree(WeatherDataNode * node, std::string name);

    WeatherDataNode * root;
    WeatherDataNode * nil;



};

#endif // WEATHERDATA_H
