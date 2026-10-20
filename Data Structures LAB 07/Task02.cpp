
#include <iostream>
using namespace std;

const int SIZE = 5;

class CircularQueue
{
    int queue[SIZE];
    int front, rear, count;

public:
    CircularQueue()
    {
        front = -1;
        rear = -1;
        count = 0;
    }

    void enqueue(int packet)
    {
        if (count == SIZE)
        {
            cout << "Queue is full! Cannot add packet.\n";
            return;
        }

        if (front == -1)
        {
            front = 0;
        }

        rear = (rear + 1) % SIZE;
        queue[rear] = packet;
        count++;

        cout << "Packet " << packet << " added to the queue.\n";
    }

    void dequeue()
    {
        if (count == 0)
        {
            cout << "Queue is empty! No packet to transmit.\n";
            return;
        }

        cout << "Packet " << queue[front] << " transmitted.\n";

        if (count == 1)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;
        }

        count--;
    }

    void display()
    {
        if (count == 0)
        {
            cout << "No packets waiting for transmission.\n";
            return;
        }

        cout << "Packets waiting for transmission: ";

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
    CircularQueue q;
    int choice, packet;

    do
    {
        cout << "\n--- Network Packet Management ---\n";
        cout << "1. Insert Packet\n";
        cout << "2. Transmit Packet\n";
        cout << "3. Display Packets\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter packet ID: ";
            cin >> packet;
            q.enqueue(packet);
            break;

        case 2:
            q.dequeue();
            break;

        case 3:
            q.display();
            break;

        case 4:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}

