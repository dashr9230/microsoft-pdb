/***********************************************************************
* Microsoft (R) Debugging Information Dumper
*
* Copyright (c) Microsoft Corporation.  All rights reserved.
*
* File Comments:
*
*
***********************************************************************/

#include "cvdump.h"

#ifndef UNALIGNED
# if defined(_M_MRX000) || defined(_M_ALPHA)
#  define UNALIGNED __unaligned
# else
#  define UNALIGNED
# endif
#endif


BYTE RecBuf[MAXTYPE];

void DumpCom()
{
    long            cnt;
    long *          pTypeTbl;       // Array of offsets int types section
    CV_typ_t        usIndex = CV_FIRST_NONPRIM;
    size_t          cbEntry;        // Size of the type - length field
    unsigned        base = 0;
    unsigned        index;
    unsigned        maxindex = 0;
    unsigned        i;
    OMFTypeFlags    flags;
    size_t          seekcount = 0;
    DWORD           lfoTypeBase = GlobalTypes.lfo;
    WORD            cbMaxType = 0;

    // Read compacted types table (array of offsets from Compacted.lfo)

    _lseek(exefile, lfoBase + GlobalTypes.lfo, SEEK_SET);
    if (Sig != SIG07) {
        // the file was not packed by QCWIN 1.0 so the flag word is present

        seekcount = sizeof(OMFTypeFlags);
        _read(exefile, &flags, sizeof(OMFTypeFlags));
    }
    _read(exefile, &cnt, sizeof(long));

    if ((pTypeTbl = (long *)malloc(INDEX_PER_READ * sizeof(DWORD))) == NULL) {
        Fatal(L"Out of memory");
    }

    if (Sig == SIG09 || Sig == SIG11) {
        lfoTypeBase += seekcount + sizeof(DWORD) * (cnt + 4);
    }
    StdOutPrintf(L"\n\n*** GLOBAL TYPES section (%d types)\n", cnt);

    // Loop through the types dumping each one

    for (index = 0; index < (unsigned)cnt; index++) {
        if (index >= maxindex) {
            _lseek(exefile, lfoBase + GlobalTypes.lfo +
                (long)(maxindex + 4) * sizeof(DWORD) + seekcount, SEEK_SET);
            i = min(INDEX_PER_READ, cnt - maxindex);
            _read(exefile, pTypeTbl, i * sizeof(long));
            base = maxindex;
            maxindex += i;
        }
        _lseek(exefile, lfoBase + lfoTypeBase + pTypeTbl[index - base], SEEK_SET);
        if (_read(exefile, &RecBuf, LNGTHSZ) != LNGTHSZ) {
            Fatal(L"Types subsection wrong length");
        }
        cbEntry = *((UNALIGNED WORD *)(RecBuf));
        if (cbEntry >= MAXTYPE - LNGTHSZ) {
            Fatal(L"Type string too long");
        }
        if (_read(exefile, RecBuf + LNGTHSZ, cbEntry) != cbEntry) {
            Fatal(L"Types subsection wrong length");
        }

        if (fRaw) {
            int i;
            for (i = 0; i<cbEntry + 2; i += 2) {
                StdOutPrintf(L"  %02x  %02x", RecBuf[i], RecBuf[i+1]);
            }
            StdOutPutc(L'\n');
        }

        cbMaxType = max(cbMaxType, cbEntry + LNGTHSZ);

        usIndex = DumpTypRecC7(usIndex, cbEntry, RecBuf + LNGTHSZ, NULL, NULL);
    }

    StdOutPrintf(L"Max Type Size = %d", cbMaxType);

    free(pTypeTbl);
}


