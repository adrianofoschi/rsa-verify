#include "../../rsa.h"

static const struct rsa_public_key public_key = {
    .size   = 64,
    .n0inv  = 0x8ae37005,
    .n = {
        0xd8e02333,         0x027f6ef2,         0x5baf5a81,         0xda65a8ac,
        0x3e699298,         0x3850e5a2,         0xc5ffd6d7,         0xec94c3c4,
        0xa1718723,         0xd1f77269,         0xbd62bc6d,         0x37a82a04,
        0x877ee1de,         0x34c75bf1,         0xf5adcb65,         0xce9a3c5a,
        0x15bcabe1,         0x2ea3bc48,         0xb8a2145f,         0x8a89fbb8,
        0x5be454f3,         0x92fc6aeb,         0x7220e810,         0x3299f1eb,
        0x63221d74,         0x25831811,         0x47d50bab,         0x71b98094,
        0x150c8478,         0x6d734bae,         0x8fbd3489,         0x11bb0944,
        0xa71d0856,         0xb4f24895,         0x0645013d,         0xada2f43d,
        0xfa1d8a33,         0xe3b2a0d5,         0xc0ec2c93,         0xe70c3d79,
        0xa2af3116,         0xe17451ed,         0x98ae29c6,         0xb659cf28,
        0xe463c8a4,         0x116d7014,         0xc65fd44d,         0xf3fa045e,
        0x4cd2b3ef,         0xe8839d2d,         0x9f3a4fbe,         0xd65e0d3f,
        0xf926a401,         0x83e1eb18,         0xc9b219ca,         0x4cde4117,
        0x03c55a86,         0xe661f5f3,         0xe35e6ec2,         0xfa1fc534,
        0x92e1452f,         0xd5465206,         0xe1910df7,         0xfaa6cca0
    },
    .rr = {
        0x6b40522a,         0x07e3e3bd,         0x8bcea806,         0xf866c607,
        0x232f8373,         0x8317657b,         0xc6d2a297,         0xd4339f3e,
        0x7a889859,         0x3709f19b,         0x7e3531ec,         0x8f383f26,
        0x5d29815e,         0x37fc00c2,         0x1905bfeb,         0x44199ec4,
        0x7ba5c537,         0x93de1b81,         0x680890ff,         0xbdb6cae5,
        0xd99ee5a2,         0x22e99c2c,         0x3f48c0a7,         0x8fce129e,
        0xc5d2556c,         0xb1636c71,         0x50eecb91,         0xda615920,
        0xa429abc3,         0x030fdc66,         0x7b152c3d,         0x16158f6c,
        0x26747050,         0xb00d1af6,         0x30a342f9,         0x9ce384d9,
        0xe84889a7,         0x32d6d510,         0x2978acca,         0x13311410,
        0xcce08242,         0x589d0b36,         0xa236bb43,         0x6b8876bd,
        0xf3bfe517,         0x0a44e102,         0xb0b52bd1,         0x4ad3efc5,
        0x1ab3b3c1,         0x8c48ee06,         0xfafe3420,         0x8956186b,
        0x5d08dd90,         0x9a23b2e1,         0x229f0606,         0x4f14aedd,
        0x9a8e6417,         0x1ae51b0d,         0xb7fd301e,         0x452f1a7c,
        0x43e533b0,         0xf5628a9f,         0x75a920e0,         0x668a214c
    }
};