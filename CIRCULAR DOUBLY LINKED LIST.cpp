#include <iostream>   // Include input/output stream library
#include <string>     // Include string library
using namespace std;  // Use standard namespace

// Define Student structure for circular doubly linked list nodes
struct Student {
	string name;    // Student's name
	int age;        // Student's age
	int id;         // Student's ID (unique identifier)
	Student *next;  // Pointer to next node
	Student *prev;  // Pointer to previous node
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

int main() {
	displayMenu();  // Start program by showing menu
	return 0;       // Exit program
}

// Displays menu and handles user input
void displayMenu() {
	int choice;  // Stores user's menu choice

	do {
		// Print menu options
		cout << "\nCIRCULAR DOUBLY LINKED LIST MENU\n"
		     << "1. Insert at beginning\n"
		     << "2. Insert at end\n"
		     << "3. Insert at position\n"
		     << "4. Delete from beginning\n"
		     << "5. Delete from end\n"
		     << "6. Delete from position\n"
		     << "7. Search for element\n"
		     << "8. Display list\n"
		     << "9. Exit\n"
		     << "----------------------\nYour Choice: ";
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
				cout << "Exiting the program.\n";
				break;
			default:
				cout << "Invalid option! Please try again.\n";
		}
	} while (choice != 9);  // Loop until exit chosen
}

// Inserts new student at beginning of circular doubly linked list
void insertAtBeginning() {
	Student *newStudent = new Student;  // Create new node

	// Get student details
	cout << "Enter name: ";
	cin >> newStudent->name;
	cout << "Enter age: ";
	cin >> newStudent->age;
	cout << "Enter ID: ";
	cin >> newStudent->id;

	if (!head) {
		// If list is empty, new node points to itself in both directions
		newStudent->next = newStudent;
		newStudent->prev = newStudent;
		head = newStudent;
	} else {
		// Get last node (which points back to head)
		Student *last = head->prev;

		// Update pointers for new node
		newStudent->next = head;
		newStudent->prev = last;

		// Update surrounding nodes' pointers
		last->next = newStudent;
		head->prev = newStudent;

		// Update head to point to new node
		head = newStudent;
	}
	cout << "Successfully Added at beginning.\n";
}

// Inserts new student at end of circular doubly linked list
void insertAtEnd() {
	Student *newStudent = new Student;  // Create new node

	// Get student details
	cout << "Enter name: ";
	cin >> newStudent->name;
	cout << "Enter age: ";
	cin >> newStudent->age;
	cout << "Enter ID: ";
	cin >> newStudent->id;

	if (!head) {
		// If list is empty, same as insertAtBeginning
		newStudent->next = newStudent;
		newStudent->prev = newStudent;
		head = newStudent;
	} else {
		// Get last node
		Student *last = head->prev;

		// Update pointers for new node
		newStudent->next = head;
		newStudent->prev = last;

		// Update surrounding nodes' pointers
		last->next = newStudent;
		head->prev = newStudent;
	}
	cout << "Added at end.\n";
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

	// If position is beyond last node, insert at end
	if (temp->next == head && pos > 1) {
		cout << "Position out of range! Inserting at end instead.\n";
		insertAtEnd();
		return;
	}

	// Update pointers for new node
	newStudent->next = temp->next;
	newStudent->prev = temp;

	// Update surrounding nodes' pointers
	temp->next->prev = newStudent;
	temp->next = newStudent;

	cout << "Added at position " << pos << ".\n";
}

// Deletes first student from circular doubly linked list
void deleteFromBeginning() {
	if (!head) {
		cout << "List is empty!\n";
		return;
	}

	Student *temp = head;  // Node to delete

	if (temp->next == head) {
		// Only one node in list
		head = NULL;
	} else {
		// Get last node
		Student *last = head->prev;

		// Update head pointer
		head = head->next;

		// Update pointers of surrounding nodes
		last->next = head;
		head->prev = last;
	}

	cout << "Deleted: " << temp->name << endl;
	delete temp;  // Free memory
}

// Deletes last student from circular doubly linked list
void deleteFromEnd() {
	if (!head) {
		cout << "List is empty!\n";
		return;
	}

	Student *last = head->prev;  // Node to delete

	if (last == head) {
		// Only one node in list
		cout << "Deleted: " << head->name << endl;
		delete head;
		head = NULL;
		return;
	}

	// Update pointers of surrounding nodes
	last->prev->next = head;
	head->prev = last->prev;

	cout << "Deleted: " << last->name << endl;
	delete last;  // Free memory
}

// Deletes student from specified position
void deleteFromPosition() {
	if (!head) {
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
	for (int i = 1; i < pos && temp->next != head; i++) {
		temp = temp->next;
	}

	// Check if position is valid
	if (temp->next == head && pos > 1) {
		cout << "Position out of range!\n";
		return;
	}

	// Update pointers of surrounding nodes
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;

	cout << "Deleted: " << temp->name << endl;
	delete temp;  // Free memory
}

// Searches for student by ID and displays info
void searchForElement() {
	if (!head) {
		cout << "List is empty!\n";
		return;
	}

	int searchId;  // ID to search for
	cout << "Enter ID to search: ";
	cin >> searchId;

	Student *temp = head;  // Start at head
	bool found = false;    // Track if found
	int position = 1;      // Track position

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
		cout << "Student with ID " << searchId << " not found in the list.\n";
	}
}

// Displays all students in circular doubly linked list
void displayList() {
	if (!head) {
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
	cout << "End of student list.\n";
}