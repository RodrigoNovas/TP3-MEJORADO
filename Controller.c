#include "Controller.h"

int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    char idAux[100];
    char nameAux[TAMANIO_NOMBRE];
    char workHoursAux[100];
    int i = -1;
    char salaryAux[100];
    Employee* empleadoAux;
    if(pArrayListEmployee != NULL && path != NULL)
    {

        pArchivo = fopen(path,"r");

        if(pArchivo != NULL)
        {
            while(!feof(pArchivo))
            {

                fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^\n]\n", idAux, nameAux, salaryAux,workHoursAux);
                if(i != -1)
                {
                    empleadoAux = employee_newParametros(idAux,nameAux,workHoursAux,salaryAux);
                    if(empleadoAux != NULL)
                    {
                        ll_add(pArrayListEmployee, empleadoAux);

                    }
                    else
                    {
                        printf("\n ERROR: SE ENCONTRO UN ELEMNTO INCOMPATIBLE\n");
                        controller_deleteListEmployee(pArrayListEmployee);
                        i = 0;
                        break;
                    }
                }
                i++;
            }
            fclose(pArchivo);
        }
        else
        {
            printf("No existe el archivo\n");
        }
    }

    return i;
}


int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    Employee* empleadoAux;
    int i = 0;

    if(pArrayListEmployee != NULL && path != NULL)
    {
    pArchivo = fopen(path,"rb");
    if(pArchivo != NULL)
    {
        while(!feof(pArchivo))
        {

            empleadoAux = (Employee*) malloc(sizeof(Employee));
            fread(empleadoAux,sizeof(Employee), 1, pArchivo);
            if(feof(pArchivo))
            {
                break;
            }
            if(empleadoAux != NULL)
            {
                ll_add(pArrayListEmployee, empleadoAux);
                i++;
            }
            else
            {
                printf("\n ERROR AL AÑADIR UN ELEMNTO EMPLOYEE\n");
            }


        }
        fclose(pArchivo);
    }



    }

    return i;
}

int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int estado = -1;
    Employee* newEmployee;
    int idAux;
    // pasar mas tarde a otra funcion
    if(pArrayListEmployee != NULL)
    {
        newEmployee = employee_new();

        controller_inputEmployeeName(newEmployee);

        controller_inputEmployeeSalary(newEmployee);

        controller_inputEmployeeWorkHours(newEmployee);

        idAux = controller_getNextID(pArrayListEmployee);
        employee_setId(newEmployee,idAux);


        if(ll_add(pArrayListEmployee,newEmployee))
        {
            printf("El empleado no se pudo agregar a la lista");
        }
        else
        {
            estado = 0;
        }
    }

    return estado;
}


int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int estado = -1;
    Employee* targetEmployee;
    LinkedList* subLista;
    int subListaInicio = 0;
    int len;
    char option;
    int pagina = 0;
    if(pArrayListEmployee != NULL)
    {
        system("cls");
        len = ll_len(pArrayListEmployee);
        if(len > 0)
        {
            do
            {
                subLista = controller_createSubList(pArrayListEmployee,len,subListaInicio,pagina);
                printf("E) Ingresar el Id de el empleado a modificar: \n");
                controller_printList(subLista);
                ll_deleteLinkedList(subLista);

                fflush(stdin);
                option = getche();
                option = tolower(option);
                switch(option)
                {
                case 'a':
                    controller_previusListPage(&pagina,&subListaInicio,len);
                    break;
                case 'd':
                    controller_nextListPage(&pagina,&subListaInicio,len);
                    break;
                case 'w':
                    controller_goToListPage(&pagina,&subListaInicio,len);
                    break;
                case 'e':
                    targetEmployee = controller_findEmployeeByID(pArrayListEmployee);
                    controller_editEmployeeMenu(targetEmployee);
                    break;
                default:
                    break;
                }
                system("cls");

            }
            while(option != 's');
            estado = 0;
        }
    }
    return estado;
}


