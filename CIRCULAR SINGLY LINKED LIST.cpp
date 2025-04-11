#include <iostream>   // Include input/output stream library
#include <string>     // Include string library
using namespace std;  // Use standard namespace

// Define Student structure for circular singly linked list nodes
struct Student {
	string name;    // Student's name
	int age;        // Student's age
	int id;         // Student's ID
	Student *next;  // Pointer to next node
};

Student *head = NULL;  // Global pointer to the first node (initially NULL)

// Function prototypes
void displayMenu();            // Displays main menu
void insertAtBeginning();      // Inserts node at beginning
void insertAtEnd();            // Inserts node at end
void insertAtPosition();       // Inserts node at specific position
void deleteFromBeginning();     // Deletes first node
void deleteFromEnd();           // Deletes last node
void deleteFromPosition();      // Deletes node at position
void searchForElement();        // Searches for student by ID
void displayList();             // Displays all students
void deleteList();              // Deletes entire list (cleanup)

int main() {
	displayMenu();  // Start program by showing menu
	deleteList();   // Clean up memory before exiting
	return 0;       // Exit program
}

// Displays menu and handles user input
void displayMenu() {
	int choice;  // Stores user's menu choice

	do {
		// Print menu options
		cout << "\nCIRCULAR SINGLY LINKED LIST MENU\n"
		     << "1. Insert at beginning\n"
		     << "2. Insert at end\n"
		     << "3. Insert at position\n"
		     << "4. Delete from beginning\n"
		     << "5. Delete from end\n"
		     << "6. Delete from position\n"
		     << "7. Search for element\n"
		     << "8. Display list\n"
		     << "9. Exit\n"
		     << "----------------------\nYour choice: ";
		cin >> choice;  // Get user input

		// Execute function based on choice
		switch (choice) {
			case 1:
				insertAtBeginning();
				break;
			case 2:
				insertAtEnd();
				break;
			case 3:
				insertAtPosition();
				break;
			case 4:
				deleteFromBeginning();
				break;
			case 5:
				deleteFromEnd();
				break;
			case 6:
				deleteFromPosition();
				break;
			case 7:
				searchForElement();
				break;
			case 8:
				displayList();
				break;
			case 9:
				cout << "Exiting program.\n";
				break;
			default:
				cout << "Invalid option! Please try again.\n";
		}
	} while (choice != 9);  // Loop until exit chosen
}

// Inserts new student at beginning of circular list
void insertAtBeginning() {
	Student *newStudent = new Student;  // Create new node

	// Get student details
	cout << "Enter name: ";
	cin >> newStudent->name;
	cout << "Enter age: ";
	cin >> newStudent->age;
	cout << "Enter ID: ";
	cin >> newStudent->id;

	if (head == NULL) {
		// If list is empty, new node points to itself
		newStudent->next = newStudent;
		head = newStudent;
	} else {
		// Find the last node (points back to head)
		Student *last = head;
		while (last->next != head) {
			last = last->next;
		}
		// Insert new node at beginning
		newStudent->next = head;
		head = newStudent;
		last->next = head;  // Update last node to point to new head
	}
	cout << "Successfully added at beginning.\n";
}

// Inserts new student at end of circular list
void insertAtEnd() {
	Student *newStudent = new Student;  // Create new node

	// Get student details
	cout << "Enter name: ";
	cin >> newStudent->name;
	cout << "Enter age: ";
	cin >> newStudent->age;
	cout << "Enter ID: ";
	cin >> newStudent->id;

	if (head == NULL) {
		// If list is empty, new node points to itself
		newStudent->next = newStudent;
		head = newStudent;
	} else {
		// Find last node (points back to head)
		Student *last = head;
		while (last->next != head) {
			last = last->next;
		}
		// Insert new node at end
		last->next = newStudent;
		newStudent->next = head;  // New last node points back to head
	}
	cout << "Successfully added at end.\n";
}

