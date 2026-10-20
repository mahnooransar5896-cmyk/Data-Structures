
#include <iostream>
using namespace std;

const int SIZE = 5;

class Patient
{
public:
    string id;
    int priority;
};

class PriorityQueue
{
    Patient patients[SIZE];
    int count;

public:
    PriorityQueue()
    {
        count = 0;
    }

    void enqueue(string id, int priority)
    {
        if (count == SIZE)
        {
            cout << "Queue is full! Cannot add more patients."<<endl;
            return;
        }

        patients[count].id = id;
        patients[count].priority = priority;
        count++;

        cout << "Patient " << id << " added successfully."<<endl;
    }

    void dequeue()
    {
        if (count == 0)
        {
            cout << "Queue is empty! No patients waiting."<<endl;
            return;
        }

        int highest = 0;

        for (int i = 1; i < count; i++)
        {
            if (patients[i].priority < patients[highest].priority)
            {
                highest = i;
            }
        }

        cout << "Patient " << patients[highest].id
             << " is being treated.\n";

        for (int i = highest; i < count - 1; i++)
        {
            patients[i] = patients[i + 1];
        }

        count--;
    }

    void display()
    {
        if (count == 0)
        {
            cout << "No patients waiting."<<endl;
            return;
        }

        cout << "\nWaiting Patients:\n";

        for (int i = 0; i < count; i++)
        {
            cout << "Patient ID: " << patients[i].id
                 << ", Priority: " << patients[i].priority << endl;
        }
    }
};

int main()
{
    PriorityQueue q;
    int choice, priority;
    string id;

    do
    {
        cout << "\n--- Hospital Emergency Department ---\n";
        cout << "1. Add Patient"<<endl;
        cout << "2. Treat Patient\n";
        cout << "3. Display Waiting Patients"<<endl;
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter patient ID: ";
            cin >> id;
            cout << "Enter priority (1 = highest): ";
            cin >> priority;
            q.enqueue(id, priority);
            break;

        case 2:
            q.dequeue();
            break;

        case 3:
            q.display();
            break;

        case 4:
            cout << "Exiting program."<<endl;
            break;

        default:
            cout << "Invalid choice!"<<endl;
        }

    } while (choice != 4);

    return 0;
}

