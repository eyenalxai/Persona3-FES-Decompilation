#include "temporary.h"

typedef int (*code)(...);

/* RenderWare Graphics 3.7 block, built with MWCCPS2 3.0.1 b119 (see
   config/compiler_units.txt).  Retail linked the RenderWare library as a
   prebuilt object; the Persona 4 tree carries the matched source bodies of the
   same build, so functions whose b210 spelling cannot reach retail land here.
   Bodies are ported from the Persona 4 twin named in each comment, with the
   Persona 3 names and raw struct offsets. */

/* P4: src/renderware/world/baclump.c RpClumpAddAtomic (func_003c0850).
   rwLinkListAddLLLink(&clump->atomicList, &atomic->inClumpLink) expands to the
   four link stores; the macro re-reads the list head between the stores, which
   is why the load appears twice.  P4 state: level 2, schedule on.
   ClumpAtomicCloneAndAttach (ported below) calls this from the same P4 file but
   from a point above this definition, so retail's call is a direct jal that is
   never inlined; dont_inline reproduces that here. */
#pragma optimization_level 2
#pragma schedule on
#pragma dont_inline on
// FUN_00491FF0
void *FUN_00491ff0(void *param_1, void *param_2)
{
  u8 *clump = (u8 *)param_1;
  u8 *atomic = (u8 *)param_2;

  *(u32 *)(atomic + 0x40) = *(u32 *)(clump + 8);
  *(u32 *)(atomic + 0x44) = (u32)(clump + 8);
  *(u32 *)(*(u32 *)(clump + 8) + 4) = (u32)(atomic + 0x40);
  *(u32 *)(clump + 8) = (u32)(atomic + 0x40);
  *(u32 *)(atomic + 0x3c) = (u32)clump;
  return param_1;
}
#pragma dont_inline off

/* P4: src/promoted/code1_003b_cw119.c func_003bfe90.  Clump child traversal
   with a per-child callback; the `result = result;` and the double
   `current == sentinel` test are the measured spelling that reproduces
   retail's branch layout.  P4 state: level 2, schedule on, no_branch_likely
   on. */
extern s32 FUN_004cb2f0(s32 arg0);

#pragma optimization_level 2
#pragma schedule on
#pragma no_branch_likely on
// FUN_00491630
u8 *FUN_00491630(u8 *param_1)
{
  s32 (*callback)(u8 *);
  u8 *result;
  u8 *current;
  u8 *entry;
  u8 *sentinel;

  sentinel = param_1 + 8;
  current = *(u8 **)sentinel;
  result = param_1;
  if (current == sentinel)
    goto empty;
loop:
  entry = current - 0x40;
  if ((*(u8 *)(current - 0x3E) & 4) != 0)
    goto callback_block;
advance:
  current = *(u8 **)current;
  if (current != sentinel)
    goto loop;
  if (current == sentinel)
    goto empty;
  result = result;
empty:
  goto done;
done:
  return result;
callback_block:
  FUN_004cb2f0(*(s32 *)(entry + 4));
  callback = *(s32 (**)(u8 *))(entry + 0x48);
  if (callback(entry) != 0)
    goto advance;
  result = 0;
  goto advance;
}

/* P4: src/promoted/code1_003b_cw119.c func_003bff30.  Same traversal with the
   callback as a parameter.  P4 state: level 2, schedule on, no_branch_likely
   on. */
#pragma optimization_level 2
#pragma schedule on
#pragma no_branch_likely on
// FUN_004916D0
void *FUN_004916d0(void *param_1, s32 (*param_2)(void *, void *), void *param_3)
{
  u8 *current;
  u8 *sentinel;
  u8 *next;

  sentinel = (u8 *)param_1 + 8;
  current = *(u8 **)((u8 *)param_1 + 8);
  if (current == sentinel)
    goto done;
loop:
  next = *(u8 **)current;
  if (param_2((void *)(current - 0x40), param_3) == 0)
    return param_1;
  current = next;
  if (current != sentinel)
    goto loop;
done:
  return param_1;
}

/* P4: src/promoted/code1_003b_cw119.c func_003bffc0.  Traversal over the
   second list head at +0x18, with the callback's first argument biased by the
   module-globals offset.  P4 state: level 2, schedule on, no_branch_likely
   on. */
extern u32 iGpffffbb20;

#pragma optimization_level 2
#pragma schedule on
#pragma no_branch_likely on
// FUN_00491760
s32 FUN_00491760(u8 *param_1, s32 (*param_2)(s32, s32 *), s32 *param_3)
{
  u8 *current;
  u8 *sentinel;
  u8 *next;

  sentinel = param_1 + 0x18;
  current = *(u8 **)sentinel;
  if (current == sentinel)
    goto done;
loop:
  next = *(u8 **)current;
  if (param_2((s32)(current - 4) - iGpffffbb20, param_3) == 0)
    return (s32)param_1;
  current = next;
  if (current != sentinel)
    goto loop;
done:
  return (s32)param_1;
}

/* P4: src/renderware/world/baworld.c WorldFindSector (func_003c8da0).  P4
   state: level 2, schedule on. */
#pragma optimization_level 2
#pragma schedule on
// FUN_004992F0
void *FUN_004992f0(void *param_1, void *param_2)
{
  if (*(void **)param_2 == param_1) {
    *(u32 *)((u8 *)param_2 + 4) = 1;
    return 0;
  }
  return param_1;
}

/* P4: src/renderware/world/baworld.c RpWorldSetSectorRenderCallBack
   (func_003c9e80).  P4 state: level 2, schedule on. */
extern u64 FUN_00499b90(u64 param_1);

#pragma optimization_level 2
#pragma schedule on
// FUN_0049A3D0
void *FUN_0049a3d0(void *param_1, code *param_2)
{
  if (param_2 == 0) {
    param_2 = (code *)FUN_00499b90;
  }
  *(code **)((u8 *)param_1 + 0x68) = param_2;
  return param_1;
}

/* P4: src/renderware/world/baworobj.c sizeSectorMesh (func_003cb8d0).
   P4 state: level 2, schedule on. */
extern u8 *FUN_0049a170(u32 arg0);
extern s32 FUN_004964f0(s32 param_1, u8 *param_2);

#pragma optimization_level 2
#pragma schedule on
// FUN_0049BE20
s32 FUN_0049be20(u8 *param_1)
{
  u8 *world;

  world = FUN_0049a170((u32)param_1);
  return FUN_004964f0(*(u32 *)(param_1 + 0x78), world);
}

/* P4: src/renderware/world/bamatlst.c _rpMaterialListFindMaterialIndex
   (func_003c4bc0).  P4 state: -O4 default, schedule on.  The earlier entries
   in this file select level 2, so the level has to be reset here.  P4 kept
   this function in bamatlst.c, so bageomet.c's calls are direct and never
   inlined; dont_inline keeps that shape for FUN_00493230 below. */
typedef struct RpMatList119 { u32 **materials; s32 numMaterials; } RpMatList119;

#pragma optimization_level 4
#pragma schedule on
#pragma dont_inline on
// FUN_00495480
s32 FUN_00495480(const RpMatList119 *matList, const u32 *material)
{
  s32 numMats;

  numMats = matList->numMaterials;
  while (numMats-- > 0) {
    if (matList->materials[numMats] == material) {
      break;
    }
  }
  return numMats;
}
#pragma dont_inline off

/* P4: src/renderware/world/baclump.c AtomicSync (func_003be9a0).  P4 state:
   schedule on only. */
extern void FUN_00491100(void *param_1);

#pragma schedule on
// FUN_00490810
void *FUN_00490810(void *param_1)
{
  if ((*(u32 *)((u8 *)param_1 + 0x4c) & 2) != 0) {
    FUN_00491100(param_1);
  }
  *(u8 *)((u8 *)param_1 + 3) = (u8)(*(u8 *)((u8 *)param_1 + 3) | 1);
  return param_1;
}

/* P4: src/renderware/world/bamesh.c _rpMeshClose (func_003c54c0).  P4 state:
   level 2, schedule on. */
extern u32 DAT_007ce848;
extern u32 DAT_007ce854;
extern void FUN_004c3c30(u32 param_1);

#pragma optimization_level 2
#pragma schedule on
// FUN_004959E0
void *FUN_004959e0(void *param_1)
{
  DAT_007ce854 = DAT_007ce854 - 1;
  if (DAT_007ce854 == 0) {
    if (DAT_007ce848 != 0) {
      FUN_004c3c30(DAT_007ce848);
      DAT_007ce848 = 0;
    }
  }
  return param_1;
}

/* P4: src/renderware/world/baworobj.c WorldCopyCameraExt (func_003ca890).
   P4 state: schedule on only. */
extern u32 iGpffffbb78;
extern void *FUN_0049c160(void *param_1, void *param_2);

