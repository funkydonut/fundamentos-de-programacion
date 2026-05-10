/* ============================================================
 * TEMA 24: Tipos de datos estructurados: tabla
 * Todos los ejemplos en C del temario
 * ============================================================ */


/* ============================================================
 * EJEMPLO 01: Definición de una tabla y acceso a sus elementos.
 * Se define una tabla de valores enteros que puede albergar
 * como máximo 10 elementos, usando un struct con un vector
 * y un contador de elementos.
 * ============================================================ */

#include <stdio.h>

/* constant definition */
#define MAX_ELEMENTS 10

/* type definition */
typedef struct {
    int elements[MAX_ELEMENTS];
    int numElements;
} tExampleTable;

int main() {
    /* Var definition using the type */
    tExampleTable aTable;
}


/* ============================================================
 * EJEMPLO 02: Definición de una tabla para puertas de edificios.
 * Se define una tabla de booleanos para controlar el estado
 * (abierta/cerrada) de hasta 40 puertas de un edificio.
 * ============================================================ */

#include <stdio.h>
#include <stdbool.h>


/* definition of the maximum number of gates */
#define MAX_GATES 40


/* definition of the type table */
typedef struct {
    bool stateGates[MAX_GATES];
    int numGates;
} tGates;


int main() {
    /* definition of variables for two
    buildings */
    tGates building1;
    tGates building2;
}


/* ============================================================
 * EJEMPLO 03: Acceso a los elementos de una tabla.
 * Se muestra cómo acceder y asignar valores a los elementos
 * de una tabla (que es una tupla con un vector), utilizando
 * la notación de punto y corchetes. Incluye paso por referencia.
 * ============================================================ */

#include <stdio.h>
#include <stdbool.h>

#define K 10
#define MAX_GATES 40

typedef struct {
    bool stateGates[MAX_GATES];
    int numGates;
} tGates;

void fillTable (tGates *Building);

int main() {
    tGates building1;
    int p;
    bool b;
    bool c;

    c = true;

   /* the following statements treat the elements of the table as variables */
    fillTable(&building1);

   /* assigns the third element of the table building1 to the variable b */
    b  = building1.stateGates[2];

   /* assigns the value of the variable c to the kth gate of building1,  assuming that k is a constant  such  that  1 ≤ K ≤ 40 */
    building1.stateGates[K-1] = c;

   /* assigns the value of the first gate of building1 to the gate  2*p +5 as long as 1 ≤ 2*p+5 ≤ 40 */
    building1.stateGates[2*p+5-1] = building1.stateGates[0];

   return 0;
}


/* ============================================================
 * EJEMPLO 04: Inicialización de una tabla.
 * Se muestra cómo inicializar una tabla poniendo el número
 * de elementos a 0. Se usa el ejemplo de cines multisala con
 * recaudaciones por sala (hasta 20 salas).
 * ============================================================ */

#include <stdio.h>

#define MAX_THEATERS 20

typedef struct {
    float collect[MAX_THEATERS];
    int numTheaters;
} tTheater;

int main() {
    /*var declaration*/
    tTheater santalo;
    tTheater sants;

    /* table initialitation, setting the number of theather to 0 */
    santalo.numTheaters = 0;
    sants.numTheaters = 0;

    return 0;
}


/* ============================================================
 * EJEMPLO 05: Carga de datos a partir de una secuencia.
 * Se lee una secuencia de valores reales desde la entrada
 * estándar (terminada en -1.0) y se insertan en la tabla.
 * Muestra el uso de punteros para parámetros de salida y
 * la notación -> para acceder a campos del struct.
 * ============================================================ */

#include <stdio.h>

#define MAX_THEATERS 20
#define END_SEQ -1.0

typedef struct {
    float collect[MAX_THEATERS];
    int numTheaters;
} tTheater;

void fillTable(tTheater *movieTheater) {
    /* var definition */
    float temp;

    /* table initialization */
    movieTheater->numTheaters = 0;
    scanf("%f", &temp);  /* read the first number */

    /* iteration while the read number is not -1 */
    while  (temp != END_SEQ) {
        /*Save the read number in the table*/
        movieTheater->collect[movieTheater->numTheaters] = temp;
        movieTheater->numTheaters = movieTheater->numTheaters + 1;
        scanf("%f", &temp);
    }
}

