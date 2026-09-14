/* RenderWare Graphics 3.7 block, built with MWCCPS2 3.0.1 b119 (see
   config/compiler_units.txt).  Retail linked the RenderWare library as a
   prebuilt object; the Persona 4 tree carries matched source bodies of the
   same build, so functions whose b210 spelling cannot reach retail land here.
   Bodies keep the Persona 3 symbols and raw struct offsets; the comment above
   each names the Persona 4 twin they were ported from. */

#include "mw_harvest_compat.h"
#include "rw/rwplcore.h"

/* P4: src/promoted/code1_003d_cw119.c func_003d59a0 (RenderWare 3.7 block).
   P4 state: unit default (-O4,p, schedule on), no_branch_likely off.  P4
   calls memcpy (P4 func_0043f810); P3's twin is FUN_00521250 == memcpy. */
#pragma schedule on
#pragma no_branch_likely off
// FUN_004B7020
s32 FUN_004b7020(u8 *param_1, u8 *param_2)
{
  memcpy(param_1 + 0x4c, param_2 + 0x4c,
         *(s32 *)(param_1 + 0x24) * *(s32 *)(param_1 + 0x2c));
  return 1;
}

/* P4: src/promoted/code1_003d_cw119.c func_003d5790 (RenderWare 3.7 block).
   Allocation through the first entry of the P3 memory-function table; the
   P4 twin calls jtbl_008873E8[0] and keeps the 19 field stores in source
   order.  P4 state: unit default (-O4,p, schedule on), no_branch_likely off. */
extern code DAT_00960178;
#pragma alias DAT_00960178_abs DAT_00960178
extern code DAT_00960178_abs[];

#pragma schedule on
#pragma no_branch_likely off
// FUN_004B6E10
u8 *FUN_004b6e10(s32 param_1, s32 param_2)
{
  u8 *temp_2;
  s32 size;

  size = param_1 * param_2;
  temp_2 = (u8 *)(*DAT_00960178_abs)(size + 0x4c, 0x3001b);
  *(s32 *)(temp_2 + 0x2c) = param_1;
  *(s32 *)(temp_2 + 0x0) = 0;
  *(s32 *)(temp_2 + 0x8) = 0;
  *(s32 *)(temp_2 + 0x4) = 0;
  *(s32 *)(temp_2 + 0xc) = 0;
  *(s32 *)(temp_2 + 0x14) = 0xbf800000;
  *(s32 *)(temp_2 + 0x10) = 0;
  *(s32 *)(temp_2 + 0x18) = 0;
  *(s32 *)(temp_2 + 0x1c) = 0;
  *(s32 *)(temp_2 + 0x24) = param_2;
  *(s32 *)(temp_2 + 0x28) = -1;
  *(s32 *)(temp_2 + 0x20) = param_2;
  *(s32 *)(temp_2 + 0x30) = 0;
  *(s32 *)(temp_2 + 0x34) = 0;
  *(s32 *)(temp_2 + 0x38) = (s32)temp_2;
  *(s32 *)(temp_2 + 0x3c) = 0;
  *(s32 *)(temp_2 + 0x44) = 0;
  *(s32 *)(temp_2 + 0x40) = 0;
  *(s32 *)(temp_2 + 0x48) = 0;
  return temp_2;
}

/* P4: src/promoted/code1_003d_cw119.c func_003d5e90 (RenderWare 3.7 block).
   Per-index callback over three rasters; the callback pointer sits at +0x40
   and takes three raster pointers plus an f32.  P4 state: unit default
   (-O4,p, schedule on), no_branch_likely off. */
#pragma schedule on
#pragma no_branch_likely off
// FUN_004B7510
s32 FUN_004b7510(u8 *param_1, u8 *param_2, u8 *param_3, f32 param_4)
{
  s32 index;
  s32 has_items;
  s32 count;

  index = 0;
  count = *(s32 *)(param_1 + 0x2c);
  has_items = (0 < count);
  if (has_items == 0) {
    goto done;
  }
  do {
    s32 off0;
    s32 off1;
    s32 off2;
    u8 *p0;
    u8 *p1;
    u8 *p2;

    off0 = index * *(s32 *)(param_1 + 0x24);
    p0 = (u8 *)(off0 + (s32)param_1);
    off1 = index * *(s32 *)(param_2 + 0x24);
    p1 = (u8 *)(off1 + (s32)param_2);
    off2 = index * *(s32 *)(param_3 + 0x24);
    p2 = (u8 *)(off2 + (s32)param_3);
    ((void (*)(u8 *, u8 *, u8 *, f32))(*(u32 *)(param_1 + 0x40)))(
        p0 + 0x4c,
        p1 + 0x4c,
        p2 + 0x4c,
        param_4);
    index += 1;
  } while (*(s32 *)(param_1 + 0x2c) > index);
done:
  return 1;
}

/* P4: src/promoted/code1_003d_cw119.c func_003db490 (RenderWare 3.7 block).
   P4 callees map to P3 FUN_0049a870, FUN_004bcae0 (address taken),
   FUN_0052ea30 (the f32 sqrt) and FUN_004d8320.  P4 state: unit default
   (-O4,p, schedule on), no_branch_likely off. */
extern s32 FUN_004bcae0(u8 *param_1, s32 param_2);
extern u8 *FUN_0049a870(u8 *param_1, s32 (*param_2)(u8 *, s32), s32 param_3);
extern f32 FUN_0052ea30(f32 param_1);
extern s32 *FUN_004d8320(s32 *param_1, f32 param_2);

#pragma schedule on
#pragma no_branch_likely off
// FUN_004BCB30
s32 FUN_004bcb30(s32 param_1, u8 *param_2)
{
  f32 value;
  s32 count;

  *(s32 *)(param_2 + 8) = param_1;
  *(s32 *)(param_2 + 0xc) = 0;
  *(s32 *)(param_2 + 0x10) = 0;
  FUN_0049a870(*(u8 **)(param_2 + 4),
               (s32 (*)(u8 *, s32))FUN_004bcae0, (s32)param_2);
  count = *(s32 *)(param_2 + 0x10);
  if (count > 0) {
    value = FUN_0052ea30(*(f32 *)(param_2 + 0xc) / (f32)count);
    FUN_004d8320((s32 *)param_1, -(value / FUN_0052ea30(2.0f)));
  }
  return param_1;
}
