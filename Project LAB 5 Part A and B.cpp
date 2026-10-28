#include <iostream>
#include <string>
#include <utility>
using namespace std;

// ========================================
// PART B: HOSPITAL PATIENT MANAGEMENT
// ========================================

// 1. Self-referential node structure

struct PatientNode
{
    int patientID;
    string name;
    int age;
    string condition;
    PatientNode* next;
};

// ========================================
// 2. LINKED LIST CLASS
// ========================================

class LinkedList
{
private:
    PatientNode* head;
    int count;

    // Prevent shallow copying
    LinkedList(const LinkedList&);
    LinkedList& operator=(const LinkedList&);

    // Find a node at a specified index
    PatientNode* GetNodeAt(int index) const
    {
        PatientNode* current = head;

        for (int i = 0; i < index && current != NULL; i++)
        {
            current = current->next;
        }

        return current;
    }

    // Exchange patient information
    void CopyPatientData(PatientNode* a, PatientNode* b)
    {
        if (a == NULL || b == NULL)
            return;

        swap(a->patientID, b->patientID);
        swap(a->name, b->name);
        swap(a->age, b->age);
        swap(a->condition, b->condition);
    }

public:

    // Constructor
    LinkedList()
    {
        head = NULL;
        count = 0;
    }

    // 6. Insert a patient at the head
    void Insert(PatientNode* patient)
    {
        if (patient == NULL)
            return;

        patient->next = head;
        head = patient;
        count++;
    }

    // 6. Remove a patient from the head
    PatientNode* Remove()
    {
        if (IsEmpty())
            return NULL;

        PatientNode* patient = head;
        head = head->next;
        patient->next = NULL;
        count--;

        return patient;
    }

    // 7. Check whether the list is empty
    bool IsEmpty() const
    {
        return head == NULL;
    }

    // 7. Check whether the list is not empty
    bool IsNotEmpty() const
    {
        return head != NULL;
    }

    // Return total number of patients
    int GetCount() const
    {
        return count;
    }

    // 5. Insert a patient at a specified index
    bool InsertAt(PatientNode* patient, int index)
    {
        if (patient == NULL || index < 0 || index > count)
            return false;

        if (index == 0)
        {
            Insert(patient);
            return true;
        }

        PatientNode* previous = GetNodeAt(index - 1);

        if (previous == NULL)
            return false;

        patient->next = previous->next;
        previous->next = patient;
        count++;

        return true;
    }

    // 5. Remove a patient at a specified index
    PatientNode* RemoveAt(int index)
    {
        if (index < 0 || index >= count)
            return NULL;

        if (index == 0)
            return Remove();

        PatientNode* previous = GetNodeAt(index - 1);

        if (previous == NULL || previous->next == NULL)
            return NULL;

        PatientNode* patient = previous->next;

        previous->next = patient->next;
        patient->next = NULL;
        count--;

        return patient;
    }

    // 5. Swap patients at two indexes
    bool Swap(int index1, int index2)
    {
        if (index1 < 0 || index1 >= count ||
            index2 < 0 || index2 >= count)
        {
            return false;
        }

        if (index1 == index2)
            return true;

        PatientNode* first = GetNodeAt(index1);
        PatientNode* second = GetNodeAt(index2);

        if (first == NULL || second == NULL)
            return false;

        CopyPatientData(first, second);
        return true;
    }

    // 5. Sort patients by ID in ascending order
    void Sort()
    {
        PatientNode* i;
        PatientNode* j;

        for (i = head; i != NULL; i = i->next)
        {
            for (j = i->next; j != NULL; j = j->next)
            {
                if (i->patientID > j->patientID)
                {
                    CopyPatientData(i, j);
                }
            }
        }
    }

    // 5. Reverse the linked list
    void Reverse()
    {
        PatientNode* previous = NULL;
        PatientNode* current = head;
        PatientNode* next = NULL;

        while (current != NULL)
        {
            next = current->next;
            current->next = previous;

            previous = current;
            current = next;
        }

        head = previous;
    }

