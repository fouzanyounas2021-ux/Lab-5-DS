#include <iostream>
#include <string>
#include <stack>
using namespace std;

class TextEditor {
private:
    string text;           
    stack<char> undoStack;  
    stack<char> redoStack; 

    string stackToString(stack<char> s) const {
        string result = "";
        while (!s.empty()) {
            result += s.top();
            s.pop();
        }
        return result;
    }
public:
    TextEditor() {
        text = "";
    }
    void typeCharacter(char ch) {
        text += ch;
        undoStack.push(ch);
        while (!redoStack.empty()) {
            redoStack.pop();
        }
        cout << "Character '" << ch
            << "' typed successfully.\n";
    }
    void deleteCharacter() {
        if (text.empty()) {
            cout << "Nothing to delete. Text is empty.\n";
            return;
        }
        char deletedChar = text.back();
        undoStack.push('\b');
        undoStack.push(deletedChar);

        text.pop_back();
        while (!redoStack.empty()) {
            redoStack.pop();
        }
        cout << "Last character deleted successfully.\n";
    }
    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo.\n";
            return;
        }
        char action = undoStack.top();
        undoStack.pop();
        if (action == '\b') {
            if (!undoStack.empty()) {
                char ch = undoStack.top();
                undoStack.pop();

                text += ch;
                redoStack.push(ch);
            }
        }
        else {
            if (!text.empty()) {
                text.pop_back();
            }
            redoStack.push(action);
        }
        cout << "Undo operation completed.\n";
    }
    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo.\n";
            return;
        }
        char ch = redoStack.top();
        redoStack.pop();

        text += ch;
        undoStack.push(ch);

        cout << "Redo operation completed.\n";
    }
    void displayText() const {
        cout << "\nCurrent Text: ";

        if (text.empty()) {
            cout << "(empty)";
        }
        else {
            cout << text;
        }

        cout << endl;
    }
    void displayUndoHistory() const {
        if (undoStack.empty()) {
            cout << "Undo history is empty.\n";
            return;
        }

        cout << "Undo history (top to bottom): "
            << stackToString(undoStack) << endl;
    }
    void displayRedoHistory() const {
        if (redoStack.empty()) {
            cout << "Redo history is empty.\n";
            return;
        }

        cout << "Redo history (top to bottom): "
            << stackToString(redoStack) << endl;
    }
};
int main() {
    TextEditor editor;
    int choice;
    char ch;

    do {
        cout << "\n===== TEXT EDITOR =====\n";
        cout << "1. Type a character\n";
        cout << "2. Delete last character\n";
        cout << "3. Undo\n";
        cout << "4. Redo\n";
        cout << "5. Display current text\n";
        cout << "6. Display undo history\n";
        cout << "7. Display redo history\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter a character to type: ";
            cin >> ch;
            editor.typeCharacter(ch);
            break;

        case 2:
            editor.deleteCharacter();
            break;

        case 3:
            editor.undo();
            break;

        case 4:
            editor.redo();
            break;

        case 5:
            editor.displayText();
            break;

        case 6:
            editor.displayUndoHistory();
            break;

        case 7:
            editor.displayRedoHistory();
            break;

        case 0:
            cout << "Exiting text editor...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