int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int estado = -1;
    Employee* targetEmployee;
    LinkedList* subLista;
    int empleadoEliminadoFlag;
    int subListaInicio = 0;
    int len;
    char option = 's';
    int pagina = 0;
    if(pArrayListEmployee != NULL)
    {
        system("cls");
        len = ll_len(pArrayListEmployee);
        if(len > 0)
        {
            do
            {
                subLista = controller_createSubList(pArrayListEmployee,len,subListaInicio,pagina);
                printf("E) Ingresar el Id de el empleado a eliminar: \n");
                controller_printList(subLista);
                ll_deleteLinkedList(subLista);

                fflush(stdin);
                option = getche();
                option = tolower(option);
                switch(option)
                {
                case 'a':
                    controller_previusListPage(&pagina,&subListaInicio,len);
                    break;
                case 'd':
                    controller_nextListPage(&pagina,&subListaInicio,len);
                    break;
                case 'w':
                    controller_goToListPage(&pagina,&subListaInicio,len);
                    break;
                case 'e':
                    targetEmployee = controller_findEmployeeByID(pArrayListEmployee);
                    empleadoEliminadoFlag = controller_deleteEmployee(pArrayListEmployee,targetEmployee);
                    if(empleadoEliminadoFlag == 0)
                    {
                        len = ll_len(pArrayListEmployee);
                        if(pagina*PAGE_SIZE >= len)
                        {
                            pagina--;
                            subListaInicio -= PAGE_SIZE;
                        }
                    }
                    break;
                default:
                    break;
                }
                system("cls");

            }
            while(option != 's');
            estado = 0;
        }
    }
    return estado;
}


int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int estado = -1;
    LinkedList* subLista;
    int subListaInicio = 0;
    int len;
    char option = 's';
    int pagina = 0;
    if(pArrayListEmployee != NULL)
    {
        len = ll_len(pArrayListEmployee);
        if(len > 0)
        {
            do
            {
                system("cls");
                subLista = controller_createSubList(pArrayListEmployee,len,subListaInicio,pagina);
                controller_printList(subLista);
                ll_deleteLinkedList(subLista);

                fflush(stdin);
                option = getche();
                option = tolower(option);
                switch(option)
                {
                case 'a':
                    controller_previusListPage(&pagina,&subListaInicio,len);
                    break;
                case 'd':
                    controller_nextListPage(&pagina,&subListaInicio,len);
                    break;
                case 'w':
                    controller_goToListPage(&pagina,&subListaInicio,len);
                    break;
                default:
                    break;
                }
                system("cls");

            }
            while(option != 's');
            estado = 0;
        }
    }
    return estado;
}

int controller_printList(LinkedList* pArrayListEmployee)
{
    int i;
    int elements;
    Employee* pEmpleadoAux;
    if(pArrayListEmployee != NULL)
    {
        elements = ll_len(pArrayListEmployee);
        if(elements > 0)
        {
            printf("%5s %20s %10s %12s","ID", "NOMBRE", "SUELDO", "HORAS TRABAJADAS\n");
            for(i=0; i < elements; i++)
            {
                pEmpleadoAux = ll_get(pArrayListEmployee, i);
                employee_print(pEmpleadoAux);
            }/**/
        }


    }
    return i;
}

int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int estado = -1;
    LinkedList* displayList;
    LinkedList* subLista;
    int subListaInicio = 0;
    int len;
    char option;
    int pagina = 0;
    if(pArrayListEmployee != NULL)
    {
        displayList = ll_clone(pArrayListEmployee);
        system("cls");
        len = ll_len(displayList);
        if(len > 0)
        {
            do
            {
                subLista = controller_createSubList(displayList,len,subListaInicio,pagina);
                printf("E) Cambiar Criteria de ordenamiento: \n");
                controller_printList(subLista);
                ll_deleteLinkedList(subLista);

                fflush(stdin);
                option = getche();
                option = tolower(option);
                switch(option)
                {
                case 'a':
                    controller_previusListPage(&pagina,&subListaInicio,len);
                    break;
                case 'd':
                    controller_nextListPage(&pagina,&subListaInicio,len);
                    break;
                case 'w':
                    controller_goToListPage(&pagina,&subListaInicio,len);
                    break;
                case 'e':
                    controller_selectSortCriteria(displayList);
                    break;
                default:
                    break;
                }
                system("cls");

            }
            while(option != 's');
            estado = 0;
        }
    }
    return estado;
}

int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    int estado = -1;
    FILE* pArchivo;
    Employee* empleadoAux;
    int i;
    int listLen;
    int* idAux;
    char* nameAux;
    int* sueldoAux;
    int* horasAux;
    if(pArrayListEmployee != NULL && path != NULL)
    {
        idAux = malloc(sizeof(int));
        nameAux = malloc(sizeof(char)*TAMANIO_NOMBRE);
        sueldoAux = malloc(sizeof(int));
        horasAux = malloc(sizeof(int));

        pArchivo = fopen(path,"w");
        listLen = ll_len(pArrayListEmployee);
        fprintf(pArchivo,"id,nombre,horasTrabajadas,sueldo\n");

        for(i=0; i<listLen; i++)
        {
            empleadoAux = ll_get(pArrayListEmployee,i);
            employee_getId(empleadoAux,idAux);
            employee_getSueldo(empleadoAux,sueldoAux);
            nameAux = employee_getNombre(empleadoAux);
            employee_getHorasTrabajadas(empleadoAux,horasAux);
            fprintf(pArchivo,"%d,%s,%d,%d\n",*idAux,nameAux,*sueldoAux,*horasAux);
        }
        free(nameAux);
        free(idAux);
        free(sueldoAux);
        free(horasAux);
        fclose(pArchivo);
    }
    return estado;
}

