#include <string.h>
#include "iscrypt_ecc.h"
#include "iscrypt_ecc_test.h"

unsigned char xdata space_for_test[128];

ECCPRIKEYCTX xdata pSelfECCPriKey;   
ECCPUBLICKEYCTX xdata pSelfECCPubKey;

ECCPRIKEYCTX xdata pOtherECCPriKey;   
ECCPUBLICKEYCTX xdata pOtherECCPubKey;

ECCPUBLICKEYCTX xdata pAgreementKey;

ECCPOINT xdata pECCPoint;
ECCSIGNATURE xdata pSignature;
ECCPLAINTEXT xdata pPlaintext; 
ECCCIPHERTEXT xdata pCiphertext;

unsigned char code ECC_160_PARA[] = 
{
    0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF4,0X8B,    \
    0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF4,0X88,    \
    0X41,0X7F,0X0E,0X7C,0X28,0X25,0X00,0X0C,0X83,0X8B,0X7C,0X95,0X15,0XD1,0XFF,0XF3,0X69,0XB5,0X0E,0X16,    \
    0X4F,0X3A,0X60,0X9A,0XEC,0X06,0XDE,0X6E,0X46,0X6E,0X2D,0XB5,0X2F,0X0E,0XD5,0X36,0XC1,0XFF,0X87,0XF4,    \
    0X85,0X59,0XEF,0X2A,0XDD,0XA2,0X00,0X56,0XC4,0XBE,0X54,0XE3,0X06,0X5D,0XE5,0XFE,0X39,0X52,0XFF,0X22,    \
    0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XA8,0XC8,0X95,0XF7,0X67,0X85,0XFC,0X17,0X91,0X71    
};

unsigned char code ECC_192_PARA[] = 
{
    0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,    \
    0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,    \
    0X64,0X21,0X05,0X19,0XE5,0X9C,0X80,0XE7,0X0F,0XA7,0XE9,0XAB,0X72,0X24,0X30,0X49,0XFE,0XB8,0XDE,0XEC,0XC1,0X46,0XB9,0XB1,    \
    0X18,0X8D,0XA8,0X0E,0XB0,0X30,0X90,0XF6,0X7C,0XBF,0X20,0XEB,0X43,0XA1,0X88,0X00,0XF4,0XFF,0X0A,0XFD,0X82,0XFF,0X10,0X12,    \
	0X07,0X19,0X2B,0X95,0XFF,0XC8,0XDA,0X78,0X63,0X10,0X11,0XED,0X6B,0X24,0XCD,0XD5,0X73,0XF9,0X77,0XA1,0X1E,0X79,0X48,0X11,    \    
	0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X99,0XDE,0XF8,0X36,0X14,0X6B,0XC9,0XB1,0XB4,0XD2,0X28,0X31
};

unsigned char code ECC_224_PARA[] = 
{
    0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,    \
    0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,    \    
    0XB4,0X05,0X0A,0X85,0X0C,0X04,0XB3,0XAB,0XF5,0X41,0X32,0X56,0X50,0X44,0XB0,0XB7,0XD7,0XBF,0XD8,0XBA,0X27,0X0B,0X39,0X43,0X23,0X55,0XFF,0XB4,    \
    0XB7,0X0E,0X0C,0XBD,0X6B,0XB4,0XBF,0X7F,0X32,0X13,0X90,0XB9,0X4A,0X03,0XC1,0XD3,0X56,0XC2,0X11,0X22,0X34,0X32,0X80,0XD6,0X11,0X5C,0X1D,0X21,    \
    0XBD,0X37,0X63,0X88,0XB5,0XF7,0X23,0XFB,0X4C,0X22,0XDF,0XE6,0XCD,0X43,0X75,0XA0,0X5A,0X07,0X47,0X64,0X44,0XD5,0X81,0X99,0X85,0X00,0X7E,0X34,    \   
    0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X16,0XA2,0XE0,0XB8,0XF0,0X3E,0X13,0XDD,0X29,0X45,0X5C,0X5C,0X2A,0X3D     \
};

