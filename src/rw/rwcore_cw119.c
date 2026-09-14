#include "rw/rwcore.h"
#include "mw_harvest_compat.h"

/* RenderWare Graphics 3.7 block, built with MWCCPS2 3.0.1 b119 (see
   config/compiler_units.txt).  Retail linked the RenderWare library as a
   prebuilt object; the Persona 4 tree carries matched source bodies of the
   same build, so functions whose b210 spelling cannot reach retail land here.
   Bodies keep the Persona 3 symbols and raw struct offsets; the comment above
   each names the Persona 4 twin they were ported from. */

extern code DAT_009600f8[];


/* P4: src/renderware/core/baraster.c RwRasterUnlock (func_003ec2a0).
   P4 state: schedule on. */
#pragma schedule on
// FUN_004CDE00
void *FUN_004cde00(void *param_1)
{
  (*DAT_009600f8)(0, param_1, 0);
  return param_1;
}

/* P4: src/renderware/p2/bapipe.c _rwRenderPipelineOpen (func_00410ed0).
   P4 state: schedule on. */
extern u32 uGpffffbe38;
extern u32 FUN_004f2a00(void);

#pragma schedule on
// FUN_004F2870
void *FUN_004f2870(void *param_1, s32 param_2)
{
  void *result;

  uGpffffbe38 = param_2;
  result = FUN_004f2a00() ? param_1 : 0;
  return result;
}

/* P4: src/renderware/core/bacamera.c RwCameraClear (func_003e82a0).
   P4 state: schedule on. */
#pragma schedule on
// FUN_004C9E90
RwCamera *FUN_004c9e90(RwCamera *camera, RwRGBA *colors, RwCameraClearMode clearMode)
{
  RwStandardFunc cameraClearFunc;
  RwCamera *result;

  cameraClearFunc = RWSTDFUNC(rwSTANDARDCAMERACLEAR);
  result = cameraClearFunc(camera, colors, clearMode) ? camera : 0;
  return result;
}

/* P4: src/renderware/core/batypehf.c _rwObjectHasFrameReleaseFrame
   (func_003efda0).  P4 state: schedule on. */
#pragma schedule on
// FUN_004D18C0
void FUN_004d18c0(void *param_1)
{
  u8 *ohf = (u8 *)param_1;

  if (*(u32 *)(ohf + 4) != 0)
  {
    *(u32 *)(*(u32 *)(ohf + 0xc)) = *(u32 *)(ohf + 8);
    *(u32 *)(*(u32 *)(ohf + 8) + 4) = *(u32 *)(ohf + 0xc);
  }
}

/* P4: src/renderware/core/baframe.c _rwFrameCloneAndLinkClones
   (func_003e90f0).  P4 state: schedule on. */
extern void *FUN_004cab70(void *, void *);
extern void FUN_004cb270(void *);

#pragma schedule on
// FUN_004CACE0
void *FUN_004cace0(void *param_1)
{
  void *lVar1;

  lVar1 = FUN_004cab70(param_1, 0);
  if (lVar1 != 0)
  {
    *(u8 *)((u8 *)lVar1 + 3) = *(u8 *)((u8 *)lVar1 + 3) & ~3;
    FUN_004cb270(lVar1);
  }
  return lVar1;
}

/* P4: src/renderware/core/baframe.c RwFrameGetLTM (func_003e9700).
   P4 state: schedule on. */
extern void FUN_004cf4c0(void *);

#pragma schedule on
// FUN_004CB2F0
void *FUN_004cb2f0(void *param_1)
{
  u8 *frame = (u8 *)param_1;

  if ((*(u8 *)(*(u32 *)(frame + 0xa0) + 3) & 1) != 0)
  {
    FUN_004cf4c0(*(void **)(frame + 0xa0));
  }
  return frame + 0x50;
}

/* P4: src/renderware/core/baimage.c RwImageFreePixels (func_003ea510).
   P4 state: schedule on. */
extern void (*DAT_0096017c[])(void *);

#pragma schedule on
// FUN_004CC050
void *FUN_004cc050(void *param_1)
{
  u32 *image = (u32 *)param_1;

  (*DAT_0096017c)((void *)image[5]);
  image[5] = 0;
  image[6] = 0;
  *image = *image & ~1u;
  return param_1;
}

/* P4: src/renderware/core/baraster.c RwRasterUnlockPalette (func_003ec2e0).
   P4 state: schedule on. */
extern void (*DAT_00960118[])(s32, void *, s32);

#pragma schedule on
// FUN_004CDE40
void *FUN_004cde40(void *param_1)
{
  u8 *raster = (u8 *)param_1;

  (*DAT_00960118)(0, param_1, 0);
  raster[0x22] = *(u8 *)(raster + 0x22) & ~0x18;
  return param_1;
}

/* P4: src/renderware/core/baraster.c RwRasterLockPalette (func_003ec3d0).
   P4 state: schedule on. */
extern s32 (*DAT_00960114[])(void *, void *, s32);

#pragma schedule on
// FUN_004CDF30
void *FUN_004cdf30(void *param_1, s32 param_2)
{
  void *palettePtr;
  void *result;

  result = (*DAT_00960114)(&palettePtr, param_1, param_2) ? palettePtr : 0;
  return result;
}

/* P4: src/renderware/core/baraster.c RwRasterLock (func_003ec6a0).
   P4 state: schedule on. */
extern s32 (*DAT_009600f4[])(void *, void *, s32);

#pragma schedule on
// FUN_004CE200
void *FUN_004ce200(void *param_1, u32 param_2, s32 param_3)
{
  void *pixelPtr;
  void *result;

  result = (*DAT_009600f4)(&pixelPtr, param_1,
                           param_3 + (param_2 & 0xff) * 0x100) ? pixelPtr : 0;
  return result;
}

/* P4: src/renderware/core/batextur.c RwTextureSetRaster (func_003ef080).
   P4 state: schedule on. */
extern s32 (*DAT_009600d8[])(void *, void *, s32);

#pragma schedule on
// FUN_004D0BE0
void *FUN_004d0be0(void *param_1, void *param_2)
{
  if (param_2 != 0)
  {
    return (*DAT_009600d8)(param_1, param_2, 0) ? param_1 : 0;
  }
  else
  {
    *(u32 *)param_1 = 0;
    return param_1;
  }
}

/* P4: src/renderware/core/bacamera.c CameraEndUpdate (func_003e7f50).
   P4 state: schedule on. */
#pragma schedule on
// FUN_004C9B40
RwCamera *FUN_004c9b40(RwCamera *camera)
{
  RwStandardFunc cameraEndUpdateFunc;

  cameraEndUpdateFunc = RWSTDFUNC(rwSTANDARDCAMERAENDUPDATE);
  if (!cameraEndUpdateFunc(NULL, camera, 0))
  {
    return NULL;
  }

  RwCameraGetCurrentCamera() = NULL;
  return camera;
}

/* P4: src/renderware/core/baraster.c RwRasterGetNumLevels (func_003ec420).
   P4 state: schedule on. */
extern s32 (*DAT_00960128[])(void *, void *, s32);

#pragma schedule on
// FUN_004CDF80
s32 FUN_004cdf80(void *param_1)
{
  s32 numMipLevels;

  if (((*(u8 *)((u8 *)param_1 + 0x23) << 8) & 0x8000) == 0)
  {
    return 1;
  }

  return (*DAT_00960128)(&numMipLevels, param_1, 0) ? numMipLevels : -1;
}

/* P4: src/renderware/core/batextur.c RwTexDictionaryAddTexture
   (func_003ef5b0).  P4 state: schedule on. */
#pragma schedule on
// FUN_004D1110
void *FUN_004d1110(void *param_1, void *param_2)
{
  u8 *dict = (u8 *)param_1;
  u8 *texture = (u8 *)param_2;

  if (*(u32 *)(texture + 4) != 0)
  {
    *(u32 *)(*(u32 *)(texture + 0xc)) = *(u32 *)(texture + 8);
    *(u32 *)(*(u32 *)(texture + 8) + 4) = *(u32 *)(texture + 0xc);
  }
  *(u32 *)(texture + 4) = (u32)dict;
  *(u32 *)(texture + 8) = *(u32 *)(dict + 8);
  *(u32 *)(texture + 0xc) = (u32)(dict + 8);
  *(u32 *)(*(u32 *)(dict + 8) + 4) = (u32)(texture + 8);
  *(u32 *)(dict + 8) = (u32)(texture + 8);
  return param_2;
}

/* P4: src/renderware/core/bacamera.c RwCameraSetViewWindow (func_003e83a0).
   P4 state: schedule on. */
