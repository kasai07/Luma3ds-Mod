#pragma once

#include <3ds/types.h>
#include "exheader.h"
#include "ifile.h"

#define MAKE_BRANCH(src,dst)      (0xEA000000 | ((u32)((((u8 *)(dst) - (u8 *)(src)) >> 2) - 2) & 0xFFFFFF))
#define MAKE_BRANCH_LINK(src,dst) (0xEB000000 | ((u32)((((u8 *)(dst) - (u8 *)(src)) >> 2) - 2) & 0xFFFFFF))

#define CONFIG(a)        (((config >> (a)) & 1) != 0)
#define MULTICONFIG(a)   ((multiConfig >> (2 * (a))) & 3)
#define BOOTCONFIG(a, b) ((bootConfig >> (a)) & (b))

#define BOOTCFG_NAND         BOOTCONFIG(0, 7)
#define BOOTCFG_FIRM         BOOTCONFIG(3, 7)
#define BOOTCFG_NOFORCEFLAG  BOOTCONFIG(6, 1)
#define BOOTCFG_NTRCARDBOOT  BOOTCONFIG(7, 1)

enum multiOptions
{
    DEFAULTEMU = 0,
    BRIGHTNESS,
    SPLASH,
    PIN,
    NEWCPU
};

enum singleOptions
{
    AUTOBOOTEMU = 0,
    USEEMUFIRM,
    LOADEXTFIRMSANDMODULES,
    PATCHGAMES,
    PATCHVERSTRING,
    SHOWGBABOOT,
    PATCHACCESS,
    PATCHUNITINFO,
    DISABLEARM11EXCHANDLERS
};

extern u32 config, multiConfig, bootConfig;
extern bool isN3DS, isSafeMode, isSdMode;

void patchCode(u64 progId, u16 progVer, u8 *code, u32 size, u32 textSize, u32 roSize, u32 dataSize, u32 roAddress, u32 dataAddress);
Result fileOpen(IFile *file, FS_ArchiveID archiveId, const char *path, int flags);
bool loadTitleCodeSection(u64 progId, u8 *code, u32 size);
bool loadTitleExheader(u64 progId, exheader_header *exheader);