int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    int estado = -1;
    FILE* pArchivo;
    Employee* employeeAux;
    int i = 0;
    int listLen;
    if(pArrayListEmployee != NULL && path != NULL)
    {

        pArchivo = fopen(path,"wb");
        listLen = ll_len(pArrayListEmployee);
        for(i=0; i< listLen; i++)
        {
            employeeAux = (Employee*)ll_get(pArrayListEmployee,i);
            fwrite(employeeAux, sizeof(Employee),1,pArchivo);
        }
        fclose(pArchivo);
    }
    return estado;
}


int controller_inputEmployeeName(Employee* empleado)
{
    int estado = -1;
    char nombre[TAMANIO_NOMBRE];
    int errorFlag = 0;
    int length;
    if(empleado != NULL)
    {
        system("cls");
        printf("Ingrese el Nombre del Empleado: ");
        do
        {

            if(errorFlag != 0)
            {

                printf("ERROR: Reingrese el Nombre del Empleado: ");
            }
            fflush(stdin);
            fgets(nombre,TAMANIO_NOMBRE,stdin);
            length = strlen(nombre);
            if(nombre[length - 1] == '\n')
            {
                nombre[length - 1] = '\0';
            }
            errorFlag = employee_setNombre(empleado, nombre);
            system("cls");
        }
        while(errorFlag != 0);
        estado = 0;
    }
    return estado;
}


int controller_inputEmployeeSalary(Employee* empleado)
{
    int estado = -1;
    int sueldo;
    int errorFlag = 0;
    if(empleado != NULL)
    {
        system("cls");
        printf("Ingrese el Sueldo del Empleado: ");
        do
        {
            if(errorFlag != 0)
            {
                printf("ERROR reingrese el Sueldo del Empleado: ");
            }
            fflush(stdin);
            if(scanf("%d", &sueldo))
            {
                errorFlag = employee_setSueldo(empleado, sueldo);
            }
            else
            {
                errorFlag = -1;
            }
            system("cls");
        }
        while(errorFlag != 0);
    }
    return estado;
}

int controller_inputEmployeeWorkHours(Employee* empleado)
{
    int estado = -1;
    int horas;
    int errorFlag = 0;
    if(empleado != NULL)
    {
        system("cls");
        printf("Ingrese la Horas trabajadas por el Empleado: ");
        do
        {
            if(errorFlag != 0)
            {
                printf("ERROR: reingrese la Horas trabajadas por el Empleado: ");
            }
            fflush(stdin);
            if(scanf("%d", &horas))
            {
                errorFlag = employee_setHorasTrabajadas(empleado, horas);
            }
            else
            {
                errorFlag = -1;
            }
            system("cls");
        }
        while(errorFlag != 0);
    }
    return estado;
}
int controller_getNextID(LinkedList* pArrayListEmployee)
{
    int id = 0;
    int idAnterior;
    int auxiliar;
    Employee* employeeAux;
    int listLen;
    int i;

    if(pArrayListEmployee != NULL)
    {
        listLen = ll_len(pArrayListEmployee);
        if(listLen > 0)
        {
            for(i = 0; i<listLen; i++)
            {
                employeeAux = (Employee*)ll_get(pArrayListEmployee,i);
                employee_getId(employeeAux,&auxiliar);
                if(auxiliar > id)
                {
                    idAnterior = id;
                    id = auxiliar;
                    if(idAnterior + 1 != id)
                    {
                        id = idAnterior;
                        break;
                    }
                }
            }
            id++;

        }
        else
        {
            id = 1;
        }

    }
    return id;
}

