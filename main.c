#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "can_crc.h"
#include <stdint.h>

#define MAX_BITS 96
#define MAX_BYTES (MAX_BITS / 8)


int main() {
    char input[MAX_BITS + 2];
    uint8_t packed_bytes[MAX_BYTES] = {0};
    long long repetitions;

    printf("Podaj ciag bitow (maksymalnie 96 znakow '0' lub '1'): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = 0;

    int length = strlen(input);
    if (length > MAX_BITS || length == 0) {
        printf("Blad: Ciag musi miec od 1 do 96 bitow!\n");
        return 1;
    }

    for (int i = 0; i < length; i++) {
        int byte_index = i / 8;
        int bit_index = 7 - (i % 8);

        if (input[i] == '1') {
            packed_bytes[byte_index] |= (1 << bit_index);
        } else if (input[i] != '0') {
            printf("Blad: Niedozwolony znak '%c'. Wprowadz tylko 0 lub 1.\n", input[i]);
            return 1;
        }
    }

    printf("Podaj liczbe powtorzen obliczen (od 1 do 1 000 000 000): ");
    if (scanf("%lld", &repetitions) != 1 || repetitions < 1 || repetitions > 1000000000LL) {
        printf("Blad: Nieprawidlowa liczba powtorzen!\n");
        return 1;
    }
    uint16_t crc_result = 0;

    struct timespec start_time;
    struct timespec end_time;
    
    timespec_get(&start_time, TIME_UTC);
    
    for (long long r = 0; r < repetitions; r++) {
        crc_result = calc_can_crc(packed_bytes, length);
    }
    
    timespec_get(&end_time, TIME_UTC);

    double elapsed_ms = (double)(end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                                    (double)(end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
    double avg_time = elapsed_ms / repetitions;

    printf("\n================ WYNIKI ================\n");
    printf("Suma kontrolna CAN (HEX): 0x%04X\n", crc_result);
    printf("Laczny czas realizacji:   %.6f milisekund\n", elapsed_ms);
    printf("Sredni czas jednego wykonania:  %.9e milisekund (%.2f ns)\n", avg_time, avg_time * 1e9);
    printf("========================================\n");

    return 0;
}