void DumpModTypC7(size_t cbTyp)
{
    size_t cbEntry;
    CV_typ_t usIndex = CV_FIRST_NONPRIM;

    while(cbTyp > 0) {
        if (_read(exefile, &RecBuf, LNGTHSZ) != LNGTHSZ) {
            Fatal(L"Types subsection wrong length");
        }
        cbEntry = *((UNALIGNED WORD *)(RecBuf));
        if (cbEntry >= MAXTYPE - LNGTHSZ) {
            Fatal(L"Type string too long");
        }
        if ((size_t)_read(exefile, RecBuf + LNGTHSZ, cbEntry) != cbEntry) {
            Fatal(L"Types subsection wrong length");
        }

        if (fRaw) {
            int i;
            for (i=0; i < cbEntry+2; i+=2) {
                StdOutPrintf(L"  %02x  %02x", RecBuf[i], RecBuf[i+1]);
            }
            StdOutPutc(L'\n');
        }

        usIndex = DumpTypRecC7(usIndex, cbEntry, RecBuf + LNGTHSZ, NULL, NULL);
        cbTyp -= cbEntry + LNGTHSZ;
    }
}


void DumpTyp()
{
    PMOD    pMod;
    DWORD   ulSignature;
    bool    fNeedsTitle = true;
    char    name[256];

    for (pMod = ModList; pMod != NULL; pMod = pMod->next) {
        if (((cbRec = pMod->TypeSize) != 0) &&
            ((iModToList == 0) || ((WORD) iModToList == pMod->iMod))) {
            if (fNeedsTitle) {
                fNeedsTitle = false;
                StdOutPuts(L"\n\n*** TYPES section\n");
            }
            _lseek(exefile, lfoBase + pMod->TypesAddr, SEEK_SET);
            strcpy_s(name, pMod->ModName);
            StdOutPrintf(L"%S\n", name);
            cbRec = 4;
            if (_read(exefile, &ulSignature, sizeof(DWORD)) != sizeof(DWORD)) {
                Fatal(L"Can't Read Types subsection");
            }
            switch (ulSignature) {
                case CV_SIGNATURE_C7:
                case CV_SIGNATURE_C11:
                case CV_SIGNATURE_C13:
                    // Types are in C7 format
                    DumpModTypC7(pMod->TypeSize - sizeof(DWORD));
                    break;

                default:
                    // Types are in C6 format
                    // Re-seek because first four bytes are not signature
                    _lseek(exefile, lfoBase + pMod->TypesAddr, SEEK_SET);
                    DumpModTypC6(pMod->TypeSize);
                    break;
            }
        }
    }
}


// DumpHex ()
//      Prints bytes from buffer in hex format.

void DumpHex(BYTE* pBytes, USHORT usCount)
{
    int num_on_line = 0;

    StdOutPuts(L"\t");

    while (usCount--)
    {
        StdOutPrintf(L" 0x%02x", *pBytes++);

        if (!(++num_on_line & 8))
        {
            if (usCount)
            {
                StdOutPuts(L"\n\t");
            }
        }
    }
}


CV_typ_t DumpTypRecC7(CV_typ_t typ, WORD cbLen, BYTE *pRec, TPI *ptpi, PDB *ppdb)
{
    // TODO: DumpTypRecC7

    StdOutPuts(L"DumpTypRecC7: Not implemented.");

    return 0;
}

const wchar_t * const C7CallTyps[] = {
    L"C Near",                      // CV_CALL_NEAR_C
    L"C Far",                       // CV_CALL_FAR_C
    L"Pascal Near",                 // CV_CALL_NEAR_PASCAL
    L"Pascal Far",                  // CV_CALL_FAR_PASCAL
    L"Fast Near",                   // CV_CALL_NEAR_FAST
    L"Fast Far",                    // CV_CALL_FAR_FAST
    L"???",                         // CV_CALL_SKIPPED
    L"STD Near",                    // CV_CALL_NEAR_STD
    L"STD Far",                     // CV_CALL_FAR_STD
    L"SYS Near",                    // CV_CALL_NEAR_SYS
    L"SYS Far",                     // CV_CALL_FAR_SYS
    L"ThisCall",                    // CV_CALL_THISCALL
    L"MIPS CALL",                   // CV_CALL_MIPSCALL
    L"Generic",                     // CV_CALL_GENERIC
    L"Alpha Call",                  // CV_CALL_ALPHACALL
    L"PPC Call",                    // CV_CALL_PPCCALL
    L"SH Call",                     // CV_CALL_SHCALL
    L"ARM Call",                    // CV_CALL_ARMCALL
    L"AM33 Call",                   // CV_CALL_AM33CALL
    L"TriCore Call",                // CV_CALL_TRICALL
    L"SH5 Call",                    // CV_CALL_SH5CALL
    L"M32R Call",                   // CV_CALL_M32RCALL
    L"CLR Call",                    // CV_CALL_CLRCALL
    L"No callconv; always Inlined", // CV_CALL_INLINE
    L"Vector Near",                 // CV_CALL_NEAR_VECTOR
};

