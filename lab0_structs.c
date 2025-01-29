#include <stdint.h>
#include <stdio.h>

/*Crear la estructura con las variables del sistema */
typedef struct{

    uint32_t main_tank_level;
    int32_t reserve_tank_level;
    int16_t temperature;
    uint16_t checksum;
    uint8_t batery;
    
} measurements_struct;

/* Prototipo de la función para ver la data */
measurements_struct data_viewer(uint8_t array[12]);

int main()
{
    uint8_t entrada[12] = {80,253,68,0,1,44,255,255,252,24,10,11}; //80, -700, 300, 4294966296
    measurements_struct medicion = data_viewer(entrada);

    printf("Batería: %hu\n", medicion.batery);
    printf("Temperatura ambiente: %hd\n", medicion.temperature);
    printf("Nivel del tanque de reserva: %ld\n", medicion.reserve_tank_level);
    printf("Nivel del tanque principal: %lu\n", medicion.main_tank_level);

    return 0;
}

/* Función que toma el arreglo con los bytes de informacion para dividirla y devolver una estructura con el valor de cada medición */
measurements_struct data_viewer(uint8_t array[12])
{
    measurements_struct system_measurements;

    // Se toma el primer byte de cada variable como el más significativo
    // Se hacen los shifts necesarios para contemplar la información completa en cada caso en una sola variable

    system_measurements.temperature = (int16_t)(array[1] << 8) | array[2];                                                 //2 bytes
    system_measurements.main_tank_level = (uint32_t)((array[6] << 24) | (array[7] << 16) | (array[8] << 8) | array[9]);    //4 bytes
    system_measurements.checksum = (uint16_t)((array[10] << 8) | array[11]);                                               //2 bytes
    system_measurements.reserve_tank_level = (int32_t)((array[3] << 16) | (array[4] << 8) | array[5]);                     //3 bytes 
    system_measurements.batery = (uint8_t)array[0];                                                                        //1 byte 
    
    return system_measurements;
}