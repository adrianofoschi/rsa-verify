import base64
from Crypto.Util.number import bytes_to_long, long_to_bytes, inverse, getPrime

# Il valore "n" del JWK
# Dati del JWK fornito da Google.
# Modulo in formato base64url (senza spazi o newline)
n_b64url = "uac7NRcojCutcceWq1nrpLGJjQ7ywvgWsUcb1DWMKJ3KNNHiRzh9jshoi9tmq1zlarJ_h7GQg8iU1qD7SgpVYJmjlKG1MNVRAtuNrNMC0UAnNfG7mBBNorHFndfp-9cLTiMjXSXRzhNqiMvTVKeolRdMB2lH9RzJnwlpXtvUbD7M1pXOlPlMaOy1zxUnHn0uszU5mPRQk79i03BNrAdhwrAUB-ZuMnqpjaUcb9VU3KIwuZNPtsVenLN12sRYpaZ6WBw8Q9q7fAoaJUovM0Go8deC9pJYyxJuHdVo9HP0osyzg3g_rOYi14wmvMBuiDf3F4pTnudAfFyl3d0Mn_i4ZQ"

# Decodifica base64url (aggiungi padding se necessario)
def base64url_decode(data):
    # Aggiungi padding
    rem = len(data) % 4
    if rem > 0:
        data += '=' * (4 - rem)
    return base64.urlsafe_b64decode(data)

n_bytes = base64url_decode(n_b64url)
n_int = bytes_to_long(n_bytes)
print("Modulo (n) in decimale:", n_int)

# Converti il modulo in array di 32-bit little-endian:
# Assumendo che n_bytes abbia lunghezza 256 (2048 bit)
# Suddividi in blocchi di 4 byte e inverti l'ordine dei byte in ciascun blocco.
words = []
for i in range(0, len(n_bytes), 4):
    word_bytes = n_bytes[i:i+4]
    # Inverti i byte (per little-endian)
    word_le = word_bytes[::-1]
    word = int.from_bytes(word_le, byteorder='big')
    words.append(word)
print("n = {")
for w in words:
    print("    0x{:08x},".format(w))
print("};")

# Calcola n0inv: -1/n[0] mod 2^32
n0 = words[0]
n0inv = (-inverse(n0, 1<<32)) % (1<<32)
print("n0inv = 0x{:08x}".format(n0inv))

# Calcola rr = (R^2 mod n), dove R = 2^(RSA_KEY_SIZE) = 2^2048
R = 1 << 2048
rr_int = (R * R) % n_int
rr_bytes = long_to_bytes(rr_int, 256)  # 256 bytes
# Converti rr_bytes in array di 32-bit little-endian come sopra
rr_words = []
for i in range(0, len(rr_bytes), 4):
    word_bytes = rr_bytes[i:i+4]
    word_le = word_bytes[::-1]
    word = int.from_bytes(word_le, byteorder='big')
    rr_words.append(word)
print("rr = {")
for w in rr_words:
    print("    0x{:08x},".format(w))
print("};")