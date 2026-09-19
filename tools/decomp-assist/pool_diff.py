import sys
from elftools.elf.elffile import ELFFile

MINE = 'build/43U/src/src/utility/iplESMisc.o'
BASE = 'build/43U/obj/src/utility/iplESMisc.o'


def pool(path):
    e = ELFFile(open(path, 'rb'))
    sec = {s.name: s for s in e.iter_sections()}
    d = sec['.data'].data()
    out = []
    off = 0
    while off < len(d):
        end = d.find(b'\x00', off)
        if end < 0:
            break
        s = d[off:end]
        if len(s) >= 4 and all(32 <= c < 127 or c == 0x0a for c in s):
            out.append((off, s.decode('latin1')))
        off = end + 1
    return out


def main():
    mine = pool(sys.argv[1] if len(sys.argv) > 1 else MINE)
    base = pool(sys.argv[2] if len(sys.argv) > 2 else BASE)
    n = min(len(mine), len(base))
    for i in range(n):
        if mine[i][1] != base[i][1]:
            print('FIRST DIVERGENCE at index %d' % i)
            for j in range(max(0, i - 2), min(n, i + 5)):
                mark = '*' if mine[j][1] != base[j][1] else ' '
                print('%s %3d mine=%-8s base=%-8s' % (mark, j, hex(mine[j][0]), hex(base[j][0])))
                print('      M %r' % mine[j][1][:70])
                print('      B %r' % base[j][1][:70])
            print()
            print('mine has %d strings, base has %d' % (len(mine), len(base)))
            return 1
    print('POOL IDENTICAL up to %d (mine=%d base=%d)' % (n, len(mine), len(base)))
    if len(mine) != len(base):
        for j in range(n, max(len(mine), len(base))):
            src = mine if j < len(mine) else base
            print(' extra %3d %r' % (j, src[j][1][:70]))
    return 0


if __name__ == '__main__':
    sys.exit(main())
