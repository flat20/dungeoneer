    7ff69ab4aae1 e8 96 d6        CALL       _Init_thread_header                              undefined _Init_thread_header()
                 47 02
    7ff69ab4aae6 83 3d 3b        CMP        dword ptr [DAT_7ff69e25c328],-0x1                = 20h     
                 18 71 03 ff
    7ff69ab4aaed 0f 85 05        JNZ        LAB_7ff69ab4a9f8
                 ff ff ff
    7ff69ab4aaf3 e8 28 1a        CALL       FUN_7ff69affc520                                 undefined FUN_7ff69affc520()
                 4b 00
    7ff69ab4aaf8 48 8b d8        MOV        RBX,RAX
    7ff69ab4aafb 41 b8 01        MOV        R8D,0x1
                 00 00 00
    7ff69ab4ab01 48 8d 15        LEA        RDX,[u_MeleeHealItemPowerFactor_7ff69d1e9e28]    = u"MeleeHealItemPowerFactor"
                 20 f3 69 02
    7ff69ab4ab08 48 8d 4c        LEA        RCX=>local_res10,[RSP + 0x78]
                 24 78
    7ff69ab4ab0d e8 1e 05        CALL       FUN_7ff69b14b030                                 undefined FUN_7ff69b14b030()
                 60 00
    7ff69ab4ab12 48 8b 10        MOV        RDX,qword ptr [RAX]
    7ff69ab4ab15 48 8b cb        MOV        RCX,RBX
    7ff69ab4ab18 e8 23 9a        CALL       FUN_7ff69a764540                                 undefined FUN_7ff69a764540()
                 c1 ff
    7ff69ab4ab1d 48 8b d0        MOV        RDX,RAX
    7ff69ab4ab20 48 8d 0d        LEA        RCX,[DAT_7ff69e25c308]                           = 000001BD4E4468A0h
                 e1 17 71 03
    7ff69ab4ab27 e8 44 4e        CALL       FUN_7ff69a7af970                                 undefined FUN_7ff69a7af970()
                 c6 ff
    7ff69ab4ab2c 48 8d 0d        LEA        RCX,[FUN_7ff69d0822e0]
                 ad 77 53 02
    7ff69ab4ab33 e8 14 d4        CALL       atexit                                           int atexit(void * param_1)
                 47 02
    7ff69ab4ab38 90              NOP
    7ff69ab4ab39 48 8d 0d        LEA        RCX,[DAT_7ff69e25c328]                           = 20h     
                 e8 17 71 03
    7ff69ab4ab40 e8 d7 d5        CALL       FUN_7ff69cfc811c                                 undefined FUN_7ff69cfc811c()
                 47 02
    7ff69ab4ab45 e9 ae fe        JMP        LAB_7ff69ab4a9f8
                 ff ff

// creates the event rdx = string name, rcx = 
undefined8 * FUN_7ff69b14b030(undefined8 *param_1,longlong param_2,uint param_3)

{
  if (param_2 != 0) {
    FUN_7ff69b1555b0(param_1,param_2,0,(ulonglong)param_3,1,0xffffffff);
    return param_1;
  }
  *param_1 = 0;
  return param_1;
}
