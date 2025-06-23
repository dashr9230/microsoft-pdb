
#include "prefast.h"

#include "windows.h"

#include "utf8.h"

#ifdef __cplusplus
extern "C" {
#endif
static int aiByteCountForLeadNibble[16] =
{
    1,  // 0000
    1,  // 0001
    1,  // 0010
    1,  // 0011
    1,  // 0100
    1,  // 0101
    1,  // 0110
    1,  // 0111
    1,  // 1000
    1,  // 1001
    1,  // 1010
    1,  // 1011
    2,  // 1100
    2,  // 1101
    3,  // 1110
    4   // 1111
};
inline BOOL IsValidWideChar(short w)
{
    return w <= 0xffef;
}
inline short __U(short w)
{
	return IsValidWideChar(w)?w:L'?';
}

size_t UTF8ToUnicode(LPCSTR lpSrcStr, LPWSTR lpDestStr, size_t cchDest)
{
	return UTF8ToUnicodeCch(lpSrcStr, strlen(lpSrcStr) + 1, lpDestStr, cchDest);
}

size_t UTF8ToUnicodeCch(LPCSTR lpSrcStr, size_t cchSrc, LPWSTR lpDestStr, size_t cchDest)
{
    int nTB = 0;                   // # trail bytes to follow
    size_t cchWC = 0;              // # of Unicode code points generated
    LPCSTR pUTF8 = lpSrcStr;
    DWORD dwSurrogateChar = 0;         // Full surrogate char
    BOOL bSurrogatePair = FALSE;   // Indicate we'r collecting a surrogate pair
    char UTF8;

    while ((cchSrc--) && ((cchDest == 0) || (cchWC < cchDest)))
    {
        //
        //  See if there are any trail bytes.
        //
        if (BIT7(*pUTF8) == 0)
        {
            //
            //  Found ASCII.
            //
            if (cchDest)
            {
                lpDestStr[cchWC] = (WCHAR)*pUTF8;
            }
            bSurrogatePair = FALSE;
            cchWC++;
        }
        else if (BIT6(*pUTF8) == 0)
        {
            //
            //  Found a trail byte.
            //  Note : Ignore the trail byte if there was no lead byte.
            //
            if (nTB != 0)
            {
                //
                //  Decrement the trail byte counter.
                //
                nTB--;

                if (bSurrogatePair)
                {
                    dwSurrogateChar <<= 6;
                    dwSurrogateChar |= LOWER_6_BIT(*pUTF8);

                    if (nTB == 0)
                    {
                        if (cchDest)
                        {
                            if ((cchWC + 1) < cchDest)
                            {
                                lpDestStr[cchWC] = (WCHAR)
                                    (((dwSurrogateChar - 0x10000) >> 10) + HIGH_SURROGATE_START);

                                lpDestStr[cchWC + 1] = (WCHAR)
                                    ((dwSurrogateChar - 0x10000) % 0x400 + LOW_SURROGATE_START);
                            }
                        }

                        cchWC += 2;
                        bSurrogatePair = FALSE;
                    }
                }
                else
                {
                    //
                    //  Make room for the trail byte and add the trail byte
                    //  value.
                    //
                    if (cchDest)
                    {
                        lpDestStr[cchWC] <<= 6;
                        lpDestStr[cchWC] |= LOWER_6_BIT(*pUTF8);
                    }

                    if (nTB == 0)
                    {
                        //
                        //  End of sequence.  Advance the output counter.
                        //
                        cchWC++;
                    }
                }
            }
            else
            {
                // error - not expecting a trail byte
                bSurrogatePair = FALSE;
            }
        }
        else
        {
            //
            //  Found a lead byte.
            //
            if (nTB > 0)
            {
                //
                //  Error - previous sequence not finished.
                //
                nTB = 0;
                bSurrogatePair = FALSE;
                cchWC++;
            }
            else
            {
                //
                //  Calculate the number of bytes to follow.
                //  Look for the first 0 from left to right.
                //
                UTF8 = *pUTF8;
                while (BIT7(UTF8) != 0)
                {
                    UTF8 <<= 1;
                    nTB++;
                }

                //
                // If this is a surrogate unicode pair
                //
                if (nTB == 4)
                {
                    dwSurrogateChar = UTF8 >> nTB;
                    bSurrogatePair = TRUE;
                }

                //
                //  Store the value from the first byte and decrement
                //  the number of bytes to follow.
                //
                if (cchDest)
                {
                    lpDestStr[cchWC] = UTF8 >> nTB;
                }
                nTB--;
            }
        }

        pUTF8++;
    }

    //
    //  Make sure the destination buffer was large enough.
    //
    if (cchDest && cchSrc != (size_t)-1)
    {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return 0;
    }

    //
    //  Return the number of Unicode characters written.
    //
    return cchWC;
}

size_t UnicodeToUTF8(LPCWSTR lpSrcStr, LPSTR lpDestStr, size_t cchDest)
{
	__debugbreak();
	return UnicodeToUTF8Cch(lpSrcStr, wcslen(lpSrcStr) + 1, lpDestStr, cchDest);
}
size_t UnicodeToUTF8Cch(LPCWSTR lpSrcStr, size_t cchSrc, LPSTR lpDestStr, size_t cchDest)
{
	__debugbreak();
	return 0;
}
size_t UnicodeLengthOfUTF8(PCSTR pUTF8)
{
	__debugbreak();
	return UnicodeLengthOfUTF8Cb(pUTF8, strlen(pUTF8) + 1);
}

size_t UnicodeLengthOfUTF8Cb (PCSTR pUTF8, size_t cbUTF)
{
	__debugbreak();
	return 0;
}

size_t UTF8LengthOfUnicode(PCWSTR pUni)
{
	__debugbreak();
	return UTF8LengthOfUnicodeCch(pUni, wcslen(pUni) + 1);
}

size_t UTF8LengthOfUnicodeCch (PCWSTR pUni, size_t cchUni)
{
	__debugbreak();
	return 0;
}

#ifdef __cplusplus
}
#endif
