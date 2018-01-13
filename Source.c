#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Shop
{
	int add_order;
	int number;
	int amount;
	float price;
	long int bar_code;
	char *name;
	struct Shop *next;
	struct Shop *prev;
}Shop;


void add_any_place(Shop *a);
void add();
void add_file( int, float, long int, char *);
void show();
void save();
void load();
void order_number();
void end();
void delete_one(Shop *temp);
void delete_all();
void show_one();
void swap(Shop *temp);
void show_series(float data);
void order_change();

Shop *show_elem(float);
Shop *show_char(char *data);
Shop *first = NULL;
Shop *last = NULL;

void menu_main();
void delete_things(Shop *, Shop *);

int main()
{
	show();
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
	order_number();
	show();
	delete_all();
	printf("\n");
	show();
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
	if(a==NULL){
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
	switch (2)
	{
	case 1:
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
	case 2:
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
		new->add_order =  1;
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
void show()
{
	Shop *temp;
	temp = first;
	if (temp == NULL) {
		printf("Brak danych");
		return;
	}
	temp = first;
	while (temp != NULL)
	{
		printf("%d;%d;%d;%f;%d;%s\n",temp->number, temp->add_order,temp->amount, temp->price, temp->bar_code, temp->name);
		temp = temp->next;
	}
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
	
		temp->number=a;
		temp = temp->next;
		a++;
	}
}
void order_change() {
	float a;
	int i, j;
	a = last->number;
	for (j = 0; j <= last->number + (a - 4); j++) {
		for (i = 1; i <= last->number; i++)
		{
			swap(show_elem(a - j - i));
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
}

Shop *show_elem(float data)
{
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
Shop *show_char(char *data)
{
	Shop *temp;
	temp = first;

	while (temp != NULL)
	{
		if (strcmp(temp->name, data) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
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
void delete_things(Shop *a, Shop *b) {
	if (a->number < b->number) 
	{
			b->next->prev = a->prev;
			a->prev->next = b->next;
	}	
	if (a->number > b->number) {

		a->next->prev = b->prev;
		b->prev->next = a->next;
	}
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
	else if(temp->next==last)//jesli jest ostatnim elementem
    {
        temp->next->prev=temp->prev;
        temp->prev->next =temp->next;
        temp->prev =temp->next;
        temp->prev->next =temp;
        temp->next =NULL;
		last =temp;

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
