#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct LinkedList {
    struct Node *head;
    int size;
};

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode -> data = data;
    newNode -> next = NULL;
    return newNode;
}

struct LinkedList *createLinkedList() {
    struct LinkedList *list = (struct LinkedList *) malloc(sizeof(struct LinkedList));
    list -> head = NULL;
    list -> size = 0;
    return list;
}

void add(struct LinkedList *list, int item) {
    struct Node *newNode = createNode(item);
    if (list -> head == NULL) {
        list -> head = newNode;
    } else {
        struct Node *current = list -> head;
        while (current -> next != NULL) {
            current = current -> next;
        }
        current -> next = newNode;
    }
    list -> size++;
}

void insert(struct LinkedList *list, int index, int item) {
    if (index < 0 || index > list -> size) {
        printf("Error: Invalid index to insert\n");
        return;
    }
    struct Node *newNode = createNode(item);
    if (index == 0) {
        newNode -> next = list -> head;
        list -> head = newNode;
    } else {
        struct Node *current = list -> head;
        for (int i = 0; i < index - 1; i++) {
            current = current -> next;
        }
        newNode -> next = current -> next;
        current -> next = newNode;
    }
    list -> size++;
    printf("\nItem inserted.\n");
}

int size(struct LinkedList *list) {
    return list -> size;
}

void removeElement(struct LinkedList *list, int index) {
    if (index < 0 || index >= list -> size) {
        printf("\nError: Invalid index to delete\n");
        return;
    }
    if (index == 0) {
        struct Node *temp = list -> head;
        list -> head = list -> head -> next;
        free(temp);
    } else {
        struct Node *current = list -> head;
        for (int i = 0; i < index - 1; i++) {
            current = current -> next;
        }
        struct Node *temp = current -> next;
        current -> next = temp -> next;
        free(temp);
    }
    list -> size--;
    printf("\nItem removed.\n");
}

void set(struct LinkedList *list, int index, int item) {
    if (index < 0 || index >= list -> size) {
        printf("\nError: Invalid index to replace\n");
        return;
    }
    struct Node *current = list -> head;
    for (int i = 0; i < index; i++) {
        current = current -> next;
    }
    current -> data = item;
    printf("\nЕлемент замінено.\n");
}

int get(struct LinkedList *list, int index) {
    if (index < 0 || index >= list -> size) {
        printf("\nError: Invalid index to retrieve\n");
        return -1;
    }
    struct Node *current = list -> head;
    for (int i = 0; i < index; i++) {
        current = current -> next;
    }
    return current -> data;
}

void printList(struct LinkedList *list) {
    struct Node *current = list -> head;
    while (current != NULL) {
        printf("%d ", current -> data);
        current = current -> next;
    }
    printf("\n");
}

void displayMenu() {
    printf("\nSelect an option:\n");
    printf("1. Add an item to the end of the list\n");
    printf("2. Insert element by index\n");
    printf("3. Get the number of items in a list\n");
    printf("4. Delete element by index\n");
    printf("5. Replace element by index\n");
    printf("6. Get the value by index\n");
    printf("7. Display the list\n");
    printf("0. Exit\n");
    printf("Your choice: ");
}

int main() {
    struct LinkedList *list = createLinkedList();

    int choice;
    int item, index;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value of the item: ");
                scanf("%d", &item);
                add(list, item);
                printf("The item is added to the end of the list.\n");
                break;
            case 2:
                if (list -> size == 0) {
                    printf("\nThe list is empty!\n");
                    break;
                }
                printf("Enter index to insert: ");
                scanf("%d", &index);
                printf("Enter the value of the item: ");
                scanf("%d", &item);
                insert(list, index, item);
                break;
            case 3:
                if (list -> size == 0) {
                    printf("\nThe list is empty!\n");
                    break;
                }
                printf("Number of items in the list: %d\n", size(list));
                break;
            case 4:
                if (list -> size == 0) {
                    printf("\nThe list is empty!\n");
                    break;
                }
                printf("Enter the index to delete: ");
                scanf("%d", &index);
                removeElement(list, index);
                break;
            case 5:
                if (list -> size == 0) {
                    printf("\nThe list is empty!\n");
                    break;
                }
                printf("Enter the index to replace: ");
                scanf("%d", &index);
                printf("Enter a new element value: ");
                scanf("%d", &item);
                set(list, index, item);
                break;
            case 6:
                if (list -> size == 0) {
                    printf("\nThe list is empty!\n");
                    break;
                }
                printf("Enter index to get: ");
                scanf("%d", &index);
                item = get(list, index);
                if (item != -1) {
                    printf("\nElement value: %d\n", item);
                }
                break;
            case 7:
                if (list -> size == 0) {
                    printf("\nThe list is empty!\n");
                    break;
                }
                printf("\nList: ");
                printList(list);
                break;
            case 0:
                free(list);
                return 0;
            default:
                printf("\nWrong choice. Try again.\n");
        }
    }
    return 0;
}