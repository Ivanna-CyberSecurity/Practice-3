#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size;
    int capacity;
} ArrayList;

ArrayList *createArrayList(int capacity) {
    ArrayList *list = (ArrayList *) malloc(sizeof(ArrayList));
    if (list == NULL) {
        printf("An error occurred while allocating memory for the list.\n");
        return NULL;
    }
    list -> array = (int *) malloc(sizeof(int) * capacity);
    if (list -> array == NULL) {
        printf("An error occurred while allocating memory for the array.\n");
        free(list);
        return NULL;
    }
    list -> size = 0;
    list -> capacity = capacity;
    return list;
}

void add(ArrayList *list, int item) {
    if (list -> size >= list -> capacity) {
        list -> capacity *= 2;
        list -> array = (int *) realloc(list -> array, sizeof(int) * list -> capacity);
        if (list -> array == NULL) {
            printf("An error occurred while allocating memory for the array.\n");
            return;
        }
    }
    list -> array[list -> size] = item;
    list -> size++;
}

void insert(ArrayList *list, int index, int item) {
    if (index < 0 || index > list -> size) {
        printf("Invalid insert index.\n");
        return;
    }
    if (list -> size >= list -> capacity) {
        // Збільшення ємності списку, якщо потрібно
        list -> capacity *= 2;
        list -> array = (int *) realloc(list -> array, sizeof(int) * list -> capacity);
        if (list -> array == NULL) {
            printf("Error allocating memory for the array.\n");
            return;
        }
    }
    for (int i = list -> size; i > index; i--) {
        list -> array[i] = list -> array[i - 1];
    }
    list -> array[index] = item;
    list -> size++;
}

int size(ArrayList *list) {
    return list -> size;
}

void removeAtIndex(ArrayList *list, int index) {
    if (index < 0 || index >= list -> size) {
        printf("Invalid index to delete.\n");
        return;
    }
    for (int i = index; i < list -> size - 1; i++) {
        list -> array[i] = list -> array[i + 1];
    }
    list -> size--;
}

void set(ArrayList *list, int index, int item) {
    if (index < 0 || index >= list -> size) {
        printf("Invalid index to modify.\n");
        return;
    }
    list -> array[index] = item;
}

void get(ArrayList *list, int index) {
    if (index < 0 || index >= list -> size) {
        printf("Invalid index to retrieve.\n");
        return;
    }
    if (list -> array[index] == 0 && list -> size == 0 || index > list -> size) {
        printf("Invalid index to retrieve.\n");
        return;
    }
    printf("Value by index %d: %d\n", index, list -> array[index]);
}

void display(ArrayList *list) {
    printf("List items: ");
    for (int i = 0; i < list -> size; i++) {
        printf("%d ", list -> array[i]);
    }
    printf("\n");
}

void destroyArrayList(ArrayList *list) {
    free(list -> array);
    free(list);
}

int main() {
    int capacity;
    printf("Enter the initial capacity of the list: ");
    scanf("%d", &capacity);

    ArrayList *list = createArrayList(capacity);
    if (list == NULL) {
        return 1;
    }

    int choice, item, index;

    do {
        printf("\nOperations menu:\n");
        printf("1. Add item to end of list\n");
        printf("2. Insert an element at the specified index\n");
        printf("3. Delete the element at the specified index\n");
        printf("4. Change the value of the element at the specified index\n");
        printf("5. Get the value of the element at the specified index\n");
        printf("6. Show list size\n");
        printf("7. Show all list items\n");
        printf("8. Go out\n");

        printf("Select an operation: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the item to add: ");
                scanf("%d", &item);
                add(list, item);
                break;
            case 2:
                if (list -> size == 0) {
                    printf("The list is empty.\n");
                    break;
                }
                printf("Enter index to insert: ");
                scanf("%d", &index);
                printf("Enter the element to insert: ");
                scanf("%d", &item);
                insert(list, index, item);
                break;
            case 3:
                if (list -> size == 0) {
                    printf("The list is empty.\n");
                    break;
                }
                printf("Enter the index to delete: ");
                scanf("%d", &index);
                removeAtIndex(list, index);
                break;
            case 4:
                if (list -> size == 0) {
                    printf("The list is empty.\n");
                    break;
                }
                printf("Enter the index to change: ");
                scanf("%d", &index);
                printf("Enter a new value: ");
                scanf("%d", &item);
                set(list, index, item);
                break;
            case 5:
                if (list -> size == 0) {
                    printf("The list is empty.\n");
                    break;
                }
                printf("Enter the index to retrieve: ");
                scanf("%d", &index);
                get(list, index);
                break;
            case 6:
                if (list -> size == 0) {
                    printf("The list is empty.\n");
                    break;
                }
                printf("List size: %d\n", size(list));
                break;
            case 7:
                if (list -> size == 0) {
                    printf("The list is empty.\n");
                    break;
                }
                display(list);
                break;
            case 8:
                break;
            default:
                printf("Incorrect choice of operation. Try again.\n");
                break;
        }
    } while (choice != 8);
    destroyArrayList(list);
    return 0;
}