/*
 * EJEMPLO PRÁCTICO de fillTable:
 * ─────────────────────────────────────────────────────────────
 * Supón un cine con 3 salas. El usuario introduce por teclado:
 *   150.50 200.00 75.25 -1.0
 *
 * Ejecución paso a paso:
 *
 *   Estado inicial:
 *     numTheaters = 0
 *     collect = [ ?, ?, ?, ... ]
 *     Se lee temp = 150.50
 *
 *   Iteración 1 (temp=150.50, no es -1 → entra al while):
 *     collect[0] = 150.50
 *     numTheaters = 1
 *     Se lee temp = 200.00
 *
 *   Iteración 2 (temp=200.00, no es -1 → sigue):
 *     collect[1] = 200.00
 *     numTheaters = 2
 *     Se lee temp = 75.25
 *
 *   Iteración 3 (temp=75.25, no es -1 → sigue):
 *     collect[2] = 75.25
 *     numTheaters = 3
 *     Se lee temp = -1.0
 *
 *   Comprobación while (temp == -1.0 → SALE del bucle)
 *
 *   Resultado final:
 *     numTheaters = 3
 *     collect = [ 150.50, 200.00, 75.25, (resto sin usar) ]
 * ─────────────────────────────────────────────────────────────
 */


/* ============================================================
 * EJEMPLO 06: Recorrido de una tabla (actualización).
 * Se recorre toda la tabla para multiplicar cada elemento
 * por 1.20 (simulando un aumento del 20% en el precio).
 * Se usa un bucle for porque se conoce el número exacto
 * de elementos.
 * ============================================================ */

#include <stdio.h>

#define MAX_THEATERS 20
#define END_SEQ -1.0

typedef struct {
    float collect[MAX_THEATERS];
    int numTheaters;
} tTheater;

void update(tTheater *movieTheater) {
   /* var definition */
   int i;

    /* iteration. We can use a for ... do iteration because we know the exact number of element of the table */
    for (i = 0; i < movieTheater->numTheaters; i++) {
        movieTheater->collect[i] = movieTheater->collect[i] *1.20; 
    }
}


/* ============================================================
 * EJEMPLO 07: Algoritmo completo con fillTable, update y printTable.
 * Programa completo que lee recaudaciones, las muestra,
 * aplica un incremento del 20% y las vuelve a mostrar.
 * Demuestra paso por referencia (puntero) vs paso por valor
 * en funciones que modifican o solo leen la tabla.
 * ============================================================ */

#include <stdio.h>

#define MAX_THEATERS 20
#define END_SEQ -1.0

typedef struct {
    float collect[MAX_THEATERS];
    int numTheaters;
} tTheater;

void fillTable(tTheater *movieTheater) {
    /* var definition */
    float temp;

    /* table initialization */
    movieTheater->numTheaters = 0;
    scanf("%f", &temp);  /* read the first dígit */

    /* iteration while the read number is not -1 */

    while (temp != END_SEQ) {

        /* Save the read number in the table */
        movieTheater->collect[movieTheater->numTheaters] = temp;
        movieTheater->numTheaters = movieTheater->numTheaters + 1; 
        scanf("%f", &temp);
    }
}

void update(tTheater *movieTheater) {
    /* var definition */
    int i;

    /* iteration. We can use a for ... do iteration because we know the exact number of element of the table */
    for (i = 0; i < movieTheater->numTheaters; i++) {
        movieTheater->collect[i] = movieTheater->collect[i] *1.20 ;  
    }
}

void printTable(tTheater movieTheater) {
    /* var definition */
    int i;

    /* iteration. We can use a for ... do iteration because we know the exact number of element of the table */

    for (i=0; i< movieTheater.numTheaters; i++) {
        printf("%f ",  movieTheater.collect[i]);
    }
}

int main() {
    tTheater santalo;
    fillTable(&santalo);
    printTable(santalo);
    update(&santalo);
    printTable(santalo);

    return 0;
}


/* ============================================================
 * EJEMPLO 08: Búsqueda de un elemento en una tabla.
 * Se busca si hay alguna sala con recaudación superior a un
 * valor dado. Usa un bucle while con variable booleana "found"
 * para detener la búsqueda al encontrar el elemento.
 * Devuelve la posición o -1 si no se encuentra.
 * ============================================================ */

#include <stdio.h>
#include <stdbool.h>

#define MAX_THEATERS 20
#define END_SEQ -1.0

typedef struct {
    float collect[MAX_THEATERS];
    int numTheaters;
} tTheater;

