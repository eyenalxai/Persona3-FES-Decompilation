/* RenderWare Graphics 3.7 block, built with MWCCPS2 3.0.1 b119 (see
   config/compiler_units.txt).  Retail linked the RenderWare library as a
   prebuilt object; the Persona 4 tree carries matched source bodies of the
   same build, so functions whose b210 spelling cannot reach retail land here.
   Bodies keep the Persona 3 symbols and raw struct offsets; the comment above
   each names the Persona 4 twin they were ported from. */

#include "mw_harvest_compat.h"
#include "rw/rwplcore.h"
#include "rw/rwcore.h"

extern u32 FUN_004cdfe0(void *param_1, u32 param_2, u32 param_3);

/* P4: src/renderware/core/bacamera.c RwCameraShowRaster (func_003e82e0).
   dev/flags pass straight through in $a1/$a2; only the raster load is
   materialised.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C9ED0
void *FUN_004c9ed0(void *param_1, u32 param_2, u32 param_3)
{
  return FUN_004cdfe0(*(void **)((u8 *)param_1 + 0x60), param_2, param_3)
             ? param_1
             : 0;
}

/* P4: src/promoted/code1_003d_cw119.c func_003de280.  Table lookup with the
   index * 0x70 scaled as ((i << 3) - i) << 4; the two locals are what fixes
   the load/scale order in the positive branch.  P4 state: schedule on,
   no_branch_likely on. */
#pragma schedule on
#pragma no_branch_likely on
// FUN_004C0830
u32 FUN_004c0830(u8 *param_1, u32 param_2)
{
  u32 base;
  u32 offset;

  if (!(param_2 < *(u32 *)(param_1 + 4)))
    goto zero;
  offset = param_2 << 3;
  offset -= param_2;
  offset <<= 4;
  base = *(u32 *)(param_1 + 0x58);
  return base + offset;
zero:
  return 0;
}

/* P4: src/renderware/plcore/baerr.c RwErrorGet (func_003df550).  The 8-byte
   error global is copied with two single-precision moves, so the copy is
   spelled as a struct assignment.  RwEngineInstance is absolute (lui/addiu)
   while errorModule.globalsOffset stays gp-relative; the offset must be a
   struct field for b119's register allocation to pick $a1/$a0 as retail does.
   P4 state: schedule on (no explicit level, so the unit's -O4,p applies). */
typedef struct {
  s32 pluginID;
  s32 errorCode;
} RwErrorB119;

typedef struct {
  RwErrorB119 errorCode;
} rwErrorGlobalsB119;

typedef struct {
  s32 globalsOffset;
  s32 numInstances;
} RwModuleInfoB119;

extern RwModuleInfoB119 iGpffffbbe0;
extern u8 DAT_00960070[];

#define RWPLUGINOFFSETB119(_type, _base, _offset) \
  ((_type *)((u8 *)(_base) + (_offset)))

#define RWERRORGLOBALB119(var) \
  (RWPLUGINOFFSETB119(rwErrorGlobalsB119, DAT_00960070, iGpffffbbe0.globalsOffset)->var)

#pragma schedule on
// FUN_004C1CD0
RwErrorB119 *FUN_004c1cd0(RwErrorB119 *code)
{
  *code = RWERRORGLOBALB119(errorCode);
  RWERRORGLOBALB119(errorCode).pluginID = 0x0;
  RWERRORGLOBALB119(errorCode).errorCode = (s32)0x80000000L;
  return code;
}

/* P4: src/renderware/plcore/bamatrix.c _rwMatrixSetMultFn (func_003e00f0).
   matrixModule.globalsOffset is the gp-relative offset variable at
   0x7ce8d8 (rwMatrixTolerancesOffset); multMatrix sits at +8 in the matrix
   plugin struct.  The NULL default is the out-of-line MatrixMultiply
   (FUN_004c2200), whose address is absolute.  P4 state: schedule on. */
typedef struct {
  void *matrixFreeList;     /* +0x00 */
  u32 matrixOptimizations;  /* +0x04 */
  void *multMatrix;         /* +0x08 */
} rwMatrixGlobalsB119;

extern RwModuleInfoB119 rwMatrixTolerancesOffset;
void FUN_004c2200(RwMatrix *param_1, const RwMatrix *param_2,
                  const RwMatrix *param_3);

#pragma schedule on
// FUN_004C2A30
u32 FUN_004c2a30(void *param_1)
{
  if (param_1 == 0)
    goto fallback;
body:
  ((rwMatrixGlobalsB119 *)((u8 *)DAT_00960070 + rwMatrixTolerancesOffset.globalsOffset))->multMatrix = param_1;
  goto done;
fallback:
  param_1 = (void *)FUN_004c2200;
  goto body;
done:
  return 1;
}

/* P4: src/renderware/plcore/batkreg.c rwDestroyEntry (func_003e3680).  The
   free-list hook is RWSRCGLOBAL(memoryFree), i.e. a function pointer at
   +0x11c in the engine globals; the registry pointer is re-read for each
   store because the entry write could alias it.  P4 state: schedule on. */
typedef struct RwPluginRegistryB119 RwPluginRegistryB119;
typedef struct RwPluginRegEntryB119 RwPluginRegEntryB119;

struct RwPluginRegistryB119 {
  s32 sizeOfStruct;                    /* +0x00 */
  s32 origSizeOfStruct;                /* +0x04 */
  s32 maxSizeOfStruct;                 /* +0x08 */
  s32 staticAlloc;                     /* +0x0c */
  RwPluginRegEntryB119 *firstRegEntry; /* +0x10 */
  RwPluginRegEntryB119 *lastRegEntry;  /* +0x14 */
};

struct RwPluginRegEntryB119 {
  s32 offset;                          /* +0x00 */
  s32 size;                            /* +0x04 */
  u32 pluginID;                        /* +0x08 */
  void *readCB;                        /* +0x0c */
  void *writeCB;                       /* +0x10 */
  void *getSizeCB;                     /* +0x14 */
  void *alwaysCB;                      /* +0x18 */
  void *rightsCB;                      /* +0x1c */
  void *constructCB;                   /* +0x20 */
  void *destructCB;                    /* +0x24 */
  void *copyCB;                        /* +0x28 */
  void *errStrCB;                      /* +0x2c */
  RwPluginRegEntryB119 *nextRegEntry;  /* +0x30 */
  RwPluginRegEntryB119 *prevRegEntry;  /* +0x34 */
  RwPluginRegistryB119 *parentRegistry;/* +0x38 */
};

typedef struct {
  void *curCamera;                         /* +0x00 */
  u8 pad0[0x14];                           /* +0x04..+0x17 */
  float zBufferNear;                       /* +0x18 */
  float zBufferFar;                        /* +0x1c */
  u8 pad0b[0x9c];                          /* +0x20..+0xbb */
  void *stdFuncBeginUpdate;                /* +0xbc */
  u8 pad1[0x34];
  u32 (*stringFuncs_strlen)(const char *); /* +0xf4 */
  u8 pad2[0x10];                           /* +0xf8..+0x107 */
  void *(*memoryFuncs_rwmalloc)(u32, u32); /* +0x108 */
  void (*memoryFuncs_rwfree)(void *);      /* +0x10c */
  void *(*memoryFuncs_rwrealloc)(void *, u32, u32); /* +0x110 */
  u8 pad3[0x4];                            /* +0x114..+0x117 */
  void *(*memoryAlloc)(void *, u32);       /* +0x118 */
  void (*memoryFree)(void *, void *);      /* +0x11c */
  u8 pad4a[0x4];                           /* +0x120..+0x123 */
  u32 engineStatus;                        /* +0x124 */
  u8 pad4b[0x70];                          /* +0x128..+0x197 */
  u32 resArenaInitSize;                    /* +0x198 */
} RwGlobalsB119;

#define RWSRCGLOBALB119(var) (((RwGlobalsB119 *)DAT_00960070)->var)

#pragma schedule on
// FUN_004C5FC0
void FUN_004c5fc0(void *param_1, void *param_2)
{
  RwPluginRegEntryB119 *entry = (RwPluginRegEntryB119 *)param_1;

  if (entry->parentRegistry->firstRegEntry != 0) {
    entry->parentRegistry->sizeOfStruct = entry->parentRegistry->origSizeOfStruct;
    entry->parentRegistry->firstRegEntry = 0;
    entry->parentRegistry->lastRegEntry = 0;
  }
  RWSRCGLOBALB119(memoryFree)(param_2, entry);
}

/* P4: src/renderware/plcore/batkreg.c _rwPluginRegistryGetPluginOffset
   (func_003e3830).  Walk the plugin registry's entry list: pluginID at +8,
   offset at +0, nextRegEntry at +0x30; miss returns -1.  P4 state:
   schedule on. */
#pragma schedule on
// FUN_004C6170
u32 FUN_004c6170(u8 *param_1, u32 param_2)
{
  u32 *puVar1;

  puVar1 = *(u32 **)(param_1 + 0x10);
  if (puVar1 != 0) {
    do {
      if (puVar1[2] == param_2)
        return *puVar1;
      puVar1 = (u32 *)puVar1[0xc];
    } while (puVar1 != 0);
  }
  return 0xffffffff;
}

/* P4: src/renderware/plcore/batkbin.c _rwPluginRegistryAddPluginStream
   (func_003e3020).  Find the entry, then fill in the stream callbacks;
   miss returns -1.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C5960
s32 FUN_004c5960(RwPluginRegistryB119 *param_1, u32 param_2, void *param_3,
                 void *param_4, void *param_5)
{
  RwPluginRegEntryB119 *entry;

  entry = param_1->firstRegEntry;
  while (entry) {
    if (entry->pluginID == param_2)
      break;
    entry = entry->nextRegEntry;
  }

  if (entry) {
    entry->readCB = param_3;
    entry->writeCB = param_4;
    entry->getSizeCB = param_5;
    return entry->offset;
  }
  return -1;
}

/* P4: src/renderware/plcore/batkbin.c _rwPluginRegistryAddPlgnStrmlwysCB
   (func_003e3070).  Same walk, alwaysCB store.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C59B0
s32 FUN_004c59b0(RwPluginRegistryB119 *param_1, u32 param_2, void *param_3)
{
  RwPluginRegEntryB119 *entry;

  entry = param_1->firstRegEntry;
  while (entry) {
    if (entry->pluginID == param_2)
      break;
    entry = entry->nextRegEntry;
  }

  if (entry) {
    entry->alwaysCB = param_3;
    return entry->offset;
  }
  return -1;
}

/* P4: src/renderware/plcore/batkbin.c _rwPluginRegistryAddPlgnStrmRightsCB
   (func_003e30c0).  Same walk, rightsCB store.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C5A00
s32 FUN_004c5a00(RwPluginRegistryB119 *param_1, u32 param_2, void *param_3)
{
  RwPluginRegEntryB119 *entry;

  entry = param_1->firstRegEntry;
  while (entry) {
    if (entry->pluginID == param_2)
      break;
    entry = entry->nextRegEntry;
  }

  if (entry) {
    entry->rightsCB = param_3;
    return entry->offset;
  }
  return -1;
}

/* P4: src/renderware/plcore/rwstring.c StrChr (func_003e4920).  The match is
   cached in a char local and the terminator test uses the cached value; the
   result is carried in the ptr/constptr union, whose 32-bit member gives
   retail's final sign-extension.  P4 state: schedule on. */
typedef union {
  char *ptrChar;
  const char *constptrChar;
} RwPtrCharB119;

#pragma schedule on
// FUN_004C7260
char *FUN_004c7260(char *param_1, int param_2)
{
  RwPtrCharB119 result;
  char match = (char)param_2;
  char cVar2;

  result.constptrChar = 0;
  do {
    cVar2 = *param_1;
    if (cVar2 == match) {
      result.constptrChar = param_1;
      break;
    }
    param_1++;
  } while (cVar2);
  return result.ptrChar;
}

/* P4: src/renderware/plcore/rwstring.c StrRChr (func_003e4960).  Same loop,
   but the last match wins.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C72A0
char *FUN_004c72a0(char *param_1, int param_2)
{
  RwPtrCharB119 result;
  char match = (char)param_2;
  char cVar2;

  result.constptrChar = 0;
  do {
    cVar2 = *param_1;
    if (cVar2 == match)
      result.constptrChar = param_1;
    param_1++;
  } while (cVar2);
  return result.ptrChar;
}

/* P4: src/renderware/plcore/rwstring.c StrUpr (func_003e4880).  P4 state:
   schedule on. */
#pragma schedule on
// FUN_004C71C0
char *FUN_004c71c0(char *param_1)
{
  char *p;

  if (param_1) {
    p = param_1;
    while (*p) {
      char c = *p;

      if ((c >= 'a') && (c <= 'z')) {
        c += 'A' - 'a';
        *p = c;
      }
      p++;
    }
  }
  return param_1;
}

/* P4: src/renderware/plcore/rwstring.c StrLwr (func_003e48d0).  P4 state:
   schedule on. */
#pragma schedule on
// FUN_004C7210
char *FUN_004c7210(char *param_1)
{
  char *p;

  if (param_1) {
    p = param_1;
    while (*p) {
      char c = *p;

      if ((c >= 'A') && (c <= 'Z')) {
        c += 'a' - 'A';
        *p = c;
      }
      p++;
    }
  }
  return param_1;
}

