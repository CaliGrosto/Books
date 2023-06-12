#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ISBN[200];
    char title[200];
    float price;
} Book;

typedef struct Node {
    Book book;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} BookList;
void printBook(BookList* list, int i);
Node* createNode(Book book) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->book = book;
    newNode->next = NULL;
    return newNode;
}

void insertBook(BookList* list, Book book) {
    Node* newNode = createNode(book);

    if (list->head == NULL) {
        list->head = newNode;
    }
    else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int searchBook(BookList* list, char* key) {
    Node* current = list->head;
    int position = 1;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->book.ISBN, key) == 0 || strcmp(current->book.title, key) == 0) {
            found = 1;
            break;
        }
        current = current->next;
        position++;
    }

    if (found) {
        printf("ͼ���ҵ���λ����ţ�%d\n", position);
        printBook(list, position);
        return position;
    }
    else {
        printf("ͼ��δ�ҵ���\n");
        return -1;
    }
}

void deleteBook(BookList* list, int position) {
    if (list->head == NULL) {
        printf("ͼ���б�Ϊ�գ�\n");
        return;
    }

    if (position == 1) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        printf("ɾ���ɹ���\n");
    }
    else {
        Node* current = list->head;
        Node* previous = NULL;
        int count = 1;

        while (current != NULL && count < position) {
            previous = current;
            current = current->next;
            count++;
        }

        if (current == NULL) {
            printf("ָ��λ����Ч��\n");
        }
        else {
            previous->next = current->next;
            free(current);
            printf("ɾ���ɹ���\n");
        }
    }
}

void modifyPrice(BookList* list, char* ISBN, float newPrice) {
    Node* current = list->head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->book.ISBN, ISBN) == 0) {
            found = 1;
            current->book.price = newPrice;
            break;
        }
        current = current->next;
    }

    if (found) {
        printf("�۸��޸ĳɹ���\n");
    }
    else {
        printf("ͼ��δ�ҵ���\n");
    }
}

void printBooks(BookList* list) {
    Node* current = list->head;

    while (current != NULL) {
        printf("ISBN: %s\n", current->book.ISBN);
        printf("����: %s\n", current->book.title);
        printf("�۸�: %.2f\n", current->book.price);
        printf("--------------------\n");

        current = current->next;
    }
}

void freeList(BookList* list) {
    Node* current = list->head;
    Node* temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    list->head = NULL;
}

void displayMenu() {
    printf("========= ͼ�����ϵͳ =========\n");
    printf("1. ���ͼ��\n");
    printf("2. ����ͼ��\n");
    printf("3. ɾ��ͼ��\n");
    printf("4. �޸�ͼ��۸�\n");
    printf("5. ��ʾ����ͼ��\n");
    printf("0. �˳�\n");
    printf("==============================\n");
    printf("������ѡ�");
}

void saveBooksToFile(BookList* list) {
    FILE* file = fopen("D:\\QQ\\908997187\\FileRecv\\book.txt", "w, ccs=UTF-8");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    Node* current = list->head;

    while (current != NULL) {
        fprintf(file, "%s %s %.2f\n", current->book.ISBN, current->book.title, current->book.price);
        current = current->next;
    }

    fclose(file);
    printf("ͼ����Ϣ�ѱ��浽�ļ���\n");
}

void loadBooksFromFile(BookList* list) {
    FILE* file = fopen("D:\\QQ\\908997187\\FileRecv\\book.txt", "rb, ccs=UTF-8");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    char line[200];
    int lineNumber = 1; // �кż�����

    while (fgets(line, sizeof(line), file)) {
        if (lineNumber > 1) { // ������һ�б�ǩ
            Book book;
            sscanf(line, "%s %s %f", book.ISBN, book.title, &book.price);
            insertBook(list, book);
        }
        lineNumber++;
    }

    fclose(file);
    printf("���ļ�����ͼ����Ϣ�ɹ���\n");
}

void printBook(BookList* list,int i) {
    BookList* booklist = list;
    int t = 0;
    while (t < i) {
        t++;
        list->head = list->head->next;
    }
    printf("ISBN: %s\n", list->head->book.ISBN);
    printf("����: %s\n", list->head->book.title);
    printf("�۸�: %.2f\n", list->head->book.price);
    printf("--------------------\n");
}
void main() {
    BookList bookList;
    bookList.head = NULL;

    int choice;
    char key[100];
    float newPrice;
    int position;

    loadBooksFromFile(&bookList);

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("�˳�����...\n");
            break;
        case 1: {
            Book book;
            printf("������ͼ���ISBN��");
            scanf("%s", book.ISBN);
            printf("������ͼ���������");
            scanf("%s", book.title);
            printf("������ͼ��ļ۸�");
            scanf("%f", &book.price);
            insertBook(&bookList, book);
            printf("ͼ����ӳɹ���\n");
            break;
        }
        case 2:
            printf("������Ҫ���ҵ�ͼ���ISBN��������");
            scanf("%s", key);
            searchBook(&bookList, key);
            break;
        case 3:
            printf("������Ҫɾ����ͼ���λ����ţ�");
            scanf("%d", &position);
            deleteBook(&bookList, position);
            break;
        case 4:
            printf("������Ҫ�޸ļ۸��ͼ���ISBN��");
            scanf("%s", key);
            printf("�������µļ۸�");
            scanf("%f", &newPrice);
            modifyPrice(&bookList, key, newPrice);
            break;
        case 5:
            printf("ͼ����Ϣ���£�\n");
            printBooks(&bookList);
            break;
        default:
            printf("��Чѡ�\n");
            break;
        }

        printf("\n");
    } while (choice != 0);

    saveBooksToFile(&bookList);

    freeList(&bookList);
}
