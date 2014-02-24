#!/usr/bin/python3
# Copyright © 2013 Bart Massey
# [This work is licensed under the "MIT License"]
# Please see the file COPYING in the source
# distribution of this software for license terms.
#

# Random password generator. Uses bit pool efficiently.

from sys import argv

def ilog2(n):
    r = 0
    while (n > 0):
        n //= 2
        r += 1
    return r

alphanumeric_chars = \
  "abcdefghijklmnopqrstuvwxyz" + \
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ" + \
  "0123456789"

punctuation_chars = "!#$%^&*-;,./"

pw_char_choices = alphanumeric_chars + punctuation_chars

rf = None
i = 1
nchars = 8
argc = len(argv)
while argc > 1:
    if argv[i] == "-u":
        rf = open("/dev/urandom", "rb")
        i += 1
        argc -= 1
        continue
    if argv[i] == "-a":
        pw_char_choices = alphanumeric_chars
        i += 1
        argc -= 1
        continue
    if argc > 2 and argv[i] == "-n":
        nchars = int(argv[i + 1])
        assert nchars > 0
        i += 2
        argc -= 2
        continue
    assert False
assert(argc == 1)
if rf == None:
    rf = open("/dev/random", "rb")

npw_char_choices = len(pw_char_choices)
bitrange = npw_char_choices ** nchars
nbits = ilog2(bitrange)
# http://stackoverflow.com/questions/14822184/
nbytes = -(-nbits // 8)

while True:
    bitpool = 0
    bytestring = rf.read(nbytes)
    assert bytestring != ''
    for b in bytestring:
        bitpool <<= 8
        bitpool |= b
    if bitpool < bitrange:
        break

for _ in range(nchars):
    ix = bitpool % npw_char_choices
    print(pw_char_choices[ix], end="")
    bitpool //= npw_char_choices
print()