/* P4: src/renderware/core/bacamera.c RwCameraSetNearClipPlane (func_003e8180).
   The near-plane store lands in the jal delay slot; the parent frame is
   re-read from the camera after CameraUpdateZShiftScale.  P4 state:
   schedule on. */
extern RwCamera *FUN_004c89a0(RwCamera *param_1); /* CameraUpdateZShiftScale */

#pragma schedule on
// FUN_004C9D70
RwCamera *FUN_004c9d70(RwCamera *param_1, float param_2)
{
  RwFrame *frame;

  param_1->nearPlane = param_2;
  FUN_004c89a0(param_1);
  frame = (RwFrame *)param_1->object.object.parent;
  if (frame)
    FUN_004cb270((u8 *)frame);
  return param_1;
}

/* P4: src/renderware/core/bacamera.c RwCameraSetFarClipPlane (func_003e81c0).
   Far-plane twin of FUN_004c9d70.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C9DB0
RwCamera *FUN_004c9db0(RwCamera *param_1, float param_2)
{
  RwFrame *frame;

  param_1->farPlane = param_2;
  FUN_004c89a0(param_1);
  frame = (RwFrame *)param_1->object.object.parent;
  if (frame)
    FUN_004cb270((u8 *)frame);
  return param_1;
}

/* P4: src/renderware/plcore/bamatrix.c _rwMatrixDeterminant (func_003e0130).
   cross(up, at) . right expanded over the implicit final column; the macro
   order (up x at, then the dot product) is what fixes the FP register
   assignment.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C2A70
float FUN_004c2a70(const float *param_1)
{
  RwV3d cross;
  const RwV3d *mx = (const RwV3d *)param_1;
  const RwV3d *my = (const RwV3d *)(param_1 + 4);
  const RwV3d *mz = (const RwV3d *)(param_1 + 8);

  cross.x = (my->y * mz->z) - (my->z * mz->y);
  cross.y = (my->z * mz->x) - (my->x * mz->z);
  cross.z = (my->x * mz->y) - (my->y * mz->x);
  return (((cross.x * mx->x) + (cross.y * mx->y)) + (cross.z * mx->z));
}

typedef struct rwLLLinkB119 rwLLLinkB119;
struct rwLLLinkB119 {
  rwLLLinkB119 *next;
  rwLLLinkB119 *prev;
};

typedef struct {
  rwLLLinkB119 *next;
  rwLLLinkB119 *prev;
} rwLinkListB119;

/* P4: src/renderware/plcore/baresour.c RwResourcesGetArenaUsage
   (func_003e23e0).  res.usedEntries (+0x24) holds the sentinel link pointer,
   res.reusageSize is +8 and each entry's size is at link+8 (the RwResEntry
   link is first).  P4 state: schedule on. */
extern s32 DAT_007ce8f0;

typedef struct {
  s32 maxSize;                  /* +0x00 */
  s32 currentSize;              /* +0x04 */
  s32 reusageSize;              /* +0x08 */
  void *memHeap;                /* +0x0c */
  rwLinkListB119 entriesA;      /* +0x10 */
  rwLinkListB119 entriesB;      /* +0x18 */
  rwLinkListB119 *freeEntries;  /* +0x20 */
  rwLinkListB119 *usedEntries;  /* +0x24 */
} rwResourcesB119;

#pragma schedule on
// FUN_004C4D20
s32 FUN_004c4d20(void)
{
  rwResourcesB119 *res = (rwResourcesB119 *)((u8 *)DAT_00960070 + DAT_007ce8f0);
  void *end;
  void *cur;
  s32 usage;

  usage = res->reusageSize;
  end = res->usedEntries;
  cur = *(void **)end;
  while (cur != end) {
    usage += *(s32 *)((u8 *)cur + 8);
    cur = *(void **)cur;
  }
  return usage;
}

/* P4: src/renderware/plcore/rwstring.c _rwStringStreamGetSize (func_003e4ad0).
   NULL strings fall back to nullString at 0x7bcbe8 (referenced as a symbol so
   the lui/addiu pair matches retail); the length call goes through
   RWSRCGLOBAL(stringFuncs).strlen (+0xf4).  P4 state: schedule on. */
extern u8 D_007BCBE8[];

#pragma schedule on
// FUN_004C7410
u32 FUN_004c7410(const char *param_1)
{
  u32 len;

  if (param_1 == 0)
    param_1 = (const char *)D_007BCBE8;
  len = RWSRCGLOBALB119(stringFuncs_strlen)(param_1);
  return (len + 4) & 0xfffffffc;
}

/* P4: src/renderware/core/babinfrm.c _rwFrameListDeinitialize
   (func_003e59e0).  RwFree is RWSRCGLOBAL(memoryFuncs).rwfree (+0x10c); the
   frames pointer load sits in the jalr delay slot.  P4 state: schedule on,
   always_inline off. */
typedef struct {
  void *frames;   /* +0x00 */
  s32 numFrames;  /* +0x04 */
} rwFrameListB119;

#pragma schedule on
// FUN_004C7D30
rwFrameListB119 *FUN_004c7d30(rwFrameListB119 *param_1)
{
  if (param_1->numFrames != 0)
    RWSRCGLOBALB119(memoryFuncs_rwfree)(param_1->frames);
  return param_1;
}

/* P4: src/renderware/core/bacamera.c RwCameraSetViewOffset (func_003e8130).
   viewOffset (+0x78) is copied with two single-precision moves.  P4 state:
   schedule on. */
#pragma schedule on
// FUN_004C9D20
RwCamera *FUN_004c9d20(RwCamera *param_1, const RwV2d *param_2)
{
  RwFrame *frame;

  param_1->viewOffset = *param_2;
  frame = (RwFrame *)param_1->object.object.parent;
  if (frame)
    FUN_004cb270((u8 *)frame);
  return param_1;
}

/* P4: src/renderware/plcore/baplcore.c RwEngineGetVideoModeInfo
   (func_003e8970).  The device request gets the address of RwGlobals'
   dOpenDevice field (+0x10) and the mode index as its fifth argument.
   P4 state: schedule on. */
extern u32 FUN_004ca3e0(void *param_1, u32 param_2, void *param_3, void * param_4,
                        u32 param_5);

#pragma schedule on
// FUN_004CA560
void *FUN_004ca560(void *param_1, u32 param_2)
{
  u32 ok;

  ok = FUN_004ca3e0((void *)(DAT_00960070 + 0x10), 6, param_1, 0, param_2);
  if (ok == 0)
    param_1 = 0;
  return param_1;
}

/* P4: src/renderware/plcore/baplcore.c RwEngineGetCurrentVideoMode
   (func_003e89c0).  Same device request as FUN_004ca560 with request code 10
   writing the current mode through the third argument; -1 on failure.
   P4 state: schedule on. */
#pragma schedule on
// FUN_004CA5B0
s32 FUN_004ca5b0(void)
{
  s32 curMode;

  if (FUN_004ca3e0((void *)(DAT_00960070 + 0x10), 10, &curMode, 0, 0) != 0)
    return curMode;
  return -1;
}

/* P4: src/renderware/plcore/babinary.c _rwStreamWriteVersionedChunkHeader
   (func_003deff0).  The mark is a 12-byte {type, length, packedLibraryID}
   record written through RwStreamWrite (FUN_004c53f0); the version/build
   packing is RWLIBRARYIDPACK.  P4 state: schedule on. */
typedef struct {
  s32 type;      /* +0x00 */
  s32 length;    /* +0x04 */
  u32 libraryID; /* +0x08 */
} rwMarkB119;

extern u32 FUN_004c53f0(void *param_1, void *param_2, u32 param_3);

extern u32 FUN_004c15a0(void *param_1, u32 param_2, u32 param_3, u32 param_4,
                        u32 param_5);

/* P4: src/renderware/plcore/bamatrix.c _rwMatrixOrthogonalError
   (func_003e0180).  dot = (up.at, at.right, right.up); the result is
   dot.dot, computed in that order.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C2AC0
float FUN_004c2ac0(const float *param_1)
{
  const RwV3d *mx = (const RwV3d *)param_1;
  const RwV3d *my = (const RwV3d *)(param_1 + 4);
  const RwV3d *mz = (const RwV3d *)(param_1 + 8);
  RwV3d dot;

  dot.x = (my->x * mz->x) + (my->y * mz->y) + (my->z * mz->z);
  dot.y = (mz->x * mx->x) + (mz->y * mx->y) + (mz->z * mx->z);
  dot.z = (mx->x * my->x) + (mx->y * my->y) + (mx->z * my->z);
  return (dot.x * dot.x) + (dot.y * dot.y) + (dot.z * dot.z);
}

/* P4: src/renderware/plcore/baresour.c _rwResourcesOpen (func_003e1db0).
   resourcesModule.globalsOffset/numInstances are the gp-relative scalars at
   0x7ce8f0/0x7ce8f4 (declared as plain s32 so the store stays %gp_rel); the
   arena size comes from RwGlobals.resArenaInitSize (+0x198).  P4 state:
   schedule on. */
extern u32 DAT_007ce8f4;
extern rwResourcesB119 *FUN_004c45f0(rwResourcesB119 *param_1, u32 param_2);

#pragma schedule on
// FUN_004C46F0
void *FUN_004c46f0(void *param_1, u32 param_2)
{
  DAT_007ce8f0 = param_2;

  if (!FUN_004c45f0((rwResourcesB119 *)((u8 *)DAT_00960070 + param_2),
                    RWSRCGLOBALB119(resArenaInitSize)))
    return 0;

  DAT_007ce8f4 = DAT_007ce8f4 + 1;
  return param_1;
}

/* P4: src/renderware/plcore/resmem.c _rwResHeapInit (func_003e44b0).  The
   heap header is 8 bytes, so the first block starts at (heap + 8 + 31) & ~31;
   the block header holds heap/next/prev/size/flags at +0/+4/+8/+0xc/+0x10.
   P4 state: schedule on. */
#pragma schedule on
// FUN_004C6DF0
u32 FUN_004c6df0(u8 *param_1, u32 param_2)
{
  u32 start;
  u32 end;
  s32 blockSize;
  u32 *firstBlock;

  start = ((u32)param_1 + 0x27U) & 0xffffffe0U;
  end = ((u32)param_1 + param_2) & 0xffffffe0U;
  blockSize = (s32)(end - start) - 0x20;

  if (blockSize < 32)
    return 0;

  firstBlock = (u32 *)start;
  firstBlock[0] = (u32)param_1;
  firstBlock[1] = 0;
  firstBlock[2] = 0;
  firstBlock[4] = 0;
  firstBlock[3] = (u32)blockSize;

  ((u32 *)param_1)[0] = start;
  ((u32 *)param_1)[1] = start;
  return 1;
}

/* P4: src/renderware/core/bacamera.c CameraBeginUpdate (func_003e7fb0).
   curCamera is the first RwGlobals field, the begin-update hook sits at
   +0xbc; the curCamera store schedules into the _rwFrameSyncDirty jal delay
   slot.  P4 state: schedule on. */
extern void FUN_004cf340(void);
extern void FUN_004f28e0(void *param_1);

#pragma schedule on
// FUN_004C9BA0
void *FUN_004c9ba0(void *param_1)
{
  void *beginUpdateFunc;
  u32 ok;

  RWSRCGLOBALB119(curCamera) = param_1;
  FUN_004cf340();

  beginUpdateFunc = RWSRCGLOBALB119(stdFuncBeginUpdate);
  ok = ((u32(*)(void *, void *, u32))beginUpdateFunc)(0, param_1, 0);
  if (ok == 0)
    return 0;

  FUN_004f28e0(param_1);
  return param_1;
}

/* P4: src/renderware/plcore/balist.c _rwSListDestroy (func_003df7f0).  The
   element array is freed first (its pointer is loaded into $a0 before the
   guards), then the list itself; both through
   RWSRCGLOBAL(memoryFuncs).rwfree.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C20B0
u32 FUN_004c20b0(u8 *param_1)
{
  if ((*(u32 *)param_1 != 0) && (*(u32 *)(param_1 + 8) != 0)) {
    RWSRCGLOBALB119(memoryFuncs_rwfree)(*(void **)param_1);
    *(u32 *)param_1 = 0;
    *(u32 *)(param_1 + 8) = 0;
  }

  RWSRCGLOBALB119(memoryFuncs_rwfree)(param_1);
  return 1;
}

/* P4: src/renderware/plcore/bamatrix.c _rwMatrixNormalError (func_003e01e0).
   dot = (|x|^2-1, |y|^2-1, |z|^2-1); the result is dot.dot.  P4 state:
   schedule on. */
#pragma schedule on
// FUN_004C2B20
float FUN_004c2b20(const float *param_1)
{
  const RwV3d *x = (const RwV3d *)param_1;
  const RwV3d *y = (const RwV3d *)(param_1 + 4);
  const RwV3d *z = (const RwV3d *)(param_1 + 8);
  RwV3d dot;

  dot.x = (x->x * x->x) + (x->y * x->y) + (x->z * x->z) - 1.0f;
  dot.y = (y->x * y->x) + (y->y * y->y) + (y->z * y->z) - 1.0f;
  dot.z = (z->x * z->x) + (z->y * z->y) + (z->z * z->z) - 1.0f;
  return (dot.x * dot.x) + (dot.y * dot.y) + (dot.z * dot.z);
}

