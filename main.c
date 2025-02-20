#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "data/message.h"
#include "data/public_key.h"
#include "data/signature.h"
#include "rsa.h"
#include "sha256.h"

static uint32_t rsa_workbuf[3 * RSANUMWORDS];

int main(int argc, char *argv[])
{
    uint8_t *rwdata;
    long rwlen;
    int status;

    // Image
    rwdata = message;
    rwlen = message_len;

	  struct sha256_ctx ctx;
	  uint8_t *hash;
    SHA256_init(&ctx);
    SHA256_update(&ctx, rwdata, rwlen);
    hash = SHA256_final(&ctx);

    struct rsa_public_key pub_key;

    // Copia i byte nel campo pub_key
    memcpy(&pub_key, rsa_public_key_bytes, sizeof(pub_key));

    status = rsa_verify(&public_key, signature, hash, rsa_workbuf);

    if (status)
      printf("Signature matches!\n");
    else
      printf("Signature does not match :-(\n");
    return status;
}
