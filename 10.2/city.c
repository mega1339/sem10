#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITY_NAME_LENGTH 100
#define HASH_TABLE_SIZE 100

// Структура для хранения информации о городе
struct City {
    char name[MAX_CITY_NAME_LENGTH];
    int population;
    struct City* next;
};

// Хэш-таблица для хранения городов
struct CityHashTable {
    struct City* table[HASH_TABLE_SIZE];
};

// Функция для вычисления хэша строки (имени города)
unsigned int hash(const char* cityName) {
    unsigned int hashValue = 0;

    for (int i = 0; cityName[i] != '\0'; i++) {
        hashValue = 31 * hashValue + cityName[i];
    }

    return hashValue % HASH_TABLE_SIZE;
}

// Функция для добавления информации о городе в базу данных
void addCity(struct CityHashTable* hashTable, const char* cityName, int population) {
    unsigned int index = hash(cityName);

    // Создание нового узла с информацией о городе
    struct City* city = (struct City*)malloc(sizeof(struct City));
    strncpy(city->name, cityName, MAX_CITY_NAME_LENGTH);
    city->population = population;
    city->next = NULL;

    // Вставка узла в хэш-таблицу
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = city;
    } else {
        struct City* current = hashTable->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = city;
    }

    printf("City added: %s\n", cityName);
}

// Функция для удаления информации о городе из базы данных
void removeCity(struct CityHashTable* hashTable, const char* cityName) {
    unsigned int index = hash(cityName);

    // Поиск города в хэш-таблице
    struct City* current = hashTable->table[index];
    struct City* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, cityName) == 0) {
            // Удаление города из хэш-таблицы
            if (prev == NULL) {
                hashTable->table[index] = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            printf("City removed: %s\n", cityName);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("City not found: %s\n", cityName);
}

// Функция для вывода списка всех городов
void listCities(struct CityHashTable* hashTable) {
    printf("List of cities:\n");

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        struct City* current = hashTable->table[i];

        while (current != NULL) {
            printf("City: %s, Population: %d\n", current->name, current->population);
            current = current->next;
        }
    }
}

int main() {
    struct CityHashTable hashTable;

    // Инициализация хэш-таблицы
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable.table[i] = NULL;
    }

    int choice;
    char cityName[MAX_CITY_NAME_LENGTH];
    int population;

    do {
        printf("\nSelect an option:\n");
        printf("1. Add a city\n");
        printf("2. Remove a city\n");
        printf("3. List all cities\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter city name: ");
                scanf("%s", cityName);
                printf("Enter population: ");
                scanf("%d", &population);
                addCity(&hashTable, cityName, population);
                break;
            case 2:
                printf("Enter city name: ");
                scanf("%s", cityName);
                removeCity(&hashTable, cityName);
                break;
            case 3:
                listCities(&hashTable);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}
