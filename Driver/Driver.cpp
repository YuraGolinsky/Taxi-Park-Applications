#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

struct Driver {
    int id;
    std::string name;
    int hoursWorked;
    std::string phoneNumber;
};

// Генерація унікального ID для нового водія
int generateID(const std::vector<Driver>& drivers) {
    if (drivers.empty()) {
        return 1; // Початкове ID, якщо список водіїв порожній
    }
    else {
        return drivers.back().id + 1; // ID на одиницю більше за останній в списку
    }
}

// Додавання нового водія
void addDriver(std::vector<Driver>& drivers) {
    Driver newDriver;
    newDriver.id = generateID(drivers);
    std::cout << "Enter the driver's name (without spaces): ";
    std::cin >> newDriver.name;
    std::cout << "Enter the driver's phone number: ";
    std::cin >> newDriver.phoneNumber;
    newDriver.hoursWorked = 0;
    drivers.push_back(newDriver);
    std::cout << "Driver added successfully with ID: " << newDriver.id << ".\n";
}

// Логування годин роботи водія
void logHours(std::vector<Driver>& drivers) {
    int id;
    int hours;
    std::cout << "Enter Driver ID: ";
    std::cin >> id;
    std::cout << "Enter the number of hours worked (integer): ";
    std::cin >> hours;

    bool found = false;
    for (auto& driver : drivers) {
        if (driver.id == id) {
            driver.hoursWorked += hours;
            found = true;
            break;
        }
    }

    if (found) {
        std::cout << "Time updated successfully.\n";
    }
    else {
        std::cout << "No driver with this ID found.\n";
    }
}

// Оновлення інформації про водія
void updateDriver(std::vector<Driver>& drivers) {
    int id;
    int newHours;
    std::string newPhoneNumber;
    std::cout << "Enter driver ID to update: ";
    std::cin >> id;

    bool found = false;
    for (auto& driver : drivers) {
        if (driver.id == id) {
            std::cout << "Enter the new number of hours worked (integer): ";
            std::cin >> newHours;
            driver.hoursWorked = newHours;
            std::cout << "Enter the new driver phone number: ";
            std::cin >> newPhoneNumber;
            driver.phoneNumber = newPhoneNumber;
            found = true;
            break;
        }
    }

    if (found) {
        std::cout << "Information updated successfully.\n";
    }
    else {
        std::cout << "No driver with this ID found.\n";
    }
}

// Видалення водія
void deleteDriver(std::vector<Driver>& drivers) {
    int id;
    std::cout << "Enter driver ID to delete: ";
    std::cin >> id;

    auto it = std::remove_if(drivers.begin(), drivers.end(), [id](const Driver& driver) {
        return driver.id == id;
        });

    if (it != drivers.end()) {
        drivers.erase(it, drivers.end());
        std::cout << "Driver removed successfully.\n";
    }
    else {
        std::cout << "No driver with this ID found.\n";
    }
}

// Відображення всіх водіїв
void displayDrivers(const std::vector<Driver>& drivers) {
    std::cout << std::setw(5) << "ID" << std::setw(15) << "Driver Name" << std::setw(20) << "Hours Worked" << std::setw(20) << "Phone\n";
    std::cout << "-------------------------------------------------------------------------------\n";
    for (const auto& driver : drivers) {
        std::cout << std::setw(5) << driver.id << std::setw(15) << driver.name << std::setw(20) << driver.hoursWorked << std::setw(20) << driver.phoneNumber << "\n";
    }
}

// Відображення детальної інформації про водія
void displayDriverDetails(const std::vector<Driver>& drivers) {
    int id;
    std::cout << "Enter driver ID to view information: ";
    std::cin >> id;

    bool found = false;
    for (const auto& driver : drivers) {
        if (driver.id == id) {
            std::cout << "\nID: " << driver.id << "\n";
            std::cout << "Name: " << driver.name << "\n";
            std::cout << "Hours worked: " << driver.hoursWorked << "\n";
            std::cout << "Phone: " << driver.phoneNumber << "\n\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No driver with this ID found.\n";
    }
}

// Збереження даних у файл
void saveToFile(const std::vector<Driver>& drivers, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& driver : drivers) {
            outFile << driver.id << " " << driver.name << " " << driver.hoursWorked << " " << driver.phoneNumber << "\n";
        }
        outFile.close();
        std::cout << "Data saved to file " << filename << ".\n";
    }
    else {
        std::cerr << "Error opening file for writing.\n";
    }
}

