#include <string>
#include <iostream>
using namespace std;

// Структура для хранения данных о туре
struct Tour {
    int Id;             // Уникальный идентификатор тура
    string Name;        // Название тура
    string Country;     // Страна проведения тура
    int PlacesCount;    // Количество мест в туре
    string Fio;         // ФИО ответственного
};

// Узел двусвязного списка
struct Node {
    Tour Value;         // Данные тура
    Node* nextNode;     // Указатель на следующий узел
    Node* previousNode; // Указатель на предыдущий узел

    // Конструктор узла
    Node(Tour val) : Value(val), nextNode(nullptr), previousNode(nullptr) {}
};

// Двусвязный список
struct LinkedList {
    Node* first;    // Указатель на первый узел
    Node* last;     // Указатель на последний узел

    // Конструктор списка
    LinkedList() : first(nullptr), last(nullptr) {}

    // Проверка на пустоту списка
    bool isEmpty() {
        return first == nullptr;
    }

    // Вывод всех туров в списке
    void print() {
        if (isEmpty()) {
            return;
        }

        Node* current = first;
        while (current) {
            cout << "ID: " << current->Value.Id << "\n";
            cout << "Name: " << current->Value.Name << "\n";
            cout << "Country: " << current->Value.Country << "\n";
            cout << "PlacesCount: " << current->Value.PlacesCount << "\n";
            cout << "FIO: " << current->Value.Fio << "\n\n";
            current = current->nextNode;
        }
    }

    // Добавление тура с сохранением сортировки по ID
    void insertSorted(Tour value) {
        Node* newNode = new Node(value);

        // Если список пуст
        if (isEmpty()) {
            first = last = newNode;
            return;
        }

        // Вставка в начало (если новый ID меньше первого)
        if (value.Id < first->Value.Id) {
            newNode->nextNode = first;
            first->previousNode = newNode;
            first = newNode;
            return;
        }

        // Вставка в конец (если новый ID больше последнего)
        if (value.Id > last->Value.Id) {
            last->nextNode = newNode;
            newNode->previousNode = last;
            last = newNode;
            return;
        }

        // Вставка в середину
        Node* current = first;
        while (current && current->Value.Id < value.Id) {
            current = current->nextNode;
        }

        // Если нашли элемент с таким же ID
        if (current && current->Value.Id == value.Id) {
            delete newNode;
            return;
        }

        // Вставка перед current
        newNode->nextNode = current;
        newNode->previousNode = current->previousNode;
        current->previousNode->nextNode = newNode;
        current->previousNode = newNode;
    }
};

int main() {
    LinkedList tourList;
    Tour newTour;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add tour\n";
        cout << "2. Show all\n";
        cout << "0. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Tour Id: ";
            cin >> newTour.Id;
            cin.ignore(); // Очистка буфера

            cout << "Tour name: ";
            getline(cin, newTour.Name);

            cout << "Tour Country: ";
            getline(cin, newTour.Country);

            cout << "Places count: ";
            cin >> newTour.PlacesCount;
            cin.ignore();

            cout << "FIO: ";
            getline(cin, newTour.Fio);

            tourList.insertSorted(newTour);
            break;
        }
        case 2:
            tourList.print();
            break;
        case 0:
            break;
        default:
            cout << "Wrong command!\n";
        }
    } while (choice != 0);

    return 0;
}