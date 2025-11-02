#include <iostream>
#include <string>
#include <unistd.h> // For sleep/delay (conceptual)

using namespace std;

// Conceptual function to simulate sending a frame
void send_frame(int seq_num) {
    cout << "Sender: Sending Frame " << seq_num << endl;
}

// Conceptual function to simulate receiving an ACK
int receive_ack(int expected_ack) {
    // Simulate some delay/network time
    usleep(500000); 

    // 90% chance of successful ACK, 10% chance of loss (simulating timeout)
    if (rand() % 10 < 9) {
        cout << "Receiver: Received Frame " << (1 - expected_ack) << ". Sending ACK " << expected_ack << endl;
        return expected_ack; // Next expected sequence number
    } else {
        cout << "Network: ACK " << expected_ack << " lost or delayed (Simulated Timeout)." << endl;
        return -1; // Indicates failure/timeout
    }
}

void stop_and_wait_arq(const string& data) {
    int seq_num = 0; // Current frame sequence number (0 or 1)
    
    // In a real implementation, you would break the data into frames.
    // Here, we simulate two frames for demonstration.

    for (int i = 0; i < 2; ++i) { 
        send_frame(seq_num);
        
        int ack_received = -1;
        while (ack_received != (1 - seq_num)) {
            // Wait for ACK
            ack_received = receive_ack(1 - seq_num); 

            if (ack_received == -1) {
                cout << "Sender: Timeout! Retransmitting Frame " << seq_num << endl;
                send_frame(seq_num); // Retransmit
            } else if (ack_received == (1 - seq_num)) {
                cout << "Sender: Received correct ACK. Moving to next frame." << endl;
                seq_num = 1 - seq_num; // Flip sequence number (0 -> 1 or 1 -> 0)
                break;
            }
        }
    }
}

int main() {
    srand(time(0)); // Seed for random simulation
    cout << "--- Stop-and-Wait ARQ Simulation ---" << endl;
    stop_and_wait_arq("Data to transmit");
    return 0;
}