unsigned char code ECC_256_PARA[] = 
{
    0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,   \
    0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,   \
    0X28,0XE9,0XFA,0X9E,0X9D,0X9F,0X5E,0X34,0X4D,0X5A,0X9E,0X4B,0XCF,0X65,0X09,0XA7,0XF3,0X97,0X89,0XF5,0X15,0XAB,0X8F,0X92,0XDD,0XBC,0XBD,0X41,0X4D,0X94,0X0E,0X93,   \
    0X32,0XC4,0XAE,0X2C,0X1F,0X19,0X81,0X19,0X5F,0X99,0X04,0X46,0X6A,0X39,0XC9,0X94,0X8F,0XE3,0X0B,0XBF,0XF2,0X66,0X0B,0XE1,0X71,0X5A,0X45,0X89,0X33,0X4C,0X74,0XC7,   \
    0XBC,0X37,0X36,0XA2,0XF4,0XF6,0X77,0X9C,0X59,0XBD,0XCE,0XE3,0X6B,0X69,0X21,0X53,0XD0,0XA9,0X87,0X7C,0XC6,0X2A,0X47,0X40,0X02,0XDF,0X32,0XE5,0X21,0X39,0XF0,0XA0,   \
    0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X72,0X03,0XDF,0X6B,0X21,0XC6,0X05,0X2B,0X53,0XBB,0XF4,0X09,0X39,0XD5,0X41,0X23
};


