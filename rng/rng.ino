#include "esp_system.h"
#include <mbedtls/sha256.h>

void printHash(uint8_t *hash, size_t length) {
  for (size_t i = 0; i < length; i++) {
    Serial.print(hash[i], BIN);
  }
}

void setup() {
  Serial.begin(921600);
}

void loop() {
  uint32_t random_number = esp_random();
  Serial.print(random_number, BIN);
  uint8_t hash[32];
  mbedtls_sha256_context ctx;
  mbedtls_sha256_init(&ctx);
  mbedtls_sha256_starts(&ctx, 0);
  mbedtls_sha256_update(&ctx, (const unsigned char*)&random_number, sizeof(random_number));
  mbedtls_sha256_finish(&ctx, hash);
  mbedtls_sha256_free(&ctx);

  printHash(hash, sizeof(hash));
}
