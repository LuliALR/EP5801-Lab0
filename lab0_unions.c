#include <stdint.h>
#include <stdio.h>

typedef struct{

    union {
        uint32_t level;       //los que llamo al leer para ver el dato completo
        uint8_t level_arr[4]; //los que modifico, tipo de dato segun el arreglo que recibo
    } main_tank_level;

    union {
        uint32_t level;
        uint8_t level_arr[4];
    } reserve_tank_level;

    union {
        int16_t temp;        
        uint8_t temp_arr[2]; 
    } temperature;

    union {
        uint16_t sum;
        uint8_t sum_arr[2];
    } checksum;

    uint8_t batery;

} measurements_struct;

measurements_struct data_viewer(uint8_t array[12]);

int main()
{
    uint8_t entrada[12] = {80,253,68,0,1,44,255,255,252,24,10,11}; //80, -700, 300, 4294966296
    measurements_struct medicion = data_viewer(entrada);

    printf("Batería: %hu\n", medicion.batery);
    printf("Temperatura ambiente: %hd\n", medicion.temperature.temp);
    printf("Nivel del tanque de reserva: %ld\n", medicion.reserve_tank_level.level);
    printf("Nivel del tanque principal: %lu\n", medicion.main_tank_level.level);

    return 0;
}

// Funcion que toma el arreglo con los bytes de informacion para dividirla y devolver una estructura con el valor de cada medición 
measurements_struct data_viewer(uint8_t array[12])
{
    measurements_struct measurements;

    int i;

    for (i = 0; i < sizeof(measurements.temperature.temp_arr); i++) { //size of array. Se ponen al revez en la union
        measurements.temperature.temp_arr[i] = array[2 - i];
    }

    for (i = 0; i < sizeof(measurements.main_tank_level.level_arr); i++) { //size of array
        measurements.main_tank_level.level_arr[i] = array[9 - i];
    }

    for (i = 0; i < sizeof(measurements.checksum.sum_arr); i++) { //size of array
        measurements.checksum.sum_arr[i] = array[11 - i];
    }

    for (i = 0; i < sizeof(measurements.reserve_tank_level.level_arr) - 1; i++) { //size of array
        measurements.reserve_tank_level.level_arr[i] = array[5 - i];
    }

    measurements.batery = (uint8_t)array[0];
    measurements.main_tank_level.level_arr[0] = 0;
    
    return measurements;
}