void fillTable(tTheater *movieTheater) {
    /* var definition */
    float temp;

    /* table initialization */
    movieTheater->numTheaters = 0;
    scanf("%f", &temp);  /* read the first digit */

    /* iteration while the read number is not -1 */
    while  (temp != END_SEQ)  {

        /*Save the read number in the table*/
        movieTheater->collect[movieTheater->numTheaters] = temp;
        movieTheater->numTheaters = movieTheater->numTheaters + 1;
        scanf("%f", &temp);
    }
}

void searchValue(tTheater movieTheater, float value, int *position) {
    int i;
    bool found;

    /*variable initialization. i is set to 1 to start searching in the table at postion 1 and found to false to indicate that so far value has not been found. The out parameter position  is set to -1 by default */
    i = 0;
    found = false;
    *position = -1;

    /* iteration while there are still elements in the table and the value has not been found */
    while (i < movieTheater.numTheaters && !found)  {
        if (movieTheater.collect[i] >= value) {
            found = true;
        } else {
            i++;
        }
    }

    if (found) {
        *position = i;
    }
}

int main () {
    tTheater movieTheater;
    float value;
    int position;

    fillTable(&movieTheater);
    scanf("%f", &value);
    searchValue(movieTheater, value, &position);
    printf("%d", position);

    return 0;
}

/*
 * EJEMPLO PRÁCTICO de searchValue (Ejemplo 08):
 * ─────────────────────────────────────────────────────────────
 * Supón que fillTable ha cargado estas recaudaciones:
 *   collect = [ 50.0, 80.0, 120.0, 45.0 ]
 *   numTheaters = 4
 *
 * El usuario quiere buscar si alguna sala recaudó >= 100.0
 *   → value = 100.0
 *
 * Ejecución paso a paso de searchValue:
 *
 *   Inicio:
 *     i = 0, found = false, *position = -1
 *
 *   Iteración 1 (i=0):
 *     collect[0] = 50.0 → 50.0 >= 100.0? NO → i++ → i = 1
 *
 *   Iteración 2 (i=1):
 *     collect[1] = 80.0 → 80.0 >= 100.0? NO → i++ → i = 2
 *
 *   Iteración 3 (i=2):
 *     collect[2] = 120.0 → 120.0 >= 100.0? SÍ → found = true
 *     (no incrementa i, sale del while)
 *
 *   found es true → *position = 2
 *   Resultado: position = 2 (la sala de índice 2, es decir la tercera)
 *
 * ─────────────────────────────────────────────────────────────
 * Si en cambio buscamos value = 200.0 (ninguna sala llega):
 *
 *   Iteración 1 (i=0): 50.0 >= 200.0? NO → i = 1
 *   Iteración 2 (i=1): 80.0 >= 200.0? NO → i = 2
 *   Iteración 3 (i=2): 120.0 >= 200.0? NO → i = 3
 *   Iteración 4 (i=3): 45.0 >= 200.0? NO → i = 4
 *   i = 4 == numTheaters → SALE del while
 *
 *   found sigue false → *position queda en -1
 *   Resultado: position = -1 (no encontrado)
 * ─────────────────────────────────────────────────────────────
 */


/* ============================================================
 * EJEMPLO 09: Inserción ordenada en una tabla.
 * Al insertar cada nuevo elemento, se busca su posición
 * correcta en la tabla ordenada, se desplazan los elementos
 * a la derecha y se inserta en el lugar adecuado.
 * La tabla se mantiene siempre ordenada.
 * ============================================================ */

#include <stdio.h>
#include <stdbool.h>

#define MAX_THEATERS 20
#define END_SEQ -1.0

typedef struct {
    float collect[MAX_THEATERS];
    int numTheaters;
} tTheater;

void fillTable(tTheater *movieTheater) {
    /* var definition */
    float temp;
    int i, j;
    bool found;

    /* table initialization */
    movieTheater->numTheaters =0;
    scanf("%f", &temp);  /* read the first digit */

    /* iteration while the read number is not -1 */
    while (temp !=END_SEQ)  {
        i = 0;
        found = false;

        while (i < movieTheater->numTheaters && ! found)  {
            if (movieTheater->collect[i] <= temp)  {
                i++;
            } else {
                found = true;
            }
        }

        /* move values to the right */
        if (movieTheater->numTheaters > 0) {
            for (j = movieTheater->numTheaters; j >= i ;  j--) {
                movieTheater->collect[j] = movieTheater->collect[j-1];
            }
        }

        /* insert new value */
        movieTheater->collect[i] = temp;
        movieTheater->numTheaters = movieTheater->numTheaters + 1  ;
        scanf("%f", &temp);
    }
}

