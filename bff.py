#!/usr/bin/env python

import ptrace.debugger
import signal
import subprocess
import sys


#handles the process
def handler(child):
    pid = child.pid
    bff_debugger = ptrace.debugger.PtraceDebugger()
    print("Attach the running process %s" % pid)

    process = bff_debugger.addProcess(pid, False)

    while 1:
            process.singleStep()
            process.waitSignals(signal.SIGTRAP)
            if process.readBytes(process.getregs().rip, 2) == "\x0f\x05":
                print "SYSCALL DETECTED"
def main():
    child = subprocess.Popen(sys.argv[1], stdin=subprocess.PIPE)
    handler(child)
    child.kill()
    #child.wait()

if __name__ == "__main__":
    main()