/* P4: src/renderware/plcore/batkreg.c _rwPluginRegistryDeInitObject
   (func_003e3c20).  Walk the registry backwards calling each destructor with
   (object, offset, size).  P4 state: schedule on. */
#pragma schedule on
// FUN_004C6560
RwPluginRegistryB119 *FUN_004c6560(RwPluginRegistryB119 *param_1, void *param_2)
{
  RwPluginRegEntryB119 *entry;

  for (entry = param_1->lastRegEntry; entry != 0; entry = entry->prevRegEntry) {
    ((void (*)(void *, s32, s32))entry->destructCB)(param_2, entry->offset,
                                                    entry->size);
  }
  return param_1;
}

/* P4: src/renderware/plcore/batkreg.c _rwPluginRegistryCopyObject
   (func_003e3c90).  Walk forwards calling each copy callback with
   (dstObject, srcObject, offset, size).  P4 state: schedule on. */
#pragma schedule on
// FUN_004C65D0
RwPluginRegistryB119 *FUN_004c65d0(RwPluginRegistryB119 *param_1, void *param_2,
                                   void *param_3)
{
  RwPluginRegEntryB119 *entry;

  entry = param_1->firstRegEntry;
  while (entry != 0) {
    ((void (*)(void *, void *, s32, s32))entry->copyCB)(param_2, param_3,
                                                        entry->offset,
                                                        entry->size);
    entry = entry->nextRegEntry;
  }
  return param_1;
}

/* P4: src/renderware/core/babintex.c RwTextureStreamGetSize (func_003e6240).
   sizeof(rwStreamTexture) + chunk header is 0x10, and the name, mask and
   extension chunks each add their own 0xc-byte header.  P4 state:
   schedule on. */
extern u8 D_0077E6D0[];
extern u32 FUN_004c5cb0(RwPluginRegistryB119 *param_1, const void *param_2);

#pragma schedule on
#pragma dont_inline on
// FUN_004C81D0
u32 FUN_004c81d0(const u8 *param_1)
{
  u32 size;

  size = 0x10;
  size += FUN_004c7410((const char *)(param_1 + 0x10)) + 0xc;
  size += FUN_004c7410((const char *)(param_1 + 0x30)) + 0xc;
  size += FUN_004c5cb0((void *)D_0077E6D0, param_1) + 0xc;
  return size;
}
#pragma dont_inline off

/* P4: src/renderware/core/bacamera.c CameraSync (func_003e7ee0).  The
   projection builders are called with the camera left in $a0; the frustum
   bbox is rebuilt from the 8 frustum corners at +0x124 into +0x10c.
   P4 state: schedule on. */
extern void FUN_004c9270(void *param_1);
extern void FUN_004c8a60(void *param_1);
extern void FUN_004c9940(void *param_1);
extern void FUN_004c9400(void *param_1);

typedef struct {
  float x;
  float y;
  float z;
} RwV3dB119;

typedef struct {
  RwV3dB119 sup; /* +0x00 */
  RwV3dB119 inf; /* +0x0c */
} RwBBoxB119;

extern RwBBoxB119 *FUN_004c7a50(RwBBoxB119 *param_1, const RwV3dB119 *param_2,
                                s32 param_3);

#pragma schedule on
// FUN_004C9AD0
void *FUN_004c9ad0(void *param_1)
{
  if (*(s32 *)((u8 *)param_1 + 0x14) == 1) {
    FUN_004c9270(param_1);
    FUN_004c8a60(param_1);
  } else {
    FUN_004c9940(param_1);
    FUN_004c9400(param_1);
  }

  FUN_004c7a50((RwBBoxB119 *)((u8 *)param_1 + 0x10c),
               (const RwV3dB119 *)((u8 *)param_1 + 0x124), 8);
  return param_1;
}

/* P4: src/renderware/plcore/babinary.c RwStreamReadChunkHeaderInfo
   (func_003df3c0).  _rwStreamReadChunkHeader fills the four locals, which are
   copied into the header record; isComplex is derived from the completed
   record by FUN_004c12d0.  P4 state: schedule on. */
extern u32 FUN_004c1450(u32 param_1, void *param_2, void *param_3, void *param_4,
                        void *param_5);
extern u32 FUN_004c12d0(void *param_1);

#pragma schedule on
// FUN_004C1970
u32 FUN_004c1970(u32 param_1, u8 *param_2)
{
  u32 readType;
  u32 readLength;
  u32 readVersion;
  u32 readBuildNum;
  u32 isComplex;

  if (FUN_004c1450(param_1, &readType, &readLength, &readVersion,
                   &readBuildNum) == 0)
    return 0;

  *(u32 *)(param_2 + 0x00) = readType;
  *(u32 *)(param_2 + 0x04) = readLength;
  *(u32 *)(param_2 + 0x08) = readVersion;
  *(u32 *)(param_2 + 0x0c) = readBuildNum;
  isComplex = FUN_004c12d0(param_2);
  *(u32 *)(param_2 + 0x10) = isComplex;
  return param_1;
}

/* P4: src/renderware/plcore/baerr.c RwErrorSet (func_003df4f0).  Only latch
   the new error when the current slot is empty; a common error (bit 31 set)
   clears the plugin id.  P4 state: schedule on. */
#pragma schedule on
#pragma dont_inline on
// FUN_004C1C50
RwErrorB119 *FUN_004c1c50(RwErrorB119 *param_1)
{
  if ((RWERRORGLOBALB119(errorCode).pluginID == 0) &&
      (RWERRORGLOBALB119(errorCode).errorCode == (s32)0x80000000L)) {
    if ((param_1->errorCode & 0x80000000) == 0)
      RWERRORGLOBALB119(errorCode).pluginID = param_1->pluginID;
    else
      RWERRORGLOBALB119(errorCode).pluginID = 0;
    RWERRORGLOBALB119(errorCode).errorCode = param_1->errorCode;
  }
  return param_1;
}
#pragma dont_inline off

/* P4: src/renderware/plcore/bamemory.c _rwMemoryClose (func_003e1c30).  The
   static _rwFreeListModuleClose is inlined in retail, including the inlined
   RwFreeListDestroy link removals around each _RwFreeListFree
   (FUN_004c3b70).  P4 state: schedule on. */
extern rwLinkListB119 DAT_007ce8e8; /* _freeListList */
extern u8 *DAT_007ce8e4;          /* _masterFreeListPtr */
extern u32 DAT_007ce8e0;          /* _freeListModuleOpen */

/* P4: RwFreeList, include/rw/plcore/bamemory.h; blockList at +0x10 and
   flags at +0x18, the module link at +0x1c. */
typedef struct {
  u32 entrySize;            /* +0x00 */
  u32 entriesPerBlock;      /* +0x04 */
  u32 heapSize;             /* +0x08 */
  u32 alignment;            /* +0x0c */
  rwLinkListB119 blockList; /* +0x10 */
  u32 flags;                /* +0x18 */
  rwLLLinkB119 link;        /* +0x1c */
} rwFreeListB119;

extern void FUN_004c3b70(rwFreeListB119 *param_1);

#pragma schedule on
#pragma dont_inline on
// FUN_004C4570
void FUN_004c4570(void)
{
  rwLLLinkB119 *link;
  rwLLLinkB119 *lastLink;
  rwLLLinkB119 *freeListLink;
  u8 *freeList;

  link = DAT_007ce8e8.next;
  lastLink = (rwLLLinkB119 *)&DAT_007ce8e8;
  while (link != lastLink) {
    freeListLink = link;
    freeListLink->prev->next = freeListLink->next;
    freeListLink->next->prev = freeListLink->prev;
    FUN_004c3b70((rwFreeListB119 *)((u8 *)link - 0x1c));
    link = DAT_007ce8e8.next;
    lastLink = (rwLLLinkB119 *)&DAT_007ce8e8;
  }

  freeList = DAT_007ce8e4;
  freeListLink = (rwLLLinkB119 *)(freeList + 0x1c);
  freeListLink->prev->next = freeListLink->next;
  freeListLink->next->prev = freeListLink->prev;
  FUN_004c3b70((rwFreeListB119 *)freeList);
  DAT_007ce8e4 = 0;
  DAT_007ce8e0 = 0;
}
#pragma dont_inline off

/* P4: src/renderware/plcore/batkbin.c _rwPluginRegistryInvokeRights
   (func_003e32f0).  Find the entry, require a rightsCB and a non-zero result
   (movz-shaped); the extra data stays in $a3.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C5C30
const RwPluginRegistryB119 *FUN_004c5c30(const RwPluginRegistryB119 *param_1,
                                           u32 param_2, void *param_3,
                                           u32 param_4)
{
  RwPluginRegEntryB119 *entry;
  u32 ok;

  entry = param_1->firstRegEntry;
  while (entry) {
    if (entry->pluginID == param_2)
      break;
    entry = entry->nextRegEntry;
  }

  if ((entry != 0) && (entry->rightsCB != 0)) {
    ok = ((u32 (*)(void *, s32, s32, u32))entry->rightsCB)(param_3,
                                                           entry->offset,
                                                           entry->size,
                                                           param_4);
    if (ok != 0)
      return param_1;
    return 0;
  }
  return 0;
}

/* P4: src/renderware/plcore/batkbin.c _rwPluginRegistryGetSize
   (func_003e3370).  Sum (size + chunk header) over the entries that report a
   positive size.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C5CB0
u32 FUN_004c5cb0(RwPluginRegistryB119 *param_1, const void *param_2)
{
  s32 size = 0;
  RwPluginRegEntryB119 *entry;
  s32 thisSize;

  entry = param_1->firstRegEntry;
  while (entry != 0) {
    if (entry->getSizeCB != 0) {
      thisSize = ((s32 (*)(const void *, s32, s32))entry->getSizeCB)(param_2,
                                                                      entry->offset,
                                                                      entry->size);
      if (thisSize > 0)
        size += thisSize + 0xc;
    }
    entry = entry->nextRegEntry;
  }
  return size;
}

/* P4: src/renderware/plcore/bavector.c VectorMultVector (func_003e3f00).  The
   scale/image half-products are what make retail's mul.s/madd.s chain; the
   incremental assignment order must be kept.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C6840
RwV3d *FUN_004c6840(RwV3d *param_1, const RwV3d *param_2, const RwMatrix *param_3)
{
  RwReal scale;
  RwReal imageX;
  RwReal imageY;
  RwReal imageZ;

  scale = param_2->x;
  imageX = (scale) * (param_3->right.x);
  imageY = (scale) * (param_3->right.y);
  imageZ = (scale) * (param_3->right.z);

  scale = param_2->y;
  imageX = (imageX) + ((scale) * (param_3->up.x));
  imageY = (imageY) + ((scale) * (param_3->up.y));
  imageZ = (imageZ) + ((scale) * (param_3->up.z));

  scale = param_2->z;
  param_1->x = ((scale) * (param_3->at.x)) + (imageX);
  param_1->y = ((scale) * (param_3->at.y)) + (imageY);
  param_1->z = ((scale) * (param_3->at.z)) + (imageZ);
  return param_1;
}

/* P4: src/renderware/plcore/baresour.c _rwResourcesClose (func_003e1e10).  The
   res globals offset is re-read from the gp scalar around each call; memHeap
   sits at +0xc in the resource globals.  P4 state: schedule on. */
extern u32 FUN_004c4d70(void);
extern void FUN_004c6e50(void *param_1);

#define RWRESOURCESGLOBALB119(var) \
  (((rwResourcesB119 *)((u8 *)DAT_00960070 + DAT_007ce8f0))->var)

#pragma schedule on
// FUN_004C4750
void *FUN_004c4750(void *param_1)
{
  FUN_004c4d70();

  if (RWRESOURCESGLOBALB119(memHeap) != 0) {
    FUN_004c6e50(RWRESOURCESGLOBALB119(memHeap));
    RWSRCGLOBALB119(memoryFuncs_rwfree)(RWRESOURCESGLOBALB119(memHeap));
    RWRESOURCESGLOBALB119(memHeap) = 0;
  }

  DAT_007ce8f4 = DAT_007ce8f4 - 1;
  return param_1;
}

/* P4: src/renderware/plcore/resmem.c splitBlock (func_003e4420).  The heap
   block header is 0x20 bytes with heap/next/prev/size/flags at
   +0/+4/+8/+0xc/+0x10; the "next block is free" test drives the merge branch.
   P4 state: schedule on. */
typedef struct rwResHeapBlockHeaderB119 rwResHeapBlockHeaderB119;

struct rwResHeapBlockHeaderB119 {
  void *heap;                     /* +0x00 */
  rwResHeapBlockHeaderB119 *next; /* +0x04 */
  rwResHeapBlockHeaderB119 *prev; /* +0x08 */
  s32 size;                       /* +0x0c */
  u32 flags;                      /* +0x10 */
  u8 pad0[0xc];                   /* +0x14..+0x1f */
};

