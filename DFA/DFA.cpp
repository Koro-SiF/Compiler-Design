#include <iostream>
#include <string>

using namespace std;

// DFA class
class DFA {
private:
    int currentState;

public:
    DFA() {
        currentState = 0;
    }

    void Transition(char input) {
        switch (currentState) {
            case 0:
                cout << "State: " << currentState << endl;
                if (input == 'a') {
                    currentState = 1;
                } else if (input == 'b') {
                    currentState = 2;
                } else {
                    currentState = -1;
                }
                break;
            case 1:
                cout << "State: " << currentState << endl;
                if (input == 'a') {
                    currentState = 3;
                    cout << "State: " << currentState << endl;
                } else if (input == 'b') {
                    currentState = 2;
                } else {
                    currentState = -1;
                }
                break;
            case 2:
                cout << "State: " << currentState << endl;
                if (input == 'a') {
                    currentState = 4;
                } else if (input == 'b') {
                    currentState = 5;
                } else {
                    currentState = -1;
                }
                break;
            case 3:
                if (input == 'a') {
                    currentState = 3;
                    cout << "State: " << currentState << endl;
                } else if (input == 'b') {
                    currentState = 2;
                } else {
                    currentState = -1;
                }
                break;
            case 4:
                cout << "State: " << currentState << endl;
                if (input == 'a') {
                    currentState = 5;
                } else {
                    currentState = -1;
                }
                break;
            case 5:
                cout << "State: " << currentState << endl;
                if (input == 'a') {
                    currentState = 6;
                } else if (input == 'b') {
                    currentState = 2;
                } else {
                    currentState = -1;
                }
                break;
            case 6:
                cout << "State: " << currentState << endl;
                if (input == 'a') {
                    currentState = 7;
                    cout << "State: " << currentState << endl;
                } else {
                    currentState = -1;
                }
                break;
            case -1:
                break;
        }
    }

    bool isAcceptState() {
        return currentState == 3 || currentState == 7;
    }
};

int main() {
    // RegEx a*(bb|baa)*aa
    while(true) {
        DFA dfa;
        string input;
        cout << "Enter a string: ";
        cin >> input;

        if (input == "exit") return false;

        for (char c : input) {
            dfa.Transition(c);
        }

        if (dfa.isAcceptState())
            cout << "Accept" << endl;
        else 
            cout << "Error: Non-acceptable string" << endl;
    }

    return 0;
}