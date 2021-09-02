#include "../include/stdafx.h"
#include "Chapters/Chapters.h"
#include "TourOfCpp/TourOfCpp.h"

using namespace std;

int main(int argc, char** argv)
{
	bool exit = false;

	cout << "Effective Modern C++" << endl << "====" << endl << endl;

	while (!exit)
	{
		bool runChapter = true;

		cout << "CHAPTERS MENU" << endl;
		cout << "____" << endl;
		cout << "1. Deducing Types" << endl;
		cout << "2. auto" << endl;
		cout << "3. Modern C++" << endl;
		cout << "4. Smart Pointers" << endl;
		cout << "5. Rvalues, Moves, Forwarding" << endl;
		cout << "6. Lambda" << endl;
		cout << "7. Concurrency API" << endl;
		cout << "8. Tweaks" << endl;
		cout << "12. User Defined Types" << endl;
		cout << "13. Modules" << endl;
		cout << "14. Classes" << endl;
		cout << "15. Move And Copy" << endl;
		cout << "16. Templates" << endl;
		cout << "17. Concepts" << endl;
		cout << "18. Standard Library" << endl;
		cout << "0. Exit" << endl;

		int selection;
		cin >> selection;

        BookChapter * chapter;

		switch (selection)
		{
		case 1:
			chapter = new C1_DeducingTypes();
			break;
		case 2:
			chapter = new C2_Auto();
			break;
		case 3:
			chapter = new C3_ModernCpp();
			break;
		// case 4:
		// 	chapter = new Chapter4();
		// 	break;
		// case 5:
		// 	chapter = new Chapter5();
		// 	break;
		// case 6:
		// 	chapter = new Chapter6();
		// 	break;
		// case 7:
		// 	chapter = new Chapter7();
		// 	break;
		// case 8:
		// 	chapter = new Chapter8();
		// 	break;
		case 12:
			chapter = new A2_UserDefinedTypes();
			break;
		case 13:
			chapter = new A3_Modularity();
			break;
		case 14:
			chapter = new A4_Classes();
			break;
		case 15:
			chapter = new A5_MoveAndCopy();
			break;
		case 16:
			chapter = new A6_Templates();
			break;
		case 17:
			chapter = new A7_Concepts();
			break;
		case 18:
			chapter = new A8_StandardLibrary();
			break;

        case 0:
            exit = true;
            break;
		default:
			cout << "Invalid Selection" << endl;
			runChapter = false;
		}

        if (!exit && runChapter)
        {
			cout << endl;
            chapter->RunChapter();
        }

	}

    return 0;

}