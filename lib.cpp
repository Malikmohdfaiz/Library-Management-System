#include<iostream>
#include<unordered_map>
#include<string>
#include<unordered_set>
using namespace std;

class Book{
    public:
    string title;
    string author;
    string isbn;
    int pubyear;
    int num=0;
    Book(){

    }
    Book(string tit, string auth,string isb,int year, int num){
        this->title=tit;
        this->author=auth;
        this->isbn=isb;
        this->pubyear=year;
        this->num=num;

    }

};
class User{
    public:
    string username;
    unordered_set<string> borrowed;// Isbns of borrowed books
    User(){}
    User(string name){
        this->username=name;
    }
};
class library{
    public:
    
    unordered_map<string,Book> books; //isbn as key
    unordered_map<string,User> users;// Username as the key
    void addBook(const Book &b){
        books[b.isbn]=b;
    }
    // note adding more books noot new books;
    void addcopies(const string & isbn, int n){
        Book & book=books[isbn];
        book.num+=n;
    }
    // adding user
    void adduser(const User& user){
        users[user.username]=user;
        cout<<"USer Added: "<<user.username<<endl;
    }
    void borrowbook(const string & isbn,const string & username){
        if(books.find(isbn)!=books.end() && users.find(username)!=users.end()){
            Book & book=books[isbn];
            User & user=users[username];

            if(book.num>0 ){
                if(user.borrowed.find(isbn)==user.borrowed.end()){
                    user.borrowed.insert(isbn);
                    book.num--;
                   cout<<"borrowed "<<endl;

                }
                else {
                    cout<<"already borrowed , only one book is allowed "<<endl;
                }
                
            }
            else{
                cout<<" books out of stock "<<endl;
            }

        }
        else{
            cout<<"book or user not found "<<endl;
        }
    }

    void returnbook(const string & isbn, const string & username){

        if(books.find(isbn)!=books.end() && users.find(username)!=users.end()){
        
            User & user=users[username];
            Book & book=books[isbn];
            if(user.borrowed.find(isbn)!=user.borrowed.end()){
                book.num++;
                user.borrowed.erase(isbn);

            }
            else{
                cout<<"book is not borrowed by "<<username<<endl;
            }
            


        }
        else{
            cout<<"book or user is not found ";
        }
    }

    void searchbook(const string &isbn){

        if(books.find(isbn)==books.end()){
            cout<<"sorry , Book is not availaible";
        }
        else{
            cout<<"available :"<<endl;
            Book b=books[isbn];
            cout<<"ISBN:-"<<b.isbn<<endl;
            cout<<"Author:-"<<b.author<<endl;
            cout<<"Publication year:-"<<b.pubyear<<endl;
            cout<<"title:-"<<b.title<<endl;
            cout<<"copies:-"<<b.num<<endl;

        }
    }
        void searchbyauthor(const string & tit){
            bool present=false;
            for(auto a: books){
                Book b=a.second;
                if(b.title==tit){
                     cout<<"available :"<<endl;
                Book b=books[a.first];
            cout<<"ISBN:-"<<b.isbn<<endl;
            cout<<"Author:-"<<b.author<<endl;
            cout<<"Publication year:-"<<b.pubyear<<endl;
            cout<<"title:-"<<b.title<<endl;
            present=true;
                 
                }
            }
            if(present==false){
                cout<<"No books from "<<tit<<endl;
            }
        }
        
    
    void delbook(const string & isbn){
        if(books.find(isbn)==books.end()){
            cout<<"Not available"<<endl;
            return ;
        }
        else{
            books.erase(isbn);
            cout<<"book with ISBN "<<isbn<<" have been deleted"<<endl;
        }
    }
    void booksbyaut(const string & aut){
        bool present=false;
        for(auto a:books){
            if(a.second.author==aut){
                cout<<a.second.title<<endl;
                present=true;
                
            }
        }
        if(present==false){
            cout<<"No books found ";
        }

    }
    void booksborroby(const string & username){
        int count=0;
        if(users.find(username)!=users.end()){
        User &user=users[username];
        for (auto a: user.borrowed){
            count++;
            cout<<a<<" ";
        }
        }
        else{
            cout<<"no user found ";
            return;
        }
        if(count==0){
            cout<<"not borrowed ";

        }
        cout<<endl;
    }
    void booksborrowhistory(){
        for(auto a: users){
            cout<<a.first<<"->";
            for(auto b: a.second.borrowed){
                cout<<b<<" ";
            }
            cout<<endl;
        }
    }

};



int main(){
    library lib;

    
    lib.addBook(Book("english", "Malik", "200", 2001,4));
    lib.addBook(Book("maths", "sanib", "201", 1949,3));
    lib.addBook(Book("urdu", "kaif", "202", 1960,2));

   
  //  lib.addcopies("202",3);
    lib.adduser(User("faiza"));
    lib.adduser(User("sanib"));
    lib.adduser(User("kaif"));
    
    lib.borrowbook("200","faiza");
    lib.borrowbook("201","sanib");
    lib.borrowbook("202","kaif");
    
    
    lib.booksborrowhistory();
    
}