// Inserts new student at specified position
void insertAtPosition() {
	int pos;  // Position to insert at
	cout << "Position to insert: ";
	cin >> pos;

	if (pos < 1) {
		cout << "Invalid position!\n";
		return;
	}

	// Handle position 1 specially
	if (pos == 1) {
		insertAtBeginning();
		return;
	}

	Student *newStudent = new Student;  // Create new node

	// Get student details
	cout << "Enter name: ";
	cin >> newStudent->name;
	cout << "Enter age: ";
	cin >> newStudent->age;
	cout << "Enter ID: ";
	cin >> newStudent->id;

	// Traverse to position before insertion point
	Student *temp = head;
	for (int i = 1; i < pos - 1 && temp->next != head; i++) {
		temp = temp->next;
	}

	if (temp->next == head && pos > 1) {
		// Inserting after last node is same as insertAtEnd
		temp->next = newStudent;
		newStudent->next = head;
	} else {
		// Insert at middle position
		newStudent->next = temp->next;
		temp->next = newStudent;
	}
	cout << "Successfully added at position " << pos << ".\n";
}

// Deletes first student from circular list
void deleteFromBeginning() {
	if (head == NULL) {
		cout << "List is empty!\n";
		return;
	}

	if (head->next == head) { // Only one node in list
		cout << "Deleted: " << head->name << endl;
		delete head;
		head = NULL;
	} else {
		// Find last node (points back to head)
		Student *last = head;
		while (last->next != head) {
			last = last->next;
		}
		// Remove first node
		Student *temp = head;
		head = head->next;
		last->next = head;  // Update last node to point to new head
		cout << "Deleted: " << temp->name << endl;
		delete temp;
	}
}

// Deletes last student from circular list
void deleteFromEnd() {
	if (head == NULL) {
		cout << "List is empty!\n";
		return;
	}

	if (head->next == head) { // Only one node in list
		cout << "Deleted: " << head->name << endl;
		delete head;
		head = NULL;
	} else {
		// Find second-to-last node
		Student *temp = head;
		Student *prev = NULL;
		while (temp->next != head) {
			prev = temp;
			temp = temp->next;
		}
		// Remove last node
		prev->next = head;  // Make second-to-last point to head
		cout << "Deleted: " << temp->name << endl;
		delete temp;
	}
}

// Deletes student from specified position
void deleteFromPosition() {
	if (head == NULL) {
		cout << "List is empty!\n";
		return;
	}

	int pos;  // Position to delete
	cout << "Position to delete: ";
	cin >> pos;

	if (pos < 1) {
		cout << "Invalid position!\n";
		return;
	}

	// Handle position 1 specially
	if (pos == 1) {
		deleteFromBeginning();
		return;
	}

	// Traverse to node to delete
	Student *temp = head;
	Student *prev = NULL;
	for (int i = 1; i < pos && temp->next != head; i++) {
		prev = temp;
		temp = temp->next;
	}

	// Check if position is valid
	if (temp == head || (temp->next == head && pos > 1)) {
		cout << "Position out of range!\n";
		return;
	}

	// Remove node at position
	prev->next = temp->next;
	cout << "Deleted: " << temp->name << endl;
	delete temp;
}

// Searches for student by ID and displays info
void searchForElement() {
	if (head == NULL) {
		cout << "List is empty!\n";
		return;
	}

	int searchId;  // ID to search for
	cout << "Enter ID to search: ";
	cin >> searchId;

	Student *temp = head;  // Start at head
	int position = 1;      // Track position
	bool found = false;    // Track if found

	// Loop through circular list
	do {
		if (temp->id == searchId) {
			// Display found student
			cout << "Student found at position " << position << ":\n";
			cout << "Name: " << temp->name << "\n";
			cout << "Age: " << temp->age << "\n";
			cout << "ID: " << temp->id << "\n";
			found = true;
			break;
		}
		temp = temp->next;
		position++;
	} while (temp != head);

	if (!found) {
		cout << "Student with ID " << searchId << " not found.\n";
	}
}

// Displays all students in circular list
void displayList() {
	if (head == NULL) {
		cout << "List is empty!\n";
		return;
	}

	Student *temp = head;  // Start at head
	int count = 1;         // Student counter

	cout << "\nStudent List:\n";
	// Loop through circular list
	do {
		// Print student info
		cout << "Student " << count++ << ":\n"
		     << "Name: " << temp->name << "\n"
		     << "Age: " << temp->age << "\n"
		     << "ID: " << temp->id << "\n\n";
		temp = temp->next;  // Move to next node
	} while (temp != head);
}

// Deletes entire circular list (cleanup)
void deleteList() {
	if (head == NULL)
		return;  // Nothing to delete

	Student *current = head;
	Student *nextNode;

	// Traverse and delete all nodes
	do {
		nextNode = current->next;
		delete current;
		current = nextNode;
	} while (current != head);

	head = NULL;  // Reset head pointer
}