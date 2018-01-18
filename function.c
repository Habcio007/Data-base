#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "function.h"
Shop *first = NULL;
Shop *last = NULL;


void add()
{
	Shop *new;
	new = (Shop *)malloc(sizeof(Shop));
	new->name = (char *)malloc(100 * sizeof(char));
	printf("Podaj liczbe: ");
	scanf("%d", &new->amount);
	printf("Podaj cene: ");
	scanf("%f", &new->price);
	printf("Podaj kod kreskowy: ");
	scanf("%d", &new->bar_code);
	printf("Podaj nazwe: ");
	scanf("%s", new->name);
	if (first == NULL)
	{
		new->add_order = 1;
		new->next = NULL;
		new->prev = NULL;
		first = new;
		last = new;
	}
	else
	{
		new->add_order = last->add_order + 1;
		new->next = NULL;
		new->prev = last;
		last->next = new;
		last = new;
	}
}
void add_any_place(Shop *a) {
	Shop *new;
	Shop *temp;
	if (a == NULL) {
		return;
	}
	temp = a->next;
	new = (Shop *)malloc(sizeof(Shop));
	new->name = (char *)malloc(100 * sizeof(char));
	printf("Podaj liczbe: ");
	scanf("%d", &new->amount);
	printf("Podaj cene: ");
	scanf("%f", &new->price);
	printf("Podaj kod kreskowy: ");
	scanf("%d", &new->bar_code);
	printf("Podaj nazwe: ");
	scanf("%s", new->name);
	int menu;
	printf("[1]-Wstaw przed\n");
	printf("[2]-Wstaw po\n");
	menu = getch();
	menu = menu - 48;
	switch (menu)
	{
	case 2:
		if (first == NULL)
		{
			new->add_order = 1;
			new->next = NULL;
			new->prev = NULL;
			first = new;
			last = new;
		}
		if (a->next == NULL) {
			new->add_order = last->add_order + 1;
			new->next = NULL;
			new->prev = last;
			last->next = new;
			last = new;
		}
		else
		{
			new->add_order = last->add_order + 1;

			a->next->prev = new;
			new->next = a->next;
			a->next = new;
			new->prev = a;
		}
		break;
	case 1:
		if (first == NULL)
		{
			new->add_order = 1;
			new->next = NULL;
			new->prev = NULL;
			first = new;
			last = new;
		}
		if (a->prev == NULL) {
			new->add_order = last->add_order + 1;
			new->prev = NULL;
			a->prev = new;
			new->next = a;
			first = new;
		}
		else
		{
			new->add_order = last->add_order + 1;

			a->prev->next = new;
			new->prev = a->prev;
			a->prev = new;
			new->next = a;
		}
		break;
	default:
		printf("Brak takiej opcji\n");
	}
}
void add_file(int amount, float price, long int bar_code, char *name) {
	Shop *new;
	new = (Shop *)malloc(sizeof(Shop));
	new->amount = amount;
	new->price = price;
	new->bar_code = bar_code;
	new->name = name;
	if (first == NULL)
	{
		new->add_order = 1;
		new->next = NULL;
		new->prev = NULL;
		first = new;
		last = new;
	}
	else
	{
		new->add_order = last->add_order + 1;
		new->next = NULL;
		new->prev = last;
		last->next = new;
		last = new;
	}
}
void load() {
	char adress[26];
	printf("Podaj nazwe pliku ");
	scanf("%20s", adress);
	strcat(adress, ".csv");
	FILE *file;
	int number, amount;
	float price;
	char znak;
	int i, n = 0;
	int temp;
	long int bar_code;
	char *name;
	name = (char *)malloc(200 * sizeof(char));
	file = fopen(adress, "r");
	if (file == NULL)
	{
		perror("Nie udalo sie otworzyc pliku ");
		return;
	}
	else {

		while (!feof(file))
		{
			znak = fgetc(file);
			if (znak == '\n')
			{
				n++;
			}
		}
		rewind(file);
		for (i = 0; i<n; i++)
		{
			name = (char *)malloc(200 * sizeof(char));
			fscanf(file, "%d;%d;%f;%d;%s\n", &temp, &amount, &price, &bar_code, name);
			add_file(amount, price, bar_code, name);
		}
		puts("Pomyslnie otwarto plik");
		return;
	}



}
void edit() {
	system("cls");
	Shop *test;
	int menu;
	int a;
	float b;

	printf("Jaka komorke chcesz edytowac?\n");
	test = search_return();
	if (test == NULL)
	{
		printf("Operacja niemozliwa?\n");
		return;
	}
	system("cls");
	printf("Co chcesz zmienic: \n");
	printf("[1]-ilosc\n");
	printf("[2]-cene\n");
	printf("[3]-nazwe\n");
	printf("[4]-powrot\n");

	menu = getch();
	menu = menu - 48;
	switch (menu)
	{
	case 1:
		printf("Podaj nowa ilosc\n");
		scanf("%d", &a);
		test->amount = a;
		break;
	case 2:
		printf("Podaj nowa cena\n");
		scanf("%f", &b);
		test->price = b;
		break;
	case 3:
		free(test->name);
		test->name = (char *)malloc(100 * sizeof(char));
		printf("Podaj nowa nazwe\n");
		scanf("%s", test->name);
		break;
	case 4:
		break;
	default:
		printf("Brak takiej opcji\n");
		break;
	}
	system("cls");
}


