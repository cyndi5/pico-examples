#include "pico/stdlib.h"

/*
 *  LED digital display segments and their corresponding pins
 */
const uint SEGMENT_DP = 0;
const uint SEGMENT_A = 1;
const uint SEGMENT_B = 2;
const uint SEGMENT_C = 3;
const uint SEGMENT_D = 4;
const uint SEGMENT_E = 5;
const uint SEGMENT_F = 6;
const uint SEGMENT_G = 7;
const uint SEGMENTS[] = { SEGMENT_DP, SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G };
const uint SEGMENT_COUNT = 8;
const uint END = 9; // Invalid segment number for marking the end of a variable-length array
/*
 * Two-dimensional array indexed by the character then by the segment.
 * The first dimension is the character index (0-9 are digits 0-9, 10 is the decimal point, 11 is all segments on).
 * The second dimension is always 8 (total segment count).
 * But since not all segments are lit for a given character, we have to end the segments with the marker (END),
 * unless all eight segments are lit (as in the lamp test).
 */
const uint CHARACTERS[][8] = {
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, END }, // 0
    { SEGMENT_B, SEGMENT_C, END }, // 1
    { SEGMENT_A, SEGMENT_B, SEGMENT_D, SEGMENT_E, SEGMENT_G, END }, // 2 (also Z)
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_G, END }, // 3
    { SEGMENT_B, SEGMENT_C, SEGMENT_F, SEGMENT_G, END }, // 4
    { SEGMENT_A, SEGMENT_C, SEGMENT_D, SEGMENT_F, SEGMENT_G, END }, // 5 (also S)
    { SEGMENT_A, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // 6
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, END }, // 7
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // 8
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_F, SEGMENT_G, END }, // 9 (also Q)
    { SEGMENT_DP, END }, // .
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, SEGMENT_DP }, // LAMP TEST
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // A
    { SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // B
    { SEGMENT_A, SEGMENT_D, SEGMENT_E, SEGMENT_F, END }, // C
    { SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_G, END }, // D
    { SEGMENT_A, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // E
    { SEGMENT_A, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // F
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_F, SEGMENT_G, END }, // G (lower case)
    { SEGMENT_C, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // H (lower case)
    { SEGMENT_C, END }, // I
    { SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, END }, // J
    { SEGMENT_B, SEGMENT_C, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // K (upper case)
    { SEGMENT_D, SEGMENT_E, SEGMENT_F, END }, // L
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_E, SEGMENT_F, END }, // M (upper case)
    { SEGMENT_C, SEGMENT_E, SEGMENT_G, END }, // N (lower case)
    { SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_G, END }, // O (lower case)
    { SEGMENT_A, SEGMENT_B, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // P
    { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_F, SEGMENT_G, END }, // Q (also 9)
    { SEGMENT_E, SEGMENT_G, END }, // R (lower case)
    { SEGMENT_A, SEGMENT_C, SEGMENT_D, SEGMENT_F, SEGMENT_G, END }, // S (also 5)
    { SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // T (lower case)
    { SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, END }, // U (upper case)
    { SEGMENT_C, SEGMENT_D, SEGMENT_E, END }, // V (lower case)
    { SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, END }, // W (upper case)
    { SEGMENT_A, SEGMENT_D, SEGMENT_G, END }, // X (upper case)
    { SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_F, SEGMENT_G, END }, // Y (lower case)
    { SEGMENT_A, SEGMENT_B, SEGMENT_D, SEGMENT_E, SEGMENT_G, END } // Z (also 2)
};

/*
 * Index those characters with constants.
 */
const uint CHAR_0 = 0;
const uint CHAR_1 = 1;
const uint CHAR_2 = 2;
const uint CHAR_3 = 3;
const uint CHAR_4 = 4;
const uint CHAR_5 = 5;
const uint CHAR_6 = 6;
const uint CHAR_7 = 7;
const uint CHAR_8 = 8;
const uint CHAR_9 = 9;
const uint CHAR_DP = 10;
const uint CHAR_LAMP_TEST = 11;
const uint CHAR_A = 12;
const uint CHAR_B = 13;
const uint CHAR_C = 14;
const uint CHAR_D = 15;
const uint CHAR_E = 16;
const uint CHAR_F = 17;
const uint CHAR_G = 18;
const uint CHAR_H = 19;
const uint CHAR_I = 20;
const uint CHAR_J = 21;
const uint CHAR_K = 22;
const uint CHAR_L = 23;
const uint CHAR_M = 24;
const uint CHAR_N = 25;
const uint CHAR_O = 26;
const uint CHAR_P = 27;
const uint CHAR_Q = 28;
const uint CHAR_R = 29;
const uint CHAR_S = 30;
const uint CHAR_T = 31;
const uint CHAR_U = 32;
const uint CHAR_V = 33;
const uint CHAR_W = 34;
const uint CHAR_X = 35;
const uint CHAR_Y = 36;
const uint CHAR_Z = 37;

/// @brief sets a segment's pin to output
/// @param segment the segment to set to output
void set_dir_out(uint segment) {
    gpio_set_dir(segment, GPIO_OUT);
}

/// @brief initializes a segment's pin
/// @param segment the segment to initialize
void init(uint segment) {
    gpio_init(segment);
}

/// @brief set or turn on a segment
/// @param segment the segment to set
void set(uint segment) {
    gpio_put(segment, 1);
}

/// @brief reset or turn off a segment
/// @param segment the segment to reset
void reset(uint segment) {
    gpio_put(segment, 0);
}

/// @brief call the specified function on an array of segments
/// @param segments array of segments on which to call the function
/// @param segment_count size of the incoming array
/// @param something pointer to a function which takes a uint (the segment) and does something to it
void segments_do(uint segments[], size_t segment_count, void (*something)(uint)) {
    for(int i = 0; i < segment_count; i++) {
        something(segments[i]);
    }
}

/// @brief call the specified function on a variable-length constant-terminated array of segments
/// @param segments array of segments on which to call the function
/// @param something pointer to a function which takes a uint (the segment) and does something to it
/// @note Max array size is SEGMENT_COUNT. Terminate the array with the constant END.
void variable_segments_do(const uint segments[], void (*something)(uint)) {
    for(int i = 0; i < SEGMENT_COUNT && segments[i] != END; i++) {
        something(segments[i]);
    }
}


/// @brief call the specified function on all segments
/// @param something pointer to a function which takes a uint (the segment) and does something to it
void all_segments_do(void (*something)(uint)) {
    segments_do((uint *)SEGMENTS, sizeof(SEGMENTS)/sizeof(SEGMENTS[0]), something);
}

/// @brief flash a character for 250 ms and clear for 250 ms
/// @param index index of the character (such as CHAR_C)
void flash_character(uint index) {
    variable_segments_do(CHARACTERS[index], set);
    sleep_ms(250);
    all_segments_do(reset);
    sleep_ms(250);
}

int main() {
    uint text[] = { CHAR_C, CHAR_Y, CHAR_N, CHAR_T, CHAR_H, CHAR_I, CHAR_A,
        CHAR_H, CHAR_U, CHAR_N, CHAR_T, CHAR_E, CHAR_R,
        CHAR_O, CHAR_F,
        CHAR_K, CHAR_N, CHAR_O, CHAR_W, CHAR_L, CHAR_E, CHAR_D, CHAR_G, CHAR_E };
    all_segments_do(init);
    all_segments_do(set_dir_out);

    while (true) {
        for(int i = 0; i < sizeof(text)/sizeof(text[0]); i++) {
            flash_character(text[i]);
        }

        sleep_ms(2000);

        for(int i = 0; i < 3; i++) {
            all_segments_do(set);
            sleep_ms(250);
            all_segments_do(reset);
            sleep_ms(250);
        }

        sleep_ms(2000);

        variable_segments_do(CHARACTERS[1], set); // Display the character index 1 (1)
        sleep_ms(250);
        all_segments_do(reset); // Clear the display between characters
        sleep_ms(250);
        variable_segments_do(CHARACTERS[0], set); // Display the character index 0 (0)
        sleep_ms(250);
        all_segments_do(reset);
        
        sleep_ms(2000);

        /*
         * Display all the characters in the array.
         */
        for(int c = 0; c < 38; c++) {
            variable_segments_do(CHARACTERS[c], set);
            sleep_ms(250);
            all_segments_do(reset);
            sleep_ms(250);
        }

        sleep_ms(2000);

        /*
         * Display "8675309"
         */
        variable_segments_do(CHARACTERS[CHAR_8], set);
        sleep_ms(250);
        all_segments_do(reset);
        sleep_ms(250);
        variable_segments_do(CHARACTERS[CHAR_6], set);
        sleep_ms(250);
        all_segments_do(reset);
        sleep_ms(250);
        variable_segments_do(CHARACTERS[CHAR_7], set);
        sleep_ms(250);
        all_segments_do(reset);
        sleep_ms(250);
        variable_segments_do(CHARACTERS[CHAR_5], set);
        sleep_ms(250);
        all_segments_do(reset);
        sleep_ms(250);
        variable_segments_do(CHARACTERS[CHAR_3], set);
        sleep_ms(250);
        all_segments_do(reset);
        sleep_ms(250);
        variable_segments_do(CHARACTERS[CHAR_0], set);
        sleep_ms(250);
        all_segments_do(reset);
        sleep_ms(250);
        variable_segments_do(CHARACTERS[CHAR_9], set);
        sleep_ms(250);
        all_segments_do(reset);
        sleep_ms(250);

        sleep_ms(2000);
    }
}