#pragma schedule on
// FUN_0049ADE0
void *FUN_0049ade0(void *param_1, void *param_2)
{
  u8 *dstCameraExt;
  u8 *srcCameraExt;
  void *world;

  dstCameraExt = (u8 *)param_1 + iGpffffbb78;
  srcCameraExt = (u8 *)param_2 + iGpffffbb78;
  world = *(void **)(srcCameraExt + 0xc);
  *(u32 *)dstCameraExt = 0;
  *(u32 *)(dstCameraExt + 4) = 0;
  *(u32 *)(dstCameraExt + 8) = 0;
  if (world != 0) {
    FUN_0049c160(world, param_1);
  }
  return param_1;
}

/* P4: src/renderware/world/baworobj.c readGeometryMesh (func_003cb720).
   P4 state: -O4 default, schedule on. */
extern void *FUN_00496230(void *stream, void *object, void *matList);

#pragma optimization_level 4
#pragma schedule on
// FUN_0049BC70
void *FUN_0049bc70(void *param_1, void *param_2, u8 *param_3)
{
  *(void **)(param_3 + 0x54) = FUN_00496230(param_1, param_3, param_3 + 0x20);
  if (*(void **)(param_3 + 0x54) != 0) {
    return param_1;
  }
  return 0;
}

/* P4: src/renderware/world/baworobj.c writeSectorMesh (func_003cb820).
   P4 state: -O4 default, schedule on.
   RpMeshHeader119/RpMesh119 are the P3 spellings of RpMeshHeader/RpMesh;
   FUN_00495fb0 (_rpMeshWrite) below is defined with the typed const
   parameters, which is what reproduces retail's schedule. */
typedef struct RpMeshHeader119 RpMeshHeader119;
struct RpMeshHeader119 {
  u32 flags;
  u16 numMeshes;
  u16 serialNum;
  u32 totalIndicesInMesh;
  u32 firstMeshOffset;
};
typedef struct RpMesh119 RpMesh119;
struct RpMesh119 {
  u16 *indices;
  u32 numIndices;
  void *material;
};
extern void *FUN_00495fb0(const RpMeshHeader119 *meshHeader, const void *object, void *stream, const RpMatList119 *matList);

#pragma optimization_level 4
#pragma schedule on
// FUN_0049BD70
void *FUN_0049bd70(void *param_1, void *param_2, u8 *param_3)
{
  u8 *world;

  world = FUN_0049a170((u32)param_3);
  return FUN_00495fb0(*(void **)(param_3 + 0x78), world, param_1, (const RpMatList119 *)(world + 0x10));
}

/* P4: src/renderware/world/baworobj.c RpWorldAddCamera (func_003cbc10).
   P4 state: -O4 default, schedule on. */
extern void FUN_004cb270(void *frame);

#pragma optimization_level 4
#pragma schedule on
// FUN_0049C160
void *FUN_0049c160(void *param_1, void *param_2)
{
  u8 *cameraExt;
  void *frame;

  cameraExt = (u8 *)param_2 + iGpffffbb78;
  frame = *(void **)((u8 *)param_2 + 4);
  if (frame != 0) {
    FUN_004cb270(frame);
  }
  *(u32 *)(cameraExt + 0xc) = (u32)param_1;
  return param_1;
}

/* P4: src/renderware/world/bamateri.c RpMaterialSetTexture (func_003c42b0).
   P4 state: -O4 default, schedule on. */
extern void FUN_004d0f00(void *texture);

#pragma optimization_level 4
#pragma schedule on
// FUN_00494D50
void *FUN_00494d50(void *param_1, u8 *param_2)
{
  if (param_2 != 0) {
    *(s32 *)(param_2 + 0x54) = *(s32 *)(param_2 + 0x54) + 1;
  }
  if (*(void **)param_1 != 0) {
    FUN_004d0f00(*(void **)param_1);
  }
  *(u8 **)param_1 = param_2;
  return param_1;
}

/* P4: src/renderware/world/baworobj.c readSectorMesh (func_003cb870).
   P4 state: -O4 default, schedule on. */

#pragma optimization_level 4
#pragma schedule on
// FUN_0049BDC0
void *FUN_0049bdc0(void *param_1, void *param_2, u8 *param_3)
{
  u8 *world;

  world = FUN_0049a170((u32)param_3);
  *(void **)(param_3 + 0x78) = FUN_00496230(param_1, world, world + 0x10);
  if (*(void **)(param_3 + 0x78) != 0) {
    return param_1;
  }
  return 0;
}

/* P4: src/renderware/world/balight.c RpLightSetColor (func_003c38b0).
   P4 state: -O4 default, schedule on. */
typedef struct RwRGBAReal119 { float red; float green; float blue; float alpha; } RwRGBAReal119;

#pragma optimization_level 4
#pragma schedule on
// FUN_004944B0
void *FUN_004944b0(void *param_1, RwRGBAReal119 *param_2)
{
  *(RwRGBAReal119 *)((u8 *)param_1 + 0x18) = *param_2;
  if ((*(float *)((u8 *)param_1 + 0x18) == *(float *)((u8 *)param_1 + 0x1c)) &&
      (*(float *)((u8 *)param_1 + 0x18) == *(float *)((u8 *)param_1 + 0x20))) {
    *(u8 *)((u8 *)param_1 + 3) = 1;
  } else {
    *(u8 *)((u8 *)param_1 + 3) = 0;
  }
  return param_1;
}

/* P4: src/renderware/world/bageomet.c RpGeometryTriangleSetMaterial
   (func_003c2150).  P4 state: -O4 default, schedule on. */
typedef struct RpGeometry119 { u8 pad[0x20]; RpMatList119 matList; } RpGeometry119;
extern s32 FUN_00495340(RpMatList119 *matList, u32 *material);

#pragma optimization_level 4
#pragma schedule on
// FUN_00493230
void *FUN_00493230(void *param_1, u8 *param_2, u32 *param_3)
{
  s32 i;

  if (param_3 != 0) {
    i = FUN_00495480((const RpMatList119 *)((const u8 *)param_1 + 0x20), param_3);
    if (i < 0) {
      i = FUN_00495340(&((RpGeometry119 *)param_1)->matList, param_3);
      if (i < 0) {
        return 0;
      }
    }
    *(u16 *)(param_2 + 6) = (u16)i;
  } else {
    *(u16 *)(param_2 + 6) = 0xffff;
  }
  return param_1;
}

/* P4: src/renderware/world/bamesh.c _rpMeshSize (func_003c5fd0).
   P4 state: -O4 default, schedule on. */

#pragma optimization_level 4
#pragma schedule on
// FUN_004964F0
s32 FUN_004964f0(s32 param_1, u8 *param_2)
{
  s32 iVar1;

  if (((*param_2 == 8) && ((*(u32 *)(param_2 + 8) & 0x1000000) != 0)) ||
      ((*param_2 == 7) && ((*(u32 *)(param_2 + 8) & 0x1000000) != 0))) {
    iVar1 = (u32)*(u16 *)(param_1 + 4) * 8 + 0xc;
  } else {
    iVar1 = (u32)*(u16 *)(param_1 + 4) * 8 + 0xc + *(s32 *)(param_1 + 8) * 4;
  }
  return iVar1;
}

/* P4: src/renderware/world/baworld.c _rpWorldSectorForAllLocalLights
   (func_003c9750).  P4 state: -O4 default, schedule on.  The pointer-typed
   link fields drive MWCC's branch layout; integer-typed fields do not. */
typedef struct RpLightTie119 {
  void *next;
  u32 pad;
  void *light;
} RpLightTie119;

#pragma optimization_level 4
#pragma schedule on
// FUN_00499CA0
void *FUN_00499ca0(void *param_1, s32 (*param_2)(void *, void *), void *param_3)
{
  RpLightTie119 *cur;
  RpLightTie119 *end;
  RpLightTie119 *next;

  cur = *(RpLightTie119 **)((u8 *)param_1 + 0x40);
  end = (RpLightTie119 *)((u8 *)param_1 + 0x40);
  while (cur != end) {
    RpLightTie119 *lightTie = cur;

    next = lightTie->next;
    if (lightTie->light) {
      if (param_2(lightTie->light, param_3) == 0) {
        return param_1;
      }
    }
    cur = next;
  }
  return param_1;
}

/* P4: src/renderware/world/bamesh.c _rpMeshHeaderForAllMeshes
   (func_003c59f0).  P4 state: -O4 default, schedule on. */

#pragma optimization_level 4
#pragma schedule on
// FUN_00495F10
void *FUN_00495f10(void *param_1, s32 (*param_2)(void *, void *, void *), void *param_3)
{
  s32 numMeshes;
  u8 *mesh;

  numMeshes = *(u16 *)((u8 *)param_1 + 4);
  mesh = (u8 *)(*(s32 *)((u8 *)param_1 + 0xc) + (s32)param_1) + 0x10;
  while (numMeshes--) {
    if (param_2(mesh, param_1, param_3) == 0) {
      return param_1;
    }
    mesh += 0xc;
  }
  return param_1;
}

/* P4: src/promoted/code1_003c_cw119.c func_003c95a0 (func_003c95a0).
   P4 state: -O4 default, schedule on.  The D_008865B0 argument must stay a
   symbol so MWCC emits the lui/addiu pair retail uses for 0x95DF30. */
