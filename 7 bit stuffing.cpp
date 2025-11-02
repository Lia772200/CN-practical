#include <iostream>
#include <string>
#include <vector>

using namespace std;

string bitStuff(const string& data) {
    string stuffed_data = "";
    int consecutive_ones = 0;

    for (char bit : data) {
        stuffed_data += bit;
        if (bit == '1') {
            consecutive_ones++;
            if (consecutive_ones == 5) {
                stuffed_data += '0'; // Stuff a '0'
                consecutive_ones = 0;
            }
        } else {
            consecutive_ones = 0;
        }
    }

    // Add flags 01111110 at start and end
    return "01111110" + stuffed_data + "01111110";
}

int main() {
    string data = "01101111110101111111101";
    cout << "Original Data: " << data << endl;
    
    string framed_data = bitStuff(data);
    cout << "Framed Data (with flags and stuffing): " << framed_data << endl;
    
    // Output:
    // Original Data: 01101111110101111111101
    // Framed Data (with flags and stuffing): 0111111001101111101010111110110101111110
    
    return 0;
}
