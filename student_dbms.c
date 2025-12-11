//School Student Database Management System

#include<stdio.h>

void addRecord();
void searchRecord();
void displayRecord();
void deleteRecord();

typedef struct{
    char name[25];
    char Class[15];
    char address[30];
    int rollNo;
    float percentage;
}Student;

int main(){

    int choice;

    printf("\n----------Student Database----------\n");
    printf("\n1.Add Student Record(s)");
    printf("\n2.Search Student Record");
    printf("\n3.Display Student Records");
    printf("\n4.Delete Student Record(s)");
    printf("\n5.Exit from the program");
    printf("\n------------------------------------\n");

    printf("Enter your choice: ");
    scanf("%d",&choice);
    
    while(choice != 5){
        switch(choice){
            case 1:
                addRecord();
                break;
            case 2:
                searchRecord();
                break;
            case 3:
                displayRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                printf("\n\nExiting from the program...");
                return 0;

            default:
                printf("Enter a valid choice!\n");
        }
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
    }

    return 0;
}
// Function to add student record

void addRecord(){
    FILE *fp;
    fp = fopen("Student_dbms.txt","ab");

    Student info;
    char another[5]; 

    if(fp == NULL){
        printf("\nCannot access file\n");
        return;
    }

    do{
        printf("\nEnter roll no: ");
        scanf("%d",&info.rollNo);
        printf("Enter first name: ");
        scanf("%s",info.name);
        printf("Enter class: ");
        scanf("%s",info.Class);
        printf("Enter address: ");
        scanf("%s",info.address);
        printf("Enter percentage: ");
        scanf("%f",&info.percentage);

        fwrite(&info,sizeof(Student),1,fp);

        printf("\nDo you want to add another record (yes/no): ");
        scanf("%s", another);   
    } while(another[0] == 'y' || another[0] == 'Y');

    fclose(fp);
}

// Function to search for a student using their roll no in the database for now
// Later I will add other elements like their class and roll no also, if there are same names in same class

void searchRecord(){
    FILE *fp;
    fp = fopen("Student_dbms.txt","rb");

    Student info;
    int searchRollno;
    int flag = 0;

    if(fp == NULL){
        printf("\nCannot access file\n");
    }else{
        printf("\nSuccessfully accessed the file\n");
    }

    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0){
        printf("No records found.\n");
        fclose(fp);
        return;
    }
    rewind(fp); // move pointer back to start

    printf("Enter roll no to search: ");
    scanf("%d",&searchRollno);

    while(fread(&info,sizeof(info),1,fp) == 1){
        if(searchRollno == info.rollNo){
            printf("Entered student's roll no is in the record.\nStudent details:\n");
            printf("\nStudent: %s",info.name);
            printf("\nRoll no: %d",info.rollNo);
            printf("\nClass: %s",info.Class);
            printf("\nAddress: %s",info.address);
            printf("\nPercentage: %.2f",info.percentage);
            flag = 1;
            break;
        }

        if(!flag){
            printf("Entered roll no is not found in the database.\n");
        }
    }
    fclose(fp);
}
// Function to display all the student records for now 
// And later will update it to select the ones we want

void displayRecord(){
    FILE *fp;
    fp = fopen("Student_dbms.txt","rb");

    Student info;

    if(fp == NULL){
        printf("\nCannot access file\n");
    }else{
        printf("\nSuccessfully accessed the file\n");
    }

    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0){
        printf("No records found.\n");
        fclose(fp);
        return;
    }
    rewind(fp); // move pointer back to start


    while(fread(&info, sizeof(info),1,fp) == 1){
        printf("\nStudent: %s",info.name);
        printf("\nRoll no: %d",info.rollNo);
        printf("\nClass: %s",info.Class);
        printf("\nAddress: %s",info.address);
        printf("\nPercentage: %.2f",info.percentage);
    }

    fclose(fp);
}
// Function to delete particular student record

void deleteRecord(){
    FILE *fp, *fp1;
    fp = fopen("Student_dbms.txt","rb");
    fp1 = fopen("temp.txt","wb");

    Student info;
    int deleteRollno;
    int flag = 0;

    if(fp == NULL){
        printf("\nCannot access file\n");
    }else{
        printf("\nSuccessfully accessed the file\n");
    }

    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0){
        printf("No records found.\n");
        fclose(fp);
        return;
    }
    rewind(fp); // move pointer back to start

    printf("Enter roll no to delete: ");
    scanf("%d",&deleteRollno);

    while(fread(&info,sizeof(Student),1,fp) == 1){
        if(info.rollNo == deleteRollno){
            printf("Entered student's roll no is in the record.\nStudent details is detailed.\n");
            flag = 1; // skip this record
        } else {
            fwrite(&info,sizeof(Student),1,fp1);
        }
    }

    if(!flag){
        printf("The student's record is not in the database.\n");
    }

    fclose(fp);
    fclose(fp1);

    remove("Student_dbms.txt");
    rename("temp.txt","Student_dbms.txt");

}

