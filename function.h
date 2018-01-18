#ifndef function
#define function

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



void add();
void add_any_place(Shop *a);
void add_file(int amount, float price, long int bar_code, char *name);
void load();
void edit();

void show();
void save();
void end();

void menu_main();
void menu_show_m();
void menu_delate_m();
void menu_delate();
void menu_delate_one();
void menu_delate_section();
void menu_add();
void menu_add_m();
void menu_add_any();
void menu_save();
void menu_save_m();
void menu_show();
void menu_sort();
void menu_sort_m();


void order_number();
void order_change();

Shop *search_return();
Shop *search_bar_code(float data);
Shop *search_amount(float data);
Shop *search_price(float data);
Shop *search_number(float data);
Shop *search_add_order(float data);
Shop *search_char(char *data);
Shop *search_number_swap(float data);

void show_one_m();
void show_one();
void show_series(float data);
void google_charts();
void swap(Shop *temp);

void delete_one(Shop *temp);
void delete_section(Shop *a, Shop *b);
void delete_all();

void sort_add_order();
void sort_price();
void sort_string();
void sort_amount();
void sort_number();
#endif