#include <iostream>
#include <vector>
#include <string>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author) : title(title), author(author) {   }
};

class BookManager 
{
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) 
    {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const 
    {
        if (books.empty()) 
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) 
        { 
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    void searchByTitle(const string& title) const 
    {
        for (const auto& book : books) 
        {
            if (book.title == title) 
            {
                cout << "책을 찾았습니다: " << book.title << " by " << book.author << endl;
                break; // 책을 찾으면 루프 종료
            }
        }
	}

    void searchByAuthor(const string& author) const 
    {
        for (const auto& book : books) 
        {
            if (book.author == author) 
            {
                cout << "책을 찾았습니다: " << book.title << " by " << book.author << endl;
                break; // 책을 찾으면 루프 종료
            }
        }
	}

};

int main() {
    BookManager manager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) 
    {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 종료" << endl; // 프로그램 종료
		cout << "4. 책 검색" << endl; // 책 제목이나 저자명으로 책 검색 기능 추가
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) 
        {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
        }
        else if (choice == 2) 
        {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3) 
        {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else if (choice == 4) 
        {
            // 4번 선택: 책 검색
            // 사용자로부터 검색할 책 제목이나 저자명을 입력받아 해당 책을 검색합니다.
			int  booksearchChoice = 0;

			cout << "책 검색 기능입니다." << endl;
			cout << "책 제목으로 검색을 원하면 1, 저자명으로 검색을 원하면 2를 입력하세요." << endl;
			cin >> booksearchChoice;

            string searchTerm;
            cout << "검색할 책 제목 또는 저자명: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, searchTerm); // 검색어 입력 (공백 포함)
            
            // 제목으로 검색
            if (booksearchChoice == 1)
            {
                manager.searchByTitle(searchTerm);
            }
            // 저자명으로 검색
            else if (booksearchChoice == 2)
            {
                manager.searchByAuthor(searchTerm);
            }
		}
        else 
        {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}
