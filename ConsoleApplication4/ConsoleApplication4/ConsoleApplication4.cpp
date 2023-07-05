#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <Windows.h>

using namespace std;

// getting a string choice of car 
string car_choice(int car_choice) {
	switch (car_choice) {
	case 1:
		return "ordinary car ";
	case 2:
		return "children_car";
	case 3:
		return "truck";
	}
}

// cheking driver's information
bool driver_check(int age, int exp, int car) { //(опираясь на средние допустимые возраст и стаж, я решила )
	if (car == 1) {
		return age > 19 && exp > 1;
	}
	else {
		return age > 21 && exp > 2;
	}
}

class car {
protected:
	int type;
	string brand;
	int quantity;
	int minute_price;
	int power;
	static int car_count;
public:
	car(int type, string brand, int quantity, int price, int power) {
		this->type = type;
		this->brand = brand;
		this->quantity = quantity;
		this->minute_price = price;
		this->power = power;
		car_count++;
	} int CountCars() {
		return car_count;
	}
	double GetPrice() {
		return this->minute_price;
	} int GetType() {
		return this->type;
	}
	void SetPrice(int new_price) {
		this->minute_price = new_price;
	}
	virtual void show() {
		std::cout << setw(9) << this->brand << setw(5) << this->quantity << setw(5) << this->minute_price << setw(5) << this->power << endl;
	}

};

class ordinary_car : public car {
	int electric;
public:
	ordinary_car(int type, string brand, int quantity, int pr, int power, int electric) : car(type, brand, quantity, pr, power) {
		this->electric = electric;
	}
	void show() {
		std::cout << setw(15) << this->brand << setw(5) << this->quantity << setw(5) << this->minute_price << setw(5) << this->power << endl;
	}
};

class children_car : public car {
	int child_place;
public:
	children_car(int type, string brand, int quantity, int pr, int power, int child_place) : car(type, brand, quantity, pr, power) {
		this->child_place = child_place;
	}
	void show() {
		std::cout << setw(15) << this->brand << setw(5) << this->quantity << setw(5) << this->minute_price << setw(5) << this->power << endl;
	}
};

class truck : public car {
	int capacity;
public:
	truck(int type, string brand, int quantity, int pr, int power, int capacity) : car(type, brand, quantity, pr, power) {
		this->capacity = capacity;
	}
	void show() {
		std::cout << setw(15) << this->brand << setw(5) << this->quantity << setw(5) << this->minute_price << setw(5) << this->power << endl;
	}
};

class driver {
	string name;
	string surname;
	int age;
	int experience;
	int car;
public:
	driver(string name, string surname, int age, int exp, int tran) {
		this->name = name;
		this->surname = surname;
		this->age = age;
		this->experience = exp;
		this->car = tran;
	} void show() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int color = driver_check(age, experience, car) ? 2 : 4;
		SetConsoleTextAttribute(hConsole, color);
		std::cout << setw(20) << name + " " + surname;
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << setw(10) << age << setw(5) << experience << setw(15) << car_choice(car) << endl;
	}
};

// getting present time (seconds from 1980 year)
//int timet() {
//	std::time_t t = std::time(0);
//	std::tm* now = std::localtime(&t);
//	int seconds = time();
//	return seconds;
//}

// initial filling lists of cars
void car_filling(vector<car>& cars) {
	ordinary_car car1(1, "Audi", 12, 10, 220, 0);
	ordinary_car car2(1, "Mercedens", 3, 10, 190, 0);
	ordinary_car car3(1, "Tesla", 3, 15, 200, 1);
	children_car car4(2, "BMW", 3, 8, 180, 2);
	children_car car5(2, "Nissan", 10, 10, 190, 1);
	children_car car6(2, "Skoda", 2, 9, 180, 2);
	truck car7(3, "Kamaz", 2, 15, 240, 20);
	truck car8(3, "MAZ", 10, 16, 260, 23);
	truck car9(3, "Ford", 1, 14, 220, 13);

	cars.push_back(car1);
	cars.push_back(car2);
	cars.push_back(car3);
	cars.push_back(car4);
	cars.push_back(car5);
	cars.push_back(car6);
	cars.push_back(car7);
	cars.push_back(car8);
	cars.push_back(car9);
}

// outputing list of available actions
void list_of_actions() {
	std::cout << "1. Add new car\n"
		<< "2. Registration + rent a car\n"
		<< "3. Price sorted list of available cars\n"
		<< "4. List of drivers\n"
		<< "5. Change car's price\n"
		<< "6. Information about carsharing system\n"
		<< "0. Exit\n";

	std::cout << "Enter number of action: ";
}

// comparing objects by price for sorting
bool compaire(car& a, car& b) {
	return a.GetPrice() < b.GetPrice();
}

// outputing the list of needed cars
void assortiment(vector<car>& cars, int car_choice=0) {
	int ind = 1;
	for (int i = 0; i < cars.size(); i++) {
		if (car_choice == 0 || cars[i].GetType() == car_choice) {
			cout << setw(2) << ind++ << ". ";
			cars[i].show();
		}
	} cout << endl;
}

// outputting list of available car types
void car_types() {
	std::cout << "1. Ordinary car\n2. Children car\n3. Truck\n";
}

int car::car_count=0;

void menu() {

	vector <car> cars;
	car_filling(cars);

	int act;

	string brand;
	int quantity;
	int price;
	int power;
	int dop_char;

	string name;
	string surname;
	int age;
	int experience;
	int car_choice;
	time_t pick_time;


	do {
		list_of_actions();
		std::cin >> act;
		switch (act) {
		case 1:
			car_types();
			std::cout << "Enter type of car: ";
			std::cin >> car_choice;
			std::cout << "Enter brand of the car: ";
			std::cin >> brand;
			std::cout << "Enter quantity: ";
			std::cin >> quantity;
			std::cout << "Enter price per minute: ";
			std::cin >> price;
			std::cout << "Enter power: ";
			std::cin >> power;
			switch (car_choice) {
			case 1:
				std::cout << "Enter 1 if car is electric, else - 0: ";
				std::cin >> dop_char;
				cars.push_back(ordinary_car(car_choice, brand, quantity, price, power, dop_char));
				break;
			case 2:
				std::cout << "Enter number of children places: ";
				std::cin >> dop_char;
				cars.push_back(children_car(car_choice, brand, quantity, price, power, dop_char));
				break;
			case 3:
				std::cout << "Enter capacity of the truck: ";
				std::cin >> dop_char;
				cars.push_back(truck(car_choice, brand, quantity, price, power, dop_char));
				break;
			}
			cout << endl << endl;
			break;
		case 2:
			break;
		case 3:
			sort(cars.begin(), cars.end(), compaire);
			assortiment(cars);
			break;
		case 4:
			break;
		case 5:
			int new_price;
			assortiment(cars);
			cout << "Enter id of needed car: ";
			cin >> car_choice;
			cout << "Enter new price: ";
			cin >> new_price;
			cars[car_choice - 1].SetPrice(new_price);
			assortiment(cars);
			break;
		}
	} while (act != 0);
}


int main() {

	time_t  timev;
	cout << time(&timev)-1 << "  " <<  time(&timev) << endl;

	menu();
	return 0;
}
