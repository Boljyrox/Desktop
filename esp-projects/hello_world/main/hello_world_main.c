#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    // Print replies immediately.
    setvbuf(stdout, NULL, _IONBF, 0);

    char message[256];
    int length = 0;
    int too_long = 0;

    printf("\nReady! Type a message and press Enter.\n");

    while (1) {
        int character = getchar();

        // No input yet: let other tasks run.
        if (character == EOF) {
            clearerr(stdin);
            vTaskDelay(pdMS_TO_TICKS(10));
            continue;
        }

        // Treat either Enter character as the end of a message.
        if (character == '\n' || character == '\r') {
            if (too_long) {
                printf("ERROR: Message too long\n");
            } else if (length > 0) {
                message[length] = '\0';
                printf("RECEIVED: %s\n", message);
            }

            length = 0;
            too_long = 0;
        } else if (!too_long) {
            if (length < sizeof(message) - 1) {
                message[length++] = (char)character;
            } else {
                too_long = 1;
            }
        }
    }
}