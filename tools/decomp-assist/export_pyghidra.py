import os
os.environ.setdefault("GHIDRA_INSTALL_DIR", "/tmp/opencode/ghidra_12.1.3_PUBLIC")
os.environ.setdefault("JAVA_HOME", "/tmp/opencode/jdk")
import pyghidra

pyghidra.start()
from java.io import File
from ghidra.base.project import GhidraProject
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

proj = GhidraProject.openProject("/tmp/opencode/gproj", "wii", True)
prog = proj.openProgram("/", "ipl.bin", True)
iface = DecompInterface()
iface.openProgram(prog)
mon = ConsoleTaskMonitor()

addrs = [0x81365C40, 0x81365EDC, 0x81366A2C, 0x81366C7C, 0x81366EE4, 0x813670A0, 0x813671C4, 0x813673E0]
out = open("/tmp/opencode/ghidra_decomp.txt", "w")
for a in addrs:
    addr = prog.getAddressFactory().getDefaultAddressSpace().getAddress(a)
    fn = prog.getFunctionManager().getFunctionAt(addr)
    if fn is None:
        fn = prog.getFunctionManager().getFunctionContaining(addr)
    if fn is None:
        out.write("=== %x NOT FOUND\n\n" % a)
        continue
    res = iface.decompileFunction(fn, 120, mon)
    out.write("=== %s @ %x\n" % (fn.getName(), a))
    if res and res.decompileCompleted():
        out.write(res.getDecompiledFunction().getC())
    else:
        out.write("DECOMP FAILED: %s\n" % (res.getErrorMessage() if res else "?"))
    out.write("\n\n")
out.close()
print("EXPORT DONE")
proj.close()
