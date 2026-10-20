
#include <iostream>
using namespace std;

const int SIZE = 5;

class Deque
{
    int queue[SIZE];
    int front, rear, count;

public:
    Deque()
    {
        front = -1;
        rear = -1;
        count = 0;
    }

    void insertFront(int id)
    {
        if (count == SIZE)
        {
            cout << "Deque is full! Cannot insert request.\n";
            return;
        }

        if (count == 0)
        {
            front = rear = 0;
        }
        else
        {
            front = (front - 1 + SIZE) % SIZE;
        }

        queue[front] = id;
        count++;

        cout << "Request " << id << " inserted at the front.\n";
    }

    void insertRear(int id)
    {
        if (count == SIZE)
        {
            cout << "Deque is full! Cannot insert request.\n";
            return;
        }

        if (count == 0)
        {
            front = rear = 0;
        }
        else
        {
            rear = (rear + 1) % SIZE;
        }

        queue[rear] = id;
        count++;

        cout << "Request " << id << " inserted at the rear.\n";
    }

    void deleteFront()
    {
        if (count == 0)
        {
            cout << "Deque is empty! No request to remove.\n";
            return;
        }

        cout << "Request " << queue[front] << " removed from the front.\n";

        if (count == 1)
        {
            front = rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;
        }

        count--;
    }

    void deleteRear()
    {
        if (count == 0)
        {
            cout << "Deque is empty! No request to remove.\n";
            return;
        }

        cout << "Request " << queue[rear] << " removed from the rear.\n";

        if (count == 1)
        {
            front = rear = -1;
        }
        else
        {
            rear = (rear - 1 + SIZE) % SIZE;
        }

        count--;
    }

    void display()
    {
        if (count == 0)
        {
            cout << "No passenger requests waiting.\n";
            return;
        }

        cout << "Requests from front to rear: ";

        int i = front;

        for (int j = 0; j < count; j++)
        {
            cout << queue[i] << " ";
            i = (i + 1) % SIZE;
        }

        cout << endl;
    }
};

int main()
{
    Deque d;
    int choice, id;

    do
    {
        cout << "\n--- Train Station Passenger Management ---\n";
        cout << "1. Insert at Front\n";
        cout << "2. Insert at Rear\n";
        cout << "3. Remove from Front\n";
        cout << "4. Remove from Rear\n";
        cout << "5. Display Requests\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter passenger request ID: ";
            cin >> id;
            d.insertFront(id);
            break;

        case 2:
            cout << "Enter passenger request ID: ";
            cin >> id;
            d.insertRear(id);
            break;

        case 3:
            d.deleteFront();
            break;

        case 4:
            d.deleteRear();
            break;

        case 5:
            d.display();
            break;

        case 6:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}