#pragma schedule on
// FUN_004C9F90
RwCamera *FUN_004c9f90(RwCamera *camera, const RwV2d *viewWindow)
{
  RwFrame *frame;

  camera->viewWindow = *viewWindow;
  camera->recipViewWindow.x = 1.0f / camera->viewWindow.x;
  camera->recipViewWindow.y = 1.0f / camera->viewWindow.y;
  frame = (RwFrame *)camera->object.object.parent;
  if (frame == 0)
  {
    goto done;
  }
  FUN_004cb270(frame);
done:
  return camera;
}

/* P4: src/renderware/core/baframe.c RwFrameCreate (func_003e9320).
   P4 state: schedule on. */
extern u8 DAT_00960070[];
extern void *(*DAT_00960188[])(u32, s32);
extern int iGpffffbc40;
extern void FUN_004cae40(void *);

#pragma schedule on
// FUN_004CAF10
void *FUN_004caf10(void)
{
  void *lVar1;

  lVar1 = (*DAT_00960188)(*(u32 *)((u8 *)DAT_00960070 + iGpffffbc40), 0x3000e);
  if (lVar1 == 0)
  {
    return 0;
  }
  FUN_004cae40(lVar1);
  return lVar1;
}

/* P4: src/renderware/core/baframe.c RwFrameForAllChildren (func_003e9af0).
   P4 state: schedule on. */
#pragma schedule on
// FUN_004CB6E0
void *FUN_004cb6e0(void *param_1, code param_2, void *param_3)
{
  u8 *frame = (u8 *)param_1;
  u8 *childFrame;
  u8 *nextChildFrame;

  childFrame = *(u8 **)(frame + 0x98);
  while (childFrame)
  {
    nextChildFrame = *(u8 **)(childFrame + 0x9c);
    if (!(*param_2)(childFrame, param_3))
    {
      return param_1;
    }
    childFrame = nextChildFrame;
  }
  return param_1;
}

/* P4: src/renderware/core/baimage.c RwImageDestroy (func_003ea370).
   P4 state: schedule on. */
extern void FUN_004c6560(void *, void *);
extern s32 (*DAT_0096018c[])(void *, void *);
extern int iGpffffbc48;
extern u8 D_0077E690[];

#pragma schedule on
#pragma alias FUN_004cc050_call FUN_004cc050
extern void FUN_004cc050_call(void *);
// FUN_004CBEB0
u32 FUN_004cbeb0(void *param_1)
{
  u8 *image = (u8 *)param_1;

  if ((*(u32 *)image & 1) != 0)
  {
    FUN_004cc050_call(param_1);
  }
  FUN_004c6560((void *)D_0077E690, param_1);
  (*DAT_0096018c)((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc48), param_1);
  return 1;
}

/* P4: src/renderware/core/baimras.c RwImageSetFromRaster (func_003ec110).
   P4 state: schedule on. */
extern s32 (*DAT_009600d0[])(void *, void *, s32);

#pragma schedule on
// FUN_004CDC70
void *FUN_004cdc70(void *param_1, void *param_2)
{
  if ((*DAT_009600d0)(param_1, param_2, 0))
  {
    if ((*(u8 *)((u8 *)param_2 + 0x22) & 1) != 0)
    {
      *(u32 *)param_1 |= 2;
    }
    return param_1;
  }
  return 0;
}

/* P4: src/renderware/core/baimras.c RwRasterSetFromImage (func_003ec180).
   P4 state: schedule on. */
extern s32 (*DAT_009600d4[])(void *, void *, s32);

#pragma schedule on
// FUN_004CDCE0
void *FUN_004cdce0(void *param_1, void *param_2)
{
  if ((*DAT_009600d4)(param_1, param_2, 0))
  {
    if ((*(u32 *)param_2 & 2) != 0)
    {
      *(u8 *)((u8 *)param_1 + 0x22) |= 1;
    }
    return param_1;
  }
  return 0;
}

/* P4: src/renderware/core/baraster.c RwRasterDestroy (func_003ec330).
   P4 state: schedule on. */
extern s32 (*DAT_009600cc[])(void *, void *, s32);
extern int iGpffffbc50;
extern u8 D_0077E6B0[];

#pragma schedule on
// FUN_004CDE90
u32 FUN_004cde90(void *param_1)
{
  FUN_004c6560((void *)D_0077E6B0, param_1);
  (*DAT_009600cc)(0, param_1, 0);
  (*DAT_0096018c)((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x60), param_1);
  return 1;
}

/* P4: src/renderware/core/baraster.c RwRasterShowRaster (func_003ec480).
   P4 state: schedule on. */
extern void FUN_004c4890(void);
extern s32 (*DAT_00960108[])(void *, void *, s32);

#pragma schedule on
// FUN_004CDFE0
void *FUN_004cdfe0(void *param_1, void *param_2, s32 param_3)
{
  s32 (*func)(void *, void *, s32);
  void *result;

  func = DAT_00960108[0];
  FUN_004c4890();
  result = (*func)(param_1, param_2, param_3) ? param_1 : 0;
  return result;
}

/* P4: src/renderware/core/basync.c _rwFrameSyncDirty (func_003ed7e0).
   P4 state: schedule on. */
extern void FUN_004cf1b0(RwFrame *);
extern u32 DAT_0096012c[];
extern u32 DAT_00960130[];

#pragma schedule on
// FUN_004CF340
u32 FUN_004cf340(void)
{
  u32 *link;
  u32 *list = (u32 *)DAT_0096012c;

  link = (u32 *)list[0];
  while (link != list)
  {
    FUN_004cf1b0((RwFrame *)((u8 *)link - 8));
    link = (u32 *)*link;
  }
  list[0] = (u32)list;
  DAT_00960130[0] = (u32)list;
  return 1;
}

/* P4: src/renderware/p2/baim3d.c RwIm3DSetTransformPipeline (func_00410a40).
   P4 state: schedule on. */
extern int iGpffffbe30;

#pragma schedule on
// FUN_004F23C0
void *FUN_004f23c0(void *param_1)
{
  if (param_1 != 0)
  {
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbe30) = (u32)param_1;
  }
  else if (*(u32 *)((u8 *)DAT_00960070 + iGpffffbe30 + 0x1c) != 0)
  {
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbe30) =
        *(u32 *)((u8 *)DAT_00960070 + iGpffffbe30 + 0x1c);
  }
  else
  {
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbe30) = 0;
  }
  return (void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbe30);
}

/* P4: src/renderware/p2/p2core.c _rxPipelineClose (func_00410ff0).
   P4 state: schedule on. */
extern void FUN_004c3c30(void *);
extern void FUN_004f6970(u32);
extern int iGpffffbe38;
extern int iGpffffbe3c;
extern u32 uGpffffbe40;

#pragma schedule on
// FUN_004F2990
u32 FUN_004f2990(void)
{
  if (iGpffffbe3c != 0)
  {
    FUN_004c3c30((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbe38));
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbe38) = 0;
    FUN_004f6970(uGpffffbe40);
    uGpffffbe40 = 0;
    iGpffffbe3c = 0;
  }
  return 1;
}

/* P4: src/renderware/core/batypehf.c _rwObjectHasFrameSetFrame (func_003efd20).
   P4 state: schedule on. */
#pragma schedule on
// FUN_004D1840
void FUN_004d1840(void *param_1, void *param_2)
{
  u8 *object = (u8 *)param_1;
  u8 *frame = (u8 *)param_2;

  if (*(u32 *)(object + 4) != 0)
  {
    *(u32 *)(*(u32 *)(object + 0xc)) = *(u32 *)(object + 8);
    *(u32 *)(*(u32 *)(object + 8) + 4) = *(u32 *)(object + 0xc);
  }
  *(u32 *)(object + 4) = (u32)frame;
  if (frame != 0)
  {
    *(u32 *)(object + 8) = *(u32 *)(frame + 0x90);
    *(u32 *)(object + 0xc) = (u32)(frame + 0x90);
    *(u32 *)(*(u32 *)(frame + 0x90) + 4) = (u32)(object + 8);
    *(u32 *)(frame + 0x90) = (u32)(object + 8);
    FUN_004cb270(frame);
  }
}

/* P4: src/renderware/core/bacamera.c RwCameraSetProjection (func_003e8310). */
extern u32 FUN_004c1d10(u32, ...);
extern void FUN_004c1c50(void *);
extern void FUN_004c89a0(void *);
extern char D_0077E600[];

#pragma schedule on
// FUN_004C9F00
RwCamera *FUN_004c9f00(RwCamera *camera, RwCameraProjection projection)
{
  u32 error[2];

  switch (projection)
  {
    case rwPARALLEL:
    case rwPERSPECTIVE:
      camera->projType = projection;
      if (camera->object.object.parent != 0)
      {
        FUN_004cb270(camera->object.object.parent);
      }
      FUN_004c89a0(camera);
      return camera;
    default:
      error[0] = 1;
      error[1] = FUN_004c1d10(0x80000003, D_0077E600);
      FUN_004c1c50(error);
      return 0;
  }
}

