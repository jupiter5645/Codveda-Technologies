#include <stdio.h>
#include <stdlib.h>


struct StackNode {
    int data;
    struct StackNode* next;
};


struct QueueNode {
    int data;
    struct QueueNode* next;
};


struct StackNode* createStackNode(int data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(struct StackNode** top, int data) {
    struct StackNode* newNode = createStackNode(data);
    newNode->next = *top;
    *top = newNode;
    printf("%d pushed to stack\n", data);
}

int pop(struct StackNode** top) {
    if (*top == NULL) {
        printf("Stack underflow\n");
        return -1; 
    }
    struct StackNode* temp = *top;
    int poppedData = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedData;
}

void displayStack(struct StackNode* top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}


struct QueueNode* createQueueNode(int data) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(struct QueueNode** front, struct QueueNode** rear, int data) {
    struct QueueNode* newNode = createQueueNode(data);
    if (*rear == NULL) {
        *front = *rear = newNode;
        printf("%d enqueued to queue\n", data);
        return;
    }
    (*rear)->next = newNode;
    *rear = newNode;
    printf("%d enqueued to queue\n", data);
}

int dequeue(struct QueueNode** front) {
    if (*front == NULL) {
        printf("Queue underflow\n");
        return -1; 
    }
    struct QueueNode* temp = *front;
    int dequeuedData = temp->data;
    *front = (*front)->next;
    if (*front == NULL) {
        printf("Queue is now empty\n");
    }
    free(temp);
    return dequeuedData;
}

void displayQueue(struct QueueNode* front) {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    while (front != NULL) {
        printf("%d ", front->data);
        front = front->next;
    }
    printf("\n");
}


int main() {
    struct StackNode* stackTop = NULL;
    struct QueueNode* queueFront = NULL;
    struct QueueNode* queueRear = NULL;

    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push to Stack\n");
        printf("2. Pop from Stack\n");
        printf("3. Display Stack\n");
        printf("4. Enqueue to Queue\n");
        printf("5. Dequeue from Queue\n");
        printf("6. Display Queue\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                push(&stackTop, data);
                break;
            case 2:
                data = pop(&stackTop);
                if (data != -1) {
                    printf("Popped from stack: %d\n", data);
                }
                break;
            case 3:
                displayStack(stackTop);
                break;
            case 4:
                printf("Enter data to enqueue: ");
                scanf("%d", &data);
                enqueue(&queueFront, &queueRear, data);
                break;
            case 5:
                data = dequeue(&queueFront);
                if (data != -1) {
                    printf("Dequeued from queue: %d\n", data);
                }
                break;
            case 6:
                displayQueue(queueFront);
                break;
            case 7:
                exit(0 );
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
