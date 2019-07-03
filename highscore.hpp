#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;
bool update_highscore(int points) {
   ofstream filew;
   ifstream filer;
   int hspoints;
   bool newfile = false;
   filer.open("./highscores", ios::out);
	bool hs = false; //This variable represents if the given points results in a new highscore or not
	   if (!filer.is_open()) {
		filew.open("./highscores");
		filew << "0";
		hspoints = 0;
		newfile = true;
		filew.close();
	}
		if (!newfile) {
			string output = "";
			string line;
	   
		while (std::getline(filer, line)) {
			hspoints = stoi(line);
		}
		}

	   filer.close();
	   
	   if (hspoints > points) {
		   hs = false;
	   } else {
		   filew.open("./highscores");
		   string newpoints = to_string(points);
		   filew << newpoints;
		   filew.close();
		   hs = true;
	   }
	   return hs;
	   
   

}

int get_highscore() {
	ofstream filew;
	ifstream filer;
	int hspoints;
	bool newfile = false;
	filer.open("./highscores", ios::out);
	   if (!filer.is_open()) {
		filew.open("./highscores");
		filew << "0";
		hspoints = 0;
		newfile = true;
		filew.close();
	}
		if (!newfile) {
			string output = "";
			string line;
	   
		while (std::getline(filer, line)) {
			hspoints = stoi(line);
		}
		}

	   filer.close();

	   return hspoints;
	   
}