void show()
{
	Shop *temp;
	temp = first;
	if (temp == NULL) {
		printf("Brak danych\n");
		return;
	}
	temp = first;
	while (temp != NULL)
	{
		printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
		temp = temp->next;
	}
}
void save() {
	int i, j;
	Shop *temp;
	FILE *file;
	char name[26];
	printf("Podaj nazwe pliku ");
	scanf("%20s", name);
	strcat(name, ".csv");
	temp = first;
	if (temp == NULL) {
		return;
	}
	file = fopen(name, "w");
	while (temp != NULL)
	{
		fprintf(file, "%d;%d;%f;%d;%s\n", temp->number, temp->amount, temp->price, temp->bar_code, temp->name);
		temp = temp->next;
	}
	fclose(file);
}
void end() {
	Shop *temp;
	temp = first;
	if (temp == NULL) {
		return;
	}
	while (temp != NULL)
	{
		free(temp->name);
		temp = temp->next;
	}
	free(temp);
}

void menu_main() {
	printf("[1]-Dodaj dane\n");
	printf("[2]-Wyswietl dane\n");
	printf("[3]-Sortowanie\n");
	printf("[4]-Zamiana kolejnosci\n");
	printf("[5]-Usuwanie danych\n");
	printf("[6]-Zapis\n");
	printf("[7]-Edytuj rekord\n");
	printf("[8]-Zakoncz\n");
}
void menu_show_m() {
	system("cls");
	printf("[1]Wyswietl cala liste\n");
	printf("[2]Wyswietl jeden element\n");
	printf("[3]Wyszukaj najblizszy  element\n");
	printf("[4]Powrot\n");
	printf("\n");
}
void menu_delate_m() {
	system("cls");
	printf("[1]-Usun jeden element\n");
	printf("[2]-Usun przedzial\n");
	printf("[3]-Usun cala liste\n");
	printf("[4]Powrot\n");
	printf("\n");
}
void menu_delate() {
	int menu_1;
	menu_delate_m();
	menu_1 = getch();
	menu_1 = menu_1 - 48;
	switch (menu_1)
	{
	case 1:
		system("cls");
		menu_delate_one();
		break;
	case 2:
		system("cls");
		menu_delate_section();
		break;
	case 3:
		system("cls");
		delete_all();
		break;
	case 4:
		system("cls");
		return;
		break;
	default:
		system("cls");
		printf("Brak takie opcji \n");
		menu_add();
		break;
	}

}
void menu_delate_one() {
	Shop *a;
	a = search_return();
	if (a == NULL) {
		system("cls");
		printf("Nie udalo sie wykonac operacji\n");
		return;
	}
	else {
		delete_one(a);
	}
}
void menu_delate_section() {
	Shop *a, *b;
	printf("Wybierz poczatek przedzialu\n");
	a = search_return();
	system("cls");
	printf("Wybierz koniec przedzialu\n");
	b = search_return();
	system("cls");
	if ((a == NULL) || (b == NULL)) {
		printf("Nie udalo sie wykonac operacji\n");
		return;
	}
	else {
		delete_section(a, b);
	}
}
void menu_add() {
	int menu_1;
	system("cls");
	menu_add_m();
	menu_1 = getch();
	menu_1 = menu_1 - 48;
	switch (menu_1)
	{
	case 1:
		system("cls");
		add();
		break;
	case 2:
		system("cls");
		if (first == NULL)
		{
			add();
		}
		else {
			menu_add_any();
		}
		break;
	case 3:
		system("cls");
		load();
		break;
	case 4:
		system("cls");
		return;
		break;
	default:
		system("cls");
		printf("Brak takie opcji\n");
		menu_add();
		break;
	}
}
void menu_add_m() {
	system("cls");
	printf("[1]Dodaj element\n");
	printf("[2]Dodaj element w wybranym miejscu\n");
	printf("[3]Wczytaj plik\n");
	printf("[4]Powrot\n");
	printf("\n");
}
void menu_add_any() {
	Shop *a;
	a = search_return();
	if (a == NULL) {
		printf("Nie udalo sie wykonac operacji\n");
		return;
	}
	else {
		add_any_place(a);
	}
}
void menu_save() {
	int menu_1;
	menu_save_m();
	menu_1 = getch();
	menu_1 = menu_1 - 48;
	switch (menu_1)
	{
	case 1:
		save();
		system("cls");
		break;
	case 2:
		google_charts();
		system("cls");
		break;
	case 3:
		return;
		break;
	default:
		system("cls");
		printf("Brak takie opcji\n");
		break;
	}

}
void menu_save_m() {
	system("cls");
	printf("[1]-Zapis do pliku\n");
	printf("[2]-Google charts\n");
	printf("[3]-Powrot\n");
	printf("\n");
}
void menu_show() {
	menu_show_m();
	int menu_1;
	Shop *temp;
	menu_1 = getch();
	menu_1 = menu_1 - 48;
	switch (menu_1)
	{
	case 1:
		system("cls");
		show();
		break;
	case 2:
		system("cls");
		show_one();
		break;
	case 3:
		system("cls");
		temp = search_return();
		system("cls");
		if (temp == NULL) {
		}
		else {
			printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
		}
		break;
	case 4:
		return;
		break;
	default:
		system("cls");
		printf("Brak takie opcji \n");
		break;
	}

}
void menu_sort() {
	menu_sort_m();
	int menu_1;
	menu_1 = getch();
	menu_1 = menu_1 - 48;
	switch (menu_1)
	{
	case 1:
		system("cls");
		sort_add_order();
		break;
	case 2:
		system("cls");
		sort_amount();
		break;
	case 3:
		system("cls");
		sort_price();
		break;
	case 4:
		system("cls");
		sort_string();
		break;
	case 5:
		return;
		break;
	default:
		system("cls");
		printf("Brak takie opcji \n");
		break;
	}
}
void menu_sort_m() {
	system("cls");
	printf("[1]-Sortowanie wzgledem kolejnosci dodania\n");
	printf("[2]-Sortowanie wzgledem ilosc\n");
	printf("[3]-Sortowanie wzgledem ceny\n");
	printf("[4]-Sortowanie wzgledem nazwy\n");
	printf("[5]Powrot\n");
	printf("\n");
}


