#!/usr/bin/env python3
import sys
import struct
from Crypto.PublicKey import RSA
from Crypto.Util.number import long_to_bytes, inverse, bytes_to_long

def pem_to_rsa_struct_bytes(pem_filename, key_size=2048):
    # Carica la chiave RSA dal PEM
    with open(pem_filename, "r") as f:
        key = RSA.import_key(f.read())
    
    n_int = key.n
    num_bytes = key_size // 8  # per RSA2048 -> 256 byte
    n_bytes = long_to_bytes(n_int, num_bytes)  # modulo in big-endian
    
    # Dividi in blocchi di 4 byte (senza alterare l'ordine interno dei byte)
    blocks = [n_bytes[i:i+4] for i in range(0, len(n_bytes), 4)]
    # Per ottenere l'array little-endian richiesto, inverti l'ordine dei blocchi:
    blocks.reverse()
    n_words = [int.from_bytes(block, byteorder='big') for block in blocks]
    
    # Calcola n0inv = (-1 / n[0]) mod 2^32 utilizzando il primo word (i 4 byte meno significativi)
    n0 = n_words[0]
    n0inv = (-inverse(n0, 1 << 32)) % (1 << 32)
    
    # Calcola rr = (R^2 mod n), con R = 2^(key_size)
    R = 1 << key_size
    rr_int = (R * R) % n_int
    rr_bytes = long_to_bytes(rr_int, num_bytes)
    rr_blocks = [rr_bytes[i:i+4] for i in range(0, len(rr_bytes), 4)]
    rr_blocks.reverse()
    rr_words = [int.from_bytes(block, byteorder='big') for block in rr_blocks]
    
    # Costruisci il buffer in formato della struttura
    result = bytearray()
    # Campo size: 64 (0x40) in little-endian (numero di parole; RSANUMWORDS)
    result.extend(struct.pack("<I", len(n_words)))
    # Campo n0inv:
    result.extend(struct.pack("<I", n0inv))
    # Campo n (64 parole)
    for word in n_words:
        result.extend(struct.pack("<I", word))
    # Campo rr (64 parole)
    for word in rr_words:
        result.extend(struct.pack("<I", word))
    
    return bytes(result)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: {} <key.pem>".format(sys.argv[0]))
        sys.exit(1)
    
    rsa_struct_bytes = pem_to_rsa_struct_bytes(sys.argv[1])
    
    # Stampa l'array in formato C (16 byte per linea)
    print("static const uint8_t rsa_public_key_bytes[] = {")
    for i in range(0, len(rsa_struct_bytes), 16):
        chunk = rsa_struct_bytes[i:i+16]
        line = ", ".join("0x{:02x}".format(b) for b in chunk)
        if i + 16 < len(rsa_struct_bytes):
            print("    " + line + ",")
        else:
            print("    " + line)
    print("};")
    print("unsigned int rsa_public_key_bytes_len = %d;" % len(rsa_struct_bytes))
