#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <ctime> //for updating current time 

using namespace std;

const int MAX_GENRES = 2;

struct Book
{
    string id, year, title, author, status;
    string genres[MAX_GENRES] ;
    int bM, bD, bY, rM, rD, rY;
    Book* left = NULL;
    Book* right = NULL;
};

struct Student
{
    string studNo, name;
    int token;
    Book* borrowedBook;
    Student* nxtS = NULL;
};

//global variable
Student* sHead = NULL;
Book* bRoot = NULL;//to store the address to root node

string toLowerCase(const string& str) //for compared use
{
  string result = str;
  transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

void createStudent()
{
  Student* newStudent = new Student;

  cout << "\nNEW STUDENT\n"
       << "\nEnter Admission No. in 7 digits."
       << "\nFor example: 0137436 " << endl;
  cin >> newStudent->studNo;
  while (newStudent->studNo.length() != 7 || !all_of(newStudent->studNo.begin(), newStudent->studNo.end(), ::isdigit)) 
  //make sure it won't crash when someone type in alphabet
  {
    cout << "Invalid input! Please enter a valid 7-digit admission no.: ";
    cin >> newStudent -> studNo;
  }

  cin.ignore();
  cout << "\nEnter Name of the Student: ";
  getline(cin >> ws, newStudent->name);//ws for reading space

  //assign variable
  newStudent -> token = 0;
  newStudent -> borrowedBook = NULL;

  cout << "\n\nStudent Record Created." << endl;

  // Link the new student to the list
  newStudent ->  nxtS = sHead;
  sHead = newStudent;
}

void selectGenres(Book* newBook)
{
  int genreChoice;
  cout << "\nSelect Genre:" << endl
       << "1. Fiction" << endl
       << "2. Non-Fiction" << endl
       << "Enter your choice: ";
  cin >> genreChoice;
  while(genreChoice < 1|| genreChoice > 2)
    {
      cout << "Invalid choice! Please enter a valid choice (1 or 2): ";
      cin >> genreChoice;
    }


  switch (genreChoice)
  {
    case 1:
        cout << "\nSelect Fiction Branch:" << endl
             << "1. History" << endl
             << "2. Mystery" << endl
             << "3. Horror" << endl;
        int fBranchChoice;
        cin >> fBranchChoice;
        while(fBranchChoice < 1 || fBranchChoice > 3)
          {
            cout << "Invalid choice! Please enter a valid choice (1, 2, or 3): ";
            cin >> fBranchChoice;
          }
        newBook -> genres[0] = "Fiction"; //if put on top then the program will not continue

        switch (fBranchChoice)
        {
        case 1: newBook -> genres[1] = "History"; break;
        case 2: newBook -> genres[1] = "Mystery"; break;
        case 3: newBook -> genres[1] = "Horror"; break;
        default: cout << "Invalid branch choice." << endl;
        }
        break;

    case 2:
        cout << "\nSelect Non-Fiction Branch:" << endl
            << "1. Computer Science" << endl
            << "2. Literature" << endl
            << "3. Science" << endl;
        int nBranchChoice;
        cin >> nBranchChoice;
        newBook -> genres[0] = "Non-Fiction";

        switch (nBranchChoice)
        {
        case 1: newBook -> genres[1] = "Computer Science"; break;
        case 2: newBook -> genres[1] = "Literature"; break;
        case 3: newBook -> genres[1] = "Science"; break;
        default: cout << "Invalid branch choice." << endl;
        }
        break;

    default:
        cout << "Invalid genre choice." << endl;
    }
}

Book* addNewBook(Book*& root, Book* newBook)
{
  //check is the tree is empty
  if (root == NULL)
  {
    root = newBook;
    return newBook;
  }

  //check if the new book is greater or less than the root
  if (newBook -> title.compare(root -> title) < 0)
  {
    root -> left = addNewBook(root -> left, newBook);
  }
  else
  {
    root -> right = addNewBook(root -> right, newBook);
  }
  return root;
}

void createRecord()
{
  Book* newBook = new Book;

  cout << "\nNEW BOOK\n"
       << "\nEnter 6 digits for Book's ID: " 
       << "\nFor example: 101001" << endl;
  cin >> newBook -> id;
  while (newBook -> id.length() != 6 || !all_of(newBook -> id.begin(), newBook -> id.end(), ::isdigit))
  {
    cout << "Invalid input! Please enter a valid 6-digit ID: ";
    cin >> newBook -> id;
  }

  cout << "\nEnter Published Year: ";
  cin >> newBook -> year;
  while (newBook -> year.length() != 4 || !all_of(newBook -> year.begin(), newBook -> year.end(), ::isdigit))
  {
    cout << "Invalid input! Please enter a valid 4-digit year: ";
    cin >> newBook -> year;
  }

  cin.ignore();
  cout << "\nEnter Title: ";
  getline(cin >> ws, newBook -> title); //ws for reading the space between

  cout << "\nEnter Author's Name: ";
  getline(cin >> ws, newBook -> author);

  selectGenres(newBook);

  //assign variable
  newBook -> status = "Available";
  newBook -> bD = 0;
  newBook -> bM = 0;
  newBook -> bY = 0;
  newBook -> rD = 0;
  newBook -> rM = 0;
  newBook -> rY = 0;
  newBook -> left = NULL;
  newBook -> right = NULL;

  cout << "\nBook Added Successfully!\n";
  addNewBook(bRoot,newBook);
}

void populate()
{
    Book* newBook1 = new Book{ "101001", "1997", "Memoirs of Geisha", "Arthur Golden", "Available", {"Fiction", "History"}, 0, 0, 0, 0, 0, 0};
    Book* newBook2 = new Book{ "102001", "1997", "Harry Potter", "JK Rowling", "Available", {"Fiction", "Mystery"}, 0, 0, 0, 0, 0, 0};
    Book* newBook3 = new Book{ "103001", "2011", "Dracula", "Bram Stoker", "Available", {"Fiction", "Horror"}, 0, 0, 0, 0, 0, 0};
    Book* newBook4 = new Book{ "201001", "2020", "Software Engineering", "Ali Selamat", "Available", {"Non-Fiction", "Mystery"}, 0, 0, 0, 0, 0, 0 };
    Book* newBook5 = new Book{ "202001", "1960", "Night", "Elie Wiesel", "Available", {"Non-Fiction", "Literature"}, 0, 0, 0, 0, 0, 0};
    Book* newBook6 = new Book{ "203001", "1859", "The Origin of Species", "Charles Darwin", "Available", {"Non-Fiction", "Science"}, 0, 0, 0, 0, 0, 0 };
    addNewBook(bRoot, newBook1);
    addNewBook(bRoot, newBook2);
    addNewBook(bRoot, newBook3);
    addNewBook(bRoot, newBook4);
    addNewBook(bRoot, newBook5);
    addNewBook(bRoot, newBook6);
}

Book* findMin(Book* root)//traverse the left child pointers until it reaches the leftmost node in the tree, which contains the minimum value.
{
  while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

//reason why don't delete with bookID is because they might be some displaying problem when deleting with bookID
Book* deleteBookHelper(Book* current, const string& searchTitle, bool& found)
{
    if (current == NULL)
    {
        return NULL;
    }

    // Check if the book is currently borrowed
    if (current->status == "Borrowed")
    {
        cout << "\nCannot delete the book with title '" << searchTitle << "' as it is currently borrowed!\n";
        return current;
    }

    string currentTitleLower = toLowerCase(current->title);
    string searchTitleLower = toLowerCase(searchTitle);

    if (currentTitleLower == searchTitleLower)
    {
        if (!found)
        {
            cout << "\nBook's ID: " << current->id
                << "\nPublished Year: " << current->year
                << "\nBook's Title: " << current->title
                << "\nAuthor's Name: " << current->author
                << "\nBook Genre: " << current->genres[0] << ", " << current->genres[1] << "\n";

            found = true;

            // Book with the specified title found, perform deletion
            cout << "\nBook with title '" << searchTitle << "' deleted successfully!\n";

            // Case 1: No child or one child
            if (current->left == NULL)
            {
                Book* temp = current->right;
                //delete current;
                return temp;
            }
            else if (current->right == NULL)
            {
                Book* temp = current->left;
                //delete current;
                return temp;
            }

            // Case 2: Two children
            Book* successor = findMin(current->right); // Find the inorder successor (smallest in the right subtree)

            // Copy the successor's data to this node
            current->id = successor->id;
            current->right = deleteBookHelper(current->right, successor->id, found); // Delete the successor
        }
    }

    current->left = deleteBookHelper(current->left, searchTitle, found);
    current->right = deleteBookHelper(current->right, searchTitle, found);

    return current;
}

void deleteBook(Book*& current)
{
    if (current == NULL)
    {
        cout << "The book list is empty" << endl;
        return;
    }

    string searchTitle;

    cout << "\nEnter the title of the book you want to delete: ";
    getline(cin >> ws, searchTitle);

    bool found = false;

    current = deleteBookHelper(current, searchTitle, found);

    if (!found)
    {
        cout << "No books found for the given title." << endl;
    }
}

void modifyBook(Book*& bRoot)
{
  string bookId;
  Book* ptr = bRoot;

  cout << "\nEnter Book's ID that you want to modify: ";
  cin >> bookId;
  while (bookId.length() != 6 || !all_of(bookId.begin(), bookId.end(), ::isdigit))
  {
    cout << "Invalid input! Please enter a valid 6-digit ID: ";
    cin >> bookId;
  }

  // Find the book to modify
  while (ptr != NULL)
  {
    if (bookId == ptr->id)
    {
      if (ptr->status == "Borrowed")
      {
        cout << "\nCannot modify the book with ID " << bookId << " as it is currently borrowed!\n";
        return;
      }

      cout << "\nEnter Updated Published Year: ";
      cin >> ptr->year;
      while (ptr->year.length() != 4 || !all_of(ptr->year.begin(), ptr->year.end(), ::isdigit))
      {
        cout << "Invalid input! Please enter a valid 4-digit year: ";
        cin >> ptr->year;
      }

      cin.ignore();
      cout << "\nEnter Updated Title: ";
      getline(cin >> ws, ptr->title);

      cout << "\nEnter Updated Author's Name: ";
      getline(cin >> ws, ptr->author);

      selectGenres(ptr);

      cout << "\nBook Information Updated Successfully!\n";
      return; // Exit the function after modifying the book
    }
    else if (bookId < ptr -> id)
    {
      ptr = ptr -> left; // Move to the left subtree
    }
    else
    {
      ptr = ptr->right; // Move to the right subtree
    }
  }

  // Book not found
  cout << "\nBook not found\n";
}

// Helper function for recursive search by title
void searchByTitleRecursive(Book* current, const string& searchTitle, bool& found)
{
  if (current == NULL)
  {
    //cout << "Book not found!" << endl; //it will keep repeating many time if put message here 
    return;
  }

  string currentTitleLower = toLowerCase(current -> title);
  string searchTitleLower = toLowerCase(searchTitle);

  if (currentTitleLower == searchTitleLower)
  {
    if (!found)
    {
      cout << "\nBook Found with the same titles:\n";
      found = true;
    }
    cout << "\nBook's ID: " << current -> id
         << "\nPublished Year: " << current -> year
         << "\nBook's Title: " << current -> title
         << "\nAuthor's Name: " << current -> author
         << "\nBook Genre: " << current -> genres[0] << ", " << current -> genres[1]
         << "\n--------------------------------------------------------\n";
  }

  // Continue searching in both subtrees to ensure more than one book with same name is found 
  searchByTitleRecursive(current -> left, searchTitle, found);
  searchByTitleRecursive(current -> right, searchTitle, found);
}

void searchByTitle(Book* current)
{
  if (current == NULL)
  {
    cout << "No books available for search!" << endl;
    return;
  }

  string searchTitle;
  cout << "Enter the title of the book you want to search: ";
  getline(cin >> ws, searchTitle);

  bool found = false;

  // Call the recursive search function
  searchByTitleRecursive(current, searchTitle, found);

  if (!found)
  {
    cout << "Book not found!" <<endl;
  }
}

//Helper function
void searchByYearRecursive(Book* current, const string& searchYear, bool& found)
{
  if (current == NULL)
  {
    return;
  }

  string currentYearLower = toLowerCase(current -> year);

  if (toLowerCase(searchYear) == currentYearLower)
  {
    if (!found)
    {
      cout << "\nBooks found with the same published year:\n";
      found = true;
    }
    cout << "\nBook's ID: " << current -> id
         << "\nPublished Year: " << current -> year
         << "\nBook's Title: " << current -> title
         << "\nAuthor's Name: " << current -> author
         << "\nBook Genre: " << current -> genres[0] << ", " << current -> genres[1]
         << "\n--------------------------------------------------------\n";
  }
  // Continue searching for more matching books in both subtrees
  searchByYearRecursive(current -> left, searchYear, found);
  searchByYearRecursive(current -> right, searchYear, found);
}

void searchByYear(Book* current)
{
  if (current == NULL)
  {
    cout << "No books available for search!" << endl;
    return;
  }

  string searchYear;
  cout << "\nEnter the Year of the book you want to search: ";
  cin >> searchYear;
  while (searchYear.length() != 4 || !all_of(searchYear.begin(), searchYear.end(), ::isdigit))
  {
    cout << "Invalid input! Please enter a valid 4-digit year: ";
    cin >> searchYear;
  }

  bool found = false;

  // Initiate the search by calling the recursive function
  searchByYearRecursive(current, searchYear, found);

  // Display a message if no books are found for the specified year
  if (!found)
  {
    cout << "No books found for the given year!" << endl;
  }
}

// Helper function for recursive search by genres
void searchByGenresRecursive(Book* current, const string& genreChoice, const string& branchChoice, bool& found)
{
  if (current == NULL)
  { 
    return;
  }

  if (current -> genres[0] == genreChoice && current->genres[1] == branchChoice)// Check if the book belongs to the selected genre and branch
  {
    if (!found)
    {
      cout << "\nBooks Found with same genre:\n";
      found = true;
    }
    cout << "\nBook ID: " << current -> id << endl
         << "Book Title: " << current -> title << endl
         << "Book Author: " << current -> author << endl;
  }
  // Recursively search in the left and right subtrees
  searchByGenresRecursive(current -> left, genreChoice, branchChoice, found);
  searchByGenresRecursive(current -> right, genreChoice, branchChoice, found);
}

void searchByGenres(Book* current)
{
  if (current == NULL)
  {  
    cout << "No books available for search!" << endl;
    return;
  }

  Book* newBook = new Book;
  selectGenres(newBook);

  string genreChoice = newBook->genres[0];
  string branchChoice = newBook->genres[1];
  bool found = false;

  searchByGenresRecursive(current, genreChoice, branchChoice, found);// Recursively search for books in the current subtree

  if (!found)
  {
    cout << "No books found for the given genre and branch." << endl;
  }
}

void searchBook()
{
  int choice;

  cout << "\nSearch Books:" 
       << "\n1. Search by Title" 
       << "\n2. Search by Year" 
       << "\n3. Search by Genres" << endl;
  cin >> choice;
  switch (choice)
  {
    case 1: searchByTitle(bRoot); break;
    case 2: searchByYear(bRoot); break;
    case 3: searchByGenres(bRoot); break;
    default: cout << "Invalid choice." << endl;
    return;
  }
}

void borrowBook()
{
    Student* newStudent = new Student;
    Book* bPtr = bRoot;
    Student* stdPtr = sHead;
    string bookId;
    char ans;

    cout << "\nEnter Admission No. to borrow: ";
    cin >> newStudent -> studNo;
    while (newStudent -> studNo.length() != 7 || !all_of(newStudent -> studNo.begin(), newStudent -> studNo.end(), ::isdigit))
    {
        cout << "Invalid input! Please enter a valid 7-digit ID: ";
        cin >> newStudent -> studNo;
    }

    // Find student
    while (stdPtr != NULL && stdPtr -> studNo != newStudent -> studNo)
    {
        stdPtr = stdPtr -> nxtS;
    }

    if (stdPtr == NULL)
    {
        cout << "Student not found";
        return;
    }

    cout << "\nEnter Book's ID to borrow: ";
    cin >> bookId;
    while (bookId.length() != 6 || !all_of(bookId.begin(), bookId.end(), ::isdigit))
    {
        cout << "Invalid input! Please enter a valid 6-digit ID: ";
        cin >> bookId;
    }

    while (bPtr != NULL)
    {
        if (bookId == bPtr->id)
        {
            if (bPtr->status == "Available")
            {
                cout << "\nBook's Title: " << bPtr->title
                    << "\nAuthor's Name: " << bPtr->author
                    << "\n\nPress Y to confirm borrowing or press N to cancel: ";
                cin >> ans;
                while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n')
                {
                    cout << "Invalid input! Please enter Y or N: ";
                    cin >> ans;
                }
                if (ans == 'Y' || ans == 'y')
                {
                   time_t now = time(0);
                   tm* currentTime = localtime(&now);
                   bPtr->bD = currentTime->tm_mday;
                   bPtr->bM = currentTime->tm_mon + 1;
                   bPtr->bY = currentTime->tm_year + 1900;

                    cout << "Borrowed date is " << bPtr->bD << "/" << bPtr->bM << "/" << bPtr->bY << endl;
                    cout << "Successfully borrowed." << endl;

                    bPtr -> status = "Borrowed";

                    // Update token and borrowedBook for the student
                    stdPtr -> token++;
                    stdPtr -> borrowedBook = bPtr; // Update the borrowed book pointer
                    return;
                }
                else
                {
                    cout << "Borrowing cancelled." << endl;
                    return;
                }
            }
            else
            {
                cout << "Book is already borrowed." << endl;
                return;
            }
        }
        bPtr = bPtr -> left;
    }
    cout << "Book Not Found!\n";
}

void returnBook()
{
    string studId;
    string bookId;
    Student* stdPtr = sHead;

    cout << "\nEnter Student ID to return book: ";
    cin >> studId;
    while (studId.length() != 7 || !all_of(studId.begin(), studId.end(), ::isdigit))
    {
        cout << "Invalid input! Please enter a valid 7-digit ID: ";
        cin >> studId;
    }

    // Find the student
    while (stdPtr != NULL && stdPtr -> studNo != studId)
    {
        stdPtr = stdPtr->nxtS;
    }

    if (stdPtr == NULL)
    {
        cout << "Student not found" << endl;
        return;
    }

    // Check if the student has borrowed any book
    if (stdPtr->borrowedBook == NULL)
    {
        cout << "No book to return. " << stdPtr->name << " has not borrowed any book." << endl;
        return;
    }

    // Find the borrowed book
    Book* borrowedBook = stdPtr -> borrowedBook;

    cout << "\nEnter Book's ID to return: ";
    cin >> bookId;
    while (bookId.length() != 6 || !all_of(bookId.begin(), bookId.end(), ::isdigit))
    {
        cout << "Invalid input! Please enter a valid 6-digit ID: ";
        cin >> bookId;
    }

    // Find the book
    Book* bPtr = bRoot;
    while (bPtr != NULL && bPtr->id != bookId)
    {
       bPtr = bPtr -> left;
    }

    if (bPtr == NULL)
    {
        cout << "Book with ID " << bookId << " not found!\n";
        return;
    }

    // Update return date
    time_t now = time(0);
    tm* currentTime = localtime(&now);

    bPtr->rD = currentTime -> tm_mday;
    bPtr->rM = currentTime -> tm_mon + 1;
    bPtr->rY = currentTime -> tm_year + 1900;

    cout << "Return date for Book ID " << bPtr -> id << " is " << bPtr -> rD << "/" << bPtr -> rM << "/" << bPtr -> rY << endl;
    cout << "Book returned successfully!\n";

    // Update book status and student's token
    borrowedBook -> status = "Available";
    stdPtr -> token--; // Decrement token to indicate the book return
}

void displayBookReport()
{
    Book* bPtr = bRoot;
    Student* stdPtr = sHead;

    cout << "Books that have been borrowed: " << endl;

    while (bPtr != NULL && stdPtr != NULL)
    {
        if (bPtr->status == "Borrowed")
        {
            cout << "\nBook ID: " << bPtr->id
                << "\nBook Title: " << bPtr->title
                << "\nBook Author: " << bPtr->author
                << "\nBorrowed by: " << stdPtr->studNo << " " << stdPtr->name
                << "\nBorrowed Date: " << bPtr->bD << "/" << bPtr->bM << "/" << bPtr->bY
                << "\nReturn Date: " << bPtr->rD << "/" << bPtr->rM << "/" << bPtr->rY << endl
                << "---------------------------------------------------------------------------\n";
        }
        bPtr = bPtr->left;
        stdPtr = stdPtr->nxtS;
    }
}

void displayBookListHelper(Book* root)
{
  if (root != NULL)
  {
    displayBookListHelper(root->left);

    cout << setw(10) << left << root->id
         << setw(10) << left << "| " + root->year
         << setw(30) << left << "| " + root->title
         << setw(20) << left << "| " + root->author
         << setw(30) << left << "| " + root->genres[0] + ", " + root->genres[1] 
         << setw(20) << left << "| " + root->status << endl;
    displayBookListHelper(root->right);
  }
}

void displayBookList()
{
  if (bRoot == NULL)
  {
    cout << "No books available!\n";
  }
  else
  {
    cout << setfill('-') << setw(135) << "-" << setfill(' ') << endl
         << setw(10) << left << "ID"
         << setw(10) << left << "| Year"
         << setw(30) << left << "| Title"
         << setw(20) << left << "| Author"
         << setw(30) << left << "| Genres"
         << setw(20) << left << "| Status" << endl
         << setfill('-') << setw(135) << "-" << setfill(' ') << endl;

    displayBookListHelper(bRoot);

    cout << setfill('-') << setw(135) << "-" << setfill(' ') << endl;
  }
}

void displayStudentList()
{
  Student* ptr = sHead;

  while (ptr != NULL)
  {
    cout << "\nAdmission no. : " << ptr->studNo
         << "\nStudent Name : " << ptr->name
         << "\nNo of Book issued : " << ptr->token
         << "\n----------------------------------" << endl;
    if (ptr->token > 0)
    {
      cout << "\nBook Id: " << ptr->borrowedBook->id << endl;
      ptr->token++;
    }
    ptr = ptr->nxtS;
  }
}

int main()
{
    int choice;
    bool flag = true;

    populate();

    do
    {
        cout << "\n\n============================================="
            << "\n\n==========Library Management System=========="
            << "\n\n============================================="
            << "\n1. Add New Student" << endl
            << "2. Add New Book" << endl
            << "3. Delete Book" << endl
            << "4. Modify Book" << endl
            << "5. Search Book" << endl
            << "6. Borrow Book" << endl
            << "7. Return Book" << endl
            << "8. Display Book Report" << endl
            << "9. Display Book List" << endl
            << "10. Display Student List" << endl
            << "11. Exit" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1: createStudent(); break;
        case 2: createRecord(); break;
        case 3: deleteBook(bRoot); break;
        case 4: modifyBook(bRoot); break;
        case 5: searchBook(); break;
        case 6: borrowBook(); break;
        case 7: returnBook(); break;
        case 8: displayBookReport(); break;
        case 9: displayBookList(); break;
        case 10: displayStudentList(); break;
        case 11: flag = false; break;
        default:
            cout << "wrong number";
            flag = true;
        }
    } while (flag);

    return 0;
}