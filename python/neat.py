#!/usr/bin/python
# -*- coding: utf-8 -*-

class NEAT(object):
    block_size = 16
    key_size = 16
    round_keys = []
    deround_keys = []
    round_mix = []
    deround_mix = []
    box = [
            0, 1, 0, 1, 2, 3, 2, 3, 0, 1, 0, 1, 2, 3, 3, 2, 0, 1, 1, 0, 2, 3, 2, 3, 0, 1, 1, 0, 2, 3, 3, 2,
            0, 1, 0, 2, 1, 3, 3, 2, 0, 1, 2, 0, 1, 3, 2, 3, 0, 1, 2, 0, 1, 3, 3, 2, 0, 1, 0, 3, 1, 2, 2, 3,
            0, 1, 0, 3, 1, 2, 3, 2, 0, 1, 3, 0, 1, 2, 2, 3, 0, 1, 3, 0, 1, 2, 3, 2, 0, 1, 1, 2, 0, 3, 2, 3,
            0, 1, 1, 2, 0, 3, 3, 2, 0, 1, 2, 1, 0, 3, 2, 3, 0, 1, 2, 1, 0, 3, 3, 2, 0, 1, 1, 3, 0, 2, 2, 3,
            0, 1, 1, 3, 0, 2, 3, 2, 0, 1, 3, 1, 0, 2, 2, 3, 0, 1, 3, 1, 0, 2, 3, 2, 0, 1, 2, 3, 0, 1, 3, 2,
            0, 1, 3, 2, 0, 1, 2, 3, 0, 2, 0, 1, 2, 3, 3, 1, 0, 2, 1, 0, 2, 3, 1, 3, 0, 2, 1, 0, 2, 3, 3, 1,
            0, 2, 0, 2, 1, 3, 1, 3, 0, 2, 0, 2, 1, 3, 3, 1, 0, 2, 2, 0, 1, 3, 1, 3, 0, 2, 2, 0, 1, 3, 3, 1,
            0, 2, 0, 3, 1, 2, 1, 3, 0, 2, 0, 3, 1, 2, 3, 1, 0, 2, 3, 0, 1, 2, 1, 3, 0, 2, 3, 0, 1, 2, 3, 1,
            0, 2, 1, 2, 0, 3, 1, 3, 0, 2, 1, 2, 0, 3, 3, 1, 0, 2, 2, 1, 0, 3, 1, 3, 0, 2, 2, 1, 0, 3, 3, 1,
            0, 2, 1, 3, 0, 2, 1, 3, 0, 2, 3, 1, 0, 2, 1, 3, 0, 2, 3, 1, 0, 2, 3, 1, 0, 2, 2, 3, 0, 1, 1, 3,
            0, 2, 2, 3, 0, 1, 3, 1, 0, 2, 3, 2, 0, 1, 1, 3, 0, 2, 3, 2, 0, 1, 3, 1, 0, 3, 0, 1, 2, 3, 2, 1,
            0, 3, 0, 1, 2, 3, 1, 2, 0, 3, 1, 0, 2, 3, 2, 1, 0, 3, 1, 0, 2, 3, 1, 2, 0, 3, 0, 2, 1, 3, 2, 1,
            0, 3, 0, 2, 1, 3, 1, 2, 0, 3, 2, 0, 1, 3, 2, 1, 0, 3, 2, 0, 1, 3, 1, 2, 0, 3, 0, 3, 1, 2, 2, 1,
            0, 3, 3, 0, 1, 2, 2, 1, 0, 3, 1, 2, 0, 3, 2, 1, 0, 3, 1, 2, 0, 3, 1, 2, 0, 3, 2, 1, 0, 3, 2, 1,
            0, 3, 2, 1, 0, 3, 1, 2, 0, 3, 1, 3, 0, 2, 2, 1, 0, 3, 1, 3, 0, 2, 1, 2, 0, 3, 3, 1, 0, 2, 2, 1,
            0, 3, 3, 1, 0, 2, 1, 2, 0, 3, 2, 3, 0, 1, 2, 1, 0, 3, 2, 3, 0, 1, 1, 2, 0, 3, 3, 2, 0, 1, 2, 1,
            0, 3, 3, 2, 0, 1, 1, 2, 1, 2, 0, 1, 2, 3, 0, 3, 1, 2, 0, 1, 2, 3, 3, 0, 1, 2, 1, 0, 2, 3, 0, 3,
            1, 2, 1, 0, 2, 3, 3, 0, 1, 2, 0, 2, 1, 3, 0, 3, 1, 2, 0, 2, 1, 3, 3, 0, 1, 2, 2, 0, 1, 3, 0, 3,
            1, 2, 2, 0, 1, 3, 3, 0, 1, 2, 0, 3, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 0, 3, 1, 2, 3, 0, 1, 2, 3, 0,
            1, 2, 1, 2, 0, 3, 0, 3, 1, 2, 1, 2, 0, 3, 3, 0, 1, 2, 2, 1, 0, 3, 0, 3, 1, 2, 2, 1, 0, 3, 3, 0,
            1, 2, 1, 3, 0, 2, 3, 0, 1, 2, 3, 1, 0, 2, 0, 3, 1, 2, 3, 1, 0, 2, 3, 0, 1, 2, 2, 3, 0, 1, 0, 3,
            1, 2, 2, 3, 0, 1, 3, 0, 1, 2, 3, 2, 0, 1, 0, 3, 1, 2, 3, 2, 0, 1, 3, 0, 1, 3, 0, 1, 2, 3, 0, 2,
            1, 3, 1, 0, 2, 3, 0, 2, 1, 3, 0, 2, 1, 3, 0, 2, 1, 3, 0, 2, 1, 3, 2, 0, 1, 3, 2, 0, 1, 3, 0, 2,
            1, 3, 2, 0, 1, 3, 2, 0, 1, 3, 0, 3, 1, 2, 0, 2, 1, 3, 0, 3, 1, 2, 2, 0, 1, 3, 3, 0, 1, 2, 0, 2,
            1, 3, 3, 0, 1, 2, 2, 0, 1, 3, 1, 2, 0, 3, 0, 2, 1, 3, 1, 2, 0, 3, 2, 0, 1, 3, 2, 1, 0, 3, 0, 2,
            1, 3, 2, 1, 0, 3, 2, 0, 1, 3, 1, 3, 0, 2, 0, 2, 1, 3, 1, 3, 0, 2, 2, 0, 1, 3, 3, 1, 0, 2, 0, 2,
            1, 3, 3, 1, 0, 2, 2, 0, 1, 3, 2, 3, 0, 1, 2, 0, 1, 3, 3, 2, 0, 1, 0, 2, 2, 3, 0, 1, 2, 3, 0, 1,
            2, 3, 0, 1, 2, 3, 1, 0, 2, 3, 1, 0, 2, 3, 1, 0, 2, 3, 0, 2, 1, 3, 0, 1, 2, 3, 0, 2, 1, 3, 1, 0,
            2, 3, 2, 0, 1, 3, 0, 1, 2, 3, 2, 0, 1, 3, 1, 0, 2, 3, 0, 3, 1, 2, 0, 1, 2, 3, 0, 3, 1, 2, 1, 0,
            2, 3, 3, 0, 1, 2, 0, 1, 2, 3, 3, 0, 1, 2, 1, 0, 2, 3, 1, 2, 0, 3, 0, 1, 2, 3, 1, 2, 0, 3, 1, 0,
            2, 3, 2, 1, 0, 3, 0, 1, 2, 3, 2, 1, 0, 3, 1, 0, 2, 3, 1, 3, 0, 2, 0, 1, 2, 3, 1, 3, 0, 2, 1, 0,
            2, 3, 3, 1, 0, 2, 1, 0, 2, 3, 2, 3, 0, 1, 0, 1, 2, 3, 2, 3, 0, 1, 1, 0, 2, 3, 3, 2, 0, 1, 1, 0
          ]

    def __init__(self, key):
        self.key_schedule(key)
        self.dekey_schedule()

    def mul(self, a, b):
        if a == 0:
            a = 0x10000
        if b == 0:
            b = 0x10000
        return (((a * b) % 0x10001) & 0xFFFF)

    def invMul(self, a):
        if a <= 1:
            return a
        t = 0
        r = 0x10001
        newt = 1
        newr = a
        while newr:
            q = r / newr
            tmp = t
            t = newt
            newt = tmp - q * newt
            tmp = r
            r = newr
            newr = tmp - q * newr
        if t < 0:
            t += 0x10001
        return (t & 0xFFFF)

    def rol(self, a, b):
        b &= 0xf
        return (((a << b) | (a >> (16 - b))) & 0xFFFF)

    def ror(self, a, b):
        return self.rol(a, (-b & 0xFFFF))

    def mix(self, x, m, dec):
        row = self.box[(m & 0x7f) * 8:(m & 0x7f) * 8 + 8]
        if dec:
            x[row[0] + 4] ^= x[row[2]]
            x[row[1] + 4] ^= x[row[3]]
            x[row[4]] ^= x[row[6] + 4]
            x[row[5]] ^= x[row[7] + 4]
        else:
            x[row[0]] ^= x[row[2] + 4]
            x[row[1]] ^= x[row[3] + 4]
            x[row[4] + 4] ^= x[row[6]]
            x[row[5] + 4] ^= x[row[7]]

    def F(self, x, K):
        x[1] ^= x[0]
        x[2] ^= x[3]
        x[0] += x[2]
        x[0] &= 0xFFFF
        x[3] += x[1]
        x[3] &= 0xFFFF

        x[1] = self.mul(x[1], K[0])
        x[2] = self.mul(x[2], K[1])

        x[0] = self.rol(x[0], x[1])
        x[3] = self.rol(x[3], x[2])
        x[1] += x[3]
        x[1] &= 0xFFFF
        x[2] += x[0]
        x[2] &= 0xFFFF

    def invF(self, x, K):
        x[1] -= x[3]
        x[1] &= 0xFFFF
        x[2] -= x[0]
        x[2] &= 0xFFFF
        x[0] = self.ror(x[0], x[1])
        x[3] = self.ror(x[3], x[2])

        x[1] = self.mul(x[1], K[2])
        x[2] = self.mul(x[2], K[3])

        x[0] -= x[2]
        x[0] &= 0xFFFF
        x[3] -= x[1]
        x[3] &= 0xFFFF
        x[1] ^= x[0]
        x[2] ^= x[3]

    def process(self, xb, dec):
        x = []
        rk = self.round_keys
        rm = self.round_mix
        if dec:
            rk = self.deround_keys
            rm = self.deround_mix
        for i in xrange(0, 16, 2):
            x.append(xb[i] | (xb[i + 1] << 8))
        for i in xrange(12):
            l = x[:4]
            r = x[4:]
            self.F(l, rk[i*4:i*4 + 4])
            self.invF(r, rk[i*4:i*4 + 4])
            x = l + r
            self.mix(x, rm[i], dec)
        l = x[:4]
        r = x[4:]
        self.F(l, rk[12*4:12*4 + 4])
        self.invF(r, rk[12*4:12*4 + 4])
        x = l + r
        for i in xrange(4):
            x[i], x[i+4] = x[i+4], x[i]
        for i in xrange(0, 16, 2):
            xb[i] = x[i / 2] & 0xFF
            xb[i + 1] = x[i / 2] >> 8

    def encrypt(self, xb):
        self.process(xb, False)
        return xb

    def decrypt(self, xb):
        self.process(xb, True)
        return xb

    def key_schedule(self, key):
        Ks = [0xFD56, 0xC7D1, 0xE36C, 0xA2DC]
        x = []
        for i in xrange(0, 16, 2):
            x.append(key[i + 1] | key[i] << 8)
        for i in xrange(6):
            l = x[:4]
            r = x[4:]
            self.F(l, Ks)
            self.invF(r, Ks)
            x = l + r
            self.mix(x, 0, False)
            for j in xrange(8):
                self.round_keys.append(x[j])
        l = x[:4]
        r = x[4:]
        self.F(l, Ks)
        self.invF(r, Ks)
        x = l + r
        self.mix(x, 0, False)
        for i in xrange(4):
            self.round_keys.append(x[i])
        for i in xrange(12):
            self.round_mix.append(self.round_keys[i*4] ^ self.round_keys[i*4 + 3])

    def dekey_schedule(self):
        for i in xrange(13):
            self.deround_keys.append(self.invMul(self.round_keys[(12 - i) * 4 + 2]))
            self.deround_keys.append(self.invMul(self.round_keys[(12 - i) * 4 + 3]))
            self.deround_keys.append(self.invMul(self.round_keys[(12 - i) * 4 + 0]))
            self.deround_keys.append(self.invMul(self.round_keys[(12 - i) * 4 + 1]))
        for i in xrange(12):
            self.deround_mix.append(self.round_mix[11 - i])

