#include <iostream>   // Include input/output stream library
#include <string>     // Include string library
using namespace std;  // Use standard namespace

// Define Student structure for doubly linked list nodes
struct Student {
	string name;    // Student's name
	int age;        // Student's age
	int id;         // Student's ID
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
		cout << "\nDOUBLY LINKED LIST MENU\n"
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

// Inserts new student at beginning of list
void insertAtBeginning() {
	Student *newStudent = new Student;  // Create new node

	// Get student details
	cout << "Enter name: ";
	cin >> newStudent->name;
	cout << "Enter age: ";
	cin >> newStudent->age;
	cout << "Enter ID: ";
	cin >> newStudent->id;

	// Set new node's pointers
	newStudent->prev = NULL;  // First node has no previous
	newStudent->next = head;  // Points to current head

	if (head != NULL) {
		head->prev = newStudent;  // Update current head's previous
	}

	head = newStudent;  // Make new node the head
	cout << "Successfully Added at beginning.\n";
}

// Inserts new student at end of list
void insertAtEnd() {
	Student *newStudent = new Student;  // Create new node

	// Get student details
	cout << "Enter name: ";
	cin >> newStudent->name;
	cout << "Enter age: ";
	cin >> newStudent->age;
	cout << "Enter ID: ";
	cin >> newStudent->id;

	newStudent->next = NULL;  // Last node has no next

	if (head == NULL) {
		// If list is empty
		newStudent->prev = NULL;
		head = newStudent;
	} else {
		// Traverse to last node
		Student *temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newStudent;  // Link last node to new node
		newStudent->prev = temp;  // New node's previous is old last
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
	for (int i = 1; i < pos - 1 && temp != NULL; i++) {
		temp = temp->next;
	}

	if (temp == NULL) {
		cout << "Position out of range!\n";
		return;
	}

	// Update pointers for new node
	newStudent->next = temp->next;
	newStudent->prev = temp;

	if (temp->next != NULL) {
		temp->next->prev = newStudent;  // Update next node's previous
	}
	temp->next = newStudent;  // Update current node's next
	cout << "Added at position " << pos << ".\n";
}

// Deletes first student from list
void deleteFromBeginning() {
	if (head == NULL) {
		cout << "List is empty!\n";
		return;
	}

	Student *temp = head;  // Store current head
	head = head->next;     // Move head to next node

	if (head != NULL) {
		head->prev = NULL;  // New head has no previous
	}

	cout << "Deleted: " << temp->name << endl;
	delete temp;  // Free memory
}

// Deletes last student from list
void deleteFromEnd() {
	if (head == NULL) {
		cout << "List is empty!\n";
		return;
	}

	Student *temp = head;
	// Traverse to last node
	while (temp->next != NULL) {
		temp = temp->next;
	}

	// Update previous node's next pointer
	if (temp->prev != NULL) {
		temp->prev->next = NULL;
	} else {
		head = NULL;  // List had only one node
	}

	cout << "Deleted: " << temp->name << endl;
	delete temp;  // Free memory
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
	for (int i = 1; i < pos && temp != NULL; i++) {
		temp = temp->next;
	}

	if (temp == NULL) {
		cout << "Position out of range!\n";
		return;
	}

	// Update surrounding nodes' pointers
	if (temp->next != NULL) {
		temp->next->prev = temp->prev;
	}
	temp->prev->next = temp->next;

	cout << "Deleted: " << temp->name << endl;
	delete temp;  // Free memory
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
	bool found = false;    // Track if found
	int position = 1;      // Track position

	while (temp != NULL) {
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
	}

	if (!found) {
		cout << "Student with ID " << searchId << " not found in the list.\n";
	}
}

// Displays all students in list
void displayList() {
	if (head == NULL) {
		cout << "List is empty!\n";
		return;
	}

	Student *temp = head;  // Start at head
	int count = 1;         // Student counter

	cout << "\nStudent List:\n";
	while (temp != NULL) {
		// Print student info
		cout << "Student " << count++ << ":\n"
		     << "Name: " << temp->name << "\n"
		     << "Age: " << temp->age << "\n"
		     << "ID: " << temp->id << "\n\n";
		temp = temp->next;  // Move to next node
	}
	cout << "End of student list.\n";
}