int controller_previusListPage(int* page, int* startIndex, int length)
{
    int estado = -1;
    int cantidadPaginas;
    if(page != NULL && startIndex != NULL)
    {
        cantidadPaginas = length/PAGE_SIZE;
        if(length%PAGE_SIZE == 0)
        {
            cantidadPaginas--;
        }
        if(*page != 0)
        {
            *startIndex -= PAGE_SIZE;
            *page -= 1;
        }
        else
        {
            if(length%PAGE_SIZE != 0)
            {
                *startIndex = length - (length%PAGE_SIZE);
                *page = cantidadPaginas;
            }
            else
            {
                *startIndex = length - PAGE_SIZE;
                *page = cantidadPaginas;
            }
        }
        estado = 0;
    }
    return estado;
}

int controller_nextListPage(int* page, int* startIndex, int length)
{
    int estado = -1;
    int cantidadPaginas;
    if(page != NULL && startIndex != NULL)
    {
        cantidadPaginas = length/PAGE_SIZE;
        if(length%PAGE_SIZE == 0)
        {
            cantidadPaginas--;
        }
        if(*page != cantidadPaginas)
        {
            *startIndex += PAGE_SIZE;
            *page += 1;
        }
        else
        {
            *startIndex = 0;
            *page = 0;
        }
        estado = 0;
    }
    return estado;
}

int controller_goToListPage(int* page, int* startIndex, int length)
{
    int estado = -1;
    int auxiliar;
    int cantidadPaginas;
    if(page != NULL && startIndex != NULL)
    {
        cantidadPaginas = length/PAGE_SIZE;
        if(length%PAGE_SIZE == 0)
        {
            cantidadPaginas--;
        }
        printf(") Indique la pagina donde quiere ir: ");
        scanf("%d", &auxiliar);
        if(auxiliar > 0 && auxiliar <= cantidadPaginas+1)
        {
            *page = auxiliar - 1;
            *startIndex = (auxiliar - 1) * PAGE_SIZE;
        }
        estado = 0;
    }
    return estado;
}
int controller_selectSortCriteria(LinkedList* pArrayListEmployee)
{
    int estado = -1;
    int orden = -1;
    int opcion;

    if(pArrayListEmployee != NULL)
    {
        do
        {
            system("cls");
            printf("Eliga el tipo de orden:\n");
            printf("A) Ordenar por nombre.\n");
            printf("D) Ordenar por sueldo.\n");
            printf("W) Ordenar por horas trabjadas.\n");
            printf("S) Cancelar.\n");

            fflush(stdin);
            opcion = getche();
            opcion = tolower(opcion);
            switch(opcion)
            {
            case 'a':
            case 'd':
            case 'w':
                orden = controller_sortTypeOfOrder();
                break;
            case 's':
                break;
            default:
                break;
            }

        }
        while(opcion != 's' && orden == -1);
        if(opcion != 's')
        {
            printf("\n Ordenando Elementos...");
            switch(opcion)
            {
            case 'a':
                ll_sort(pArrayListEmployee,employee_ordenNombre,orden);
                break;
            case 'd':
                ll_sort(pArrayListEmployee,employee_ordenSueldo,orden);
                break;
            case 'w':
                ll_sort(pArrayListEmployee,employee_ordenHoras,orden);
                break;
            }
            estado = 0;
        }
    }


    return estado;
}

int controller_sortTypeOfOrder(void)
{
    int order;
    int opcion;
    do
    {
        system("cls");
        if(opcion == '0')
        {
            printf("(ERROR)");
        }
        printf("Eliga una de las siguientes opciones:\n");
        printf("A) Orden acendente.\n");
        printf("D) Orden decendiente.\n");
        printf("S) Cancelar.\n");

        fflush(stdin);
        opcion = getche();
        opcion = tolower(opcion);

        switch(opcion)
        {
        case 'a':
            order = 1;
            break;
        case 'd':
            order = 0;
            break;
        case 's':
            order = -1;
            break;
        default:
            break;
        }
    }
    while(opcion == '0');
    return order;
}
Employee* controller_findEmployeeByID(LinkedList* pArrayListEmployee)
{
    Employee* employee = NULL;
    Employee* employeeAuxliar;
    int id;
    int idAuxiliar;
    int i;
    int listLength;
    if(pArrayListEmployee != NULL)
    {
        printf(") Ingrese el Id del empleado: ");
        if(scanf("%d", &id))
        {
            listLength = ll_len(pArrayListEmployee);
            for(i=0; i<listLength; i++)
            {
                employeeAuxliar = (Employee*)ll_get(pArrayListEmployee,i);
                employee_getId(employeeAuxliar,&idAuxiliar);
                if(id == idAuxiliar)
                {
                    employee = employeeAuxliar;
                    break;
                }
            }
        }
    }

    return employee;
}


