#include"Clinic.h"


uint8_t dates[]={1,2,3,4,5};

/************ADMIN MODE***********/
Return_Status Add_Patient_Data(patient_node** patient)
{
    Return_Status ret = R_NOK;
    if(patient!=NULL)
    {
        ret=R_OK;
        uint8_t name[50];
        uint8_t gender[7];
        patient_node* newPatient=(patient_node*)malloc(sizeof(patient_node));
        printf("Enter Patient Name :");
        scanf(" %[^\n]s",newPatient->patient_data->name);
        printf("Enter Patient Age :");
        scanf("%d",&newPatient->patient_data->age);
        printf("Enter Patient Gender (male/female):");
        scanf(" %[^\n]s",newPatient->patient_data->gender);
        printf("Enter Patient ID :");
        scanf("%d",&(newPatient->patient_data->id));
        newPatient->next_patient=NULL;
        if(*patient==NULL)
        {
            *patient=newPatient;
        }
        else
        {
            patient_node* tempPatient=(patient_node*)malloc(sizeof(patient_node));
            tempPatient=*patient;
            while(tempPatient->next_patient!=NULL)
            {
                if(newPatient->patient_data->id==tempPatient->patient_data->id)
                {
                    printf("This ID is already exist please choose another ID:");
                    scanf("%d",&newPatient->patient_data->id);
                }
                tempPatient=tempPatient->next_patient;
            }
            tempPatient->next_patient=newPatient;
            free(tempPatient);
        }
        printf("\t\t\t\tData Has Been Added Successfully...\n");
    }
    else {/*Nothing*/}
    return ret;
}


Return_Status Edit_Patient_Data(patient_node** patient)
{
    Return_Status ret = R_NOK;
    if(patient!=NULL)
    {
        ret=R_OK;
        if(*patient==NULL)
        {
        printf("There are no patients In The Database \n");
        }
        else
        {
        patient_node* wantedPatient=(patient_node*)malloc(sizeof(patient_node));
        patient_node* tempPatient=*patient;
        printf("Please Enter The ID of the Patient That You Want to Change His/Her Information:");
        scanf("%d",&wantedPatient->patient_data->id);
        uint8_t flag=0;
        while(tempPatient!=NULL)
        {
            if(wantedPatient->patient_data->id==tempPatient->patient_data->id)
            {
                flag=1;
                uint8_t choice;
                printf("Choose Which Data You Want To Edit:");
                printf("-> 1) Name\n");
                printf("-> 2) Age\n");
                printf("-> 3) Gender\n");
                scanf("%d",&choice);
                switch(choice)
                {
                case 1:
                    scanf(" %[^\n]s",wantedPatient->patient_data->name);
                    break;
                case 2:
                    scanf("%d",&(wantedPatient->patient_data->age));
                    break;
                case 3:
                    scanf(" %[^\n]s",wantedPatient->patient_data->gender);
                    break;
                default:
                    printf("Invalid Choice,Please Try Again");
                    Edit_Patient_Data(patient);
                }
                break;
            }
            else
            {
                tempPatient=tempPatient->next_patient;
            }
        }
        if(0==flag)
        {
            printf("\t\t\t\t ********* Invalid ID ************ \n");
            printf("If you still want to edit a patient info choose Edit patient Informations from the list again \n");
        }

        }
    }
    else {/*Nothing*/}
    return ret;
}

Return_Status Book_reservation(patient_node** patient)
{
    Return_Status ret = R_NOK;
    if(patient!=NULL)
    {
        ret=R_OK;
        if(*patient==NULL)
        {
            printf("There are no patients In The Database \n");
        }
        else
        {
            uint8_t flag=0;
            patient_node* Patient_t=(patient_node*)malloc(sizeof(patient_node));
            patient_node* tempPatient=*patient;
            printf("Please Enter the Patient ID :");
            scanf("%d",&Patient_t->patient_data->id);
            while(tempPatient!=NULL)
            {
                if(Patient_t->patient_data->id==tempPatient->patient_data->id)
                {
                    flag=1;
                    break;
                }
            }
            if(1==flag)
            {
                printf("\t\t\t->1) From 12:00 PM To 12:30 PM \n");
                printf("\t\t\t->2) From 12:30 PM To 1:00  PM \n");
                printf("\t\t\t->3) From 1:00  PM To 1:30  PM \n");
                printf("\t\t\t->4) From 1:30  PM To 2:00  PM \n");
                printf("\t\t\t->5) From 2:30  PM To 3:00  PM \n");
                printf("\n\nPlease Choose the Suitable Date:");
                scanf("%d",&Patient_t->patient_data->date);
                if(dates[Patient_t->patient_data->date-1]==0)
                {
                    printf("This Date is Already Reserved\n");
                }
                else
                {
                    dates[Patient_t->patient_data->date-1]=0;
                }
            }
            else
            {
                printf("Incorrect ID Please Re Enter The Right ID : \n");
            }
        }
    }
    else {/*Nothing*/}
    return ret;
}



Return_Status Cancel_reservation(patient_node** patient)
{
    Return_Status ret = R_NOK;
    if(patient!=NULL)
    {
        ret=R_OK;
        uint16_t id;
        printf("Enter Patient ID To Cancel Reservation:");
        scanf("%d",&id);
        patient_node* temp=(patient_node*)malloc(sizeof(patient_node));
        while(temp!=NULL)
        {
            if(id==temp->patient_data->id)
            {
             dates[temp->patient_data->date-1]=temp->patient_data->date;
            }
            else
            {
                temp=temp->next_patient;
            }
        }
    }
    else {/*Nothing*/}
    return ret;
}



/************USER MODE***********/
Return_Status Display_Patient_info(patient_node** patient)
{
    Return_Status ret=R_NOK;
    if(patient!=NULL)
    {
        ret=R_OK;
        if(*patient==NULL)
        {
            printf("There are no patients..\n");
        }
        else
        {
            uint16_t id;
            printf("Enter ID of The Patient you Want To Display His Data:");
            scanf("%d",&id);
            patient_node* temp=*patient;
            while(temp!=NULL)
            {
                if(id==temp->patient_data->id)
                {
                    printf("Name   : %s\n",temp->patient_data->name);
                    printf("Gender : %s\n",temp->patient_data->gender);
                    printf("Age    : %d\n",temp->patient_data->age);
                    printf("ID     : %d\n",temp->patient_data->id);
                    break;
                }
                else
                {
                    temp=temp->next_patient;
                }
            }
        }
    }
    else {/*Nothing*/}
    return ret;
}
