#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 50

struct vehicle_details{
    char reg_no[10];
    char name[MAX_LEN];
    char address[MAX_LEN];
    char vehicle_type[20];
};

void add_record();
void display_records();
void delete_record(char reg_no[10]);
void edit_record(char reg_no[10]);
void search_by_name(char name[MAX_LEN]);
void search_by_reg_no(char reg_no[10]);
void search_by_vt(char vehicle_type[10]);
void admin_mode();
void user_mode();

int main() {
    int choice;
    do {
        printf("\nRTO Management System\n");
        printf("\t MAIN MENU \t\n");
        printf("1. Admin Mode\n");
        printf("2. User Mode\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                admin_mode();
                break;
            case 2:
                user_mode();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 0);
    return 0;
}

void user_mode() {
    char id[20], password[20];
    printf("\nEnter User ID: ");
    scanf("%s", id);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(id, "user") == 0 && strcmp(password, "user") == 0) {
        int choice;
        do {
            printf("\nUser Mode\n");
            printf("1. Display Records\n");
            printf("2. Search data by Registration Number\n");
            printf("3. Search data by Owner's Name\n");
            printf("4. Search data by Vehicle Type\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    display_records();
                    break;
                case 2: {
                    char reg_no[10];
                    printf("Enter registration number to search: ");
                    scanf("%s", reg_no);
                    search_by_reg_no(reg_no);
                    break;
                }
                case 3: {
                    char name[MAX_LEN];
                    printf("Enter owner's name to search: ");
                    scanf("%s", name);
                    search_by_name(name);
                    break;
                }
                case 4: {
                    char vehicle_type[10];
                    printf("Enter Vehicle Type to search: ");
                    scanf("%s", vehicle_type);
                    search_by_vt(vehicle_type);
                    break;
                }
                case 0:
                    printf("Exiting User Mode...\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 0);
    } else {
        printf("Invalid ID or Password!\n");
    }
}


void admin_mode() {
    char id[20], password[20];
    printf("\nEnter Admin ID: ");
    scanf("%s", id);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(id, "admin") == 0 && strcmp(password, "admin") == 0) {
        int choice;
        do {
            printf("\nAdmin Mode\n");
            printf("1. Add Record\n");
            printf("2. Display Records\n");
            printf("3. Search data by Registration Number\n");
            printf("4. Search data by Owner's Name\n");
            printf("5. Search data by Vehicle Type\n");
            printf("6. Delete Record\n");
            printf("7. Edit Record\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    add_record();
                    break;
                case 2:
                    display_records();
                    break;
                case 3: {
                    char reg_no[10];
                    printf("Enter registration number to search: ");
                    scanf("%s", reg_no);
                    search_by_reg_no(reg_no);
                    break;
                }
                case 4: {
                    char name[MAX_LEN];
                    printf("Enter owner's name to search: ");
                    scanf("%s", name);
                    search_by_name(name);
                    break;
                }
                case 5: {
                    char vehicle_type[10];
                    printf("Enter Vehicle Type to search: ");
                    scanf("%s", vehicle_type);
                    search_by_vt(vehicle_type);
                    break;
                }
                case 6: {
                    char reg_no[10];
                    printf("Enter the Registration Number to be deleted: ");
                    scanf("%s", reg_no);
                    delete_record(reg_no);
                    break;
                }
                case 7: {
                    char reg_no[10];
                    printf("Enter the Registration Number to be edited: ");
                    scanf("%s", reg_no);
                    edit_record(reg_no);
                    break;
                }
                case 0:
                    printf("Exiting Admin Mode...\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 0);
    } else {
        printf("Invalid ID or Password!\n");
    }
}

void add_record() {
    struct vehicle_details v;
    FILE *fp;
    fp = fopen("vehicle_details.txt", "a");
    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }
    printf("Enter Registration Number: ");
    scanf("%s", v.reg_no);
    printf("Enter Owner's Name: ");
    scanf("%s", v.name);
    printf("Enter Owner's Address: ");
    scanf("%s", v.address);
    printf("Enter Vehicle Type: ");
    scanf("%s", v.vehicle_type);
    fprintf(fp, "%s\t%s\t%s\t%s\n", v.reg_no, v.name, v.address, v.vehicle_type);
    fclose(fp);
    printf("\nRecord added successfully.");
}

void display_records() {
    struct vehicle_details v;
    FILE *fp;
    fp = fopen("vehicle_details.txt", "r");
    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }
    printf("+------------+------------+----------------------+--------------+\n");
    printf("| Reg. No.   | Name       | Address              | Vehicle Type |\n");
    printf("+------------+------------+----------------------+--------------+\n");
    int items_read;
    while ((items_read = fscanf(fp, "%s\t%s\t%s\t%s\n", v.reg_no, v.name, v.address, v.vehicle_type)) != EOF) {
        if (items_read < 1) {
            break;
        }
        printf("| %-10s | %-10s | %-20s | %-12s |\n", v.reg_no, v.name, v.address, v.vehicle_type);
    }
    printf("+-----------+----------+-----------------------+--------------+\n");
    fclose(fp);
}

void delete_record(char reg_no[10]) {
    struct vehicle_details v;
    int flag = 0;
    FILE *fp, *ft;
    fp = fopen("vehicle_details.txt", "r");
    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }
    ft = fopen("temp.txt", "w");
    if (ft == NULL) {
        printf("File does not exist.\n");
        fclose(fp);
        return;
    }
    while (fscanf(fp, "%s\t%s\t%s\t%s\n", v.reg_no, v.name, v.address, v.vehicle_type) != EOF) {
        if (strcmp(v.reg_no, reg_no) != 0) {
            fprintf(ft, "%s\t%s\t%s\t%s\n", v.reg_no, v.name, v.address, v.vehicle_type);
        } else {
            flag = 1;
        }
    }
    fclose(fp);
    fclose(ft);
    if (flag == 0) {
        printf("Record not found.\n");
        return;
    }
    remove("vehicle_details.txt");
    rename("temp.txt", "vehicle_details.txt");
    printf("Record deleted successfully.\n");
}

void edit_record(char reg_no[10]) {
    struct vehicle_details v, temp;
    int flag = 0;
    FILE *fp, *ft;
    fp = fopen("vehicle_details.txt", "r");
    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }
    ft = fopen("temp.txt", "w");
    if (ft == NULL) {
        printf("File does not exist.\n");
        fclose(fp);
        return;
    }
    while (fscanf(fp, "%s\t%s\t%s\t%s\n", v.reg_no, v.name, v.address, v.vehicle_type) != EOF) {
        if (strcmp(v.reg_no, reg_no) == 0) {
            flag = 1;
            printf("Enter new registration number: ");
            scanf("%s", temp.reg_no);
            printf("Enter new name: ");
            scanf("%s", temp.name);
            printf("Enter new address: ");
            scanf("%s", temp.address);
            printf("Enter new vehicle type: ");
            scanf("%s", temp.vehicle_type);
            fprintf(ft, "%s\t%s\t%s\t%s\n", temp.reg_no, temp.name, temp.address, temp.vehicle_type);
        } else {
            fprintf(ft, "%s\t%s\t%s\t%s\n", v.reg_no, v.name, v.address, v.vehicle_type);
        }
    }
    fclose(fp);
    fclose(ft);
    if (flag == 0) {
        printf("Record not found.\n");
        return;
    }
    remove("vehicle_details.txt");
    rename("temp.txt", "vehicle_details.txt");
    printf("Record updated successfully.\n");
}

void search_by_name(char name[MAX_LEN]) {
    struct vehicle_details v;
    int flag = 0;
    FILE *fp;
    fp = fopen("vehicle_details.txt", "r");
    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }
    printf("+-----------+----------+-----------------------+--------------+\n");
    printf("| Reg. No.  | Name     | Address               | Vehicle Type |\n");
    printf("+-----------+----------+-----------------------+--------------+\n");
    while (fscanf(fp, "%s\t%s\t%s\t%s\n", v.reg_no, v.name, v.address, v.vehicle_type) != EOF) {
        if (strcmp(v.name, name) == 0) {
            flag = 1;
            printf("| %-10s | %-10s | %-20s | %-12s |\n", v.reg_no, v.name, v.address, v.vehicle_type);
        }
    }
    if (flag == 1) {
        printf("+-----------+----------+-----------------------+--------------+\n");
        printf("\n Searched by Owner's Name\n\n");
    }
    fclose(fp);
    if (flag == 0) {
        printf("No record found with the given owner's name.\n");
        printf("+-----------+----------+-----------------------+--------------+\n");
    }
}

