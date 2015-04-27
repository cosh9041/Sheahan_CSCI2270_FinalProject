#include "weatherdata.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>

using namespace std;

WeatherData::WeatherData() {
    nil = new WeatherDataNode();
    root = nil;
    root->parent = nil;
    root->leftChild = nil;
    root->rightChild = nil;
}

WeatherData::~WeatherData(){
	DeleteAll(root);
}

void WeatherData::DeleteAll(WeatherDataNode * node) {
	if (node) {
		DeleteForecasts(node->fore);
		if (node->leftChild != nil)
			DeleteAll(node->leftChild);
		if (node->rightChild != nil)
			DeleteAll(node->rightChild);
    }
    delete node;
}

void WeatherData::DeleteForecasts(Forecast * node) {
	if (node->next) 
		DeleteForecasts(node->next);
	delete node;
}

bool WeatherData::foundCity(string name) {
	if (searchWeatherTree(root, name) != nil)
		return true;
	return false;
}

WeatherDataNode* WeatherData::searchWeatherTree(WeatherDataNode * node, string name) {
   if (node == nil)
       return nil;
   else if (node->loc.cityName == name)
       return node;
   else {
      if(name.compare(node->loc.cityName) < 0)
         return searchWeatherTree(node->leftChild,name);
      else
         return searchWeatherTree(node->rightChild,name);
   }
}


