#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

/****************************************************
    Menu:
     1. x Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. x Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. hacer validaciones: Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. x Listar empleados
     7. Ordenar empleados
     8. x Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. x Salir
*****************************************************/


int main()
{
    int option = 0;
    int elementosCargados = 0;
    int proceso;
    LinkedList* listaEmpleados = ll_newLinkedList();
    do
    {
        proceso = 0;
        printf("Lista de Empleados:\n");
        printf("1.  Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n");
        printf("2.  Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n");
        printf("3.  Alta de empleado\n");
        printf("4.  Modificar datos de empleado\n");
        printf("5.  Baja de empleado\n");
        printf("6.  Listar empleados\n");
        printf("7.  Ordenar empleados\n");
        printf("8.  Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");
        printf("9.  Guardar los datos de los empleados en el archivo data.csv (modo binario).\n");
        printf("10. Salir\n");
        printf("Eliga Su Opcion: ");
        fflush(stdin);
        if(!scanf("%d", &option))
        {
            option = -1;
        }
        switch(option)
        {

        case 1:
            if(elementosCargados < 1)
            {
                elementosCargados = controller_loadFromText("data.csv",listaEmpleados);
                if(elementosCargados != -1)
                {
                    printf("Se cargaron %d Empleados\n", elementosCargados);
                }
                else
                {
                    printf("Error Al cargar la lista\n");
                }
            }
            else
            {
                printf("Esta lista ya fue cargada...\n");
            }
            break;
        case 2:
            if(elementosCargados < 1)
            {
                elementosCargados = controller_loadFromBinary("data.dat",listaEmpleados);
                printf("Se cargaron %d Empleados\n", elementosCargados);
            }
            else
            {
                printf("Esta lista ya fue cargada...\n");
            }
            break;
        case 3:
            controller_addEmployee(listaEmpleados);
            break;
        case 4:
            proceso = controller_editEmployee(listaEmpleados);
            break;
        case 5:
            proceso = controller_removeEmployee(listaEmpleados);
            break;
        case 6:
            proceso = controller_ListEmployee(listaEmpleados);
            break;
             case 7:
            proceso = controller_sortEmployee(listaEmpleados);
            break;
        case 8:
            controller_saveAsText("data.csv",listaEmpleados);
            break;
        case 9:
            controller_saveAsBinary("data.dat",listaEmpleados);
            break;
        case 10:
            printf("Adios!\n");
            break;
        default:
            printf("No ingreso una Opcion Valida\n");
            break;
        }
        if(proceso != 0)
        {
            printf("Esta Opcion requiere empleados en la lista para usarse\n");
        }
        printf("Presione cualuqier tecla para continuar...");
            fflush(stdin);
            getche();
        system("cls");
    }
    while(option != 10);

    controller_deleteListEmployee(listaEmpleados);
    return 0;
}
