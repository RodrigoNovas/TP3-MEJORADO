#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Employee.h"

Employee* employee_new()
{
    Employee* newEmploye;

    newEmploye = (Employee*)malloc(sizeof(Employee));
    if(newEmploye != NULL)
    {
        newEmploye->horasTrabajadas = 0;
        newEmploye->sueldo = 0;
        newEmploye->id = 0;
        strcpy(newEmploye->nombre, " ");
    }
    return newEmploye;
}

void employee_delete(Employee* this)
{
    if(this != NULL)
    {
        free(this);
    }
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
    Employee* newEmploye;
    int aux;
    int errorFlag;
    newEmploye = employee_new();
    if(newEmploye != NULL && idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL
            && sueldoStr != NULL)
    {
        if(employee_setNombre(newEmploye, nombreStr))
        {
            errorFlag = 1;
        }

        aux = atoi(sueldoStr);
        if(employee_setSueldo(newEmploye, aux))
        {
            errorFlag = 1;
        }

        aux = atoi(horasTrabajadasStr);
        if(employee_setHorasTrabajadas(newEmploye, aux))
        {
            errorFlag = 1;
        }
        aux = atoi(idStr);
        if(employee_setId(newEmploye, aux))
        {
            errorFlag = 1;
        }

        if(errorFlag == 1)
        {
            free(newEmploye);
            newEmploye = NULL;
        }
    }
    return newEmploye;
}



int employee_setId(Employee* this,int id)
{
    int estado = -1;
    if(this != NULL)
    {
        if(id > 0)
        {
            this->id = id;
            estado = 0;
        }
    }
    return estado;
}
int employee_getId(Employee* this,int* id)
{
    int estado = -1;
    if(this != NULL && id != NULL)
    {
        *id = this->id;
        estado = 0;

    }
    return estado;
}
int employee_setSueldo(Employee* this,int sueldo)
{
    int estado = -1;
    if(this != NULL)
    {
        if(sueldo > 0)
        {
            this->sueldo = sueldo;
            estado = 0;
        }
    }
    return estado;
}
int employee_getSueldo(Employee* this,int* sueldo)
{
    int estado = -1;
    if(this != NULL && sueldo != NULL)
    {
        *sueldo = this->sueldo;
        estado = 0;

    }
    return estado;
}
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int estado = -1;
    if(this != NULL)
    {
        if(horasTrabajadas >= 0)
        {
            this->horasTrabajadas = horasTrabajadas;
            estado = 0;
        }
    }
    return estado;
}
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int estado = -1;
    if(this != NULL && horasTrabajadas != NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        estado = 0;
    }
    return estado;
}
int employee_setNombre(Employee* this,char* nombre)
{
    int estado = -1;
    char auxiliar;
    int len;
    int i;
    if(this != NULL && nombre != NULL)
    {
        len = strlen(nombre);
        if(len > 0 && len < TAMANIO_NOMBRE)
        {
            if(isalpha(*nombre)) // Validacion: el primer caracter debe ser del alfabeto
            {
                for(i=0; i<len; i++)
                {
                    auxiliar = *(nombre+i);
                    if(i == len -1) // se asume si se pudo llegar al final la cadena es correcta.
                    {
                        estado = 0;
                        break;
                    }
                    if(!isalpha(auxiliar) && !isspace(auxiliar) && auxiliar != '-')
                    {
                        break;
                    }
                }
                if(estado == 0)
                {
                    strcpy(this->nombre,nombre);
                }
            }

        }
    }
    return estado;
}
char* employee_getNombre(Employee* this)
{
    char* nombre = NULL;

    if(this != NULL)
    {
        nombre = (char*)malloc(sizeof(char)*TAMANIO_NOMBRE);
        strcpy(nombre,this->nombre);
    }
    return nombre;
}

int employee_print(Employee* this)
{
    int estado = -1;

    int id;
    int sueldo;
    int horas;

    if(this != NULL)
    {
        employee_getId(this,&id);
        employee_getHorasTrabajadas(this,&horas);
        employee_getSueldo(this,&sueldo);
        printf("%5d %20s %10d %15d\n", id, employee_getNombre(this), sueldo, horas);
    }
    return estado;
}

int employee_ordenHoras(void* cajaA,void* cajaB)
{
    int estado = 0;
    Employee* empleadoA;
    Employee* empleadoB;
    int horasA;
    int horasB;
    if(cajaA != NULL && cajaB != NULL)
    {
        empleadoA = (Employee*) cajaA;
        empleadoB = (Employee*) cajaB;
        if(empleadoA != NULL && empleadoB != NULL)
        {
            employee_getHorasTrabajadas(empleadoA,&horasA);
            employee_getHorasTrabajadas(empleadoB,&horasB);

            if(horasA > horasB)
            {
                estado = 1;
            }
            else if(horasA < horasB)
            {
                estado = -1;
            }

        }
    }

    return estado;
}

int employee_ordenSueldo(void* cajaA,void* cajaB)
{
    int estado = 0;
    Employee* empleadoA;
    Employee* empleadoB;
    int sueldoA;
    int sueldoB;
    if(cajaA != NULL && cajaB != NULL)
    {
        empleadoA = (Employee*) cajaA;
        empleadoB = (Employee*) cajaB;
        if(empleadoA != NULL && empleadoB != NULL)
        {
            employee_getSueldo(empleadoA,&sueldoA);
            employee_getSueldo(empleadoB,&sueldoB);

            if(sueldoA > sueldoB)
            {
                estado = 1;
            }
            else if(sueldoA < sueldoB)
            {
                estado = -1;
            }

        }
    }

    return estado;
}

int employee_ordenNombre(void* cajaA,void* cajaB)
{
    int estado = -2;
    Employee* empleadoA;
    Employee* empleadoB;
    char* nombreA;
    char* nombreB;
    if(cajaA != NULL && cajaB != NULL)
    {
        empleadoA = (Employee*) cajaA;
        empleadoB = (Employee*) cajaB;
        if(empleadoA != NULL && empleadoB != NULL)
        {
            nombreA = employee_getNombre(cajaA);
            nombreB = employee_getNombre(cajaB);

            estado = strcasecmp(nombreA,nombreB);
        }
    }

    return estado;
}
