#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum Components {player, wall, coin, alien, alien1};

int levelloader(void){
	int width=0, height=0;
	ifstream level_file("level1.level", ios::in);

	level_file >> width;
	level_file >> height;

	Components the_level [width][height];

	for(int i=0; i < height; i++){
	   string line;
	   level_file >> line;
	   int x;
	   level_file >> x;
           int y;
	   level_file >> y;
	}

	cout << width << endl;
	cout << height << endl;
}
	   
