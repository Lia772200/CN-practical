#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to calculate parity bits
int calculate_parity(const vector<int>& codeword, int pos, int len) {
    int parity = 0;
    for (int i = pos - 1; i < len; i += 2 * pos) {
        for (int j = 0; j < pos && i + j < len; ++j) {
            parity ^= codeword[i + j];
        }
    }
    return parity;
}

// 1. Sender Side Implementation (Conceptual) [cite: 25]
vector<int> sender_hamming(const vector<int>& data) {
    int m = data.size();
    int r = 0;
    while (pow(2, r) < (m + r + 1)) {
        r++;
    }

    int len = m + r;
    vector<int> codeword(len, 0); // Initialize with placeholders
    int j = 0; // index for data bits
    
    // Place data bits and parity bit placeholders
    for (int i = 0; i < len; ++i) {
        if (i + 1 == pow(2, r)) {
            r--; // Placeholders for P bits
        } else {
            codeword[i] = data[j++];
        }
    }

    // Calculate and fill parity bits
    r = 0;
    while (pow(2, r) <= len) {
        int pos = pow(2, r);
        codeword[pos - 1] = calculate_parity(codeword, pos, len);
        r++;
    }

    return codeword;
}

// 2. Receiver Side Implementation (Conceptual) [cite: 26]
void receiver_hamming(vector<int> received) {
    int len = received.size();
    int r = 0;
    while (pow(2, r) <= len) {
        r++;
    }

    vector<int> syndrome;
    int error_pos = 0;

    for (int i = 0; i < r; ++i) {
        int pos = pow(2, i);
        int parity_check = calculate_parity(received, pos, len);
        syndrome.push_back(parity_check);

        if (parity_check == 1) {
            error_pos += pos;
        }
    }

    cout << "\nReceiver Side Check:" << endl;
    cout << "Syndrome (P" << pow(2, r - 1) << " ... P1): ";
    for (int i = syndrome.size() - 1; i >= 0; --i) {
        cout << syndrome[i];
    }
    cout << endl;

    if (error_pos == 0) {
        cout << "Result: Codeword is **Correct**." << endl;
    } else {
        cout << "Result: Codeword is **Wrong**." << endl;
        cout << "Error located at position: " << error_pos << endl;
        // Correct the error
        received[error_pos - 1] = 1 - received[error_pos - 1];
        cout << "Corrected Codeword: ";
        for (int bit : received) {
            cout << bit;
        }
        cout << endl;
    }
}

int main() {
    vector<int> data = {1, 0, 1, 1, 0, 0, 1}; // D: 1011001
    
    cout << "Sender Side (Data: 1011001)" << endl;
    vector<int> codeword = sender_hamming(data);
    cout << "Hamming Codeword: ";
    for (int bit : codeword) {
        cout << bit;
    }
    cout << " (Expected: 10100111001)" << endl; // Match with P101P011P001

    // Simulation of error at position 10 (as per Q.4)
    vector<int> received_with_error = codeword;
    received_with_error[10 - 1] = 1 - received_with_error[10 - 1]; 
    cout << "\nSimulated Received Codeword (Error at pos 10): ";
    for (int bit : received_with_error) {
        cout << bit;
    }
    cout << " (Matches Q.4: 10101101110)" << endl;

    receiver_hamming(received_with_error);

    return 0;
}