    // 5. Display all patients
    void Print() const
    {
        PatientNode* current = head;
        int index = 0;

        cout << "\nIndex\tPatient ID\tName"
             << "\tAge\tCondition\n";

        cout << "------------------------------------------------"
             << "----------------\n";

        if (IsEmpty())
        {
            cout << "No patients in the list.\n";
        }

        while (current != NULL)
        {
            cout << index << "\t"
                 << current->patientID << "\t\t"
                 << current->name << "\t"
                 << current->age << "\t"
                 << current->condition << "\n";

            current = current->next;
            index++;
        }

        cout << "------------------------------------------------"
             << "----------------\n";

        cout << "Total patients: " << count << "\n";
    }

    // Release all dynamically allocated nodes
    ~LinkedList()
    {
        while (!IsEmpty())
        {
            delete Remove();
        }
    }
};

// ========================================
// CREATE A PATIENT NODE
// ========================================

PatientNode* CreatePatient(
    int id, string name, int age, string condition)
{
    PatientNode* patient = new PatientNode;

    patient->patientID = id;
    patient->name = name;
    patient->age = age;
    patient->condition = condition;
    patient->next = NULL;

    return patient;
}

// ========================================
// 8. MAIN: PROJECT DEMONSTRATION
// ========================================

int main()
{
    LinkedList hospital;

    cout << "========================================\n";
    cout << " HOSPITAL PATIENT MANAGEMENT SYSTEM\n";
    cout << "========================================\n";

    // Add initial sample patients
    hospital.InsertAt(
        CreatePatient(104, "Ahmed", 35, "Fever"), 0);

    hospital.InsertAt(
        CreatePatient(101, "Ali", 22, "Flu"), 1);

    hospital.InsertAt(
        CreatePatient(105, "Sara", 29, "Allergy"), 2);

    hospital.InsertAt(
        CreatePatient(102, "Usman", 40, "Injury"), 3);

    hospital.InsertAt(
        CreatePatient(103, "Ayesha", 25, "Cough"), 4);

    cout << "\n1. INITIAL PATIENT LIST";
    hospital.Print();

    // Insert at head
    hospital.Insert(
        CreatePatient(100, "Hassan", 31, "Headache"));

    cout << "\n2. AFTER INSERTING AT HEAD";
    hospital.Print();

    // Insert at index 2
    hospital.InsertAt(
        CreatePatient(106, "Fatima", 27, "Checkup"), 2);

    cout << "\n3. AFTER INSERTING AT INDEX 2";
    hospital.Print();

    // Remove at index 3
    PatientNode* removed = hospital.RemoveAt(3);

    if (removed != NULL)
    {
        cout << "\nRemoved patient: "
             << removed->name << "\n";

        delete removed;
    }

    cout << "\n4. AFTER REMOVING INDEX 3";
    hospital.Print();

    // Swap patients at indexes 0 and 2
    hospital.Swap(0, 2);

    cout << "\n5. AFTER SWAPPING INDEX 0 AND 2";
    hospital.Print();

    // Sort patients by ID
    hospital.Sort();

    cout << "\n6. AFTER SORTING BY PATIENT ID";
    hospital.Print();

    // Reverse the list
    hospital.Reverse();

    cout << "\n7. AFTER REVERSING THE LIST";
    hospital.Print();

    // Remove patient from head
    removed = hospital.Remove();

    if (removed != NULL)
    {
        cout << "\nRemoved from head: "
             << removed->name << "\n";

        delete removed;
    }

    cout << "\n8. AFTER REMOVING FROM HEAD";
    hospital.Print();

    // Check collection status
    cout << "\n9. COLLECTION STATUS\n";

    if (hospital.IsEmpty())
    {
        cout << "The patient list is empty.\n";
    }
    else if (hospital.IsNotEmpty())
    {
        cout << "The patient list is not empty.\n";
    }

    cout << "Total patients: "
         << hospital.GetCount() << "\n";

    cout << "\n========================================\n";
    cout << "PROJECT DEMONSTRATION COMPLETED\n";
    cout << "========================================\n";

    return 0;
}