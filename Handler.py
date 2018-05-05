#!/usr/bin/python

# This is the Handler class
# Usage: Handler(child)
import ptrace.debugger
import signal
class Handler():

    # Class Variables
    _child = None
    _bff_debugger = None
    _process = None

    # Constructor
    def __init__(self, child):
        self._child = child
        _bff_debugger = ptrace.debugger.PtraceDebugger()
        print("Attaching the running process %s" % child.pid)
        _process = _bff_debugger.addProcess(child.pid, False)

    # Under construction
    def detectSyscalls(self):
        while 1:
                _process.singleStep()
                _process.waitSignals(signal.SIGTRAP)
                if _process.readBytes(_process.getregs().rip, 2) == "\x0f\x05":
                    print "SYSCALL DETECTED"
