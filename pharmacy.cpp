#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For transforming text to lowercase

using namespace std;

// 1. Define a structure to hold medicine details
struct Medicine {
    string name;
    string uses;
};

// 2. Helper function to convert a string to lowercase
// This ensures that "Panadol" and "panadol" are treated the same way.
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int main() {
    // 3. Initialize the database with 10 medicines
    vector<Medicine> pharmacy = {
        {"Panadol", "Used for mild to moderate pain relief and reducing fever."},
        {"Brufen", "Anti-inflammatory drug used for pain relief, arthritis, and fever."},
        {"Disprin", "Used for headaches, toothaches, and reducing risk of heart attack."},
        {"Augmentin", "Antibiotic used to treat bacterial infections like pneumonia and ear infections."},
        {"Flagyl", "Used to treat bacterial and parasitic infections (e.g., stomach issues)."},
        {"Zyrtec", "Antihistamine used to relieve allergy symptoms like runny nose and sneezing."},
        {"Gaviscon", "Used to treat heartburn and acid indigestion."},
        {"Risek", "Used to treat GERD (acid reflux) and ulcers."},
        {"Arinac", "Used for cold and flu symptoms, specifically nasal congestion and pain."},
        {"Gravinate", "Used to prevent and treat nausea, vomiting, and dizziness."}
    };

    string searchInput;
    bool keepRunning = true;

    cout << "========================================" << endl;
    cout << "      WELCOME TO THE PHARMACY APP       " << endl;
    cout << "========================================" << endl;

    while (keepRunning) {
        cout << "\nEnter the name of the medicine you want to find (or type 'exit' to quit): ";
        // getline allows us to read the whole line including spaces
        getline(cin, searchInput);

        // Check if user wants to exit
        if (toLowerCase(searchInput) == "exit") {
            keepRunning = false;
            break;
        }

        bool found = false;
        string searchLower = toLowerCase(searchInput);

        // 4. Search logic
        for (const auto& med : pharmacy) {
            // Compare the lowercase versions of the names
            if (toLowerCase(med.name) == searchLower) {
                cout << "\n----------------------------------------" << endl;
                cout << "Medicine: " << med.name << endl;
                cout << "Uses:     " << med.uses << endl;
                cout << "----------------------------------------" << endl;
                found = true;
                break; // Stop looking once we find it
            }
        }

        if (!found) {
            cout << "\n[!] Sorry, '" << searchInput << "' was not found in our database." << endl;
            cout << "Available medicines: Panadol, Brufen, Disprin, Augmentin, Flagyl, Zyrtec, Gaviscon, Risek, Arinac, Gravinate." << endl;
        }
    }

    cout << "\nThank you for using the Pharmacy App!" << endl;
    return 0;
}