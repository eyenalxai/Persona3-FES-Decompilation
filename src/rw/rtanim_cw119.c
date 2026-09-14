/* RenderWare Graphics 3.7 block, built with MWCCPS2 3.0.1 b119 (see
   config/compiler_units.txt).  Retail linked the RenderWare library as a
   prebuilt object; the Persona 4 tree carries matched source bodies of the
   same build, so functions whose b210 spelling cannot reach retail land here.
   Bodies keep the Persona 3 symbols and raw struct offsets; the comment above
   each names the Persona 4 twin they were ported from. */

#include "temporary.h"

/* P4: src/promoted/code1_0039_cw119.c func_0039a8a0 (RenderWare 3.7 block).
   `x ? 0x58 : 0x8000000068` is the b119 movz for the 64-bit flag word.  P4
   state: unit default (-O4,p, schedule on). */
extern u32 iGpffffba48;

#pragma schedule on
// FUN_00469B50
void FUN_00469b50(s32 param_1)
{
  u8 *obj = *(u8 **)(param_1 + iGpffffba48);

  if (*(s32 *)(obj + 0x80) == 3) {
    *(s64 *)(obj + 0x68) = *(s32 *)(obj + 0x4c) ? 0x58 : 0x8000000068LL;
  }
  else {
    *(s64 *)(obj + 0x28) = *(s32 *)(obj + 0xc) ? 0x58 : 0x8000000068LL;
  }
}

/* P4: src/promoted/code1_0039_cw119.c func_0039f050.  Virtual dispatch:
   the index (state + 0x80) selects a function from the PTR_FUN_006b4ee4
   table; the entry is called with three arguments.  The explicit `obj` local
   keeps arg0 below temp_17 in saved-register order.  P4 state: unit default
   (-O4,p, schedule on), no_branch_likely on, opt_propagation off. */
extern u32 PTR_FUN_006b4ee4;
#pragma alias PTR_FUN_006b4ee4_abs PTR_FUN_006b4ee4
extern u8 PTR_FUN_006b4ee4_abs[];

#pragma schedule on
#pragma no_branch_likely on
#pragma opt_propagation off
// FUN_0046EA80
void FUN_0046ea80(u8 *param_1)
{
  s32 temp_17;
  u8 *obj;
  s32 temp_5;
  s32 var_2;
  u8 *temp_2;
  u8 *temp_6;
  s32 (*func)(u8 *, s32, u8 *);

  temp_2 = *(u8 **)(*(s32 *)(*(u8 **)(param_1 + 0x2c) + 8) + iGpffffba48);
  if (temp_2 != NULL) {
    var_2 = *(s32 *)(temp_2 + 0x80);
  }
  else {
    var_2 = 0;
  }
  obj = param_1;
  temp_6 = *(u8 **)(obj + 4);
  temp_5 = var_2 * 0x10;
  temp_17 = *(s32 *)(temp_6 + 0x18);
  *(s32 *)(temp_6 + 0x18) = temp_17 + temp_5;
  func = (s32 (*)(u8 *, s32, u8 *))*(void **)((u8 *)PTR_FUN_006b4ee4_abs + (var_2 * 4));
  func(obj, temp_5, temp_6);
  *(s32 *)(*(u8 **)(obj + 4) + 0x18) = temp_17;
}

/* P4: src/promoted/code1_003a_cw119.c func_003a3de0.  Walk a 0x20-byte
   stride list while the count stays at or below the end field.  P4 calls
   func_003f32d0 directly; P3's twin is FUN_004d4df0.  P4 state: unit default
   (-O4,p, schedule on). */
extern u32 DAT_007ce770;
extern void FUN_004d4df0(void);

#pragma schedule on
// FUN_00475CB0
void FUN_00475cb0(u8 *param_1)
{
  u32 count;
  u8 *base;
  u8 *list;
  u8 *node;

  base = *(u8 **)(param_1 + DAT_007ce770);
  if ((*(s32 *)(base + 0x44) & 0x10) == 0) {
    list = *(u8 **)(base + 0x9c);
    if (*(s32 *)(list + 0xd8) != 0) {
      count = 0;
      node = list;
      do {
        if (*(s32 *)(node + 0x10) != 0) {
          FUN_004d4df0();
          FUN_004d4df0();
        }
        count++;
        node += 0x20;
      } while ((u32)*(s32 *)(list + 0xe8) >= count);
    }
  }
}

/* P4: src/promoted/code1_003b_cw119.c func_003bb4a0 (RenderWare 3.7 block).
   P4 callees map to P3 FUN_004c1d10 (_rwerror), FUN_004c1c50 (RwErrorSet) and
   FUN_0048b910; the error string D_0070AF50 is D_0077DCC0 in the P3 split
   assembly.  P4 state: unit default (-O4,p, schedule on), no_branch_likely
   off, opt_propagation off. */
extern s32 FUN_0048b910(u8 *param_1, u8 *param_2);
extern s32 FUN_004c1d10(s32 param_1, ...);
extern void FUN_004c1c50(s32 *param_1);
extern u8 D_0077DCC0[];

#pragma schedule on
#pragma no_branch_likely off
#pragma opt_propagation off
// FUN_0048D370
u8 *FUN_0048d370(u8 *param_1, s32 param_2, f32 *param_3)
{
  s32 err[2];
  s32 pair[2];
  s32 temp_3;
  s32 count;
  u8 *temp_2;
  f32 f2;
  f32 f1;
  f32 f0;

  if (param_2 < 0) {
    goto block_9;
  }
  temp_3 = *(s32 *)(param_1 + 0xc);
  switch (temp_3) {
  case 1:
    count = *(s32 *)(param_1 + 8) - 2;
    break;
  case 2:
    count = *(s32 *)(param_1 + 8) - 3;
    break;
  default:
    pair[0] = 0x102;
    pair[1] = FUN_004c1d10(1);
    FUN_004c1c50(pair);
    count = 0;
    break;
  }
  if (param_2 < count) {
    temp_2 = *(u8 **)(param_1 + 0x14) + param_2 * 0xc;
    f2 = param_3[0];
    f1 = param_3[1];
    f0 = param_3[2];
    *(f32 *)(temp_2 + 0) = f2;
    *(f32 *)(temp_2 + 4) = f1;
    *(f32 *)(temp_2 + 8) = f0;
    return FUN_0048b910(param_1, *(u8 **)(param_1 + 0x14)) ? param_1 : NULL;
  }
block_9:
  err[0] = 0x102;
  err[1] = FUN_004c1d10(0x80000003, D_0077DCC0);
  FUN_004c1c50(err);
  return NULL;
}
