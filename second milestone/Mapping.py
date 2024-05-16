import serial

# Open serial port for UART communication
ser = serial.Serial("COM3", 9600, timeout=1)  # Change 'COM3' to your UART port

# Open file to save GPS data
file_name = "Coordinates.txt"
open("coordinates.txt", "w").close()  # clearing the file

# Main loop
char_to_send = input("Enter U to receive the date in EEPROM: ")

# Send the character
ser.write(char_to_send.encode())
flag = True
with open(file_name, "a") as file:
    while True:
        # Prompt user to send character

        # Read data from serial port
        data = ser.readline().decode("utf-8").strip()

        # Check if data is "logdone", if so, break out of the loop
        if data == "done":
            print("Received 'done'. Stopping writing to file.")
            break

        # Remove spaces and convert numbers to float and divide by 100000
        data = "".join(data.split())  # Remove spaces
        data = " ".join(
            str(float(num) / 100000) if num.isdigit() else num for num in data.split()
        )

        # Write data to file
        file.write(data + "\n")
        # Print received data
        if flag:
            if data != "logdone":
                print("Data received:", data)
            elif data == "logdone":
                flag = False
                continue

        else:
            if not data:
                continue
            else:
                print("Total Distance is ", float(data) * 1000)

file.close() 

# %%
import folium

# Read locations from text file
locations = []
latitude = []
longitude = []
with open("coordinates.txt", "r") as file:
    latitudes_done = False
    for line in file:
        line = line.strip()  # Remove leading/trailing whitespaces

        if line == "logdone":
            break  # Exit the loop when 'logdone' is encountered

        if not line:  # Skip empty lines
            continue

        if line == "latdone":
            latitudes_done = True
            continue

        if not latitudes_done:
            if len(line) > 7:
                latitude.append(int(line[0:2]) + (float(line[2:]) / 60))
        else:
            if len(line) > 7:
                longitude.append(int(line[0:2]) + (float(line[2:]) / 60))

    for loc in range(len(longitude)):
        locations.append([latitude[loc], longitude[loc]])


m = folium.Map(location=locations[0], zoom_start=23)  # Start Point
for loc in locations:
    folium.Marker(location=loc).add_to(m)
# print(locations)
# display
m

# %%

# Hassan Ramadan Zaref 2101364
