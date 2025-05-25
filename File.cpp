#include <string>
#include <iostream>
using namespace std;

// ��������� ��� �������� ������ � ����
struct Tour {
    int Id;             // ���������� ������������� ����
    string Name;        // �������� ����
    string Country;     // ������ ���������� ����
    int PlacesCount;    // ���������� ���� � ����
    string Fio;         // ��� ��������������
};

// ���� ����������� ������
struct Node {
    Tour Value;         // ������ ����
    Node* nextNode;     // ��������� �� ��������� ����
    Node* previousNode; // ��������� �� ���������� ����

    // ����������� ����
    Node(Tour val) : Value(val), nextNode(nullptr), previousNode(nullptr) {}
};

// ���������� ������
struct LinkedList {
    Node* first;    // ��������� �� ������ ����
    Node* last;     // ��������� �� ��������� ����

    // ����������� ������
    LinkedList() : first(nullptr), last(nullptr) {}

    // �������� �� ������� ������
    bool isEmpty() {
        return first == nullptr;
    }

    // ����� ���� ����� � ������
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

    // ���������� ���� � ����������� ���������� �� ID
    void insertSorted(Tour value) {
        Node* newNode = new Node(value);

        // ���� ������ ����
        if (isEmpty()) {
            first = last = newNode;
            return;
        }

        // ������� � ������ (���� ����� ID ������ �������)
        if (value.Id < first->Value.Id) {
            newNode->nextNode = first;
            first->previousNode = newNode;
            first = newNode;
            return;
        }

        // ������� � ����� (���� ����� ID ������ ����������)
        if (value.Id > last->Value.Id) {
            last->nextNode = newNode;
            newNode->previousNode = last;
            last = newNode;
            return;
        }

        // ������� � ��������
        Node* current = first;
        while (current && current->Value.Id < value.Id) {
            current = current->nextNode;
        }

        // ���� ����� ������� � ����� �� ID
        if (current && current->Value.Id == value.Id) {
            delete newNode;
            return;
        }

        // ������� ����� current
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
            cin.ignore(); // ������� ������

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