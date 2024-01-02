#include <regex>
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

namespace Employee
{
	const int Address_postal_code_length = 7;

	struct Address
	{
		unsigned street_number;
		std::string street_name;
		std::string postal_code;

		bool load(std::ifstream& f)
		{
			f >> street_number >> street_name;
			char postal_code_temp[1 + Address_postal_code_length + 1] = { 0 };
			f.read(postal_code_temp, Address_postal_code_length + 1);
			postal_code = std::string(postal_code_temp + 1);
			return f.good();
		}

		bool save(std::ofstream& f) const
		{
			if (!f.is_open() || !f.good())
				return false;  // Check if the file is open and in a good state

			// Save the individual components of the Address
			f << street_number << ' ' << street_name << ' ' << postal_code << ' ';

			return f.good();  // Return the status of the ofstream (true if write operations are successful)
		}

		friend std::ostream& operator<<(std::ostream& os, const Address& address)
		{
			os << std::setw(10) << address.street_number << " " 
				<< std::setw(10) << address.street_name << " " 
				<< std::setw(7) << address.postal_code << " ";
			return os;
		}

		friend std::istream& operator>>(std::istream& is, Address& address)
		{
			bool error = false;
			int street_number;
			std::string street_name, postal_code;
			while (!error)
			{
				std::cout << "Enter street number: ";
				is >> street_number;
				//checks for valid street number
				if (street_number < 0)
				{
					is.clear();
					std::cout << "Invalid Street Number\n";
				}
				else
				{
					error = true;
				}
			}
			error = false;
			while (!error)
			{
				std::cout << "Enter street name: ";
				// Read street_name until newline character
				std::getline(is >> std::ws, street_name);
				//checking if street name is empty or if is stream fails
				if (is.fail() || street_name[0] == '\n')
				{
					is.clear();
					std::cout << "Invalid Street Name\n";
				}
				else
				{
					error = true;
				}
			}
			error = false;
			while (!error)
			{
				std::cout << "Enter postal code: ";
				// Read postal_code until newline character
				std::getline(is >> std::ws, postal_code);
				// Validate postal code using a regular expression
				std::regex postalCodePattern("[A-Za-z]\\d[A-Za-z] \\d[A-Za-z]\\d");
				if (!std::regex_match(postal_code, postalCodePattern))
				{
					is.clear();
					std::cout << "Invalid Postal Code\n";
				}
				else
				{
					error = true;
				}
			}
			address.street_number = street_number;
			address.street_name = street_name;
			address.postal_code = postal_code;
			return is;
		}
	};

	struct Name
	{
		std::string first_name;
		std::string last_name;

		Name() = default;

		bool operator==(const Name& other) const
		{
			return (first_name == other.first_name) && (last_name == other.last_name);
		}
		
		bool load(std::ifstream& f)
		{
			f >> first_name >> last_name;
			return f.good();
		}

		bool save(std::ofstream& f) const
		{
			if (!f.is_open() || !f.good())
				return false;  // Check if the file is open and in a good state

			f << first_name << ' ' << last_name << ' ';

			return f.good();  // Return the status of the ofstream (true if write operations are successful)
		}


		friend std::ostream& operator<<(std::ostream& os, const Name& name)
		{
			os << std::setw(10) << name.first_name << " " << std::setw(10) << name.last_name << " ";
			return os;
		}

		friend std::istream& operator>>(std::istream& is, Name& name)
		{
			std::string first_name, last_name;
			bool error = false;
			while (!error)
			{
				std::cout << "Enter employee's first name: ";
				// Read First name until newline charater
				std::getline(is >> std::ws, first_name);
				// Checks if istream fails or first name is valid
				if (is.fail() || first_name[0] == '\n')
				{
					is.clear();
					std::cout << "Invalid First Name\n";
				}
				else
				{
					error = true;
				}
			}
			error = false;
			while (!error)
			{
				std::cout << "Enter employee's last name: ";
				// Read Last name until newline charater
				std::getline(is >> std::ws, last_name);
				// Checks if istream fails or last name is valid
				if (is.fail() || last_name[0] == '\n')
				{
					is.clear();
					std::cout << "Invalid Last Name\n";
				}
				else
				{
					error = true;
				}
			}
			name.first_name = first_name;
			name.last_name = last_name;
			return is;
		}
	};

	class Employee
	{
	private:
		Name name;
		Address address;
		double salary;
		unsigned employee_number;
		std::string position;
	public:
		Employee() = default;
		Employee(const Name& name, const Address& address, const double salary, const std::string& position, const unsigned employee_number);
		Employee(const Employee& copy);
		bool load(std::ifstream& f);
		bool save(std::ofstream& f) const;

		//helpers
		void display(std::ostream& os) const;
		void inputEmployee(std::istream& is);
		unsigned getEmployeeNumber() const;
	};
	std::ostream& operator<<(std::ostream& os, const Employee& emp);
	std::istream& operator>>(std::istream& is, Employee& emp);

}

#endif // !EMPLOYEE_H