/* P4: src/renderware/core/bacamera.c RwCameraFrustumTestSphere (func_003e8200). */
#pragma schedule on
// FUN_004C9DF0
RwFrustumTestResult FUN_004c9df0(const RwCamera *camera, const RwSphere *sphere)
{
  const RwFrustumPlane *frustumPlane;
  RwInt32 numPlanes;
  RwFrustumTestResult result;

  result = rwSPHEREINSIDE;
  frustumPlane = camera->frustumPlanes;
  numPlanes = 6;
  while (numPlanes--)
  {
    RwReal nDot;

    nDot = sphere->center.x * frustumPlane->normal.x +
           sphere->center.y * frustumPlane->normal.y +
           sphere->center.z * frustumPlane->normal.z;
    nDot -= frustumPlane->distance;

    if (nDot > sphere->radius)
    {
      return rwSPHEREOUTSIDE;
    }
    else if (nDot > (-sphere->radius))
    {
      result = rwSPHEREBOUNDARY;
    }
    frustumPlane++;
  }
  return result;
}

/* P4: src/renderware/core/batextur.c TextureDefaultFind (func_003eef60). */
extern u8 *FUN_004d1170(void *, void *);
extern int iGpffffbc60;

#pragma schedule on
// FUN_004D0AC0
u8 *FUN_004d0ac0(void *param_1)
{
  u8 *name;
  u8 *globals;
  u8 *dict;
  u8 *cur;
  u8 *result;

  name = (u8 *)param_1;
  globals = (u8 *)DAT_00960070 + iGpffffbc60;
  dict = *(u8 **)(globals + 0x10);
  if (dict)
  {
    result = FUN_004d1170(dict, name);
    return result;
  }
  cur = *(u8 **)globals;
  while (cur != globals)
  {
    dict = cur - 0x10;
    result = FUN_004d1170(dict, name);
    if (result)
    {
      return result;
    }
    cur = *(u8 **)cur;
  }
  return 0;
}

/* P4: src/renderware/p2/p2altmdl.c _rxPacketDestroy (func_00410f50). */
extern void FUN_004f65b0(void *, void *);

#pragma schedule on
// FUN_004F28F0
void FUN_004f28f0(void *param_1)
{
  u8 *packet = (u8 *)param_1;
  u32 n;
  u8 *cl;
  u8 *pipeline;

  pipeline = *(u8 **)(packet + 4);
  *(u32 *)(pipeline + 0x10) = 1;
  n = *(u16 *)(packet + 2);
  cl = packet + 0x14;
  do
  {
    if (*(u32 *)(cl + 0x14) != 0)
    {
      if (*(u32 *)(cl + 4) != 0 && (*(u16 *)cl & 2) == 0)
      {
        FUN_004f65b0((void *)uGpffffbe40, *(void **)(cl + 4));
      }
      *(u32 *)cl = 0;
      *(u32 *)(cl + 4) = 0;
      *(u32 *)(cl + 0xc) = 0;
      *(u32 *)(cl + 0x10) = 0;
      *(u32 *)(cl + 0x14) = 0;
    }
    n--;
    cl += 0x1c;
  } while (n != 0);
  *(u16 *)packet = 0;
}

/* P4: src/renderware/p2/p2core.c RxPipelineCreate (func_004115d0). */
extern void FUN_00521408(void *, u32, u32);

#pragma schedule on
// FUN_004F2F70
void *FUN_004f2f70(void)
{
  u32 error[2];
  void *pipeline;

  pipeline = (*DAT_00960188)(*(u32 *)((u8 *)DAT_00960070 + iGpffffbe38), 0x30409);
  if (pipeline != 0)
  {
    FUN_00521408(pipeline, 0, 0x34);
    *(u32 *)pipeline = 0;
    return pipeline;
  }
  error[0] = 1;
  error[1] = FUN_004c1d10(0x80000013, 0x34);
  FUN_004c1c50(error);
  return 0;
}

/* P4: src/renderware/core/baframe.c rwSetHierarchyRoot (func_003e8ed0). */
#pragma schedule on
// FUN_004CAAC0
void FUN_004caac0(RwFrame *frame, RwFrame *root)
{
  frame->root = root;
  frame = frame->child;
  while (frame != 0)
  {
    FUN_004caac0(frame, root);
    frame = frame->next;
  }
}

/* P4: src/renderware/core/batextur.c RwTexDictionaryDestroy (func_003ef1b0). */
extern void FUN_004d0dc0(void *, code, void *);
extern u32 FUN_004d0f00(void *);
extern u8 D_0077E6F0[];

#pragma schedule on
// FUN_004D0D10
u32 FUN_004d0d10(void *param_1)
{
  u8 *dict = (u8 *)param_1;

  if (*(u8 **)((u8 *)DAT_00960070 + iGpffffbc60 + 0x10) == dict)
  {
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbc60 + 0x10) = 0;
  }
  FUN_004d0dc0(dict, (code)FUN_004d0f00, 0);
  FUN_004c6560((void *)D_0077E6F0, dict);
  *(u32 *)(*(u32 *)(dict + 0x14)) = *(u32 *)(dict + 0x10);
  *(u32 *)(*(u32 *)(dict + 0x10) + 4) = *(u32 *)(dict + 0x14);
  (*DAT_0096018c)((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc60 + 0xc), dict);
  return 1;
}

/* P4: src/renderware/p2/p2define.c RxPipelineNodeCreateInitData (func_00412520). */
extern void *(*DAT_00960178[])(u32, s32);

#pragma schedule on
// FUN_004F3EC0
void *FUN_004f3ec0(void *param_1, u32 param_2)
{
  u8 *node = (u8 *)param_1;
  u32 error[2];

  if (*(void **)(node + 0x20) != 0)
  {
    (*DAT_0096017c)(*(void **)(node + 0x20));
    *(void **)(node + 0x20) = 0;
    *(u32 *)(node + 0x24) = 0;
  }
  *(void **)(node + 0x20) = (*DAT_00960178)(param_2, 0x30409);
  if (*(void **)(node + 0x20) == 0)
  {
    error[0] = 1;
    error[1] = FUN_004c1d10(0x80000013, param_2);
    FUN_004c1c50(error);
    return 0;
  }
  *(u32 *)(node + 0x24) = param_2;
  return *(void **)(node + 0x20);
}

/* P4: src/renderware/core/baframe.c RwFrameSetIdentity (func_003e9df0).
   RwFrameUpdateObjects (same P4 unit) is inlined by the retail build, so its
   body is spelled out here: private flags 3/0xC mirror
   rwFRAMEPRIVATEHIERARCHYSYNC* / rwFRAMEPRIVATESUBTREESYNC*. */
#pragma schedule on
// FUN_004CB930
void *FUN_004cb930(RwFrame *frame)
{
  RwUInt8 oldFlags;

  RwMatrixSetIdentity(&frame->modelling);

  oldFlags = frame->root->object.privateFlags;
  if ((oldFlags & 3) == 0)
  {
    RwLinkList *dirtyList = (RwLinkList *)DAT_0096012c;

    frame->root->inDirtyListLink.next = dirtyList->link.next;
    frame->root->inDirtyListLink.prev = (RwLLLink *)dirtyList;
    dirtyList->link.next->prev = &frame->root->inDirtyListLink;
    dirtyList->link.next = &frame->root->inDirtyListLink;
  }
  frame->root->object.privateFlags = oldFlags | 3;
  frame->object.privateFlags |= 0xc;
  return frame;
}

/* P4: src/renderware/core/baframe.c RwFrameDestroy (func_003e9390).
   P4 state: schedule on. */
extern void FUN_004cb590(void *);
extern u8 D_0077E670[];

#pragma schedule on
// FUN_004CAF80
u32 FUN_004caf80(void *param_1)
{
  u8 *frame = (u8 *)param_1;
  u8 *child;

  FUN_004c6560((void *)D_0077E670, frame);
  if (*(u32 *)(frame + 4) != 0)
  {
    FUN_004cb590(frame);
  }
  if ((*(u8 *)(frame + 3) & 3) != 0)
  {
    *(u32 *)(*(u32 *)(frame + 0xc)) = *(u32 *)(frame + 8);
    *(u32 *)(*(u32 *)(frame + 8) + 4) = *(u32 *)(frame + 0xc);
  }
  child = *(u8 **)(frame + 0x98);
  while (child != 0)
  {
    *(u32 *)(child + 4) = 0;
    child = *(u8 **)(child + 0x9c);
  }
  (*DAT_0096018c)((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc40), frame);
  return 1;
}

/* P4: src/renderware/core/baframe.c RwFrameAddChildNoUpdate (func_003e9760).
   rwSetHierarchyRoot (same P4 unit) is auto-inlined by the retail build and
   FUN_004caac0 above is its P3 twin, so -inline auto reproduces the shape.
   P4 state: schedule on. */
