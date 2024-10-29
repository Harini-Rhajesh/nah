#include <stdio.h>
#include <stdlib.h>  // For rand() function
#include <time.h>    // For seeding rand()
#include <unistd.h>  // For sleep() function

void send_packet(int packet) {
    printf("Sender: Sending packet %d\n", packet);
    sleep(1);  // Simulate network delay in sending
}

int receive_ack(int packet) {
    // Randomly decide if ACK is received or lost
    int ack_received = rand() % 2;  // 50% chance of ACK loss

    if (ack_received) {
        printf("Receiver: Acknowledging packet %d\n", packet);
        sleep(1);  // Simulate network delay in receiving ACK
    } else {
        printf("Receiver: ACK for packet %d lost! Resending...\n", packet);
    }

    return ack_received;
}

void stop_and_wait_protocol(int packets[], int n) {
    int expected_packet = 1;

    for (int i = 0; i < n; i++) {
        if (packets[i] != expected_packet) {
            printf("Error: Missing packet %d. Resending...\n", expected_packet);
            i--;  // Repeat the current iteration until the missing packet is "resent"
            continue;
        }

        int ack_received = 0;

        // Keep resending the packet until ACK is received
        while (!ack_received) {
            send_packet(packets[i]);       // Send packet
            ack_received = receive_ack(packets[i]);  // Try to receive ACK
        }

        printf("Sender: ACK received for packet %d, moving to next packet\n", packets[i]);
        expected_packet++;  // Move to the next expected packet
    }
    printf("All packets sent and acknowledged.\n");
}

int main() {
    int packet_count;

    // Seed the random number generator
    srand(time(0));

    // Get the number of packets from the user
    printf("Enter the number of packets to send: ");
    scanf("%d", &packet_count);

    // Validate packet count
    if (packet_count <= 0) {
        printf("Invalid packet count. Exiting.\n");
        return 1;
    }

    int packets[packet_count];

    // Get each packet content from the user
    printf("Enter the packet contents in sequence:\n");
    for (int i = 0; i < packet_count; i++) {
        printf("Packet %d: ", i + 1);
        scanf("%d", &packets[i]);
    }

    printf("\nStarting Stop-and-Wait Protocol simulation\n");
    stop_and_wait_protocol(packets, packet_count);
    return 0;
}
