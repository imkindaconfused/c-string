#include <stdint.h>
#include <stdlib.h>

typedef struct {
    char *data;
    uint32_t len;
} String;

int makeString(String *string, char s) {
    // trying to assign an already initialized string
    if ((*string).data != NULL && (*string).len != 0) return -2;
    // 2 for null terminator
    char *data = (char*)calloc(2, sizeof(char));
    // allocation failed, errno can be used to handle this error
    if (!data) return -1;
    *data = s;
    *(data+1) = '\0';

    *string = (String){.data = data, .len = 1};
    return 0;
}

int pushChar(String *string, char c) {
    char *ptr = (*string).data;

    if (!((*string).data)) {
        // data is null; nowhere to push
        return -2;
    }

    (*string).len++; // Increment for new character
    char *new_data = (char*)calloc((*string).len+1, sizeof(char)); // +1 for null terminator
    // allocation failed, errno can be used to handle this error
    if (!new_data) return -1;

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
    return 0;
}