extern s32 FUN_0049c6c0(void);
extern s32 FUN_004c3b60(s32 a, s32 b, s32 c, s32 d, void *e, s32 f);
extern u32 iGpffffbb70;
extern u32 iGpffffbb74;
extern u8 DAT_00960070[];
extern u8 DAT_0095df30[];

#pragma optimization_level 4
#pragma schedule on
// FUN_00499AF0
s32 FUN_00499af0(s32 arg0, s32 arg1)
{
  u8 *slot;
  s32 result;

  iGpffffbb70 = arg1;
  if (FUN_0049c6c0() == 0) {
    return 0;
  }
  result = FUN_004c3b60(0x10, 8, 4, 1, (void *)DAT_0095df30, 0x4000b);
  slot = DAT_00960070 + iGpffffbb70;
  *(s32 *)slot = result;
  result = *(s32 *)slot;
  if (result == 0) {
    return 0;
  }
  slot += 4;
  *(u8 **)(slot + 0) = slot;
  *(u8 **)(slot + 4) = slot;
  iGpffffbb74 += 1;
  return arg0;
}

/* P4: src/renderware/world/baworobj.c RwCameraForAllSectorsInFrustum
   (func_003cbde0).  P4 state: -O4 default, schedule on. */

#pragma optimization_level 4
#pragma schedule on
// FUN_0049C330
void *FUN_0049c330(void *param_1, s32 (*param_2)(void *, void *), void *param_3)
{
  u8 *cameraExt;
  void **frustumSectors;
  s32 i;

  cameraExt = (u8 *)param_1 + iGpffffbb78;
  frustumSectors = *(void ***)cameraExt;
  i = *(s32 *)(cameraExt + 8);
  for (; i != 0; i--) {
    if (param_2(*frustumSectors, param_3) == 0) {
      return param_1;
    }
    frustumSectors++;
  }
  return param_1;
}

/* P4: src/renderware/world/baclump.c ClumpAtomicCloneAndAttach (func_003bea60).
   P4 state: -O4 default, schedule on. */
extern void *FUN_00491b40(void *param_1);
extern void FUN_00491a80(void *param_1);
extern void FUN_00492d10(void *param_1, void *param_2, ...);
extern s32 FUN_004c1d10(s32 param_1, ...);
extern void FUN_004c1c50(void *param_1);

#pragma optimization_level 4
#pragma schedule on
// FUN_004908D0
void *FUN_004908d0(void *param_1, u8 *param_2)
{
  void *newAtomic;
  u32 frame;
  u32 err[2];

  newAtomic = FUN_00491b40(param_1);
  if (newAtomic == 0) {
    *(u32 *)(param_2 + 8) = 0;
    return 0;
  }
  frame = *(u32 *)((u8 *)param_1 + 4);
  if (frame == 0) {
    FUN_00491a80(newAtomic);
    err[0] = 2;
    err[1] = FUN_004c1d10(5);
    FUN_004c1c50(err);
    return 0;
  }
  FUN_00492d10(newAtomic, (void *)*(u32 *)(frame + 0xa0));
  FUN_00491ff0((void *)*(u32 *)(param_2 + 4), newAtomic);
  return param_1;
}

/* P4: src/renderware/world/bageomet.c RpGeometryForAllMaterials (func_003c21e0).
   P4 state: -O4 default, schedule on. */

#pragma optimization_level 4
#pragma schedule on
// FUN_004932C0
void *FUN_004932c0(void *param_1, s32 (*param_2)(void *, void *), void *param_3)
{
  RpGeometry119 *geometry = (RpGeometry119 *)param_1;
  s32 numMaterials;
  s32 i;

  numMaterials = geometry->matList.numMaterials;
  for (i = 0; i < numMaterials; i++) {
    if (param_2(geometry->matList.materials[i], param_3) == 0) {
      return param_1;
    }
  }
  return param_1;
}

/* P4: src/promoted/code1_003c_cw119.c func_003c9940 (func_003c9940).
   P4 state: -O4 default, schedule on.  The allocator is an array element, so
   retail loads it absolutely; the DAT_00960070 + iGpffffbb70 base is re-formed
   at each use because the P4 source repeats that expression. */
extern u32 DAT_00960188[];

#pragma optimization_level 4
#pragma schedule on
// FUN_00499E90
void FUN_00499e90(u32 arg0, u32 arg1)
{
  u8 *temp2;
  u8 *temp4;
  u8 *(*allocator)(u8 *, u32);

  allocator = (u8 *(*)(u8 *, u32))DAT_00960188[0];
  temp2 = allocator(*(u8 **)(DAT_00960070 + iGpffffbb70), 0x40507);
  if (temp2 != 0) {
    *(u32 *)(temp2 + 0) = arg0;
    *(u32 *)(temp2 + 4) = arg1;
    *(u32 *)(temp2 + 8) = *(u32 *)(DAT_00960070 + iGpffffbb70 + 4);
    *(u32 *)(temp2 + 0xc) = (u32)(DAT_00960070 + iGpffffbb70 + 4);
    temp4 = temp2 + 8;
    *(u32 *)(*(u32 *)(DAT_00960070 + iGpffffbb70 + 4) + 4) = (u32)temp4;
    *(u32 *)(DAT_00960070 + iGpffffbb70 + 4) = (u32)temp4;
  }
}

/* P4: src/renderware/world/baworld.c RpWorldLock (func_003c9a80).
   P4 state: -O4 default, schedule on. */
typedef struct RpWorldSector119 { u8 pad[0x78]; void *mesh; } RpWorldSector119;
typedef struct RpPlaneSector119 { u8 pad[8]; s32 *leftSubTree; s32 *rightSubTree; } RpPlaneSector119;
extern void FUN_00495c80(void *param_1);

#pragma optimization_level 4
#pragma schedule on
// FUN_00499FD0
void *FUN_00499fd0(void *param_1)
{
  s32 *sector;
  s32 stack[64];
  s32 sp;

  sector = *(s32 **)((u8 *)param_1 + 0x1c);
  sp = 0;
  if (sector == 0) {
    return 0;
  }
  do {
    if (*sector < 0) {
      RpWorldSector119 *worldSector = (RpWorldSector119 *)sector;

      if (worldSector->mesh) {
        FUN_00495c80(worldSector->mesh);
        worldSector->mesh = 0;
      }
      sector = (s32 *)stack[sp--];
    } else {
      RpPlaneSector119 *planeSector = (RpPlaneSector119 *)sector;

      sector = planeSector->leftSubTree;
      stack[++sp] = (s32)planeSector->rightSubTree;
    }
  } while (sp >= 0);
  return param_1;
}

/* P4: src/renderware/world/baworld.c RpWorldForAllMaterials (func_003ca270).
   P4 state: -O4 default, schedule on. */
typedef struct RpWorld119 { u8 pad[0x10]; RpMatList119 matList; } RpWorld119;

#pragma optimization_level 4
#pragma schedule on
// FUN_0049A7C0
void *FUN_0049a7c0(void *param_1, s32 (*param_2)(void *, void *), void *param_3)
{
  RpWorld119 *world = (RpWorld119 *)param_1;
  s32 numMaterials;
  s32 i;

  numMaterials = world->matList.numMaterials;
  for (i = 0; i < numMaterials; i++) {
    if (param_2(world->matList.materials[i], param_3) == 0) {
      return param_1;
    }
  }
  return param_1;
}

/* P4: src/renderware/world/bameshop.c TriStripGetTriEdge (func_003c6960).
   P4 state: -O4 default, schedule on. */
typedef struct TriEdge119 { u16 v1; u16 v2; } TriEdge119;
typedef struct TriBinEntry119 { u32 pad0; TriEdge119 *edge[3]; } TriBinEntry119;

#pragma optimization_level 4
#pragma schedule on
// FUN_00496E80
static TriEdge119 *FUN_00496e80(TriBinEntry119 *binEntry, u16 v1, u16 v2)
{
  if ((binEntry->edge[0]->v1 == v1 && binEntry->edge[0]->v2 == v2) ||
      (binEntry->edge[0]->v1 == v2 && binEntry->edge[0]->v2 == v1)) {
    return binEntry->edge[0];
  }
  if ((binEntry->edge[1]->v1 == v1 && binEntry->edge[1]->v2 == v2) ||
      (binEntry->edge[1]->v1 == v2 && binEntry->edge[1]->v2 == v1)) {
    return binEntry->edge[1];
  }
  if ((binEntry->edge[2]->v1 == v1 && binEntry->edge[2]->v2 == v2) ||
      (binEntry->edge[2]->v1 == v2 && binEntry->edge[2]->v2 == v1)) {
    return binEntry->edge[2];
  }
  return 0;
}

/* P4: src/promoted/code1_003d_cw119.c func_003d0460 (func_003d0460).
   P4 state: -O4 default, schedule on, no_branch_likely off.  Every store in
   the fast path re-reads *arg1 because it may alias arg1 itself. */
extern u8 *FUN_004c4930(u8 *arg0);
extern u32 DAT_00960178[];