#pragma schedule on
// FUN_004CB350
RwFrame *FUN_004cb350(RwFrame *parent, RwFrame *child)
{
  if ((RwFrame *)child->object.parent)
  {
    FUN_004cb590(child);
  }

  child->next = parent->child;
  parent->child = child;
  child->object.parent = parent;
  FUN_004caac0(child, parent->root);
  return parent;
}

/* P4: src/renderware/core/batextur.c TextureDefaultMipmapName (func_003eda60).
   CalculateIndexCharacter (same P4 unit) is auto-inlined by the retail build;
   the ternary below is its body.  rwstrcat is the stringFuncs.vecStrcat slot of
   the engine globals (ourGlobals + 0x4494 = DAT_00960070 + 0xD4).
   P4 state: schedule on. */
extern const char s_0123456789abcdef_007bcc10[];

#pragma schedule on
// FUN_004CF5C0
u32 FUN_004cf5c0(char *param_1, char *param_2, u8 param_3, s32 param_4)
{
  char mip[3];

  mip[0] = 'm';
  mip[1] = (param_3 > 0 && param_3 < 0x10) ? s_0123456789abcdef_007bcc10[param_3] : 0;
  mip[2] = 0;
  if (mip[1] != 0)
  {
    (*(void (**)(char *, char *))((u8 *)DAT_00960070 + 0xD4))(param_1, mip);
    if (param_2 != 0 && param_2[0] != 0)
    {
      (*(void (**)(char *, char *))((u8 *)DAT_00960070 + 0xD4))(param_2, mip);
    }
  }
  return 1;
}

/* P4: src/renderware/core/batextur.c RwTextureDestroy (func_003ef3a0).
   TextureAnnihilate (same P4 unit) is inlined by the retail build; its body is
   spelled out here (its RWRETURN(TRUE) becomes the result assignment).
   RwRasterDestroy must stay a call, so it goes through the alias.
   P4 state: schedule on. */
extern u8 D_0077E6D0[];
extern u32 FUN_004cde90_call(void *);
#pragma alias FUN_004cde90_call FUN_004cde90

#pragma schedule on
// FUN_004D0F00
u32 FUN_004d0f00(void *param_1)
{
  u8 *texture = (u8 *)param_1;
  u32 result = 1;

  *(u32 *)(texture + 0x54) = *(u32 *)(texture + 0x54) - 1;
  if (*(s32 *)(texture + 0x54) <= 0)
  {
    *(u32 *)(texture + 0x54) = *(u32 *)(texture + 0x54) + 1;
    FUN_004c6560((void *)D_0077E6D0, texture);
    if (*(u32 *)(texture + 4) != 0)
    {
      *(u32 *)(*(u32 *)(texture + 0xc)) = *(u32 *)(texture + 8);
      *(u32 *)(*(u32 *)(texture + 8) + 4) = *(u32 *)(texture + 0xc);
    }
    if (*(u32 *)texture != 0)
    {
      FUN_004cde90_call((void *)*(u32 *)texture);
      *(u32 *)texture = 0;
    }
    *(u32 *)(texture + 0x54) = *(u32 *)(texture + 0x54) - 1;
    (*DAT_0096018c)((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc60 + 8), texture);
    result = 1;
  }
  return result;
}

/* P4: src/renderware/p2/p2core.c _rxPipelineOpen (func_00411060).
   P4 state: schedule on. */
extern u32 uGpffffb100;
extern u32 uGpffffb104;
extern u32 uGpffffb108;
extern u32 uGpffffb10c;
extern void *FUN_004f6a10(u32);
extern void FUN_004f6b50(void *);
extern s32 FUN_004c3b60(s32, s32, s32, s32, void *, s32);
extern u8 D_00965AA0[];

#pragma schedule on
// FUN_004F2A00
u32 FUN_004f2a00(void)
{
  if (iGpffffbe3c == 0)
  {
    void *heap = FUN_004f6a10(uGpffffb100);

    uGpffffbe40 = (u32)heap;
    if (heap == 0)
    {
      return 0;
    }
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbe38) =
        FUN_004c3b60(0x34, uGpffffb108, 4, uGpffffb10c, (void *)D_00965AA0, 0x40409);
    if (*(u32 *)((u8 *)DAT_00960070 + iGpffffbe38) == 0)
    {
      FUN_004f6970(uGpffffbe40);
      uGpffffbe40 = 0;
      return 0;
    }
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbe38 + 0x38) = uGpffffb104;
    FUN_004f6b50((void *)((u8 *)DAT_00960070 + iGpffffbe38 + 4));
    iGpffffbe3c = 1;
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbe38 + 0x34) = 0;
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbe38 + 0x30) = 0;
    return 1;
  }
  return 0;
}

/* P4: src/renderware/p2/p2core.c _rxPipelineDestroy (func_00411670).
   P4 state: schedule on. */
extern void FUN_004f2ad0(void *, void *);

#pragma schedule on
// FUN_004F3010
void FUN_004f3010(void *param_1)
{
  u8 *pipeline = (u8 *)param_1;

  if (pipeline != 0)
  {
    u32 numNodes, i;
    u8 *node = *(u8 **)(pipeline + 8);

    numNodes = *(u32 *)(pipeline + 4);
    for (i = 0; i < numNodes; i++)
    {
      FUN_004f2ad0(node, pipeline);
      node += 0x28;
    }
    *(u32 *)(pipeline + 8) = 0;
    if (*(u32 *)(pipeline + 0x20) != 0)
    {
      (*DAT_0096017c)((void *)*(u32 *)(pipeline + 0x20));
      *(u32 *)(pipeline + 0x20) = 0;
      *(u32 *)(pipeline + 0x24) = 0;
    }
    (*DAT_0096018c)((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbe38), pipeline);
  }
}

/* P4: src/renderware/core/baraster.c _rwRasterOpen (func_003ec760).
   P4 state: schedule on. */
extern u32 iGpffffbc54;
extern u32 uGpffffb090;
extern u32 uGpffffb094;
extern u8 D_00964100[];

#pragma schedule on
// FUN_004CE2C0
void *FUN_004ce2c0(void *param_1, s32 param_2)
{
  iGpffffbc50 = param_2;
  FUN_00521408((u8 *)DAT_00960070 + iGpffffbc50 + 0x2C, 0, 0x34);
  *(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x38) = 0;
  *(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x3C) = 0;
  *(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x40) = 0;
  *(u8 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x4D) = 0x80;
  *(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x30) = 0;
  *(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x34) = 0;
  *(u8 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x4C) = 0;
  *(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x28) = 0;
  *(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x00) = (u32)((u8 *)DAT_00960070 + iGpffffbc50 + 0x2C);
  *(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x60) =
      FUN_004c3b60(*(u32 *)D_0077E6B0, uGpffffb090, 4, uGpffffb094, (void *)D_00964100, 0x40407);
  if (*(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x60) == 0)
  {
    return 0;
  }
  iGpffffbc54 = iGpffffbc54 + 1;
  return param_1;
}

/* P4: src/renderware/core/batextur.c RwTexDictionaryCreate (func_003ef0d0).
   P4 state: schedule on. */
extern void FUN_004c64b0(void *, void *);

#pragma schedule on
// FUN_004D0C30
void *FUN_004d0c30(void)
{
  u8 *dict = (u8 *)(*DAT_00960188)(*(u32 *)((u8 *)DAT_00960070 + iGpffffbc60 + 0xC), 0x30016);

  if (dict == 0)
  {
    return 0;
  }
  *(u8 *)(dict + 0x0) = 6;
  *(u8 *)(dict + 0x1) = 0;
  *(u8 *)(dict + 0x2) = 0;
  *(u8 *)(dict + 0x3) = 0;
  *(u32 *)(dict + 0x4) = 0;
  *(u32 *)(dict + 0x10) = *(u32 *)((u8 *)DAT_00960070 + iGpffffbc60);
  *(u32 *)(dict + 0x14) = (u32)((u8 *)DAT_00960070 + iGpffffbc60);
  *(u32 *)(*(u32 *)((u8 *)DAT_00960070 + iGpffffbc60) + 0x4) = (u32)(dict + 0x10);
  *(u32 *)((u8 *)DAT_00960070 + iGpffffbc60) = (u32)(dict + 0x10);
  *(u32 *)(dict + 0x8) = (u32)(dict + 0x8);
  *(u32 *)(dict + 0xC) = (u32)(dict + 0x8);
  FUN_004c64b0((void *)D_0077E6F0, dict);
  return dict;
}

/* P4: src/renderware/core/baimage.c RwImageSetPath (func_003eaa80).
   P4 state: schedule on. */
extern s32 (*DAT_00960164[])(const char *);
extern void *(*DAT_00960180[])(void *, u32, u32);
extern void FUN_00521250(void *, const void *, u32);

