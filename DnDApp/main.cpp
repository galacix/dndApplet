#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
class dndChar{
public:

};
vector <string> lineCopier(string fileName) { //Initiates the vector creation function // eventually put in a header
	string line;
	vector <string> nameVector; //initiates vector

	ifstream tempFile(fileName);  //constructs an ifstream object temporarily using a local file temporarily
	if (tempFile.is_open()) //if the file is opened successfully
	{
		while (!tempFile.eof()) { //Loop that runs until the last line of the file
			getline(tempFile, line); //Grabs the line it is on
			nameVector.push_back(line); //Pushes the contents of the line back into the vector
		}
		tempFile.close();
	}
	return nameVector;
}

string nameGenerator(string fileHeader, string fileEnder) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //obtains a time since last epoch, stores it in seed

	vector <string> nameHeader = lineCopier(fileHeader);
	vector <string> nameEnder = lineCopier(fileEnder);

	shuffle(nameHeader.begin(), nameHeader.end(), std::default_random_engine(seed)); //shuffles the elements of the vector based on a random number generated from seed
	string generatedName = nameHeader[0];

	shuffle(nameEnder.begin(), nameEnder.end(), std::default_random_engine(seed)); //shuffles the elements of the vector based on a random number generated from seed
	generatedName += nameEnder[0];

	return generatedName;
}


int main() 
{
	string race[3] {"humanHeader.txt", "humanEnder.txt" };
	string choiceBump = "\n\nResponse: ";
	short exitMenu = 0, menuChoice, counter = 0, gmeBreak;

	while (exitMenu != 1) {
		cout << "Choose an option:" << endl << "1. Character Name Generator" << choiceBump;
		cin >> menuChoice;

		if (menuChoice == 1) {
			cout << "\nWould you like to generate a new name... " << endl << "1. Yes\n2. No " << choiceBump;
			cin >> menuChoice;				
			while (menuChoice == 1) {
				if (counter == 0) {
					cout << "\nPlease choose a race type:" << endl << "1. Human" << choiceBump;
					cin >> menuChoice;
					counter++;
				}
				cout << "\nGenerating name..." << endl;

				string name = nameGenerator(race[menuChoice++], race[--menuChoice]);

				cout << endl << "Do you like the name: " << name << "\n\n1. Re-Generate\n2. Accept" << choiceBump;
				cin >> menuChoice;

				if (menuChoice == 2)
					cout << "Exiting name generator..." << endl;
			}
		}
	}
	system("pause");
	return 0;
}