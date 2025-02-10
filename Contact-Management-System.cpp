#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std;
class Node {
public:
string name;
string phoneNumber;
Node* left;
Node* right;
Node(string name, string phoneNumber) {
this->name = name;
this->phoneNumber = phoneNumber;
left = right = nullptr;
}
};
struct CompareNames {
bool operator()(const Node* a, const Node* b) {
return a->name > b->name;
}
};
class AddressBook {
private:
Node* root;
map<string, string> phoneToNameMap;
priority_queue<Node*, vector<Node*>, CompareNames> minHeap;
Node* insert(Node* root, string name, string phoneNumber) {
if (root == nullptr) {
Node* newNode = new Node(name, phoneNumber);
minHeap.push(newNode);
return newNode;
}
if (name < root->name) {
root->left = insert(root->left, name, phoneNumber);
} else if (name > root->name) {
root->right = insert(root->right, name, phoneNumber);
} else {
root->phoneNumber = phoneNumber;
}
return root;
}
void inOrder(Node* root) {
if (root != nullptr) {
inOrder(root->left);
cout << "Name: " << root->name << ", Phone: " << root->phoneNumber << endl;
inOrder(root->right);
}
}
Node* searchByName(Node* root, string name) {
if (root == nullptr || root->name == name) {
return root;
}
if (name < root->name) {
return searchByName(root->left, name);
} else {
return searchByName(root->right, name);
}
}
Node* minValueNode(Node* node) {
Node* current = node;
while (current && current->left != nullptr) {
current = current->left;
}
return current;
}
Node* deleteNode(Node* root, string name) {
if (root == nullptr) return root;
if (name < root->name) {
root->left = deleteNode(root->left, name);
} else if (name > root->name) {
root->right = deleteNode(root->right, name);
} else {
if (root->left == nullptr) {
Node* temp = root->right;
delete root;
return temp;
} else if (root->right == nullptr) {
Node* temp = root->left;
delete root;
return temp;
}
Node* temp = minValueNode(root->right);
root->name = temp->name;
root->phoneNumber = temp->phoneNumber;
root->right = deleteNode(root->right, temp->name);
}
return root;
}
public:
AddressBook() {
root = nullptr;
}
void addContact(string name, string phoneNumber) {
root = insert(root, name, phoneNumber);
phoneToNameMap[phoneNumber] = name;
cout << "Contact added successfully." << endl;
}
void updateContact(string oldName, string newName, string newPhoneNumber) {
Node* result = searchByName(root, oldName);
if (result != nullptr) {
phoneToNameMap.erase(result->phoneNumber);
root = deleteNode(root, oldName);
root = insert(root, newName, newPhoneNumber);
phoneToNameMap[newPhoneNumber] = newName;
cout << "Contact updated successfully." << endl;
} else {
cout << "Contact not found." << endl;
}
}
void viewContacts() {
if (root == nullptr) {
cout << "No contacts in the address book." << endl;
} else {
cout << "Contacts in the address book (sorted by name):" << endl;
inOrder(root);
}
}
void searchContactByName(string name) {
Node* result = searchByName(root, name);
if (result != nullptr) {
cout << "Found: Name: " << result->name << ", Phone: " << result->phoneNumber << endl;
} else {
cout << "Contact not found." << endl;
}
}
void searchContactByPhone(string phoneNumber) {
if (phoneToNameMap.find(phoneNumber) != phoneToNameMap.end()) {
cout << "Found: Name: " << phoneToNameMap[phoneNumber] << ", Phone: " << phoneNumber << endl;
} else {
cout << "Contact not found." << endl;
}
}
void deleteContact(string name) {
root = deleteNode(root, name);
cout << "Contact '" << name << "' deleted (if it existed)." << endl;
}
};
int main() {
AddressBook addressBook;
while (true) {
cout << "\nAddress Book Menu:\n";
cout << "1. Add Contact\n";
cout << "2. View Contacts\n";
cout << "3. Search Contact by Name\n";
cout << "4. Search Contact by Phone Number\n";
cout << "5. Update Contact\n";
cout << "6. Delete Contact\n";
cout << "7. Quit\n";
cout << "Enter your choice: ";
int choice;
cin >> choice;
cin.ignore();
switch (choice) {
case 1: {
string name, phoneNumber;
cout << "Enter Name: ";
getline(cin, name);
cout << "Enter Phone Number: ";
getline(cin, phoneNumber);
while (phoneNumber.length() != 10) {
cout << "Not valid. \nPlease enter a valid 10-digit number: ";
getline(cin, phoneNumber);
}
addressBook.addContact(name, phoneNumber);
break;
}
case 2:
addressBook.viewContacts();
break;
case 3: {
string name;
cout << "Enter Name to Search: ";
getline(cin, name);
addressBook.searchContactByName(name);
break;
}
case 4: {
string phoneNumber;
cout << "Enter Phone Number to Search: ";
getline(cin, phoneNumber);
while (phoneNumber.length() != 10) {
cout << "Not valid. \nPlease enter a valid 10-digit number: ";
getline(cin, phoneNumber);
}
addressBook.searchContactByPhone(phoneNumber);
break;
}
case 5: {
string oldName, newName, newPhoneNumber;
cout << "Enter Name to Update: ";
getline(cin, oldName);
cout << "Enter New Name: ";
getline(cin, newName);
cout << "Enter New Phone Number: ";
getline(cin, newPhoneNumber);
while (newPhoneNumber.length() != 10) {
cout << "Not valid. \nPlease enter a valid 10-digit number: ";
getline(cin, newPhoneNumber);
}
addressBook.updateContact(oldName, newName, newPhoneNumber);
break;
}
case 6: {
string name;
cout << "Enter Name to Delete: ";
getline(cin, name);
addressBook.deleteContact(name);
break;
}
case 7:
cout << "Goodbye!" << endl;
return 0;
default:
cout << "Invalid choice. Please enter a valid option." << endl;
}
}
return 0;
}