const wchar_t *SzNameC7CallType(CV_typ_t calltype)
{
    if (calltype < _countof(C7CallTyps)) {
        return (C7CallTyps[calltype]);
    }
    else {
        return(L"???");
    }
}

const wchar_t *SzNameC7FuncAttr(CV_funcattr_t attr)
{
    if (attr.cxxreturnudt) {
        return(L"return UDT (C++ style)");
    }

    if (attr.ctor) {
        return(L"instance constructor");
    }

    if (attr.ctorvbase) {
        return(L"instance constructor of a class with virtual base");
    }

    if (attr.unused != 0) {
        return(L"****Warning**** unused field non-zero!");
    } else {
        return(L"none");
    }
}

// Print the properties info

void PrintProp(CV_prop_t prop)
{
    int i;

    i = 0;
    if (prop.packed) {
        StdOutPuts(L"PACKED, ");
        i++;
    }
    if (prop.ctor) {
        StdOutPuts(L"CONSTRUCTOR, ");
        i++;
    }
    if (prop.ovlops) {
        StdOutPuts(L"OVERLOAD, ");
        i++;
    }
    if (prop.isnested) {
        StdOutPuts(L"NESTED, ");
        i++;
    }
    if (prop.scoped) {
        if (i == 4) {
            StdOutPuts(L"\n\t\t");
            i = 0;
        }
        StdOutPuts(L"LOCAL, ");
        i++;
    }
    if (prop.cnested) {
        if (i == 4) {
            StdOutPuts(L"\n\t\t");
            i = 0;
        }
        StdOutPuts(L"CONTAINS NESTED, ");
        i++;
    }
    if (prop.opassign) {
        if (i == 4) {
            StdOutPuts(L"\n\t\t");
            i = 0;
        }
        StdOutPuts(L"OVERLOADED ASSIGNMENT, ");
        i++;
    }
    if (prop.opcast) {
        if (i == 4) {
            StdOutPuts(L"\n\t\t");
            i = 0;
        }
        StdOutPuts(L"CASTING, ");
        i++;
    }
    if (prop.fwdref) {
        if (i == 4) {
            StdOutPuts(L"\n\t\t");
            i = 0;
        }
        StdOutPuts(L"FORWARD REF, ");
        i++;
    }
    if (prop.sealed) {
        if (i == 4) {
            StdOutPuts(L"\n\t\t");
            i = 0;
        }
        StdOutPuts(L"SEALED, ");
        i++;
    }
    if (prop.intrinsic) {
        if (i == 4) {
            StdOutPuts(L"\n\t\t");
            i = 0;
        }
        StdOutPuts(L"INTRINSIC TYPE, ");
        i++;
    }
    if (prop.hfa) {
        if (i == 4) {
            StdOutPuts(L"\n\t\t");
            i = 0;
        }
        switch (prop.hfa) {
        case CV_HFA_float:
            StdOutPuts(L"HFA float, ");
            break;
        case CV_HFA_double:
            StdOutPuts(L"HFA double, ");
            break;
        case CV_HFA_other:
            StdOutPuts(L"HFA other, ");
            break;
        default:
            if (prop.hfa != CV_HFA_none) {
                StdOutPuts(L"****Warning**** HFA field contains invalid value!");
            }
            break;
        }
        i++;
    }
    if (prop.mocom) {
        if (i == 4) {
            StdOutPuts(L"\n\t\t");
            i = 0;
        }
        switch (prop.mocom) {
        case CV_MOCOM_UDT_ref:
            StdOutPuts(L"REF");
            break;
        case CV_MOCOM_UDT_value:
            StdOutPuts(L"VALUE");
            break;
        case CV_MOCOM_UDT_interface:
            StdOutPuts(L"INTERFACE");
            break;
        }
    }
}
