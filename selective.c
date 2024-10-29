#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10
#define TIMEOUT 2  // Timeout duration in seconds

typedef struct {
    int packet_num;
    int acked;
} Packet;

void send_packet(int packet_num) {
    printf("Sender: Sending packet %d\n", packet_num);
    sleep(1);  // Simulate network delay
}

int receive_ack(int packet_num) {
    // Simulate ACK loss with a 70% chance of success
    if (rand() % 100 < 70) {
        printf("Receiver: Acknowledging packet %d\n", packet_num);
        return 1;
    } else {
        printf("Receiver: ACK for packet %d lost!\n", packet_num);
        return 0;
    }
}

void selective_repeat_arq() {
    Packet packets[TOTAL_PACKETS];
    int base = 0;
    int next_packet = 0;

    // Initialize packets
    for (int i = 0; i < TOTAL_PACKETS; i++) {
        packets[i].packet_num = i;
        packets[i].acked = 0;
    }

    while (base < TOTAL_PACKETS) {
        // Send packets within the window
        while (next_packet < base + WINDOW_SIZE && next_packet < TOTAL_PACKETS) {
            if (!packets[next_packet].acked) {
                send_packet(packets[next_packet].packet_num);
            }
            next_packet++;
        }

        // Check for ACKs within the window
        for (int i = base; i < next_packet; i++) {
            if (!packets[i].acked) {
                if (receive_ack(packets[i].packet_num)) {
                    packets[i].acked = 1;
                    printf("Sender: ACK received for packet %d\n", packets[i].packet_num);
                } else {
                    printf("Sender: Resending packet %d due to lost ACK\n", packets[i].packet_num);
                    send_packet(packets[i].packet_num);
                    sleep(TIMEOUT);  // Simulate timeout before resending
                }
            }
        }

        // Slide the window if the base packet is acknowledged
        while (base < TOTAL_PACKETS && packets[base].acked) {
            base++;
        }
    }

    printf("All packets sent and acknowledged.\n");
}

int main() {
    srand(time(0));  // Seed for random ACK loss simulation
    printf("Starting Selective Repeat ARQ Simulation...\n");
    selective_repeat_arq();
    return 0;
}
