#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
string toLower(string);
string toLower(string str){
    for(auto& s:str){
        if(s>=65 && s<=90){
            s+=32;
        }
    }
    return str;
}
class Book{
    private:
        string title;
        string author;
        string ISBN;
        bool is_available=true;
    public:
        void setBook(string auth, string t, string isbn, bool avail){
            author=auth;
            title=t;
            ISBN=isbn;
            is_available=avail;
        }
        void showBook(){
            cout<<"Title: "<<title<<" || Author: "<<author<<" || ISBN: "<<ISBN<<" || Available: "<<(is_available ? "Yes" : "No");
            cout<<endl;
        }
        bool availability(){
            return is_available;
        }
        void setAvailability(bool avail){
            is_available=avail;
        }
        string getISBN(){
            return ISBN;
        }
        string getTitle(){
            return title;
        }
        string getAuthor(){
            return author;
        }
};
class Library{
    private:
        vector<Book> books;
    public:
        void addBook(const Book& book){
            books.push_back(book);
        }
        void displayBooks(){
            for(auto book: books){
                book.showBook();
            }
        }
        void removeBook(Book& book){
            auto it=remove_if(books.begin(),books.end(), [&](Book& b){return b.getISBN()==book.getISBN();});
            if(it!=books.end()){
                books.erase(it,books.end());
                cout<<"Book removed successfully"<<endl;
            }
            else{
                cout<<"Book not found"<<endl;
            }
        }
        Book* searchBookBytitle(const string& t){
            for(auto& book:books){
                if(toLower(t)==toLower(book.getTitle())){
                    return &book;
                }
            }
            return nullptr;
        }
        Book* searchBookByauthor(const string& auth){
            for(auto& book:books){
                if(toLower(auth)==toLower(book.getAuthor())){
                    return &book;
                }
            }
            return nullptr;
        }
        Book* searchBookByISBN(const string& ISBN){
            for(auto& book:books){
                if(ISBN==book.getISBN()){
                    return &book;
                }
            }
            return nullptr;
        }
};

class User{
    private:
        string userID;
        string name;
        vector<Book> borrowedBooks;
    public:
        void setUser(string id, string n){
            userID=id;
            name=n;
        }
        void showBorrowedBooks(){
            for(auto book:borrowedBooks){
                book.showBook();
            }
        }
        void borrowBook(Book& book){
            if(book.availability()){
                borrowedBooks.push_back(book);
                book.setAvailability(false);
                cout<<"Book borrowed successfully"<<endl;
            }
            else{
                cout<<"The Book "<<book.getTitle()<<" is not available"<<endl;
            }
        }
        void returnBook(Book& book){
            auto it = find_if(borrowedBooks.begin(), borrowedBooks.end(), [&](Book &b){return b.getISBN()==book.getISBN();});
            if(it!=borrowedBooks.end()){
                borrowedBooks.erase(it);
                book.setAvailability(true);
                cout<<"Book returned succesfully"<<endl;
            }
            else{
                cout<<"Book not found in borrowed books"<<endl;
            }
        }
};
int main(){
    Book b1;
    string author="Saurabh Shukla";
    string title="Concepts of C++";
    string ISBN="567014";
    bool is_available=true;
    b1.setBook(author, title, ISBN, is_available);
    Library l1;
    l1.addBook(b1);
    //l1.removeBook(b1);
    //l1.displayBooks();
    Book *b=l1.searchBookByauthor("saurabh shukla");
    b->showBook();
    User u1;
    u1.setUser("101","saurabh");
    u1.borrowBook(b1);
    u1.showBorrowedBooks();
    u1.returnBook(b1);
    u1.showBorrowedBooks();
    return 0;
}