import struct, subprocess, sys

def sec(path, name=".text"):
    d = open(path,"rb").read()
    e_shoff = struct.unpack(">I", d[0x20:0x24])[0]
    esz = struct.unpack(">H", d[0x2e:0x30])[0]
    n = struct.unpack(">H", d[0x30:0x32])[0]
    si = struct.unpack(">H", d[0x32:0x34])[0]
    hdrs = [struct.unpack(">10I", d[e_shoff+i*esz:e_shoff+i*esz+40]) for i in range(n)]
    strt = hdrs[si][4]
    for h in hdrs:
        e = d.index(b"\0", strt+h[0]); nm = d[strt+h[0]:e].decode()
        if nm == name: return d[h[4]:h[4]+h[5]]

def funcs(path):
    out = subprocess.run(["readelf","-sW",path],capture_output=True,text=True).stdout
    fns = {}
    for l in out.splitlines():
        p = l.split()
        if len(p)>7 and p[3]=="FUNC":
            fns[p[7]] = (int(p[1],16), int(p[2]))
    return fns

unit = sys.argv[1] if len(sys.argv)>1 else "pf_file"
o = funcs(f"build/43U/obj/libs/RVL_SDK/src/fa/{unit}.o")
m = funcs(f"build/43U/src/libs/RVL_SDK/src/fa/{unit}.o")
oraw = sec(f"build/43U/obj/libs/RVL_SDK/src/fa/{unit}.o")
mraw = sec(f"build/43U/src/libs/RVL_SDK/src/fa/{unit}.o")
diffs = []
for nm,(oo,os_) in sorted(o.items(), key=lambda x:x[1][0]):
    if nm not in m:
        diffs.append((nm, "missing")); continue
    mo,ms_ = m[nm]
    if oraw[oo:oo+os_] != mraw[mo:mo+ms_]:
        diffs.append((nm, f"orig {os_} mine {ms_}"))
print(f"{len(o)-len(diffs)}/{len(o)} fns byte-identical")
for d in diffs: print("  DIFF:", *d)