int main () {
    tTheater santalo;
    int i;

    fillTable(&santalo);

    for (i = 0; i < santalo.numTheaters; i++) {
        printf("%f ", santalo.collect[i]); 
    }

    return 0;
}

/*
 * EJEMPLO PRÁCTICO de fillTable con inserción ordenada (Ejemplo 09):
 * ─────────────────────────────────────────────────────────────
 * Supón que el usuario introduce por teclado: 80.0 30.0 120.0 50.0 -1.0
 *
 * La función tiene 3 fases por cada número que lee:
 *   FASE 1 – Buscar la posición correcta (líneas 450-458)
 *   FASE 2 – Desplazar elementos a la derecha (líneas 462-466)
 *   FASE 3 – Insertar el nuevo valor (líneas 469-470)
 *
 *
 * ═══════════════════════════════════════════════════════════
 * INSERCIÓN DE temp = 80.0 (tabla vacía, numTheaters = 0)
 * ═══════════════════════════════════════════════════════════
 *
 * FASE 1 – Buscar posición:
 *   Se ejecuta (línea 450): i = 0, found = false
 *   El while interno (línea 453):
 *     while (i < 0 && !found) → 0 < 0 es false → NO ENTRA
 *   Resultado: i = 0 (se insertará en la posición 0)
 *
 * FASE 2 – Desplazar:
 *   El if (línea 462): numTheaters > 0? → 0 > 0 es false → NO ENTRA
 *   No hay nada que mover porque la tabla está vacía.
 *
 * FASE 3 – Insertar:
 *   (línea 469): collect[0] = 80.0
 *   (línea 470): numTheaters = 0 + 1 = 1
 *
 *   Tabla: [ 80.0 ]
 *
 *
 * ═══════════════════════════════════════════════════════════
 * INSERCIÓN DE temp = 30.0 (numTheaters = 1)
 * ═══════════════════════════════════════════════════════════
 *
 * FASE 1 – Buscar posición:
 *   Se ejecuta (línea 450): i = 0, found = false
 *   El while interno (línea 453):
 *     while (0 < 1 && !false) → true → ENTRA
 *       (línea 454): collect[0]=80.0 <= 30.0? → NO
 *       (línea 457): found = true → sale del while
 *   Resultado: i = 0 (el 30.0 va ANTES del 80.0)
 *
 * FASE 2 – Desplazar:
 *   El if (línea 462): 1 > 0? → SÍ → entra al for
 *   El for (línea 463): j arranca en numTheaters=1, baja hasta i=0
 *     j=1: collect[1] = collect[0] → collect[1] = 80.0
 *   Ahora la tabla tiene:  [ 80.0, 80.0 ]  (la pos 0 se va a sobrescribir)
 *
 * FASE 3 – Insertar:
 *   (línea 469): collect[0] = 30.0
 *   (línea 470): numTheaters = 1 + 1 = 2
 *
 *   Tabla: [ 30.0, 80.0 ]
 *
 *
 * ═══════════════════════════════════════════════════════════
 * INSERCIÓN DE temp = 120.0 (numTheaters = 2)
 * ═══════════════════════════════════════════════════════════
 *
 * FASE 1 – Buscar posición:
 *   Se ejecuta (línea 450): i = 0, found = false
 *   El while interno (línea 453):
 *     i=0: while (0 < 2 && !false) → true → ENTRA
 *       (línea 454): collect[0]=30.0 <= 120.0? → SÍ → i++ → i=1
 *     i=1: while (1 < 2 && !false) → true → ENTRA
 *       (línea 454): collect[1]=80.0 <= 120.0? → SÍ → i++ → i=2
 *     i=2: while (2 < 2 && ...) → false → SALE (no encontró ninguno mayor)
 *   Resultado: i = 2 (el 120.0 va AL FINAL, después del 80.0)
 *
 * FASE 2 – Desplazar:
 *   El if (línea 462): 2 > 0? → SÍ → entra al for
 *   El for (línea 463): j arranca en 2, condición j >= i → 2 >= 2 → ENTRA
 *     j=2: collect[2] = collect[1] → collect[2] = 80.0
 *     j=1: 1 >= 2? → NO → SALE del for
 *   Pero como i=2, collect[2] se va a sobrescribir de todos modos.
 *
 * FASE 3 – Insertar:
 *   (línea 469): collect[2] = 120.0
 *   (línea 470): numTheaters = 2 + 1 = 3
 *
 *   Tabla: [ 30.0, 80.0, 120.0 ]
 *
 *
 * ═══════════════════════════════════════════════════════════
 * INSERCIÓN DE temp = 50.0 (numTheaters = 3)
 * ═══════════════════════════════════════════════════════════
 *
 * FASE 1 – Buscar posición:
 *   Se ejecuta (línea 450): i = 0, found = false
 *   El while interno (línea 453):
 *     i=0: while (0 < 3 && !false) → true → ENTRA
 *       (línea 454): collect[0]=30.0 <= 50.0? → SÍ → i++ → i=1
 *     i=1: while (1 < 3 && !false) → true → ENTRA
 *       (línea 454): collect[1]=80.0 <= 50.0? → NO
 *       (línea 457): found = true → SALE del while
 *   Resultado: i = 1 (el 50.0 va entre el 30.0 y el 80.0)
 *
 * FASE 2 – Desplazar:
 *   El if (línea 462): 3 > 0? → SÍ → entra al for
 *   El for (línea 463): j arranca en numTheaters=3, baja hasta i=1
 *     j=3: collect[3] = collect[2] → collect[3] = 120.0
 *     j=2: collect[2] = collect[1] → collect[2] = 80.0
 *     j=1: 1 >= 1 → ENTRA: collect[1] = collect[0] → collect[1] = 30.0
 *     j=0: 0 >= 1? → NO → SALE del for
 *   Tabla intermedia: [ 30.0, 30.0, 80.0, 120.0 ] (pos 1 se sobrescribirá)
 *
 * FASE 3 – Insertar:
 *   (línea 469): collect[1] = 50.0
 *   (línea 470): numTheaters = 3 + 1 = 4
 *
 *   Tabla: [ 30.0, 50.0, 80.0, 120.0 ]
 *
 *
 * ═══════════════════════════════════════════════════════════
 * Se lee temp = -1.0 → la condición del while principal
 * (línea 449): temp != END_SEQ → -1.0 != -1.0 → false → SALE
 *
 * RESULTADO FINAL (siempre ordenada de menor a mayor):
 *   numTheaters = 4
 *   collect = [ 30.0, 50.0, 80.0, 120.0 ]
 * ─────────────────────────────────────────────────────────────
 */


