#include "../rsa.h"

static const uint8_t rsa_public_key_bytes[] = {
    0x40, 0x00, 0x00, 0x00, 0x93, 0xc6, 0x50, 0x2e, 0x65, 0xb8, 0xf8, 0x9f, 0x0c, 0xdd, 0xdd, 0xa5,
    0x5c, 0x7c, 0x40, 0xe7, 0x9e, 0x53, 0x8a, 0x17, 0xf7, 0x37, 0x88, 0x6e, 0xc0, 0xbc, 0x26, 0x8c,
    0xd7, 0x22, 0xe6, 0xac, 0x3f, 0x78, 0x83, 0xb3, 0xcc, 0xa2, 0xf4, 0x73, 0xf4, 0x68, 0xd5, 0x1d,
    0x6e, 0x12, 0xcb, 0x58, 0x92, 0xf6, 0x82, 0xd7, 0xf1, 0xa8, 0x41, 0x33, 0x2f, 0x4a, 0x25, 0x1a,
    0x0a, 0x7c, 0xbb, 0xda, 0x43, 0x3c, 0x1c, 0x58, 0x7a, 0xa6, 0xa5, 0x58, 0xc4, 0xda, 0x75, 0xb3,
    0x9c, 0x5e, 0xc5, 0xb6, 0x4f, 0x93, 0xb9, 0x30, 0xa2, 0xdc, 0x54, 0xd5, 0x6f, 0x1c, 0xa5, 0x8d,
    0xa9, 0x7a, 0x32, 0x6e, 0xe6, 0x07, 0x14, 0xb0, 0xc2, 0x61, 0x07, 0xac, 0x4d, 0x70, 0xd3, 0x62,
    0xbf, 0x93, 0x50, 0xf4, 0x98, 0x39, 0x35, 0xb3, 0x2e, 0x7d, 0x1e, 0x27, 0x15, 0xcf, 0xb5, 0xec,
    0x68, 0x4c, 0xf9, 0x94, 0xce, 0x95, 0xd6, 0xcc, 0x3e, 0x6c, 0xd4, 0xdb, 0x5e, 0x69, 0x09, 0x9f,
    0xc9, 0x1c, 0xf5, 0x47, 0x69, 0x07, 0x4c, 0x17, 0x95, 0xa8, 0xa7, 0x54, 0xd3, 0xcb, 0x88, 0x6a,
    0x13, 0xce, 0xd1, 0x25, 0x5d, 0x23, 0x23, 0x4e, 0x0b, 0xd7, 0xfb, 0xe9, 0xd7, 0x9d, 0xc5, 0xb1,
    0xa2, 0x4d, 0x10, 0x98, 0xbb, 0xf1, 0x35, 0x27, 0x40, 0xd1, 0x02, 0xd3, 0xac, 0x8d, 0xdb, 0x02,
    0x51, 0xd5, 0x30, 0xb5, 0xa1, 0x94, 0xa3, 0x99, 0x60, 0x55, 0x0a, 0x4a, 0xfb, 0xa0, 0xd6, 0x94,
    0xc8, 0x83, 0x90, 0xb1, 0x87, 0x7f, 0xb2, 0x6a, 0xe5, 0x5c, 0xab, 0x66, 0xdb, 0x8b, 0x68, 0xc8,
    0x8e, 0x7d, 0x38, 0x47, 0xe2, 0xd1, 0x34, 0xca, 0x9d, 0x28, 0x8c, 0x35, 0xd4, 0x1b, 0x47, 0xb1,
    0x16, 0xf8, 0xc2, 0xf2, 0x0e, 0x8d, 0x89, 0xb1, 0xa4, 0xeb, 0x59, 0xab, 0x96, 0xc7, 0x71, 0xad,
    0x2b, 0x8c, 0x28, 0x17, 0x35, 0x3b, 0xa7, 0xb9, 0x5b, 0x7f, 0x7e, 0x0c, 0x61, 0xf6, 0xde, 0x7b,
    0x72, 0xcf, 0x52, 0xb8, 0x16, 0x29, 0x2f, 0xd2, 0x3d, 0xbf, 0x02, 0x7f, 0x80, 0xfb, 0xc6, 0x69,
    0x91, 0xbd, 0x61, 0xb7, 0x8f, 0x4a, 0x1c, 0x35, 0xac, 0x6e, 0x16, 0xf1, 0xd4, 0xe5, 0x3b, 0x71,
    0x3d, 0x93, 0xe4, 0xdc, 0x39, 0x00, 0x2c, 0x2c, 0xca, 0x05, 0x57, 0xdd, 0xcf, 0x43, 0x56, 0xce,
    0x80, 0xe7, 0x51, 0x98, 0x00, 0x8d, 0xe2, 0x99, 0x19, 0xd2, 0x5f, 0xf8, 0x3d, 0x7c, 0xb4, 0x65,
    0xef, 0x1d, 0x24, 0x85, 0xfe, 0xc9, 0x1e, 0xa3, 0x47, 0x3b, 0xea, 0x28, 0xfd, 0x7a, 0x9b, 0x82,
    0x05, 0x42, 0xc0, 0x1b, 0x81, 0x95, 0xbe, 0xa3, 0x94, 0xbb, 0xec, 0xd6, 0xc1, 0xbb, 0x08, 0x3c,
    0x6a, 0xaf, 0x94, 0x24, 0x76, 0x22, 0x75, 0x16, 0x90, 0xe7, 0x45, 0x79, 0x7b, 0x84, 0xa2, 0xe6,
    0x5c, 0xb1, 0x47, 0xe3, 0xc5, 0x2e, 0xca, 0x55, 0xad, 0xf5, 0xb1, 0xa1, 0x9f, 0xaf, 0x62, 0x26,
    0x48, 0x4b, 0x38, 0xb8, 0x48, 0x79, 0x08, 0x79, 0x79, 0xf8, 0x8e, 0x39, 0x6f, 0x49, 0x09, 0xf3,
    0x68, 0x62, 0xe3, 0x98, 0x70, 0xb8, 0xb2, 0xac, 0x86, 0xe1, 0x9d, 0x95, 0xa8, 0x44, 0x93, 0x13,
    0xf7, 0x6d, 0x0b, 0x38, 0x39, 0x6a, 0xf3, 0xbd, 0x87, 0x0d, 0xfc, 0xf8, 0xf4, 0x80, 0x26, 0xd6,
    0xe5, 0xb8, 0x89, 0x07, 0xe7, 0xd1, 0x7b, 0x5e, 0xab, 0x68, 0x6f, 0x5f, 0x3b, 0xc3, 0x1c, 0x7b,
    0x65, 0x52, 0x29, 0x42, 0xf6, 0xe9, 0xee, 0x02, 0xce, 0x39, 0xd7, 0x72, 0xe7, 0xc0, 0x13, 0x3f,
    0x59, 0x88, 0x08, 0x31, 0xe3, 0x00, 0x9d, 0x41, 0xbd, 0x13, 0xa2, 0xea, 0xe3, 0xb6, 0x32, 0xfc,
    0x77, 0xb4, 0x96, 0x80, 0xad, 0x97, 0x23, 0x80, 0xa4, 0xf9, 0x0b, 0x10, 0x52, 0x38, 0x7b, 0x14,
    0x09, 0xe6, 0x9e, 0xb5, 0xe2, 0xa2, 0x36, 0x63
};

