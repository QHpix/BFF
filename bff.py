import ptrace.debugger
import signal
import subprocess
import sys


#handles the process
def handler(target_process):
    bff_debug = ptrace.debugger.PtraceDebugger()
    process = bff_debug.addProcess(target_process.pid, False)
    registers = process.getregs()
    rax = registers.rax
    rbx = registers.rbx
    rcx = registers.rcx
    rdx = registers.rdx
    rip = registers.rip
    print("rip is at: 0x%x" % rip)
    process.detach()
    bff_debug.quit()

def main():
    child = subprocess.Popen(sys.argv[1:len(sys.argv)], stdin=subprocess.PIPE)
    handler(child)
    child.kill()
    child.wait()

if __name__ == "__main__":
    main()
