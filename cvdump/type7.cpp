
#include "cvdump.h"

BYTE RecBuf[MAXTYPE];


void DumpCom()
{
	// TODO: DumpCom

	StdOutPrintf(L"DumpCom: Not Implemented.");
}


void DumpModTypC7(size_t cbTyp)
{
	// TODO: DumpModTypC7

	StdOutPrintf(L"DumpModTypC7: Not Implemented.");
}


void DumpTyp()
{
	// TODO: DumpTyp

	StdOutPrintf(L"DumpTyp: Not Implemented.");
}


CV_typ_t DumpTypRecC7(CV_typ_t a, WORD b, BYTE* c, TPI* d, PDB* e)
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
