#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Definir los Macros */
#define MAX_STACK_SIZE 12

/* Definir la estructura del item y del stack */
typedef struct ITEM {

    uint32_t interruption_time;
    uint16_t *ref_ptr;
    uint8_t input_pin;

} item_struct;

typedef struct STACK {

    item_struct* stack_arr;
    uint8_t item_counter;
    uint8_t size;

} stack_struct;

/* Prototipos de las funciones básicas del stack y de resolución*/
item_struct pop(stack_struct* stack);
uint8_t count_items(stack_struct stack);
uint8_t push(stack_struct* stack, item_struct const* item);
bool is_empty(stack_struct stack);
bool is_full(stack_struct stack);
uint8_t resolve_instructions(stack_struct* stack);

/* Enumeración de las posibles instrucciones a ejecutar */
enum INSTRUCTIONS {
    INSTRUCTION_0 = 0,
    INSTRUCTION_1,
    INSTRUCTION_2,
    INSTRUCTION_3,
    INSTRUCTION_4,
    INSTRUCTION_5,
    INSTRUCTION_6,
};

/* Código de prueba del programa */
int main()
{
    // Argumentos: stack size to malloc, los items 

    /* Crear la pila */
    stack_struct stack = {0};
    stack.size = MAX_STACK_SIZE;      
    stack.stack_arr = (item_struct*)malloc(stack.size*sizeof(item_struct));
    
    /* Arreglo con las instrucciones a ejecutar, referencia y tiempo de interrupción*/
    uint8_t inst_arr[7] = {6,5,4,3,2,1,0};
    uint16_t ref = 0;
    uint32_t int_time = 5;

    /* Crear items, uno por cada instruccion */
    item_struct item_1 = {int_time, &ref, inst_arr[0]};
    item_struct item_2 = {int_time, &ref, inst_arr[1]};
    item_struct item_3 = {int_time, &ref, inst_arr[2]};
    item_struct item_4 = {int_time, &ref, inst_arr[3]};
    item_struct item_5 = {int_time, &ref, inst_arr[4]};
    item_struct item_6 = {int_time, &ref, inst_arr[5]};
    item_struct item_7 = {int_time, &ref, inst_arr[6]};

    /*Llenar la pila con los items*/
    push(&stack, &item_1);
    push(&stack, &item_2);
    push(&stack, &item_3);
    push(&stack, &item_4);
    push(&stack, &item_5);
    push(&stack, &item_6);
    push(&stack, &item_7);
    
    /* Ejecutar las interrupciones */
    size_t count = resolve_instructions(&stack);

    /* Liberar memoria dinámica */
    free(stack.stack_arr);
    return count;

}


/* Definición de las funciones básicas del stack*/
bool is_full(stack_struct stack)
{
    return stack.item_counter == stack.size;
}

bool is_empty(stack_struct stack)
{
    return stack.item_counter == 0;
}

uint8_t count_items(stack_struct stack)
{
    return stack.item_counter;
}

uint8_t push(stack_struct* stack, item_struct const* item) //constant pointer to item
{
    //use realloc if it reaches the limit
    
    if(is_full(*stack)) {
        printf("Can't push item, stack is full\n");
        return 0;
    }

    (*stack).stack_arr[(*stack).item_counter] = *item;  // Guardo el item de entrada en el tope del stack
    (*stack).item_counter++;                           
    
    return 1;
}

item_struct pop(stack_struct* stack)
{
    if(is_empty(*stack)) {
        printf("Can't pop item, stack is empty\n");
        item_struct item = {0};
        return item;
    }

    (*stack).item_counter--;
    return (*stack).stack_arr[(*stack).item_counter]; // Devuelvo el item guardado en el tope del stack
}


/* Definición de la función de reslución */
uint8_t resolve_instructions(stack_struct* stack)
{
    uint8_t stack_size = (*stack).item_counter; // Tamaño del stack, cantidad de items y por ende de instrucciones a ejecutar
    size_t count = 0;                           // Contador 
    enum INSTRUCTIONS instructions;             // Posibles interrupciones
    bool pin_1 = false;                         // Salida del pin 1
    item_struct poped_item = {0};               // Variable para guardar el item que se saca del stack
    int i;

    if(is_empty(*stack)) {
        printf("No hay instrucciones por ejecutar");
        return count;
    }
    
    for (i = 0; i < stack_size; i++) {

        poped_item = pop(stack);
        instructions = poped_item.input_pin;  
        //instructions = (*stack).stack_arr[stack_size - 1 - i].input_pin; // Las instrucciones corresponden al pin de entrada

        switch(instructions){
            case INSTRUCTION_0:
                // Hacer toggle de una variable booleana para el pin 1
                pin_1 = !pin_1;
                printf("Instrucción 0. Modifica Pin 1 ---> %d\n", pin_1);
                break;

            case INSTRUCTION_1:
                // Imprimir el valor del pin 1
                printf("Instrucción 1. Pin 1 ---> %d\n", pin_1);
                break;

            case INSTRUCTION_2:
                // Aumentar el contador
                count++;
                printf("Instrucción 2. Modifica Contador ---> %d\n", count);
                break;

            case INSTRUCTION_3:
                // Imprimir el contador
                printf("Instrucción 3. Contador ---> %d\n", count);
                break;

            case INSTRUCTION_5:
                // Verificar el número de items en la pila
                printf("Instrucción 5. Cantidad de ítems restantes en la pila ---> %d\n", (*stack).item_counter);
                break;

            case INSTRUCTION_6:
                // Si la pila está llena, finalizar la ejecución del programa
                if(is_full(*stack)){
                    printf("La pila está llena");
                    exit(404);
                }
                break;

            default: 
                printf("No se encontró la instrucción\n");
                break;
        }

        //(*stack).item_counter--;
    }

    return count;

}