#pragma schedule on
// FUN_004CC5C0
const char *FUN_004cc5c0(const char *param_1)
{
  s32 newPathLength = (*DAT_00960164)(param_1) + 1;

  if (*(s32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 8) < newPathLength)
  {
    u8 *newPath =
        (u8 *)(*DAT_00960180)((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 4), newPathLength, 0x1040406);

    if (newPath == 0)
    {
      u32 error[2];

      error[0] = 1;
      error[1] = FUN_004c1d10(0x80000013, newPathLength);
      FUN_004c1c50(error);
      return 0;
    }
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 4) = (u32)newPath;
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 8) = newPathLength;
  }
  FUN_00521250((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 4), param_1, newPathLength);
  return param_1;
}

/* P4: src/renderware/core/basync.c FrameSyncHierarchyRecurse (func_003ed450;
   static in the P4 unit).
   P4 state: schedule on. */
extern void FUN_004c2f30(void *, void *, void *);

#pragma schedule on
// FUN_004CEFB0
void FUN_004cefb0(RwFrame *frame, s32 flags)
{
  while (frame != 0)
  {
    s32 accumflags = flags | *(u8 *)((u8 *)frame + 3);

    if ((accumflags & 4) != 0)
    {
      FUN_004c2f30(&frame->ltm, &frame->modelling, &((RwFrame *)frame->object.parent)->ltm);
    }
    if (frame->objectList.link.next != &frame->objectList.link)
    {
      RwLLLink *current = frame->objectList.link.next;
      RwLLLink *end = &frame->objectList.link;

      while (current != end)
      {
        RwObjectHasFrame *object = (RwObjectHasFrame *)((u8 *)current - 8);

        object->sync(object);
        current = current->next;
      }
    }
    frame->object.privateFlags = *(u8 *)((u8 *)frame + 3) & ~0xc;
    FUN_004cefb0(frame->child, accumflags);
    frame = frame->next;
  }
}

/* P4: src/renderware/core/batextur.c StringCompare (func_003eee70; static in
   the P4 unit).
   P4 state: schedule on. */
#pragma schedule on
// FUN_004D09D0
u32 FUN_004d09d0(const char *param_1, const char *param_2)
{
  while ((*param_1) && (*param_2))
  {
    char cA = *param_1;
    char cB = *param_2;

    if ((cA >= 'a') && (cA <= 'z'))
    {
      cA += 'A' - 'a';
    }
    if ((cB >= 'a') && (cB <= 'z'))
    {
      cB += 'A' - 'a';
    }
    if (cA != cB)
    {
      return 0;
    }
    param_1++;
    param_2++;
  }
  if ((*param_1) == (*param_2))
  {
    return 1;
  }
  return 0;
}

/* P4: src/renderware/p2/p2define.c PipelineTallyInputs (func_00411ee0; static
   in the P4 unit).  The P2 Rx types are absent from the P3 headers, so the
   node layout is mirrored locally.
   P4 state: schedule on. */
struct RxPipelineNodeTopSortData_l
{
  u32 numIns;
  u32 numInsVisited;
};

struct RxPipelineNode_l
{
  void *nodeDef;
  u32 numOutputs;
  u32 *outputs;
  void *slotClusterRefs;
  u32 *slotsContinue;
  void *privateData;
  u32 *inputToClusterSlot;
  struct RxPipelineNodeTopSortData_l *topSortData;
  void *initializationData;
  u32 initializationDataSize;
};

struct RxPipeline_l
{
  u32 locked;
  u32 numNodes;
  struct RxPipelineNode_l *nodes;
  u32 packetNumClusterSlots;
  u32 embeddedPacketState;
  void *embeddedPacket;
  u32 numInputRequirements;
  void *inputRequirements;
  void *superBlock;
  u32 superBlockSize;
  u32 entryPoint;
};

#define ISNODELIVE(_node) (NULL != ((_node)->nodeDef))

#pragma schedule on
// FUN_004F3880
void FUN_004f3880(struct RxPipeline_l *pipeline)
{
  struct RxPipelineNode_l *nodes;
  u32 i;

  nodes = &pipeline->nodes[0];
  for (i = 0; i < pipeline->numNodes; i++)
  {
    if (ISNODELIVE(nodes))
    {
      nodes->topSortData->numInsVisited = 0;
      nodes->topSortData->numIns = 0;
    }
    nodes++;
  }

  nodes = &pipeline->nodes[0];
  for (i = 0; i < pipeline->numNodes; i++)
  {
    if (ISNODELIVE(nodes))
    {
      if (nodes->numOutputs != 0)
      {
        int j = nodes->numOutputs;
        u32 *outputs = &nodes->outputs[0];

        do
        {
          if (*(int *)outputs != -1)
          {
            pipeline->nodes[*outputs].topSortData->numIns++;
          }
        } while (outputs++, --j);
      }
    }
    nodes++;
  }
}

/* P4: src/renderware/core/baframe.c _rwFramePurgeClone (func_003e9140).
   rwSetHierarchyRoot (same P4 unit) is auto-inlined by the retail build and
   FUN_004caac0 above is its P3 twin, so -inline auto reproduces the shape.
   P4 state: schedule on. */
#pragma schedule on
// FUN_004CAD30
RwFrame *FUN_004cad30(RwFrame *root)
{
  RwFrame *parent = (RwFrame *)root->object.parent;

  if (parent)
  {
    FUN_004caac0(root, parent->root);
  }
  else
  {
    FUN_004caac0(root, root);
  }
  return root;
}

/* P4: src/renderware/core/batextur.c PalettizeImage (func_003edb30; static in
   the P4 unit).  RwPalQuant is an opaque 0x4010-byte working area here.
   P4 state: schedule on. */
extern u32 FUN_004d3fc0(void *);
extern void FUN_004d22f0(void *, void *, float);
extern s32 FUN_004d3300(void *, s32, void *);
extern void *FUN_004cbe00(u32, u32, u32);
extern u32 FUN_004cbf20(void *);
extern void FUN_004d3800(void *, s32, s32, u32, void *, void *);
extern void FUN_004d41e0(void *);
extern void FUN_004cbeb0_call(void *);
#pragma alias FUN_004cbeb0_call FUN_004cbeb0
extern void FUN_00521250(void *, const void *, u32);

#pragma schedule on
// FUN_004CF690
u32 FUN_004cf690(RwImage **param_1, s32 param_2)
{
  RwRGBA palette[256];
  RwImage *palImage;
  u8 palQuant[0x4010];

  if (FUN_004d3fc0(palQuant) == 0)
  {
    return 0;
  }
  FUN_004d22f0(palQuant, *param_1, 1.0f);
  FUN_004d3300(palette, (s32)(1UL << param_2), palQuant);
  palImage = (RwImage *)FUN_004cbe00((*param_1)->width, (*param_1)->height, param_2);
  if (palImage != 0)
  {
    FUN_004cbf20(palImage);
    FUN_004d3800(palImage->cpPixels, palImage->stride, palImage->depth, 0, palQuant, *param_1);
    FUN_00521250(palImage->palette, palette, sizeof(RwRGBA) * (1UL << param_2));
    FUN_004cbeb0_call(*param_1);
    *param_1 = palImage;
  }
  else
  {
    return 0;
  }
  FUN_004d41e0(palQuant);
  return 1;
}

/* P4: src/renderware/core/baraster.c RwRasterCreate (func_003ec590).
   P4 state: schedule on.
   The stdFunc slot lives in the engine globals (DAT_00960070 + 0x58); the
   source-globals spelling also keeps the retail schedule (an absolute slot
   symbol sinks the load past the raster field stores). */
#pragma schedule on
// FUN_004CE0F0
void *FUN_004ce0f0(s32 param_1, s32 param_2, s32 param_3, s32 param_4)
{
  RwRaster *raster;

  raster = (RwRaster *)(*DAT_00960188)(*(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x60), 0x30407);
  if (raster != 0)
  {
    s32 (*rasterCreateFunc)(void *, void *, s32) =
        *(s32 (**)(void *, void *, s32))((u8 *)DAT_00960070 + 0x58);

    raster->privateFlags = 0;
    raster->cFlags = 0;
    raster->width = param_1;
    raster->height = param_2;
    raster->nOffsetX = 0;
    raster->nOffsetY = 0;
    raster->depth = param_3;
    raster->parent = raster;
    raster->cpPixels = 0;
    raster->palette = 0;

    if (rasterCreateFunc(0, raster, param_4) == 0)
    {
      (*DAT_0096018c)((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc50 + 0x60), raster);
      return 0;
    }

    FUN_004c64b0((void *)D_0077E6B0, raster);
    return raster;
  }
  return 0;
}

/* P4: src/renderware/core/basync.c FrameSyncHierarchyRecurseNoLTM
   (func_003ed540; static in the P4 unit).  -inline auto expands the
   recursive call one level, as in retail.
   P4 state: schedule on. */
