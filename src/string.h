#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    char *data;
    uint32_t len;
} String;

void exitError(void) {
    fprintf(stderr, "Error: %s; exiting\n", strerror(errno));
    exit(errno);
}

String makeString(char s) {
    // 2 for null terminator
    char *data = (char*)calloc(2, sizeof(char));
    if (!data) exitError();
    *data = s;
    *(data+1) = '\0';

    return (String){.data = data, .len = 1};
}

void pushChar(String *string, char c) {
    char *ptr = (*string).data;

    if (!((*string).data)) {
        printf("data is null\n; returning");
        return;
    }

    (*string).len++; // Increment for new character
    char *new_data = (char*)calloc((*string).len+1, sizeof(char)); // +1 for null terminator
    if (!new_data) exitError();

    // Copy old data to new data and add new character with null-terminator
    for (int i = 0;; i++, ptr++) {
        if (*ptr == '\0') {
            *(new_data+i) = c;
            *(new_data+(i+1)) = '\0';
            break;
        }
        *(new_data+i) = *ptr;
    }

    free((*string).data);
    (*string).data = new_data;
}