#pragma schedule on
// FUN_004C6D60
static void FUN_004c6d60(rwResHeapBlockHeaderB119 *param_1, s32 param_2)
{
  rwResHeapBlockHeaderB119 *newBlock;

  newBlock = (rwResHeapBlockHeaderB119 *)((u8 *)param_1 + param_2 + 0x20);

  if ((param_1->next != 0) && ((~param_1->next->flags & 1) != 0)) {
    newBlock->next = param_1->next->next;
    newBlock->size = (param_1->size - param_2) + param_1->next->size;
  } else {
    newBlock->next = param_1->next;
    newBlock->size = param_1->size - param_2 - 0x20;
  }

  param_1->next = newBlock;
  newBlock->flags = 0;
  newBlock->prev = param_1;
  if (newBlock->next != 0) {
    newBlock->next->prev = newBlock;
  }
  param_1->size = param_2;
  newBlock->heap = param_1->heap;
}

/* P4: src/renderware/plcore/babinary.c RwStreamWriteReal (func_003df1a0).  The
   float and endian conversions are no-ops on the PS2, so the 256-byte bounce
   buffer goes straight through memcpy and RwStreamWrite.  P4 state:
   schedule on. */
extern void *FUN_00521250(void *param_1, const void *param_2, u32 param_3);

#pragma schedule on
// FUN_004C1750
void *FUN_004c1750(void *param_1, const u8 *param_2, u32 param_3)
{
  u8 convertBuffer[256];
  u32 bytesToWrite;

  while (param_3) {
    bytesToWrite = (param_3 >= 256) ? 256 : param_3;

    FUN_00521250(convertBuffer, param_2, bytesToWrite);

    if (FUN_004c53f0(param_1, convertBuffer, bytesToWrite) == 0)
      return 0;

    param_3 -= bytesToWrite;
    param_2 += bytesToWrite;
  }

  return param_1;
}

/* P4: src/renderware/plcore/bamatrix.c RwMatrixCreate (func_003e0f80).  The
   free list hangs off the matrix plugin globals at +0; the identity is
   written with the chained assignments rwMatrixInitializeIdentity expands to
   (flags 3, diagonal 1.0, everything else 0, flags |= 0x20003).  P4 state:
   schedule on. */
#pragma schedule on
// FUN_004C38C0
RwMatrix *FUN_004c38c0(void)
{
  RwMatrix *matrix;

  matrix = RWSRCGLOBALB119(memoryAlloc)(
      ((rwMatrixGlobalsB119 *)((u8 *)DAT_00960070 +
                               rwMatrixTolerancesOffset.globalsOffset))
          ->matrixFreeList,
      0x3000d);

  if (matrix != 0) {
    matrix->flags = 3;
    matrix->right.x = matrix->up.y = matrix->at.z = 1.0f;
    matrix->right.y = matrix->right.z = matrix->up.x = 0.0f;
    matrix->up.z = matrix->at.x = matrix->at.y = 0.0f;
    matrix->pos.x = matrix->pos.y = matrix->pos.z = 0.0f;
    matrix->flags = matrix->flags | 0x20003;
  }
  return matrix;
}

/* P4: src/renderware/plcore/baresour.c _rwResourcesPurge (func_003e1f50).
   Splice the free entry list onto the used list (or move it when the used
   list is empty), then swap the lists and reset the reusage counter.  P4
   state: schedule on. */
#pragma schedule on
// FUN_004C4890
void FUN_004c4890(void)
{
  rwLinkListB119 *usedEntries;
  rwLinkListB119 *freeEntries;

  usedEntries = (rwLinkListB119 *)RWRESOURCESGLOBALB119(usedEntries);
  freeEntries = (rwLinkListB119 *)RWRESOURCESGLOBALB119(freeEntries);

  if (freeEntries->next != (rwLLLinkB119 *)freeEntries) {
    if (usedEntries->next == (rwLLLinkB119 *)usedEntries) {
      usedEntries->next = freeEntries->next;
      usedEntries->next->prev = (rwLLLinkB119 *)usedEntries;
      usedEntries->prev = freeEntries->prev;
      usedEntries->prev->next = (rwLLLinkB119 *)usedEntries;
      freeEntries->next = (rwLLLinkB119 *)freeEntries;
      freeEntries->prev = (rwLLLinkB119 *)freeEntries;
    } else {
      rwLLLinkB119 *first;
      rwLLLinkB119 *last;

      last = usedEntries->prev;
      first = freeEntries->next;
      last->next = first;
      first->prev = last;

      last = freeEntries->prev;
      last->next = (rwLLLinkB119 *)usedEntries;
      usedEntries->prev = last;

      freeEntries->next = (rwLLLinkB119 *)freeEntries;
      freeEntries->prev = (rwLLLinkB119 *)freeEntries;
    }
  }

  RWRESOURCESGLOBALB119(usedEntries) = freeEntries;
  RWRESOURCESGLOBALB119(freeEntries) = usedEntries;
  RWRESOURCESGLOBALB119(reusageSize) = 0;
}

/* P4: src/renderware/plcore/bavector.c VectorMultPoint (func_003e3dc0).  Same
   incremental scale/image form as VectorMultVector, plus the translation.
   P4 state: schedule on. */
#pragma schedule on
// FUN_004C6700
RwV3d *FUN_004c6700(RwV3d *pointOut, const RwV3d *pointIn,
                    const RwMatrix *matrix)
{
  RwReal scale;
  RwReal imageX;
  RwReal imageY;
  RwReal imageZ;

  scale = pointIn->x;
  imageX = ((scale) * (matrix->right.x));
  imageY = ((scale) * (matrix->right.y));
  imageZ = ((scale) * (matrix->right.z));

  scale = pointIn->y;
  imageX = ((imageX) + (((scale) * (matrix->up.x))));
  imageY = ((imageY) + (((scale) * (matrix->up.y))));
  imageZ = ((imageZ) + (((scale) * (matrix->up.z))));

  scale = pointIn->z;
  imageX = ((imageX) + (((scale) * (matrix->at.x))));
  imageY = ((imageY) + (((scale) * (matrix->at.y))));
  imageZ = ((imageZ) + (((scale) * (matrix->at.z))));

  pointOut->x = ((imageX) + (matrix->pos.x));
  pointOut->y = ((imageY) + (matrix->pos.y));
  pointOut->z = ((imageZ) + (matrix->pos.z));

  return pointOut;
}

/* P4: src/renderware/plcore/bavector.c VectorMultVectors (func_003e3e60).
   The count-down loop keeps the first output pointer for the return value.
   P4 state: schedule on. */
#pragma schedule on
// FUN_004C67A0
RwV3d *FUN_004c67a0(RwV3d *pointsOut, const RwV3d *pointsIn, s32 numPoints,
                    const RwMatrix *matrix)
{
  RwV3d *cachedOut = pointsOut;

  while (--numPoints >= 0) {
    RwReal scale;
    RwReal imageX;
    RwReal imageY;
    RwReal imageZ;

    scale = pointsIn->x;
    imageX = ((scale) * (matrix->right.x));
    imageY = ((scale) * (matrix->right.y));
    imageZ = ((scale) * (matrix->right.z));

    scale = pointsIn->y;
    imageX = ((imageX) + (((scale) * (matrix->up.x))));
    imageY = ((imageY) + (((scale) * (matrix->up.y))));
    imageZ = ((imageZ) + (((scale) * (matrix->up.z))));

    scale = pointsIn->z;
    pointsOut->x = ((((scale) * (matrix->at.x))) + (imageX));
    pointsOut->y = ((((scale) * (matrix->at.y))) + (imageY));
    pointsOut->z = ((((scale) * (matrix->at.z))) + (imageZ));

    pointsIn++;
    pointsOut++;
  }

  return cachedOut;
}

/* P4: src/promoted/code1_003d_cw119.c func_003dd620.  The name at +0xc is
   freed, reallocated (strlen + 1 with the 0x401be hint) and copied through
   the engine's fixed callback slots.  P4 state: schedule on,
   no_branch_likely off. */
extern s32 *FUN_004c0070(u8 *arg0);
extern void (*DAT_0096013c[])(void *, void *);
extern u32 (*DAT_00960164[])(void *);
extern void *(*DAT_00960178[])(u32, u32);
extern void (*DAT_0096017c[])(void *);

#pragma schedule on
#pragma no_branch_likely off
// FUN_004BFA70
s32 FUN_004bfa70(u8 *arg0, u8 *arg1)
{
  if (FUN_004c0070(arg1) != 0) {
    return 7;
  }
  if (*(void **)(arg0 + 0xc) != 0) {
    DAT_0096017c[0](*(void **)(arg0 + 0xc));
  }
  *(void **)(arg0 + 0xc) = DAT_00960178[0](DAT_00960164[0](arg1) + 1, 0x401be);
  DAT_0096013c[0](*(void **)(arg0 + 0xc), arg1);
  return 1;
}

/* P4: src/renderware/plcore/baresour.c RwResourcesFreeResEntry (func_003e1ea0).
   Resource entry: link +0, size +8, owner +0xc, ownerRef +0x10, notify +0x14.
   A linked entry is unlinked and returned to the resource heap, an orphan one
   goes through RwFree.  P4 state: schedule on. */
typedef struct {
  rwLLLinkB119 link;             /* +0x00 */
  u32 size;                      /* +0x08 */
  void *owner;                   /* +0x0c */
  void **ownerRef;               /* +0x10 */
  void (*destroyNotify)(void *); /* +0x14 */
} RwResEntryB119;

extern void FUN_004c6e60(void *param_1);

#pragma schedule on
// FUN_004C47E0
u32 FUN_004c47e0(RwResEntryB119 *param_1)
{
  if (param_1->destroyNotify != 0)
    param_1->destroyNotify(param_1);

  if (param_1->ownerRef != 0)
    *param_1->ownerRef = 0;

  if (param_1->link.next == 0) {
    DAT_0096017c[0](param_1);
  } else {
    param_1->link.prev->next = param_1->link.next;
    param_1->link.next->prev = param_1->link.prev;
    RWRESOURCESGLOBALB119(currentSize) -= param_1->size;
    FUN_004c6e60(param_1);
  }
  return 1;
}

/* P4: src/renderware/plcore/bastream.c StreamMemoryInitialize (func_003e2750).
   Stream fields: position +0xc, nSize +0x10, memBlock +0x14 inside the
   memory view of the union.  The access-type switch is emitted as the 3/2/1
   comparison chain; the default raises E_RW_INVSTREAMACCESSTYPE through
   RwErrorSet.  P4 state: schedule on. */
typedef struct {
  void *start; /* +0x00 */
  u32 length;  /* +0x04 */
} RwMemoryB119;

typedef struct {
  u32 position; /* +0x00 */
  u32 nSize;    /* +0x04 */
  u8 *memBlock; /* +0x08 */
} RwStreamMemoryB119;

typedef struct {
  u32 type;                     /* +0x00 */
  u32 accessType;               /* +0x04 */
  s32 position;                 /* +0x08 */
  RwStreamMemoryB119 memory;    /* +0x0c (the Type union) */
  u8 pad0[0x8];                 /* +0x18..+0x1f */
  u32 rwOwned;                  /* +0x20 */
} RwStreamB119;

extern s32 FUN_004c1d10(s32 param_1, ...);

#pragma schedule on
#pragma dont_inline on
// FUN_004C5090
RwStreamB119 *FUN_004c5090(RwStreamB119 *stream, u32 accessType,
                           const RwMemoryB119 *pData)
{
  RwStreamB119 *result = 0;
  const RwMemoryB119 *mepMem = (const RwMemoryB119 *)pData;

  switch (accessType) {
  case 1: {
    stream->memory.position = 0;
    stream->memory.nSize = mepMem->length;
    stream->memory.memBlock = mepMem->start;
    result = stream;
    break;
  }
  case 2: {
    stream->memory.position = 0;
    stream->memory.nSize = 0;
    stream->memory.memBlock = 0;
    result = stream;
    break;
  }
  case 3: {
    stream->memory.position = mepMem->length;
    stream->memory.nSize = mepMem->length;
    stream->memory.memBlock = mepMem->start;
    result = stream;
    break;
  }
  default: {
    RwErrorB119 error;
    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0xd);
    FUN_004c1c50(&error);
    break;
  }
  }
  return result;
}
#pragma dont_inline off

/* P4: src/renderware/plcore/batkreg.c _rwPluginRegistryInitObject
   (func_003e3b70).  Construct forward; on the first failure unwind backwards
   through the destructors.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C64B0
const RwPluginRegistryB119 *FUN_004c64b0(const RwPluginRegistryB119 *param_1,
                                         void *param_2)
{
  RwPluginRegEntryB119 *entry;

  entry = param_1->firstRegEntry;
  while (entry) {
    if (!((u32 (*)(void *, s32, s32))entry->constructCB)(param_2, entry->offset,
                                                         entry->size)) {
      entry = entry->prevRegEntry;
      while (entry) {
        ((void (*)(void *, s32, s32))entry->destructCB)(param_2, entry->offset,
                                                        entry->size);
        entry = entry->prevRegEntry;
      }
      return 0;
    }
    entry = entry->nextRegEntry;
  }
  return param_1;
}

/* P4: src/renderware/plcore/bavector.c _rwVectorSetMultFn (func_003e3f80).
   The vector plugin globals hold the four multiplication entry points at
   +8/+0xc/+0x10/+0x14; a NULL argument selects the matching default.  P4
   state: schedule on. */
typedef RwV3d *(*rwVectorMultFnB119)(RwV3d *pointOut, const RwV3d *pointIn,
                                     const RwMatrix *matrix);
typedef RwV3d *(*rwVectorsMultFnB119)(RwV3d *pointsOut, const RwV3d *pointsIn,
                                      s32 numPoints, const RwMatrix *matrix);

