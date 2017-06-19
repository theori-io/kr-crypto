#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t roundKeys[13 * 4];
    uint16_t roundMix[12];
} ks_t;

const uint8_t box[] = {
    0, 1, 0, 1, 2, 3, 2, 3,
    0, 1, 0, 1, 2, 3, 3, 2,
    0, 1, 1, 0, 2, 3, 2, 3,
    0, 1, 1, 0, 2, 3, 3, 2,
    0, 1, 0, 2, 1, 3, 3, 2,
    0, 1, 2, 0, 1, 3, 2, 3,
    0, 1, 2, 0, 1, 3, 3, 2,
    0, 1, 0, 3, 1, 2, 2, 3,
    0, 1, 0, 3, 1, 2, 3, 2,
    0, 1, 3, 0, 1, 2, 2, 3,
    0, 1, 3, 0, 1, 2, 3, 2,
    0, 1, 1, 2, 0, 3, 2, 3,
    0, 1, 1, 2, 0, 3, 3, 2,
    0, 1, 2, 1, 0, 3, 2, 3,
    0, 1, 2, 1, 0, 3, 3, 2,
    0, 1, 1, 3, 0, 2, 2, 3,
    0, 1, 1, 3, 0, 2, 3, 2,
    0, 1, 3, 1, 0, 2, 2, 3,
    0, 1, 3, 1, 0, 2, 3, 2,
    0, 1, 2, 3, 0, 1, 3, 2,
    0, 1, 3, 2, 0, 1, 2, 3,
    0, 2, 0, 1, 2, 3, 3, 1,
    0, 2, 1, 0, 2, 3, 1, 3,
    0, 2, 1, 0, 2, 3, 3, 1,
    0, 2, 0, 2, 1, 3, 1, 3,
    0, 2, 0, 2, 1, 3, 3, 1,
    0, 2, 2, 0, 1, 3, 1, 3,
    0, 2, 2, 0, 1, 3, 3, 1,
    0, 2, 0, 3, 1, 2, 1, 3,
    0, 2, 0, 3, 1, 2, 3, 1,
    0, 2, 3, 0, 1, 2, 1, 3,
    0, 2, 3, 0, 1, 2, 3, 1,
    0, 2, 1, 2, 0, 3, 1, 3,
    0, 2, 1, 2, 0, 3, 3, 1,
    0, 2, 2, 1, 0, 3, 1, 3,
    0, 2, 2, 1, 0, 3, 3, 1,
    0, 2, 1, 3, 0, 2, 1, 3,
    0, 2, 3, 1, 0, 2, 1, 3,
    0, 2, 3, 1, 0, 2, 3, 1,
    0, 2, 2, 3, 0, 1, 1, 3,
    0, 2, 2, 3, 0, 1, 3, 1,
    0, 2, 3, 2, 0, 1, 1, 3,
    0, 2, 3, 2, 0, 1, 3, 1,
    0, 3, 0, 1, 2, 3, 2, 1,
    0, 3, 0, 1, 2, 3, 1, 2,
    0, 3, 1, 0, 2, 3, 2, 1,
    0, 3, 1, 0, 2, 3, 1, 2,
    0, 3, 0, 2, 1, 3, 2, 1,
    0, 3, 0, 2, 1, 3, 1, 2,
    0, 3, 2, 0, 1, 3, 2, 1,
    0, 3, 2, 0, 1, 3, 1, 2,
    0, 3, 0, 3, 1, 2, 2, 1,
    0, 3, 3, 0, 1, 2, 2, 1,
    0, 3, 1, 2, 0, 3, 2, 1,
    0, 3, 1, 2, 0, 3, 1, 2,
    0, 3, 2, 1, 0, 3, 2, 1,
    0, 3, 2, 1, 0, 3, 1, 2,
    0, 3, 1, 3, 0, 2, 2, 1,
    0, 3, 1, 3, 0, 2, 1, 2,
    0, 3, 3, 1, 0, 2, 2, 1,
    0, 3, 3, 1, 0, 2, 1, 2,
    0, 3, 2, 3, 0, 1, 2, 1,
    0, 3, 2, 3, 0, 1, 1, 2,
    0, 3, 3, 2, 0, 1, 2, 1,
    0, 3, 3, 2, 0, 1, 1, 2,
    1, 2, 0, 1, 2, 3, 0, 3,
    1, 2, 0, 1, 2, 3, 3, 0,
    1, 2, 1, 0, 2, 3, 0, 3,
    1, 2, 1, 0, 2, 3, 3, 0,
    1, 2, 0, 2, 1, 3, 0, 3,
    1, 2, 0, 2, 1, 3, 3, 0,
    1, 2, 2, 0, 1, 3, 0, 3,
    1, 2, 2, 0, 1, 3, 3, 0,
    1, 2, 0, 3, 1, 2, 3, 0,
    1, 2, 3, 0, 1, 2, 0, 3,
    1, 2, 3, 0, 1, 2, 3, 0,
    1, 2, 1, 2, 0, 3, 0, 3,
    1, 2, 1, 2, 0, 3, 3, 0,
    1, 2, 2, 1, 0, 3, 0, 3,
    1, 2, 2, 1, 0, 3, 3, 0,
    1, 2, 1, 3, 0, 2, 3, 0,
    1, 2, 3, 1, 0, 2, 0, 3,
    1, 2, 3, 1, 0, 2, 3, 0,
    1, 2, 2, 3, 0, 1, 0, 3,
    1, 2, 2, 3, 0, 1, 3, 0,
    1, 2, 3, 2, 0, 1, 0, 3,
    1, 2, 3, 2, 0, 1, 3, 0,
    1, 3, 0, 1, 2, 3, 0, 2,
    1, 3, 1, 0, 2, 3, 0, 2,
    1, 3, 0, 2, 1, 3, 0, 2,
    1, 3, 0, 2, 1, 3, 2, 0,
    1, 3, 2, 0, 1, 3, 0, 2,
    1, 3, 2, 0, 1, 3, 2, 0,
    1, 3, 0, 3, 1, 2, 0, 2,
    1, 3, 0, 3, 1, 2, 2, 0,
    1, 3, 3, 0, 1, 2, 0, 2,
    1, 3, 3, 0, 1, 2, 2, 0,
    1, 3, 1, 2, 0, 3, 0, 2,
    1, 3, 1, 2, 0, 3, 2, 0,
    1, 3, 2, 1, 0, 3, 0, 2,
    1, 3, 2, 1, 0, 3, 2, 0,
    1, 3, 1, 3, 0, 2, 0, 2,
    1, 3, 1, 3, 0, 2, 2, 0,
    1, 3, 3, 1, 0, 2, 0, 2,
    1, 3, 3, 1, 0, 2, 2, 0,
    1, 3, 2, 3, 0, 1, 2, 0,
    1, 3, 3, 2, 0, 1, 0, 2,
    2, 3, 0, 1, 2, 3, 0, 1,
    2, 3, 0, 1, 2, 3, 1, 0,
    2, 3, 1, 0, 2, 3, 1, 0,
    2, 3, 0, 2, 1, 3, 0, 1,
    2, 3, 0, 2, 1, 3, 1, 0,
    2, 3, 2, 0, 1, 3, 0, 1,
    2, 3, 2, 0, 1, 3, 1, 0,
    2, 3, 0, 3, 1, 2, 0, 1,
    2, 3, 0, 3, 1, 2, 1, 0,
    2, 3, 3, 0, 1, 2, 0, 1,
    2, 3, 3, 0, 1, 2, 1, 0,
    2, 3, 1, 2, 0, 3, 0, 1,
    2, 3, 1, 2, 0, 3, 1, 0,
    2, 3, 2, 1, 0, 3, 0, 1,
    2, 3, 2, 1, 0, 3, 1, 0,
    2, 3, 1, 3, 0, 2, 0, 1,
    2, 3, 1, 3, 0, 2, 1, 0,
    2, 3, 3, 1, 0, 2, 1, 0,
    2, 3, 2, 3, 0, 1, 0, 1,
    2, 3, 2, 3, 0, 1, 1, 0,
    2, 3, 3, 2, 0, 1, 1, 0
};