unsigned char ECC_TEST_160(void)
{
    unsigned char ret;
    int i;
    
    EC_PARA xdata ec_para_160;
//     EC_PARA xdata ec_para_160 = 
//     {
//         160,
//             
//         {0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF4,0X8B},
//         {0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF4,0X88},
//         {0X41,0X7F,0X0E,0X7C,0X28,0X25,0X00,0X0C,0X83,0X8B,0X7C,0X95,0X15,0XD1,0XFF,0XF3,0X69,0XB5,0X0E,0X16},
//         {0X4F,0X3A,0X60,0X9A,0XEC,0X06,0XDE,0X6E,0X46,0X6E,0X2D,0XB5,0X2F,0X0E,0XD5,0X36,0XC1,0XFF,0X87,0XF4},
//         {0X85,0X59,0XEF,0X2A,0XDD,0XA2,0X00,0X56,0XC4,0XBE,0X54,0XE3,0X06,0X5D,0XE5,0XFE,0X39,0X52,0XFF,0X22},
//         {0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XA8,0XC8,0X95,0XF7,0X67,0X85,0XFC,0X17,0X91,0X71},
//         
//         {0},
//         
//         {0},{0},{0},
//         
//         {0},{0},{0}
//     };
    
    unsigned char xdata SelfPrikey[] = 
    {
        0X3A,0XC0,0XE7,0X17,0XEB,0X61,0X60,0X2E,0XFC,0XBB,0X1D,0XE8,0X1A,0XA1,0X44,0XA2,
        0X72,0XB4,0X4B,0XA1
    };
    
    unsigned char xdata SelfPubkey[] = 
    {
        0XDF,0XFA,0X23,0XF8,0X08,0X51,0X48,0XF4,0X6E,0X87,0X56,0XEE,0X54,0X0A,0X5A,0XE1,
        0XF5,0X4C,0X16,0XFB,
        0X8E,0X34,0X50,0X5D,0X2D,0X08,0XC8,0X95,0XF7,0X23,0X30,0X80,0XF3,0XE1,0X07,0X8F,
        0X5D,0X60,0XAF,0X41
    };
    
    unsigned char xdata Digest[] = 
    {
        0X02,0XB0,0X04,0X2B,0X54,0XB5,0X8B,0X69,0X02,0X6F,0X9C,0X6A,0XBE,0XED,0X1D,0XB1,
        0X13,0XEC,0X50,0X86
    };
    
    unsigned char xdata OtherPrikey[] = 
    {
        0X25,0XFB,0XB3,0X2E,0XFB,0XEC,0X6E,0XCB,0X13,0X14,0X33,0X2A,0X02,0X65,0X82,0XDB,
        0X7B,0XE0,0X0C,0X05
    };
    
    unsigned char xdata OtherPubkey[] = 
    {
        0X95,0XA4,0X13,0X6E,0XD7,0X7D,0X08,0X73,0X97,0X07,0XF3,0X6C,0X2D,0X0A,0X6A,0X8C,
        0X38,0X17,0XC6,0X6E,
        0X25,0X84,0X4D,0XEE,0XBD,0XAD,0X1A,0X7F,0XDF,0X13,0XDA,0X1A,0XFA,0X51,0X4A,0XAE,
        0XB1,0X2F,0X80,0XE2
    };
    
    unsigned char xdata reduce_test_vector[32] = 
    {
        0X32,0XC4,0XAE,0X2C,0X1F,0X19,0X81,0X19,0X5F,0X99,0X04,0X46,0X6A,0X39,0XC9,0X94,
        0X8F,0XE3,0X0B,0XBF,0XF2,0X66,0X0B,0XE1,0X71,0X5A,0X45,0X89,0X33,0X4C,0X74,0XC7
    };
    
    unsigned char xdata ReduceResult[20] = 
    {
        0XEC,0XDF,0X77,0X3B,0X1A,0X83,0XE9,0X3D,0X98,0X7C,0X97,0X96,0X81,0XDF,0X41,0X88,
        0X06,0XF0,0XD0,0XD1
    };
    
    memset(&ec_para_160, 0, sizeof(ec_para_160));
    
    ec_para_160.bitLen = 160;
    
    memcpy(ec_para_160.p, ECC_160_PARA, 20);
    memcpy(ec_para_160.a, ECC_160_PARA+20, 20);
    memcpy(ec_para_160.b, ECC_160_PARA+40, 20);
    memcpy(ec_para_160.Gx, ECC_160_PARA+60, 20);
    memcpy(ec_para_160.Gy, ECC_160_PARA+80, 20);
    memcpy(ec_para_160.n, ECC_160_PARA+100, 20);
        
    //////////////////////////////////////////
    ret = ECC_Init(&ec_para_160);
    if (0 != ret)
    {
        return 1;
    }

    //////////////////////////////////////////
    memcpy(space_for_test, ec_para_160.Gx, 20);
    memcpy(space_for_test+20, ec_para_160.Gy, 20);
    
    pSelfECCPubKey.x = space_for_test;
    pSelfECCPubKey.y = space_for_test+20;

    ret = ECC_PointMult(&ec_para_160, SelfPrikey, &pSelfECCPubKey);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, SelfPubkey, 40);
    if (0 != ret)
    {
        return 1;
    }
 
    //////////////////////////////////////////
    pSelfECCPriKey.d = SelfPrikey;
    pSelfECCPubKey.x = SelfPubkey;
    pSelfECCPubKey.y = SelfPubkey+20;
    
    pSignature.r = space_for_test;
    pSignature.s = space_for_test+32;
   
    ret = ECC_ECDSA_Sign(&ec_para_160, &pSelfECCPriKey, Digest, &pSignature);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = ECC_ECDSA_Verify(&ec_para_160, &pSelfECCPubKey, Digest, &pSignature);
    if (0 != ret)
    {
        return 1;
    }
    
    ///////////////////////////////////////////
    
    memset(space_for_test, 0x11, 20);
    
    pPlaintext.pd = space_for_test;
    pPlaintext.len = 20;
    
    pECCPoint.x = space_for_test+32;
    pECCPoint.y = space_for_test+52;
    
    pCiphertext.p = &pECCPoint;
    pCiphertext.c = space_for_test+96;
    pCiphertext.h = NULL;
    pCiphertext.clen = 0;
       
    ret = ECC_ECES_Encrypt(&ec_para_160, &pSelfECCPubKey, &pPlaintext, &pCiphertext);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = ECC_ECES_Decrypt(&ec_para_160, &pSelfECCPriKey, &pCiphertext, &pPlaintext);
    if (0 != ret)
    {
        return 1;
    }
    
    for (i = 0; i < 20; i++)
    {
        if (0x11 != space_for_test[i])
        {
            return 1;
        }
    }
    
    /////////////////////////////////
    pSelfECCPriKey.d = SelfPrikey;
    pSelfECCPubKey.x = SelfPubkey;
    pSelfECCPubKey.y = SelfPubkey+20;

    pOtherECCPriKey.d = OtherPrikey;
    pOtherECCPubKey.x = OtherPubkey;
    pOtherECCPubKey.y = OtherPubkey+20;
    
    pAgreementKey.x = space_for_test;
    pAgreementKey.y = space_for_test+20;
    
    ret = ECC_ECDH(&ec_para_160, &pSelfECCPriKey, &pOtherECCPubKey, &pAgreementKey);
    if (0 != ret)
    {
        return 1;
    }

    pAgreementKey.x = space_for_test+64;
    pAgreementKey.y = space_for_test+84;
    
    ret = ECC_ECDH(&ec_para_160, &pOtherECCPriKey, &pSelfECCPubKey, &pAgreementKey);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, space_for_test+64, 40);
    if (0 != ret)
    {
        return 1;
    }
    
    ///////////////////////////////////////////////
    
    memcpy(space_for_test, reduce_test_vector, 32);
        
    ret = ECC_ModReduceN(&ec_para_160, space_for_test, 32);

    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, ReduceResult, 20);
    if (0 != ret)
    {
        return 1;
    };
    
    return 0;
}
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