#pragma optimization_level 4
#pragma schedule on
#pragma no_branch_likely off
// FUN_004A08F0
void FUN_004a08f0(u8 *arg0, u32 **arg1, s32 arg2, s32 arg3)
{
  u32 *var_2;
  u8 *temp_16;

  if (*(s32 *)(arg0 + 0x24) == 0) {
    temp_16 = *(u8 **)(*(u8 **)(arg0 + 8) + 0x18);
    if (*(s32 *)(temp_16 + 8) & 0x02000000) {
      *arg1 = (u32 *)((u8 *(*)(s32, s32))DAT_00960178[0])(arg2 + 0x18, 0x3050D);
      *(u32 *)(*arg1) = 0;
      *(s32 *)((u8 *)(*arg1) + 4) = 0;
      *(u8 **)((u8 *)(*arg1) + 0xC) = temp_16;
      *(s32 *)((u8 *)(*arg1) + 8) = arg2;
      *(s32 *)((u8 *)(*arg1) + 0x10) = (s32)arg1;
      *(s32 *)((u8 *)(*arg1) + 0x14) = arg3;
    } else {
      var_2 = (u32 *)FUN_004c4930(temp_16);
      *arg1 = var_2;
    }
  } else {
    var_2 = (u32 *)FUN_004c4930(*(u8 **)(arg0 + 8));
    *arg1 = var_2;
  }
}

/* P4: src/promoted/code1_003d_cw119.c func_003d0850 (func_003d0850).
   P4 state: -O4 default, schedule on, no_branch_likely off. */
extern u8 DAT_00960074[];

#pragma optimization_level 4
#pragma schedule on
#pragma no_branch_likely off
// FUN_004A0CE0
u32 *FUN_004a0ce0(u8 *arg0, u32 **arg1, s32 arg2, s32 arg3)
{
  u8 *temp_16;

  temp_16 = *(u8 **)(arg0 + 8);
  if (*temp_16 == 0xFF) {
    if (*(s32 *)(*(u8 **)DAT_00960074 + 8) & 0x02000000) {
      *arg1 = (u32 *)((u8 *(*)(s32, s32))DAT_00960178[0])(arg2 + 0x18, 0x3050D);
      *(u32 *)(*arg1) = 0;
      *(s32 *)((u8 *)(*arg1) + 4) = 0;
      *(u8 **)((u8 *)(*arg1) + 0xC) = temp_16;
      *(s32 *)((u8 *)(*arg1) + 8) = arg2;
      *(s32 *)((u8 *)(*arg1) + 0x10) = (s32)arg1;
      *(s32 *)((u8 *)(*arg1) + 0x14) = arg3;
    } else {
      *arg1 = (u32 *)FUN_004c4930(temp_16);
    }
  } else {
    FUN_004a08f0(arg0, arg1, arg2, arg3);
  }
  return *arg1;
}

/* P4: src/renderware/world/baworld.c RpWorldUnlock (func_003c9b30).
   P4 state: -O4 default, schedule on. */
typedef struct RpWorldSectorUnlock119 {
  u8 pad[0x78];
  void *mesh;
  u8 pad2[4];
  u16 matListWindowBase;
  u16 pad3;
  u16 numTriangles;
} RpWorldSectorUnlock119;
extern void *FUN_00495b10(u16 numTriangles);
extern void *FUN_00499400(void *world, void *buildMesh, void *worldSector, u32 **matBase);

#pragma optimization_level 4
#pragma schedule on
// FUN_0049A080
void *FUN_0049a080(void *param_1)
{
  s32 *sector;
  s32 stack[64];
  s32 sp;
  void *buildMesh;
  u32 **matBase;

  sector = *(s32 **)((u8 *)param_1 + 0x1c);
  sp = 0;
  if (sector == 0) {
    return 0;
  }
  do {
    if (*sector < 0) {
      RpWorldSectorUnlock119 *worldSector = (RpWorldSectorUnlock119 *)sector;

      matBase = ((RpMatList119 *)((u8 *)param_1 + 0x10))->materials + worldSector->matListWindowBase;
      if (worldSector->mesh == 0) {
        buildMesh = FUN_00495b10(worldSector->numTriangles);
        if (buildMesh != 0) {
          param_1 = FUN_00499400(param_1, buildMesh, worldSector, matBase);
          if (param_1 == 0) {
            return 0;
          }
        } else {
          return 0;
        }
      }
      sector = (s32 *)stack[sp--];
    } else {
      RpPlaneSector119 *planeSector = (RpPlaneSector119 *)sector;

      sector = planeSector->leftSubTree;
      stack[++sp] = (s32)planeSector->rightSubTree;
    }
  } while (sp >= 0);
  return param_1;
}

/* P4: src/promoted/code1_003c_cw119.c func_003cc370 (func_003cc370).
   P4 state: -O4 default, schedule on, opt_propagation on. */
extern u8 *FUN_0049c810(void);
extern s32 FUN_0046a890(s32 param_1);
extern void FUN_004f23c0(void *param_1);
extern void FUN_004f2430(s32 param_1, s32 param_2);
extern u32 DAT_007ceb20;

#pragma optimization_level 4
#pragma schedule on
#pragma opt_propagation on
// FUN_0049C8C0
s32 FUN_0049c8c0(void)
{
  u8 *temp_20;
  s32 temp_17;
  s32 temp_19;
  s32 temp_16;
  s32 temp_18;
  u8 *temp_2;

  temp_20 = FUN_0049c810();
  temp_17 = FUN_0046a890(4);
  temp_19 = FUN_0046a890(6);
  temp_16 = FUN_0046a890(5);
  temp_18 = FUN_0046a890(7);
  temp_2 = DAT_00960070 + DAT_007ceb20;
  *(u8 **)(temp_2 + 0x1C) = temp_20;
  *(s32 *)(temp_2 + 0x20) = temp_19;
  *(s32 *)(temp_2 + 0x24) = temp_19;
  *(s32 *)(temp_2 + 0x28) = temp_19;
  *(s32 *)(temp_2 + 0x2C) = temp_18;
  *(s32 *)(temp_2 + 0x30) = temp_18;
  *(s32 *)(temp_2 + 0x38) = temp_17;
  *(s32 *)(temp_2 + 0x3C) = temp_16;
  FUN_004f23c0(temp_20);
  FUN_004f2430(temp_19, 3);
  FUN_004f2430(temp_19, 5);
  FUN_004f2430(temp_19, 4);
  FUN_004f2430(temp_18, 1);
  FUN_004f2430(temp_18, 2);
  return 1;
}

/* P4: src/promoted/code1_003c_cw119.c func_003c00e0 (func_003c00e0).
   P4 state: -O4 default, schedule on.  The goto structure reproduces
   retail's separate null_result block (return NULL placed out of line). */
extern u32 iGpffffbb30;
extern void *FUN_00490860(void *param_1);
extern void FUN_004c64b0(void *param_1, void *param_2);
extern u32 DAT_0077dce0;
#pragma alias DAT_0077dce0_abs DAT_0077dce0
extern u8 DAT_0077dce0_abs[];

#pragma optimization_level 4
#pragma schedule on
#pragma opt_propagation on
// FUN_00491880
u8 *FUN_00491880(void)
{
  u8 *obj;

  obj = (u8 *)((u8 *(*)(u32, s32))DAT_00960188[0])(*(u32 *)(DAT_00960070 + iGpffffbb30), 0x30014);
  if (obj != 0) {
    *(u8 *)(obj + 0) = 1;
    *(u8 *)(obj + 1) = 0;
    *(u8 *)(obj + 2) = 0;
    *(u8 *)(obj + 3) = 0;
    *(u32 *)(obj + 4) = 0;
    *(code **)(obj + 0x10) = (code *)FUN_00490810;
    *(u32 *)(obj + 0x14) = 0;
    *(u8 *)(obj + 2) = 5;
    *(u8 *)(obj + 3) = 1;
    FUN_00492d10(obj, 0, 1);
    *(u32 *)(obj + 0x18) = 0;
    *(u32 *)(obj + 0x28) = 0;
    *(u32 *)(obj + 0x1c) = 0;
    *(u32 *)(obj + 0x20) = 0;
    *(u32 *)(obj + 0x24) = 0;
    *(u32 *)(obj + 0x38) = 0;
    *(u32 *)(obj + 0x2c) = 0;
    *(u32 *)(obj + 0x30) = 0;
    *(u32 *)(obj + 0x34) = 0;
    *(code **)(obj + 0x48) = (code *)FUN_00490860;
    if (*(code **)(obj + 0x48) == 0) {
      goto reset_callback;
    }
init:
    *(u16 *)(obj + 0x50) = 0;
    *(u16 *)(obj + 0x52) = 0;
    *(u32 *)(obj + 0x54) = 0x3f800000;
    *(u32 *)(obj + 0x58) = 0x3f800000;
    *(u32 *)(obj + 0x5c) = 0;
    *(u32 *)(obj + 0x4c) = 3;
    *(u32 *)(obj + 0x44) = 0;
    *(u32 *)(obj + 0x40) = 0;
    *(u32 *)(obj + 0x3c) = 0;
    *(u32 *)(obj + 0x6c) = 0;
    *(u8 **)(obj + 0x64) = obj + 0x64;
    *(u8 **)(obj + 0x68) = obj + 0x64;
    FUN_004c64b0((void *)DAT_0077dce0_abs, obj);
    goto done;
  }
null_result:
  return 0;
reset_callback:
  *(code **)(obj + 0x48) = (code *)FUN_00490860;
  goto init;
done:
  return obj;
}

