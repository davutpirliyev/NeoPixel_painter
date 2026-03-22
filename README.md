# 🚀 STM32 NeoPixel POV Light Painter
A high-resolution Persistence of Vision (POV) light painting stick built with an **STM32F103C8T6** (Blue Pill) and a **144-LED WS2812B** strip.

## 🌟 Result
| Original Image | Light Painting Result |
| :---: | :---: |
| ![Original](tkm_afg.png) | ![Result](1774206424579.jpg) |

## 🛠 Technical Specifications
- **Microcontroller:** STM32F103C8T6 (ARM Cortex-M3)
- **LED Density:** 144 Pixels per meter (High Resolution)
- **Color Correction:** 2.8 Gamma LUT (Lookup Table) for realistic photo reproduction.
- **Timing:** ~28ms per column delay for a steady 5-second "painting" sweep.
- **Communication:** Driven via FastLED library on Pin PB15.

## 🧠 How It Works
### 1. Image Conversion
The provided `converter.py` Python script uses the **Pillow** library to resize images to 144 pixels in height and convert them into a 1D `const uint8_t` C-array.
### 2. Gamma Correction
To prevent colors from looking "washed out" in long-exposure photography, the firmware applies a **Gamma 2.8 correction curve**. This ensures that the deep reds and greens of the flags appear saturated and natural on the camera sensor.
### 3. Persistence of Vision (POV)
By flashing one vertical column of pixels at a time while moving the stick horizontally, the human eye (or a camera shutter) perceives a complete 2D image "floating" in mid-air.

## 📂 Project Structure
- `/src`: STM32 source code (PlatformIO/Arduino).
- `/tools`: Python image-to-header converter.
- `/include`: Generated `image_data.h` files.

## 🔧 Setup & Installation
1. **Convert Image:** Place your image in `/tools` and run `python converter.py`.
2. **Flash MCU:** - Set **BOOT0** jumper to **1**.
   - Connect via **CP2102** (UART1: PA9/PA10).
   - Upload via VS Code/PlatformIO.
   - Set **BOOT0** back to **0** and Reset.
3. **Capture:** Use a tripod and a smartphone with **Manual/Pro Mode** (Shutter: 8s, ISO: 100).