#pragma schedule on
// FUN_004CF0A0
void FUN_004cf0a0(RwFrame *frame)
{
  while (frame != 0)
  {
    if (frame->objectList.link.next != &frame->objectList.link)
    {
      RwLLLink *current = frame->objectList.link.next;
      RwLLLink *end = &frame->objectList.link;

      while (current != end)
      {
        RwObjectHasFrame *object = (RwObjectHasFrame *)((u8 *)current - 8);

        object->sync(object);
        current = current->next;
      }
    }
    frame->object.privateFlags = *(u8 *)((u8 *)frame + 3) & ~8;
    FUN_004cf0a0(frame->child);
    frame = frame->next;
  }
}

/* P4: src/renderware/core/basync.c FrameSyncHierarchy (func_003ed650; static in
   the P4 unit).  RwMatrixCopy is the struct copy, the link-list helpers are
   spelled out.  FrameSyncHierarchyRecurse = FUN_004cefb0, kept a real call via
   the _call alias; FrameSyncHierarchyRecurseNoLTM = FUN_004cf0a0 (its twin
   above) is inlined by the retail build, and -inline auto does the same.
   P4 state: schedule on. */
extern void FUN_004cefb0_call(RwFrame *, s32);
#pragma alias FUN_004cefb0_call FUN_004cefb0

#pragma schedule on
// FUN_004CF1B0
void FUN_004cf1b0(RwFrame *frame)
{
  s32 oldFlags = ((const RwObject *)frame)->privateFlags;

  if (oldFlags & 1)
  {
    if (oldFlags & 4)
    {
      /* Root of hierarchy has no parent matrix - different from rest */
      frame->ltm = frame->modelling;
    }

    if (frame->objectList.link.next != &frame->objectList.link)
    {
      RwLLLink *current = frame->objectList.link.next;
      RwLLLink *end = &frame->objectList.link;

      while (current != end)
      {
        RwObjectHasFrame *object = (RwObjectHasFrame *)((u8 *)current - 8);

        object->sync(object);
        current = current->next;
      }
    }

    FUN_004cefb0_call(frame->child, oldFlags & 4);
  }
  else
  {
    if (frame->objectList.link.next != &frame->objectList.link)
    {
      RwLLLink *current = frame->objectList.link.next;
      RwLLLink *end = &frame->objectList.link;

      while (current != end)
      {
        RwObjectHasFrame *object = (RwObjectHasFrame *)((u8 *)current - 8);

        object->sync(object);
        current = current->next;
      }
    }

    FUN_004cf0a0(frame->child);
  }

  ((RwObject *)frame)->privateFlags = (RwUInt8)(oldFlags & ~0xf);
}

/* P4: src/renderware/p2/p2define.c ReallocAndFixupSuperBlock (func_004118c0;
   static in the P4 unit).  RwRealloc is the memoryFuncs.rwrealloc slot
   (DAT_00960180); _PTRINC is the P4's conditional pointer fixup macro; the
   NULL path is the error[2] / FUN_004c1d10 / FUN_004c1c50 pattern used by the
   other ports (RWERROR((E_RW_NOMEM, newSize))).
   P4 state: schedule on. */
#define _PTRINC(_ptr, _type, _numbytes)                      \
    (((_type *)NULL == (_ptr))?                              \
     ((_type *)NULL):                                        \
     ((_ptr) = (_type *)(((u8 *)_ptr) + (_numbytes))) )

#pragma schedule on
// FUN_004F3260
u32 FUN_004f3260(struct RxPipeline_l *pipeline, u32 newSize)
{
  void *oldBlock, *newBlock;
  u32 i;

  oldBlock = pipeline->superBlock;
  newBlock = (*DAT_00960180)(oldBlock, newSize, 0x1040409);
  if (NULL != newBlock)
  {
    const u32 numNodes = pipeline->numNodes;
    s32 diff;

    diff = ((u8 *)newBlock) - ((u8 *)oldBlock);

    pipeline->superBlock = newBlock;
    pipeline->superBlockSize = newSize;
    pipeline->nodes = (struct RxPipelineNode_l *)pipeline->superBlock;
    _PTRINC(pipeline->embeddedPacket, void, diff);
    _PTRINC(pipeline->inputRequirements, void, diff);

    for (i = 0; i < numNodes; i++)
    {
      _PTRINC(pipeline->nodes[i].outputs, u32, diff);
      _PTRINC(pipeline->nodes[i].slotClusterRefs, void, diff);
      _PTRINC(pipeline->nodes[i].slotsContinue, u32, diff);
      _PTRINC(pipeline->nodes[i].privateData, void, diff);
      _PTRINC(pipeline->nodes[i].inputToClusterSlot, u32, diff);
      _PTRINC(pipeline->nodes[i].topSortData, struct RxPipelineNodeTopSortData_l, diff);
    }
  }
  else
  {
    u32 error[2];

    error[0] = 1;
    error[1] = FUN_004c1d10(0x80000013, newSize);
    FUN_004c1c50(error);
    return 0;
  }

  return 1;
}

/* P4: src/renderware/core/baimage.c RwImageMakeMask (func_003ea560).
   P4 state: schedule on. */
#pragma schedule on
// FUN_004CC0A0
RwImage *FUN_004cc0a0(RwImage *image)
{
  s32 i;

  switch (image->depth)
  {
    case 4:
    case 8:
    {
      s32 palSize = (1 << image->depth);
      RwRGBA *rpPal = image->palette;

      for (i = 0; i < palSize; i++)
      {
        s32 nOpacity = rpPal[i].r;

        if (rpPal[i].g > nOpacity)
        {
          nOpacity = rpPal[i].g;
        }
        if (rpPal[i].b > nOpacity)
        {
          nOpacity = rpPal[i].b;
        }

        rpPal[i].a = (u8)nOpacity;
      }
      break;
    }
    case 32:
    {
      u8 *cpSpan = image->cpPixels;
      s32 j;

      for (i = 0; i < image->height; i++)
      {
        RwRGBA *rpCur = (RwRGBA *)cpSpan;

        for (j = 0; j < image->width; j++)
        {
          s32 nOpacity = rpCur[j].r;

          if (rpCur[j].g > nOpacity)
          {
            nOpacity = rpCur[j].g;
          }
          if (rpCur[j].b > nOpacity)
          {
            nOpacity = rpCur[j].b;
          }

          rpCur[j].a = (u8)nOpacity;
        }

        cpSpan += image->stride;
      }
    }
  }

  return image;
}

/* P4: src/renderware/core/batextur.c RwTextureRead (func_003ef740).
   P4 state: schedule on.  The texture module function pointers live in the
   engine globals (DAT_00960070 + iGpffffbc60); RwTexDictionaryAddTexture is
   inlined by -inline auto. */
extern u32 uGpffffb0a0;

#pragma schedule on
// FUN_004D1260
void *FUN_004d1260(const char *name, const char *maskName)
{
  u8 *result;

  result = ((u8 *(*)(const char *)) *
            (u32 *)((u8 *)DAT_00960070 + iGpffffbc60 + 0x18))(name);
  if (result != 0)
  {
    *(u32 *)(result + 0x54) = *(u32 *)(result + 0x54) + 1;
    return result;
  }

  result = ((u8 *(*)(const char *, const char *)) *
            (u32 *)((u8 *)DAT_00960070 + iGpffffbc60 + 0x14))(name, maskName);
  if (result == 0)
  {
    if (maskName != 0)
    {
      u32 error[2];

      error[0] = 1;
      error[1] = FUN_004c1d10(0x16, name, maskName);
      FUN_004c1c50(error);
    }
    else
    {
      u32 error[2];

      error[0] = 1;
      error[1] = FUN_004c1d10(0x16, name, &uGpffffb0a0);
      FUN_004c1c50(error);
    }
    return 0;
  }

  if (*(u32 *)((u8 *)DAT_00960070 + iGpffffbc60 + 0x10) != 0)
  {
    FUN_004d1110((void *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc60 + 0x10), result);
  }

  return result;
}

/* P4: src/renderware/p2/p2define.c PipelineUnlockTopSort (func_004123c0;
   static in the P4 unit).  Error codes: entry point 0x24, fragmented 0x22,
   cyclic 0x1c.  PipelineTallyInputs (FUN_004f3880) stays a real call.
   P4 state: schedule on. */
struct RxTopSortData_l
{
  struct RxPipeline_l *pipeline;
  u32 nodesArraySlot;
};

extern u32 FUN_004f3970(void *, u32);

#pragma schedule on
// FUN_004F3D60
struct RxPipeline_l *FUN_004f3d60(struct RxPipeline_l *pipeline)
{
  struct RxTopSortData_l data;
  u32 i;

  data.pipeline = pipeline;
  data.nodesArraySlot = 0;

  FUN_004f3880(pipeline);

  if (pipeline->nodes[pipeline->entryPoint].topSortData->numIns != 0)
  {
    u32 error[2];

    error[0] = 1;
    error[1] = FUN_004c1d10(0x24);
    FUN_004c1c50(error);
    return 0;
  }