/* ============================================================
 * EJEMPLO 10 (Sección 3.2): Algoritmo de ordenación por selección.
 * Implementa el algoritmo Selection Sort: en cada iteración
 * busca el elemento mínimo del subvector no ordenado y lo
 * intercambia con la primera posición no ordenada.
 * ============================================================ */

#include <stdio.h>

#define MAX_THEATERS 20
#define END_SEQ -1.0

typedef struct {
    float collect[MAX_THEATERS];
    int numTheaters;
} tTheater;

void fillTable(tTheater *movieTheater) {
    /* var definition */
    int i;
    float temp;

    /* table initialization */
    movieTheater->numTheaters = 0;
    scanf("%f", &temp);  /* read the first digit */

    /* iteration while the read number is not -1 */
    while  (temp !=END_SEQ)  {
        /*Save the read number in the table*/
        movieTheater->collect[movieTheater->numTheaters] = temp;
        movieTheater->numTheaters = movieTheater->numTheaters + 1; 
        scanf("%f", &temp);  
    }
}

void sort(tTheater *movieTheater) {
    /* var definition */
    int i, j, posMin;
    int aux;

    i  =0;
    while (i < movieTheater->numTheaters)  {
        posMin = i;
        j = i + 1;
        while  (j < movieTheater->numTheaters)  {
            if (movieTheater->collect[j] < 
movieTheater->collect[posMin]) {
                posMin=j;
            }
            j = j + 1;
        }
        aux = movieTheater->collect[posMin];
        movieTheater->collect[posMin] = movieTheater->collect[i];
        movieTheater->collect[i] = aux;
        i = i + 1;
    }
}

int main () {
    tTheater santalo;
    int i;

    fillTable(&santalo);
    sort(&santalo);

    for (i = 0; i < santalo.numTheaters; i++) {
        printf("%f ", santalo.collect[i]);
    }

    return 0;
}


