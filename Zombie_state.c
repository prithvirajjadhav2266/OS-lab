#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort(int arr[], int n)
{
    // Bubble Sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent process
        printf("Parent process (PID: %d) sorting the array.\n", getpid());
        sort(arr, n);
        printf("Parent process (PID: %d) sorted array: ", getpid());
        printArray(arr, n);

        // Sleep for 10 seconds to simulate delay (zombie process)
        sleep(10);

        // Now wait for the child process to avoid it being a zombie process
        wait(NULL);
        printf("Parent process (PID: %d) completed waiting for the child.\n", getpid());
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process (PID: %d) sorting the array.\n", getpid());
        sort(arr, n);
        printf("Child process (PID: %d) sorted array: ", getpid());
        printArray(arr, n);
        exit(0);
    }
    else
    {
        // Fork failed
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}
