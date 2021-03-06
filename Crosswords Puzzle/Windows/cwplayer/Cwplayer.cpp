/*Turma 8, Grupo 1, Trabalho 2 Parte 2(cwplayer)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Ara?jo Ferreira
*/

#define NOMINMAX
#include "dirent.h"
#include <iomanip>
#include <sstream>
#include "GameBoard.h"
#include "Player.h"


bool gameStart = false;

int welcome(Player *p, string message = "") {
	string name;
	Console console;
	bool validName = false;
	bool validOption = false;
	int option;
	cout << "WELCOME TO CROSSWORDS PUZZLE" << endl;
	cout << setfill('=') << setw(COUT_SIZE) << '=' << endl;
	if (message != "") {
		console.setcolor(LIGHTCYAN);
		cout << message << endl;
		cout << setfill('-') << setw(COUT_SIZE) << '-' << endl;
		console.setcolor(WHITE);
	}
	cout << "   > 0: Start a new Game;" << endl;
	cout << "   > 1: View Score Boards;" << endl;
	cout << "   > 2: Exit;" << endl;

	while (!validOption) {
		cout << "Choose one option: ";
		cin >> option;
		if (cin.eof()) {
			cout << "Invalid option!" << endl;
			cin.clear();
			continue;
		}
		if (!cin.fail()) {
			switch (option) {
			case 0: validOption = true;
				break;
			case 1: return 1;
			case 2: return 2;
			default:
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid option!" << endl;
			}
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid option!" << endl;
		}
	}

	if (p->getName().length() > 0) {
		char change = ' ';
		while (change != 'y' && change != 'n') {

			if (!cin.fail()) {
				cout << "Change player (y/n)? ";
				cin >> change;
				if (cin.eof()) {
					cout << "Invalid option!" << endl;
					cin.clear();
					continue;
				}
				if (change == 'n') {
					return 0;
				}
				if (change == 'y') {
					break;
				}
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid option!" << endl;
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid option!" << endl;
			}

		}
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "What is your name ? : ";

	while (!validName) {


		getline(cin, name);
		if (cin.eof()) {
			cout << "Invalid option!" << endl;
			cin.clear();
			cout << "What is your name ? : ";
			continue;
		}
		if (name.length() > 0 && !cin.fail()) {
			for (unsigned int i = 0; i < name.length(); i++) {
				if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ') {
					validName = true;
				}
				else {
					validName = false;
					console.clrscr();
					cout << "WELCOME TO CROSSWORDS PUZZLE" << endl;
					cout << setfill('=') << setw(COUT_SIZE) << '=' << endl;
					console.setcolor(LIGHTRED);
					cerr << "Please use only letters." << endl;
					cout << setfill('-') << setw(COUT_SIZE) << '-' << endl;
					console.setcolor(WHITE);
					cout << "Please enter your name ? : ";
					break;
				}
			}
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			console.clrscr();
			cout << "WELCOME TO CROSSWORDS PUZZLE" << endl;
			cout << setfill('=') << setw(COUT_SIZE) << '=' << endl;
			console.setcolor(LIGHTRED);
			cerr << "The name cannot be empty." << endl;
			cout << setfill('-') << setw(COUT_SIZE) << '-' << endl;
			cout << "Please enter your name ? : ";
			console.setcolor(WHITE);
		}
		if (validName) {
			p->setName(name);
		}
	}
	return 0;
}

void printHeader(Player *p, string puzzle = "", char op = 'a') {
	Console console;
	cout << "CROSSWORDS PUZZLE - GAME" << endl;
	cout << setfill('=') << setw(COUT_SIZE) << '=' << endl;
	cout << "Player: " << p->getName() << endl;
	if (puzzle != "") {
		cout << "Puzzle: " << puzzle;
	}

	if (op == 'y') {
		cout << "  |  " << "Clear Console: Yes";
	}

	if (op == 'n') {
		cout << "  |  " << "Clear Console: No";
	}
	cout << endl;

	cout << "Started at: "; p->printStartTime();
	cout << "  |  " << "Time: "; p->updateElapsedTime();
	p->printElapsedInSeconds(); cout << endl;
	if (gameStart) {
		p->printAlternativeClues();
		console.setcolor(BROWN);
		cout << "(At any time: p->print board; c->print clues)" << endl;
	}
	console.setcolor(LIGHTBLUE);
	cout << setfill('-') << setw(COUT_SIZE) << '-' << endl;
	console.setcolor(WHITE);
}

