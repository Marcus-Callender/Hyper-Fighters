#include <iostream>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <fstream>

#include "Refere.h"

void printInstructions()
{
	system("cls");

	// loads the file
	std::ifstream file("Instructions.txt");
	std::string line;

	// this makes sure the file was opened correctly
	if (file.is_open())
	{
		// while we haven't reached the end of the file print the lines we read to the screen
		while (std::getline(file, line))
		{
			std::cout << line << "\n";
		}

		// close the file
		file.close();
	}

	_getch();
}

void mainMenu(bool &exit, C_Refere* pRefere)
{
	bool repeat = false;

	do
	{
		repeat = false;

		system("cls");
		std::cout << "Welcome to HYPER FIGHTERS!!!\n\n";
		std::cout << "What would you like to do?\n";
		std::cout << "1: Play player vs player\n";
		std::cout << "2: Play player vs CPU\n";
		std::cout << "3: Watch CPU vs CPU\n";
		std::cout << "4: Read instructions\n";
		std::cout << "5: Exit\n";
		std::cout << ">";

		int choice = _getch();

		choice -= 48;

		switch (choice)
		{
		case 1:
			pRefere->InitializeControlers(TYPE_PLAYER, TYPE_PLAYER);
			break;
		case 2:
			pRefere->InitializeControlers(TYPE_PLAYER, TYPE_AI);
			break;
		case 3:
			pRefere->InitializeControlers(TYPE_AI, TYPE_AI);
			break;
		case 4:
			printInstructions();
			repeat = true;
			break;
		case 5:
			exit = true;
			break;
		default:
			std::cout << "\n\nPlease enter a valid option.\n";
			_getch();
			repeat = true;
			break;
		}
	} while (repeat);
}

void charicterSelect(C_Refere* pRefere)
{
	for (int player = 0; player < 2; player++)
	{
		int choice = 0;

		system("cls");

		std::cout << "Player " << (player + 1) << ", select you're fighter!\n\n";
		std::cout << "1: Hothead avenger,   Rush\n";
		std::cout << "2: Charming criminal, Lance\n";
		std::cout << "3: Natural killer,    Wave\n";
		std::cout << "4: Lost robot,        DSPD_0017\n";
		std::cout << "5: Savage destroyer,  Tarja\n";
		std::cout << "6: Forgotten hero,    Fenrir\n";
		std::cout << "7: Wannabe hero,      Dash\n";
		std::cout << "0: Random select\n";
		std::cout << ">";

		choice = _getch();

		choice -= 48;

		if (choice > 7 || choice < 1)
		{
			choice = (rand() % 7) + 1;
		}

		switch (choice)
		{
		case 1:
			pRefere->InitializeCharicter(player, TYPE_RUSH);
			break;
		case 2:
			pRefere->InitializeCharicter(player, TYPE_LANCE);
			break;
		case 3:
			pRefere->InitializeCharicter(player, TYPE_WAVE);
			break;
		case 4:
			pRefere->InitializeCharicter(player, TYPE_DSPD_017);
			break;
		case 5:
			pRefere->InitializeCharicter(player, TYPE_TARJA);
			break;
		case 6:
			pRefere->InitializeCharicter(player, TYPE_FENRIR);
			break;
		case 7:
			pRefere->InitializeCharicter(player, TYPE_DASH);
			break;
		}

	}
}

int main()
{
	{
		C_Refere* pRefere;

		bool exit = false;

		srand((unsigned)time(0));

		pRefere = new C_Refere();

		while (!exit)
		{
			mainMenu(exit, pRefere);

			if (!exit)
			{
				system("cls");

				charicterSelect(pRefere);

				pRefere->Start();
			}
		}

		if (pRefere != nullptr)
		{
			delete pRefere;
			pRefere = nullptr;
		}
	}

	_CrtDumpMemoryLeaks();

	std::cout << "\n\n";

	return 0;
}

