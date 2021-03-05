#include <iostream>

int size = 0;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* head = NULL;

void Insert(int data, int pos) {

    if (pos > size + 1) {
        std::cout << "Insertion at chosen position not possible, try position <= " << size+1 << " for insertion." << std::endl;
        return;
    }

    ++size;

    Node* temp = new Node;
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
        return;
    }

    if (pos == 0) {
        head->prev = temp;
        temp->next = head;
        head = temp;
        return;
    }

    Node* tempDash = head;
    if (pos == -1) {
        while (tempDash->next != NULL) {
            tempDash = tempDash->next;
        }
        tempDash->next = temp;
        temp->prev = tempDash;
        return;
    }

    for (int i = 1; i < pos - 1; ++i) {
        tempDash = tempDash->next;
    }
    temp->prev = tempDash;
    temp->next = tempDash->next;
    tempDash->next = temp;

}

int Search(int data) {
    if (head == NULL) {
        return -1;
    }

    Node* temp = head;
    int i = 0;

    while (temp != NULL)
    {
        if (temp->data == data) {
            return i + 1;
        }
        ++i;
        temp = temp->next;
    }
    return -1;
}

void Delete(int data, int pos) {

    if (pos > size || pos < -1) {
        std::cout << "Invalid Index, deletion not possible." << std::endl;
        return;
    }

    if (data == -1) {
        --size;
        Node* temp = head;
        if (pos == 0) {
            head = head->next;
            delete(temp);
            return;
        }

        if (size == 0) {
            head = NULL;
            delete(temp);
        } else {
            if (pos == -1) {
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->prev->next = NULL;
                delete(temp);
                return;
            }

            for (int i = 0; i < pos - 1; ++i) {
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete(temp);
            return;
        }
    }

    int res = Search(data);
    if (res == -1) {
        std::cout << "Deletion not possible as element not found." << std::endl;
    } else {
        if (size == 1) {
            Delete(-1, -1);
        }
        else {
            Delete(-1, res);
        }
    }
}

void Print(int i) {
    Node* temp = head;

    std::cout << "The Linked List:" << std::endl;

    if (i == 0) {
        while (temp != NULL) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        while (temp != NULL) {
            std::cout << temp->data << " ";
            temp = temp->prev;
        }
        std::cout << "\n";
    }
}

void Reverse() {
    if (size <= 1) {
        return;
    }
    Node* curr = head, *prev = NULL;

    while (curr != NULL) {
        prev = curr->prev;
        curr->prev = curr->next;
        curr->next = prev;
        curr = curr->prev;
    }
    if (prev != NULL) {
        head = prev->prev;
    }
}

int main() {
    int i = 0, data, index, rNum, branch;

    while (i != 6) {
        std::cout << "Operations:\n1.Insert\n2.Delete\n3.Search\n4.Print\n5.Reverse\n6.Exit" << std::endl;
        std::cin >> i;

        switch (i) {
        case 1: std::cout << "Enter data element followed by index (0 for insertion at start, -1 for insertion at end):" << std::endl;
            std::cin >> data >> index;
            Insert(data, index);
            break;

        case 2: std::cout << "Delete element by value(enter 0) or by index(enter 1):" << std::endl;
            std::cin >> branch;
            if (branch == 0) {
                std::cout << "Enter data element:" << std::endl;
                std::cin >> data;
                Delete(data, -1);
            }
            else if (branch == 1) {
                std::cout << "Enter position(0 for beginning and -1 for last):" << std::endl;
                std::cin >> index;
                Delete(-1, index);
            }
            else {
                std::cout << "Invalid Input!" << std::endl;
            }
            break;

        case 3: std::cout << "Enter number to be searched:" << std::endl;
            std::cin >> data;
            rNum = Search(data);
            if (rNum != -1) {
                std::cout << "Number found in linked list at " << rNum << " position." << std::endl;
            }
            else {
                std::cout << "Number doesn't exist in linked list." << std::endl;
            }
            break;

        case 4: std::cout << "Enter 0 to print in order or anything else to print in reverse:" << std::endl;
            std::cin >> branch;
            Print(branch);
            break;

        case 5: Reverse();
            std::cout << "List has been reversed." << std::endl;
            break;

        default:
            if (i != 6) {
                std::cout << "Invalid Input!\n" << std::endl;
            }
        }
    }
    return 0;
}