/* P4: src/renderware/world/baworld.c _rpWorldSectorDeinstanceAll (func_003c91d0).
   P4 state: -O4 default, schedule on.  Type the repEntry/mesh conditions as
   pointers: MWCC inlines the then-call for pointer null tests, outlines it
   for integer tests. */
extern void FUN_004c47e0(void *param_1);
extern void FUN_0049af20(void *param_1);
extern void FUN_0049aeb0(void *param_1);
extern void FUN_004c6560(void *param_1, void *param_2);
typedef struct RpWorldSectorMesh119 { u8 pad[0x78]; void *mesh; } RpWorldSectorMesh119;
extern u32 DAT_0077ddb0;
#pragma alias DAT_0077ddb0_abs DAT_0077ddb0
extern u8 DAT_0077ddb0_abs[];

#pragma optimization_level 4
#pragma schedule on
#pragma opt_propagation off
// FUN_00499720
void FUN_00499720(s32 *param_1)
{
  s32 *cur;
  s32 *end;
  s32 *tie;
  s32 *lightTie;

  switch (*param_1) {
  case -1:
    if (*(void **)((u8 *)param_1 + 0x34) != 0) {
      FUN_004c47e0(*(void **)((u8 *)param_1 + 0x34));
    }
    cur = *(s32 **)((u8 *)param_1 + 0x38);
    end = (s32 *)((u8 *)param_1 + 0x38);
    while (cur != end) {
      tie = cur;
      cur = *(s32 **)cur;
      FUN_0049af20(tie);
    }
    cur = *(s32 **)((u8 *)param_1 + 0x40);
    end = (s32 *)((u8 *)param_1 + 0x40);
    while (cur != end) {
      lightTie = cur;
      cur = *(s32 **)cur;
      FUN_0049aeb0(lightTie);
    }
    FUN_004c6560((void *)DAT_0077ddb0_abs, param_1);
    {
      RpWorldSectorMesh119 *worldSector = (RpWorldSectorMesh119 *)param_1;

      if (worldSector->mesh) {
        FUN_00495c80(worldSector->mesh);
        worldSector->mesh = 0;
      }
    }
    break;
  case -2:
    break;
  default:
    if (*(s32 **)((u8 *)param_1 + 8) != 0) {
      FUN_00499720(*(s32 **)((u8 *)param_1 + 8));
    }
    if (*(s32 **)((u8 *)param_1 + 0xc) != 0) {
      FUN_00499720(*(s32 **)((u8 *)param_1 + 0xc));
    }
    break;
  }
}

/* P4: src/renderware/world/baworld.c _rpWorldSetupSectorBoundingBoxes
   (func_003c97e0).  P4 state: -O4 default, schedule on.  The P4 tree's
   SETCOORD operands are mirrored vs. the golden binary; the stores below
   are the golden shapes (rightValue->entry.sup, leftValue->bbox.inf). */
typedef struct RwV3d119 { f32 x; f32 y; f32 z; } RwV3d119;
typedef struct RwBBox119 { RwV3d119 inf; RwV3d119 sup; } RwBBox119;
typedef struct RpWorldSectorBB119 { u8 pad[0x48]; RwBBox119 boundingBox; } RpWorldSectorBB119;
typedef struct RpPlaneSectorBB119 {
  s32 type;
  f32 value;
  s32 *leftSubTree;
  s32 *rightSubTree;
  f32 leftValue;
  f32 rightValue;
} RpPlaneSectorBB119;

#pragma optimization_level 4
#pragma schedule on
// FUN_00499D30
void *FUN_00499d30(void *param_1)
{
  s32 nStack;
  s32 *sector;
  s32 *sectorStack[64];
  RwBBox119 bbox;
  RwBBox119 bboxStack[64];

  nStack = 0;
  sector = *(s32 **)((u8 *)param_1 + 0x1c);
  bbox = *(RwBBox119 *)((u8 *)param_1 + 0x50);

  while (nStack >= 0) {
    if (*sector < 0) {
      RpWorldSectorBB119 *worldSector = (RpWorldSectorBB119 *)sector;

      worldSector->boundingBox = bbox;
      sector = (s32 *)sectorStack[nStack];
      bbox = bboxStack[nStack];
      nStack--;
    } else {
      RpPlaneSectorBB119 *plane = (RpPlaneSectorBB119 *)sector;

      nStack++;
      sectorStack[nStack] = plane->rightSubTree;
      bboxStack[nStack] = bbox;
      *(f32 *)((u8 *)&bboxStack[nStack].sup + plane->type) = plane->rightValue;
      *(f32 *)((u8 *)&bbox.inf + plane->type) = plane->leftValue;
      sector = plane->leftSubTree;
    }
  }
  return param_1;
}

/* P4: src/renderware/world/baclump.c RpAtomicClone (func_003c03a0).
   P4 state: -O4 default, schedule on.  rwObjectCopy/RpAtomicSetFlags are
   expanded from the P4 headers; RpAtomicSetGeometry (P4 func_003c0210) is
   reproduced as its inlined body. */
typedef struct RwObject119 {
  u8 type;
  u8 subType;
  u8 flags;
  u8 privateFlags;
  void *parent;
} RwObject119;
typedef struct RwSphere119 { f32 x; f32 y; f32 z; f32 radius; } RwSphere119;
typedef struct RpInterpolator119 {
  s32 flags;
  s32 startMorphTarget;
  s32 endMorphTarget;
  f32 time;
  f32 recipTime;
} RpInterpolator119;
extern void FUN_00493b40(void *param_1);
extern void FUN_00493b60(void *param_1);
extern s32 FUN_0049c230(void *param_1);
extern void FUN_004c65d0(void *param_1, void *param_2, void *param_3);

#pragma optimization_level 4
#pragma schedule on
// FUN_00491B40
void *FUN_00491b40(void *param_1)
{
  u8 *atomic = (u8 *)param_1;
  u8 *newAtomic;
  u8 *geometry;
  u8 *frame;

  newAtomic = FUN_00491880();
  if (newAtomic == 0) {
    return 0;
  }

  ((RwObject119 *)newAtomic)->type = ((RwObject119 *)atomic)->type;
  ((RwObject119 *)newAtomic)->subType = ((RwObject119 *)atomic)->subType;
  ((RwObject119 *)newAtomic)->flags = ((RwObject119 *)atomic)->flags;
  ((RwObject119 *)newAtomic)->privateFlags = ((RwObject119 *)atomic)->privateFlags;
  ((RwObject119 *)newAtomic)->parent = 0;
  ((RwObject119 *)newAtomic)->flags = ((RwObject119 *)atomic)->flags;

  FUN_00492d10(newAtomic, 0);

  geometry = *(u8 **)(atomic + 0x18);
  if (geometry != *(u8 **)(newAtomic + 0x18)) {
    if (geometry != 0) {
      FUN_00493b40(geometry);
    }
    if (*(u8 **)(newAtomic + 0x18) != 0) {
      FUN_00493b60(*(u8 **)(newAtomic + 0x18));
    }
    *(u8 **)(newAtomic + 0x18) = geometry;
    if (geometry != 0) {
      u8 *morph = *(u8 **)(geometry + 0x5c);

      *(RwSphere119 *)(newAtomic + 0x1c) = *(RwSphere119 *)(morph + 4);
    }
    frame = *(u8 **)(newAtomic + 4);
    if (frame != 0) {
      if (FUN_0049c230(newAtomic) != 0) {
        FUN_004cb270(frame);
      }
    }
  }

  *(RwSphere119 *)(newAtomic + 0x1c) = *(RwSphere119 *)(atomic + 0x1c);
  *(void **)(newAtomic + 0x48) = *(void **)(atomic + 0x48);
  *(void **)(newAtomic + 0x6c) = *(void **)(atomic + 0x6c);
  *(RpInterpolator119 *)(newAtomic + 0x4c) = *(RpInterpolator119 *)(atomic + 0x4c);

  FUN_004c65d0((void *)DAT_0077dce0_abs, newAtomic, atomic);
  return newAtomic;
}

/* P4: src/promoted/code1_003d_cw119.c func_003d3460 (func_003d3460).
   P4 state: -O4 default, schedule on, no_branch_likely off. */
extern u8 *FUN_004f3f70();
extern u8 *FUN_004f3ec0();

