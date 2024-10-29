#include <stdio.h>
#include <string.h>

void xorOperation(char *dividend, const char *divisor, int len) {
    for (int i = 0; i < len; i++) {
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
    }
}

void crc(const char *input, const char *generator, char *remainder) {
    int msgLen = strlen(input);
    int genLen = strlen(generator);
    char temp[256];

    // Copy input to temp and append genLen - 1 zeros
    strcpy(temp, input);
    for (int i = 0; i < genLen - 1; i++) {
        temp[msgLen + i] = '0';
    }
    temp[msgLen + genLen - 1] = '\0';

    // Perform division using XOR
    for (int i = 0; i <= msgLen; i++) {
        if (temp[i] == '1') {
            xorOperation(&temp[i], generator, genLen);
        }
    }

    // Copy the remainder to output
    strncpy(remainder, &temp[msgLen], genLen - 1);
    remainder[genLen - 1] = '\0';
}

int main() {
    char message[128], generator[128], received[128];
    char remainder[128], temp[256];

    printf("Enter the bit message: ");
    scanf("%s", message);
    printf("Enter the generator polynomial: ");
    scanf("%s", generator);

    // Generate CRC and append to the message to form transmitted message
    crc(message, generator, remainder);
    strcpy(temp, message);
    strcat(temp, remainder);

    printf("Transmitted message: %s\n", temp);

    // Simulate receiving the message
    printf("Enter the received message: ");
    scanf("%s", received);

    // Calculate CRC of received message
    crc(received, generator, remainder);
    printf("Remainder after checking: %s\n", remainder);

    // Check if there is an error
    int error = 0;
    for (int i = 0; i < strlen(remainder); i++) {
        if (remainder[i] != '0') {
            error = 1;
            break;
        }
    }

    if (error) {
        printf("Error detected in the received message.\n");
    } else {
        printf("No error detected in the received message.\n");
    }

    return 0;
}