int controller_editEmployeeMenu(Employee* oldEmployee)
{
    int estado = -1;
    Employee* newEmployee;
    char option;
    int salir = -1;

    if(oldEmployee != NULL)
    {

        newEmployee = employee_new();
        *newEmployee = *oldEmployee;
        do
        {
            system("cls");
            printf("Empleado Original:\n ");
            printf("%5s %20s %10s %12s","ID", "NOMBRE", "SUELDO", "HORAS TRABAJADAS\n");
            employee_print(oldEmployee);
            printf("Empleado Editado:\n ");
            printf("%5s %20s %10s %12s","ID", "NOMBRE", "SUELDO", "HORAS TRABAJADAS\n");

            employee_print(newEmployee);

            printf("A) Cambiar Nombre.\n");
            printf("D) Cambiar Sueldo.\n");
            printf("W) Cambiar Horas Trabajadas.\n");
            printf("S) Guardar Y Salir.\n");
            printf("Q) Cancelar Cambios.\n");

            fflush(stdin);
            option = getche();
            option = tolower(option);
            switch(option)
            {
            case 'a':
                controller_inputEmployeeName(newEmployee);
                break;
            case 'd':
                controller_inputEmployeeSalary(newEmployee);
                break;
            case 'w':
                controller_inputEmployeeWorkHours(newEmployee);
                break;
            case 's':
                printf("Cambios Guardados");
                *oldEmployee = *newEmployee;
                salir = 0;
                break;
            case 'q':
                printf("Modificacion Cancelada");
                salir = 0;
                break;
            }
        }
        while(salir != 0);
        estado = 0;
        free(newEmployee);
    }
    return estado;
}

int controller_deleteEmployee(LinkedList* pArrayListEmployee, Employee* target)
{
    int estado = -1;
    char* buffer;
    int lastChar;
    int id;
    int errorFlag;
    if(pArrayListEmployee != NULL && target != NULL)
    {
        system("cls");
        buffer = (char*) malloc(sizeof(char)* 1024);
        do
        {
            errorFlag = 0;
            printf("%5s %20s %10s %12s","ID", "NOMBRE", "SUELDO", "HORAS TRABAJADAS\n");
            employee_print(target);

            printf("\nESTAS SEGURO QUE QUIERES ELIMINAR AL EMPLEADO.\n");
            printf("toda su informacion se borrara del sistema(SI/NO): ");
            fflush(stdin);
            fgets(buffer,1024, stdin);
            lastChar = strcspn(buffer, "\n");
            *(buffer + lastChar) = 0;
            if(!stricmp(buffer, "SI"))
            {
                id = ll_indexOf(pArrayListEmployee,target);
                target = ll_pop(pArrayListEmployee,id);

                if(target != NULL)
                {
                    employee_delete(target);
                    printf("Empleado Eliminado...");
                    estado = 0;
                }
                else
                {
                    printf("Hubo un Error al borrar el empleado...");
                }
            }
            else if(!stricmp(buffer, "NO"))
            {
                printf("Eliminacion Cancelada...");
            }
            else
            {
                errorFlag = -1;
            }
            getche();
            system("cls");
        }
        while(errorFlag != 0);
        free(buffer);
    }
    return estado;
}
LinkedList* controller_createSubList(LinkedList* pArrayListEmployee, int len, int from, int actualPage)
{
    LinkedList* subLista = NULL;
    int to;
    int totalPages;
    if(pArrayListEmployee != NULL)
    {
        totalPages = len / PAGE_SIZE;
        if(len%PAGE_SIZE == 0)
        {
            totalPages--;
        }

        if(len < from + PAGE_SIZE)
        {
            to = len;
        }
        else
        {
            to = from + PAGE_SIZE;
        }
        subLista = ll_subList(pArrayListEmployee,from,to);
        printf("Lista de empleados: Pagina %d de %d\n",actualPage + 1, totalPages + 1);
        printf("A)Pagina Anterior: D) Pagina Siguiente: W)Ir a pagina: S) Salir\n");

    }

    return subLista;
}


int controller_deleteListEmployee(LinkedList* pArrayListEmployee)
{
    int estado = -1;
    int len;
    int i;
    Employee* pEmployee;
    if(pArrayListEmployee != NULL)
    {
        len = ll_len(pArrayListEmployee);
        if(len > 0)
        {
            for(i=0; i<len; i++)
            {
                pEmployee = ll_get(pArrayListEmployee, i);
                employee_delete(pEmployee);
            }
            ll_deleteLinkedList(pArrayListEmployee);
            estado = 0;
        }
    }
    return estado;

}