#pragma optimization_level 4
#pragma schedule on
#pragma no_branch_likely off
// FUN_004A38F0
s32 FUN_004a38f0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
  u8 *var_2;
  u8 *temp_2;
  u32 var_5;
  u8 *var_4;
  s32 var_5_2;

  if (arg0 == 0) {
    return 0;
  }
  if (arg1 <= 0) {
    return 0;
  }
  if (arg2 < 3) {
    return 0;
  }
  if (arg3 <= 0) {
    return 0;
  }

  var_2 = (u8 *)FUN_004f3f70();
  if ((var_2 != 0) && ((*(u32 *)(var_2 + 0x3c) & 0x1c) != 0)) {
    return 0;
  }
  if (var_2 == 0) {
    temp_2 = (u8 *)FUN_004f3ec0(arg0, 0x40);
    if (temp_2 != 0) {
      var_5 = 0;
      var_4 = temp_2;
      do {
        *(u32 *)(var_4 + 0) = 0;
        var_5 += 5;
        *(u32 *)(var_4 + 4) = 0;
        *(u32 *)(var_4 + 8) = 0;
        *(u32 *)(var_4 + 0xC) = 0;
        *(u32 *)(var_4 + 0x10) = 0;
        var_4 += 0x14;
      } while (var_5 < 0xA);

      *(u32 *)(temp_2 + 0x3C) = 0;
      *(u32 *)(temp_2 + 0x38) = 4;
      *(u32 *)(temp_2 + 0x34) = *(u32 *)(temp_2 + 0x38) * 0x45;
      *(u32 *)(temp_2 + 0x30) = *(u32 *)(temp_2 + 0x38) * 0x45;
      var_5_2 = 1;
    } else {
      var_5_2 = 0;
    }
    if (var_5_2 == 0) {
      return 0;
    }
    var_2 = (u8 *)FUN_004f3f70(arg0, var_5_2);
  }

  *(u32 *)(var_2 + 0x34) = arg1 * (arg3 * 3);
  *(u32 *)(var_2 + 0x30) = arg2 * arg1;
  *(u32 *)(var_2 + 0x38) = arg1;
  *(u32 *)(var_2 + 0x3c) = 3;
  return arg0;
}

/* P4: src/promoted/code1_003d_cw119.c func_003d35f0 (func_003d35f0).
   P4 state: -O4 default, schedule on, no_branch_likely off. */

#pragma optimization_level 4
#pragma schedule on
#pragma no_branch_likely off
// FUN_004A3A80
s32 FUN_004a3a80(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
  u8 *var_2;
  u8 *temp_2;
  u32 var_5;
  u8 *var_4;
  s32 var_5_2;

  if (arg0 == 0) {
    return 0;
  }
  if (arg1 <= 0) {
    return 0;
  }
  if (arg2 < 2) {
    return 0;
  }
  if (arg3 <= 0) {
    return 0;
  }

  var_2 = (u8 *)FUN_004f3f70();
  if ((var_2 != 0) && ((*(u32 *)(var_2 + 0x3c) & 0x13) != 0)) {
    return 0;
  }
  if (var_2 == 0) {
    temp_2 = (u8 *)FUN_004f3ec0(arg0, 0x40);
    if (temp_2 != 0) {
      var_5 = 0;
      var_4 = temp_2;
      do {
        *(u32 *)(var_4 + 0) = 0;
        var_5 += 5;
        *(u32 *)(var_4 + 4) = 0;
        *(u32 *)(var_4 + 8) = 0;
        *(u32 *)(var_4 + 0xC) = 0;
        *(u32 *)(var_4 + 0x10) = 0;
        var_4 += 0x14;
      } while (var_5 < 0xA);

      *(u32 *)(temp_2 + 0x3C) = 0;
      *(u32 *)(temp_2 + 0x38) = 4;
      *(u32 *)(temp_2 + 0x34) = *(u32 *)(temp_2 + 0x38) * 0x45;
      *(u32 *)(temp_2 + 0x30) = *(u32 *)(temp_2 + 0x38) * 0x45;
      var_5_2 = 1;
    } else {
      var_5_2 = 0;
    }
    if (var_5_2 == 0) {
      return 0;
    }
    var_2 = (u8 *)FUN_004f3f70(arg0, var_5_2);
  }

  *(u32 *)(var_2 + 0x34) = arg1 * (arg3 * 2);
  *(u32 *)(var_2 + 0x30) = arg2 * arg1;
  *(u32 *)(var_2 + 0x38) = arg1;
  *(u32 *)(var_2 + 0x3c) = 0xC;
  return arg0;
}

/* P4: src/renderware/world/baclump.c _rpAtomicResyncInterpolatedSphere
   (func_003bf930).  P4 state: -O4 default, schedule on.  In P3 the morph
   target indices are 16-bit (lh) and the morph target stride is 0x1c. */
typedef struct RpMorphTarget119 {
  u8 pad[4];
  RwSphere119 boundingSphere;
  u8 pad2[8];
} RpMorphTarget119;
typedef struct RpGeometry119b {
  u8 pad0[0x18];
  s32 numMorphTargets;
  u8 pad1[0x40];
  RpMorphTarget119 *morphTarget;
} RpGeometry119b;
typedef struct RpInterpolator119b {
  s32 flags;
  s16 startMorphTarget;
  s16 endMorphTarget;
  f32 f08;
  f32 f0C;
  f32 f10;
} RpInterpolator119b;
typedef struct RpAtomic119b {
  RwObject119 object;
  u8 pad1[0x10];
  RpGeometry119b *geometry;
  RwSphere119 boundingSphere;
  u8 pad2[0x20];
  RpInterpolator119b interpolator;
} RpAtomic119b;

#pragma optimization_level 4
#pragma schedule on
// FUN_00491100
void FUN_00491100(void *param_1)
{
  RpAtomic119b *atomic = (RpAtomic119b *)param_1;
  RpGeometry119b *geom;

  geom = atomic->geometry;
  if (geom != 0) {
    RpInterpolator119b *interpolator = &atomic->interpolator;

    if ((interpolator->startMorphTarget == interpolator->endMorphTarget)
        || (interpolator->startMorphTarget >= geom->numMorphTargets)
        || (interpolator->endMorphTarget >= geom->numMorphTargets)) {
      if ((interpolator->startMorphTarget >= geom->numMorphTargets)
          || (interpolator->endMorphTarget >= geom->numMorphTargets)) {
        atomic->boundingSphere = geom->morphTarget[0].boundingSphere;
      } else {
        atomic->boundingSphere = geom->morphTarget[interpolator->startMorphTarget].boundingSphere;
      }
    } else {
      RpMorphTarget119 *startMorphTarget = &geom->morphTarget[interpolator->startMorphTarget];
      RpMorphTarget119 *endMorphTarget = &geom->morphTarget[interpolator->endMorphTarget];
      f32 scale = interpolator->f0C * interpolator->f10;

      atomic->boundingSphere.radius =
          (endMorphTarget->boundingSphere.radius - startMorphTarget->boundingSphere.radius) * scale
          + startMorphTarget->boundingSphere.radius;

      atomic->boundingSphere.x = endMorphTarget->boundingSphere.x - startMorphTarget->boundingSphere.x;
      atomic->boundingSphere.y = endMorphTarget->boundingSphere.y - startMorphTarget->boundingSphere.y;
      atomic->boundingSphere.z = endMorphTarget->boundingSphere.z - startMorphTarget->boundingSphere.z;
      atomic->boundingSphere.x = atomic->boundingSphere.x * scale;
      atomic->boundingSphere.y = atomic->boundingSphere.y * scale;
      atomic->boundingSphere.z = atomic->boundingSphere.z * scale;
      atomic->boundingSphere.x = atomic->boundingSphere.x + startMorphTarget->boundingSphere.x;
      atomic->boundingSphere.y = atomic->boundingSphere.y + startMorphTarget->boundingSphere.y;
      atomic->boundingSphere.z = atomic->boundingSphere.z + startMorphTarget->boundingSphere.z;
    }

    interpolator->flags = interpolator->flags & 0xfffffffd;
    atomic->object.privateFlags = atomic->object.privateFlags | 1;
  }
}

/* P4: src/renderware/world/bameshop.c TriStripMarkTriUsed (func_003c6a40).
   P4 state: -O4 default, schedule on. */
typedef struct TriBinEntry119c TriBinEntry119c;
typedef struct TriEdge119c {
  u16 v1;
  u16 v2;
  TriBinEntry119c *tri1;
  TriBinEntry119c *tri2;
  struct TriEdge119c *next;
} TriEdge119c;
struct TriBinEntry119c {
  u32 tri;
  TriEdge119c *edge[3];
  TriBinEntry119c *next;
  TriBinEntry119c *prev;
  s32 used;
  s32 used2;
  u8 adjCount;
};
typedef struct TriBinList119 { TriBinEntry119c *head; } TriBinList119;