void order_number()
{
	Shop *temp;
	temp = first;
	int a = 1;
	if (temp == NULL) {
		return;
	}
	while (temp != NULL)
	{

		temp->number = a;
		temp = temp->next;
		a++;
	}
}
void order_change() {
	if (first == NULL)
	{
		printf("Brak danych\n");
		return;
	}
	else {
		float a;
		int i, j;
		a = last->number;
		for (j = 0; j <= last->number + (a - 4); j++) {
			for (i = 1; i <= last->number; i++)
			{
				swap(search_number_swap(a - j - i));
			}
		}
	}
}

Shop *search_return() {
	Shop *temp;
	int menu_1;
	printf("Wybierz rekord\n");
	printf("[1]-Liczby porzadkowej\n");
	printf("[2]-Kolejnosci dodania\n");
	printf("[3]-ceny\n");
	printf("[4]-ilosc\n");
	printf("[5]-kodu kreskowego\n");
	printf("[6]-nazwy\n");
	menu_1 = getch();
	menu_1 = menu_1 - 48;
	float a = 0;
	char nazwa[99];
	switch (menu_1)
	{
	case 1:
		printf("Podaj wzgledem indeksu glownego\n");
		scanf("%f", &a);
		temp = search_number(a);
		if (temp == NULL) {
			printf("Brak takiego rekordu\n");
			return NULL;
		}
		else {
			return temp;
		}
		break;
	case 2:
		printf("Podaj wzgledem kolejnosci wczytywania\n");
		scanf("%f", &a);
		temp = search_add_order(a);
		if (temp == NULL) {
			printf("Brak takiego rekordu\n");
			return NULL;
		}
		else {
			return temp;
		}
		break;
	case 3:
		printf("Podaj wzgledem ilosc\n");
		scanf("%f", &a);
		temp = search_amount(a);
		if (temp == NULL) {
			printf("Brak takiego rekordu\n");
			return NULL;
		}
		else {
			return temp;
		}
		break;
	case 4:
		printf("Podaj wzgledem ceny\n");
		scanf("%f", &a);
		temp = search_price(a);
		if (temp == NULL) {
			printf("Brak takiego rekordu\n");
			return NULL;
		}
		else {
			return temp;
		}
		break;
	case 5:
		printf("Podaj wzgledem kodu kreskowego\n");
		scanf("%f", &a);
		temp = search_bar_code(a);
		if (temp == NULL) {
			printf("Brak takiego rekordu\n");
			return NULL;
		}
		else {
			return temp;
		}
		break;
	case 6:
		printf("Podaj wzgledem nazwy prduktu\n");
		scanf("%s", nazwa);
		temp = search_char(nazwa);
		if (temp == NULL) {
			printf("Brak takiego rekordu\n");
			return NULL;
		}
		else {
			return temp;
		}
		break;
	case 7:
		return NULL;
		break;
	}


}
Shop *search_bar_code(float data)
{
	int a = 0;
	int menu;
	Shop *lasttemp = NULL;
	Shop *temp;
	temp = first;
	while (temp != NULL)
	{
		if ((data == temp->bar_code))
		{
			a = 1;
			printf("Znaleziono: ");
			printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
			printf("Wyswietlic nastepny wyszukany element t/n?\n");
			menu = getch();
			menu = menu - 115;
			lasttemp = temp;
			if (menu != 1)
			{
				return temp;
			}
		}
		temp = temp->next;
	}
	if (a == 0) {
		printf("Nie ma takiego elementu\n");
		return NULL;
	}
	else {
		temp = lasttemp;
		printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
		printf("To byl ostatni element\nZwrocic go? t/n\n");
		menu = getch();
		menu = menu - 115;
		if (menu == 1)
		{
			return temp;
		}
		return NULL;
	}

}
Shop *search_amount(float data)
{

	int a = 0;
	int menu;
	Shop *lasttemp = NULL;
	Shop *temp;
	temp = first;
	while (temp != NULL)
	{
		if ((data == temp->amount))
		{
			a = 1;
			printf("Znaleziono: ");
			printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
			printf("Wyswietlic nastepny wyszukany element t/n?\n");
			menu = getch();
			menu = menu - 115;
			lasttemp = temp;
			if (menu != 1)
			{
				return temp;
			}
		}
		temp = temp->next;
	}
	if (a == 0) {
		printf("Nie ma takiego elementu\n");
		return NULL;
	}
	else {
		temp = lasttemp;
		printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
		printf("To byl ostatni element\nZwrocic go? t/n\n");
		menu = getch();
		menu = menu - 115;
		if (menu == 1)
		{
			return temp;
		}
		return NULL;
	}
}
Shop *search_price(float data)
{
	int a = 0;
	int menu;
	Shop *lasttemp = NULL;
	Shop *temp;
	temp = first;
	while (temp != NULL)
	{
		if ((data == temp->price))
		{
			a = 1;
			printf("Znaleziono: ");
			printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
			printf("Wyswietlic nastepny wyszukany element t/n?\n");
			menu = getch();
			menu = menu - 115;
			lasttemp = temp;
			if (menu != 1)
			{
				return temp;
			}
		}
		temp = temp->next;
	}
	if (a == 0) {
		printf("Nie ma takiego elementu\n");
		return NULL;
	}
	else {
		temp = lasttemp;
		printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
		printf("To byl ostatni element\nZwrocic go? t/n\n");
		menu = getch();
		menu = menu - 115;
		if (menu == 1)
		{
			return temp;
		}
		return NULL;
	}
}
Shop *search_number(float data)
{
	int a = 0;
	int menu;
	Shop *lasttemp = NULL;
	Shop *temp;
	temp = first;
	while (temp != NULL)
	{
		if ((data == temp->number))
		{
			a = 1;
			printf("Znaleziono: ");
			printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
			printf("Wyswietlic nastepny wyszukany element t/n?\n");
			menu = getch();
			menu = menu - 115;
			lasttemp = temp;
			if (menu != 1)
			{
				return temp;
			}
		}
		temp = temp->next;
	}
	if (a == 0) {
		printf("Nie ma takiego elementu\n");
		return NULL;
	}
	else {
		temp = lasttemp;
		printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
		printf("To byl ostatni element\nZwrocic go? t/n\n");
		menu = getch();
		menu = menu - 115;
		if (menu == 1)
		{
			return temp;
		}
		return NULL;
	}
}
Shop *search_add_order(float data)
{
	int a = 0;
	int menu;
	Shop *lasttemp = NULL;
	Shop *temp;
	temp = first;
	while (temp != NULL)
	{
		if ((data == temp->add_order))
		{
			a = 1;
			printf("Znaleziono: ");
			printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
			printf("Wyswietlic nastepny wyszukany element t/n?\n");
			menu = getch();
			menu = menu - 115;
			lasttemp = temp;
			if (menu != 1)
			{
				return temp;
			}
		}
		temp = temp->next;
	}
	if (a == 0) {
		printf("Nie ma takiego elementu\n");
		return NULL;
	}
	else {
		temp = lasttemp;
		printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
		printf("To byl ostatni element\nZwrocic go? t/n\n");
		menu = getch();
		menu = menu - 115;
		if (menu == 1)
		{
			return temp;
		}
		return NULL;
	}
}
Shop *search_char(char *data)
{
	int a = 0;
	int menu;
	Shop *lasttemp = NULL;
	Shop *temp;
	temp = first;
	while (temp != NULL)
	{
		if (strcmp(temp->name, data) == 0)
		{
			a = 1;
			printf("Znaleziono: ");
			printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
			printf("Wyswietlic nastepny wyszukany element t/n?\n");
			menu = getch();
			menu = menu - 115;
			lasttemp = temp;
			if (menu != 1)
			{
				return temp;
			}
		}
		temp = temp->next;
	}
	if (a == 0) {
		printf("Nie ma takiego elementu\n");
		return NULL;
	}
	else {
		temp = lasttemp;
		printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
		printf("To byl ostatni element\nZwrocic go? t/n\n");
		menu = getch();
		menu = menu - 115;
		if (menu == 1)
		{
			return temp;
		}
		return NULL;
	}
}
Shop *search_number_swap(float data)
{
	int a = 0;
	int menu;
	Shop *temp;
	temp = first;
	while (temp != NULL)
	{
		if ((data == temp->number))
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void show_one_m() {
	system("cls");
	printf("[1]-przesun liste do przodu:\n");
	printf("[2]-przesun liste do tylu:\n");
	printf("[3]-powrot do menu glownego:\n");
}
void show_one() {
	Shop *temp;
	temp = first;
	if (temp == NULL) {
		printf("Lista jest pusta\n");
		return;
	}
	show_one_m();

	int opcja = 3;
	do
	{
		printf("Wpisz:\n");

		opcja = getch();
		opcja = opcja - 48;
		switch (opcja)
		{
		case 1:
			show_one_m();
			if (temp->next == NULL)
			{
				printf("Brak rekordu\n");
			}
			else {
				temp = temp->next;
				printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);

			}
			break;
		case 2:
			show_one_m();
			if (temp->prev == NULL)
			{
				printf("Brak rekordu\n");
			}
			else {
				temp = temp->prev;
				printf("%d;%d;%d;%f;%d;%s\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);

			}
			break;
		case 3:
			return;
		default:
			show_one_m();
			printf("Nieznana komenda\n");
			break;
		}
	} while (opcja != 4);
}
void show_series(float data)
{
	Shop *temp;
	temp = first;
	while (temp != NULL)
	{
		if ((data == temp->amount) || (data == temp->price) || (data == temp->number) || (data == temp->bar_code))
		{
			printf("%d;%d;%f;%d;%s;%d\n", temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name, temp->number);
		}
		temp = temp->next;
	}
	return NULL;
}
void google_charts()
{
	printf("Podaj nazwe pliku ");
	char name[26];
	scanf("%20s", name);
	strcat(name, ".html");
	Shop *temp;
	FILE *file;
	temp = first;
	file = fopen(name, "w");
	fprintf(file, "<html>\n<head>\n");
	fprintf(file, "<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>\n");
	fprintf(file, "<script type=\"text/javascript\">\n");
	fprintf(file, "google.charts.load('current', {'packages':['table']});\n");
	fprintf(file, "google.charts.setOnLoadCallback(Table);\n");
	fprintf(file, "function Table() {\n");
	fprintf(file, "var data = new google.visualization.DataTable();\n");
	fprintf(file, "data.addColumn('number', 'L.p.');\n");
	fprintf(file, "data.addColumn('number', 'Kolejnosc dodania');\n");
	fprintf(file, "data.addColumn('number', 'Ilosc');\n");
	fprintf(file, "data.addColumn('number', 'Cena');\n");
	fprintf(file, "data.addColumn('number', 'Kod kreskowy');\n");
	fprintf(file, "data.addColumn('string', 'nazwa');\n");
	fprintf(file, "data.addRows([\n");
	while (temp != NULL)
	{
		fprintf(file, "[%d,%d,%d,%f,%d,'%s'],\n", temp->number, temp->add_order, temp->amount, temp->price, temp->bar_code, temp->name);
		temp = temp->next;
	}
	fprintf(file, "]);\nvar table = new google.visualization.Table(document.getElementById('table_div'));\n");
	fprintf(file, "table.draw(data, table);}\n");
	fprintf(file, "</script>\n</head>\n<body>\n");
	fprintf(file, "<div id=\"table_div\"></div>\n");
	fprintf(file, "</body>\n</html>");
	fclose(file);
}
void swap(Shop *temp)
{
	if (temp == first)//jesli jest pierwszym elmentem
	{
		temp->next->next->prev = temp;//trzeci element juz wskazuje na pierwszy ktory stanie sie drugim
		temp->prev = temp->next;
		temp->next = temp->next->next;
		temp->prev->next = temp;
		temp->prev->prev = NULL;
		first = temp->prev;
	}
	else if (temp->next == last)//jesli jest ostatnim elementem
	{
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		temp->prev = temp->next;
		temp->prev->next = temp;
		temp->next = NULL;
		last = temp;

	}
	else//jesli jest gdzie ze srodka
	{
		temp->prev->next = temp->next;
		temp->next->next->prev = temp;
		temp->next->prev = temp->prev;
		temp->prev = temp->next;
		temp->next = temp->next->next;
		temp->prev->next = temp;

	}
}


void delete_one(Shop *temp)
{
	if (temp == NULL) {
		printf("Brak listy");
		return;
	}
	if ((temp == first) && (temp == last)) {
		free(temp->name);
		free(temp);
		first = NULL;
		last = NULL;
		return;
	}
	if (temp == first) {
		first = temp->next;
		first->prev = NULL;
	}
	else if (temp == last) {
		last = temp->prev;
		last->next = NULL;
	}
	else {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	free(temp);
}
void delete_section(Shop *a, Shop *b) {
	Shop *temp;
	Shop *temp2;
	if (((a == last) && (b == first)) || ((b == last) && (a == first))) {
		delete_all();
		return;
	}
	if ((a == first) && (b != last)) {
		temp = a;
		while (temp->next != b->next)
		{
			free(temp->name);
			temp = temp->next;
			free(temp->prev);
		}
		first = b->next;
		return;
	}
	if ((b == first) && (a != last)) {
		temp = a;
		while (temp->next != b->next)
		{
			free(temp->name);
			temp = temp->next;
			free(temp->prev);
		}
		first = b->next;
		return;
	}

	if ((b == last) && (a != first)) {
		temp = a;
		temp2 = a->prev;
		while (temp != last)
		{
			free(temp->name);
			temp = temp->next;
			free(temp->prev);
		}
		last = temp2;
		last->next = NULL;
		return;
	}
	if ((a == last) && (b != first)) {
		temp = a;
		temp2 = a->prev;
		while (temp != last)
		{
			free(temp->name);
			temp = temp->next;
			free(temp->prev);
		}
		last = temp2;
		last->next = NULL;
		return;
	}
	if ((a != last) && (b != first)) {
		if (a->number > b->number) {
			temp = b;
			temp2 = b->prev;
			while (temp->next != a->next)
			{
				free(temp->name);
				temp = temp->next;
				free(temp->prev);
			}
			temp2->next = a->next->next->prev;
			a->next->next->prev = temp2;

		}

		if (a->number < b->number) {
			temp = a;
			temp2 = a->prev;
			while (temp->next != b->next)
			{
				free(temp->name);
				temp = temp->next;
				free(temp->prev);
			}
			temp2->next = b->next->next->prev;
			b->next->next->prev = temp2;

		}

	}
}
void delete_all() {
	Shop *temp;
	temp = first;
	if (temp == NULL) {
		printf("Brak danych");
		return;
	}
	while (temp->next != NULL)
	{
		free(temp->name);
		temp = temp->next;
		free(temp->prev);

	}
	first = NULL;
	last = NULL;
	return;
}


void sort_add_order()
{
	Shop *temp;
	int i, a = 0;
	for (i = 0; i <= a; i++)
	{
		temp = first;
		a = 0;
		while (temp != last)
		{
			if (temp->add_order>temp->next->add_order)
			{
				swap(temp);
				a++;
			}
			else if (temp->add_order<
				temp->next->add_order)
			{
				temp = temp->next;
				a++;
			}
		}
	}
}
void sort_price()
{
	Shop *temp;
	int i, a = 0;
	for (i = 0; i <= a; i++)
	{
		temp = first;
		a = 0;
		while (temp != last)
		{
			if (temp->price>temp->next->price)
			{
				swap(temp);
				a++;
			}
			else
			{
				temp = temp->next;
				a++;
			}
		}
	}
}
void sort_string()
{
	Shop *temp;
	int ret;
	int i, a = 0;
	for (i = 0; i <= a; i++)
	{
		temp = first;
		a = 0;
		while (temp != last)
		{
			ret = strcmp(temp->name, temp->next->name);
			if (ret>0)
			{
				swap(temp);
				a++;
			}
			else if (ret <= 0)
			{
				temp = temp->next;
				a++;
			}
		}
	}
}
void sort_amount()
{
	Shop *temp;
	int i, a = 0;
	for (i = 0; i <= a; i++)
	{
		temp = first;
		a = 0;
		while (temp != last)
		{
			if (temp->amount>temp->next->amount)
			{
				swap(temp);
				a++;
			}
			else
			{
				temp = temp->next;
				a++;
			}
		}
	}
}
void sort_number()
{
	Shop *temp;
	int i, a = 0;
	for (i = 0; i <= a; i++)
	{
		temp = first;
		a = 0;
		while (temp != last)
		{
			if (temp->number>temp->next->number)
			{
				swap(temp);
				a++;
			}
			else
			{
				temp = temp->next;
				a++;
			}
		}
	}
}



