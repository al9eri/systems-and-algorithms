#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int serv_fd, new_sock, arr[100], n, sum = 0;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t addr_size;
    char buffer[1024];

    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(serv_fd, 5);
    printf("Listening for client..\n");

    addr_size = sizeof(cli_addr);
    new_sock = accept(serv_fd, (struct sockaddr*)&cli_addr, &addr_size);

    read(new_sock, buffer, sizeof(buffer));
    printf("Server Received: %s\n", buffer);
    send(new_sock, "Hello Back!", 12, 0);

    read(new_sock, &n, sizeof(n));
    read(new_sock, arr, sizeof(int) * n);
    
    printf("Array received:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
        sum += arr[i];
    }
    printf("\nComputing sum: %d\n", sum);
    
    send(new_sock, &sum, sizeof(sum), 0);
    close(new_sock);
    close(serv_fd);
    return 0;
}