void WeatherData::addCity(string cityInfo) {
	WeatherDataNode * newCity = new WeatherDataNode();
	newCity->parent = nil;
	newCity->leftChild = nil;
	newCity->rightChild = nil;

	//Get Sun Data
	newCity->sunData.sunrise = cityInfo.substr(cityInfo.find("sunrise\":") + 11 , 7);
	newCity->sunData.sunset = cityInfo.substr(cityInfo.find("sunset\":") + 10 , 7);
	
	//Get Astronomy Data
	newCity->atmosData.humidity = cityInfo.substr(cityInfo.find("humidity") + 12, 2) + "%";
	
	cityInfo.erase(0, cityInfo.find("pressure\":"));
	newCity->atmosData.pressure = cityInfo.substr(cityInfo.find("pressure") + 12, cityInfo.find("\",") - (cityInfo.find("pressure") + 12)) + " psi";
	
	cityInfo.erase(0, cityInfo.find("rising\":"));
	newCity->atmosData.rising = cityInfo.substr(cityInfo.find("rising") + 10, cityInfo.find("\",") 
		- (cityInfo.find("rising") + 10));
	
	cityInfo.erase(0, cityInfo.find("visibility\":"));
	newCity->atmosData.visibility = cityInfo.substr(cityInfo.find("visibility") 
		+ 14, cityInfo.find("\" ") - (cityInfo.find("visibility") + 14)) + " mi";
	
	
	//Get curr temp and time
	cityInfo.erase(0, cityInfo.find("date\":"));
	newCity->timeOfQuery = cityInfo.substr(cityInfo.find("date") + 8, cityInfo.find("\",") 
		- (cityInfo.find("date") + 8));
		
	cityInfo.erase(0, cityInfo.find("temp\":"));
	newCity->currTemp = cityInfo.substr(cityInfo.find("temp") + 8, cityInfo.find("\",") 
		- (cityInfo.find("temp") + 8)) + " F";
		
	cityInfo.erase(0, cityInfo.find("text\":"));
	newCity->currWeather = cityInfo.substr(cityInfo.find("text") + 8, cityInfo.find("\" ") 
		- (cityInfo.find("text") + 8));
		
	
	//Get Forecast Data
	for (int i = 0; i < 5; i++) { 
		Forecast * temp = new Forecast();
		
		cityInfo.erase(0, cityInfo.find("date\":"));
		temp->date = cityInfo.substr(cityInfo.find("date") + 8, cityInfo.find("\",") 
			- (cityInfo.find("date") + 8));
			
		cityInfo.erase(0, cityInfo.find("day\":"));
		temp->day = cityInfo.substr(cityInfo.find("day") + 7, cityInfo.find("\",") 
			- (cityInfo.find("day") + 7));
			
		cityInfo.erase(0, cityInfo.find("high\":"));
		temp->high = cityInfo.substr(cityInfo.find("high") + 8, cityInfo.find("\",") 
			- (cityInfo.find("high") + 8)) + " F";
			
		cityInfo.erase(0, cityInfo.find("low\":"));
		temp->low = cityInfo.substr(cityInfo.find("low") + 7, cityInfo.find("\",") 
			- (cityInfo.find("low") + 7)) + " F";
			
		cityInfo.erase(0, cityInfo.find("text\":"));
		temp->storm = cityInfo.substr(cityInfo.find("text") + 8, cityInfo.find("\" ") 
			- (cityInfo.find("text") + 8));
		
		
		Forecast * x = newCity->fore;
		
		if (!x) {
			newCity->fore = temp;
		}
		else { 
			while(x->next) 
				x = x->next;
			x->next = temp;
		}
	}
	
	
	//Get Location Data
	cityInfo.erase(0, cityInfo.find("lat\":"));
	newCity->loc.lat = cityInfo.substr(cityInfo.find("lat") + 7, cityInfo.find("\",") - (cityInfo.find("lat") + 7));
	
	cityInfo.erase(0, cityInfo.find("long\":"));
	newCity->loc.lon = cityInfo.substr(cityInfo.find("long") + 8, cityInfo.find("\",") - (cityInfo.find("lon") + 8));	
	
	cityInfo.erase(0, cityInfo.find("city\":"));
	newCity->loc.cityName = cityInfo.substr(cityInfo.find("city\":") + 8, cityInfo.find("\",") - (cityInfo.find("city\":")+8));
	
	cityInfo.erase(0, cityInfo.find("country\":"));
	newCity->loc.country = cityInfo.substr(cityInfo.find("country\":") + 11, cityInfo.find("\",") - (cityInfo.find("country\":")+11));
	
	cityInfo.erase(0, cityInfo.find("region\":"));
	newCity->loc.region = cityInfo.substr(cityInfo.find("region\":") + 10, cityInfo.find("\" ") - (cityInfo.find("region\":")+10));

	
	//Get Wind Data
	cityInfo.erase(0, cityInfo.find("chill\":"));
	newCity->wind.chill = cityInfo.substr(cityInfo.find("chill") + 9, cityInfo.find("\",") - (cityInfo.find("chill") + 9)) + " F";
		
	cityInfo.erase(0, cityInfo.find("direction\":"));
	newCity->wind.direction = cityInfo.substr(cityInfo.find("direction") + 13, cityInfo.find("\",") - (cityInfo.find("direction") + 13));
	
	cityInfo.erase(0, cityInfo.find("speed\":"));
	newCity->wind.speed = cityInfo.substr(cityInfo.find("speed") + 9, cityInfo.find("\" ") - (cityInfo.find("speed") + 9)) + " mph";



	//Put weather data into tree by cityname.
	WeatherDataNode * x = root;
	
    if (root == nil) {
        root = newCity;
        root->isRed = false;
    }
    else {
        while (x != nil) {
            if (strcmp(newCity->loc.cityName.c_str(), x->loc.cityName.c_str()) < 0) {
                if (x->leftChild == nil) {
					x->leftChild = newCity;
					newCity->parent = x;
					break;
				}
				x = x->leftChild;
				continue;
			}
			if (strcmp(newCity->loc.cityName.c_str(), x->loc.cityName.c_str()) >= 0) {
				if (x->rightChild == nil) {
					x->rightChild = newCity;
					newCity->parent = x;
					break;
				}
				x = x->rightChild;
				continue;
			}
		}
	}
    rbAddFixup(newCity);
    return;
}