/* ============================================================
 * EJEMPLO 11 (Sección 3.3): Búsqueda dicotómica (binaria).
 * Busca un valor en una tabla ORDENADA dividiendo
 * repetidamente el rango de búsqueda a la mitad.
 * Mucho más eficiente que la búsqueda lineal para tablas grandes.
 * ============================================================ */

#include <stdio.h>

/* type definition for a table of 20 elements */
#define MAX_THEATERS 20

typedef struct {
    float collect[MAX_THEATERS];
    int numTheaters;
} tTheater;

void searchValue(tTheater movieTheater, float value, int *position) {

    int i;
    int first, last, middle;
    first = 0;
    *position = -1;
    last = movieTheater.numTheaters-1;
    while (first != last)  {
        middle = (first + last) / 2;
        if (movieTheater.collect[middle] < value) {
            first = middle + 1;
        } else {
            last = middle;
        }
    }
    if (movieTheater.collect[first] == value)  {
        *position = first;
    }
}


/* ============================================================
 * EJEMPLO 12 (Sección 4.1): Tablas de tuplas.
 * Cada elemento de la tabla es un struct complejo
 * (tTheaterDescription) con nombre, capacidad, recaudación
 * y fecha. Se muestra cómo acceder a campos anidados.
 * ============================================================ */

#include <stdio.h>

#define MAX_THEATERS 20
#define MAX_NAME 50

typedef struct {
    int day;
    int month;
    int year;
} tDate;

typedef struct {
    char name[MAX_NAME];
    int capacity;
    float collect;
    tDate date;
} tTheaterDescription;

typedef struct {
    tTheaterDescription movieTheathers[MAX_THEATERS];
    int numTheaters;
} tTheater;

int main () {
    tTheater santalo;
    int k;

    /* we can access to be information in the folowing way */

    /* to access to the name of the third theater in santalo */
    santalo.movieTheater[2].name;

    /* to access to the field collect of the  k th.  theater in santalo */
    santalo.movieTheaters[k-1].collect;

    /* to access to the capacity of the last theater stored in the table santalo */
    santalo.movieTheaters[santalo.numTheaters-1].capacity;

    return 0;
}


/* ============================================================
 * EJEMPLO 13 (Sección 4.2): Tablas de tablas.
 * Se define una tabla (tCompany) cuyos elementos son a su vez
 * tablas (tTheater). Se muestra cómo acceder a elementos
 * en estructuras doblemente anidadas (tabla de tablas de tuplas).
 * ============================================================ */

#include <stdio.h>

#define MAX_THEATERS 20
#define MAX_MOVIES 15

typedef struct {
    int day;
    int month;
    int year; 
} tDate; 

typedef struct {
    tString name;
    int capacity;
    float collect;
    tDate date;
} tTheaterDescription;

typedef struct {
    tTheaterDescription movieTheathers[MAX_THEATERS];
    int numTheaters;
} tTheater;

/* declaration of a table of tTheater */
typedef struct { 
    tTheater movies[MAX_MOVIES];
    int numMovies;
 } tCompany;

int main () {
    tCompany theMovieCompany;
    int m, k;
    int lmovie, ltheater;

    /* we can access to be information in the folowing way */

    /* to access to the name of the third theater of the 
first movie */
    theMovieCompany.movies[0].movieTheaters[2].name;

    /* to access to the filed collect of the  k th  theater 
of the m th movie */
    theMovieCompany.movies[m-1].movieTheaters[k-1].collect;

    /* to access to the capacity of the last theater of 
the last movie */
    lmovie = theMovieCompany.numMovies-1;
    ltheater = theMovieCompany.movies[lmovie].numTheaters-1;
        theMovieCompany.movies[lmovie].movieTheaters[ltheater].capacity;

    return 0;
}


/* ============================================================
 * EJEMPLO 14 (Sección 5): calculateMark - Cálculo de nota media.
 * Programa completo que define una tabla de CAAs (actividades
 * evaluables) con nombre y nota, permite añadir elementos
 * a la tabla y calcula la nota media recorriendo todos
 * los elementos.
 * ============================================================ */

#include <stdio.h>
#include <string.h>

/* Definition of the contants */
#define MAX_CAAS 5
#define MAX_NAME 5+1

/* Definition of the record tCaa */
typedef struct {
    char name[MAX_NAME];
    float mark;
} tCaa;