typedef struct {
  u8 pad0[8];
  rwVectorMultFnB119 multPoint;    /* +0x08 */
  rwVectorsMultFnB119 multPoints;  /* +0x0c */
  rwVectorMultFnB119 multVector;   /* +0x10 */
  rwVectorsMultFnB119 multVectors; /* +0x14 */
} rwVectorGlobalsB119;

extern RwModuleInfoB119 DAT_007ce910;
extern RwV3d *FUN_004c6640(RwV3d *pointsOut, const RwV3d *pointsIn,
                           s32 numPoints, const RwMatrix *matrix);

#pragma schedule on
// FUN_004C68C0
u32 FUN_004c68c0(rwVectorMultFnB119 param_1, rwVectorsMultFnB119 param_2,
                 rwVectorMultFnB119 param_3, rwVectorsMultFnB119 param_4)
{
  if (param_1 == 0)
    param_1 = FUN_004c6700;

  ((rwVectorGlobalsB119 *)((u8 *)DAT_00960070 + DAT_007ce910.globalsOffset))
      ->multPoint = param_1;

  if (param_2 == 0)
    param_2 = FUN_004c6640;

  ((rwVectorGlobalsB119 *)((u8 *)DAT_00960070 + DAT_007ce910.globalsOffset))
      ->multPoints = param_2;

  if (param_3 == 0)
    param_3 = FUN_004c6840;

  ((rwVectorGlobalsB119 *)((u8 *)DAT_00960070 + DAT_007ce910.globalsOffset))
      ->multVector = param_3;

  if (param_4 == 0)
    param_4 = FUN_004c67a0;

  ((rwVectorGlobalsB119 *)((u8 *)DAT_00960070 + DAT_007ce910.globalsOffset))
      ->multVectors = param_4;

  return 1;
}

/* P4: src/renderware/plcore/bamemory.c _RwFreeListFree (func_003e1230).
   Release every block in the free list's block list, then the free list
   itself unless it is static: master/None go through RwFree, otherwise the
   two-argument free to the master free list.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C3B70
void FUN_004c3b70(rwFreeListB119 *param_1)
{
  rwLLLinkB119 *link;
  rwLLLinkB119 *lastLink;

  link = param_1->blockList.next;
  lastLink = (rwLLLinkB119 *)&param_1->blockList;
  while (link != lastLink) {
    link->prev->next = link->next;
    link->next->prev = link->prev;
    RWSRCGLOBALB119(memoryFuncs_rwfree)(link);
    link = param_1->blockList.next;
    lastLink = (rwLLLinkB119 *)&param_1->blockList;
  }

  if ((param_1->flags & 1) == 0) {
    if ((DAT_007ce8e4 == (u8 *)param_1) || (DAT_007ce8e4 == 0)) {
      RWSRCGLOBALB119(memoryFuncs_rwfree)(param_1);
    } else {
      RWSRCGLOBALB119(memoryFree)(DAT_007ce8e4, param_1);
    }
  }
}

/* P4: src/renderware/plcore/bavector.c VectorMultPoints (func_003e3d00).
   Per-point version of VectorMultPoint with the running cached output
   pointer.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C6640
RwV3d *FUN_004c6640(RwV3d *pointsOut, const RwV3d *pointsIn, s32 numPoints,
                    const RwMatrix *matrix)
{
  RwV3d *cachedOut = pointsOut;

  while (--numPoints >= 0) {
    RwReal scale;
    RwReal imageX;
    RwReal imageY;
    RwReal imageZ;

    scale = pointsIn->x;
    imageX = ((scale) * (matrix->right.x));
    imageY = ((scale) * (matrix->right.y));
    imageZ = ((scale) * (matrix->right.z));

    scale = pointsIn->y;
    imageX = ((imageX) + (((scale) * (matrix->up.x))));
    imageY = ((imageY) + (((scale) * (matrix->up.y))));
    imageZ = ((imageZ) + (((scale) * (matrix->up.z))));

    scale = pointsIn->z;
    imageX = ((imageX) + (((scale) * (matrix->at.x))));
    imageY = ((imageY) + (((scale) * (matrix->at.y))));
    imageZ = ((imageZ) + (((scale) * (matrix->at.z))));

    pointsOut->x = ((imageX) + (matrix->pos.x));
    pointsOut->y = ((imageY) + (matrix->pos.y));
    pointsOut->z = ((imageZ) + (matrix->pos.z));

    pointsIn++;
    pointsOut++;
  }

  return cachedOut;
}

/* P4: src/renderware/plcore/rwstring.c StrICmp (func_003e47c0).  Case
   insensitive compare: fold both characters, differ wins, the trailing
   check covers the NUL mismatch.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C7100
s32 FUN_004c7100(const s8 *param_1, const s8 *param_2)
{
  s8 c1;
  s8 c2;

  if ((param_1 != 0) && (param_2 != 0)) {
    do {
      c1 = *param_1;
      c2 = *param_2;

      /* Convert to lower case for comparison */
      if ((c1 >= 'A') && (c1 <= 'Z')) {
        c1 += 'a' - 'A';
      }

      if ((c2 >= 'A') && (c2 <= 'Z')) {
        c2 += 'a' - 'A';
      }

      /* Compare - anything beats NUL!!! */
      if (c1 != c2) {
        return c1 - c2;
      }

      param_1++;
      param_2++;
    } while (c1 && c2);

    if (c1 != c2) {
      return c1 - c2;
    }
  }

  return 0;
}

/* P4: src/renderware/plcore/rwstring.c _rwStringStreamWrite (func_003e4b20).
   nullString replaces a NULL string, the size is the inlined versioned
   string size, then the versioned chunk header (rwID_STRING = 2, library
   version 0x37002, build 55) and the payload.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C7460
const char *FUN_004c7460(const char *param_1, void *param_2)
{
  u32 stringSize;

  if (param_1 == 0) {
    param_1 = (const char *)D_007BCBE8;
  }

  stringSize = FUN_004c7410(param_1);

  if (FUN_004c15a0(param_2, 2, stringSize, 0x37002, 0x37) == 0) {
    return 0;
  }

  if (FUN_004c53f0(param_2, (void *)param_1, stringSize) != 0) {
    return param_1;
  }
  return 0;
}

/* P4: src/renderware/core/bacamera.c CameraUpdateZShiftScale
   (func_003e6db0).  zOut comes from the device's screen-z range, zIn from
   the projection planes (parallel uses them directly, perspective uses the
   reciprocals); the mapping then trims 0.02% at both ends.  P4 state:
   schedule on. */
#pragma schedule on
// FUN_004C89A0
RwCamera *FUN_004c89a0(RwCamera *param_1)
{
  float zOutInf = RWSRCGLOBALB119(zBufferNear);
  float zOutSup = RWSRCGLOBALB119(zBufferFar);
  float zInInf;
  float zInSup;

  switch (param_1->projType) {
  case (rwPARALLEL):
    zInSup = param_1->farPlane;
    zInInf = param_1->nearPlane;
    break;

  default:
    /* Should never happen, but do the perspective thing if it does */
  case (rwPERSPECTIVE):
    zInSup = ((float)1) / (param_1->farPlane);
    zInInf = ((float)1) / (param_1->nearPlane);
    break;
  }

  {
    float zOutWid;
    float zDelta;
    float zScale;
    float zShift;

    zOutWid = zOutSup - zOutInf;
    zDelta = zOutWid * ((float)0.0001);

    zOutSup = zOutSup - zDelta;
    zOutInf = zOutInf + zDelta;

    zOutWid = zOutSup - zOutInf;

    zScale = zOutWid / (zInSup - zInInf);
    zShift = (((float)0.5) *
              ((zOutSup + zOutInf) - zScale * (zInSup + zInInf)));

    param_1->zScale = zScale;
    param_1->zShift = zShift;
  }

  return param_1;
}

/* Moved after its only caller: fun_004c15a0 is written as a mark record
   round-trip, and callers that precede this definition must see a plain
   call (different TU in P4), not an inlined body. */
#pragma schedule on
// FUN_004C15A0
u32 FUN_004c15a0(void *param_1, u32 param_2, u32 param_3, u32 param_4,
                 u32 param_5)
{
  rwMarkB119 mark;
  u32 streamRet;

  mark.type = param_2;
  mark.length = param_3;
  mark.libraryID = ((((param_4 - 0x30000U) & 0x3ff00U) << 14) |
                    ((param_4 & 0x0003fU) << 16)) |
                   (param_5 & 0xffffU);

  streamRet = FUN_004c53f0(param_1, &mark, 0xc);
  return streamRet;
}

/* P4: src/renderware/core/badevice.c RwEngineStart (func_003e8a50).  Probe
   the device start request, initialize the engine plugin registry, set the
   image gamma from the device and finalize the device start; on failure the
   device stop request runs before returning false.  engineTKList is the
   recovered 0x77e630 registry.  P4 state: schedule on. */
typedef struct {
  float gammaCorrection; /* +0x00 */
  u8 pad0[0x04];         /* +0x04..+0x07 */
  float zBufferNear;     /* +0x08 */
  float zBufferFar;      /* +0x0c */
} RwDeviceB119;

extern u8 D_0077E630[];
extern float FUN_004cdb50(float param_1);

#pragma schedule on
#pragma dont_inline on
// FUN_004CA640
u32 FUN_004ca640(void)
{
  RwDeviceB119 *const device = (RwDeviceB119 *)((u8 *)DAT_00960070 + 0x10);

  if (FUN_004ca3e0(device, 2, 0, 0, 0)) {
    if (FUN_004c64b0((const RwPluginRegistryB119 *)D_0077E630,
                     (void *)DAT_00960070)) {
      FUN_004cdb50(device->gammaCorrection);

      FUN_004ca3e0(device, 0x11, 0, 0, 0);

      RWSRCGLOBALB119(engineStatus) = 3;
      return 1;
    }

    FUN_004ca3e0(device, 3, 0, 0, 0);
  }

  return 0;
}
#pragma dont_inline off

/* P4: src/renderware/plcore/batkbin.c _rwPluginRegistrySkipDataChunks
   (func_003e3560).  Find the extension chunk, then walk its sub-chunks
   without interpreting them: read each header and skip its payload.  P4
   state: schedule on. */
extern void *FUN_004c1600(void *param_1, u32 param_2, void *param_3,
                          void *param_4);
extern RwStreamB119 *FUN_004c5620(RwStreamB119 *stream, u32 offset);

#pragma schedule on
// FUN_004C5EA0
const RwPluginRegistryB119 *FUN_004c5ea0(const RwPluginRegistryB119 *param_1,
                                         void *param_2)
{
  u32 length;

  if (FUN_004c1600(param_2, 3, &length, 0) == 0) {
    return 0;
  }

  while (length > 0) {
    u32 readLength;

    if (FUN_004c1450((u32)param_2, 0, &readLength, 0, 0) == 0) {
      return 0;
    }

    if (FUN_004c5620(param_2, readLength) == 0) {
      return 0;
    }

    length -= (readLength + 0xc);
  }

  return param_1;
}

/* P4: src/renderware/plcore/resmem.c _rwResHeapFree (func_003e4520).  The
   block header sits 0x20 bytes before the payload; clear the used flag, make
   it the new first free block when it precedes the current one, then merge
   with the neighbouring free blocks.  P4 state: schedule on. */
typedef struct {
  rwResHeapBlockHeaderB119 *firstBlock;     /* +0x00 */
  rwResHeapBlockHeaderB119 *firstFreeBlock; /* +0x04 */
} rwResHeapB119;

#pragma schedule on
// FUN_004C6E60
void FUN_004c6e60(void *param_1)
{
  rwResHeapBlockHeaderB119 *block = (rwResHeapBlockHeaderB119 *)param_1 - 1;
  rwResHeapBlockHeaderB119 *prevBlock;
  rwResHeapBlockHeaderB119 *nextBlock;

  block->flags = 0;

  prevBlock = block->prev;
  nextBlock = block->next;

  if ((((rwResHeapB119 *)block->heap)->firstFreeBlock == 0) ||
      (block < ((rwResHeapB119 *)block->heap)->firstFreeBlock)) {
    ((rwResHeapB119 *)block->heap)->firstFreeBlock = block;
  }

  if ((prevBlock != 0) && ((~prevBlock->flags & 1) != 0)) {
    prevBlock->next = nextBlock;
    if (nextBlock != 0) {
      nextBlock->prev = prevBlock;
    }

    prevBlock->size += (block->size + 0x20);

    block = prevBlock;
  }

  if ((nextBlock != 0) && ((~nextBlock->flags & 1) != 0)) {
    block->next = nextBlock->next;
    if (nextBlock->next != 0) {
      nextBlock->next->prev = block;
    }

    block->size += (nextBlock->size + 0x20);
  }
}

/* P4: src/renderware/plcore/bamemory.c RwFreeListDestroy (func_003e12f0).
   Unlink the free list from the module list then release it (the static
   _RwFreeListFree body is inlined in the P4 build, so it is spelled out
   here).  P4 state: schedule on. */
