#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Shop
{
	int number;
	int amount;
	float price;
	long int bar_code;
	char *name;
	struct Shop *next;
	struct Shop *prev;
}Shop;

void add();
void add_file( int, float, long int, char *);
void show();
void save();
void load();
void end();
void delete_one(Shop *temp);
void show_one();

Shop *show_elem(char *);
Shop *first = NULL;
Shop *last = NULL;

void menu_main();

int main()
{
	int opcja = 3;
	int a;
	/*
	do
	{
		menu_main();
		printf("Wpisz: ");
		scanf("%d", &opcja);
		switch (opcja)
		{
		case 1:
			add();
			break;
		case 2:
			load();
			break;
		case 3:
			save();
			break;
		case 4:
			show_one();
			break;
		case 5:
			show();
			break;
		case 6:
			scanf("%d", &a);
			printf("%d;%d;%f;%d;%s\n", show_elem(a)->number, show_elem(a)->amount, show_elem(a)->price, show_elem(a)->bar_code, show_elem(a)->name);
			break;
		case 7:
			scanf("%d", &a);
			delete_one(show_elem(a));
			break;
		case 9:
			end();
			return 0;
			break;
		default:
			break;
		}
	} while (opcja);
	*/
	load();
	show();

	scanf("%f", &a);
	printf("%d;%d;%f;%d;%s\n", show_elem(a)->number, show_elem(a)->amount, show_elem(a)->price, show_elem(a)->bar_code, show_elem(a)->name);
	system("pause");
	return 0;

}
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
		new->number = 1;
		new->next = NULL;
		new->prev = NULL;
		first = new;
		last = new;
	}
	else
	{
		new->number = last->number + 1;
		new->next = NULL;
		new->prev = last;
		last->next = new;
		last = new;
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
		new->number =  1;
		new->next = NULL;
		new->prev = NULL;
		first = new;
		last = new;
	}
	else
	{
		new->number = last->number + 1;
		new->next = NULL;
		new->prev = last;
		last->next = new;
		last = new;
	}
}
void show()
{
	Shop *temp;
	temp = first;
	if (temp == NULL) {
		return;
	}
	while (temp != NULL)
	{
		printf("%d;%d;%f;%d;%s\n",temp->number,temp->amount, temp->price, temp->bar_code, temp->name);
		temp = temp->next;
	}
}
Shop *show_elem(float data)
{
	Shop *temp;
	temp = first;
	while (temp != NULL)
	{
		if ((data==temp->amount)|| (data == temp->price)|| (data == temp->number)|| (data == temp->bar_code))
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}
void save() {
	int i, j;
	Shop *temp;
	FILE *file;

	temp = first;
	if (temp == NULL) {
		return;
	}
	file = fopen("out.csv", "w");
	while (temp != NULL)
	{
	fprintf(file,"%d;%d;%f;%d;%s\n", temp->number,temp->amount, temp->price, temp->bar_code, temp->name);
	temp = temp->next;
	}
	fclose(file);
}
void load() {
	FILE *file;
	int number, amount;
	float price;
	char znak;
	int i, n = 0;
	int temp;
	long int bar_code;
	char *name;
	name = (char *)malloc(200 * sizeof(char));
	file = fopen("out.csv", "r");
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
		for(i=0;i<n;i++)
		{
			name = (char *)malloc(200 * sizeof(char));
			fscanf(file, "%d;%d;%f;%d;%s\n", &temp, &amount, &price, &bar_code, name);
			add_file( amount, price, bar_code, name);
		}
		puts("Pomyslnie otwarto plik");
		return;
	}


		
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
	printf("1-Dodaj rekord\n");
	printf("2-Wczytaj baze danych z pliku csv\n");
	printf("3-Zapisz baze danych dp pliku csv\n");
	printf("4-Wyswietl pierwszy\n");
	printf("5-Wyswietl wszystkie\n");
	printf("6-Wyszukaj\n");
	printf("7-Zakoncz\n");
}
void delete_one(Shop *temp)
{
	if (temp == NULL) {
		printf("Brak listy");
		return;
	}
	if ((temp == first) && (temp == last)) {
		free(temp);
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
void show_one() {
	Shop *temp;
	temp = first;
	int a = 1;
	if (temp == NULL) {
		printf("Lista jest pusta");
		return;
	}
	int opcja = 3;
	do
	{
		printf("Wpisz: ");
		scanf("%d", &opcja);
		switch (opcja)
		{
		case 1:
			if (temp->next == NULL)
			{
				printf("Brak rekordu");
			}
			else {
				temp = temp->next;
				printf("%d;%d;%f;%d;%s\n", temp->number, temp->amount, temp->price, temp->bar_code, temp->name);

			}
			break;
		case 2:
			if (temp->prev == NULL)
			{
				printf("Brak rekordu");
			}
			else {
				temp = temp->prev;
				printf("%d;%d;%f;%d;%s\n", temp->number, temp->amount, temp->price, temp->bar_code, temp->name);

			}
			break;
		case 3:
			return;
		default:
			break;
		}
	} while (opcja != 4);
}
void sort(Shop *first)
{
	Shop *newfirst = NULL;
	Shop *max, *popmax, *tmp;
	while (first)
	{
		max = first;
		popmax = NULL;
		tmp = first;
		while (tmp->next)
		{
			if (tmp->next->price > max->price)
			{
				popmax = tmp;
				max = tmp->next;
			}
			tmp = tmp->next;
		}
		if (popmax) popmax->next = max->next;
		else first = max->next;
		max->next = newfirst;
		newfirst = max;
	}
	first = newfirst;
}