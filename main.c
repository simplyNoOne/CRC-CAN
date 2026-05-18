#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "can_crc.h"
#include <stdint.h>

#define MAX_BITS 96
#define MAX_BYTES (MAX_BITS / 8)
#define MAX_INPUT_CHARS 256


static void discard_rest_of_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

void wait_for_enter() {
    printf("Nacisnij Enter, aby kontynuowac...");
    fflush(stdout);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int main() {
    char input[MAX_INPUT_CHARS];
    uint8_t packed_bytes[MAX_BYTES] = {0};
    long long repetitions;

    printf("Podaj ciag bitow (maksymalnie 96 bitow, spacje sa ignorowane): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        wait_for_enter();
        return 1;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        discard_rest_of_line();
        printf("Blad: Ciag jest zbyt dlugi! Maksymalnie 96 bitow.\n");
        wait_for_enter();
        return 1;
    }

    input[strcspn(input, "\n")] = 0;

    int length = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ') {
            continue;
        }

        if (input[i] != '0' && input[i] != '1') {
            printf("Blad: Niedozwolony znak '%c'. Wprowadz tylko 0 lub 1 oraz spacje.\n", input[i]);
            wait_for_enter();
            return 1;
        }

        if (length >= MAX_BITS) {
            printf("Blad: Ciag musi miec od 1 do 96 bitow!\n");
            wait_for_enter();
            return 1;
        }

        int byte_index = length / 8;
        int bit_index = 7 - (length % 8);

        if (input[i] == '1') {
            packed_bytes[byte_index] |= (1 << bit_index);
        }

        length++;
    }

    if (length == 0) {
        printf("Blad: Ciag musi miec od 1 do 96 bitow!\n");
        wait_for_enter();
        return 1;
    }

    printf("Podaj liczbe powtorzen obliczen (od 1 do 1 000 000 000): ");
    if (scanf("%lld", &repetitions) != 1 || repetitions < 1 || repetitions > 1000000000LL) {
        printf("Blad: Nieprawidlowa liczba powtorzen!\n");

        discard_rest_of_line();
        wait_for_enter();
        return 1;
    }
    discard_rest_of_line();
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

    wait_for_enter();
    return 0;
}