#pragma schedule on
// FUN_004C3C30
u32 FUN_004c3c30(rwFreeListB119 *param_1)
{
  rwLLLinkB119 *link;
  rwLLLinkB119 *lastLink;

  param_1->link.prev->next = param_1->link.next;
  param_1->link.next->prev = param_1->link.prev;

  link = param_1->blockList.next;
  lastLink = (rwLLLinkB119 *)&param_1->blockList;
  while (link != lastLink) {
    link->prev->next = link->next;
    link->next->prev = link->prev;
    RWSRCGLOBALB119(memoryFuncs_rwfree)(link);
    link = param_1->blockList.next;
    lastLink = (rwLLLinkB119 *)&param_1->blockList;
  }

  if ((param_1->flags & 1) == 0) {
    if ((DAT_007ce8e4 == (u8 *)param_1) || (DAT_007ce8e4 == 0)) {
      RWSRCGLOBALB119(memoryFuncs_rwfree)(param_1);
    } else {
      RWSRCGLOBALB119(memoryFree)(DAT_007ce8e4, param_1);
    }
  }

  return 1;
}

/* P4: src/renderware/plcore/resmem.c _rwResHeapAlloc (func_003e45f0).  Round
   the request up to a 32 byte multiple, walk the free list for a block that
   is unused and large enough, split off the excess through splitBlock (a
   call in the P4 object) and step firstFreeBlock past the used blocks.  P4
   state: schedule on. */
#pragma schedule on
// FUN_004C6F30
void *FUN_004c6f30(void *param_1, u32 param_2)
{
  rwResHeapB119 *heapInfo = (rwResHeapB119 *)param_1;
  rwResHeapBlockHeaderB119 *targetBlock;
  rwResHeapBlockHeaderB119 *curBlock;

  param_2 += 31;
  param_2 &= 0xffffffe0U;

  targetBlock = 0;
  curBlock = heapInfo->firstFreeBlock;
  while (curBlock && !targetBlock) {
    if ((~curBlock->flags & 1) && curBlock->size >= param_2) {
      targetBlock = curBlock;
    }

    curBlock = curBlock->next;
  }

  if (!targetBlock) {
    return 0;
  }

  if (targetBlock->size > (param_2 + 64)) {
    FUN_004c6d60(targetBlock, param_2);
  }

  if (targetBlock == heapInfo->firstFreeBlock) {
    do {
      heapInfo->firstFreeBlock = heapInfo->firstFreeBlock->next;
    } while (heapInfo->firstFreeBlock &&
             (heapInfo->firstFreeBlock->flags & 1));
  }

  targetBlock->flags = 1;

  return (void *)(targetBlock + 1);
}

/* P4: src/renderware/plcore/balist.c _rwSListGetNewEntry (func_003df6e0).
   Grow the element array by a quarter when it is full (realloc through
   memoryFuncs.rwrealloc at +0x110, E_RW_NOMEM on failure), then hand back
   the slot for the next element.  P4 state: schedule on. */
typedef struct {
  u8 *listElements;       /* +0x00 */
  s32 numElementsFilled;  /* +0x04 */
  s32 numElementsAlloced; /* +0x08 */
  s32 entrySize;          /* +0x0c */
} rwSListB119;

#pragma schedule on
#pragma dont_inline on
// FUN_004C1E70
void *FUN_004c1e70(rwSListB119 *param_1, u32 param_2)
{
  void *pData;

  if (param_1->numElementsFilled >= param_1->numElementsAlloced) {
    u8 *cpNew;

    cpNew = (u8 *)RWSRCGLOBALB119(memoryFuncs_rwrealloc)(
        param_1->listElements,
        (param_1->numElementsAlloced + param_1->numElementsAlloced / 4) *
            param_1->entrySize,
        param_2);
    if (cpNew == 0) {
      RwErrorB119 error;

      error.pluginID = 1;
      error.errorCode = FUN_004c1d10(
          0x80000013,
          (param_1->numElementsAlloced + param_1->numElementsAlloced / 4) *
              param_1->entrySize);
      FUN_004c1c50(&error);
      return 0;
    }

    param_1->listElements = cpNew;
    param_1->numElementsAlloced =
        param_1->numElementsAlloced + param_1->numElementsAlloced / 4;
  }

  pData = (void *)&(param_1->listElements[param_1->numElementsFilled *
                                          param_1->entrySize]);
  param_1->numElementsFilled++;

  return pData;
}
#pragma dont_inline off

/* P4: src/renderware/plcore/baresour.c ResourcesInit (func_003e1cb0).  When
   a size is given, allocate the resource heap and initialise it (freeing it
   and raising E_RW_INSUFFICIENTRESOURCES when the init fails); otherwise the
   heap stays NULL.  Both entry lists become empty circular lists and the
   used/free lists are exchanged.  P4 state: schedule on. */
#pragma schedule on
#pragma dont_inline on
// FUN_004C45F0
rwResourcesB119 *FUN_004c45f0(rwResourcesB119 *param_1, u32 param_2)
{
  if (param_2 > 0) {
    param_1->memHeap = RWSRCGLOBALB119(memoryFuncs_rwmalloc)(param_2, 0x4040b);
    if (param_1->memHeap == 0) {
      RwErrorB119 error;

      error.pluginID = 1;
      error.errorCode = FUN_004c1d10(0x80000013, param_2);
      FUN_004c1c50(&error);
      return 0;
    }

    if (FUN_004c6df0((u8 *)param_1->memHeap, param_2) == 0) {
      RwErrorB119 error;

      RWSRCGLOBALB119(memoryFuncs_rwfree)(param_1->memHeap);

      error.pluginID = 1;
      error.errorCode = FUN_004c1d10(0xc, 0);
      FUN_004c1c50(&error);
      return 0;
    }
  } else {
    param_1->memHeap = 0;
  }

  param_1->entriesA.next = (rwLLLinkB119 *)&param_1->entriesA;
  param_1->entriesA.prev = (rwLLLinkB119 *)&param_1->entriesA;
  param_1->entriesB.next = (rwLLLinkB119 *)&param_1->entriesB;
  param_1->entriesB.prev = (rwLLLinkB119 *)&param_1->entriesB;

  param_1->usedEntries = &param_1->entriesA;
  param_1->freeEntries = &param_1->entriesB;

  param_1->maxSize = param_2;
  param_1->currentSize = 0;
  param_1->reusageSize = 0;

  return param_1;
}
#pragma dont_inline off

/* P4: src/renderware/plcore/bastream.c StreamFileNameInitialize
   (func_003e2650).  Open the file with the mode that matches the access
   type (rwSTREAMREAD/WRITE/APPEND = 1/2/3), store the handle in the file
   view of the stream union (+0xc) and report a bad access type or a failed
   open through RwErrorSet.  P4 state: schedule on. */
typedef struct {
  u32 type;       /* +0x00 */
  u32 accessType; /* +0x04 */
  s32 position;   /* +0x08 */
  void *fpFile;   /* +0x0c */
} RwStreamFileB119;

extern void *FUN_004c0240(const char *param_1, const char *param_2);

#pragma schedule on
#pragma dont_inline on
// FUN_004C4F90
RwStreamB119 *FUN_004c4f90(RwStreamB119 *param_1, u32 param_2,
                           const void *param_3)
{
  RwStreamB119 *result = 0;
  void *fp = 0;
  const char *cpFile = (const char *)param_3;

  switch (param_2) {
  case 1: {
    fp = FUN_004c0240(cpFile, "rb");
    break;
  }
  case 2: {
    fp = FUN_004c0240(cpFile, "wb");
    break;
  }
  case 3: {
    fp = FUN_004c0240(cpFile, "ab");
    break;
  }
  default: {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0xd);
    FUN_004c1c50(&error);
    break;
  }
  }

  if (fp != 0) {
    ((RwStreamFileB119 *)param_1)->fpFile = fp;
    result = param_1;
  } else {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0x80000002, (u32)cpFile);
    FUN_004c1c50(&error);
  }

  return result;
}
#pragma dont_inline off

/* P4: src/renderware/plcore/balist.c _rwSListCreate (func_003df5d0).  Allocate
   the SList header (E_RW_NOMEM on failure), seed it with SLIST_STARTSIZE (20)
   elements and allocate the element array with the RESIZABLE hint; a failed
   element allocation raises E_RW_NOMEM and frees the header.  P4 state:
   schedule on. */
#pragma schedule on
#pragma dont_inline on
// FUN_004C1D50
rwSListB119 *FUN_004c1d50(s32 param_1, u32 param_2)
{
  rwSListB119 *sList;

  sList = (rwSListB119 *)RWSRCGLOBALB119(memoryFuncs_rwmalloc)(0x10, 0x30000);
  if (!sList) {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0x80000013, 0x10);
    FUN_004c1c50(&error);
    return 0;
  }

  sList->numElementsFilled = 0;
  sList->numElementsAlloced = 0x14;
  sList->entrySize = param_1;

  sList->listElements =
      (u8 *)RWSRCGLOBALB119(memoryFuncs_rwmalloc)(
          sList->numElementsAlloced * sList->entrySize, param_2 | 0x1000000);

  if (!sList->listElements) {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(
        0x80000013, sList->numElementsAlloced * sList->entrySize);
    FUN_004c1c50(&error);
    RWSRCGLOBALB119(memoryFuncs_rwfree)(sList);
    return 0;
  }

  return sList;
}
#pragma dont_inline off

/* P4: src/renderware/plcore/bastream.c _rwStreamInitialize (func_003e2800).
   Store the type/access/ownership into the stream, then dispatch to the
   initializer for the stream kind: file (ftell probe then handle), filename
   (FUN_004c4f90), memory (FUN_004c5090) or custom (the 0x14 byte custom
   record is copied); an unknown type raises E_RW_INVSTREAMTYPE.  P4 state:
   schedule on. */
extern s32 FUN_004c0820(void *param_1);

/* P4: src/renderware/plcore/bastream.c StreamFileInitialize (static helper,
   inlined by b119 into _rwStreamInitialize): the ftell probe rejects
   non-file handles before the handle is stored. */
static RwStreamB119 *streamFileInitB119(RwStreamB119 *param_1,
                                        const void *param_2)
{
  if (-1 == FUN_004c0820((void *)param_2)) {
    return 0;
  }

  ((RwStreamFileB119 *)param_1)->fpFile = (void *)param_2;
  return param_1;
}

#pragma schedule on
// FUN_004C5140
RwStreamB119 *FUN_004c5140(RwStreamB119 *param_1, u32 param_2, u32 param_3,
                           u32 param_4, const void *param_5)
{
  RwStreamB119 *result = 0;

  if (!param_1) {
    return result;
  }

  param_1->type = param_3;
  param_1->accessType = param_4;

  param_1->rwOwned = param_2;

  switch (param_3) {
  case 1: {
    result = streamFileInitB119(param_1, param_5);
    break;
  }
  case 2: {
    result = FUN_004c4f90(param_1, param_4, param_5);
    break;
  }
  case 3: {
    result = FUN_004c5090(param_1, param_4, param_5);
    break;
  }
  case 4: {
    FUN_00521250((void *)&param_1->memory, param_5, 0x14);
    result = param_1;
    break;
  }
  default: {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0xe);
    FUN_004c1c50(&error);
    break;
  }
  }

  return result;
}

/* P4: src/renderware/core/babbox.c RwBBoxCalculate (func_003e5110).  Seed
   both corners from the first vertex, then track the per-axis minima and
   maxima (each test's store is kept out of line).  P4 state: schedule on. */
#pragma schedule on
// FUN_004C7A50
RwBBoxB119 *FUN_004c7a50(RwBBoxB119 *param_1, const RwV3dB119 *param_2,
                         s32 param_3)
{
  param_1->inf = *param_2;
  param_1->sup = *param_2;

  param_2++;
  param_3--;

  while (param_3--) {
    if (param_1->inf.x > param_2->x) {
      param_1->inf.x = param_2->x;
    }
    if (param_1->inf.y > param_2->y) {
      param_1->inf.y = param_2->y;
    }
    if (param_1->inf.z > param_2->z) {
      param_1->inf.z = param_2->z;
    }

    if (param_1->sup.x < param_2->x) {
      param_1->sup.x = param_2->x;
    }
    if (param_1->sup.y < param_2->y) {
      param_1->sup.y = param_2->y;
    }
    if (param_1->sup.z < param_2->z) {
      param_1->sup.z = param_2->z;
    }

    param_2++;
  }

  return param_1;
}

/* P4: src/renderware/plcore/bastream.c RwStreamClose (func_003e2e40).  Close
   by kind: filenames fclose (TRUE when the close succeeds), memory streams
   write the position back into the caller's RwMemory when they were not
   opened for reading, custom streams run their close callback; an unknown
   type raises E_RW_INVSTREAMTYPE.  An owned stream goes back to the stream
   free list through memoryFree (+0x11c).  P4 state: schedule on. */
typedef struct {
  u32 type;                  /* +0x00 */
  u32 accessType;            /* +0x04 */
  s32 position;              /* +0x08 */
  void (*sfnclose)(void *);  /* +0x0c */
  void *sfnread;             /* +0x10 */
  void *sfnwrite;            /* +0x14 */
  void *sfnskip;             /* +0x18 */
  void *data;                /* +0x1c */
  u32 rwOwned;               /* +0x20 */
} RwStreamCustomB119;

extern s32 DAT_007ce8f8; /* streamModule.globalsOffset */
extern s32 FUN_004c0370(void *param_1);

