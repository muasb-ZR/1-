#include <stdio.h>
#include <string.h>

// 1. استخدام اسم مختلف للحجم
#define MAX_CAPACITY 10 

// 2. تغيير اسم الـ struct وأسماء العناصر بداخله
typedef struct {
    char data_array[MAX_CAPACITY]; // بدلاً من buffer
    int write_pos;                 // بدلاً من head
    int read_pos;                  // بدلاً من tail
    int active_elements;           // بدلاً من count
} RingBuffer; // اسم جديد للهيكل

// 3. دالة تهيئة باسم جديد
void setupBuffer(RingBuffer *rb) {
    rb->write_pos = 0;
    rb->read_pos = 0;
    rb->active_elements = 0;
}

// 4. دوال الفحص بأسماء مختلفة
int bufferFull(RingBuffer *rb) {
    return rb->active_elements == MAX_CAPACITY;
}

int bufferEmpty(RingBuffer *rb) {
    return rb->active_elements == 0;
}

// 5. دالة الإضافة (بأسلوب كتابة مختلف قليلاً)
void pushData(RingBuffer *rb, char val) {
    if (bufferFull(rb)) {
        printf("\n[Warning] Capacity reached! Overflow at: %c", val);
        return;
    }
    rb->data_array[rb->write_pos] = val;
    rb->write_pos = (rb->write_pos + 1) % MAX_CAPACITY;
    rb->active_elements++;
}

// 6. دالة السحب
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

// 7. الدالة الرئيسية بتنسيق مختلف
int main() {
    RingBuffer myRing;
    setupBuffer(&myRing);

    char input_text[64]; // زيادة الحجم قليلاً للتغيير
    printf("Enter Student Name: ");
    scanf("%s", input_text);

    // إضافة اللاحقة بأسلوب مختلف
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

    printf("\n\nTask finished successfully.\n");

    return 0;
}