unsigned char ECC_TEST_192(void)
{
    unsigned char ret;
    int i;
    
    EC_PARA xdata ec_para_192;
    
    unsigned char xdata SelfPrikey[] = 
    {
        0X3A,0XC0,0XE7,0X17,0XEB,0X61,0X60,0X2E,0XFC,0XBB,0X1D,0XE8,0X1A,0XA1,0X44,0XA2,
        0X72,0XB4,0X4B,0XA1,0XF1,0X69,0X36,0XAC
    };
    
    unsigned char xdata SelfPubkey[] = 
    {
        0XC4,0X5C,0XE4,0X87,0X32,0X5F,0XB2,0XA8,0XD9,0XCD,0X67,0X22,0X23,0X8B,0X63,0X89,
        0X59,0XBE,0X39,0X1D,0X19,0X68,0X1F,0X08,
        0XD0,0X0C,0XDE,0XAC,0XAD,0X31,0X50,0XA0,0X59,0X04,0X40,0X1C,0XD1,0X42,0XE5,0X4A,
        0X28,0X74,0X39,0X02,0XA6,0X0C,0X8B,0X68
    };
    
    unsigned char xdata Digest[] = 
    {
        0X02,0XB0,0X04,0X2B,0X54,0XB5,0X8B,0X69,0X02,0X6F,0X9C,0X6A,0XBE,0XED,0X1D,0XB1,
        0X13,0XEC,0X50,0X86,0X5F,0XB1,0X11,0X31
    };
    
    unsigned char xdata OtherPrikey[] = 
    {
        0X25,0XFB,0XB3,0X2E,0XFB,0XEC,0X6E,0XCB,0X13,0X14,0X33,0X2A,0X02,0X65,0X82,0XDB,
        0X7B,0XE0,0X0C,0X05,0X1C,0XF2,0XFA,0X80
    };
    
    unsigned char xdata OtherPubkey[] = 
    {
        0X2D,0XA5,0XEC,0XD2,0XEB,0X65,0X9A,0X5C,0X7B,0XAF,0X15,0XEE,0XE4,0XF0,0X3C,0XE8,
        0X5F,0XAE,0X74,0X32,0XEE,0XBF,0X64,0X75,
        0XA5,0XAC,0X43,0X21,0XFA,0X3D,0X25,0X51,0XB3,0X23,0XC0,0X09,0X83,0X5C,0X5A,0XEA,
        0X1E,0X7D,0XEA,0X8C,0XA2,0X76,0X58,0X38
    };
    
    unsigned char xdata reduce_test_vector[32] = 
    {
        0X32,0XC4,0XAE,0X2C,0X1F,0X19,0X81,0X19,0X5F,0X99,0X04,0X46,0X6A,0X39,0XC9,0X94,
        0X8F,0XE3,0X0B,0XBF,0XF2,0X66,0X0B,0XE1,0X71,0X5A,0X45,0X89,0X33,0X4C,0X74,0XC7
    };
    
    unsigned char xdata ReduceResult[24] = 
    {
        0X5F,0X99,0X04,0X46,0X7E,0X7A,0XB3,0XE0,0X03,0XDF,0X1D,0X53,0XDF,0XCE,0X92,0X29,
        0XA7,0XFC,0XB5,0X40,0XC8,0XBC,0XD6,0XFE
    };

    
    memset(&ec_para_192, 0, sizeof(ec_para_192));

    ec_para_192.bitLen = 192;
    memcpy(ec_para_192.p, ECC_192_PARA, 24);
    memcpy(ec_para_192.a, ECC_192_PARA+24, 24);
    memcpy(ec_para_192.b, ECC_192_PARA+48, 24);
    memcpy(ec_para_192.Gx, ECC_192_PARA+72, 24);
    memcpy(ec_para_192.Gy, ECC_192_PARA+96, 24);
    memcpy(ec_para_192.n, ECC_192_PARA+120, 24);
        
    //////////////////////////////////////////
    ret = ECC_Init(&ec_para_192);
    if (0 != ret)
    {
        return 1;
    }

    //////////////////////////////////////////
    memcpy(space_for_test, ec_para_192.Gx, 24);
    memcpy(space_for_test+24, ec_para_192.Gy, 24);
    
    pSelfECCPubKey.x = space_for_test;
    pSelfECCPubKey.y = space_for_test+24;

    ret = ECC_PointMult(&ec_para_192, SelfPrikey, &pSelfECCPubKey);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, SelfPubkey, 48);
    if (0 != ret)
    {
        return 1;
    }
 
    //////////////////////////////////////////
    pSelfECCPriKey.d = SelfPrikey;
    pSelfECCPubKey.x = SelfPubkey;
    pSelfECCPubKey.y = SelfPubkey+24;
    
    pSignature.r = space_for_test;
    pSignature.s = space_for_test+32;
   
    ret = ECC_ECDSA_Sign(&ec_para_192, &pSelfECCPriKey, Digest, &pSignature);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = ECC_ECDSA_Verify(&ec_para_192, &pSelfECCPubKey, Digest, &pSignature);
    if (0 != ret)
    {
        return 1;
    }
    
    ///////////////////////////////////////////
    
    memset(space_for_test, 0x11, 24);
    
    pPlaintext.pd = space_for_test;
    pPlaintext.len = 24;
    
    pECCPoint.x = space_for_test+32;
    pECCPoint.y = space_for_test+56;
    
    pCiphertext.p = &pECCPoint;
    pCiphertext.c = space_for_test+96;
    pCiphertext.h = NULL;
    pCiphertext.clen = 0;
       
    ret = ECC_ECES_Encrypt(&ec_para_192, &pSelfECCPubKey, &pPlaintext, &pCiphertext);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = ECC_ECES_Decrypt(&ec_para_192, &pSelfECCPriKey, &pCiphertext, &pPlaintext);
    if (0 != ret)
    {
        return 1;
    }
    
    for (i = 0; i < 24; i++)
    {
        if (0x11 != space_for_test[i])
        {
            return 1;
        }
    }
    
    /////////////////////////////////
    pSelfECCPriKey.d = SelfPrikey;
    pSelfECCPubKey.x = SelfPubkey;
    pSelfECCPubKey.y = SelfPubkey+24;

    pOtherECCPriKey.d = OtherPrikey;
    pOtherECCPubKey.x = OtherPubkey;
    pOtherECCPubKey.y = OtherPubkey+24;
    
    pAgreementKey.x = space_for_test;
    pAgreementKey.y = space_for_test+24;
    
    ret = ECC_ECDH(&ec_para_192, &pSelfECCPriKey, &pOtherECCPubKey, &pAgreementKey);
    if (0 != ret)
    {
        return 1;
    }

    pAgreementKey.x = space_for_test+64;
    pAgreementKey.y = space_for_test+88;
    
    ret = ECC_ECDH(&ec_para_192, &pOtherECCPriKey, &pSelfECCPubKey, &pAgreementKey);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, space_for_test+64, 48);
    if (0 != ret)
    {
        return 1;
    }
    
    ////////////////////////////////////
    ////////////////////////////////////////
    memcpy(space_for_test, reduce_test_vector, 32);
        
    ret = ECC_ModReduceN(&ec_para_192, space_for_test, 32);

    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, ReduceResult, 24);
    if (0 != ret)
    {
        return 1;
    };

    
    return 0;
}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
unsigned char ECC_TEST_224(void)
{
    unsigned char ret;
    int i;
    
    EC_PARA xdata ec_para_224;
    
    unsigned char xdata SelfPrikey[] = 
    {
        0X3A,0XC0,0XE7,0X17,0XEB,0X61,0X60,0X2E,0XFC,0XBB,0X1D,0XE8,0X1A,0XA1,0X44,0XA2,
        0X72,0XB4,0X4B,0XA1,0XF1,0X69,0X36,0XAC,0XA4,0XE7,0XF4,0X14
    };
    
    unsigned char xdata SelfPubkey[] = 
    {
        0XD5,0X83,0X3A,0X56,0X8B,0X78,0XB9,0XDD,0X11,0XED,0X5A,0XB1,0XE9,0X8D,0X07,0XD6,
        0X28,0X4F,0X9D,0X9F,0X12,0X14,0X6F,0XE5,0X24,0X67,0X1F,0XD5,
        0XDA,0X27,0X3E,0X16,0X23,0XC5,0X2B,0X7B,0XA5,0X8D,0XAA,0X27,0X59,0X83,0X4C,0XF5,
        0XBF,0X4F,0XDE,0X74,0X28,0X7B,0X30,0X3E,0XA6,0X90,0X29,0X7B
    };
    
    unsigned char xdata Digest[] = 
    {
        0X02,0XB0,0X04,0X2B,0X54,0XB5,0X8B,0X69,0X02,0X6F,0X9C,0X6A,0XBE,0XED,0X1D,0XB1,
        0X13,0XEC,0X50,0X86,0X5F,0XB1,0X11,0X31,0XA6,0X90,0X29,0X7B
    };
    
    unsigned char xdata OtherPrikey[] = 
    {
        0X25,0XFB,0XB3,0X2E,0XFB,0XEC,0X6E,0XCB,0X13,0X14,0X33,0X2A,0X02,0X65,0X82,0XDB,
        0X7B,0XE0,0X0C,0X05,0X1C,0XF2,0XFA,0X80,0XAB,0X09,0X52,0X75
    };
    
    unsigned char xdata OtherPubkey[] = 
    {
        0X64,0X68,0XBF,0X93,0X8F,0X11,0XE3,0X1C,0X15,0X59,0X18,0X8A,0X1F,0XCD,0X13,0XA0,
        0X08,0X0B,0X04,0XD2,0X40,0XCF,0XFB,0X27,0XC8,0XC8,0XAD,0X5B,
        0XDC,0XED,0X41,0X50,0X1B,0X2D,0X8C,0X00,0XD4,0XA8,0X01,0XC7,0XE9,0X8E,0X0F,0X20,
        0XCD,0X66,0XCD,0X05,0X9E,0XD8,0X94,0XC1,0X4A,0XC0,0X7A,0XF4
    };
    
    unsigned char xdata reduce_test_vector[32] = 
    {
        0X32,0XC4,0XAE,0X2C,0X1F,0X19,0X81,0X19,0X5F,0X99,0X04,0X46,0X6A,0X39,0XC9,0X94,
        0X8F,0XE3,0X0B,0XBF,0XF2,0X66,0X0B,0XE1,0X71,0X5A,0X45,0X89,0X33,0X4C,0X74,0XC7
    };
    
    unsigned char xdata ReduceResult[28] = 
    {
        0X1F,0X19,0X81,0X19,0X5F,0X99,0X04,0X46,0X6A,0X39,0XF7,0XDC,0X0A,0X10,0X46,0X7F,
        0X8F,0XEA,0X28,0X52,0X90,0X25,0X52,0X06,0X6E,0X0B,0XBC,0X4B
    };

    
    memset(&ec_para_224, 0, sizeof(ec_para_224));

    ec_para_224.bitLen = 224;
    memcpy(ec_para_224.p, ECC_224_PARA, 28);
    memcpy(ec_para_224.a, ECC_224_PARA+28, 28);
    memcpy(ec_para_224.b, ECC_224_PARA+56, 28);
    memcpy(ec_para_224.Gx, ECC_224_PARA+84, 28);
    memcpy(ec_para_224.Gy, ECC_224_PARA+112, 28);
    memcpy(ec_para_224.n, ECC_224_PARA+140, 28);
    

    //////////////////////////////////////////
    memcpy(space_for_test, ec_para_224.Gx, 28);
    memcpy(space_for_test+28, ec_para_224.Gy, 28);
    
    pSelfECCPubKey.x = space_for_test;
    pSelfECCPubKey.y = space_for_test+28;
    
    //////////////////////////////////////////
    ret = ECC_Init(&ec_para_224);
    if (0 != ret)
    {
        return 1;
    }

    ret = ECC_PointMult(&ec_para_224, SelfPrikey, &pSelfECCPubKey);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, SelfPubkey, 56);
    if (0 != ret)
    {
        return 1;
    }

    
    //////////////////////////////////////////
    pSelfECCPriKey.d = SelfPrikey;
    pSelfECCPubKey.x = SelfPubkey;
    pSelfECCPubKey.y = SelfPubkey+28;
    
    pSignature.r = space_for_test;
    pSignature.s = space_for_test+32;
   
    ret = ECC_ECDSA_Sign(&ec_para_224, &pSelfECCPriKey, Digest, &pSignature);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = ECC_ECDSA_Verify(&ec_para_224, &pSelfECCPubKey, Digest, &pSignature);
    if (0 != ret)
    {
        return 1;
    }
    
    ///////////////////////////////////////////
    memset(space_for_test, 0x11, 28);
    
    pSelfECCPriKey.d = SelfPrikey;
    pSelfECCPubKey.x = SelfPubkey;
    pSelfECCPubKey.y = SelfPubkey+28;
    
    pPlaintext.pd = space_for_test;
    pPlaintext.len = 28;
    
    pECCPoint.x = space_for_test+32;
    pECCPoint.y = space_for_test+60;
    
    pCiphertext.p = &pECCPoint;
    pCiphertext.c = space_for_test+96;
    pCiphertext.h = NULL;
    pCiphertext.clen = 0;
       
    ret = ECC_ECES_Encrypt(&ec_para_224, &pSelfECCPubKey, &pPlaintext, &pCiphertext);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = ECC_ECES_Decrypt(&ec_para_224, &pSelfECCPriKey, &pCiphertext, &pPlaintext);
    if (0 != ret)
    {
        return 1;
    }
    
    for (i = 0; i < 28; i++)
    {
        if (0x11 != space_for_test[i])
        {
            return 1;
        }
    }
    
    /////////////////////////////////
    pSelfECCPriKey.d = SelfPrikey;
    pSelfECCPubKey.x = SelfPubkey;
    pSelfECCPubKey.y = SelfPubkey+28;

    pOtherECCPriKey.d = OtherPrikey;
    pOtherECCPubKey.x = OtherPubkey;
    pOtherECCPubKey.y = OtherPubkey+28;
    
    pAgreementKey.x = space_for_test;
    pAgreementKey.y = space_for_test+28;
    
    ret = ECC_ECDH(&ec_para_224, &pSelfECCPriKey, &pOtherECCPubKey, &pAgreementKey);
    if (0 != ret)
    {
        return 1;
    }

    pAgreementKey.x = space_for_test+64;
    pAgreementKey.y = space_for_test+92;
    
    ret = ECC_ECDH(&ec_para_224, &pOtherECCPriKey, &pSelfECCPubKey, &pAgreementKey);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, space_for_test+64, 56);
    if (0 != ret)
    {
        return 1;
    }
    
    ////////////////////////////////////////
    memcpy(space_for_test, reduce_test_vector, 32);
        
    ret = ECC_ModReduceN(&ec_para_224, space_for_test, 32);

    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, ReduceResult, 28);
    if (0 != ret)
    {
        return 1;
    };

    
    return 0;
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
unsigned char ECC_TEST_256(void)
{
    unsigned char ret;
    int i;
    
    EC_PARA xdata ec_para_256;
    
    unsigned char xdata SelfPrikey[] = 
    {
        0X39,0X45,0X20,0X8F,0X7B,0X21,0X44,0XB1,0X3F,0X36,0XE3,0X8A,0XC6,0XD3,0X9F,0X95,    \
        0X88,0X93,0X93,0X69,0X28,0X60,0XB5,0X1A,0X42,0XFB,0X81,0XEF,0X4D,0XF7,0XC5,0XB8						  	
    };
    
    unsigned char xdata SelfPubkey[] = 
    {
        0X09,0XF9,0XDF,0X31,0X1E,0X54,0X21,0XA1,0X50,0XDD,0X7D,0X16,0X1E,0X4B,0XC5,0XC6,    \
        0X72,0X17,0X9F,0XAD,0X18,0X33,0XFC,0X07,0X6B,0XB0,0X8F,0XF3,0X56,0XF3,0X50,0X20,    \
        0XCC,0XEA,0X49,0X0C,0XE2,0X67,0X75,0XA5,0X2D,0XC6,0XEA,0X71,0X8C,0XC1,0XAA,0X60,   \
        0X0A,0XED,0X05,0XFB,0XF3,0X5E,0X08,0X4A,0X66,0X32,0XF6,0X07,0X2D,0XA9,0XAD,0X13
    };
    
    unsigned char xdata Digest[] = 
    {
        0XF0,0XB4,0X3E,0X94,0XBA,0X45,0XAC,0XCA,0XAC,0XE6,0X92,0XED,0X53,0X43,0X82,0XEB,    \
        0X17,0XE6,0XAB,0X5A,0X19,0XCE,0X7B,0X31,0XF4,0X48,0X6F,0XDF,0XC0,0XD2,0X86,0X40
    };
    
    unsigned char xdata OtherPrikey[] = 
    {
        0X81,0XEB,0X26,0XE9,0X41,0XBB,0X5A,0XF1,0X6D,0XF1,0X16,0X49,0X5F,0X90,0X69,0X52,    \
        0X72,0XAE,0X2C,0XD6,0X3D,0X6C,0X4A,0XE1,0X67,0X84,0X18,0XBE,0X48,0X23,0X00,0X29
    };
    
    unsigned char xdata OtherPubkey[] = 
    {
        0X16,0X0E,0X12,0X89,0X7D,0XF4,0XED,0XB6,0X1D,0XD8,0X12,0XFE,0XB9,0X67,0X48,0XFB,    \
        0XD3,0XCC,0XF4,0XFF,0XE2,0X6A,0XA6,0XF6,0XDB,0X95,0X40,0XAF,0X49,0XC9,0X42,0X32,	\
        0X4A,0X7D,0XAD,0X08,0XBB,0X9A,0X45,0X95,0X31,0X69,0X4B,0XEB,0X20,0XAA,0X48,0X9D,    \
        0X66,0X49,0X97,0X5E,0X1B,0XFC,0XF8,0XC4,0X74,0X1B,0X78,0XB4,0XB2,0X23,0X00,0X7F
    };

    memset(&ec_para_256, 0, sizeof(ec_para_256));

    ec_para_256.bitLen = 256;
    memcpy(ec_para_256.p, ECC_256_PARA, 32);
    memcpy(ec_para_256.a, ECC_256_PARA+32, 32);
    memcpy(ec_para_256.b, ECC_256_PARA+64, 32);
    memcpy(ec_para_256.Gx, ECC_256_PARA+96, 32);
    memcpy(ec_para_256.Gy, ECC_256_PARA+128, 32);
    memcpy(ec_para_256.n, ECC_256_PARA+160, 32);
    
    //////////////////////////////////////////
    memcpy(space_for_test, ec_para_256.Gx, 32);
    memcpy(space_for_test+32, ec_para_256.Gy, 32);
    
    pSelfECCPubKey.x = space_for_test;
    pSelfECCPubKey.y = space_for_test+32;
    
    //////////////////////////////////////////
    ret = ECC_Init(&ec_para_256);
    if (0 != ret)
    {
        return 1;
    }


    ret = ECC_PointMult(&ec_para_256, SelfPrikey, &pSelfECCPubKey);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, SelfPubkey, 64);
    if (0 != ret)
    {
        return 1;
    }
    
    //////////////////////////////////////////
    pSelfECCPriKey.d = SelfPrikey;
    pSelfECCPubKey.x = SelfPubkey;
    pSelfECCPubKey.y = SelfPubkey+32;
    
    pSignature.r = space_for_test;
    pSignature.s = space_for_test+32;
   
    ret = ECC_ECDSA_Sign(&ec_para_256, &pSelfECCPriKey, Digest, &pSignature);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = ECC_ECDSA_Verify(&ec_para_256, &pSelfECCPubKey, Digest, &pSignature);
    if (0 != ret)
    {
        return 1;
    }
    
    ///////////////////////////////////////////
    memset(space_for_test, 0x11, 32);
    
    pPlaintext.pd = space_for_test;
    pPlaintext.len = 32;
    
    pECCPoint.x = space_for_test+32;
    pECCPoint.y = space_for_test+64;
    
    pCiphertext.p = &pECCPoint;
    pCiphertext.c = space_for_test+96;
    pCiphertext.h = NULL;
    pCiphertext.clen = 0;
       
    ret = ECC_ECES_Encrypt(&ec_para_256, &pSelfECCPubKey, &pPlaintext, &pCiphertext);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = ECC_ECES_Decrypt(&ec_para_256, &pSelfECCPriKey, &pCiphertext, &pPlaintext);
    if (0 != ret)
    {
        return 1;
    }
    
    for (i = 0; i < 32; i++)
    {
        if (0x11 != space_for_test[i])
        {
            return 1;
        }
    }
    
    /////////////////////////////////
    pSelfECCPriKey.d = SelfPrikey;
    pSelfECCPubKey.x = SelfPubkey;
    pSelfECCPubKey.y = SelfPubkey+32;

    pOtherECCPriKey.d = OtherPrikey;
    pOtherECCPubKey.x = OtherPubkey;
    pOtherECCPubKey.y = OtherPubkey+32;
    
    pAgreementKey.x = space_for_test;
    pAgreementKey.y = space_for_test+32;
    
    ret = ECC_ECDH(&ec_para_256, &pSelfECCPriKey, &pOtherECCPubKey, &pAgreementKey);
    if (0 != ret)
    {
        return 1;
    }

    pAgreementKey.x = space_for_test+64;
    pAgreementKey.y = space_for_test+96;
    
    ret = ECC_ECDH(&ec_para_256, &pOtherECCPriKey, &pSelfECCPubKey, &pAgreementKey);
    if (0 != ret)
    {
        return 1;
    }
    
    ret = memcmp(space_for_test, space_for_test+64, 64);
    if (0 != ret)
    {
        return 1;
    }
    
    return 0;
}


