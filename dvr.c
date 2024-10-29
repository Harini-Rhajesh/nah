#include <stdio.h>

#define MAX_NODES 5
#define INF 9999  // A large number to represent infinity (no direct connection)

void printDistance(int distance[MAX_NODES][MAX_NODES], int nodes) {
    printf("\nDistance Table:\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (distance[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", distance[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int nodes;
    int distance[MAX_NODES][MAX_NODES];

    // Get the number of nodes
    printf("Enter the number of nodes (<= %d): ", MAX_NODES);
    scanf("%d", &nodes);

    // Get the cost matrix input
    printf("Enter the cost matrix (-1 for no direct connection):\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            printf("Cost from Node%d to Node%d: ", i, j);
            scanf("%d", &distance[i][j]);

            // Replace -1 with INF (representing no connection)
            if (distance[i][j] == -1)
                distance[i][j] = INF;
        }
    }

    // Perform the distance vector update
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            for (int k = 0; k < nodes; k++) {
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    // Display the final distance table
    printDistance(distance, nodes);

    return 0;
}
