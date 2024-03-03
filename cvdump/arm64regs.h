
#ifndef _ARM64REGS_H_
#define _ARM64REGS_H_

const wchar_t * const rgszRegArm64[] = {
    L"None",         // 0   CV_ARM64_NOREG
    L"???",          // 1
    L"???",          // 2
    L"???",          // 3
    L"???",          // 4
    L"???",          // 5
    L"???",          // 6
    L"???",          // 7
    L"???",          // 8
    L"???",          // 9
    L"w0",           // 10  CV_ARM64_W0
    L"w1",           // 11  CV_ARM64_W1
    L"w2",           // 12  CV_ARM64_W2
    L"w3",           // 13  CV_ARM64_W3
    L"w4",           // 14  CV_ARM64_W4
    L"w5",           // 15  CV_ARM64_W5
    L"w6",           // 16  CV_ARM64_W6
    L"w7",           // 17  CV_ARM64_W7
    L"w8",           // 18  CV_ARM64_W8
    L"w9",           // 19  CV_ARM64_W9
    L"w10",          // 20  CV_ARM64_W10
    L"w11",          // 21  CV_ARM64_W11
    L"w12",          // 22  CV_ARM64_W12
    L"w13",          // 23  CV_ARM64_W13
    L"w14",          // 24  CV_ARM64_W14
    L"w15",          // 25  CV_ARM64_W15
    L"w16",          // 26  CV_ARM64_W16
    L"w17",          // 27  CV_ARM64_W17
    L"w18",          // 28  CV_ARM64_W18
    L"w19",          // 29  CV_ARM64_W19
    L"w20",          // 30  CV_ARM64_W20
    L"w21",          // 31  CV_ARM64_W21
    L"w22",          // 32  CV_ARM64_W22
    L"w23",          // 33  CV_ARM64_W23
    L"w24",          // 34  CV_ARM64_W24
    L"w25",          // 35  CV_ARM64_W25
    L"w26",          // 36  CV_ARM64_W26
    L"w27",          // 37  CV_ARM64_W27
    L"w28",          // 38  CV_ARM64_W28
    L"w29",          // 39  CV_ARM64_W29
    L"w30",          // 40  CV_ARM64_W30
    L"wzr",          // 41  CV_ARM64_WZR
    L"???",          // 42
    L"???",          // 43
    L"???",          // 44
    L"???",          // 45
    L"???",          // 46
    L"???",          // 47
    L"???",          // 48
    L"???",          // 49
    L"x0",           // 50  CV_ARM64_X0
    L"x1",           // 51  CV_ARM64_X1
    L"x2",           // 52  CV_ARM64_X2
    L"x3",           // 53  CV_ARM64_X3
    L"x4",           // 54  CV_ARM64_X4
    L"x5",           // 55  CV_ARM64_X5
    L"x6",           // 56  CV_ARM64_X6
    L"x7",           // 57  CV_ARM64_X7
    L"x8",           // 58  CV_ARM64_X8
    L"x9",           // 59  CV_ARM64_X9
    L"x10",          // 60  CV_ARM64_X10
    L"x11",          // 61  CV_ARM64_X11
    L"x12",          // 62  CV_ARM64_X12
    L"x13",          // 63  CV_ARM64_X13
    L"x14",          // 64  CV_ARM64_X14
    L"x15",          // 65  CV_ARM64_X15
    L"ip0",          // 66  CV_ARM64_IP0
    L"ip1",          // 67  CV_ARM64_IP1
    L"x18",          // 68  CV_ARM64_X18
    L"x19",          // 69  CV_ARM64_X19
    L"x20",          // 70  CV_ARM64_X20
    L"x21",          // 71  CV_ARM64_X21
    L"x22",          // 72  CV_ARM64_X22
    L"x23",          // 73  CV_ARM64_X23
    L"x24",          // 74  CV_ARM64_X24
    L"x25",          // 75  CV_ARM64_X25
    L"x26",          // 76  CV_ARM64_X26
    L"x27",          // 77  CV_ARM64_X27
    L"x28",          // 78  CV_ARM64_X28
    L"fp",           // 79  CV_ARM64_FP
    L"lr",           // 80  CV_ARM64_LR
    L"sp",           // 81  CV_ARM64_SP
    L"zr",           // 82  CV_ARM64_ZR
    L"???",          // 83
    L"???",          // 84
    L"???",          // 85
    L"???",          // 86
    L"???",          // 87
    L"???",          // 88
    L"???",          // 89
    L"nzcv",         // 90  CV_ARM64_NZCV
    L"???",          // 91
    L"???",          // 92
    L"???",          // 93
    L"???",          // 94
    L"???",          // 95
    L"???",          // 96
    L"???",          // 97
    L"???",          // 98
    L"???",          // 99
    L"s0",           // 100 CV_ARM64_S0
    L"s1",           // 101 CV_ARM64_S1
    L"s2",           // 102 CV_ARM64_S2
    L"s3",           // 103 CV_ARM64_S3
    L"s4",           // 104 CV_ARM64_S4
    L"s5",           // 105 CV_ARM64_S5
    L"s6",           // 106 CV_ARM64_S6
    L"s7",           // 107 CV_ARM64_S7
    L"s8",           // 108 CV_ARM64_S8
    L"s9",           // 109 CV_ARM64_S9
    L"s10",          // 110 CV_ARM64_S10
    L"s11",          // 111 CV_ARM64_S11
    L"s12",          // 112 CV_ARM64_S12
    L"s13",          // 113 CV_ARM64_S13
    L"s14",          // 114 CV_ARM64_S14
    L"s15",          // 115 CV_ARM64_S15
    L"s16",          // 116 CV_ARM64_S16
    L"s17",          // 117 CV_ARM64_S17
    L"s18",          // 118 CV_ARM64_S18
    L"s19",          // 119 CV_ARM64_S19
    L"s20",          // 120 CV_ARM64_S20
    L"s21",          // 121 CV_ARM64_S21
    L"s22",          // 122 CV_ARM64_S22
    L"s23",          // 123 CV_ARM64_S23
    L"s24",          // 124 CV_ARM64_S24
    L"s25",          // 125 CV_ARM64_S25
    L"s26",          // 126 CV_ARM64_S26
    L"s27",          // 127 CV_ARM64_S27
    L"s28",          // 128 CV_ARM64_S28
    L"s29",          // 129 CV_ARM64_S29
    L"s30",          // 130 CV_ARM64_S30
    L"s31",          // 131 CV_ARM64_S31
    L"???",          // 132
    L"???",          // 133
    L"???",          // 134
    L"???",          // 135
    L"???",          // 136
    L"???",          // 137
    L"???",          // 138
    L"???",          // 139
    L"d0",           // 140 CV_ARM64_D0
    L"d1",           // 141 CV_ARM64_D1
    L"d2",           // 142 CV_ARM64_D2
    L"d3",           // 143 CV_ARM64_D3
    L"d4",           // 144 CV_ARM64_D4
    L"d5",           // 145 CV_ARM64_D5
    L"d6",           // 146 CV_ARM64_D6
    L"d7",           // 147 CV_ARM64_D7
    L"d8",           // 148 CV_ARM64_D8
    L"d9",           // 149 CV_ARM64_D9
    L"d10",          // 150 CV_ARM64_D10
    L"d11",          // 151 CV_ARM64_D11
    L"d12",          // 152 CV_ARM64_D12
    L"d13",          // 153 CV_ARM64_D13
    L"d14",          // 154 CV_ARM64_D14
    L"d15",          // 155 CV_ARM64_D15
    L"d16",          // 156 CV_ARM64_D16
    L"d17",          // 157 CV_ARM64_D17
    L"d18",          // 158 CV_ARM64_D18
    L"d19",          // 159 CV_ARM64_D19
    L"d20",          // 160 CV_ARM64_D20
    L"d21",          // 161 CV_ARM64_D21
    L"d22",          // 162 CV_ARM64_D22
    L"d23",          // 163 CV_ARM64_D23
    L"d24",          // 164 CV_ARM64_D24
    L"d25",          // 165 CV_ARM64_D25
    L"d26",          // 166 CV_ARM64_D26
    L"d27",          // 167 CV_ARM64_D27
    L"d28",          // 168 CV_ARM64_D28
    L"d29",          // 169 CV_ARM64_D29
    L"d30",          // 170 CV_ARM64_D30
    L"d31",          // 171 CV_ARM64_D31
    L"???",          // 172
    L"???",          // 173
    L"???",          // 174
    L"???",          // 175
    L"???",          // 176
    L"???",          // 177
    L"???",          // 178
    L"???",          // 179
    L"q0",           // 180 CV_ARM64_Q0
    L"q1",           // 181 CV_ARM64_Q1
    L"q2",           // 182 CV_ARM64_Q2
    L"q3",           // 183 CV_ARM64_Q3
    L"q4",           // 184 CV_ARM64_Q4
    L"q5",           // 185 CV_ARM64_Q5
    L"q6",           // 186 CV_ARM64_Q6
    L"q7",           // 187 CV_ARM64_Q7
    L"q8",           // 188 CV_ARM64_Q8
    L"q9",           // 189 CV_ARM64_Q9
    L"q10",          // 190 CV_ARM64_Q10
    L"q11",          // 191 CV_ARM64_Q11
    L"q12",          // 192 CV_ARM64_Q12
    L"q13",          // 193 CV_ARM64_Q13
    L"q14",          // 194 CV_ARM64_Q14
    L"q15",          // 195 CV_ARM64_Q15
    L"q16",          // 196 CV_ARM64_Q16
    L"q17",          // 197 CV_ARM64_Q17
    L"q18",          // 198 CV_ARM64_Q18
    L"q19",          // 199 CV_ARM64_Q19
    L"q20",          // 200 CV_ARM64_Q20
    L"q21",          // 201 CV_ARM64_Q21
    L"q22",          // 202 CV_ARM64_Q22
    L"q23",          // 203 CV_ARM64_Q23
    L"q24",          // 204 CV_ARM64_Q24
    L"q25",          // 205 CV_ARM64_Q25
    L"q26",          // 206 CV_ARM64_Q26
    L"q27",          // 207 CV_ARM64_Q27
    L"q28",          // 208 CV_ARM64_Q28
    L"q29",          // 209 CV_ARM64_Q29
    L"q30",          // 210 CV_ARM64_Q30
    L"q31",          // 211 CV_ARM64_Q31
    L"???",          // 212
    L"???",          // 213
    L"???",          // 214
    L"???",          // 215
    L"???",          // 216
    L"???",          // 217
    L"???",          // 218
    L"???",          // 219
    L"fpsr",         // 220 CV_ARM64_FPSR
};

#endif // _ARM64REGS_H_
