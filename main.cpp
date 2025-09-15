#pragma warning(disable:4996)
#include <iostream>
#include<vector>
#include <string>
#include <ctime>
using namespace std;
class clsBook {
private:
	string Title;
	string Author;
	string ISBN;
	bool Available = true;
public:
	clsBook() {}
	clsBook(string title, string author, string isbn) {
		Title = title;
		Author = author;

		ISBN = isbn;
	}
	string getTitle() {
		return Title;
	}
	string getAuthor() {
		return Author;
	}

	string getISBN() {
		return ISBN;
	}
	void setTitle(string title) {
		Title = title;
	}
	void setAuthor(string author) {
		Author = author;
	}

	void setISBN(string isbn) {
		ISBN = isbn;
	}
	bool isAvailable() {
		return Available;
	}
	void setAvailable(bool available) {
		Available = available;
	}
	void printInfo() {
		cout << "Title: " << Title << endl;
		cout << "Author: " << Author << endl;
		cout << "ISBN: " << ISBN << endl;
		cout << "Available: " << (Available ? "Yes" : "No") << endl;
	}
};
class clsUser {
private:
	string Name;
	string UserID;
	vector<clsBook> BorrowedBooks;
public:
	clsUser(string name, string userID) {
		Name = name;
		UserID = userID;
	}
	string getName() {
		return Name;
	}
	string getUserID() {
		return UserID;
	}
	void setName(string name) {
		Name = name;
	}
	void setUserID(string userID) {
		UserID = userID;
	}
	void borrowBook(clsBook& book) {
		if (book.isAvailable()) {
			BorrowedBooks.push_back(book);
			book.setAvailable(false);
			cout << Name << " borrowed " << book.getTitle() << endl;
		}
		else {
			cout << book.getTitle() << " is not available." << endl;
		}
	}
	void returnBook(clsBook& book) {
		for (size_t i = 0; i < BorrowedBooks.size(); i++) {
			if (BorrowedBooks[i].getISBN() == book.getISBN()) {
				BorrowedBooks.erase(BorrowedBooks.begin() + i);
				book.setAvailable(true);
				cout << Name << " returned " << book.getTitle() << endl;
				return;
			}
		}
		cout << Name << " did not borrow " << book.getTitle() << endl;
	}

	void printInfo() {
		cout << "Name: " << Name << endl;
		cout << "User ID: " << UserID << endl;
		cout << "Borrowed Books: " << endl;
		for (clsBook& book : BorrowedBooks) {
			book.printInfo();
			cout << endl;
		}
	}
};
class Library {
private:
	vector<clsBook> Books;
	vector<clsUser> Users;
public:
	void addBook(clsBook book) {
		Books.push_back(book);
	}
	void addUser(clsUser user) {
		Users.push_back(user);
	}
	void DeleteUser(string userID) {
		for (size_t i = 0; i < Users.size(); i++) {
			if (Users[i].getUserID() == userID) {
				Users.erase(Users.begin() + i);
				cout << "User with ID " << userID << " deleted." << endl;
				return;
			}
		}
		cout << "User with ID " << userID << " not found." << endl;
	}
	void deleteBook(string isbn) {
		for (size_t i = 0; i < Books.size(); i++) {
			if (Books[i].getISBN() == isbn) {
				Books.erase(Books.begin() + i);
				cout << "Book with ISBN " << isbn << " deleted." << endl;
				return;
			}
		}
		cout << "Book with ISBN " << isbn << " not found." << endl;
	}
	void printBooks() {
		for (clsBook& book : Books) {
			book.printInfo();
			cout << endl;
		}
	}
	void printUsers() {
		for (clsUser& user : Users) {
			user.printInfo();
			cout << endl;
		}
	}
	void Borrow(string UserId, string isbn) {
		for (clsUser& user : Users) {
			if (user.getUserID() == UserId) {
				for (clsBook& book : Books) {
					if (book.getISBN() == isbn) {
						if (book.isAvailable()) {
							user.borrowBook(book);
							return;
						}
						else {
							cout << book.getTitle() << " is not available." << endl;
							return;
						}

					}
				}
				cout << "Book with ISBN " << isbn << " not found." << endl;
				return;
			}
		}
		cout << "User with ID " << UserId << " not found." << endl;
	}
	void returnBook(string UserId, string isbn) {
		for (clsUser& user : Users) {
			if (user.getUserID() == UserId) {
				for (clsBook& book : Books) {
					if (book.getISBN() == isbn) {
						book.setAvailable(true);
						user.returnBook(book);
						return;
					}
				}
				cout << "Book with ISBN " << isbn << " not found." << endl;
				return;
			}
		}
		cout << "User with ID " << UserId << " not found." << endl;
	}




};
void Menue() {
	cout << "1. Add Book" << endl;
	cout << "2. Add User" << endl;
	cout << "3. Delete Book" << endl;
	cout << "4. Delete User" << endl;
	cout << "5. Borrow Book" << endl;
	cout << "6. Return Book" << endl;
	cout << "7. Print Books" << endl;
	cout << "8. Print Users" << endl;
	cout << "9. Exit" << endl;
}
int GetOption() {
	int option;
	cout << "Enter option: ";
	cin >> option;
	return option;
}


int main()
{
	Library library;
	int option;
	do {
		Menue();
		option = GetOption();
		switch (option) {
		case 1: {
			string title, author, isbn;
			cout << "Enter title: ";
			cin >> ws;
			getline(cin, title);
			cout << "Enter author: ";
			getline(cin, author);
			cout << "Enter ISBN: ";
			getline(cin, isbn);
			clsBook book(title, author, isbn);
			library.addBook(book);
			break;
		}
		case 2: {
			string name, userID;
			cout << "Enter name: ";
			cin >> ws;
			getline(cin, name);
			cout << "Enter User ID: ";
			getline(cin, userID);
			clsUser user(name, userID);
			library.addUser(user);
			break;
		}
		case 3: {
			string isbn;
			cout << "Enter ISBN: ";
			cin >> ws;
			getline(cin, isbn);
			library.deleteBook(isbn);
			break;
		}
		case 4: {
			string userID;
			cout << "Enter User ID: ";
			cin >> ws;
			getline(cin, userID);
			library.DeleteUser(userID);
			break;
		}
		case 5: {
			string userID, isbn;
			cout << "Enter User ID: ";
			cin >> ws;
			getline(cin, userID);
			cout << "Enter ISBN: ";
			getline(cin, isbn);
			library.Borrow(userID, isbn);
			break;
		}
		case 6: {
			string userID, isbn;
			cout << "Enter User ID: ";
			cin >> ws;
			getline(cin, userID);
			cout << "Enter ISBN: ";
			getline(cin, isbn);
			library.returnBook(userID, isbn);
			break;
		}
		case 7: {
			library.printBooks();
			break;
		}
		case 8: {
			library.printUsers();
			break;
		}
		case 9: {
			cout << "Exiting..." << endl;
			break;
		}
		default: {
			cout << "Invalid option." << endl;
			break;
		}
		}
	} while (option != 9);




	return 0;
}

