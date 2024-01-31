#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct
{
    char name[50];
    char unit[20];
    int quantity;
    float price;
    time_t lastArrivalDate;
} Product;

Product inventory[100];
int currentInventorySize = 0;

// Завантаження
void loadProduct()
{
    printf("\nВи обрали опцію 'Завантажити товар'.\n");

    if (currentInventorySize < 100)
    {
        printf("\nВведіть назву товару: ");
        scanf("%s", inventory[currentInventorySize].name);

        printf("Введіть одиниці виміру товару: ");
        scanf("%s", inventory[currentInventorySize].unit);

        printf("Введіть кількість товару: ");
        scanf("%d", &inventory[currentInventorySize].quantity);

        printf("Введіть ціну товару: ");
        scanf("%f", &inventory[currentInventorySize].price);

        inventory[currentInventorySize].lastArrivalDate = time(NULL);

        currentInventorySize++;

        printf("Товар успішно завантажено!\n");
    }
    else
    {
        printf("\nІнвентар повний. Неможливо завантажити більше товарів.\n");
    }
}

// Відвантаження
void unloadProduct()
{
    if (currentInventorySize > 0)
    {
        printf("\nВи обрали опцію 'Відвантажити товар'.\n");

        printf("Доступно для відвантаження:\n");
        printf("Індекс\tНазва товару\tОдиниці виміру\tКількість\tДата завозу\n");
        for (int i = 0; i < currentInventorySize; i++)
        {
            struct tm *arrivalDate = localtime(&inventory[i].lastArrivalDate);
            printf("%-6d\t%-20s\t%-15s\t%-9d\t%02d/%02d/%04d %02d:%02d:%02d\n", i + 1, inventory[i].name, inventory[i].unit,
                   inventory[i].quantity, arrivalDate->tm_mday, arrivalDate->tm_mon + 1, arrivalDate->tm_year + 1900,
                   arrivalDate->tm_hour, arrivalDate->tm_min, arrivalDate->tm_sec);
        }

        int unloadIndex;
        do
        {
            printf("Виберіть індекс товару для відвантаження (або 0 для виходу): ");
            scanf("%d", &unloadIndex);

            if (unloadIndex == 0)
            {
                printf("Скасування відвантаження. Повернення до головного меню.\n");
                break;
            }

            if (unloadIndex >= 1 && unloadIndex <= currentInventorySize)
            {
                int unloadQuantity;
                printf("Введіть кількість товару для відвантаження: ");
                scanf("%d", &unloadQuantity);

                if (unloadQuantity > 0)
                {
                    if (unloadQuantity <= inventory[unloadIndex - 1].quantity)
                    {
                        inventory[unloadIndex - 1].quantity -= unloadQuantity;
                        printf("Товар успішно відвантажено!\n");

                        if (inventory[unloadIndex - 1].quantity == 0)
                        {
                            currentInventorySize--;
                        }
                        break;
                    }
                    else
                    {
                        printf("Недостатня кількість товару для відвантаження. Повторіть введення.\n");
                    }
                }
                else
                {
                    printf("Введено неправильну кількість товару для відвантаження. Повторіть введення.\n");
                }
            }
            else
            {
                printf("Невірний індекс товару. Повторіть введення.\n");
            }
        } while (1);
    }
    else
    {
        printf("Інвентар порожній. Немає товару для відвантаження.\n");
    }
}

// Прибуткова накладна
void loadInvoice()
{
    if (currentInventorySize > 0)
    {
        printf("\nСформовано прибуткову накладну:\n");
        printf("Назва товару\tОдиниці виміру\tКількість\tЦіна за одиницю\tСума\n");
        printf("--------------------------------------------------------------\n");

        float totalRevenue = 0;

        for (int i = 0; i < currentInventorySize; i++)
        {
            float totalProductRevenue = inventory[i].quantity * inventory[i].price;
            totalRevenue += totalProductRevenue;

            printf("%-20s\t%-15s\t%-9d\t%-16.2f\t%-10.2f\n", inventory[i].name, inventory[i].unit,
                   inventory[i].quantity, inventory[i].price, totalProductRevenue);
        }

        printf("--------------------------------------------------------------\n");
        printf("Загальний прибуток: %.2f\n", totalRevenue);
    }
    else
    {
        printf("Інвентар порожній. Немає товару для формування накладної.\n");
    }
}