#pragma schedule on
#pragma dont_inline on
// FUN_004C5780
u32 FUN_004c5780(RwStreamB119 *param_1, RwMemoryB119 *param_2)
{
  u32 result;

  switch (param_1->type) {
  case 1: {
    result = 1;
    break;
  }
  case 2: {
    result = (FUN_004c0370(((RwStreamFileB119 *)param_1)->fpFile) == 0);
    break;
  }
  case 3: {
    if (param_1->accessType != 1) {
      if (param_2) {
        param_2->start = param_1->memory.memBlock;
        param_2->length = param_1->memory.position;
      }
    }

    result = 1;
    break;
  }
  case 4: {
    if (((RwStreamCustomB119 *)param_1)->sfnclose) {
      ((RwStreamCustomB119 *)param_1)->sfnclose(
          ((RwStreamCustomB119 *)param_1)->data);
    }

    result = 1;
    break;
  }
  default: {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0xe);
    FUN_004c1c50(&error);
    return 0;
  }
  }

  if (param_1->rwOwned) {
    RWSRCGLOBALB119(memoryFree)(
        *(void **)((u8 *)DAT_00960070 + DAT_007ce8f8), param_1);
  }

  return result;
}
#pragma dont_inline off

/* P4: src/renderware/plcore/rwstring.c _rwStringOpen (func_003e49a0).
   Install the ANSI string function table; each slot is one absolute store
   (the four local helpers are already defined above).  P4 state: schedule
   on. */
extern u64 FUN_00523ac8();
extern u64 FUN_00523b40();
extern u64 FUN_00523e68();
extern u64 FUN_00524128();
extern u64 FUN_00524270();
extern u64 FUN_00524388();
extern u64 FUN_005244c0();
extern u64 FUN_00524670();
extern u64 FUN_00524828();
extern u64 FUN_00524a50();
extern u64 FUN_00525958();
extern u64 FUN_005288c8();
extern u32 DAT_00960134[];
extern u32 DAT_00960138[];
extern u32 DAT_00960140[];
extern u32 DAT_00960144[];
extern u32 DAT_00960148[];
extern u32 DAT_0096014c[];
extern u32 DAT_00960150[];
extern u32 DAT_00960154[];
extern u32 DAT_00960158[];
extern u32 DAT_0096015c[];
extern u32 DAT_00960160[];
extern u32 DAT_00960168[];
extern u32 DAT_0096016c[];
extern u32 DAT_00960170[];
extern u32 DAT_00960174[];

#pragma schedule on
// FUN_004C72E0
u32 FUN_004c72e0(void)
{
  DAT_00960134[0] = (u32)(FUN_00523ac8);
  DAT_00960138[0] = (u32)(FUN_005288c8);
  DAT_0096013c[0] = (void (*)(void *, void *))FUN_00524270;
  DAT_00960140[0] = (u32)(FUN_00524828);
  DAT_00960144[0] = (u32)(FUN_00523e68);
  DAT_00960148[0] = (u32)(FUN_005244c0);
  DAT_0096014c[0] = (u32)(FUN_004c72a0);
  DAT_00960150[0] = (u32)(FUN_004c7260);
  DAT_00960154[0] = (u32)(FUN_00524a50);
  DAT_00960158[0] = (u32)(FUN_00524128);
  DAT_0096015c[0] = (u32)(FUN_00524670);
  DAT_00960160[0] = (u32)(FUN_004c7100);
  DAT_00960164[0] = (u32 (*)(void *))FUN_00524388;
  DAT_00960168[0] = (u32)(FUN_004c71c0);
  DAT_0096016c[0] = (u32)(FUN_004c7210);
  DAT_00960170[0] = (u32)(FUN_00525958);
  DAT_00960174[0] = (u32)(FUN_00523b40);
  return 1;
}

/* P4: src/renderware/plcore/baplcore.c _rwDeviceSystemRequest (func_003e87f0).
   Ask the driver's system request hook; when it declines, answer the core
   requests (sub system count/info/current/selection) and only fail for
   anything else.  P4 state: schedule on. */

#pragma schedule on
// FUN_004CA3E0
u32 FUN_004ca3e0(void *param_1, u32 param_2, void *param_3, void * param_4,
                 u32 param_5)
{
  u32 result;

  result = ((u32(*)(u32, void *, u32, u32)) * (u32 **)((u8 *)param_1 + 4))(
      param_2, param_3, (u32)param_4, param_5);
  if (!result) {
    switch (param_2) {
    case 0x11:
    case 0x12:
      result = 1;
      break;

    case 0xd:
      *(u32 *)param_3 = 1;
      result = 1;
      break;

    case 0xe:
      result = (param_5 == 0);
      if (result) {
        DAT_0096013c[0](param_3, "Only rendering sub system");
      }
      break;

    case 0xf:
      *(u32 *)param_3 = 0;
      result = 1;
      break;

    case 0x10:
      result = (param_5 == 0);
      break;
    }
  }

  if (!result) {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0x18, param_2);
    FUN_004c1c50(&error);
  }

  return result;
}

/* P4: src/renderware/plcore/bamatrix.c MatrixMultiply (func_003df8c0).  dst =
   A x B, translation row included; the out-of-line default matrix multiply
   hook.  P4 state: schedule on. */

#pragma schedule on
// FUN_004C2200
void FUN_004c2200(RwMatrix *matrixOut, const RwMatrix *matrixIn1,
                  const RwMatrix *matrixIn2)
{
  matrixOut->right.x = ((matrixIn1->right.x * matrixIn2->right.x) +
                        (matrixIn1->right.y * matrixIn2->up.x) +
                        (matrixIn1->right.z * matrixIn2->at.x));
  matrixOut->right.y = ((matrixIn1->right.x * matrixIn2->right.y) +
                        (matrixIn1->right.y * matrixIn2->up.y) +
                        (matrixIn1->right.z * matrixIn2->at.y));
  matrixOut->right.z = ((matrixIn1->right.x * matrixIn2->right.z) +
                        (matrixIn1->right.y * matrixIn2->up.z) +
                        (matrixIn1->right.z * matrixIn2->at.z));

  matrixOut->up.x = ((matrixIn1->up.x * matrixIn2->right.x) +
                     (matrixIn1->up.y * matrixIn2->up.x) +
                     (matrixIn1->up.z * matrixIn2->at.x));
  matrixOut->up.y = ((matrixIn1->up.x * matrixIn2->right.y) +
                     (matrixIn1->up.y * matrixIn2->up.y) +
                     (matrixIn1->up.z * matrixIn2->at.y));
  matrixOut->up.z = ((matrixIn1->up.x * matrixIn2->right.z) +
                     (matrixIn1->up.y * matrixIn2->up.z) +
                     (matrixIn1->up.z * matrixIn2->at.z));

  matrixOut->at.x = ((matrixIn1->at.x * matrixIn2->right.x) +
                     (matrixIn1->at.y * matrixIn2->up.x) +
                     (matrixIn1->at.z * matrixIn2->at.x));
  matrixOut->at.y = ((matrixIn1->at.x * matrixIn2->right.y) +
                     (matrixIn1->at.y * matrixIn2->up.y) +
                     (matrixIn1->at.z * matrixIn2->at.y));
  matrixOut->at.z = ((matrixIn1->at.x * matrixIn2->right.z) +
                     (matrixIn1->at.y * matrixIn2->up.z) +
                     (matrixIn1->at.z * matrixIn2->at.z));

  matrixOut->pos.x = ((matrixIn1->pos.x * matrixIn2->right.x) +
                      (matrixIn1->pos.y * matrixIn2->up.x) +
                      (matrixIn1->pos.z * matrixIn2->at.x) +
                      matrixIn2->pos.x);
  matrixOut->pos.y = ((matrixIn1->pos.x * matrixIn2->right.y) +
                      (matrixIn1->pos.y * matrixIn2->up.y) +
                      (matrixIn1->pos.z * matrixIn2->at.y) +
                      matrixIn2->pos.y);
  matrixOut->pos.z = ((matrixIn1->pos.x * matrixIn2->right.z) +
                      (matrixIn1->pos.y * matrixIn2->up.z) +
                      (matrixIn1->pos.z * matrixIn2->at.z) +
                      matrixIn2->pos.z);
}

/* P4: src/renderware/plcore/bamatrix.c RwMatrixInvert (func_003e0960).
   Identity matrices are copied, orthonormal ones transposed with the
   translation row recomputed, everything else goes through the generic
   inverse (FUN_004c2860).  P4 state: schedule on. */
/* P4: src/renderware/plcore/bamatrix.c MatrixInvertGeneric (func_003dff20).
   Generic 3x3 cofactor inverse (rwMat03Inv macro expanded), translation row
   recomputed from the inverse and marked clean (flags 0).  Defined before
   FUN_004c32a0 (as in P4) so its a0-preserving body is visible to the
   caller's codegen.  P4 state: schedule on. */
typedef union {
  float nReal;
  volatile s32 nInt;
} RwSplitBitsB119;

#pragma schedule on
// FUN_004C2860
static RwMatrix *FUN_004c2860(RwMatrix *dst, const RwMatrix *src)
{
  RwSplitBitsB119 determinant;

  dst->right.x = (src->up.y * src->at.z) - (src->up.z * src->at.y);
  dst->right.y = -((src->right.y * src->at.z) - (src->right.z * src->at.y));
  dst->right.z = (src->right.y * src->up.z) - (src->right.z * src->up.y);

  determinant.nReal = (dst->right.x * src->right.x) +
                      (dst->right.y * src->up.x) +
                      (dst->right.z * src->at.x);

  {
    const float normalize = (determinant.nInt != 0)
                                ? (((float)1) / determinant.nReal)
                                : ((float)1);

    dst->right.x *= normalize;
    dst->right.y *= normalize;
    dst->right.z *= normalize;

    dst->up.x = -((src->up.x * src->at.z) - (src->up.z * src->at.x)) *
                normalize;
    dst->up.y = ((src->right.x * src->at.z) - (src->right.z * src->at.x)) *
                normalize;
    dst->up.z = -((src->right.x * src->up.z) - (src->right.z * src->up.x)) *
                normalize;

    dst->at.x = ((src->up.x * src->at.y) - (src->up.y * src->at.x)) * normalize;
    dst->at.y = -((src->right.x * src->at.y) - (src->right.y * src->at.x)) *
                normalize;
    dst->at.z = ((src->right.x * src->up.y) - (src->right.y * src->up.x)) *
                normalize;
  }

  dst->pos.x = -((src->pos.x * dst->right.x) + (src->pos.y * dst->up.x) +
                 (src->pos.z * dst->at.x));
  dst->pos.y = -((src->pos.x * dst->right.y) + (src->pos.y * dst->up.y) +
                 (src->pos.z * dst->at.y));
  dst->pos.z = -((src->pos.x * dst->right.z) + (src->pos.y * dst->up.z) +
                 (src->pos.z * dst->at.z));

  dst->flags = 0;
  return dst;
}

#pragma schedule on
// FUN_004C32A0
RwMatrix *FUN_004c32a0(RwMatrix *dst, const RwMatrix *src)
{
  if (src->flags & (((rwMatrixGlobalsB119 *)((u8 *)DAT_00960070 +
                                             rwMatrixTolerancesOffset
                                                 .globalsOffset))
                        ->matrixOptimizations &
                    0x20000)) {
    *dst = *src;
  } else if ((src->flags & 3) == 3) {
    dst->right.x = src->right.x;
    dst->right.y = src->up.x;
    dst->right.z = src->at.x;

    dst->up.x = src->right.y;
    dst->up.y = src->up.y;
    dst->up.z = src->at.y;

    dst->at.x = src->right.z;
    dst->at.y = src->up.z;
    dst->at.z = src->at.z;

    dst->pos.x = -((src->pos.x * src->right.x) +
                   (src->pos.y * src->right.y) +
                   (src->pos.z * src->right.z));
    dst->pos.y = -((src->pos.x * src->up.x) +
                   (src->pos.y * src->up.y) +
                   (src->pos.z * src->up.z));
    dst->pos.z = -((src->pos.x * src->at.x) +
                   (src->pos.y * src->at.y) +
                   (src->pos.z * src->at.z));

    dst->flags = 3;
  } else {
    FUN_004c2860(dst, src);
  }

  return dst;
}

/* P4: src/renderware/plcore/rwstring.c _rwStringStreamFindAndRead
   (func_003e4f60).  Walk the chunk stream until a string chunk appears,
   rejecting chunks outside the library version range.  P4 state: schedule
   on. */
extern u32 FUN_004c7520(u32 param_1, u32 param_2, u32 param_3);
extern u32 FUN_004c76c0(u32 param_1, u32 param_2, u32 param_3);

#pragma schedule on
// FUN_004C78A0
u32 FUN_004c78a0(u32 param_1, u32 param_2)
{
  u32 type;
  u32 length;
  u32 version;

  while (FUN_004c1450(param_2, &type, &length, &version, 0)) {
    const u32 valid = (version >= 0x35000) && (version <= 0x37002);

    if (!valid) {
      RwErrorB119 error;

      error.pluginID = 1;
      error.errorCode = FUN_004c1d10(0x80000004);
      FUN_004c1c50(&error);
      return 0;
    }

    if (type == 2) {
      return FUN_004c7520(param_1, param_2, length);
    }
    if (type == 0x13) {
      return FUN_004c76c0(param_1, param_2, length);
    }

    if (!FUN_004c5620((void *)param_2, length)) {
      return 0;
    }
  }

  return 0;
}

