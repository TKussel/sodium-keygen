/*
Copyright (C) Sodium Keygen 2023 Tobias Kussel
(tobias.kussel@dkfz-heidelberg.de)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <getopt.h>
#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_usage(char *progname) {
  printf("Usage: %s [-f filename]\n", progname);
  printf("  -f filename Save the keys to the specified base filename, e.g. "
         "\"libsodium_key\"\n");
}

int main(int argc, char *argv[]) {
  if (sodium_init() < 0) {
    printf("Error: sodium_init() failed\n");
    return 1;
  }

  char *filename_base = NULL;

  int opt;
  while ((opt = getopt(argc, argv, "psf:")) != -1) {
    switch (opt) {
    case 'f':
      filename_base = optarg;
      break;
    default:
      print_usage(argv[0]);
      return 1;
    }
  }

  unsigned char pk[crypto_box_PUBLICKEYBYTES];
  unsigned char sk[crypto_box_SECRETKEYBYTES];

  crypto_box_keypair(pk, sk);

  if (filename_base == NULL) {
    printf("Public Key: ");
    for (int i = 0; i < crypto_box_PUBLICKEYBYTES; i++) {
      printf("%02x", pk[i]);
    }
    printf("\n");

    printf("Secret Key: ");
    for (int i = 0; i < crypto_box_SECRETKEYBYTES; i++) {
      printf("%02x", sk[i]);
    }
    printf("\n");
  }

  if (filename_base != NULL) {
    char filename_pub[strlen(filename_base) +
                      9]; // allocate space for ".pub.key\0"
    snprintf(filename_pub, sizeof(filename_pub), "%s.pub.key", filename_base);
    {
      FILE *fp = fopen(filename_pub, "w");
      if (fp == NULL) {
        printf("Error: cannot open file %s\n", filename_pub);
        return 1;
      }

      for (int i = 0; i < crypto_box_PUBLICKEYBYTES; i++) {
        fprintf(fp, "%02x", pk[i]);
      }

      fclose(fp);
    }

    char filename_priv[strlen(filename_base) +
                       10]; // allocate space for ".priv.key\0"
    snprintf(filename_priv, sizeof(filename_priv), "%s.priv.key",
             filename_base);
    {
      FILE *fp = fopen(filename_priv, "w");
      if (fp == NULL) {
        printf("Error: cannot open file %s\n", filename_priv);
        return 1;
      }
      for (int i = 0; i < crypto_box_SECRETKEYBYTES; i++) {
        fprintf(fp, "%02x", sk[i]);
      }
    }
  }

  return 0;
}
