from PIL import Image
import numpy as np

def image_to_rgb_arrays(image_path, target_size=(64, 64)):
    # Open the image
    img = Image.open(image_path)
    
    # Resize the image to the target size using LANCZOS filter
    img = img.resize(target_size, Image.LANCZOS)
    
    # Convert the image to RGB mode in case it's not
    img = img.convert("RGB")
    
    # Convert the image to a numpy array
    img_array = np.array(img)
    
    # Split the image array into R, G, and B components
    red_channel = img_array[:, :, 0]
    green_channel = img_array[:, :, 1]
    blue_channel = img_array[:, :, 2]
    
    return img, red_channel, green_channel, blue_channel

def save_channel_to_csv(channel_data, filename):
    # Save the channel data to a CSV file with space-separated values
    np.savetxt(filename, channel_data, fmt='%d', delimiter=' ')


image_path = 'lena.jpeg'
target_size = (16, 16)  # You can try (32, 32), (64, 64), or other sizes
downscaled_img, red, green, blue = image_to_rgb_arrays(image_path, target_size)

# Display the downscaled image
downscaled_img.show()

# Save each channel to separate CSV files
save_channel_to_csv(red, 'red_channel.csv')
save_channel_to_csv(green, 'green_channel.csv')
save_channel_to_csv(blue, 'blue_channel.csv')

# Confirm by printing shapes
print("Red channel shape:", red.shape)
print("Green channel shape:", green.shape)
print("Blue channel shape:", blue.shape)
