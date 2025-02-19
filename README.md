# RSA Signature verification

Here is the signature verification code extracted from the Chrome OS
verified boot system "vboot". Fork of jhallen/rsa-verify.

# Instructions to test JWT signature verification

The input data you needs are:

```
test_data/jwk.json
test_data/jwt.txt
```

## 1. Divide JWT in parts

```
test_data/message.txt << header.payload
test_data/signature.b64 << the latest part of the jwt
```

## 2. Obtain formatted signature

We need to format signature in array of bytes and put it inside `data/signature.h`.

Convert signature from base64 to base64url
```
tr '_-' '/+' < signature.b64 > sig_std.b64
```

Check the signature length
```
wc -c < sig_std.b64
```

if it is not a multiple of 4 add the padding i.e. the necessary = at the end
```
echo "=" >> sig_std.b64
```

decode Base64 string to binary
```
base64 -d sig_std.b64 > sig.bin
```

verify that sig.bin is 256 bytes long
```
wc -c < sig.bin
```

generates signature.h header
```
xxd -i sig.bin
```

## 3. Obtain formatted message
We need to format message in array of bytes and put it inside `data/message.h`.
```
xxd -i header+payload.txt
```

## 4. Obtain formatted public key (JWK)
We need to format public key (JWK) in a specific struct and put it inside `data/public_key.h`.

Convert JWK to PEM
```
python3 utils/jwk_to_pem.py test_data/jwk.json >> test_data/key.pem
```

Convert PEM to c rsa struct
```
python3 utils/pem_to_rsa.py test_data/key.pem
```

# Usage

```
make
./verify
```