uint16_t mul (uint32_t a, uint32_t b)
{
    if (a == 0) a = 0x10000;
    if (b == 0) b = 0x10000;
    return (a * b) % 0x10001;
}

uint16_t invMul (int a)
{
    if (a <= 1)
        return a;

    // extended euclidean algorithm
    // (https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Pseudocode)
    int t = 0, r = 0x10001, newt = 1, newr = a;
    while (newr)
    {
        int tmp;
        int q = r / newr;

        tmp = t;
        t = newt;
        newt = tmp - q * newt;

        tmp = r;
        r = newr;
        newr = tmp - q * newr;
    }
    if (t < 0)
        t += 0x10001;
    return t;
}

uint16_t rol (uint16_t a, uint16_t b)
{
    b &= 0xf;
    return (a << b) | (a >> (16 - b));
}

uint16_t ror (uint16_t a, uint16_t b)
{
    return rol(a, -b);
}

void mix (uint16_t * x, uint8_t m, int decryption)
{
    const uint8_t * row = &box[(m & 0x7f) * 8];
    if (decryption)
    {
        // values are swapped
        x[row[0] + 4] ^= x[row[2]];
        x[row[1] + 4] ^= x[row[3]];
        x[row[4]] ^= x[row[6] + 4];
        x[row[5]] ^= x[row[7] + 4];
    }
    else
    {
        x[row[0]] ^= x[row[2] + 4];
        x[row[1]] ^= x[row[3] + 4];
        x[row[4] + 4] ^= x[row[6]];
        x[row[5] + 4] ^= x[row[7]];
    }
}