// Редагувати дані
void editProduct()
{
    if (currentInventorySize > 0)
    {
        printf("\nВи обрали опцію 'Редагувати дані про товар'.\n");

        printf("Доступно для редагування:\n");
        printf("Індекс\tНазва товару\tОдиниці виміру\tКількість\tДата завозу\n");
        for (int i = 0; i < currentInventorySize; i++)
        {
            struct tm *arrivalDate = localtime(&inventory[i].lastArrivalDate);
            printf("%-6d\t%-20s\t%-15s\t%-9d\t%02d/%02d/%04d %02d:%02d:%02d\n", i + 1, inventory[i].name, inventory[i].unit,
                   inventory[i].quantity, arrivalDate->tm_mday, arrivalDate->tm_mon + 1, arrivalDate->tm_year + 1900,
                   arrivalDate->tm_hour, arrivalDate->tm_min, arrivalDate->tm_sec);
        }

        int editIndex;
        do
        {
            printf("Виберіть індекс товару для редагування (або 0 для виходу): ");
            scanf("%d", &editIndex);

            if (editIndex == 0)
            {
                printf("Скасування редагування. Повернення до головного меню.\n");
                break;
            }

            if (editIndex >= 1 && editIndex <= currentInventorySize)
            {
                printf("Редагування товару '%s':\n", inventory[editIndex - 1].name);

                printf("Нова назва товару: ");
                scanf("%s", inventory[editIndex - 1].name);

                printf("Нові одиниці виміру: ");
                scanf("%s", inventory[editIndex - 1].unit);

                printf("Нова кількість товару: ");
                scanf("%d", &inventory[editIndex - 1].quantity);

                printf("Нова ціна товару: ");
                scanf("%f", &inventory[editIndex - 1].price);

                printf("Товар успішно відредаговано!\n");
                break;
            }
            else
            {
                printf("Невірний індекс товару. Повторіть введення.\n");
            }
        } while (1);
    }
    else
    {
        printf("Інвентар порожній. Немає товару для редагування.\n");
    }
}

// Видалити продукт
void deleteProduct()
{
    if (currentInventorySize > 0)
    {
        printf("\nВи обрали опцію 'Видалити товар'.\n");

        printf("Доступно для видалення:\n");
        printf("Індекс\tНазва товару\tОдиниці виміру\tКількість\tДата завозу\n");
        for (int i = 0; i < currentInventorySize; i++)
        {
            struct tm *arrivalDate = localtime(&inventory[i].lastArrivalDate);
            printf("%-6d\t%-20s\t%-15s\t%-9d\t%02d/%02d/%04d %02d:%02d:%02d\n", i + 1, inventory[i].name, inventory[i].unit,
                   inventory[i].quantity, arrivalDate->tm_mday, arrivalDate->tm_mon + 1, arrivalDate->tm_year + 1900,
                   arrivalDate->tm_hour, arrivalDate->tm_min, arrivalDate->tm_sec);
        }

        int deleteIndex;
        do
        {
            printf("Виберіть індекс товару для видалення (або 0 для виходу): ");
            scanf("%d", &deleteIndex);

            if (deleteIndex == 0)
            {
                printf("Скасування видалення. Повернення до головного меню.\n");
                break;
            }

            if (deleteIndex >= 1 && deleteIndex <= currentInventorySize)
            {
                for (int i = deleteIndex - 1; i < currentInventorySize - 1; i++)
                {
                    // Переміщення наступних товарів на один елемент назад
                    strcpy(inventory[i].name, inventory[i + 1].name);
                    strcpy(inventory[i].unit, inventory[i + 1].unit);
                    inventory[i].quantity = inventory[i + 1].quantity;
                    inventory[i].price = inventory[i + 1].price;
                    inventory[i].lastArrivalDate = inventory[i + 1].lastArrivalDate;
                }

                currentInventorySize--;
                printf("Товар успішно видалено!\n");
                break;
            }
            else
            {
                printf("Невірний індекс товару. Повторіть введення.\n");
            }
        } while (1);
    }
    else
    {
        printf("Інвентар порожній. Немає товару для видалення.\n");
    }
}

