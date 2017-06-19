#!/usr/bin/python
# -*- coding: utf-8 -*-

class PKCS7Padding(object):
    def __init__(self, bs=16):
        self._bs = bs

    def pad(self, data):
        padding = self._bs - (len(data) % self._bs)
        return data + (chr(padding) * padding)

    def unpad(self, data):
        assert len(data) % self._bs == 0
        padding = ord(data[-1])
        assert padding <= self._bs
        return data[:-padding]

class CBCCryptor(object):
    def __init__(self, cipher, key, iv, padding=PKCS7Padding):
        assert len(key) == cipher.key_size
        assert len(iv) == cipher.block_size
        self._cipher = cipher([ord(c) for c in key])
        self._padding = padding(cipher.block_size)
        self._iv = [ord(c) for c in iv]

    def encrypt(self, plaintext):
        ciphertext = []
        prev_block = self._iv
        padded = self._padding.pad(plaintext)
        bs = self._cipher.block_size
        blocks = [padded[i*bs:(i+1)*bs] for i in xrange(len(padded) / bs)]
        for block in blocks:
            block = [ord(c) for c in block]
            xored = [(c ^ p) for (c, p) in zip(block, prev_block)]
            prev_block = self._cipher.encrypt(xored)
            ciphertext.append(prev_block)
        return ''.join([chr(c) for c in [ctblock for ctblocks in ciphertext for ctblock in ctblocks]])

    def decrypt(self, ciphertext):
        assert len(ciphertext) % self._cipher.block_size == 0
        plaintext = []
        prev_block = self._iv
        bs = self._cipher.block_size
        blocks = [ciphertext[i*bs:(i+1)*bs] for i in xrange(len(ciphertext) / bs)]
        for block in blocks:
            block = [ord(c) for c in block]
            _block = list(block)
            xored = [(t ^ p) for (t, p) in zip(self._cipher.decrypt(block), prev_block)]
            prev_block = _block
            plaintext.append(xored)
        padded = ''.join([chr(c) for c in [ptblock for ptblocks in plaintext for ptblock in ptblocks]])
        return self._padding.unpad(padded)