int showAvailableFiles(string location, vector<string> &v) {
	if (v.size() > 0) {
		v.clear();
	}

	int position = -1;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(&location[0])) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			string s = ent->d_name;
			//print only the files started with b
			if (s[0] == 'b') {
				cout << "  --> " << s << endl;
				v.push_back(s);
			}
		}
		closedir(dir);
		cout << endl;
	}

	if (v.size() > 0) {
		string temp = "";
		cout << "Type the name of the file: ";
		while (position == -1) {
			cin >> temp;
			if (cin.eof()) {
				cout << "Invalid file name, please choose another: ";
				cin.clear();
				continue;
			}
			if (!cin.fail()) {
				for (unsigned int i = 0; i < v.size(); i++) {
					if (!temp.compare(v[i])) {
						position = i;
						break;
					}
				}
				if (position == -1) {
					cout << "Invalid file name, please choose another: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			else {
				cout << endl;
				cout << "Something went wrong, please try again: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		return position;
	}
	else {
		return 99;
	}

}

bool abandonGame() {
	char userAnswer;
	cout << "Are you Sure? (y/n) ";
	cin.clear();
	cin >> userAnswer;
	userAnswer = toupper(userAnswer);

	while (cin.fail() || (userAnswer != 'Y' && userAnswer != 'N')) {
		cout << "Invalid option, choose yes(y) or no(n)." << endl << endl;
		cout << "Are you Sure? (y/n) ";
		if (cin.eof()) {
			cin.clear();
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin >> userAnswer;
		userAnswer = toupper(userAnswer);
	}
	if (userAnswer == 'Y') {
		cout << endl;
		cout << "Returning to main menu";
		cout << endl;
		cout << endl;
		return true;
	}
	else return false;

	return false;
}

int main()
{
	Player p1;
	Console console;
	string message = "";
strt:
	int startOption = welcome(&p1, message);
	message = "";
	vector<string> puzzles;
	int position = -1;
	//process option;
	switch (startOption) {
	case 0: break;
	case 1: cout << setfill('-') << setw(COUT_SIZE) << '-' << endl;
		cout << "Choose one of the available Score Boards" << endl;
		cout << endl;
		position = showAvailableFiles("scoreboards/", puzzles);
		if (position < 99) {
			FileManager scoreBoard("scoreboards/" + puzzles.at(position));
			console.clrscr();
			scoreBoard.printOnScreen();
			cout << endl;
			cout << endl;
			cout << "Press enter to continue: ";
			cin.get();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			console.clrscr();
			goto strt;
		}
		else {
			cout << endl;
			message = "There are no Score Boards yet. \nMaybe you can be the first one!";
			console.clrscr();
			goto strt;
		}
	case 2: return 0;
	}
	string aux;
	//Start the Game here
	p1.updateStartTime();
	console.clrscr();
	printHeader(&p1);
	cout << "Choose one of the available Puzzles" << endl;
	cout << endl;
	position = showAvailableFiles("puzzles/", puzzles);

	if (position == 99) {
		cout << endl;
		message = "There are no available Puzzles :(!";
		console.clrscr();
		goto strt;
	}

	GameBoard board("puzzles/" + puzzles.at(position), "Dictionary/Dictionary.txt");
	console.clrscr();
	printHeader(&p1, puzzles.at(position));
	cout << "Play in clear console mode (y/n)? ";
	char op = 'a';
	cin.clear();
	cin.ignore(1000, '\n');
	cin >> op;
	while (op != 'y' && op != 'n') {
		cout << "Not a valid option - (y/n): ";
		if (cin.eof())
			cin.clear();
		else {
			cin.clear();
			cin.ignore(1000, '\n');
		}
		cin >> op;
	}
	//Entering the loop
	gameStart = true;
	console.clrscr();
	printHeader(&p1, puzzles.at(position), op);
	board.print();
	board.printClues();
	string boardPos = "";
	string word = "";
	bool check = true;
	while (!board.isFull() || !board.isCorrect()) {

		if (board.isFull() && check) {
			// The board is full check answers
			cout << "Your answers:";
			board.checkAnswers();

			if (board.isCorrect()) break;
			check = false;
		}


		if (boardPos == "") {
			cout << "Position ( LCD / CTRL-Z or e = stop )  ? ";
			cin >> boardPos;
			//process exit
			if (boardPos == "e" || cin.eof()) {
				if (abandonGame()) {
					goto strt;
				}
				else goto bgn;
			}
			if (cin.fail()) {
				cin.clear();
				goto bgn;
			}


		}
		else {
			console.setcolor(LIGHTCYAN);
			cout << "  > " << "Position: " << boardPos << endl;
			console.setcolor(WHITE);
			cout << "Word (- / ? / + / ! / e) ? ";
			cin >> word;
			if (cin.fail()) {
				cout << endl << "Invalid input, try again" << endl;
				cin.clear();
				word = "";
				continue;
			}
			if (word == "e") {
				if (abandonGame()) {
					goto strt;
				}
				else goto bgn;
			}
		}

		//possibility to change location without typing the word

		//Hack: Save without filling the board
		if (boardPos == "&") {
			break;
		}

		//print board
		if (boardPos == "p" || word == "p") {
			if (boardPos == "p") goto bgn;
			if (word == "p") goto word;
		}

		//print clues
		if (boardPos == "c" || word == "c") {
			board.printClues();
			if (boardPos == "c") boardPos = "";
			if (word == "e") word = "";
			continue;
		}

		if (word == "!") {
			goto bgn;
		}

		cout << endl;
		switch (board.validateOption(boardPos, word)) {
		case 0:     if (boardPos != "" && word == "") {
			continue;
		}
					check = true;
					goto bgn;

		case 1:     cout << "That option has an unexpected size!" << endl;
			boardPos = "";
			continue;

		case 2:     cout << "You have chosen a line out of range!" << endl;
			boardPos = "";
			continue;

		case 3:     cout << "You have chosen a column out of range!" << endl;
			boardPos = "";
			continue;

		case 4:     cout << "You have chosen an invalid position on the board" << endl;
			boardPos = "";
			continue;

		case 5:     continue;

		case 6:     p1.incrementAltClues();
			continue;

		case 7:     cout << "The word typed doesnt fit on that location!" << endl;
			word = "";
			continue;

		case 8:     cout << "There is no word to remove there!" << endl;
			word = "";
			continue;

		case 9:     cout << "Your word doesnt match with one of the letters already on the board!" << endl;
			word = "";
			continue;
		}

	bgn:
		boardPos = "";
	word:
		word = "";
		if (op == 'y') {
			console.clrscr();
		}
		else {
			cout << setfill('*') << setw(COUT_SIZE) << '*' << endl;
		}
		printHeader(&p1, puzzles.at(position), op);
		board.print();
		board.printClues();
		cout << endl;
		cout << setfill('-') << setw(COUT_SIZE) << '-' << endl;
	}

	//save data
	string scrLocation = "scoreboards/";
	scrLocation += puzzles.at(position).substr(0, 4);
	scrLocation += "_p.txt";
	string playerInfo = "Player Name: " + p1.getName() + "; ";
	playerInfo += "Alternative Clues: ";
	playerInfo += to_string(p1.getAlternativeClues());
	playerInfo += "; ";
	playerInfo += "Time Spent: ";
	playerInfo += to_string(p1.getElapsedTime());
	playerInfo += "s";

	FileManager file;
	file.save(scrLocation, playerInfo);
	message = "Well Done! Score saved!";
	gameStart = false;
	console.clrscr();
	goto strt;

}