void WeatherData::rbAddFixup(WeatherDataNode * node) {
   while (node != root && node->parent->isRed) {
      if (node->parent == node->parent->parent->leftChild) {
         WeatherDataNode *temp = node->parent->parent->rightChild;
         if (temp->isRed) {
            node->parent->isRed = false;
            temp->isRed = false;
            node->parent->parent->isRed = true;
            node = node->parent->parent;
         }
         else {
            if (node == node->parent->rightChild) {
               node = node->parent;
               leftRotate(node);
            }
            node->parent->isRed = false;
            node->parent->parent->isRed = true;
            rightRotate(node->parent->parent);
         }
      }
      else {
         WeatherDataNode *temp = node->parent->parent->leftChild;
         if (temp->isRed) {
            node->parent->isRed = false;
            temp->isRed = false;
            node->parent->parent->isRed = true;
            node = node->parent->parent;
         }
         else {
            if (node == node->parent->leftChild) {
               node = node->parent;
               rightRotate(node);
            }
            node->parent->isRed = false;
            node->parent->parent->isRed = true;
            leftRotate(node->parent->parent);
         }
      }
   }
   root->isRed = false;
}


void WeatherData::leftRotate(WeatherDataNode *node) {
    WeatherDataNode *x = node->rightChild;
    node->rightChild = x->leftChild;
    if (x->leftChild != nil)
        x->leftChild->parent = node;
    x->parent = node->parent;
    if (node->parent == nil)
        root = x;
    else if (node->parent->leftChild == node)
        node->parent->leftChild = x;
    else node->parent->rightChild = x;
    node->parent = x;
    x->leftChild = node;
}

void WeatherData::rightRotate(WeatherDataNode *node) {
    WeatherDataNode *x = node->leftChild;
    node->leftChild = x->rightChild;
    if (x->rightChild != nil)
        x->rightChild->parent = node;
    x->parent = node->parent;
    if (node->parent == nil)
        root = x;
    else if (node->parent->leftChild == node)
        node->parent->leftChild = x;
    else node->parent->rightChild = x;
    node->parent = x;
    x->rightChild = node;
}


void WeatherData::printCitiesByName() {
   printCitiesByName(root);
}

/* Prints the inventory(in order traversal) */
void WeatherData::printCitiesByName(WeatherDataNode * node) {
   if(node->leftChild != nil)
       printCitiesByName(node->leftChild);

	cout << node->loc.cityName << endl;

   if(node->rightChild != nil)
       printCitiesByName(node->rightChild);
   return;
}

void WeatherData::getAstronomyData(string city) {
	WeatherDataNode * x = searchWeatherTree(root, city);
	cout << "The Sunrise for today is at " << x->sunData.sunrise << "." << endl;
	cout << "The sunset for today is at " << x->sunData.sunset << "." << endl;
}

void WeatherData::getAtmosphericData(string city) {
	WeatherDataNode * x = searchWeatherTree(root, city);
	cout << "The humidity right now is " << x->atmosData.humidity << "." << endl;
	cout << "The atmospheric pressure right now is " << x->atmosData.pressure << "." << endl;
	cout << "The visibility right now is " << x->atmosData.visibility << "." << endl;
}

void WeatherData::getForecast(string city) {
	WeatherDataNode * x = searchWeatherTree(root, city);
	Forecast * temp = x->fore;
	cout << "5 Day Forecast for " << x->loc.cityName << ", " << x->loc.region << ":" << endl;
	while (temp) {
		cout << "_____" + temp->day + ", " + temp->date + "_____" << endl;
		cout << "High: " << temp->high << endl;
		cout << "Low: " << temp->low << endl;
		cout << temp->storm << endl << endl;
		temp = temp->next;
	}
}

void WeatherData::getWindData(string city) {
	WeatherDataNode * x = searchWeatherTree(root, city);
	cout << "Chill Factor: " << x->wind.chill << endl;
	cout << "Direction: " << x->wind.direction << endl;
	cout << "Speed: " << x->wind.speed << endl;
}

void WeatherData::getLocation(string city) {
	WeatherDataNode * x = searchWeatherTree(root, city);
	cout << x->loc.cityName << ", " << x->loc.region << endl;
	cout << x->loc.country << endl;
	cout << "Latitude: " << x->loc.lat << endl;
	cout << "Longitude: " << x->loc.lon << endl;
}

