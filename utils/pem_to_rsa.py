import sys
from Crypto.PublicKey import RSA
from Crypto.Util.number import long_to_bytes, inverse, bytes_to_long
import base64

def pem_to_rsa_struct(pem_filename, key_size=2048):
    with open(pem_filename, "r") as f:
        key = RSA.import_key(f.read())
    
    n_int = key.n
    # Converti il modulo in byte (big-endian) con lunghezza fissa (256 byte per RSA2048)
    num_bytes = key_size // 8
    n_bytes = long_to_bytes(n_int, num_bytes)
    
    # Suddividi in blocchi da 4 byte, ma NON inverte i byte interni;
    # Invece, inverte l'ordine dei blocchi.
    blocks = [n_bytes[i:i+4] for i in range(0, len(n_bytes), 4)]
    blocks.reverse()  # Inverte l'ordine dei blocchi
    n_words = [int.from_bytes(block, byteorder='big') for block in blocks]
    
    # Calcola n0inv usando il primo blocco (che ora contiene i 4 byte meno significativi)
    n0 = n_words[0]
    n0inv = (-inverse(n0, 1 << 32)) % (1 << 32)
    
    # Calcola rr = (R^2 mod n), con R = 2^(key_size)
    R = 1 << key_size
    rr_int = (R * R) % n_int
    rr_bytes = long_to_bytes(rr_int, num_bytes)
    rr_blocks = [rr_bytes[i:i+4] for i in range(0, len(rr_bytes), 4)]
    rr_blocks.reverse()
    rr_words = [int.from_bytes(block, byteorder='big') for block in rr_blocks]
    
    return n_words, n0inv, rr_words

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python3 pem_to_rsa.py <key.pem>")
        sys.exit(1)
    
    pem_filename = sys.argv[1]
    n_words, n0inv, rr_words = pem_to_rsa_struct(pem_filename)
    
    # Stampa la struttura C
    print("static const struct rsa_public_key public_key = {")
    print("    .size   = 64,")
    print("    .n0inv  = 0x{:08x},".format(n0inv))
    print("    .n = {")
    for w in n_words:
        print("        0x{:08x},".format(w))
    print("    },")
    print("    .rr = {")
    for w in rr_words:
        print("        0x{:08x},".format(w))
    print("    }")
    print("};")
