#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>
#include "Employee.h"

namespace Database
{
	template <typename T>
	class DataBase
	{
	private:
		std::vector<T> database;
	public:
		DataBase() { }
		DataBase(const char* fn)
		{
			// Open the file with the given filename
			std::ifstream file(fn);
			// Check if the file opening was successful
			if (!file)
				// If not, throw an exception with an error message
				throw std::string("*** Failed to open file ") + std::string(fn) + std::string(" ***");
			// Loop to read data from the file until the end of the file is reached
			while (file)
			{
				// Create an instance of type T (e.g., Employee) to hold the data
				T e;
				// Try to load data from the file into the instance of type T
				try
				{
					// If loading is successful, add the instance to the vector
					if (e.load(file))
						database.push_back(T(e));
				}
				// Catch any exceptions that might occur during the loading process
				catch (...)
				{
					// If an exception is caught, exit the loop
					break;
				}
			}
		}
		void operator+=(const T& address)
		{
			database.emplace_back(address);
		}

		void display(std::ostream& os) const
		{
			os << std::fixed << std::setprecision(2);

			int employeeNumber = 1;  // Initialize the employee number

			for (const auto& e : database)
			{
				os << "[" << employeeNumber << "] ";  // Display the employee number
				os << e;
				employeeNumber++;  // Increment the employee number for the next employee
			}
		}
		void save(const char* fn) const
		{
			std::ofstream file(fn);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(fn) + std::string(" ***");
			for (const auto& e : database)
			{
				e.save(file);
				file << '\n';
			}
		}

		bool pop(int selection)
		{
			auto it = database.cbegin() + selection;
			if (it != database.cend())
			{
				database.erase(it);
				return true; // Successfully removed the element
			}
			return false; // Element not found, removal failed
		}

		const T& findEmployeeByNumber(unsigned employeeNumber) const
		{
			for (const auto& e : database)
			{
				if (e.getEmployeeNumber() == employeeNumber)
				{
					// Employee found, return the employee object
					return e;
				}
			}
			throw std::out_of_range("Employee not found");
		}
	};
	template<typename T>
	std::ostream& operator<<(std::ostream& os, const DataBase<T>& db)
	{
		db.display(os);
		return os;
	}
}
#endif // !DATABASE_H
