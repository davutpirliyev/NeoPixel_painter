from PIL import Image

# CONFIGURATION
IMAGE_PATH = "oguzhan_logo.png"  # Ensure this file is in the same folder
LED_COUNT = 144 
OUTPUT_FILE = "image_data.h"

def convert_to_c_array():
    try:
        img = Image.open(IMAGE_PATH).convert('RGB')
    except FileNotFoundError:
        print(f"Error: Could not find {IMAGE_PATH}")
        return

    # Resize height to match LED count
    width_pct = (LED_COUNT / float(img.size[1]))
    new_width = int((float(img.size[0]) * float(width_pct)))
    
    # Compatibility fix for older Pillow versions
    try:
        resample_type = Image.Resampling.LANCZOS
    except AttributeError:
        resample_type = Image.LANCZOS # For older versions
        
    img = img.resize((new_width, LED_COUNT), resample_type)

    with open(OUTPUT_FILE, "w") as f:
        f.write(f"// Image Dimensions: {new_width} width x {LED_COUNT} height\n")
        f.write(f"const int IMAGE_WIDTH = {new_width};\n")
        f.write(f"const int IMAGE_HEIGHT = {LED_COUNT};\n\n")
        f.write("const unsigned char image_data[] = {\n")
        
        for x in range(new_width):
            f.write(f"  // Column {x}\n  ")
            for y in range(LED_COUNT):
                r, g, b = img.getpixel((x, y))
                # WS2812B usually uses GRB order, but RGB is easier to code
                f.write(f"0x{r:02x}, 0x{g:02x}, 0x{b:02x}, ")
            f.write("\n")
            
        f.write("};\n")
    print(f"Success! Created {OUTPUT_FILE} with {new_width} columns.")

if __name__ == "__main__":
    convert_to_c_array()