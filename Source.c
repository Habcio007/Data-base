#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "function.h"



int main()


{
	int opcja;
	do
	{
		order_number();
		menu_main();
		printf("Wpisz: ");
		opcja = getch();
		opcja = opcja - 48;
		printf("\n");
		switch (opcja)
		{
		case 1:
			system("cls");
			menu_add();
			break;
		case 2:
			system("cls");
			menu_show();
			break;
		case 3:
			system("cls");
			menu_sort();
			break;
		case 4:
			system("cls");
			order_change();
			break;
		case 5:
			system("cls");
			menu_delate();
			break;
		case 6:
			system("cls");
			menu_save();
			break;
		case 7:
			edit();
			break;
		case 8:
			return 0;
			break;
		default:
			system("cls");
			printf("\nBrak takiej opcji\n\n");
			break;
		}
	} while (opcja);
}
