#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Employee.h"


namespace Employee
{

	Employee::Employee(const Name& name, const Address& address, const double salary, const std::string& position, const unsigned employee_number)
	{
		this->name = name;
		this->address = address;
		this->salary = salary;
		this->position = position;
		this->employee_number = employee_number;
	}

	Employee::Employee(const Employee& copy)
	{
		this->name = copy.name;
		this->address = copy.address;
		this->salary = copy.salary;
		this->position = copy.position;
		this->employee_number = copy.employee_number;
	}

	bool Employee::load(std::ifstream& f)
	{
		if (!name.load(f) || !address.load(f) || !(f >> salary >> employee_number))
		{
			if (!f.eof()) {
				// If it's not EOF, then there was an actual read error
				std::cerr << "Error: Failed to read employee data from the file.\n";
			}
			return false;
		}
		std::getline(f >> std::ws, position);

		return true;
	}

	bool Employee::save(std::ofstream& f) const
	{
		if (!f.is_open() || !f.good())
			return false;  // Check if the file is open and in a good state

		// Save the individual components of the Employee
		name.save(f);
		address.save(f);
		f << salary << ' ' << ' ' << employee_number << ' ' << position;
		return f.good();
	}

	void Employee::display(std::ostream& os) const
	{
		os << name
			<< std::setw(10) << address
			<< std::setw(5) << salary
			<< std::setw(10) << employee_number
			<< std::setw(10) << position
			<< "\n";
	}

	void Employee::inputEmployee(std::istream& is)
	{
		bool error = false;
		is >> name;
		is >> address;
		while (!error)
		{
			std::cout << "Enter Employee's salary: ";
			is >> salary;
			// Checks if salary is valid
			if (salary < 0)
			{
				is.clear();
				std::cout << "Invalid Salary\n";
			}
			else
			{
				error = true;
			}
		}
		error = false;
		while (!error)
		{
			std::cout << "Enter Employee's position: ";
			//Read position until newline character
			std::getline(is >> std::ws, position);
			//Checks if istream failed or position is valid
			if (is.fail() || position[0] == '\n')
			{
				is.clear();
				std::cout << "Invalid Position\n";
			}
			else
			{
				error = true;
			}
		}
		error = false;
		while (!error)
		{
			std::cout << "Enter Employee number: ";
			is >> employee_number;
			//Checks if employee number is between 100 000 and 200 000
			if (employee_number < 100000 && employee_number > 200000)
			{
				is.clear();
				std::cout << "Invalid Employee Number\n";
			}
			else
			{
				error = true;
			}
		}
	}

	unsigned Employee::getEmployeeNumber() const
	{
		return employee_number;
	}

	std::ostream& operator<<(std::ostream& os, const Employee& emp)
	{
		emp.display(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, Employee& emp)
	{
		emp.inputEmployee(is);
		return is;
	}
}
