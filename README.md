Pharmacy Management System (C++)

A robust, console-based application designed to manage pharmaceutical inventory, track sales, and maintain persistent records using file handling. This project demonstrates core Object-Oriented Programming (OOP) concepts in C++.

🚀 Features

Inventory Management: Add new medicines with details (ID, Name, Company, Price, Quantity).

Persistent Storage: Automatically saves and loads data from a local file (pharmacy_db.txt), ensuring data isn't lost when the program closes.

Search Functionality: Quickly find medicines by their unique ID.

Billing System: Sell medicines, calculate total costs, and automatically update stock levels.

Formatted Dashboard: Clean, table-based console output for easy viewing.

🛠️ Tech Stack

Language: C++ (Standard 11 or higher recommended)

Storage: Flat File Database (.txt)

Interface: Command Line Interface (CLI) / Console

📂 Project Structure

pharmacy_system.cpp - The main source code containing the class definitions and logic.

pharmacy_db.txt - The database file (automatically created after adding the first medicine).

README.md - This documentation file.

⚙️ How to Run

Option 1: Using Visual Studio Code (VS Code)

Ensure you have the C/C++ Extension and a compiler like MinGW installed.

Open the folder containing pharmacy_system.cpp in VS Code.

Open the file and press the Run / Play button (top right).

Select g++.exe if prompted.

Interact with the application in the Terminal tab.

Option 2: Using Dev-C++ or Code::Blocks

Open the IDE.

Create a new Source File.

Paste the code and save it as pharmacy_system.cpp.

Press F11 (Dev-C++) or Build and Run (Code::Blocks).

Option 3: Command Line (Manual Compilation)

If you have G++ installed in your system path:

# Compile
g++ pharmacy_system.cpp -o pharmacy_app

# Run (Windows)
pharmacy_app.exe

# Run (Mac/Linux)
./pharmacy_app


🧩 Code Architecture

The system is built on two main classes:

class Medicine:

Represents a single product.

Encapsulates private data: id, name, company, price, quantity.

Handles serialization (converting object data to a comma-separated string for file storage).

class PharmacySystem:

Manages the collection of medicines using std::vector.

Handles business logic: addMedicine(), sellMedicine(), searchMedicine().

Manages File I/O: loadData() reads from text, saveData() writes to text.

📝 Usage Guide

Start the App: Upon launching, the system attempts to load existing data.

Add Stock: Choose option 1 to add items. Ensure IDs are unique.

View Stock: Choose option 2 to see a formatted table of all items.

Sell: Choose option 4. Enter the ID and Quantity. The system will validate stock and generate a mini-bill on the screen.

⚠️ Notes

Data File: Do not manually edit pharmacy_db.txt unless you keep the format id,name,company,price,qty. Corrupting this format may crash the loader.

Clear Screen: The system("cls") command is used for Windows. If running on Linux/Mac, the code automatically switches to system("clear").
