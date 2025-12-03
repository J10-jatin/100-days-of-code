#include <stdio.h>
#include <string.h>

struct Expense {
    char date[15], cat[30], desc[100];
    int amount;
};

struct Expense e;

void addExp(), viewExp(), delExp(), summary();

int main() {
    int ch;
    while (1) {
        printf("\n--- EXPENSE TRACKER ---\n");
        printf("1. Add\n2. View\n3. Delete\n4. Summary\n5. Exit\nChoice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addExp(); break;
            case 2: viewExp(); break;
            case 3: delExp(); break;
            case 4: summary(); break;
            case 5: return 0;
            default: printf("Invalid!\n");
        }
    }
}

void addExp() {
    FILE *fp = fopen("expenses.txt", "a");
    if (!fp) return;

    printf("Date (DD-MM-YYYY): ");
    scanf("%s", e.date);

    printf("Category: ");
    scanf("%s", e.cat);

    printf("Amount: ");
    scanf("%d", &e.amount);

    printf("Description: ");
    scanf(" %[^\n]", e.desc);

    fprintf(fp, "%s %s %d %s\n", e.date, e.cat, e.amount, e.desc);
    fclose(fp);

    printf("Added.\n");
}

void viewExp() {
    FILE *fp = fopen("expenses.txt", "r");
    if (!fp) { printf("No records!\n"); return; }

    printf("\nDate\t\tCat\tAmt\tDesc\n");

    while (fscanf(fp, "%s %s %d %[^\n]", e.date, e.cat, &e.amount, e.desc) != EOF)
        printf("%s\t%s\t%d\t%s\n", e.date, e.cat, e.amount, e.desc);

    fclose(fp);
}

void delExp() {
    FILE *fp = fopen("expenses.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char d[20];
    int found = 0;

    if (!fp) { printf("No records!\n"); return; }

    printf("Enter date to delete: ");
    scanf("%s", d);

    while (fscanf(fp, "%s %s %d %[^\n]", e.date, e.cat, &e.amount, e.desc) != EOF) {
        if (strcmp(e.date, d) == 0) {
            found = 1;
            continue;
        }
        fprintf(temp, "%s %s %d %s\n", e.date, e.cat, e.amount, e.desc);
    }

    fclose(fp);
    fclose(temp);
    remove("expenses.txt");
    rename("temp.txt", "expenses.txt");

    found ? printf("Deleted.\n") : printf("Not found.\n");
}

void summary() {
    FILE *fp = fopen("expenses.txt", "r");
    int total = 0;

    if (!fp) { printf("No records!\n"); return; }

    while (fscanf(fp, "%s %s %d %[^\n]", e.date, e.cat, &e.amount, e.desc) != EOF)
        total += e.amount;

    fclose(fp);

    printf("Total expenses = %d\n", total);
}
