#include <stdio.h>
#include <stdlib.h>
#include "Clinic.h"
patient_node *pat,*pat2,*pat3,*pat4,*pat5;
int main()
{
    for(int i=0;i<3;i++)
    {
        uint8_t name[55];
        printf("Enter Your Name:");
        scanf(" %[^\n]s",name);
    }
    //Add_Patient_Data(&pat);
    //Add_Patient_Data(&pat2);
    //Add_Patient_Data(&pat3);
    //Add_Patient_Data(&pat4);
    //Add_Patient_Data(&pat5);
    return 0;
}
