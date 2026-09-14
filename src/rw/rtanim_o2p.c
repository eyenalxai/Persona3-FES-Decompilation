/* RenderWare Graphics 3.7 block, built with MWCCPS2 3.0.1 b210's optimize-for-
   speed variant (`-O<n>,p`; see config/speed_units.txt).  FUN_00475c20 is
   byte-exact under the speed scheduler but not under the plain `-O2` used by
   src/rw/rtanim.c, so it lives here.  The Persona 4 twin is func_003a3d50. */

#include "temporary.h"

#pragma alias FUN_004c47e0_rwt FUN_004c47e0
extern void FUN_004c47e0_rwt(s32 arg0);
#pragma alias iGpffffba80_s32 iGpffffba80
extern u32 iGpffffba80;
extern s32 iGpffffba80_s32;

/* measured: `-O2,p` alone does not schedule this body; `schedule on` reaches
   retail's instruction order (nd 24 -> 0). */
#pragma schedule on
// FUN_00475C20
void FUN_00475c20(u8 *arg0)
{
    s32 count;
    u8 *base;
    u8 *list;
    u8 *node;

    base = *(u8 **)(arg0 + iGpffffba80_s32);
    if ((*(s32 *)(base + 0x44) & 0x10) == 0) {
        list = *(u8 **)(base + 0x9C);
        count = 0;
        node = list;
        do {
            if (*(s32 *)(node + 0x138) != 0) {
                FUN_004c47e0_rwt(*(s32 *)(node + 0x138));
                *(s32 *)(node + 0x138) = 0;
            }
            node += 4;
        } while ((u32)*(s32 *)(list + 0xE8) >= (u32)++count);
    }
}
