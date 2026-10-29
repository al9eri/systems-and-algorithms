#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock, arr[100], n, sum;
    struct sockaddr_in serv_addr;
    char buffer[1024] = "hello";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    send(sock, buffer, strlen(buffer) + 1, 0);
    read(sock, buffer, sizeof(buffer));
    printf("Client Received: %s\n", buffer);

    printf("Enter the size of the array: ");
    scanf("%d", &n);
    send(sock, &n, sizeof(n), 0);

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    send(sock, arr, sizeof(int) * n, 0);
    read(sock, &sum, sizeof(sum));
    printf("Client received Sum= %d\n", sum);

    close(sock);
    return 0;
}
