'''
This program querys the yahoo weather api in order to get the weather conditions at any city in the world.

Enjoy!

Gabriel Walker
gabriel.walker@colorado.edu
'''

#Example calls:

'''To get information about boulder'''
#C:\Users\Gabriel\Documents\School Spring 2015\Data Structures> & '.\test_script.py' boulder


#urllib.request is the library that allows us to get information from a website
#The json library is what we use for formating
#The sys library is to use command line arguments
import urllib.request, json

#Getting the comand line argument part of the sys library
from sys import argv

#Setting the city name and the condition wanted to the command line arguments entered. The first argument of argv is the script path, which we don't need
not_used, city = argv

#The website with jsons object, one of which we will be using. In this case, the yahoo weather query api page
baseurl = "https://query.yahooapis.com/v1/public/yql?"

#Our (inconplete) query which tells the website that we want the temperature object from the city that was inputed
temp_query = 'select * from weather.forecast where woeid in (select woeid from geo.places(1) where text="")'

#Find where the city name will be inserted
index = temp_query.find('")')

#Create a new string (which is part of our query) with the city name sandwiched in the correct spot
yql_query = temp_query[:index] + city + temp_query[index:]

#Creates the url that we will get our specific json object from by appending the baseurl, our query* and the format that we want (the default format is xml)
#* I have not a clue what urlencode does
yql_url = baseurl + urllib.parse.urlencode({'q':yql_query}) + "&format=json"

#This is the part of the code that politely asks for the part of the json object that we want (the temperature)
encoded_result = urllib.request.urlopen(yql_url).read()

#Aparently urlopen returns "bytes" but json wants "str" so . . .
decoded_result = encoded_result.decode("utf-8")

#Load the string into json so that is can be manipulated as such
data = json.loads(decoded_result)

#By manipulated we mean pretty print
data = json.dumps(data, indent=1, sort_keys=True)

#Writes the temperature information to a text file with the name of the city. ex Boulder.txt
outfile = open(city + '.txt','w')
outfile.write(data)

#Closes the file
outfile.close()


#Most of the code is the example code from https://developer.yahoo.com/weather/
#All the rest is from google searches and stackexchange