void search_by_reg_no(char reg_no[10]) {
    struct vehicle_details v;
    int flag = 0;
    FILE *fp;
    fp = fopen("vehicle_details.txt", "r");
    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }
    printf("+-----------+----------+-----------------------+--------------+\n");
    printf("| Reg. No.  | Name     | Address               | Vehicle Type |\n");
    printf("+-----------+----------+-----------------------+--------------+\n");
    while (fscanf(fp, "%s\t%s\t%s\t%s\n", v.reg_no, v.name, v.address, v.vehicle_type) != EOF) {
        if (strcmp(v.reg_no, reg_no) == 0) {
            flag = 1;
            printf("| %-10s | %-10s | %-20s | %-12s |\n", v.reg_no, v.name, v.address, v.vehicle_type);
        }
    }
    if (flag == 1) {
        printf("+-----------+----------+-----------------------+--------------+\n");
        printf("\n Searched by Registration Number\n\n");
    }
    fclose(fp);
    if (flag == 0) {
        printf("No record found with the given registration number.\n");
        printf("+-----------+----------+-----------------------+--------------+\n");
    }
}

void search_by_vt(char vehicle_type[10]) {
    struct vehicle_details v;
    int flag = 0;
    FILE *fp;
    fp = fopen("vehicle_details.txt", "r");
    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }
    printf("+-----------+----------+-----------------------+--------------+\n");
    printf("| Reg. No.  | Name     | Address               | Vehicle Type |\n");
    printf("+-----------+----------+-----------------------+--------------+\n");
    while (fscanf(fp, "%s\t%s\t%s\t%s\n", v.reg_no, v.name, v.address, v.vehicle_type) != EOF) {
        if (strcmp(v.vehicle_type, vehicle_type) == 0) {
            flag = 1;
            printf("| %-10s | %-10s | %-20s | %-12s |\n", v.reg_no, v.name, v.address, v.vehicle_type);
        }
    }
    if (flag == 1) {
        printf("+-----------+----------+-----------------------+--------------+\n");
        printf("\n Searched by Vehicle Type\n\n");
    }
    fclose(fp);
    if (flag == 0) {
        printf("No record found with the given vehicle type.\n");
        printf("+-----------+----------+-----------------------+--------------+\n");
    }
}

