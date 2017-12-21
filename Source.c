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
void show_one();
void search_one(char *);
void save();
void load();
void end();
Shop *first = NULL;
Shop *last = NULL;

void show_one() {
		Shop *temp;
		temp = first;
		int a=1;
		if (temp == NULL) {
			printf("Lista jest pusta");
			return;
		}
		while (temp != NULL)
		{
			scanf("%d", &a);
			if(a==1)
			{ 
				if (temp->next == NULL)
				{
					return;
				}
				else {
					temp = temp->next;
				}
			}
			if (a == 2)
			{
				if (temp->prev == NULL)
				{
					return;
				}
				else {
					temp = temp->prev;
				}
			}
			if (a == "end")
			{
				return NULL;
			}
			printf("%d;%d;%f;%d;%s\n", temp->number, temp->amount, temp->price, temp->bar_code, temp->name);
		}
	}
int main()
{
	load();
	add();
	show_one();
	system("pause");
	/*
	int opcja = 3;
	do
	{
		printf("Wpisz: ");
		scanf("%d", &opcja);
		switch (opcja)
		{
		case 1:
			add();
			opcja = 4;
			break;
		case 2:
			save();
			opcja = 4;
			break;
		case 3:
			return 0;
			break;
		case 5:
			search_one(2);
			opcja = 4;
			break;
		default:
			opcja = 4;
			break;
		}
	} while (opcja == 4);*/
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
void search_one(char *a)
{
	Shop *temp;
	temp = first;
	if (temp == NULL) {
		printf("sdadada");
		return;
	}
	while (temp != NULL)
	{
		if (*temp->name == a)
		{
			printf("%d, %s\n", temp->number, temp->name);
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
	long int bar_code;
	char *name;
	name = (char *)malloc(100 * sizeof(char));
	file = fopen("out.csv", "r");
	if (file == NULL)
	{
		perror("Nie udalo sie otworzyc pliku ");
		return;
	}
	else {
		int i;
		for(i=0;i<2;i++)
		{
			fscanf(file,"%d;%f;%d;%s\n", &amount, &price, &bar_code, name);
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


