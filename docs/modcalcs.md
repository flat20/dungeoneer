
SlowMultiplicativeResistanceModCalculation.Default__SlowMultiplicativeResistanceModCalculation->CalculateBaseMagnitude(6ed1ccaf30)
RangedDamageModCalculation.Default__RangedDamageModCalculation->CalculateBaseMagnitude(6ed1ccb750)
MeleeModDamageCalculation.Default__MeleeModDamageCalculation->CalculateBaseMagnitude(6ed1ccd8d0)
AddSoulModCalculation.Default__AddSoulModCalculation->CalculateBaseMagnitude(6ed1ccde70)
AddSoulModCalculation.Default__AddSoulModCalculation->CalculateBaseMagnitude(6ed1ccde70)


TArray? Pointer to Data, ArrayNum, ArrayMax
https://forums.unrealengine.com/development-discussion/c-gameplay-programming/107042-how-to-use-uarrayproperty-and-or-fscriptarrayhelper-to-get-the-values-of-an-array-through-reflection
This code says you can get the class from InnerElement, but all I've ever seen is StructProperty
https://answers.unrealengine.com/questions/405610/ue-reflection-how-to-get-type-of-tarray-elements.html

Looks like an array of FNames.

          GameplayTags(ArrayProperty)offset:0,PropertyFlags:20080001000204,ArrayDim:1,ElementSize:10,innerClass:StructProperty,innerEleSize:8,innerFlags:8001000000000,innerCastFlags:41=4,4,214f1b50380
 Array Element 0
0214f1b50380  0000    78 fa 01 00 00 00 00 00   7c fa 01 00 00 00 00 00   =1fa78  =1fa7c - element size is 8, FNames?
 Array Element 1
0214f1b50388  0000    7c fa 01 00 00 00 00 00   05 fb 01 00 00 00 00 00   =1fa7c  =1fb05
 Array Element 2
0214f1b50390  0000    05 fb 01 00 00 00 00 00   14 fb 01 00 00 00 00 00   =1fb05  =1fb14
 Array Element 3
0214f1b50398  0000    14 fb 01 00 00 00 00 00   40 09 80 f6 14 02 00 00   =1fb14  =214f6800940
init values.. how?

          ParentTags(ArrayProperty)offset:10,PropertyFlags:20080000002200,ArrayDim:1,ElementSize:10,innerClass:StructProperty,innerEleSize:8,innerFlags:8001000000000,innerCastFlags:41=5,6,214f7aeda50
 Array Element 0
0214f7aeda50  0000    33 58 00 00 00 00 00 00   c4 fb 01 00 00 00 00 00   =5833  =1fbc4
 Array Element 1
0214f7aeda58  0000    c4 fb 01 00 00 00 00 00   c2 fb 01 00 00 00 00 00   =1fbc4  =1fbc2
 Array Element 2
0214f7aeda60  0000    c2 fb 01 00 00 00 00 00   b7 fb 01 00 00 00 00 00   =1fbc2  =1fbb7
 Array Element 3
0214f7aeda68  0000    b7 fb 01 00 00 00 00 00   c8 fb 01 00 00 00 00 00   =1fbb7  =1fbc8
 Array Element 4
0214f7aeda70  0000    c8 fb 01 00 00 00 00 00   00 00 00 00 00 00 00 00   =1fbc8  =0
init values.. how?

    FString (TArray) in the first 8, most likely.
    RelevantAttributesToCapture(ArrayProperty)offset:28,PropertyFlags:20080000010215,ArrayDim:1,ElementSize:10,innerClass:StructProperty,innerEleSize:28,innerFlags:8000000000000,innerCastFlags:41=6,22,214b088eb00
 Array Element 0
0214b088eb00  0000    20 41 3b ba 14 02 00 00   15 00 00 00 18 00 00 00   =214ba3b4120  =1800000015 - not objects - 2 x 32ints first one always lower
0214b088eb10  0010    40 aa 94 b9 14 02 00 00   00 68 f0 ab 14 02 00 00   =214b994aa40  =214abf06800 - two objects
0214b088eb20  0020    01 00 74 00 79 00 44 00   00 4f cf a9 14 02 00 00   =44007900740001  =214a9cf4f00 - 4 x uint16s?
 Array Element 1
0214b088eb28  0000    00 4f cf a9 14 02 00 00   0e 00 00 00 10 00 00 00   =214a9cf4f00  =100000000e
0214b088eb38  0010    00 35 8c b9 14 02 00 00   00 e6 e6 ab 14 02 00 00   =214b98c3500  =214abe6e600
0214b088eb48  0020    00 01 6f 00 6e 00 00 00   80 18 5e ba 14 02 00 00   =6e006f0100  =214ba5e1880
 Array Element 2
0214b088eb50  0000    80 18 5e ba 14 02 00 00   1f 00 00 00 20 00 00 00   =214ba5e1880  =200000001f
0214b088eb60  0010    30 fb 8c b9 14 02 00 00   00 90 ed ab 14 02 00 00   =214b98cfb30  =214abed9000
0214b088eb70  0020    00 01 6f 00 77 00 73 00   00 17 5e ba 14 02 00 00   =730077006f0100  =214ba5e1700
 Array Element 3
0214b088eb78  0000    00 17 5e ba 14 02 00 00   1c 00 00 00 20 00 00 00   =214ba5e1700  =200000001c
0214b088eb88  0010    e0 0b a0 b9 14 02 00 00   00 bc f1 ab 14 02 00 00   =214b9a00be0  =214abf1bc00
0214b088eb98  0020    00 01 6e 00 69 00 00 00   80 16 5e ba 14 02 00 00   =69006e0100  =214ba5e1680

This is a FGameplayTagQuery
 OwningTagQuery(StructProperty) PropElementSize 72 Offset: 32= FGameplayTagQuery
    TokenStreamVersion(IntProperty) PropElementSize 4 Offset: 0=
    TagDictionary(ArrayProperty) PropElementSize 16 Offset: 8=
    QueryTokenStream(ArrayProperty) PropElementSize 16 Offset: 24=
    UserDescription(StrProperty) PropElementSize 16 Offset: 40=
    AutoDescription(StrProperty) PropElementSize 16 Offset: 56=