void WeatherData::getCurrentWeather(string city) {
	WeatherDataNode * x = searchWeatherTree(root, city);
	cout << "As of " + x->timeOfQuery + ":" << endl;
	cout <<"Temperature: " << x->currTemp << endl;
	cout << x->currWeather << endl;
}
	
void WeatherData::getAllWeatherData(string city) {
	WeatherDataNode * x = searchWeatherTree(root, city);
	cout << "Information for " << x->loc.cityName << ", " << x->loc.region << ":" << endl;
	getCurrentWeather(city);
	cout << "Location Information:" << endl;
	getLocation(city);
	getForecast(city);
	getAstronomyData(city);
	getAtmosphericData(city);
	getWindData(city);
	
}

void WeatherData::deleteCity(string city){
   WeatherDataNode *found = searchWeatherTree(root, city);

   if (found == nil)
      cout << "That city is not in the network!" << endl;
   else {
      rbDelete(found);
   }
}

void WeatherData::rbDelete(WeatherDataNode * z){
   WeatherDataNode *y = z;
   bool origCol = y->isRed;
   WeatherDataNode *temp;
   if (z->leftChild == nil) {
      temp = z->rightChild;
      rbTransplant(z, z->rightChild);
   }
   else if (z->rightChild == nil) {
      temp = z->leftChild;
      rbTransplant(z, z->leftChild);
   }
   else {
      y = y->rightChild;
      while (y->leftChild != nil) {
         y = y->leftChild;
      }
      origCol = y->isRed;
      temp = y->rightChild;
      if (y->parent == z)
         temp->parent = z;
      else {
         rbTransplant(y, y->rightChild);
         y->rightChild = z->rightChild;
         y->rightChild->parent = y;
      }
      rbTransplant(z, y);
      y->leftChild = z->leftChild;
      y->leftChild->parent = y;
      y->isRed = z->isRed;
   }
   delete z;
   if (!origCol)
      rbDeleteFixup(temp);
}

void WeatherData::rbDeleteFixup(WeatherDataNode * x){
    while (x != root && !x->isRed) {
      if (x == x->parent->leftChild) {
         WeatherDataNode *w = x->parent->rightChild;
         if (w->isRed) {
            w->isRed = false;
            x->parent->isRed = true;
            leftRotate(x->parent);
            w = x->parent->rightChild;
         }
         if (!w->leftChild->isRed && !w->rightChild->isRed) {
            w->isRed = true;
            x = x->parent;
         }
         else {
            if (!w->rightChild->isRed) {
               w->leftChild->isRed = false;
               w->isRed = true;
               rightRotate(w);
               w = x->parent->rightChild;
            }
            w->isRed = x->parent->isRed;
            x->parent->isRed = false;
          //  w->isRed = x->parent->isRed;
            w->rightChild->isRed = false;
            leftRotate(x->parent);
            x = root;
         }
      }
      else  {
         WeatherDataNode *w = x->parent->leftChild;
         if (w->isRed) {
            w->isRed = false;
            x->parent->isRed = true;
            rightRotate(x->parent);
            w = x->parent->leftChild;
         }
         if (!w->rightChild->isRed && !w->leftChild->isRed) {
            w->isRed = true;
            x = x->parent;
         }
         else {
            if (!w->leftChild->isRed) {
               w->rightChild->isRed = false;
               w->isRed = true;
               leftRotate(w);
               w = x->parent->leftChild;
            }
            w->isRed = x->parent->isRed;
            x->parent->isRed = false;
            w->leftChild->isRed = false;
            rightRotate(x->parent);
            x = root;
         }
      }
  }
   x->isRed = false;
}

void WeatherData::rbTransplant(WeatherDataNode * u, WeatherDataNode * v){
    if(u->parent == nil){
        root = v;
    }

    else{
        if(u == u->parent->leftChild){
            u->parent->leftChild = v;
        }
        else{
            u->parent->rightChild = v;
            v->parent = u->parent;
        }
    }
}

//WeatherData