/* Definition of the table tSubject */
typedef struct {
    tCaa caa[MAX_CAAS];
    int numCaas;
} tSubject;


/* Predeclaration of the functions/actions */
void addCaa(tSubject *subject, tCaa caa);
float calculateMark(tSubject subject);


/* Main program */
int main(int argc, char **argv) {

    /* Variables definition */
    tSubject fp;
    tCaa caa1, caa2, caa3;
    float mark;

    /* Variables initialization */
    mark = 0;
    strcpy(caa1.name,"CAA01");
    caa1.mark = 10;
    strcpy(caa2.name,"CAA02");
    caa2.mark = 8.5;
    strcpy(caa3.name,"CAA03");
    caa3.mark = 7.5;

    fp.numCaas = 0;

    /* Add CAAs to the subject */
    addCaa(&fp, caa1);
    addCaa(&fp, caa2);
    addCaa(&fp, caa3);

    /* Calculate the mark */
    mark = calculateMark(fp);
    printf("The average mark of the %d CAA is %f\n", fp.numCaas, mark);

    return 0;
}


/* Implementation of the functions/actions */

/* Action that adds an element of type tCaa to tSubject table */
void addCaa(tSubject *subject, tCaa caa) {
    /* Add caa as the last element in subject */
    subject->caa[subject->numCaas] = caa;

    /* Increase the value of numCaas */
    subject->numCaas = subject->numCaas + 1;
}

/* Function that calculates the average of all tCaa contained in tSubject*/
float calculateMark(tSubject subject) {
    /* sum contains the sum of all the marks in tCaa that are in tSubject */
    float sum;
    int i;
    sum = 0.0;

    /* Traverse through all tCaa elements in tSubject and accumulate the marks */

    for (i = 0; i < subject.numCaas; i++) {
        sum = sum + subject.caa[i].mark;
    }

    /* Calculate the average of grades */
    return sum / subject.numCaas;
}


/* ============================================================
 * EJEMPLO 15 (Sección 5): calculateMark con iteración.
 * Adaptación del ejemplo anterior para que pida los valores
 * iterativamente por teclado. El usuario introduce el número
 * de CAAs y luego nombre y nota de cada una mediante un bucle.
 * ============================================================ */

#include <stdio.h>
#include <string.h>

/* Definition of the constants */
#define MAX_CAAS 10
#define MAX_NAME 10+1

/* Definition of the record tCaa */
typedef struct {
    char name[MAX_NAME];
    float mark;
} tCaa;

/* Definition of the table tSubject */
typedef struct {
    tCaa caa[MAX_CAAS];
    int numCaas;
} tSubject;

/* Predeclaration of the functions/actions */

void addCaa(tSubject *subject, tCaa caa);
float calculateMark(tSubject subject);

/* Main program */
int main() {
    /* Define variables */
    tSubject fp;
    float mark;
    int numCaas, i;
    tCaa caaAux;

    /* Initialize variables */
    mark = 0;
    numCaas = 0;
    i = 0;
 
    /* Initialize the table */
    fp.numCaas = 0;

    /* Enter CAA data from keyboard */
    printf("Number of CAAs to enter (<%d): ", MAX_CAAS);
    scanf("%d", &numCaas);

    for (i = 0; i < numCaas; i++) {   
        printf("Data for the CAA0%d : \n", i+1);
        printf("\tname : ");
        scanf("%s", caaAux.name);
        printf("\tmark : ");
        scanf("%f", &caaAux.mark);

        /* Add the auxiliary tCaa to the table */
        addCaa(&fp, caaAux);
    }

    /* We calculate the mark with the calculateMark function */
    mark = calculateMark(fp);
    printf("The average mark of the %d CAA is %f\n", fp.numCaas, mark);
    return 0;
}

/* Implementation of the functions/actions */
/* Action that adds an element of type tCaa to the tSubject table */
void addCaa(tSubject *subject, tCaa caa) {

    /* numCaas contains the number of elements of type tCaa
    * in the table
    */
    subject->caa[subject->numCaas] = caa;

    /* Once we have assigned a new element tCaa
    * to the table we increase the value of numCaas
    */
    subject->numCaas = subject->numCaas + 1;
}

/* Function that calculates the average of all tCaa contained in the tSubject table
*/
float calculateMark(tSubject subject) {

    /* Add caaAux to the table. In each iteration a different tCaa will be added */
    float sum;
    int i;
    sum = 0.0;

    /* Traverse through all tCaa elements in tSubject and accumulate the marks */
    for (i = 0; i < subject.numCaas; i++) {
        sum = sum + subject.caa[i].mark;
    }

    /* Calculate the average of grades */
    return sum / subject.numCaas;
}


