#include <iostream>
#include <conio.h>
#include <time.h>

#include "Refere.h"

void printInstructions()
{
	system("cls");

	std::cout << "Attacks (L) & (H) beat throws.\n";
	std::cout << "Light and Heavy attacks will react diffrently to certain attacks, \nsuch as parries.\n";
	std::cout << "Moves 1 & 2 will always be attacks.\n\n";
	std::cout << "Throws (T) beat defending.\n";
	std::cout << "Move 3 will always be an Throw.\n\n";
	std::cout << "Defending (B) & (D) beats Attacks.\n";
	std::cout << "Blocking will help you gain focus faster, Dodging will counter you're opponent.\n";
	std::cout << "Moves 4 & 5 will always be a defensive action.\n\n";

	std::cout << "When you're focus reaches 100 you will be able to use you're hyper move.\n";
	std::cout << "You can increse you're focus by sucsesfuly blocking and parying attacks.\n";
	std::cout << "You will also gain some focus by dealing and receving damage.\n\n";

	std::cout << "Rush, Lance & Fenrir use an attacking hyper.\n";
	std::cout << "Tarja & Dash have a hyper throws.\n";
	std::cout << "Wave has a defencive, counter hyper.\n";
	std::cout << "DSPD_017 activates a powered up state for a unique type of hyper.\n";

	std::cout << "\nPress any key to continue\n>";

	_getch();
}

void mainMenu(bool &exit, C_Refere* pRefere)
{
	bool repeat = false;

	// loops while the player dose not chose Exit on the main menu.
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

		std::cout << "Player " << (player + 1) << ", select you're fighter!\n";
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

		// initialize the random algorythem with the current time.
		srand((unsigned)time(0));

		pRefere = new C_Refere();

		// loops while the player has not selected exit from the main menu
		while (!exit)
		{
			// gives the player the main menu
			mainMenu(exit, pRefere);

			if (!exit)
			{
				system("cls");

				charicterSelect(pRefere);

				// has a match between the seected charicters
				pRefere->Start();
			}
		}

		if (pRefere != nullptr)
			delete pRefere;
	}

	// checks for meory leaks
	_CrtDumpMemoryLeaks();

	return 0;
}