#pragma optimization_level 4
#pragma schedule on
// FUN_00496F60
static void FUN_00496f60(TriBinEntry119c *tri, TriBinList119 *binListArray, s32 currentAttempt)
{
  u8 i;
  TriBinEntry119c *newTri;

  if (currentAttempt < 4) {
    tri->used2 = 1;
  } else {
    tri->used = 1;

    if (binListArray[tri->adjCount].head == tri) {
      binListArray[tri->adjCount].head = binListArray[tri->adjCount].head->next;
      if (binListArray[tri->adjCount].head != 0) {
        binListArray[tri->adjCount].head->prev = 0;
      }
    } else {
      if (tri->next != 0) {
        tri->next->prev = tri->prev;
      }
      if (tri->prev != 0) {
        tri->prev->next = tri->next;
      }
    }

    for (i = 0; i < 3; i++) {
      newTri = 0;
      if ((tri->edge[i]->tri1 != 0) && (tri->edge[i]->tri1 != tri) && (tri->edge[i]->tri1->used == 0)) {
        newTri = tri->edge[i]->tri1;
      } else if ((tri->edge[i]->tri2 != 0) && (tri->edge[i]->tri2->used == 0)) {
        newTri = tri->edge[i]->tri2;
      }

      if (newTri != 0) {
        if (binListArray[newTri->adjCount].head == newTri) {
          binListArray[newTri->adjCount].head = binListArray[newTri->adjCount].head->next;
          if (binListArray[newTri->adjCount].head != 0) {
            binListArray[newTri->adjCount].head->prev = 0;
          }
        } else {
          if (newTri->next != 0) {
            newTri->next->prev = newTri->prev;
          }
          if (newTri->prev != 0) {
            newTri->prev->next = newTri->next;
          }
        }

        newTri->adjCount--;

        newTri->next = binListArray[newTri->adjCount].head;
        if (newTri->next != 0) {
          newTri->next->prev = newTri;
        }
        binListArray[newTri->adjCount].head = newTri;
        newTri->prev = 0;
      }
    }
  }
}

/* P4: src/renderware/world/bamesh.c _rpMeshWrite (func_003c5a90).
   P4 state: -O4 default, schedule on.  The typed const parameters and the
   value-first comparisons are what reproduce retail's instruction schedule. */
typedef struct binMeshHeader119 {
  u32 flags;
  u32 numMeshes;
  u32 totalIndicesInMesh;
} binMeshHeader119;
typedef struct binMesh119 {
  u32 numIndices;
  s32 matIndex;
} binMesh119;

#define RWINDEXBUFFERSIZE 256

extern void *FUN_004c17f0(void *stream, const s32 *data, u32 length);

#pragma optimization_level 4
#pragma schedule on
// FUN_00495FB0
void *FUN_00495fb0(const RpMeshHeader119 *meshHeader, const void *object, void *stream, const RpMatList119 *matList)
{
  binMeshHeader119 bmh;
  u32 numMeshes;
  const RpMesh119 *mesh;

  bmh.flags = meshHeader->flags;
  bmh.numMeshes = (u32)meshHeader->numMeshes;
  bmh.totalIndicesInMesh = meshHeader->totalIndicesInMesh;

  if (FUN_004c17f0(stream, (const s32 *)&bmh, sizeof(bmh)) == 0) {
    return 0;
  }

  mesh = (const RpMesh119 *)(meshHeader + 1);
  numMeshes = meshHeader->numMeshes;
  while (numMeshes--) {
    binMesh119 bm;
    u32 numIndices;
    u16 *meshIndices;

    bm.numIndices = mesh->numIndices;
    bm.matIndex = FUN_00495480(matList, mesh->material);

    if (bm.matIndex < 0) {
      bm.matIndex = 0;
    }

    if (FUN_004c17f0(stream, (const s32 *)&bm, sizeof(bm)) == 0) {
      return 0;
    }

    if (((8 == *(const u8 *)object) && ((0x1000000 & *(const u32 *)((const u8 *)object + 8)) == 0)) ||
        ((7 == *(const u8 *)object) && ((0x1000000 & *(const u32 *)((const u8 *)object + 8)) == 0))) {
      numIndices = mesh->numIndices;
      meshIndices = mesh->indices;

      while (numIndices > 0) {
        u32 IndexBuffer[RWINDEXBUFFERSIZE];
        u32 writeIndices;
        u32 i;

        writeIndices = (numIndices < RWINDEXBUFFERSIZE) ? (numIndices) : (RWINDEXBUFFERSIZE);

        for (i = 0; i < writeIndices; i++) {
          IndexBuffer[i] = (u32)*meshIndices++;
        }

        if (FUN_004c17f0(stream, (const s32 *)&IndexBuffer[0], sizeof(IndexBuffer[0]) * writeIndices) == 0) {
          return 0;
        }

        numIndices -= writeIndices;
      }
    }

    mesh++;
  }

  return stream;
}

/* P4: src/renderware/world/baclump.c ClumpAtomicStreamRead (func_003bf5f0).
   P4 state: -O4 default, schedule on.  rwID_STRUCT = 1, rwID_GEOMETRY = 0xf,
   rwLIBRARYBASEVERSION = 0x35000, rwLIBRARYCURRENTVERSION = 0x37002,
   E_RW_READ = 0x8000001a, E_RW_BADVERSION = 0x80000004, rwPLUGIN_ID = 2;
   RWERROR() expands to the two-word RwError local + _rwerror + RwErrorSet. */
typedef struct rwFrameList119 {
  void **frames;
  s32 numFrames;
} rwFrameList119;
typedef struct rpGeometryList119 {
  void **geometries;
  s32 numGeoms;
} rpGeometryList119;
typedef struct rpAtomicBinary119 {
  s32 frameIndex;
  s32 geomIndex;
  s32 flags;
  s32 unused;
} rpAtomicBinary119;

extern s32 FUN_004c1600(void *stream, u32 type, u32 *size, u32 *version);
extern void *FUN_00521408(void *dst, s32 c, u32 n);
extern s32 FUN_004c5250(void *stream, void *data, u32 size);
extern void FUN_004919b0(void *atomic, void *geom, s32 flag);
extern void *FUN_00493cb0(void *stream);
extern void *FUN_004c5a50(void *tkList, void *stream, void *object);
extern void FUN_004c5c30(void *tkList, s32 id, void *object, u32 extra);
extern u32 iGpffffbb2c;
extern u32 uGpffffbb28;

#define RWERROR119(code) do { u32 err[2]; err[0] = 2; err[1] = FUN_004c1d10(code); FUN_004c1c50(err); } while (0)

#pragma optimization_level 4
#pragma schedule on
// FUN_00490DC0
void *FUN_00490dc0(void *stream, rwFrameList119 *fl, rpGeometryList119 *gl)
{
  s32 status;
  u32 size;
  u32 version;

  status = FUN_004c1600(stream, 1, &size, &version);

  if (!status) {
    RWERROR119(0x8000001a);
    return 0;
  }

  if ((version >= 0x35000) && (version <= 0x37002)) {
    void *atom;
    rpAtomicBinary119 a;
    void *geom;

    FUN_00521408(&a, 0, sizeof(a));
    status = (size == FUN_004c5250(stream, &a, size));
    if (!status) {
      RWERROR119(0x8000001a);
      return 0;
    }

    atom = FUN_00491880();
    if (!atom) {
      return 0;
    }

    *(u8 *)((u8 *)atom + 2) = (u8)a.flags;
    if (fl->numFrames) {
      FUN_00492d10(atom, fl->frames[a.frameIndex]);
    }

    if (gl->numGeoms) {
      FUN_004919b0(atom, gl->geometries[a.geomIndex], 0);
    } else {
      status = FUN_004c1600(stream, 0xf, 0, &version);
      if (!status) {
        FUN_00491a80(atom);
        RWERROR119(0x8000001a);
        return 0;
      }

      if ((version >= 0x35000) && (version <= 0x37002)) {
        geom = FUN_00493cb0(stream);
        status = (geom != 0);
        if (!status) {
          FUN_00491a80(atom);
          RWERROR119(0x8000001a);
          return 0;
        }
      } else {
        FUN_00491a80(atom);
        RWERROR119(0x80000004);
        return 0;
      }

      FUN_004919b0(atom, geom, 0);
      FUN_00493b60(geom);
    }

    iGpffffbb2c = 0;
    uGpffffbb28 = 0;

    status = (FUN_004c5a50((void *)DAT_0077dce0_abs, stream, atom) != 0);
    if (!status) {
      RWERROR119(0x8000001a);
      return 0;
    }

    if (iGpffffbb2c) {
      FUN_004c5c30((void *)DAT_0077dce0_abs, iGpffffbb2c, atom, uGpffffbb28);
    }

    return atom;
  } else {
    RWERROR119(0x80000004);
    return 0;
  }
}

/* P4: src/renderware/world/babinwor.c PlaneSectorStreamRead (func_003bdd00).
   P4 state: -O4 default, schedule on.  BinaryWorldMalloc is a file-static in
   babinwor.c that retail inlined (bump the caller's pointer by the size);
   RwMemFloat32ToReal is a no-op on the PS2.  rwID_ATOMICSECT = 9,
   rwID_PLANESECT = 10, E_RW_NOMEM = 0x80000013. */
typedef struct RpPlaneSector119b {
  s32 type;
  float value;
  s32 *leftSubTree;
  s32 *rightSubTree;
  float leftValue;
  float rightValue;
} RpPlaneSector119b;
typedef struct rpPlaneSectorChunkInfo119 {
  s32 type;
  float value;
  s32 leftIsWorldSector;
  s32 rightIsWorldSector;
  float leftValue;
  float rightValue;
} rpPlaneSectorChunkInfo119;

