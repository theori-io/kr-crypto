#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include "winnt_types.h"
#include "pe_linker.h"
#include "ntoskernel.h"
#include "util.h"

void main()
{
    PIMAGE_DOS_HEADER DosHeader;
    PIMAGE_NT_HEADERS PeHeader;
    struct pe_image image = {
        .entry = NULL,
        .name = "gpkiapi_wc.dll",
    };

    if (pe_load_library(image.name, &image.image, &image.size) == false) {
        fprintf(stderr, "pe_load_library failed!\n");
        return;
    }

    link_pe_images(&image, 1);

    // Fetch the headers to get base offsets.
    DosHeader   = (PIMAGE_DOS_HEADER) image.image;
    PeHeader    = (PIMAGE_NT_HEADERS)(image.image + DosHeader->e_lfanew);

    // Load any additional exports.
    if (!process_extra_exports(image.image, PeHeader->OptionalHeader.BaseOfCode, "gpkiapi_wc.map")) {
        fprintf(stderr, "failed to load exports\n");
        return;
    }

    int (__cdecl *pEncryptNesCBC)(uint8_t *key, int keylen, uint8_t *iv, int ivlen, uint8_t *in, int inlen, uint8_t *out, int *outlen, int unk);
    void (__cdecl *pNesKeySchedule)(uint8_t *ek, uint8_t *k);
    if (get_export("EncryptNesCBC", &pEncryptNesCBC) == -1) {
        fprintf(stderr, "failed to resolve symbol\n");
        return;
    }
    if (get_export("NesKeySchedule", &pNesKeySchedule) == -1) {
        fprintf(stderr, "failed to resolve symbol\n");
        return;
    }

    uint8_t k[32], iv[32], ek[0x380];
    uint8_t data[32], out[64];
    int outlen = 64;
    for (int i = 0; i < 32; i++)
        k[i] = i;
    for (int i = 0; i < 32; i++)
        data[i] = i;
    memset(iv, 0, sizeof(iv));

    fprintf(stderr, "EncryptNesCBC: %p\n", pEncryptNesCBC);

    if(pEncryptNesCBC(k, 32, iv, 32, data, 32, out, &outlen, 0) != 0) {
       fprintf(stderr, "encrypt failed.\n");
       return;
    }

    printf("outlen: %d\n", outlen);
    for (int i = 0; i < 32; i++)
        printf("%02X ", out[i]);
    printf("\n");
}