/* P4: src/renderware/plcore/babinary.c RwStreamFindChunk (func_003df050).
   Skip chunks until the wanted type shows up; the version must lie inside
   the library range, then the length/version out-params are filled.  P4
   state: schedule on. */
#pragma schedule on
// FUN_004C1600
void *FUN_004c1600(void *param_1, u32 param_2, void *param_3, void *param_4)
{
  u32 readType;
  u32 readLength;
  u32 readVersion;

  while (FUN_004c1450((u32)param_1, &readType, &readLength, &readVersion, 0)) {
    if (readType == param_2) {
      if (readVersion < 0x35000) {
        RwErrorB119 error;

        error.pluginID = 1;
        error.errorCode = FUN_004c1d10(0x80000004);
        FUN_004c1c50(&error);
        return 0;
      } else if (readVersion > 0x37002) {
        RwErrorB119 error;

        error.pluginID = 1;
        error.errorCode = FUN_004c1d10(0x80000004);
        FUN_004c1c50(&error);
        return 0;
      }

      if (param_3) {
        *(u32 *)param_3 = readLength;
      }
      if (param_4) {
        *(u32 *)param_4 = readVersion;
      }
      return (void *)1;
    }

    if (!FUN_004c5620(param_1, readLength)) {
      return 0;
    }
  }

  return 0;
}

/* P4: src/renderware/plcore/baplcore.c RwEngineOpen (func_003e8b10).  The
   static EngineOpen body is inlined: register the device, open it, then
   push the standard functions and bump the instance count.  P4 state:
   schedule on. */
extern void *FUN_004e2f00(void);
extern u8 DAT_00960080[];  /* RWSRCGLOBAL(dOpenDevice) */
extern u8 DAT_009600b8[];  /* RWSRCGLOBAL(stdFunc) */
extern u32 iGpffffbc38;    /* engineInstancesOpened */

#pragma schedule on
// FUN_004CA700
u32 FUN_004ca700(void *param_1)
{
  u32 result;

  result = (RWSRCGLOBALB119(engineStatus) == 1);
  if (result) {
    result = (param_1 != 0);
    if (result) {
      void *device = FUN_004e2f00();

      result = (device != 0);
      if (result) {
        FUN_004ca3e0(device, 4, DAT_00960080, DAT_00960178, 0);
        if (FUN_004ca3e0(device, 0, 0, param_1, 0)) {
          FUN_004ca3e0(device, 0xb, DAT_009600b8, 0, 0x1d);
          iGpffffbc38 = iGpffffbc38 + 1;
          result = 1;
        } else {
          result = 0;
        }
        if (result) {
          RWSRCGLOBALB119(engineStatus) = 2;
        }
      }
    } else {
      RwErrorB119 error;

      error.pluginID = 1;
      error.errorCode = FUN_004c1d10(0x80000016);
      FUN_004c1c50(&error);
    }
  } else {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0x80000001);
    FUN_004c1c50(&error);
  }

  return result;
}

/* P4: src/renderware/plcore/bastream.c RwStreamSkip (func_003e2ce0).  Skip
   bytes: file streams fseek and raise E_RW_ENDOFSTREAM at EOF, memory
   streams move the position within bounds, custom streams run their skip
   callback; an unknown type raises E_RW_INVSTREAMTYPE.  P4 state: schedule
   on. */
extern s32 FUN_004c0470(void *param_1, s64 param_2, s32 param_3);
extern s32 FUN_004c06b0(void *param_1);

#pragma schedule on
// FUN_004C5620
RwStreamB119 *FUN_004c5620(RwStreamB119 *stream, u32 offset)
{
  if (offset == 0) {
    return stream;
  }

  switch (stream->type) {
  case 2:
  case 1: {
      void *fp = ((RwStreamFileB119 *)stream)->fpFile;
      void *retVal;

      if (FUN_004c0470(fp, offset, 1)) {
        if (FUN_004c06b0(fp)) {
          RwErrorB119 error;

          error.pluginID = 1;
          error.errorCode = FUN_004c1d10(5);
          FUN_004c1c50(&error);
        }
        retVal = 0;
      } else {
        retVal = stream;
      }

      return retVal;
    }
  case 3: {
      RwStreamMemoryB119 *smpMem = &stream->memory;

      if (smpMem->position + offset > smpMem->nSize) {
        RwErrorB119 error;

        smpMem->position = smpMem->nSize;
        error.pluginID = 1;
        error.errorCode = FUN_004c1d10(5);
        FUN_004c1c50(&error);
        return 0;
      }

      smpMem->position += offset;
      return stream;
    }
  case 4: {
      RwStreamCustomB119 *custom = (RwStreamCustomB119 *)stream;

      if (((u32(*)(void *, u32))custom->sfnskip)(custom->data, offset)) {
        return stream;
      }
      return 0;
    }
  default: {
      RwErrorB119 error;

      error.pluginID = 1;
      error.errorCode = FUN_004c1d10(0xe);
      FUN_004c1c50(&error);
      return 0;
    }
  }
}

/* P4: src/renderware/plcore/bastream.c RwStreamRead (func_003e2910).  Read
   bytes: file streams fread and report E_RW_ENDOFSTREAM/E_RW_READ on a
   short read, memory streams clamp to the remaining size, custom streams
   call their read callback; an unknown type raises E_RW_INVSTREAMTYPE.  P4
   state: schedule on. */
extern u32 FUN_004c03d0(void *param_1, u32 param_2, u32 param_3,
                        void *param_4);

#pragma schedule on
// FUN_004C5250
u32 FUN_004c5250(RwStreamB119 *stream, void *buffer, u32 length)
{
  switch (stream->type) {
  case 2:
  case 1: {
    void *fp = ((RwStreamFileB119 *)stream)->fpFile;
    u32 nBytesRead = FUN_004c03d0(buffer, 1, length, fp);

    if (nBytesRead != length) {
      if (FUN_004c06b0(fp)) {
        RwErrorB119 error;

        error.pluginID = 1;
        error.errorCode = FUN_004c1d10(5);
        FUN_004c1c50(&error);
      } else {
        RwErrorB119 error;

        error.pluginID = 1;
        error.errorCode = FUN_004c1d10(0x8000001a);
        FUN_004c1c50(&error);
      }
    }

    return nBytesRead;
  }
  case 3: {
    RwStreamMemoryB119 *smpMem = &stream->memory;

    if (length > smpMem->nSize - smpMem->position) {
      RwErrorB119 error;

      length = smpMem->nSize - smpMem->position;
      error.pluginID = 1;
      error.errorCode = FUN_004c1d10(5);
      FUN_004c1c50(&error);
    }

    FUN_00521250(buffer, &smpMem->memBlock[smpMem->position], length);
    smpMem->position += length;

    return length;
  }
  case 4: {
    RwStreamCustomB119 *custom = (RwStreamCustomB119 *)stream;

    return ((u32(*)(void *, void *, u32))custom->sfnread)(custom->data, buffer,
                                                          length);
  }
  default: {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0xe);
    FUN_004c1c50(&error);
    return 0;
  }
  }
}

/* P4: src/renderware/plcore/bamatrix.c RwMatrixTranslate (func_003e0c90).
   Replace sets the identity then the position; pre-concat adds translation
   in the matrix's own space (rows dotted against the translation), post-
   concat adds it in world space; bad combination types raise E_RW_BADPARAM
   and return NULL.  The identity bit is cleared on the way out.  P4 state:
   schedule on. */
#pragma schedule on
// FUN_004C35D0
RwMatrix *FUN_004c35d0(RwMatrix *matrix, const RwV3d *translation,
                       u32 combineOp)
{
  switch (combineOp) {
  case 0: {
    matrix->right.x = matrix->up.y = matrix->at.z = 1.0f;
    matrix->right.y = matrix->right.z = matrix->up.x = 0.0f;
    matrix->up.z = matrix->at.x = matrix->at.y = 0.0f;
    matrix->pos.x = matrix->pos.y = matrix->pos.z = 0.0f;
    matrix->flags = matrix->flags | (0x20000 | 3);

    matrix->pos.x = translation->x;
    matrix->pos.y = translation->y;
    matrix->pos.z = translation->z;
    break;
  }
  case 1: {
    matrix->pos.x =
        matrix->pos.x + ((translation->x * matrix->right.x) +
                         (translation->y * matrix->up.x) +
                         (translation->z * matrix->at.x));
    matrix->pos.y =
        matrix->pos.y + ((translation->x * matrix->right.y) +
                         (translation->y * matrix->up.y) +
                         (translation->z * matrix->at.y));
    matrix->pos.z =
        matrix->pos.z + ((translation->x * matrix->right.z) +
                         (translation->y * matrix->up.z) +
                         (translation->z * matrix->at.z));
    break;
  }
  case 2: {
    matrix->pos.x = matrix->pos.x + translation->x;
    matrix->pos.y = matrix->pos.y + translation->y;
    matrix->pos.z = matrix->pos.z + translation->z;
    break;
  }
  default: {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0x80000003, "Invalid combination type");
    FUN_004c1c50(&error);
    matrix = 0;
    break;
  }
  }

  matrix->flags = matrix->flags & ~0x20000;

  return matrix;
}

/* P4: src/renderware/plcore/bamatrix.c RwMatrixScale (func_003e0a90).
   Replace builds the identity then the diagonal scale; pre-concat scales
   each basis row by its own factor, post-concat scales component-wise per
   row including the position (turning it non-orthonormal); bad combination
   types raise E_RW_BADPARAM and return NULL.  P4 state: schedule on. */
#pragma schedule on
// FUN_004C33D0
RwMatrix *FUN_004c33d0(RwMatrix *matrix, const RwV3d *scale, u32 combineOp)
{
  switch (combineOp) {
  case 0: {
    matrix->right.x = matrix->up.y = matrix->at.z = 1.0f;
    matrix->right.y = matrix->right.z = matrix->up.x = 0.0f;
    matrix->up.z = matrix->at.x = matrix->at.y = 0.0f;
    matrix->pos.x = matrix->pos.y = matrix->pos.z = 0.0f;
    matrix->flags = matrix->flags | (0x20000 | 3);

    matrix->right.x = scale->x;
    matrix->up.y = scale->y;
    matrix->at.z = scale->z;
    break;
  }
  case 1: {
    matrix->right.x = matrix->right.x * scale->x;
    matrix->right.y = matrix->right.y * scale->x;
    matrix->right.z = matrix->right.z * scale->x;
    matrix->up.x = matrix->up.x * scale->y;
    matrix->up.y = matrix->up.y * scale->y;
    matrix->up.z = matrix->up.z * scale->y;
    matrix->at.x = matrix->at.x * scale->z;
    matrix->at.y = matrix->at.y * scale->z;
    matrix->at.z = matrix->at.z * scale->z;
    break;
  }
  case 2: {
    matrix->right.x = matrix->right.x * scale->x;
    matrix->right.y = matrix->right.y * scale->y;
    matrix->right.z = matrix->right.z * scale->z;
    matrix->up.x = matrix->up.x * scale->x;
    matrix->up.y = matrix->up.y * scale->y;
    matrix->up.z = matrix->up.z * scale->z;
    matrix->at.x = matrix->at.x * scale->x;
    matrix->at.y = matrix->at.y * scale->y;
    matrix->at.z = matrix->at.z * scale->z;
    matrix->pos.x = matrix->pos.x * scale->x;
    matrix->pos.y = matrix->pos.y * scale->y;
    matrix->pos.z = matrix->pos.z * scale->z;
    break;
  }
  default: {
    RwErrorB119 error;

    error.pluginID = 1;
    error.errorCode = FUN_004c1d10(0x80000003, "Invalid combination type");
    FUN_004c1c50(&error);
    matrix = 0;
    break;
  }
  }

  matrix->flags = matrix->flags & ~(0x20000 | 3);

  return matrix;
}

/* P4: src/renderware/plcore/babinary.c ChunkIsComplex (func_003ded20).  Only
   container chunk types are "complex" (their payload is a chunk list, not a
   struct); struct/string/extension/light chunks are simple.  P4 state:
   schedule on. */
#pragma schedule on
// FUN_004C12D0
u32 FUN_004c12d0(void *param_1)
{
  u32 result = 0;

  switch (*(u32 *)param_1) {
  case 1: {
    result = 0;
    break;
  }
  case 2: {
    result = 0;
    break;
  }
  case 3: {
    result = 0;
    break;
  }
  case 5: {
    result = 1;
    break;
  }
  case 6: {
    result = 1;
    break;
  }
  case 7: {
    result = 1;
    break;
  }
  case 8: {
    result = 1;
    break;
  }
  case 9: {
    result = 1;
    break;
  }
  case 10: {
    result = 1;
    break;
  }
  case 0xb: {
    result = 1;
    break;
  }
  case 0xd: {
    result = 0;
    break;
  }
  case 0xe: {
    result = 1;
    break;
  }
  case 0xf: {
    result = 1;
    break;
  }
  case 0x10: {
    result = 1;
    break;
  }
  case 0x12: {
    result = 1;
    break;
  }
  case 0x13: {
    result = 0;
    break;
  }
  case 0x14: {
    result = 1;
    break;
  }
  case 0x1a: {
    result = 1;
    break;
  }
  default: {
    result = 0;
    break;
  }
  }

  return result;
}
