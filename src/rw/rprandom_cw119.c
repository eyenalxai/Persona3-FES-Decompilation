/* RenderWare Graphics 3.7 block, built with MWCCPS2 3.0.1 b119 (see
   config/compiler_units.txt).  Retail linked the RenderWare library as a
   prebuilt object; the Persona 4 tree carries matched source bodies of the
   same build, so functions whose b210 spelling cannot reach retail land here.
   Bodies keep the Persona 3 symbols and raw struct offsets; the comment above
   each names the Persona 4 twin they were ported from. */

#include "rw/rprandom.h"

/* P4: src/promoted/code1_003b_cw119.c func_003b6da0 (RenderWare 3.7 block).
   P4 state: unit default (-O4,p, schedule on), opt_propagation off.
   Measured on the P4
   twin: the head store must go through the D_0095D410 symbol, not the base
   local (a base-local store measures 45 words off). */
extern RwUInt32 D_0095D410[];
#pragma alias D_0095D410_abs D_0095D410
extern u8 D_0095D410_abs[];
extern RwUInt32 uGpffffaed4;

#pragma schedule on
#pragma opt_propagation off
// FUN_00488C70
void RpRandomSeedMT(RwUInt32 seed)
{
    RwUInt8* base;
    RwInt32 value;
    RwInt32* ptr;
    RwInt32 factor;
    RwInt32 count;

    base = D_0095D410_abs;
    value = seed | 1;
    uGpffffaed4 = 0;
    ptr = (RwInt32*)(base + 4);
    count = 0x270;
    count = count - 1;
    *(RwInt32*)D_0095D410_abs = value;
    if (count == 0)
    {
        goto done;
    }
    factor = 0x10DCD;
    do
    {
        value = value * factor;
        count = count - 1;
        *ptr = value;
        ptr++;
    } while (count != 0);
done:
    return;
}

/* P4: src/promoted/code1_003b_cw119.c func_003b7860 (RenderWare 3.7 block).
   Lazy one-time init with a call counter.  P4's absolute-addressed arrays
   (D_008864xx) become the P3 DAT_0095dexx spellings in array form so the
   compiler emits lui/lw rather than gp-relative; the two uGpffff globals stay
   gp-relative.  P4 state: unit default (-O4,p, schedule on), opt_propagation on. */
extern u32 DAT_0095de30[];
extern u32 DAT_0095de28[];
extern u32 DAT_0095de20[];
extern u32 DAT_0095de1c[];
extern u32 uGpffffaed8;
extern u32 uGpffffaedc;
extern u32 DAT_00960178[];
extern u8 DAT_0095dde0[];
extern s32 FUN_004ca550(s32 param_1);
extern u32 FUN_0048abf0(u32 param_1);
extern s32 FUN_004c3b60(s32 a, s32 b, s32 c, s32 d, void *e, s32 f);
extern void FUN_00521408(void *dst, s32 value, u32 size);

#pragma schedule on
#pragma opt_propagation on
// FUN_00489730
s32 FUN_00489730(s32 param_1)
{
  s32 flags;

  if (DAT_0095de30[0] != 0) {
    goto increment;
  }
  flags = 1;
  if (FUN_004ca550(0x120) != -1) {
    flags |= 2;
  }
  if (FUN_004ca550(0x12e) != -1) {
    flags |= 4;
  }
  FUN_0048abf0(flags);
  DAT_0095de28[0] = FUN_004c3b60(0x48, uGpffffaed8, 4, uGpffffaedc,
                                 DAT_0095dde0, 0x40116);
  DAT_0095de20[0] = ((s32 (*)(s32, s32))DAT_00960178[0])(0x400f, 0x40116);
  FUN_00521408((void *)DAT_0095de20[0], 0, 0x400f);
  DAT_0095de1c[0] = (s32)(DAT_0095de20[0] + 0xf) & ~0xf;
increment:
  DAT_0095de30[0] += 1;
  return param_1;
}
