#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для узла бинарного дерева
struct TreeNode {
    char* word;
    int frequency;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Функция для создания нового узла
struct TreeNode* createNode(const char* word) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->word = strdup(word);
    node->frequency = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для вставки узла в бинарное дерево
struct TreeNode* insertNode(struct TreeNode* root, const char* word) {
    if (root == NULL) {
        return createNode(word);
    }

    int cmp = strcmp(word, root->word);
    if (cmp == 0) {
        root->frequency++;
    } else if (cmp < 0) {
        root->left = insertNode(root->left, word);
    } else {
        root->right = insertNode(root->right, word);
    }

    return root;
}

// Функция для вывода уникальных слов и их частоты повторения
void printUniqueWords(struct TreeNode* root, const char* order) {
    if (root == NULL) {
        return;
    }

    if (strcmp(order, "DESC") == 0) {
        printUniqueWords(root->right, "DESC");
        printf("%s: %d\n", root->word, root->frequency);
        printUniqueWords(root->left, "DESC");
    } else {
        printUniqueWords(root->left, "ASC");
        printf("%s: %d\n", root->word, root->frequency);
        printUniqueWords(root->right, "ASC");
    }
}

// Функция для освобождения памяти, выделенной для бинарного дерева
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root->word);
    free(root);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename> [-o ASC|DESC]\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    char* order = "ASC";

    if (argc >= 4 && strcmp(argv[2], "-o") == 0) {
        order = argv[3];
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file: %s\n", filename);
        return 1;
    }

    struct TreeNode* root = NULL;
    char word[256];

    // Чтение слов из файла и вставка их в бинарное дерево
    while (fscanf(file, "%s", word) == 1) {
        root = insertNode(root, word);
    }

    fclose(file);

    // Вывод уникальных слов в алфавитном порядке и их частоты повторения
    printf("Unique words in %s:\n", filename);
    printUniqueWords(root, order);

    // Освобождение памяти
    freeTree(root);

    return 0;
}
