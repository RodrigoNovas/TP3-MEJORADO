#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANIO_NOMBRE 128

typedef struct
{
    int id;
    char nombre[TAMANIO_NOMBRE];
    int horasTrabajadas;
    int sueldo;
}Employee;

/** \brief Crea un nuevo objecto Employee
 *
 * \param void
 * \return  (NULL) si no hay memoria para crear el elemento.
 *          Employee* si TODO OK;
 *
 */
Employee* employee_new(void);


/** \brief Crea un nuevo empleado cargando los campos con informacion
 *
 * \param char* idStr string que contiene el ID
 * \param char* nombreStr el Nombre
 * \param char* sueldoStr string que contiene el Sueldo
 * \param char* horasStr string que contiene las Horas Trabajadas
 * \return (NULL): si los parametros son nulos, los parametros son incorrectos o no hay espacio disponible
 *         Employee*: TODO OK
 *
 *
 *
 */
 // nota Se usaron char* por respetar la funcion recibida.
Employee* employee_newParametros(char*,char*,char*, char*);
/** \brief Elimina un empleado de memoria
 *
 * \param this Employee* el empleado a eliminar
 * \return void
 *
 */
void employee_delete(Employee* this);

/** \brief establece el id de un empleado
 *
 * \param this Employee* empleado a modificar
 * \param id int nuevo Id
 * \return int  (-1) ERROR: employee* es NULL o Id incorrecto.
 *               (0) TODO BIEN
 *
 */
int employee_setId(Employee* this,int id);
/** \brief se obtiene valor de id de un empleado
 *
 * \param this Employee* Empleado objectivo
 * \param id int* dirrecion donde se copia el valor del Id
 * \return int (-1) ERROR: si los parametros son NULL
 *              (0) TODO BIEN.
 *
 */
int employee_getId(Employee* this,int* id);

/** \brief establece el nombre del empleado
 *
 * \param this Employee* empleado a modificar
 * \param nombre char* nuevo nombre
 * \return int (-1) ERROR: employee* es NULL o nombre incorrecto.
 *               (0) TODO BIEN
 */
int employee_setNombre(Employee* this,char* nombre);
/** \brief se obtiene el nombre del empleado
 *
 * \param this Employee* Empleado Objectivo
 * \return char* (NULL) ERROR: parametro es NULL
 *               char* TODO BIEN
 *
 */
char* employee_getNombre(Employee* this);

/** \brief establece la carga horaria de un empleado
 *
 * \param this Employee* empleado a modificar
 * \param id int la nueva carga horaria
 * \return int  (-1) ERROR: employee* es NULL o horas trabajadas incorrecta.
 *               (0) TODO BIEN
 *
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
/** \brief se obtiene valor de la carga horaria de un empleado
 *
 * \param this Employee* Empleado objectivo
 * \param id int* dirrecion donde se copia el valor de las horas trabajadas
 * \return int (-1) ERROR: si los parametros son NULL
 *              (0) TODO BIEN.
 *
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

/** \brief establece el sueldo de un empleado
 *
 * \param this Employee* empleado a modificar
 * \param id int nuevo sueldo
 * \return int  (-1) ERROR: employee* es NULL o sueldo incorrecto.
 *               (0) TODO BIEN
 *
 */
int employee_setSueldo(Employee* this,int sueldo);
/** \brief se obtiene valor del sueldo de un empleado
 *
 * \param this Employee* Empleado objectivo
 * \param id int* dirrecion donde se copia el valor del sueldo
 * \return int (-1) ERROR: si los parametros son NULL
 *              (0) TODO BIEN.
 *
 */
int employee_getSueldo(Employee* this,int* sueldo);

/** \brief Muestra la informacion de un empleado
 *
 * \param this Employee* empleado a mostrar
 * \return int (-1) ERROR: parametro Employee* NULL
 *              (0) TODO BIEN
 *
 */
int employee_print(Employee* this);


/** \brief define entre 2 employe quien tiene el mayor sueldo.
 *
 * \param cajaA void* Se espra que el dato sea un employee*
 * \param cajaB void* Se espra que el dato sea un employee*
 * \return int:
 *             (0) si: los elementos son iguales o ERROR: Parametros NULL o los elementos no son employee
 *             (1) si: A tiene un salrio mas grande que B
 *             (-1) si: B tiene un salrio mas grande que A
 */
int employee_ordenSueldo(void* cajaA,void* cajaB);
/** \brief define entre 2 employee quien trabaja mas.
 *
 * \param cajaA void* Se espra que el dato sea un employee*
 * \param cajaB void* Se espra que el dato sea un employee*
 * \return int:
 *             (0) si: los elementos son iguales o ERROR: Parametros NULL o los elementos no son employee
 *             (1) si: A trabaja mas  que B
 *             (-1) si: B trabaja mas  que A
 */
int employee_ordenHoras(void* cajaA,void* cajaB);
/** \brief define entre 2 employee quien tiene el orden alfabetico menor.
 *
 * \param cajaA void* Se espra que el dato sea un employee*
 * \param cajaB void* Se espra que el dato sea un employee*
 * \return int (-2) si: ERROR: Los parametros Son NULL o No son tipo Employee.
 *             (0) si: los elementos son iguales
 *             (1) si: A tiene mayor valor ASCII que B
 *             (-1) si: B tiene mayor valor ASCII que A
 */
int employee_ordenNombre(void* cajaA,void* cajaB);
#endif // employee_H_INCLUDED