extern void *FUN_0048f580(void *stream, u8 **binaryWorldMallocAddr, void *world, u32 flags);
extern void FUN_00499850(void *param_1);

#pragma optimization_level 4
#pragma schedule on
// FUN_0048FBD0
void *FUN_0048fbd0(void *stream, u8 **binaryWorldMallocAddr, void *world, u32 flags)
{
  RpPlaneSector119b *planeSector;
  rpPlaneSectorChunkInfo119 ps;
  u32 size, version;
  s32 result;

  result = 1;

  if (!FUN_004c1600(stream, 1, &size, &version)) {
    return 0;
  }

  if ((version < 0x35000) || (version > 0x37002)) {
    RWERROR119(0x80000004);
    return 0;
  }

  FUN_00521408(&ps, 0, sizeof(ps));
  if (FUN_004c5250(stream, &ps, size) != size) {
    return 0;
  }

  planeSector = (RpPlaneSector119b *)*binaryWorldMallocAddr;
  *binaryWorldMallocAddr = *binaryWorldMallocAddr + sizeof(RpPlaneSector119b);
  if (!planeSector) {
    u32 err[2];
    err[0] = 2;
    err[1] = FUN_004c1d10(0x80000013, sizeof(RpPlaneSector119b));
    FUN_004c1c50(err);
    return 0;
  }

  planeSector->type = ps.type;
  planeSector->value = ps.value;
  if (flags & 0x40000000) {
    planeSector->leftValue = ps.leftValue;
    planeSector->rightValue = ps.rightValue;
  } else {
    planeSector->leftValue = ps.value;
    planeSector->rightValue = ps.value;
  }

  if (ps.leftIsWorldSector) {
    if (!FUN_004c1600(stream, 9, 0, &version)) {
      result = 0;
    }
    if (result && ((version < 0x35000) || (version > 0x37002))) {
      RWERROR119(0x80000004);
      result = 0;
    }
    if (result && ((planeSector->leftSubTree = FUN_0048f580(stream, binaryWorldMallocAddr, world, flags)) == 0)) {
      result = 0;
    }
  } else {
    if (!FUN_004c1600(stream, 10, 0, &version)) {
      result = 0;
    }
    if (result && ((version < 0x35000) || (version > 0x37002))) {
      RWERROR119(0x80000004);
      result = 0;
    }
    if (result && ((planeSector->leftSubTree = FUN_0048fbd0(stream, binaryWorldMallocAddr, world, flags)) == 0)) {
      result = 0;
    }
  }

  if (result) {
    if (ps.rightIsWorldSector) {
      if (!FUN_004c1600(stream, 9, 0, &version)) {
        result = 0;
      }
      if (result && ((version < 0x35000) || (version > 0x37002))) {
        RWERROR119(0x80000004);
        result = 0;
      }
      if (result && ((planeSector->rightSubTree = FUN_0048f580(stream, binaryWorldMallocAddr, world, flags)) == 0)) {
        result = 0;
      }
    } else {
      if (!FUN_004c1600(stream, 10, 0, &version)) {
        result = 0;
      }
      if (result && ((version < 0x35000) || (version > 0x37002))) {
        RWERROR119(0x80000004);
        result = 0;
      }
      if (result && ((planeSector->rightSubTree = FUN_0048fbd0(stream, binaryWorldMallocAddr, world, flags)) == 0)) {
        result = 0;
      }
    }
  }

  if (result == 0) {
    if (planeSector->leftSubTree) {
      if (*(u8 *)((u8 *)world + 3) & 1) {
        FUN_00499720(planeSector->leftSubTree);
      } else {
        FUN_00499850(planeSector->leftSubTree);
      }
      planeSector->leftSubTree = 0;
    }
    return 0;
  }

  return planeSector;
}

/* P4: src/renderware/world/bameshop.c TriStripFollow (func_003c6c10).
   P4 state: -O4 default, schedule on.  The P4 build has TURNCORNERS defined
   and ODDTURNS/TRISTRIPLOOKAHEAD disabled, so the touchup keeps running with
   currentAttempt < 4, the odd strip length path ends the walk, and the
   lookahead calls are compiled out.  FUN_00496e80/FUN_00496f60 must be static
   so MWCC's interprocedural register information keeps the whole loop state
   in the t-registers the retail image uses. */
typedef struct TriStripListEntry119 {
  u16 *strip;
  u32 stripLen;
  u32 stripSize;
  struct TriStripListEntry119 *next;
} TriStripListEntry119;

#pragma optimization_level 4
#pragma schedule on
// FUN_00497130
u32 FUN_00497130(TriStripListEntry119 *strip, TriEdge119c *nextEdge, TriBinList119 *binListArray, void *triList, s32 currentAttempt)
{
  u32 addedTris = 0;
  TriEdge119c *prevEdge = 0;
  TriEdge119c *otherEdge = 0;
  s32 nextIsLast = 0;
  s32 otherIsLast = 0;
  s32 turnResult;

  while (nextEdge) {
    TriBinEntry119c *bestTri = 0;
    u16 v1;
    u16 v2;
    u16 v3 = 0;
    s32 nextEdgeIndex = -1;

    if (strip->stripLen % 2) {
      v1 = strip->strip[strip->stripLen - 1];
      v2 = strip->strip[strip->stripLen - 2];
    } else {
      v1 = strip->strip[strip->stripLen - 2];
      v2 = strip->strip[strip->stripLen - 1];
    }

    if (currentAttempt < 4) {
      if (nextEdge->tri1 && nextEdge->tri1->used2 == 0) {
        bestTri = nextEdge->tri1;
      } else if (nextEdge->tri2 && nextEdge->tri2->used2 == 0) {
        bestTri = nextEdge->tri2;
      }
    } else {
      if (nextEdge->tri1 && nextEdge->tri1->used == 0) {
        bestTri = nextEdge->tri1;
      } else if (nextEdge->tri2 && nextEdge->tri2->used == 0) {
        bestTri = nextEdge->tri2;
      }
    }

    if (!bestTri) {
      return addedTris;
    }

    addedTris++;

    FUN_00496f60(bestTri, binListArray, currentAttempt);

    if (nextEdge == bestTri->edge[0]) {
      nextEdgeIndex = 0;
    } else if (nextEdge == bestTri->edge[1]) {
      nextEdgeIndex = 1;
    } else if (nextEdge == bestTri->edge[2]) {
      nextEdgeIndex = 2;
    }

    if (bestTri->edge[(nextEdgeIndex + 1) % 3]->tri1 == bestTri) {
      v3 = bestTri->edge[(nextEdgeIndex + 1) % 3]->v2;
    } else {
      v3 = bestTri->edge[(nextEdgeIndex + 1) % 3]->v1;
    }

    prevEdge = nextEdge;
    nextEdge = (TriEdge119c *)FUN_00496e80((TriBinEntry119 *)bestTri, strip->strip[strip->stripLen - 1], v3);

    if (currentAttempt < 4) {
      turnResult = !nextEdge || (((nextEdge->tri1 && !nextEdge->tri1->used2) + (nextEdge->tri2 && !nextEdge->tri2->used2)) == 0) || nextIsLast;
    } else {
      turnResult = !nextEdge || (((nextEdge->tri1 && !nextEdge->tri1->used) + (nextEdge->tri2 && !nextEdge->tri2->used)) == 0) || nextIsLast;
    }

    if (turnResult) {
      if (bestTri->edge[0] != prevEdge && bestTri->edge[0] != nextEdge) {
        otherEdge = bestTri->edge[0];
      } else if (bestTri->edge[1] != prevEdge && bestTri->edge[1] != nextEdge) {
        otherEdge = bestTri->edge[1];
      } else if (bestTri->edge[2] != prevEdge && bestTri->edge[2] != nextEdge) {
        otherEdge = bestTri->edge[2];
      }

      if (currentAttempt < 4) {
        turnResult = (otherEdge && ((otherEdge->tri1 && !otherEdge->tri1->used2) + (otherEdge->tri2 && !otherEdge->tri2->used2)) && !(otherIsLast && nextIsLast));
      } else {
        turnResult = (otherEdge && ((otherEdge->tri1 && !otherEdge->tri1->used) + (otherEdge->tri2 && !otherEdge->tri2->used)) && !(otherIsLast && nextIsLast));
      }

      if (turnResult) {
        if (strip->stripLen % 2) {
          strip->strip[strip->stripLen] = v3;
          strip->stripLen++;
          nextEdge = 0;
        } else {
          strip->strip[strip->stripLen] = strip->strip[strip->stripLen - 2];
          strip->stripLen++;
          strip->strip[strip->stripLen] = v3;
          strip->stripLen++;
          nextEdge = otherEdge;
        }
      } else {
        strip->strip[strip->stripLen] = v3;
        strip->stripLen++;
        nextEdge = 0;
      }
    } else {
      strip->strip[strip->stripLen] = v3;
      strip->stripLen++;
    }
  }

  return addedTris;
}
