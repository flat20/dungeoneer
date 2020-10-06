# bla

offset: 4 = float32. /5 for actual damage.
50h pointers, always different
60h pointers, always different

BP_DamageNumberNotifyStatic_C.OnExecute() params 3
  Param   MyTarget(ObjectProperty)offset:0,PropertyFlags:8001040000294,ArrayDim:1,ElementSize:8,RepIndex:0
  Param Reference Out   Parameters(StructProperty)offset:8,PropertyFlags:8008000196,ArrayDim:1,ElementSize:b8,RepIndex:0
Printing struct props
cpp size: aecd91d8 7ff7 struct size: 998be180 10f
0005e74c9fa8  0000    00 00 00 00 01 00 70 c2   f8 a4 9e ae f7 7f 00 00   =c270000100000000  =7ff7ae9ea4f8
0005e74c9fb8  0010    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
0005e74c9fc8  0020    f3 fa 01 00 00 00 00 00   00 00 00 00 00 00 00 00   =1faf3  =0
0005e74c9fd8  0030    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
0005e74c9fe8  0040    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
0005e74c9ff8  0050    30 33 01 be 0f 01 00 00   01 00 00 00 02 00 00 00   =10fbe013330  =200000001
0005e74ca008  0060    50 ed 01 be 0f 01 00 00   01 00 00 00 02 00 00 00   =10fbe01ed50  =200000001
0005e74ca018  0070    c4 24 81 46 c5 c1 1f 46   9a 50 32 46 00 00 00 00   =461fc1c5468124c4  =4632509a
0005e74ca028  0080    00 00 00 00 00 00 00 00   da e5 05 00 3b 47 00 00   =0  =473b0005e5da
0005e74ca038  0090    ff ff ff ff 00 00 00 00   ff ff ff ff 00 00 00 00   =ffffffff  =ffffffff
0005e74ca048  00a0    ff ff ff ff 00 00 00 00   01 00 00 00 01 00 00 00   =ffffffff  =100000001
0005e74ca058  00b0    ff ff ff ff 00 00 00 00   00 ff ff ff 00 00 00 00   =ffffffff  =ffffff00

0005e74cb8a8  0000    00 00 00 00 ef 56 d1 c2   f8 a4 9e ae f7 7f 00 00   =c2d156ef00000000  =7ff7ae9ea4f8
0005e74cb8b8  0010    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
0005e74cb8c8  0020    f3 fa 01 00 00 00 00 00   00 00 00 00 00 00 00 00   =1faf3  =0
0005e74cb8d8  0030    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
0005e74cb8e8  0040    00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00   =0  =0
0005e74cb8f8  0050    50 c9 01 be 0f 01 00 00   01 00 00 00 02 00 00 00   =10fbe01c950  =200000001
0005e74cb908  0060    a0 cc 01 be 0f 01 00 00   01 00 00 00 02 00 00 00   =10fbe01cca0  =200000001
0005e74cb918  0070    cf 24 81 46 1e c3 1f 46   9a 50 32 46 00 00 00 00   =461fc31e468124cf  =4632509a
0005e74cb928  0080    00 00 00 00 00 00 00 00   da e5 05 00 3b 47 00 00   =0  =473b0005e5da
0005e74cb938  0090    ff ff ff ff 00 00 00 00   ff ff ff ff 00 00 00 00   =ffffffff  =ffffffff
0005e74cb948  00a0    ff ff ff ff 00 00 00 00   01 00 00 00 01 00 00 00   =ffffffff  =100000001
0005e74cb958  00b0    ff ff ff ff 00 00 00 00   00 ff ff ff 00 00 00 00   =ffffffff  =ffffff00



3 pointers? only first one changes. data in that pointer is either broken or very very static.
1 pointer is "Health" a wide string...


BP_AlexCharacter_C.OnCharacterDamageReceivedWithType() params 8c776cdaa8
  Param   Amount(FloatProperty)offset:0=64.545227
  Param  Reference   Type(StructProperty)offset:8struct property.Struct 0
 Array Dim 1
 ElementSize 32
008c776cdab0  0000    30 ad b7 cb fb 01 00 00   07 00 00 00 08 00 00 00        1fbcbb7ad30         800000007
008c776cdac0  0010    f0 a8 8f a1 fb 01 00 00   00 68 ea 93 fb 01 00 00        1fba18fa8f0       1fb93ea6800
00301c0cd480  0000    f0 bf 24 39 8c 01 00 00   07 00 00 00 08 00 00 00   3924bff0   18c     7     8  0.000157118  5.54914e-43  9.80909e-45  1.12104e-44
00301c0cd490  0010    f0 a8 d7 77 8c 01 00 00   00 68 35 6a 8c 01 00 00   77d7a8f0   18c  6a356800   18c  8.74821e+33  5.54914e-43  5.48267e+25  5.54914e-43
pointer? 18c3924bff0
018c3924bff0  0000    48 00 65 00 61 00 6c 00   74 00 68 00 00 00 00 00 = H e a l t h

