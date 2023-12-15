#ifndef CLINIC_H
#define CLINIC_H


#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "STD_TYPES.h"


#define MAX_SIZE_OF_DATES 5


typedef struct{
    uint8_t  name[50];
    uint8_t  gender[7];
    uint16_t id;
    uint8_t  age;
    uint8_t  date;
}patient_info;

typedef struct node
{
    patient_info* patient_data;
    struct node*  next_patient;
}patient_node;

typedef enum{
    R_NOK,
    R_OK
}Return_Status;

/************ADMIN MODE***********/
/*void welcome_func();
void choose_mode();*/
Return_Status Add_Patient_Data  (patient_node** patient);
Return_Status Edit_Patient_Data (patient_node** patient);
Return_Status Book_reservation  (patient_node** patient);
Return_Status Cancel_reservation(patient_node** patient);


/************USER MODE***********/
Return_Status Display_Patient_info(patient_node** patient);




#endif // CLINIC_H
