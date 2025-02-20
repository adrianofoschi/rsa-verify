#!/usr/bin/env python3
import sys
import base64

def b64url_to_bytes(b64url_str):
    # Aggiunge padding se necessario
    rem = len(b64url_str) % 4
    if rem:
        b64url_str += '=' * (4 - rem)
    return base64.urlsafe_b64decode(b64url_str)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: {} <base64url_string>".format(sys.argv[0]))
        sys.exit(1)
    
    b64url_str = sys.argv[1]
    data = b64url_to_bytes(b64url_str)
    
    print("static const uint8_t my_array[] = {")
    for i in range(0, len(data), 16):
        chunk = data[i:i+16]
        line = ", ".join("0x{:02x}".format(b) for b in chunk)
        if i + 16 < len(data):
            print("    " + line + ",")
        else:
            print("    " + line)
    print("};")
    print("unsigned int my_array_len = {};".format(len(data)))
