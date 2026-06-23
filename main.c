#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 1000

// Globally accessible data structure
unsigned char buffer[BUFFER_SIZE];
int buffer_size = 0;

// Function to simulate sensor data generation
void generateSensorData()
{
    int count = rand() % 6; // Random number from 0 to 5

    printf("Generated %d byte(s): ", count);

    for (int i = 0; i < count; i++)
    {
        unsigned char data = rand() % 256; // Random byte

        if (buffer_size < BUFFER_SIZE)
        {
            buffer[buffer_size++] = data;
        }

        printf("%02X ", data);
    }

    printf("\n");
}

// Function to print latest 50 bytes and delete them
void processBuffer()
{
    printf("\n----- 10-Second Check -----\n");

    if (buffer_size < 50)
    {
        printf("Buffer contains only %d byte(s). Not enough data to print.\n",
               buffer_size);
        return;
    }

    int start = buffer_size - 50;

    printf("Latest 50 bytes:\n");

    for (int i = start; i < buffer_size; i++)
    {
        printf("%02X ", buffer[i]);
    }

    printf("\n");

    // Delete the printed 50 bytes
    buffer_size = start;

    printf("50 bytes deleted.\n");
    printf("Remaining bytes in buffer: %d\n", buffer_size);
}

int main()
{
    int seconds = 0;

    srand(time(NULL));

    printf("Sensor Data Simulation Started...\n\n");

    while (1)
    {
        sleep(1); // Timer triggers every second

        seconds++;

        printf("\nTime = %d second(s)\n", seconds);

        generateSensorData();

        // Every 10 seconds
        if (seconds % 10 == 0)
        {
            processBuffer();
        }
    }

    return 0;
}