/* ============================================================
 * EJEMPLO 16 (Sección 5): Recorrido frente a búsqueda.
 * Programa completo de gestión de jugadores de baloncesto.
 * Demuestra la diferencia entre recorrido (mostrar todos
 * los jugadores) y búsqueda (encontrar un jugador por número
 * y equipo usando while con variable booleana).
 * ============================================================ */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 20+1
#define MAX_SURNAME 20+1
#define MAX_PLAYERS 10

typedef enum {LOCAL, VISITING} tTeam;

/* Definition of the player struct */
typedef struct {
    char name[MAX_NAME];
    char surname[MAX_SURNAME];
    int number;
    tTeam team;
} tPlayer;

/* Definition of the player table type */
typedef struct {
    tPlayer players[MAX_PLAYERS];
    int numPlayers;
} tTablePlayers;

/* Actions declaration */
void readPlayer(tPlayer *p);
void showPlayer(tPlayer p);
void initializeTable(tTablePlayers *table);
void addPlayer(tTablePlayers *table, tPlayer p);
void showPlayers(tTablePlayers table);
void searchPlayer(tTablePlayers table, int number, tTeam team);

/* Main program */
int main(int argc, char **argv) {
    tPlayer player;
    tTablePlayers table;
    tTeam team;
    int number, i;

   initializeTable(&table);

    /* Introduce the players data */
    for (i=0; i<MAX_PLAYERS; i++) {
        readPlayer(&player);
        addPlayer(&table, player);
    }

    /* Show all the players */
    showPlayers(table);

    /* Search for a player */
    /* Ask for the information to be introduced
     * through the keyboard */
    printf("\nWhich player do you want to search for? : ");
    printf("\n>> Team (0=LOCAL, 1=VISITING) : ");
    scanf("%u", &team);
    printf(">> Number : ");
    scanf("%d", &number);

    /* Search for the player */ 
    searchPlayer(table, number, team);

    return 0;
}

/* Implementation of the actions */

void readPlayer(tPlayer *p) {
    printf("Enter the data of the new player: \n");
    printf("\tName: ");
    scanf("%s", p->name);
    printf("\tSurname: ");
    scanf("%s", p->surname);
    printf("\tTeam (0=LOCAL, 1=VISITING): ");
    scanf("%u", &p->team);
    printf("\tNumber: ");
    scanf("%d", &p->number);
}

void showPlayer(tPlayer p) {
    if (p.team == LOCAL) {
        printf("LOCAL   : %d %s,%s\n", p.number, p.surname, p.name);
    } else {
        printf("VISITING: %d %s,%s\n", p.number, p.surname, p.name);
    }
}

void initializeTable(tTablePlayers *table) {    
    table->numPlayers= 0;
}

void addPlayer(tTablePlayers *table, tPlayer p) {
    /* It is checked first that the table is not full! */
    if(table->numPlayers >= MAX_PLAYERS) {
        printf("Error adding player to the table\n");
    } else {
        /* The player is added to the table, and the
        * table's element counter is incremented */
        table->players[table->numPlayers] = p;

        /* Important! After adding a player, we must not
        * forget to increase the counter! */
        table->numPlayers++;
    }
}

void showPlayers(tTablePlayers table) {
    int i;
    i = 0;
    printf("\nTraverse: players added to the table ...\n");
    while (i < table.numPlayers) {
        showPlayer(table.players[i]);
        i = i+1;
    }
}

void searchPlayer(tTablePlayers table, int number, tTeam team) {
    int i;
    bool isFound; /* This is used to exit the loop, if the player is found */

   i=0;
   isFound = false;
   
    if (team == LOCAL) {
        printf("\nSearch: local player with number %d ...", number);
    } else {
        printf("\nSearch: visiting player with number %d ...", number);
    }

    while (i<table.numPlayers && !isFound) {
        if (table.players[i].number == number &&
            table.players[i].team == team) {
            isFound = true;
        }
        i++;
    }

    /* The results obtained are shown on the screen.
    */
    if (!isFound) {
        printf("\n>> No player found. \n");
    } else {
        printf("\n>> Player found : \n");
        showPlayer(table.players[i-1]);
    }
}
