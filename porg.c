#include <stdio.h>
#include <string.h>

#define MAX_CAPACITY 10 

//عمل masking لعناصر ال struct
typedef struct {
    char data_array[MAX_CAPACITY]; 
    int write_pos;                
    int read_pos;                 
    int active_elements;          
} RingBuffer; 

// اعطاء قيم صفرية لعناصر الbuffer
void setupBuffer(RingBuffer *rb) {
    rb->write_pos = 0;
    rb->read_pos = 0;
    rb->active_elements = 0;
}

// فحص إن كان ممتلئ او فارغ
int bufferFull(RingBuffer *rb) {
    return rb->active_elements == MAX_CAPACITY;
}

int bufferEmpty(RingBuffer *rb) {
    return rb->active_elements == 0;
}

// تابع الدخال العناصر
void pushData(RingBuffer *rb, char val) {
    if (bufferFull(rb)) {
        printf("\n[Warning] Capacity reached! Overflow at: %c", val);
        return;
    }
    rb->data_array[rb->write_pos] = val;
    rb->write_pos = (rb->write_pos + 1) % MAX_CAPACITY;
    rb->active_elements++;
}

// 6. تابع الأخراح
char popData(RingBuffer *rb) {
    if (bufferEmpty(rb)) {
        printf("\n[Warning] No data available (Underflow).");
        return '\0';
    }
    char out_val = rb->data_array[rb->read_pos];
    rb->read_pos = (rb->read_pos + 1) % MAX_CAPACITY;
    rb->active_elements--;
    return out_val;
}


int main() {
    RingBuffer myRing;
    setupBuffer(&myRing);

    char input_text[64]; // زيادة الحجم قليلا
    printf("Enter Student Name: ");
    scanf("%s", input_text);

    
    strcat(input_text, "-CE-ESY");

    printf("\nProcessing String: %s\n", input_text);
    printf("Storing to Ring Buffer...\n");

    int len = strlen(input_text);
    for (int j = 0; j < len; j++) {
        pushData(&myRing, input_text[j]);
    }

    printf("\n\nRetrieving Data...\n");
    while (!bufferEmpty(&myRing)) {
        printf("%c", popData(&myRing));
    }
// طباعة رسالة الإنتهاء من التاسك
    printf("\n\nTask finished successfully.\n");

    return 0;
}
