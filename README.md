# eqCheck

```assembly
                                                                           0: ld   a5,-24(s0)  

{s0, Mem}                 <=  | Mem[-24(s0)] = a0              |  =>       {a0, Mem}
                              | -24(s0) != Mem[-24(s0)]        |           


1: ld   a5,-24(s0)                                                         1: ld   a5,0(a0)
2: ld   a4,0(a5)                                                           2: slli a5,a5,1
3: addi a5,zero,0x1                                                        3: sd   a5,0(a0)
4: mul  a4,a4,a5                          ?==?                             4: ld   a0,8(a0)
5: ld   a5,-24(s0)                                                         5: sd   a5,-24(s0)
6: sd   a4,0(a5)                                                           
7: ld   a5,-24(s0)    
8: ld   a5,8(a5)    
9: sd   a5,-24(s0)    


{-, Mem'}                <=  | Mem'[0(a5)]    = Mem''[0(a0)]   |  =>       {-, Mem''}
                             | Mem'[-24(s0)] != Mem''[-24(s0)] |
```