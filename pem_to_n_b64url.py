from Crypto.PublicKey import RSA
from Crypto.Util.number import long_to_bytes
import base64
import sys

def pem_to_n_b64url(pem_filename, key_size=2048):
    # Carica la chiave RSA dal file PEM
    with open(pem_filename, "r") as f:
        key = RSA.import_key(f.read())
    
    # Estrai il modulo (n) come intero
    n_int = key.n
    # Converti n in byte, assicurandoti che abbia la lunghezza corretta (2048 bit = 256 byte)
    n_bytes = long_to_bytes(n_int, key_size // 8)
    
    # Codifica in base64 standard
    b64 = base64.b64encode(n_bytes).decode('ascii')
    
    # Converti in base64url: sostituisci '+' con '-', '/' con '_' e rimuovi eventuali '=' di padding
    b64url = b64.replace('+', '-').replace('/', '_').rstrip('=')
    
    return b64url

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python3 pem_to_n_b64url.py <key.pem>")
        sys.exit(1)
    
    pem_filename = sys.argv[1]
    n_b64url = pem_to_n_b64url(pem_filename)
    print("n_b64url:")
    print(n_b64url)
