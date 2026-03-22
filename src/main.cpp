// #include <Arduino.h>
// #include <FastLED.h>
// #include "image_data.h" // Your generated file

// // --- CONFIGURATION ---
// #define LED_PIN     PB15    // Connect LED DIN to PB15 (or any 5V tolerant pin)
// #define NUM_LEDS    144     // Your strip height
// #define BRIGHTNESS  50      // Keep this LOW (max 255) to save battery/power
// #define COLUMN_DELAY 2      // Milliseconds between columns (controls image width)
// #define BUTTON_PIN  PA0

// // Gamma correction lookup table (Gamma 2.8)
// const uint8_t PROGMEM gammaTable[] = {
//     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//     0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,
//     1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,
//     3,  3,  4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  7,
//     7,  7,  8,  8,  8,  9,  9,  9, 10, 10, 10, 11, 11, 11, 12, 12,
//     13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20,
//     20, 21, 21, 22, 22, 23, 24, 24, 25, 25, 26, 27, 27, 28, 29, 29,
//     30, 31, 31, 32, 33, 34, 34, 35, 36, 37, 37, 38, 39, 40, 40, 41,
//     42, 43, 44, 45, 46, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
//     57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
//     73, 74, 76, 77, 78, 79, 80, 81, 83, 84, 85, 86, 88, 89, 90, 91,
//     93, 94, 95, 97, 98, 99, 101, 102, 104, 105, 107, 108, 110, 111, 113, 114,
//     116, 117, 119, 121, 122, 124, 125, 127, 129, 130, 132, 134, 135, 137, 139, 141,
//     142, 144, 146, 148, 150, 151, 153, 155, 157, 159, 161, 163, 165, 166, 168, 170,
//     172, 174, 176, 178, 180, 182, 184, 186, 189, 191, 193, 195, 197, 199, 201, 204,
//     206, 208, 210, 212, 215, 217, 219, 221, 224, 226, 228, 231, 233, 235, 238, 240,
//     243, 245, 248, 250, 253, 255 };

// CRGB leds[NUM_LEDS];

// void setup() {
// // Initialize Button with Internal Pull-up
//     pinMode(BUTTON_PIN, INPUT_PULLUP);

//     // STM32 is fast, but WS2812B needs specific timing
//     FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
//     FastLED.setBrightness(BRIGHTNESS);
//     FastLED.clear();
//     FastLED.show();
// }
// void paintImage() {
//     for (int col = 0; col < IMAGE_WIDTH; col++) {
//         for (int row = 0; row < NUM_LEDS; row++) {
//             int pixelIndex = (col * NUM_LEDS + row) * 3;
            
//             // Apply Gamma Correction from the table
//             uint8_t r = gammaTable[image_data[pixelIndex]];
//             uint8_t g = gammaTable[image_data[pixelIndex + 1]];
//             uint8_t b = gammaTable[image_data[pixelIndex + 2]];
            
//             leds[row] = CRGB(r, g, b);
//         }
//         FastLED.show();
//         delay(COLUMN_DELAY); 
//     }
//     FastLED.clear();
//     FastLED.show();
// }
// void loop() {
//     // Check if button is pressed (Logic is LOW because of INPUT_PULLUP)
//     if (digitalRead(BUTTON_PIN) == LOW) {
        
//         // Small debounce delay to prevent double-triggering
//         delay(50); 
        
//         // Run the painting sequence
//         paintImage();
        
//         // Wait for user to release the button before allowing another paint
//         while(digitalRead(BUTTON_PIN) == LOW) {
//             delay(10);
//         }
//     }
// }

#include <Arduino.h>
#include <FastLED.h>
#include "/home/cipher/Projects/painter/image_data.h"

// --- CONFIGURATION ---
#define LED_PIN     PB15
#define NUM_LEDS    144
#define BRIGHTNESS  25      // Keep it low for safety
#define COLUMN_DELAY 28     // Total ~5 seconds for the sweep

CRGB leds[NUM_LEDS];

// Gamma correction table (Gamma 2.8)
const uint8_t gammaTable[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,
    3,  3,  4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  7,
    7,  7,  8,  8,  8,  9,  9,  9, 10, 10, 10, 11, 11, 11, 12, 12,
    13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20,
    20, 21, 21, 22, 22, 23, 24, 24, 25, 25, 26, 27, 27, 28, 29, 29,
    30, 31, 31, 32, 33, 34, 34, 35, 36, 37, 37, 38, 39, 40, 40, 41,
    42, 43, 44, 45, 46, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
    57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
    73, 74, 76, 77, 78, 79, 80, 81, 83, 84, 85, 86, 88, 89, 90, 91,
    93, 94, 95, 97, 98, 99, 101, 102, 104, 105, 107, 108, 110, 111, 113, 114,
    116, 117, 119, 121, 122, 124, 125, 127, 129, 130, 132, 134, 135, 137, 139, 141,
    142, 144, 146, 148, 150, 151, 153, 155, 157, 159, 161, 163, 165, 166, 168, 170,
    172, 174, 176, 178, 180, 182, 184, 186, 189, 191, 193, 195, 197, 199, 201, 204,
    206, 208, 210, 212, 215, 217, 219, 221, 224, 226, 228, 231, 233, 235, 238, 240,
    243, 245, 248, 250, 253, 255 };

void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();
}

void paintImage() {
    for (int col = 0; col < IMAGE_WIDTH; col++) {
        for (int row = 0; row < NUM_LEDS; row++) {
            int pixelIndex = (col * NUM_LEDS + row) * 3;
            
            // Apply Gamma Correction
            uint8_t r = gammaTable[image_data[pixelIndex]];
            uint8_t g = gammaTable[image_data[pixelIndex + 1]];
            uint8_t b = gammaTable[image_data[pixelIndex + 2]];
            
            leds[row] = CRGB(r, g, b);
        }
        FastLED.show();
        delay(COLUMN_DELAY); 
    }
    FastLED.clear();
    FastLED.show();
}

void loop() {
    // 1. BLINK RED ONCE TO SHOW "GET READY"
    leds[0] = CRGB::Red; 
    FastLED.show();
    delay(200);
    FastLED.clear();
    FastLED.show();

    // 2. WAIT 5 SECONDS FOR YOU TO POSITION THE STICK
    delay(3000); 

    // 3. START THE PAINTING
    paintImage();

    // 4. WAIT BEFORE STARTING THE NEXT CYCLE
    delay(2000); 
}