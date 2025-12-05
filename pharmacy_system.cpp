#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>  // For table formatting
#include <stdlib.h> // For system("cls")

using namespace std;

// --- Configuration & Helpers ---
const string DB_FILENAME = "pharmacy_db.txt";

void clearScreen() {
    // Windows uses "cls", Linux/Mac uses "clear"
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    cout << "\n\tPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void printHeader() {
    cout << "\n\t=================================================";
    cout << "\n\t   P H A R M A C Y   M A N A G E M E N T   S Y S ";
    cout << "\n\t=================================================\n";
}

// --- Class Definition ---
class Medicine {
private:
    int id;
    string name;
    string company;
    double price;
    int quantity;

public:
    Medicine() {}
    Medicine(int i, string n, string c, double p, int q) {
        id = i;
        name = n;
        company = c;
        price = p;
        quantity = q;
    }

    // Getters
    int getId() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }
    int getQuantity() { return quantity; }
    
    // Setters
    void setQuantity(int q) { quantity = q; }

    // Serialization: Save object to file string
    string toFileString() {
        return to_string(id) + "," + name + "," + company + "," + to_string(price) + "," + to_string(quantity);
    }

    // Display formatted row
    void printRow() {
        cout << "\t" 
             << left << setw(8) << id 
             << left << setw(20) << name 
             << left << setw(20) << company 
             << left << setw(10) << price 
             << left << setw(10) << quantity << endl;
    }
};

// --- System Logic ---
class PharmacySystem {
private:
    vector<Medicine> inventory;

    // Helper: Split string by delimiter for file reading
    vector<string> split(string s, char delimiter) {
        vector<string> tokens;
        string token;
        size_t pos = 0;
        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            tokens.push_back(token);
            s.erase(0, pos + 1);
        }
        tokens.push_back(s);
        return tokens;
    }

public:
    // Load data from file on startup
    void loadData() {
        inventory.clear();
        ifstream inFile(DB_FILENAME);
        if (!inFile) return; // File doesn't exist yet, that's fine

        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            vector<string> data = split(line, ',');
            if (data.size() == 5) {
                Medicine m(stoi(data[0]), data[1], data[2], stod(data[3]), stoi(data[4]));
                inventory.push_back(m);
            }
        }
        inFile.close();
    }

    // Save data to file
    void saveData() {
        ofstream outFile(DB_FILENAME);
        for (Medicine &m : inventory) {
            outFile << m.toFileString() << endl;
        }
        outFile.close();
    }

    void addMedicine() {
        clearScreen();
        printHeader();
        cout << "\n\t[ ADD NEW MEDICINE ]\n";

        int id, qty;
        string name, company;
        double price;

        cout << "\tEnter ID: "; cin >> id;
        
        // Check if ID exists
        for (Medicine &m : inventory) {
            if (m.getId() == id) {
                cout << "\n\tError: Medicine ID already exists!\n";
                return;
            }
        }

        cout << "\tEnter Name: "; cin.ignore(); getline(cin, name);
        cout << "\tEnter Company: "; getline(cin, company);
        cout << "\tEnter Price: "; cin >> price;
        cout << "\tEnter Quantity: "; cin >> qty;

        Medicine newMed(id, name, company, price, qty);
        inventory.push_back(newMed);
        saveData();
        cout << "\n\tSuccess: Medicine added to database!\n";
    }

    void viewInventory() {
        clearScreen();
        printHeader();
        cout << "\n\t[ CURRENT INVENTORY ]\n\n";
        
        cout << "\t" 
             << left << setw(8) << "ID" 
             << left << setw(20) << "Name" 
             << left << setw(20) << "Company" 
             << left << setw(10) << "Price($)" 
             << left << setw(10) << "Qty" << endl;
        cout << "\t-----------------------------------------------------------------\n";

        if (inventory.empty()) {
            cout << "\tNo records found.\n";
        } else {
            for (Medicine &m : inventory) {
                m.printRow();
            }
        }
    }

    void searchMedicine() {
        clearScreen();
        printHeader();
        cout << "\n\t[ SEARCH MEDICINE ]\n";
        int id;
        cout << "\tEnter ID to search: "; cin >> id;

        bool found = false;
        cout << "\n\tResult:\n";
        cout << "\t-----------------------------------------------------------------\n";
        for (Medicine &m : inventory) {
            if (m.getId() == id) {
                m.printRow();
                found = true;
                break;
            }
        }
        if (!found) cout << "\tMedicine not found.\n";
    }

    void sellMedicine() {
        clearScreen();
        printHeader();
        cout << "\n\t[ SELL MEDICINE ]\n";
        
        int id, qty;
        cout << "\tEnter Medicine ID: "; cin >> id;

        bool found = false;
        for (Medicine &m : inventory) {
            if (m.getId() == id) {
                found = true;
                cout << "\tFound: " << m.getName() << " | Price: $" << m.getPrice() << " | Available: " << m.getQuantity() << endl;
                cout << "\tEnter Quantity to Sell: "; cin >> qty;

                if (qty > m.getQuantity()) {
                    cout << "\n\tError: Not enough stock available!\n";
                } else {
                    m.setQuantity(m.getQuantity() - qty);
                    double total = qty * m.getPrice();
                    cout << "\n\t--------------------------";
                    cout << "\n\t BILL GENERATED";
                    cout << "\n\t--------------------------";
                    cout << "\n\t Item: " << m.getName();
                    cout << "\n\t Qty:  " << qty;
                    cout << "\n\t Total: $" << total;
                    cout << "\n\t--------------------------\n";
                    saveData(); // Update DB
                }
                break;
            }
        }
        if (!found) cout << "\n\tError: ID not found.\n";
    }
};

int main() {
    PharmacySystem pharmacy;
    pharmacy.loadData(); // Load database on startup

    int choice;
    do {
        clearScreen();
        printHeader();
        cout << "\n\t1. Add New Medicine";
        cout << "\n\t2. View Inventory";
        cout << "\n\t3. Search Medicine";
        cout << "\n\t4. Sell Medicine (Billing)";
        cout << "\n\t5. Exit";
        cout << "\n\n\tEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: pharmacy.addMedicine(); pauseScreen(); break;
            case 2: pharmacy.viewInventory(); pauseScreen(); break;
            case 3: pharmacy.searchMedicine(); pauseScreen(); break;
            case 4: pharmacy.sellMedicine(); pauseScreen(); break;
            case 5: cout << "\n\tExiting... Data Saved.\n"; break;
            default: cout << "\n\tInvalid Choice!\n"; pauseScreen();
        }
    } while (choice != 5);

    return 0;
}