  for (i = 0; i < pipeline->numNodes; i++)
  {
    if ((i != pipeline->entryPoint) &&
        (pipeline->nodes[i].topSortData->numIns == 0))
    {
      u32 error[2];

      error[0] = 1;
      error[1] = FUN_004c1d10(0x22);
      FUN_004c1c50(error);
      return 0;
    }
  }

  FUN_004f3970(&data, pipeline->entryPoint);

  for (i = 0; i < pipeline->numNodes; i++)
  {
    if (pipeline->nodes[i].topSortData->numIns !=
        pipeline->nodes[i].topSortData->numInsVisited)
    {
      u32 error[2];

      error[0] = 1;
      error[1] = FUN_004c1d10(0x1c);
      FUN_004c1c50(error);
      return 0;
    }
  }

  pipeline->entryPoint = 0;
  return pipeline;
}

/* P4: src/renderware/core/baframe.c rwFrameCloneRecurse (func_003e8f80;
   static in the P4 unit).  The P4 rwObjectCopy macro copies the four byte
   fields and clears the parent, so the parent store appears twice (the
   second one is rwObjectSetParent).
   P4 state: schedule on. */
extern void FUN_004cb1b0(void *);
extern void FUN_004c65d0(void *, void *, void *);

#pragma schedule on
// FUN_004CAB70
void *FUN_004cab70(void *param_1, void *param_2)
{
  RwFrame *oldFrame = (RwFrame *)param_1;
  RwFrame *newRoot = (RwFrame *)param_2;
  RwFrame *newFrame;
  RwFrame *child;

  newFrame = (RwFrame *)(*DAT_00960188)(*(u32 *)((u8 *)DAT_00960070 + iGpffffbc40), 0x3000e);
  if (newFrame == 0)
  {
    return 0;
  }
  if (newRoot == 0)
  {
    newRoot = newFrame;
  }

  newFrame->object.type = oldFrame->object.type;
  newFrame->object.subType = oldFrame->object.subType;
  newFrame->object.flags = oldFrame->object.flags;
  newFrame->object.privateFlags = oldFrame->object.privateFlags;
  newFrame->object.parent = 0;

  newFrame->objectList.link.next = &newFrame->objectList.link;
  newFrame->objectList.link.prev = &newFrame->objectList.link;

  newFrame->object.parent = 0;

  newFrame->modelling = oldFrame->modelling;
  newFrame->child = 0;
  newFrame->next = 0;
  newFrame->root = newRoot;
  oldFrame->root = newFrame;

  child = oldFrame->child;
  while (child != 0)
  {
    RwFrame *newChild = (RwFrame *)FUN_004cab70(child, newRoot);

    if (newChild == 0)
    {
      FUN_004cb1b0(newFrame);
      return 0;
    }
    newChild->next = newFrame->child;
    newFrame->child = newChild;
    newChild->object.parent = newFrame;
    child = child->next;
  }

  FUN_004c64b0((void *)D_0077E670, newFrame);
  FUN_004c65d0((void *)D_0077E670, newFrame, oldFrame);
  return newFrame;
}

/* P4: src/renderware/core/baframe.c RwFrameAddChild (func_003e9830).
   rwSetHierarchyRoot (FUN_004caac0) is auto-inlined by the retail build;
   RwFrameUpdateObjects is auto-inlined there too (neither the P4 object nor
   retail emits a symbol for it), so its body lives in the static helper below
   and -inline auto inlines it at the call site just as the P4 build does.
   RwFrameRemoveChild (FUN_004cb590) stays a call.
   P4 state: schedule on. */

#pragma schedule on
static RwFrame *rwFrameUpdateObjects_l(RwFrame *frame)
{
  RwUInt32 oldFlags;

  oldFlags = frame->root->object.privateFlags;
  if (!(oldFlags & 3))
  {
    RwLinkList *dirtyList = (RwLinkList *)((u8 *)DAT_00960070 + 0xBC);

    frame->root->inDirtyListLink.next = dirtyList->link.next;
    frame->root->inDirtyListLink.prev = (RwLLLink *)dirtyList;
    dirtyList->link.next->prev = &frame->root->inDirtyListLink;
    dirtyList->link.next = &frame->root->inDirtyListLink;
  }
  ((RwObject *)frame->root)->privateFlags = (RwUInt8)(oldFlags | 3);
  ((RwObject *)frame)->privateFlags = (RwUInt8)(((const RwObject *)frame)->privateFlags | 0xc);
  return frame;
}

// FUN_004CB420
void *FUN_004cb420(RwFrame *parent, RwFrame *child)
{
  if ((RwFrame *)((const RwObject *)child)->parent)
  {
    FUN_004cb590(child);
  }

  child->next = parent->child;
  parent->child = child;
  ((RwObject *)child)->parent = (void *)parent;
  FUN_004caac0(child, parent->root);

  if ((((const RwObject *)child)->privateFlags & (RwUInt8)(3)))
  {
    child->inDirtyListLink.prev->next = child->inDirtyListLink.next;
    child->inDirtyListLink.next->prev = child->inDirtyListLink.prev;
    ((RwObject *)child)->privateFlags = (RwUInt8)(((const RwObject *)child)->privateFlags & ~3);
  }

  rwFrameUpdateObjects_l(child);
  return parent;
}

/* P4: src/renderware/core/baimage.c RwImageRead (func_003eaf60).
   rwstrrchr/rwstrcmp are the stringFuncs slots of the engine globals
   (DAT_00960070 + 0xDC / + 0xE8).  RWIMAGEGLOBAL(imageFormats) is the image
   module globals (DAT_00960070 + iGpffffbc48) offset 0x21C.  rwImageFormat and
   imageReadData live below, matching include/rw/core/baimage.h; ImageAttempRead
   and ImagePathForAllFullNames are calls into the parent unit's drafts.
   P4 state: schedule on. */
extern void FUN_004cc6d0(const RwChar *pathname, RwInt32 size, void *callBack, void *data);
extern RwImage *FUN_004cca60(RwChar *pathname, void *data);

typedef RwBool (*RwImageCallBackWrite_l)(const RwChar *, RwImage *);
typedef RwImage *(*RwImageCallBackRead_l)(const RwChar *);

typedef struct rwImageFormat_l rwImageFormat_l;
struct rwImageFormat_l
{
  RwChar lcExtension[20];
  RwChar ucExtension[20];
  RwImageCallBackRead_l readImage;
  RwImageCallBackWrite_l writeImage;
  rwImageFormat_l *nextFormat;
};

typedef struct imageReadData_l imageReadData_l;
struct imageReadData_l
{
  RwImageCallBackRead_l readImage;
  RwImage *image;
};

#pragma schedule on
// FUN_004CCAC0
void *FUN_004ccac0(const RwChar *imageName)
{
  const RwChar *lastSeparator, *testSeparator, *extender;

  lastSeparator = imageName;

  testSeparator = (*(RwChar *(**)(const RwChar *, RwInt32))((u8 *)DAT_00960070 + 0xDC))(lastSeparator, ':');
  lastSeparator = testSeparator ? testSeparator : lastSeparator;

  testSeparator = (*(RwChar *(**)(const RwChar *, RwInt32))((u8 *)DAT_00960070 + 0xDC))(lastSeparator, '/');
  lastSeparator = testSeparator ? testSeparator : lastSeparator;

  testSeparator = (*(RwChar *(**)(const RwChar *, RwInt32))((u8 *)DAT_00960070 + 0xDC))(lastSeparator, '\\');
  lastSeparator = testSeparator ? testSeparator : lastSeparator;

  extender = (*(RwChar *(**)(const RwChar *, RwInt32))((u8 *)DAT_00960070 + 0xDC))(lastSeparator, '.');
  if (extender)
  {
    rwImageFormat_l *imageFormat;

    imageFormat = (rwImageFormat_l *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 0x21C);
    while (imageFormat)
    {
      if (!(*(s32 (**)(const RwChar *, const RwChar *))((u8 *)DAT_00960070 + 0xE8))(imageFormat->lcExtension, extender) ||
          !(*(s32 (**)(const RwChar *, const RwChar *))((u8 *)DAT_00960070 + 0xE8))(imageFormat->ucExtension, extender))
      {
        if (imageFormat->readImage)
        {
          imageReadData_l imageData;

          imageData.readImage = imageFormat->readImage;
          imageData.image = (RwImage *)NULL;

          FUN_004cc6d0(imageName, 5 * sizeof(RwChar), (void *)FUN_004cca60, &imageData);

          return imageData.image;
        }

        return (RwImage *)NULL;
      }

      imageFormat = imageFormat->nextFormat;
    }

    return (RwImage *)NULL;
  }

  return (RwImage *)NULL;
}

