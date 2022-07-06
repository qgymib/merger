#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sha256_ctx_s
{
    uint8_t     data[64];   // current 512-bit chunk of message data, just like a buffer
    size_t      datalen;    // sign the data length of current chunk
    size_t      bitlen;     // the bit length of the total message
    uint32_t    state[8];   // store the middle state of hash abstract
} sha256_ctx_t;

/**
 * @brief Initialize SHA-256 context.
 * @param[out] ctx  Context
 */
void sha256_init(sha256_ctx_t *ctx);

/**
 * @brief Update SHA-256
 * @param[in] ctx   Context
 * @param[in] data  Data to calculate SHA-256
 * @param[in] size  Data size in bytes
 */
void sha256_update(sha256_ctx_t *ctx, const void* data, size_t size);

/**
 * @brief Output SHA-256 as 32 byte digest.
 * @param[in] ctx   SHA-256 context.
 * @param[out] hash 32 byte digest.
 */
void sha256_final(sha256_ctx_t* ctx, uint8_t hash[32]);

#ifdef __cplusplus
}
#endif

#endif   // SHA256_H