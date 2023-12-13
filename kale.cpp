#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Expense
{
  int year;
  int month;
  int day;
  string description;
  double amount;
};

Expense *expenses = nullptr;
int numExpenses = 0;


void loadExpenses(const string &filename);
void saveExpenses(const string &filename);
void addExpense();
void viewExpenses();
double calculateTotalExpense();
void searchExpensesByYear(int searchYear);
void displayMenu();

void loadExpenses(const string &filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cout << "Error: Could not open file" << endl;
    return;
  }

  string line, description;
  double amount;
  int year, month, day;

  while (getline(file, line))
  {
    stringstream ss(line);
    ss >> year >> month >> day >> amount;
    ss.ignore();
    getline(ss, description, '\"');
    getline(ss, description, '\"');

    Expense *temp = new Expense[numExpenses + 1];
    for (int i = 0; i < numExpenses; ++i)
    {
      temp[i] = expenses[i];
    }
    temp[numExpenses] = {year, month, day, description, amount};

    delete[] expenses;
    expenses = temp;
    numExpenses++;
  }
  file.close();
}

void saveExpenses(const string &filename)
{
  ofstream file(filename);
  if (!file.is_open())
  {
    cout << "Error: Could not open file for writing" << endl;
    return;
  }

  for (int i = 0; i < numExpenses; ++i)
  {
    file << expenses[i].year << " " << expenses[i].month << " " << expenses[i].day
         << " \"" << expenses[i].description << "\" " << expenses[i].amount << endl;
  }
  file.close();
}

void addExpense()
{
  int year, month, day;
  string description;
  double amount;
  int i;
  cout << "Enter year: ";
  cin >> year;

  cout << "Enter month: ";
label:
  {
    cin >> month;
  }
  if (month > 12)
  {
    cout << "Entered Month is invalid.\nEnter Month: ";
    goto label;
  }
  cout << "Enter day: ";
label1:
  cin >> day;
  if (day > 31)
  {
    cout << "Entered Day is invalid.\nEnter Day: ";
    goto label1;
  }
  cout << "Enter description: ";
  cin.ignore();
  getline(cin, description);
  cout << "Enter amount: ";
  cin >> amount;

  Expense *temp = new Expense[numExpenses + 1];
  for (int i = 0; i < numExpenses; ++i)
  {
    temp[i] = expenses[i];
  }
  temp[numExpenses] = {year, month, day, description, amount};

  delete[] expenses;
  expenses = temp;
  numExpenses++;
}

void viewExpenses()
{
  if (numExpenses == 0)
  {
    cout << "No expenses found!" << endl;
    return;
  }

  for (int i = 0; i < numExpenses; ++i)
  {
    cout << expenses[i].year << "-" << expenses[i].month << "-" << expenses[i].day
         << ": " << expenses[i].description << " - ₹" << expenses[i].amount << endl;
  }
}

double calculateTotalExpense()
{
  double total = 0;
  for (int i = 0; i < numExpenses; ++i)
  {
    total += expenses[i].amount;
  }
  return total;
}

void searchExpensesByYear(int searchYear)
{
  bool found = false;

  for (int i = 0; i < numExpenses; ++i)
  {
    if (expenses[i].year == searchYear)
    {
      found = true;
      cout << expenses[i].year << "-" << expenses[i].month << "-" << expenses[i].day
           << ": " << expenses[i].description << " - ₹" << expenses[i].amount << endl;
    }
  }

  if (!found)
  {
    cout << "No expenses found for the year " << searchYear << endl;
  }
}

void displayMenu()
{
  cout << "\nMonthly Expense Tracker" << endl;
  cout << "1. Add Expense" << endl;
  cout << "2. View Expenses" << endl;
  cout << "3. Search Expenses by Year" << endl; // New option
  cout << "4. Total Expense" << endl;
  cout << "5. Quit" << endl;
  cout << "Enter your choice: ";
}

int main()
{
  const string filename = "expenses.txt";
  loadExpenses(filename);

  int choice;
  do
  {
    displayMenu();
    cin >> choice;

    switch (choice)
    {
    case 1:
      addExpense();
      saveExpenses(filename);
      break;
    case 2:
      viewExpenses();
      break;
    case 3:
      int searchYear;
      cout << "Enter the year to search: ";
      cin >> searchYear;
      searchExpensesByYear(searchYear);
      break;
    case 4:
      cout << "Total expense: ₹" << calculateTotalExpense() << endl;
      break;
    case 5:
      cout << "Exiting program." << endl;
      break;
    default:
      cout << "Invalid choice!" << endl;
    }
  } while (choice != 5);

  
  delete[] expenses;

  return 0;
}