void F (uint16_t * x, const uint16_t * K)
{
    x[1] ^= x[0];
    x[2] ^= x[3];
    x[0] += x[2];
    x[3] += x[1];

    x[1] = mul(x[1], K[0]);
    x[2] = mul(x[2], K[1]);

    x[0] = rol(x[0], x[1]);
    x[3] = rol(x[3], x[2]);
    x[1] += x[3];
    x[2] += x[0];
}

// F^-1
void invF (uint16_t * x, const uint16_t * K)
{
    x[1] -= x[3];
    x[2] -= x[0];
    x[0] = ror(x[0], x[1]);
    x[3] = ror(x[3], x[2]);

    x[1] = mul(x[1], K[2]);
    x[2] = mul(x[2], K[3]);

    x[0] -= x[2];
    x[3] -= x[1];
    x[1] ^= x[0];
    x[2] ^= x[3];
}

void NeatProcess (uint8_t * xb, const ks_t * KS, int decryption)
{
    uint16_t x[8];

    // convert to 16-bit integers
    for (int i = 0; i < 16; i += 2)
        x[i / 2] = xb[i] | (xb[i + 1] << 8);

    // 12 full rounds
    for (int i = 0; i < 12; ++i)
    {
        F(&x[0], &KS->roundKeys[i * 4]);
        invF(&x[4], &KS->roundKeys[i * 4]);
        mix(x, KS->roundMix[i], decryption);
    }

    // final half round
    F(&x[0], &KS->roundKeys[12 * 4]);
    invF(&x[4], &KS->roundKeys[12 * 4]);

    // swap left and right
    for (int i = 0; i < 4; ++i)
    {
        uint16_t tmp = x[i];
        x[i] = x[i + 4];
        x[i + 4] = tmp;
    }

    // convert back to bytes
    for (int i = 0; i < 16; i += 2)
    {
        xb[i] = x[i / 2];
        xb[i + 1] = x[i / 2] >> 8;
    }
}

void NeatEncrypt (uint8_t * xb, const ks_t * KS)
{
    NeatProcess(xb, KS, 0);
}

void NeatDecrypt (uint8_t * xb, const ks_t * KS)
{
    NeatProcess(xb, KS, 1);
}

void NeatKeySchedule (ks_t * ks, const uint8_t * key)
{
    const uint16_t Ks[] = { 0xFD56, 0xC7D1, 0xE36C, 0xA2DC };
    uint16_t x[8];

    // copy key to temporary block
    for (int i = 0; i < 16; i += 2)
        x[i / 2] = key[i + 1] | (key[i] << 8);

    // 6 full rounds (12 64-bit round keys)
    for (int i = 0; i < 6; ++i)
    {
        F(&x[0], Ks);
        invF(&x[4], Ks);
        mix(x, 0, 0);
        for (int j = 0; j < 8; ++j)
            ks->roundKeys[i * 8 + j] = x[j];
    }

    // 1 full round (last 64-bit round key)
    F(&x[0], Ks);
    invF(&x[4], Ks);
    mix(x, 0, 0);
    for (int j = 0; j < 4; ++j)
        ks->roundKeys[48 + j] = x[j];

    // generate round mix values
    for (int i = 0; i < 12; ++i)
    {
        ks->roundMix[i] = ks->roundKeys[i * 4] ^ ks->roundKeys[i * 4 + 3];
    }
}

void NeatDeKeySchedule (ks_t * dKS, const ks_t * KS)
{
    // reverse and swap the round keys
    for (int i = 0; i < 13; ++i)
    {
        dKS->roundKeys[i * 4 + 0] = invMul(KS->roundKeys[(12 - i) * 4 + 2]);
        dKS->roundKeys[i * 4 + 1] = invMul(KS->roundKeys[(12 - i) * 4 + 3]);
        dKS->roundKeys[i * 4 + 2] = invMul(KS->roundKeys[(12 - i) * 4 + 0]);
        dKS->roundKeys[i * 4 + 3] = invMul(KS->roundKeys[(12 - i) * 4 + 1]);
    }

    // reverse the round mix values
    for (int i = 0; i < 12; ++i)
    {
        dKS->roundMix[i] = KS->roundMix[11 - i];
    }
}

int main (int argc, char *argv[])
{
    // key (128-bit)
    uint8_t k[16];
    // data block (128-bit)
    uint8_t x[16];
    // round keys
    ks_t KS, dKS;

    for (int i = 0; i < 16; ++i)
        k[i] = i;
    for (int i = 0; i < 16; ++i)
        x[i] = i ^ 0x55;

    NeatKeySchedule(&KS, k);
    NeatEncrypt(x, &KS);

    NeatDeKeySchedule(&dKS, &KS);
    NeatDecrypt(x, &dKS);

    for (int i = 0; i < 16; i++)
        printf("%02X ", x[i] ^ 0x55);
    printf("\n");

    return 0;
}