BP_AlexCharacter_C.OnCharacterDamageReceivedWithType() params 8c776cdaa8
  Param   Amount(FloatProperty)offset:0=64.545227
  Param  Reference   Type(StructProperty)offset:8struct property.Struct 0
 Array Dim 1
 ElementSize 32
008c776cdab0  0000    d0 ed 5c cb fb 01 00 00   07 00 00 00 08 00 00 00        1fbcb5cedd0         800000007
008c776cdac0  0010    f0 a8 8f a1 fb 01 00 00   00 68 ea 93 fb 01 00 00        1fba18fa8f0       1fb93ea6800


SAME session:
BP_IllagerVindicatorVariant1Character_C.OnCharacterDamageReceivedWithType() params 8c776cd328
  Param   Amount(FloatProperty)offset:0=104.669800
  Param  Reference   Type(StructProperty)offset:8struct property.Struct 0
 Array Dim 1
 ElementSize 32
008c776cd330  0000    60 ef 5c cb fb 01 00 00   07 00 00 00 08 00 00 00        1fbcb5cef60         800000007
008c776cd340  0010    f0 a8 8f a1 fb 01 00 00   00 68 ea 93 fb 01 00 00        1fba18fa8f0       1fb93ea6800


BP_IllagerVindicatorVariant1Character_C.OnCharacterDamageReceivedWithType() params 8c776cc978
  Param   Amount(FloatProperty)offset:0=60.000000
  Param  Reference   Type(StructProperty)offset:8struct property.Struct 0
 Array Dim 1
 ElementSize 32
008c776cc980  0000    20 f5 5c cb fb 01 00 00   07 00 00 00 08 00 00 00        1fbcb5cf520         800000007
008c776cc990  0010    f0 a8 8f a1 fb 01 00 00   00 68 ea 93 fb 01 00 00        1fba18fa8f0       1fb93ea6800

BP_AlexCharacter_C.OnCharacterDamageReceivedWithType() params 301c0cd478
  Param   Amount(FloatProperty)offset:0=42.000000
  Param  Reference   Type(StructProperty)offset:8struct property.Struct 0
 Array Dim 1
 ElementSize 32
00301c0cd480  0000    f0 bf 24 39 8c 01 00 00   07 00 00 00 08 00 00 00   3924bff0   18c     7     8  0.000157118  5.54914e-43  9.80909e-45  1.12104e-44
00301c0cd490  0010    f0 a8 d7 77 8c 01 00 00   00 68 35 6a 8c 01 00 00   77d7a8f0   18c  6a356800   18c  8.74821e+33  5.54914e-43  5.48267e+25  5.54914e-43
pointer? 18c3924bff0
018c3924bff0  0000    48 00 65 00 61 00 6c 00   74 00 68 00 00 00 00 00   650048  6c0061  680074     0  9.27549e-39  9.91837e-39  9.55105e-39     0
018c3924c000  0010    08 11 25 3c f7 7f 00 00   00 f7 c0 0b 8c 01 00 00   3c251108  7ff7  bc0f700   18c  0.0100749  4.59051e-41  7.43274e-32  5.54914e-43
018c3924c010  0020    50 c0 24 39 8c 01 00 00   00 00 00 00 00 00 00 00   3924c050   18c     0     0  0.000157119  5.54914e-43     0     0
018c3924c020  0030    80 d1 24 39 8c 01 00 00   00 00 00 00 00 00 00 00   3924d180   18c     0     0  0.000157183  5.54914e-43     0     0
018c3924c030  0040    08 11 25 3c f7 7f 00 00   80 07 f4 88 8c 01 00 00   3c251108  7ff7  88f40780   18c  0.0100749  4.59051e-41  -1.4687e-33  5.54914e-43
018c3924c040  0050    80 db 24 39 8c 01 00 00   00 00 00 00 00 00 00 00   3924db80   18c     0     0  0.00015722  5.54914e-43     0     0
018c3924c050  0060    30 b1 24 39 8c 01 00 00   00 00 00 00 00 00 00 00   3924b130   18c     0     0  0.000157063  5.54914e-43     0     0
018c3924c060  0070    10 7b 24 39 8c 01 00 00   00 00 00 00 00 00 00 00   39247b10   18c     0     0  0.000156861  5.54914e-43     0     0


