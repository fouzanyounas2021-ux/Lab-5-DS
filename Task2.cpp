#include <iostream>
using namespace std;

template <typename T>
class AbstractStack {
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;

    virtual ~AbstractStack() {}
};

template <typename T>
class myStack : public AbstractStack<T> {
private:
    T* arr;          
    T* minArr;       
    int capacity;   
    int stackTop;   
    int minTop;     

public:
    myStack(int size) {
        capacity = size;
        arr = new T[capacity];
        minArr = new T[capacity];

        stackTop = -1;
        minTop = -1;
    }
    ~myStack() {
        delete[] arr;
        delete[] minArr;
    }
    void push(T value) override {
        if (isFull()) {
            cout << "Stack Overflow! Stack is full.\n";
            return;
        }
        arr[++stackTop] = value;
        if (minTop == -1 || value <= minArr[minTop]) {
            minArr[++minTop] = value;
        }
        cout << value << " pushed onto the stack.\n";
    }
    T pop() override {
        if (isEmpty()) {
            cout << "Stack Underflow! Stack is empty.\n";
            return T{};
        }
        T value = arr[stackTop--];
        if (value == minArr[minTop]) {
            minTop--;
        }
        return value;
    }
    T top() const override {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return T{};
        }
        return arr[stackTop];
    }
    T getMin() const {
        if (isEmpty()) {
            cout << "Stack is empty. No minimum element.\n";
            return T{};
        }
        return minArr[minTop];
    }
    bool isEmpty() const override {
        return stackTop == -1;
    }
    bool isFull() const override {
        return stackTop == capacity - 1;
    }
    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Stack elements (Top to Bottom):\n";
        for (int i = stackTop; i >= 0; i--) {
            cout << arr[i] << endl;
        }
    }
};
int main() {
    int size;
    cout << "Enter maximum stack size: ";
    cin >> size;

    if (size <= 0) {
        cout << "Stack size must be positive.\n";
        return 1;
    }
    myStack<int> s(size);
    int choice, value;
    do {
        cout << "\n===== ENHANCED STACK MENU =====\n";
        cout << "1. Push element\n";
        cout << "2. Pop element\n";
        cout << "3. Show top element\n";
        cout << "4. Check if stack is empty\n";
        cout << "5. Check if stack is full\n";
        cout << "6. Display stack elements\n";
        cout << "7. Show minimum element\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> value;
            s.push(value);
            break;
        case 2:
            if (!s.isEmpty()) {
                cout << "Popped element: " << s.pop() << endl;
            }
            else {
                s.pop();
            }
            break;
        case 3:
            if (!s.isEmpty()) {
                cout << "Top element: " << s.top() << endl;
            }
            else {
                s.top();
            }
            break;
        case 4:
            cout << (s.isEmpty()
                ? "Stack is empty.\n"
                : "Stack is not empty.\n");
            break;

        case 5:
            cout << (s.isFull()
                ? "Stack is full.\n"
                : "Stack is not full.\n");
            break;
        case 6:
            s.display();
            break;
        case 7:
            if (!s.isEmpty()) {
                cout << "Minimum element: "
                    << s.getMin() << endl;
            }
            else {
                s.getMin();
            }
            break;
        case 8:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);
    return 0;
}
