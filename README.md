# Sheahan_CSCI2270_FinalProject

Project Summary:
This project offers the user a way to get weather information from the command line in Unix. 
The program executable, when called, will then offer the user a menu. The program queries the Yahoo!
Weather API to provide up to the minute inforamtion to the user. The user has options to add cities to a locally stored 
database. The use can then request all possible weather information contained on the Yahoo! Weather page
from the command terminal. In addition, a number of major cities in North America will 
be pre-loaded with Yahoo weather up to the minute information when the program starts. 

How to Run:
Download ProjectDriver.cpp, getWeatherData.py, weatherdata.cpp, and weatherdata.h into the same file. Open a 
command terminal and type: "g++ ProjectDriver.cpp weatherdata.cpp -o Weather". This will compile the program into the
executable file called Weather. It should be noted that you may name the file whatever you wish. To run the program
simply type "./Weather" and you will enter the program. The program will prompt you with menu options. Type and integer 
corresponding to your desired choice and then press Enter. This is how you run the program.

Dependencies:
The program depends on the yahoo weather API, however this is invisible to the user. This program also requires Python 3.4
to run. You must have it installed.

System requirements:
This program will run on any modern machine running a Linux operating system. Support is currently not 
available for other operating systems. Python 3.4 is required.

Group Members:
Corwin Sheahan, Gabriel Walker

Contributors:
Rhonda Hoenigman

Open issues/bugs:
Would like to offer support for different operating systems. At this point, the code is dependent upon
the structure of the file system used in Linux and is not compatible with any other operating system.

Won't get information for different cities with the same name. Example: Aurora IL and Aurora CO
