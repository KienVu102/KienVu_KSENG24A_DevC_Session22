#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Students {
    char id[10];
    char fullName[100];
    int age;
};

void addStudents(struct Students student[], int *sizePtr) {
    fflush(stdin);
    printf("\nNhap ID: ");
    fgets(student[*sizePtr].id, 10, stdin);
    student[*sizePtr].id[strcspn(student[*sizePtr].id, "\n")] = '\0';
    printf("Nhap ho ten: ");
    fgets(student[*sizePtr].fullName, 100, stdin);
    student[*sizePtr].fullName[strcspn(student[*sizePtr].fullName, "\n")] = '\0';
    printf("Nhap tuoi: ");
    scanf("%d", &student[*sizePtr].age);
    (*sizePtr)++;
    printf("\n");
}

void saveToFile(struct Students student[], int *sizePtr) {
    FILE *file;
    file = fopen("student.bin", "wb");
    if (file == NULL) {
        printf("\nKhong the luu file\n\n");
        return;
    }
    fwrite(student, sizeof(struct Students), *sizePtr, file);
    fclose(file);
}

void loadToFile(struct Students student[], int *sizePtr) {
    FILE *file = fopen("student.bin", "rb");
    (*sizePtr) = 0;
    while (fread(&student[*sizePtr], sizeof(struct Students), 1, file) == 1 && *sizePtr < 100) {
        (*sizePtr)++;
    }
    if (*sizePtr != 0) {
        printf("\nLoad file thanh cong\n\n");
    }
    fclose(file);
}

void printStudents(struct Students student[], int *sizePtr) {
    if (*sizePtr == 0) {
        printf("\nDanh sach sinh vien trong\n\n");
    } else {
        printf("\nThong tin sinh vien\n");
        for (int i = 0; i < *sizePtr; i++) {
            printf("ID: %s", student[i].id);
            printf("\nHo ten: %s", student[i].fullName);
            printf("\nTuoi: %d", student[i].age);
            printf("\n==============\n");
        }
        printf("\n");
    }
}

void editStudents(struct Students student[], int *sizePtr) {
    fflush(stdin);
    char *id;
    int found = 0;
    id = (char *)calloc(10, sizeof(char));
    printf("\nNhap ID sinh vien muon sua thong tin: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *sizePtr; i++) {
        if (strstr(student[i].id, id) != NULL) {
            found = 1;
            printf("\nNhap ten sinh vien: ");
            fgets(student[i].fullName, 100, stdin);
            student[i].fullName[strcspn(student[i].fullName, "\n")] = '\0';
            printf("Nhap tuoi: ");
            scanf("%d", &student[i].age);
        }
    }
    if (found == 0) {
        printf("\nID sinh vien khong ton tai\n\n");
    } else {
        printf("\nSua thong tin hoan tat\n\n");
    }
    free(id);
}

void removeStudents(struct Students student[], int *sizePtr) {
    fflush(stdin);
    char *id;
    int found = 0;
    id = (char *)calloc(10, sizeof(char));
    printf("\nNhap ID sinh vien muon xoa: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *sizePtr; i++) {
        if (strstr(student[i].id, id) != NULL) {
            found = 1;
            for (int j = i; j < *sizePtr - 1; j++) {
                student[j] = student[j + 1];
            }
            (*sizePtr)--;
            break;
        }
    }
    if (found == 0) {
        printf("\nID sinh vien khong ton tai\n\n");
    } else {
        printf("\nXoa thanh cong\n\n");
    }
    free(id);
}

int main() {
    struct Students student[100];
    int size = 0, choice;
    int *sizePtr = &size;
    loadToFile(student, sizePtr);
    do {
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("7. Thoat\n");
        printf("Moi ban nhap chuc nang: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printStudents(student, sizePtr);
                break;
                
            case 2:
                addStudents(student, sizePtr);
                saveToFile(student, sizePtr);
                break;
                
            case 3:
                editStudents(student, sizePtr);
                saveToFile(student, sizePtr);
                break;
                
            case 4:
                removeStudents(student, sizePtr);
                saveToFile(student, sizePtr);
                break;
                
            case 5:
                break;
                
            case 6:
                break;
                
            case 7:
                printf("Thoat chuong trinh\n");
                break;
                
            default:
                printf("Lua chon khong hop le. Vui long thu lai!\n");
        }
    } while(choice != 7);
    return 0;
}