static const struct rsa_public_key public_key = {
    .size   = 64,
    .n0inv  = 0x2e50c693,
    .n = {
        0x9ff8b865,
        0xa5dddd0c,
        0xe7407c5c,
        0x178a539e,
        0x6e8837f7,
        0x8c26bcc0,
        0xace622d7,
        0xb383783f,
        0x73f4a2cc,
        0x1dd568f4,
        0x58cb126e,
        0xd782f692,
        0x3341a8f1,
        0x1a254a2f,
        0xdabb7c0a,
        0x581c3c43,
        0x58a5a67a,
        0xb375dac4,
        0xb6c55e9c,
        0x30b9934f,
        0xd554dca2,
        0x8da51c6f,
        0x6e327aa9,
        0xb01407e6,
        0xac0761c2,
        0x62d3704d,
        0xf45093bf,
        0xb3353998,
        0x271e7d2e,
        0xecb5cf15,
        0x94f94c68,
        0xccd695ce,
        0xdbd46c3e,
        0x9f09695e,
        0x47f51cc9,
        0x174c0769,
        0x54a7a895,
        0x6a88cbd3,
        0x25d1ce13,
        0x4e23235d,
        0xe9fbd70b,
        0xb1c59dd7,
        0x98104da2,
        0x2735f1bb,
        0xd302d140,
        0x02db8dac,
        0xb530d551,
        0x99a394a1,
        0x4a0a5560,
        0x94d6a0fb,
        0xb19083c8,
        0x6ab27f87,
        0x66ab5ce5,
        0xc8688bdb,
        0x47387d8e,
        0xca34d1e2,
        0x358c289d,
        0xb1471bd4,
        0xf2c2f816,
        0xb1898d0e,
        0xab59eba4,
        0xad71c796,
        0x17288c2b,
        0xb9a73b35,
    },
    .rr = {
        0x0c7e7f5b,
        0x7bdef661,
        0xb852cf72,
        0xd22f2916,
        0x7f02bf3d,
        0x69c6fb80,
        0xb761bd91,
        0x351c4a8f,
        0xf1166eac,
        0x713be5d4,
        0xdce4933d,
        0x2c2c0039,
        0xdd5705ca,
        0xce5643cf,
        0x9851e780,
        0x99e28d00,
        0xf85fd219,
        0x65b47c3d,
        0x85241def,
        0xa31ec9fe,
        0x28ea3b47,
        0x829b7afd,
        0x1bc04205,
        0xa3be9581,
        0xd6ecbb94,
        0x3c08bbc1,
        0x2494af6a,
        0x16752276,
        0x7945e790,
        0xe6a2847b,
        0xe347b15c,
        0x55ca2ec5,
        0xa1b1f5ad,
        0x2662af9f,
        0xb8384b48,
        0x79087948,
        0x398ef879,
        0xf309496f,
        0x98e36268,
        0xacb2b870,
        0x959de186,
        0x139344a8,
        0x380b6df7,
        0xbdf36a39,
        0xf8fc0d87,
        0xd62680f4,
        0x0789b8e5,
        0x5e7bd1e7,
        0x5f6f68ab,
        0x7b1cc33b,
        0x42295265,
        0x02eee9f6,
        0x72d739ce,
        0x3f13c0e7,
        0x31088859,
        0x419d00e3,
        0xeaa213bd,
        0xfc32b6e3,
        0x8096b477,
        0x802397ad,
        0x100bf9a4,
        0x147b3852,
        0xb59ee609,
        0x6336a2e2,
    }
};