// Шукати продукт
void searchProduct()
{
    if (currentInventorySize > 0)
    {
        printf("\nВи обрали опцію 'Пошук за параметром'.\n");

        printf("Оберіть параметр пошуку:\n");
        printf("1. Назва товару\n");
        printf("2. Одиниці виміру\n");
        printf("3. Кількість товару\n");
        printf("4. Ціна товару\n");
        printf("5. Дата завозу\n");

        int searchOption;
        printf("Ваш вибір: ");
        scanf("%d", &searchOption);

        int found = 0; // Flag to check if any matching items are found

        switch (searchOption)
        {
        case 1:
        {
            char searchName[50];
            printf("Введіть назву товару для пошуку: ");
            scanf("%s", searchName);

            printf("\nРезультати пошуку за назвою товару '%s':\n", searchName);
            printf("╔====================╦===================╦=============╦===============╦=======================╦===================╗\n");
            printf("║    Найменування    ║ Одиниці виміру    ║     Ціна    ║    Кількість  ║ Дата постачання       ║ Загальна вартість ║\n");
            printf("╠====================╬===================╬=============╬===============╬=======================╬===================╣\n");
            for (int i = 0; i < currentInventorySize; i++)
            {
                if (strcmp(inventory[i].name, searchName) == 0)
                {
                    struct tm *arrivalDate = localtime(&inventory[i].lastArrivalDate);
                    printf("║ %-18.20s ║ %-17.15s ║ %-11.2f ║ %-13d ║  %02d/%02d/%04d  %02d:%02d:%02d ║ %-17.2f ║\n",
                           inventory[i].name, inventory[i].unit,
                           inventory[i].price,
                           inventory[i].quantity,
                           arrivalDate->tm_mday, arrivalDate->tm_mon + 1, arrivalDate->tm_year + 1900,
                           arrivalDate->tm_hour, arrivalDate->tm_min, arrivalDate->tm_sec,
                           inventory[i].price * inventory[i].quantity);

                    found = 1;
                }
            }
            printf("╚====================╩===================╩=============╩===============╩=======================╩===================╝\n");
        }
        break;

        default:
            printf("\nНеправильний вибір параметра пошуку.\n");
        }

        if (!found)
        {
            printf("Товар за вказаними параметрами не знайдено.\n");
        }
    }
    else
    {
        printf("Інвентар порожній. Немає товару для пошуку.\n");
    }
}

// Інвентарний висновок
void displayInventory()
{
    printf("\nВи обрали опцію 'Інвентарний висновок'.\n");

    if (currentInventorySize > 0)
    {
        printf("\nІнвентарний висновок:\n");
        printf("╔====================╦===================╦=============╦===============╦=======================╦===================╗\n");
        printf("║    Найменування    ║ Одиниці виміру    ║     Ціна    ║    Кількість  ║ Дата постачання       ║ Загальна вартість ║\n");
        printf("╠====================╬===================╬=============╬===============╬=======================╬===================╣\n");
        for (int i = 0; i < currentInventorySize; i++)
        {
            struct tm *arrivalDate = localtime(&inventory[i].lastArrivalDate);
            printf("║ %-20.20s ║ %-15.15s ║ %-11.2f ║ %-13d ║  %02d/%02d/%04d  %02d:%02d:%02d ║ %-17.2f ║\n",
                   inventory[i].name, inventory[i].unit,
                   inventory[i].price,
                   inventory[i].quantity,
                   arrivalDate->tm_mday, arrivalDate->tm_mon + 1, arrivalDate->tm_year + 1900,
                   arrivalDate->tm_hour, arrivalDate->tm_min, arrivalDate->tm_sec,
                   inventory[i].price * inventory[i].quantity);
        }
        printf("╚====================╩===================╩=============╩===============╩=======================╩===================╝\n");
    }
    else
    {
        printf("Інвентар порожній. Немає товару для відвантаження.\n");
    }
}

int main()
{
    int choice;

    do
    {
        printf("┌────────────────────────────────────────────┐\n");
        printf("│                   СКЛАД                    │\n");
        printf("├────────────────────────────────────────────┤\n");
        printf("│ 1. Завантажити товар                       │\n");
        printf("│ 2. Відвантажити товар                      │\n");
        printf("│ 3. Дата останнього завозу                  │\n");
        printf("│ 4. Сформувати прибуткову накладну          │\n");
        printf("│ 5. Сформувати видаткову накладну           │\n");
        printf("│ 6. Пошук за параметром                     │\n");
        printf("│ 7. Редагувати дані про товар               │\n");
        printf("│ 8. Видалити товар                          │\n");
        printf("│ 9. Інвентарний висновок                    │\n");
        printf("│10. Вихід                                   │\n");
        printf("└────────────────────────────────────────────┘\n");

        printf("Оберіть опцію (1-10): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            loadProduct();
            break;
        case 2:
            unloadProduct();
            break;
        case 3:
            unloadProduct();
            break;
        case 4:
            loadInvoice();
            break;
        case 9:
            displayInventory();
            break;
        case 10:
            printf("\nВихід з програми. Дякуємо!\n");
            break;
        default:
            printf("\nНеправильний вибір. Спробуйте ще раз.\n");
        }

        printf("\nНатисніть Enter для продовження...\n");

    } while (choice != 10);

    return 0;
}