/* P4: src/renderware/core/baresamp.c RwImageCreateResample (func_003ed2d0).
   RwImageCreate = FUN_004cbe00, RwImageAllocatePixels = FUN_004cbf20,
   RwImageFreePixels = FUN_004cc050 and RwImageDestroy = FUN_004cbeb0 (both via
   the _call aliases declared above), RwImageCopy = FUN_004cd620,
   RwImageResample = FUN_004cec10.
   P4 state: schedule on. */
extern RwImage *FUN_004cd620(RwImage *destImage, const RwImage *srcImage);
extern RwBool FUN_004cec10(RwImage *dstImage, const RwImage *srcImage);

#pragma schedule on
// FUN_004CEE30
RwImage *FUN_004cee30(const RwImage *srcImage, RwInt32 width, RwInt32 height)
{
  RwImage *dstImage = (RwImage *)FUN_004cbe00(width, height, 32);

  if (!dstImage)
  {
    return (RwImage *)NULL;
  }

  if (!FUN_004cbf20(dstImage))
  {
    FUN_004cbeb0_call(dstImage);
    return (RwImage *)NULL;
  }

  if (srcImage->depth != 32)
  {
    RwImage *ipUse = (RwImage *)FUN_004cbe00(srcImage->width, srcImage->height, 32);

    if (!ipUse)
    {
      FUN_004cc050_call(dstImage);
      FUN_004cbeb0_call(dstImage);
      return (RwImage *)NULL;
    }

    if (!FUN_004cbf20(ipUse))
    {
      FUN_004cbeb0_call(ipUse);
      FUN_004cc050_call(dstImage);
      FUN_004cbeb0_call(dstImage);
      return (RwImage *)NULL;
    }

    FUN_004cd620(ipUse, srcImage);

    if (!FUN_004cec10(dstImage, ipUse))
    {
      FUN_004cc050_call(ipUse);
      FUN_004cbeb0_call(ipUse);
      FUN_004cc050_call(dstImage);
      FUN_004cbeb0_call(dstImage);
      return (RwImage *)NULL;
    }

    FUN_004cc050_call(ipUse);
    FUN_004cbeb0_call(ipUse);
  }
  else
  {
    if (!FUN_004cec10(dstImage, srcImage))
    {
      FUN_004cc050_call(dstImage);
      FUN_004cbeb0_call(dstImage);
      return (RwImage *)NULL;
    }
  }

  return dstImage;
}

/* P4: src/renderware/core/baimage.c _rwImageClose (func_003ea130).
   RwFree is the memoryFuncs.rwfree slot (DAT_0096017c), RwFreeListFree the
   free-list free slot (DAT_0096018c), RwFreeListDestroy = FUN_004c3c30.
   RWIMAGEGLOBAL(x) is DAT_00960070 + iGpffffbc48; imageModule.numInstances is
   iGpffffbc4c.  Fields: imageFreeList +0, imagePath +4, imagePathSize +8,
   scratchMem +0x210, scratchMemSize +0x214, imageFormatFreeList +0x218,
   imageFormats +0x21C.
   P4 state: schedule on. */
extern void FUN_004c3c30(void *);
extern int iGpffffbc4c;

#pragma schedule on
// FUN_004CBC70
void *FUN_004cbc70(void *instance, RwInt32 offset, RwInt32 size)
{
  if (*(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x210))
  {
    (*DAT_0096017c)(*(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x210));
    *(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x210) = (void *)NULL;
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 0x214) = 0;
  }

  if (*(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 4))
  {
    (*DAT_0096017c)(*(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 4));
    *(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 4) = (void *)NULL;
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 8) = 0;
  }

  while (*(rwImageFormat_l **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x21C))
  {
    rwImageFormat_l *formatToDestroy =
      *(rwImageFormat_l **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x21C);

    *(rwImageFormat_l **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x21C) = formatToDestroy->nextFormat;
    (*(s32 (**)(void *, void *))((u8 *)DAT_00960070 + 0x11C))(
        *(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x218),
        (void *)formatToDestroy);
  }

  if (*(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x218))
  {
    FUN_004c3c30(*(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x218));
    *(void **)((u8 *)DAT_00960070 + iGpffffbc48 + 0x218) = (void *)NULL;
  }

  if (*(void **)((u8 *)DAT_00960070 + iGpffffbc48))
  {
    FUN_004c3c30(*(void **)((u8 *)DAT_00960070 + iGpffffbc48));
    *(void **)((u8 *)DAT_00960070 + iGpffffbc48) = (void *)NULL;
  }

  iGpffffbc4c = iGpffffbc4c - 1;
  return instance;
}

/* P4: src/renderware/core/baimage.c RwImageRegisterImageFormat (func_003eb1f0).
   String functions come from the engine globals: rwstrncpy (+0xD0) and rwstrcmp
   (+0xE8) are kept in a register (as in retail); rwstrlwr (+0xFC), rwstrupr
   (+0xF8) and RwFreeListAlloc (DAT_00960188, +0x118) load through the absolute
   slot.  memcpy = FUN_00521250; RWIMAGEGLOBAL(x) is DAT_00960070 +
   iGpffffbc48, with imageFormatFreeList at +0x218 and imageFormats at +0x21C.
   P4 state: schedule on. */
extern void (*DAT_0096016c[])(RwChar *);
extern void (*DAT_00960168[])(RwChar *);

#pragma schedule on
// FUN_004CCD50
u32 FUN_004ccd50(const RwChar *extension, RwImageCallBackRead_l imageRead,
                 RwImageCallBackWrite_l imageWrite)
{
  rwImageFormat_l *newFormat, *imageFormat;
  RwChar lcExtension[20];

  /* Need to make sure it's not already there (compare the LC version) */
  lcExtension[0] = '.';
  (*(void (**)(RwChar *, const RwChar *, RwInt32))((u8 *)DAT_00960070 + 0xD0))(&lcExtension[1],
                                                                               extension, 18);
  lcExtension[19] = 0;
  (*DAT_0096016c)(lcExtension);

  /* If we find it already there, override the methods */
  imageFormat = (rwImageFormat_l *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 0x21C);
  newFormat = (rwImageFormat_l *)NULL;
  while (imageFormat && !newFormat)
  {
    if (!(*(s32 (**)(const RwChar *, const RwChar *))((u8 *)DAT_00960070 + 0xE8))(
            imageFormat->lcExtension, lcExtension))
    {
      /* Got it, so prepare to replace operations */
      newFormat = imageFormat;
    }
    else
    {
      /* Look at the next one */
      imageFormat = imageFormat->nextFormat;
    }
  }

  /* If we didn't find one, create one and link it in */
  if (!newFormat)
  {
    /* Time to allocate the new element */
    newFormat = (rwImageFormat_l *)(*DAT_00960188)(
        *(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 0x218), 0x30406);

    if (!newFormat)
    {
      /* Allocation failure */
      return 0;
    }

    /* Put in the extension */
    /* We already got the lower case version */
    FUN_00521250(newFormat->lcExtension, lcExtension, 20);

    /* Figure out the upper case version */
    newFormat->ucExtension[0] = '.';
    (*(void (**)(RwChar *, const RwChar *, RwInt32))((u8 *)DAT_00960070 + 0xD0))(
        &newFormat->ucExtension[1], extension, 18);
    newFormat->ucExtension[19] = 0;
    (*DAT_00960168)(newFormat->ucExtension);

    /* And some default I/O functions (none) */
    newFormat->readImage = (RwImageCallBackRead_l)NULL;
    newFormat->writeImage = (RwImageCallBackWrite_l)NULL;

    /* And link it in */
    newFormat->nextFormat =
        (rwImageFormat_l *)*(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 0x21C);
    *(u32 *)((u8 *)DAT_00960070 + iGpffffbc48 + 0x21C) = (u32)newFormat;
  }

  /* And the different functions for reading/writing (if specified) */
  if (imageRead)
  {
    newFormat->readImage = imageRead;
  }
  if (imageWrite)
  {
    newFormat->writeImage = imageWrite;
  }

  return 1;
}

/* P4: src/renderware/core/batextur.c _rwTextureClose (func_003ef900).
   RWTEXTUREGLOBAL(x) is DAT_00960070 + iGpffffbc60: texDictList +0,
   textureFreeList +8, texDictFreeList +0xC, currentTexDict +0x10, scratchMem
   +0x24, scratchMemSize +0x28 (RwInt16).  dummyTexDict is the gp-relative
   puGpffffbc58; RwTexDictionaryDestroy = FUN_004d0d10 (the retail build inlines
   it, and -inline auto does the same from its twin above), RwFreeListDestroy =
   FUN_004c3c30, RwFree = DAT_0096017c, textureModule.numInstances =
   iGpffffbc64.
   P4 state: schedule on. */
typedef struct rwTexDictionary_l rwTexDictionary_l;
extern rwTexDictionary_l *puGpffffbc58;
extern int iGpffffbc64;

#pragma schedule on
