#include "Utilities.h"
#include <cstdlib>
#include <iostream>
#include "DataBase.h"
#include "Employee.h"
void run()
{
	const char* file = "Employees.txt";
	Database::DataBase<Employee::Employee> employees(file);
	int userInput = -1;
	bool flag = false;
	menu();
	while (flag == false)
	{
		std::cin >> userInput;
		if (std::cin.fail()) {
			std::cout << "Invalid Integer, try again: ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		else if (userInput == 1)
		{
			std::cout << "Name"
				<< std::setw(10) << "Address"
				<< std::setw(5) << "Salary"
				<< std::setw(10) << "Employee Number"
				<< std::setw(10) << "Position\n";
			printLine(90);
			std::cout << employees;
			system("pause");
			system("CLS");
			menu();
		}
		else if (userInput == 2)
		{
			std::cout << "Adding Employee\n";
			Employee::Employee emp;
			if (std::cin >> emp)
			{
				// Input operation was successful
				std::cout << "\nEmployee details entered successfully:\n\n";
				// You can now use the emp object as needed
			}
			else
			{
				// Input operation failed
				std::cout << "\nError: Invalid input for employee details.\n\n";
				// Handle the error or take appropriate action
			}
			employees += emp;
			system("pause");
			system("CLS");
			menu();
		}
		else if (userInput == 3)
		{
			int userSelect = -1;
			std::cout << "Choose Employee to remove | 0 To Return to menu\n";
			//Displays list of all employees
			std::cout << employees;
			std::cout << "> ";
			//Recieves user input
			std::cin >> userSelect;
			if (userSelect > 0)
			{
				//If employee is found, it will be removed
				if (employees.pop(userSelect - 1))
				{
					std::cout << "Employee Removed Successfully\n";
				}
				else
				{
					std::cout << "Error occured removing employee\n";
				}
			}
			system("pause");
			system("CLS");
			menu();
		}
		else if (userInput == 4)
		{
			std::cout << "Search For Employee\n";
			unsigned employee_number;
			bool selection = false;
			Employee::Employee emp;
			while (!selection)
			{
				std::cout << "Enter Employee Number :> ";
				std::cin >> employee_number;
				if (employee_number <= 0)
				{
					std::cout << "Invalid Employee Number!\n";
				}
				else
				{
					try
					{
						const Employee::Employee& foundEmployee = employees.findEmployeeByNumber(employee_number);
						// Employee found, you can use it
						std::cout << "Employee found\n" << foundEmployee << '\n';
					}
					catch (const std::out_of_range& e)
					{
						// Employee not found, handle accordingly
						std::cout << "Employee not found\n";
					}
				}
				selection = true;
			}
			system("pause");
			system("CLS");
			menu();
		}
		else if (userInput == 0)
		{
			bool flag2 = false;
			std::string input;

			std::cout << "Do you want to save your changes? Y/N :> ";

			while (!flag2)
			{
				std::cin >> input;

				if (input == "Y" || input == "y")
				{
					std::cout << ">>>> Saving Data.............................................................\n";
					std::cout << "Saving data in " << file << "\n";
					employees.save("Employees.txt");
					flag2 = true;
				}
				else if (input == "N" || input == "n")
				{
					std::cout << "Changes were not saved!\n";
					flag2 = true;
				}
				else
				{
					system("CLS");
					std::cout << "Invalid Selection\n";
					std::cout << "Do you want to save your changes? Y/N :> ";
				}
			}
			flag = true;
		}
		else if (userInput < 0 || userInput > 4)
		{
			std::cout << "[0<=value<=4], retry: > ";
		}

	}
	std::cout << "Goodbye!\n";
}

void menu()
{
	std::cout << "Employee Management System\n";
	std::cout << "1- List Employees\n";
	std::cout << "2- Add Employee\n";
	std::cout << "3- Remove Employee\n";
	std::cout << "4- Search Employee\n";
	std::cout << "0- exit program\n";
	std::cout << "> ";
}

void printLine(int width)
{
	for (int i = 0; i < width; ++i)
	{
		std::cout << "-";
	}
	std::cout << "\n";
}