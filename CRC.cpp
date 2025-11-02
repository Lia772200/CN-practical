#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function for Modulo-2 Binary Division (XOR)
string mod2_division(string dividend, const string& divisor) {
    int div_len = divisor.length();
    
    // Perform XOR on the current section of the dividend
    for (int i = 0; i <= dividend.length() - div_len; ) {
        if (dividend[i] == '1') {
            for (int j = 0; j < div_len; ++j) {
                // XOR operation
                dividend[i + j] = (dividend[i + j] == divisor[j] ? '0' : '1');
            }
        }
        // Find the next '1' to start the next division cycle
        while (i < dividend.length() && dividend[i] != '1') {
            i++;
        }
    }
    
    // The remainder is the last (div_len - 1) bits
    return dividend.substr(dividend.length() - (div_len - 1));
}

// 1. Sender Side Implementation [cite: 35]
string sender_crc(string data, const string& generator) {
    int n = generator.length() - 1; // Degree of polynomial
    string augmented_data = data + string(n, '0');

    string remainder = mod2_division(augmented_data, generator);

    // Transmitted codeword
    return data + remainder;
}

// 2. Receiver Side Implementation [cite: 36]
bool receiver_crc(string received_codeword, const string& generator) {
    string remainder = mod2_division(received_codeword, generator);

    // Check if remainder is all zeros
    return all_of(remainder.begin(), remainder.end(), [](char c){ return c == '0'; });
}

int main() {
    string data = "1101011011"; // M
    string generator = "10011";  // G(x) = x^4 + x + 1

    cout << "--- CRC Implementation (Generator: " << generator << ") ---" << endl;
    
    // Sender Side
    string transmitted_codeword = sender_crc(data, generator);
    cout << "\nSender Side:" << endl;
    cout << "Original Data: " << data << endl;
    cout << "Transmitted Codeword: " << transmitted_codeword << endl; 
    // Output: 11010110111010 (Matches Q.3: Remainder 1010)

    // Receiver Side (No error)
    cout << "\nReceiver Side (Correct Codeword):" << endl;
    bool is_correct = receiver_crc(transmitted_codeword, generator);
    cout << "Check Result: " << (is_correct ? "CORRECT (Remainder is 0)" : "ERROR DETECTED") << endl;

    // Receiver Side (Simulate error at 2nd bit)
    string received_error = transmitted_codeword;
    received_error[1] = (received_error[1] == '0' ? '1' : '0'); 
    
    cout << "\nReceiver Side (Codeword with simulated error):" << endl;
    cout << "Received Codeword: " << received_error << endl;
    is_correct = receiver_crc(received_error, generator);
    cout << "Check Result: " << (is_correct ? "CORRECT (Remainder is 0)" : "**ERROR DETECTED** (Remainder is non-zero)") << endl;

    return 0;
}