// Завантаження даних з файлу
void loadFromFile(std::vector<Driver>& drivers, const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        Driver driver;
        while (inFile >> driver.id >> driver.name >> driver.hoursWorked >> driver.phoneNumber) {
            drivers.push_back(driver);
        }
        inFile.close();
        std::cout << "Data loaded from file " << filename << ".\n";
    }
    else {
        std::cerr << "Error opening file for reading.\n";
    }
}

// Інформація про компанію
void aboutUs() {
    std::cout << "\nAbout Us:\n";
    std::cout << "Welcome to our taxi fleet! We offer quality passenger transportation services. \n";
    std::cout << "Our drivers are professional in their work, ensuring safe and comfortable trips.\n";
    std::cout << "We are constantly improving our service and taking care of our customers.\n\n";
}

// Допомога
void help() {
    std::cout << "\nHelp:\n";
    std::cout << "1. Add a driver: Enter the driver's name (without spaces) and phone number to add a new driver. The driver will get a unique ID.\n";
    std::cout << "2. Log hours: Enter driver ID and number of hours worked (integer).\n";
    std::cout << "3. Update driver information: Enter the driver ID to update the driver's information, then enter the new number of hours worked and the new phone number.\n";
    std::cout << "4. Delete driver: Enter the driver ID to delete.\n";
    std::cout << "5. Show all drivers: Lists all drivers, their IDs, hours worked, and phone numbers.\n";
    std::cout << "6. View driver details: Enter driver ID to view driver details.\n";
    std::cout << "7. Save and exit: Saves all data to a file and exits the program.\n";
    std::cout << "8. About Us: Shows information about the company.\n";
    std::cout << "9. Help: Shows this help.\n\n";;
}

// Пошук водія за іменем або ID
void searchDriver(const std::vector<Driver>& drivers) {
    std::string searchQuery;
    std::cout << "Enter the name or driver ID to search for: ";
    std::cin >> searchQuery;

    bool found = false;
    for (const auto& driver : drivers) {
        if (driver.name == searchQuery || std::to_string(driver.id) == searchQuery) {
            std::cout << "\nID: " << driver.id << "\n";
            std::cout << "Name: " << driver.name << "\n";
            std::cout << "Hours worked: " << driver.hoursWorked << "\n";
            std::cout << "Phone: " << driver.phoneNumber << "\n\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No driver with this name or ID found.\n";
    }
}

int main() {
    std::vector<Driver> drivers;
    std::string filename = "drivers.txt";

    // Завантаження даних при запуску програми
    loadFromFile(drivers, filename);

    int choice;

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Add driver\n";
        std::cout << "2. Register hours\n";
        std::cout << "3. Update driver information\n";
        std::cout << "4. Delete the driver\n";
        std::cout << "5. Show all drivers\n";
        std::cout << "6. View detailed information about the driver\n";
        std::cout << "7. Save and exit\n";
        std::cout << "8. About us\n";
        std::cout << "9. Help\n";
        std::cout << "10. Search for driver by name or ID\n";
        std::cout << "Select option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addDriver(drivers);
            break;
        case 2:
            logHours(drivers);
            break;
        case 3:
            updateDriver(drivers);
            break;
        case 4:
            deleteDriver(drivers);
            break;
        case 5:
            displayDrivers(drivers);
            break;
        case 6:
            displayDriverDetails(drivers);
            break;
        case 7:
            saveToFile(drivers, filename);
            std::cout << "Exit...\n";
            return 0;
        case 8:
            aboutUs();
            break;
        case 9:
            help();
            break;
        case 10:
            searchDriver(drivers);
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
