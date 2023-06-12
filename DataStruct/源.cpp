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
        printf("图书找到！位置序号：%d\n", position);
        printBook(list, position);
        return position;
    }
    else {
        printf("图书未找到！\n");
        return -1;
    }
}

void deleteBook(BookList* list, int position) {
    if (list->head == NULL) {
        printf("图书列表为空！\n");
        return;
    }

    if (position == 1) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        printf("删除成功！\n");
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
            printf("指定位置无效！\n");
        }
        else {
            previous->next = current->next;
            free(current);
            printf("删除成功！\n");
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
        printf("价格修改成功！\n");
    }
    else {
        printf("图书未找到！\n");
    }
}

void printBooks(BookList* list) {
    Node* current = list->head;

    while (current != NULL) {
        printf("ISBN: %s\n", current->book.ISBN);
        printf("书名: %s\n", current->book.title);
        printf("价格: %.2f\n", current->book.price);
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
    printf("========= 图书管理系统 =========\n");
    printf("1. 添加图书\n");
    printf("2. 查找图书\n");
    printf("3. 删除图书\n");
    printf("4. 修改图书价格\n");
    printf("5. 显示所有图书\n");
    printf("0. 退出\n");
    printf("==============================\n");
    printf("请输入选项：");
}

void saveBooksToFile(BookList* list) {
    FILE* file = fopen("D:\\QQ\\908997187\\FileRecv\\book.txt", "w, ccs=UTF-8");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    Node* current = list->head;

    while (current != NULL) {
        fprintf(file, "%s %s %.2f\n", current->book.ISBN, current->book.title, current->book.price);
        current = current->next;
    }

    fclose(file);
    printf("图书信息已保存到文件！\n");
}

void loadBooksFromFile(BookList* list) {
    FILE* file = fopen("D:\\QQ\\908997187\\FileRecv\\book.txt", "rb, ccs=UTF-8");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    char line[200];
    int lineNumber = 1; // 行号计数器

    while (fgets(line, sizeof(line), file)) {
        if (lineNumber > 1) { // 跳过第一行标签
            Book book;
            sscanf(line, "%s %s %f", book.ISBN, book.title, &book.price);
            insertBook(list, book);
        }
        lineNumber++;
    }

    fclose(file);
    printf("从文件加载图书信息成功！\n");
}

void printBook(BookList* list,int i) {
    BookList* booklist = list;
    int t = 0;
    while (t < i) {
        t++;
        list->head = list->head->next;
    }
    printf("ISBN: %s\n", list->head->book.ISBN);
    printf("书名: %s\n", list->head->book.title);
    printf("价格: %.2f\n", list->head->book.price);
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
            printf("退出程序...\n");
            break;
        case 1: {
            Book book;
            printf("请输入图书的ISBN：");
            scanf("%s", book.ISBN);
            printf("请输入图书的书名：");
            scanf("%s", book.title);
            printf("请输入图书的价格：");
            scanf("%f", &book.price);
            insertBook(&bookList, book);
            printf("图书添加成功！\n");
            break;
        }
        case 2:
            printf("请输入要查找的图书的ISBN或书名：");
            scanf("%s", key);
            searchBook(&bookList, key);
            break;
        case 3:
            printf("请输入要删除的图书的位置序号：");
            scanf("%d", &position);
            deleteBook(&bookList, position);
            break;
        case 4:
            printf("请输入要修改价格的图书的ISBN：");
            scanf("%s", key);
            printf("请输入新的价格：");
            scanf("%f", &newPrice);
            modifyPrice(&bookList, key, newPrice);
            break;
        case 5:
            printf("图书信息如下：\n");
            printBooks(&bookList);
            break;
        default:
            printf("无效选项！\n");
            break;
        }

        printf("\n");
    } while (choice != 0);

    saveBooksToFile(&bookList);

    freeList(&bookList);
}
