from krcrypt import CBCCryptor
from neat import NEAT
from nes import NES
import os

cryptor = CBCCryptor(NEAT, os.urandom(16), os.urandom(16))

e = cryptor.encrypt('Theori is the best cybersecurity company!')
print 'Encrypted with NEAT:', e.encode('hex')
d = cryptor.decrypt(e)
print 'Decrypted with NEAT:', d

cryptor = CBCCryptor(NES, os.urandom(32), os.urandom(32))
e = cryptor.encrypt('Theori is the best cybersecurity company!')
print 'Encrypted with NES:', e.encode('hex')
d = cryptor.decrypt(e)
print 'Decrypted with NES:', d
