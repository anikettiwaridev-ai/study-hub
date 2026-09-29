#include <iostream>
#include <string>
using namespace std;

class Book {
    int bookID;
    string title;
    bool available;
    int timesIssued;
    double fine;
    int issueDay;                         // day number the book went out

public:
    static const int ALLOWED_DAYS = 14;   // free borrowing period
    static const int FINE_PER_DAY = 2;    // rupees per late day

    Book(int id, string t) {
        bookID = id; title = t;
        available = true; timesIssued = 0; fine = 0; issueDay = 0;
    }

    bool issue(int day) {
        if (!available) {                 // refuse a book that is already out
            cout << "  \"" << title << "\" is already issued" << endl;
            return false;
        }
        available = false;
        issueDay = day;
        timesIssued++;
        cout << "  Issued \"" << title << "\" on day " << day << endl;
        return true;
    }

    double calculateFine(int returnDay) const {
        int late = returnDay - issueDay - ALLOWED_DAYS;
        return late > 0 ? late * FINE_PER_DAY : 0;
    }

    void giveBack(int day) {
        if (available) { cout << "  \"" << title << "\" was not issued" << endl; return; }
        double f = calculateFine(day);
        fine += f;
        available = true;
        cout << "  Returned \"" << title << "\" on day " << day << ", fine " << f << endl;
    }

    int getTimesIssued() const { return timesIssued; }
    double getFine() const { return fine; }
    string getTitle() const { return title; }
};

int main() {
    Book books[3] = { Book(1, "C++ Primer"), Book(2, "Clean Code"), Book(3, "CLRS") };

    cout << "Transactions:" << endl;
    books[0].issue(1);  books[0].issue(2);   books[0].giveBack(10);   // on time
    books[0].issue(12); books[0].giveBack(30);                        // 4 days late
    books[1].issue(3);  books[1].giveBack(27);                        // 10 days late
    books[2].issue(5);  books[2].giveBack(12);
    books[0].issue(31); books[0].giveBack(40);

    int most = 0, maxFine = 0;
    for (int i = 1; i < 3; i++) {
        if (books[i].getTimesIssued() > books[most].getTimesIssued()) most = i;
        if (books[i].getFine() > books[maxFine].getFine()) maxFine = i;
    }
    cout << "Most issued: " << books[most].getTitle() << " (" << books[most].getTimesIssued() << " times)" << endl;
    cout << "Maximum fine: " << books[maxFine].getTitle() << " (Rs " << books[maxFine].getFine() << ")" << endl;
    return 0;
}