BP_PlayerController_C.OnAnyPlayerDamaged() params 7eb52cd558
  Param   Damage(FloatProperty)offset:0=17.407568


BP_ZombieBtCharacter_C.OnCharacterDeath() params 0

UObject hook

KillTrackerComponent.HandleMobKill() params 36faacbd60
  Param   Item(ObjectProperty)offset:0flags:4018001 UObjectProperty UObjectPropertyBase=BP_BowArrow_C
  Param   Player(ObjectProperty)offset:8flags:4018001 UObjectProperty UObjectPropertyBase=BP_AlexCharacter_C
  Param   mob(ObjectProperty)offset:10flags:4018001 UObjectProperty UObjectPropertyBase=BP_ZombieBtCharacter_C

  
Interested to see what the return value is if we first call processevent.
MeleeModDamageCalculation.CalculateBaseMagnitude() params 2
  Param  Reference   Spec(StructProperty)offset:0,property.Struct:0,,ArrayDim:1,ElementSize:664
  Param  Return   ReturnValue(FloatProperty)offset:298=0.000000

Tried it and it does return the damage.
MeleeModDamageCalculation.CalculateBaseMagnitude() params 2
  Param  Reference   Spec(StructProperty)offset:0,property.Struct:0,ArrayDim:1,ElementSize:664
  Param  Return   ReturnValue(FloatProperty)offset:298=-104.669792

An arrow

RangedDamageModCalculation.CalculateBaseMagnitude() params 2
  Param  Reference   Spec(StructProperty)offset:0,property.Struct:0,ArrayDim:1,ElementSize:664
  Param  Return   ReturnValue(FloatProperty)offset:298=-60.000004

Gets rounded afterwards.

BP_DamageNumberNotifyStatic_C.OnExecute() params 36faacaec0
  Param   MyTarget(ObjectProperty)offset:0flags:4018001 UObjectProperty UObjectPropertyBase=BP_ZombieBtCharacter_C
  Param  Reference   Parameters(StructProperty)offset:8struct property.Struct 20004861d00
    CallFunc_BreakGameplayCueParameters_MatchedTagName(StructProperty)offset:e8
    CallFunc_BreakGameplayCueParameters_OriginalTag(StructProperty)offset:f0
    CallFunc_BreakGameplayCueParameters_AggregatedSourceTags(StructProperty)offset:f8
    CallFunc_BreakGameplayCueParameters_AggregatedTargetTags(StructProperty)offset:118
    CallFunc_BreakGameplayCueParameters_Location(StructProperty)offset:138
    CallFunc_BreakGameplayCueParameters_Normal(StructProperty)offset:144
    CallFunc_BreakGameplayCueParameters_Instigator(ObjectProperty)offset:150
    CallFunc_BreakGameplayCueParameters_EffectCauser(ObjectProperty)offset:158
    CallFunc_BreakGameplayCueParameters_SourceObject(ObjectProperty)offset:160
    CallFunc_BreakGameplayCueParameters_PhysicalMaterial(ObjectProperty)offset:168
    CallFunc_BreakGameplayCueParameters_GameplayEffectLevel(IntProperty)offset:170
    CallFunc_BreakGameplayCueParameters_AbilityLevel(IntProperty)offset:174
    CallFunc_BreakGameplayCueParameters_TargetAttachComponent(ObjectProperty)offset:178
    CallFunc_OnExecute_ReturnValue(BoolProperty)offset:180
    CallFunc_EqualEqual_ObjectObject_ReturnValue(BoolProperty)offset:181
    CallFunc_Not_PreBool_ReturnValue(BoolProperty)offset:182
    K2Node_DynamicCast_AsPlayer_Character(ObjectProperty)offset:188
    K2Node_DynamicCast_bSuccess(BoolProperty)offset:190
    CallFunc_IsLocallyControlled_ReturnValue(BoolProperty)offset:191
    CallFunc_GetController_ReturnValue(ObjectProperty)offset:198
    K2Node_DynamicCast_AsBP_Player_Controller(ObjectProperty)offset:1a0
    K2Node_DynamicCast_bSuccess1(BoolProperty)offset:1a8
    CallFunc_Abs_ReturnValue(FloatProperty)offset:1ac
    K2Node_DynamicCast_AsBP_Mob_Character(ObjectProperty)offset:1b0
    K2Node_DynamicCast_bSuccess2(BoolProperty)offset:1b8
    CallFunc_K2_GetActorLocation_ReturnValue(StructProperty)offset:1bc
    CallFunc_GetActorDamageNumberEmitPosition_EmitPosition(StructProperty)offset:1c8

  Param  Return   ReturnValue(BoolProperty)offset:c0=false
  