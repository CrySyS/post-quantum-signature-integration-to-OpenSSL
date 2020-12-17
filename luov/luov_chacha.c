/*
chacha-merged.c version 20080118
D. J. Bernstein
Public domain.
*/

#include "luov_chacha.h"

#define LUOV_U8C(v) (v##U)
#define LUOV_U32C(v) (v##U)

#define LUOV_U8V(v) ((unsigned char)(v) & LUOV_U8C(0xFF))
#define LUOV_U32V(v) ((uint32_t)(v) & LUOV_U32C(0xFFFFFFFF))

#define LUOV_ROTL32(v, n) \
  (LUOV_U32V((v) << (n)) | ((v) >> (32 - (n))))

#if (LUOV_USE_UNALIGNED == 1)
#define LUOV_U8TO32_LITTLE(p) \
    (*((uint32_t *)(p)))
#define LUOV_U32TO8_LITTLE(p, v) \
    do { \
      *((uint32_t *)(p)) = v; \
    } while (0)
#else
#define LUOV_U8TO32_LITTLE(p) \
  (((uint32_t)((p)[0])      ) | \
   ((uint32_t)((p)[1]) <<  8) | \
   ((uint32_t)((p)[2]) << 16) | \
   ((uint32_t)((p)[3]) << 24))
#define LUOV_U32TO8_LITTLE(p, v) \
  do { \
    (p)[0] = LUOV_U8V((v)      ); \
    (p)[1] = LUOV_U8V((v) >>  8); \
    (p)[2] = LUOV_U8V((v) >> 16); \
    (p)[3] = LUOV_U8V((v) >> 24); \
  } while (0)
#endif

#define LUOV_ROTATE(v,c) (LUOV_ROTL32(v,c))
#define LUOV_XOR(v,w) ((v) ^ (w))
#define LUOV_PLUS(v,w) (LUOV_U32V((v) + (w)))
#define LUOV_PLUSONE(v) (LUOV_PLUS((v),1))

#define LUOV_QUARTERROUND(a,b,c,d) \
  a = LUOV_PLUS(a,b); d = LUOV_ROTATE(LUOV_XOR(d,a),16); \
  c = LUOV_PLUS(c,d); b = LUOV_ROTATE(LUOV_XOR(b,c),12); \
  a = LUOV_PLUS(a,b); d = LUOV_ROTATE(LUOV_XOR(d,a), 8); \
  c = LUOV_PLUS(c,d); b = LUOV_ROTATE(LUOV_XOR(b,c), 7);

static const char sigma[16] = "expand 32-byte k";
static const char tau[16] = "expand 16-byte k";

void
chacha_keysetup(struct chacha_ctx *x,const unsigned char *k,uint32_t kbits)
{
  const char *constants;

  x->input[4] = LUOV_U8TO32_LITTLE(k + 0);
  x->input[5] = LUOV_U8TO32_LITTLE(k + 4);
  x->input[6] = LUOV_U8TO32_LITTLE(k + 8);
  x->input[7] = LUOV_U8TO32_LITTLE(k + 12);
  if (kbits == 256) { /* recommended */
    k += 16;
    constants = sigma;
  } else { /* kbits == 128 */
    constants = tau;
  }
  x->input[8] = LUOV_U8TO32_LITTLE(k + 0);
  x->input[9] = LUOV_U8TO32_LITTLE(k + 4);
  x->input[10] = LUOV_U8TO32_LITTLE(k + 8);
  x->input[11] = LUOV_U8TO32_LITTLE(k + 12);
  x->input[0] = LUOV_U8TO32_LITTLE(constants + 0);
  x->input[1] = LUOV_U8TO32_LITTLE(constants + 4);
  x->input[2] = LUOV_U8TO32_LITTLE(constants + 8);
  x->input[3] = LUOV_U8TO32_LITTLE(constants + 12);
}

void
chacha_ivsetup(struct chacha_ctx *x, const unsigned char *iv, const unsigned char *counter)
{
  x->input[12] = counter == NULL ? 0 : LUOV_U8TO32_LITTLE(counter + 0);
  x->input[13] = counter == NULL ? 0 : LUOV_U8TO32_LITTLE(counter + 4);
  x->input[14] = LUOV_U8TO32_LITTLE(iv + 0);
  x->input[15] = LUOV_U8TO32_LITTLE(iv + 4);
}

void
chacha_encrypt_bytes(struct chacha_ctx *x,const unsigned char *m,unsigned char *c,uint32_t bytes)
{
  uint32_t x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;
  uint32_t j0, j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12, j13, j14, j15;
  unsigned char *ctarget = NULL;
  unsigned char tmp[64];
  unsigned int i;

  if (!bytes) return;

  j0 = x->input[0];
  j1 = x->input[1];
  j2 = x->input[2];
  j3 = x->input[3];
  j4 = x->input[4];
  j5 = x->input[5];
  j6 = x->input[6];
  j7 = x->input[7];
  j8 = x->input[8];
  j9 = x->input[9];
  j10 = x->input[10];
  j11 = x->input[11];
  j12 = x->input[12];
  j13 = x->input[13];
  j14 = x->input[14];
  j15 = x->input[15];

  for (;;) {
    if (bytes < 64) {
#if (LUOV_USE_MEMCPY == 1)
      memcpy(tmp, m, bytes);
#else
      for (i = 0;i < bytes;++i) tmp[i] = m[i];
#endif
      m = tmp;
      ctarget = c;
      c = tmp;
    }
    x0 = j0;
    x1 = j1;
    x2 = j2;
    x3 = j3;
    x4 = j4;
    x5 = j5;
    x6 = j6;
    x7 = j7;
    x8 = j8;
    x9 = j9;
    x10 = j10;
    x11 = j11;
    x12 = j12;
    x13 = j13;
    x14 = j14;
    x15 = j15;
    for (i = 8;i > 0;i -= 2) {
      LUOV_QUARTERROUND( x0, x4, x8,x12)
      LUOV_QUARTERROUND( x1, x5, x9,x13)
      LUOV_QUARTERROUND( x2, x6,x10,x14)
      LUOV_QUARTERROUND( x3, x7,x11,x15)
      LUOV_QUARTERROUND( x0, x5,x10,x15)
      LUOV_QUARTERROUND( x1, x6,x11,x12)
      LUOV_QUARTERROUND( x2, x7, x8,x13)
      LUOV_QUARTERROUND( x3, x4, x9,x14)
    }
    x0 = LUOV_PLUS(x0,j0);
    x1 = LUOV_PLUS(x1,j1);
    x2 = LUOV_PLUS(x2,j2);
    x3 = LUOV_PLUS(x3,j3);
    x4 = LUOV_PLUS(x4,j4);
    x5 = LUOV_PLUS(x5,j5);
    x6 = LUOV_PLUS(x6,j6);
    x7 = LUOV_PLUS(x7,j7);
    x8 = LUOV_PLUS(x8,j8);
    x9 = LUOV_PLUS(x9,j9);
    x10 = LUOV_PLUS(x10,j10);
    x11 = LUOV_PLUS(x11,j11);
    x12 = LUOV_PLUS(x12,j12);
    x13 = LUOV_PLUS(x13,j13);
    x14 = LUOV_PLUS(x14,j14);
    x15 = LUOV_PLUS(x15,j15);

    x0 = LUOV_XOR(x0,LUOV_U8TO32_LITTLE(m + 0));
    x1 = LUOV_XOR(x1,LUOV_U8TO32_LITTLE(m + 4));
    x2 = LUOV_XOR(x2,LUOV_U8TO32_LITTLE(m + 8));
    x3 = LUOV_XOR(x3,LUOV_U8TO32_LITTLE(m + 12));
    x4 = LUOV_XOR(x4,LUOV_U8TO32_LITTLE(m + 16));
    x5 = LUOV_XOR(x5,LUOV_U8TO32_LITTLE(m + 20));
    x6 = LUOV_XOR(x6,LUOV_U8TO32_LITTLE(m + 24));
    x7 = LUOV_XOR(x7,LUOV_U8TO32_LITTLE(m + 28));
    x8 = LUOV_XOR(x8,LUOV_U8TO32_LITTLE(m + 32));
    x9 = LUOV_XOR(x9,LUOV_U8TO32_LITTLE(m + 36));
    x10 = LUOV_XOR(x10,LUOV_U8TO32_LITTLE(m + 40));
    x11 = LUOV_XOR(x11,LUOV_U8TO32_LITTLE(m + 44));
    x12 = LUOV_XOR(x12,LUOV_U8TO32_LITTLE(m + 48));
    x13 = LUOV_XOR(x13,LUOV_U8TO32_LITTLE(m + 52));
    x14 = LUOV_XOR(x14,LUOV_U8TO32_LITTLE(m + 56));
    x15 = LUOV_XOR(x15,LUOV_U8TO32_LITTLE(m + 60));

    j12 = LUOV_PLUSONE(j12);
    if (!j12) {
      j13 = LUOV_PLUSONE(j13);
      /* stopping at 2^70 bytes per nonce is user's responsibility */
    }

    LUOV_U32TO8_LITTLE(c + 0,x0);
    LUOV_U32TO8_LITTLE(c + 4,x1);
    LUOV_U32TO8_LITTLE(c + 8,x2);
    LUOV_U32TO8_LITTLE(c + 12,x3);
    LUOV_U32TO8_LITTLE(c + 16,x4);
    LUOV_U32TO8_LITTLE(c + 20,x5);
    LUOV_U32TO8_LITTLE(c + 24,x6);
    LUOV_U32TO8_LITTLE(c + 28,x7);
    LUOV_U32TO8_LITTLE(c + 32,x8);
    LUOV_U32TO8_LITTLE(c + 36,x9);
    LUOV_U32TO8_LITTLE(c + 40,x10);
    LUOV_U32TO8_LITTLE(c + 44,x11);
    LUOV_U32TO8_LITTLE(c + 48,x12);
    LUOV_U32TO8_LITTLE(c + 52,x13);
    LUOV_U32TO8_LITTLE(c + 56,x14);
    LUOV_U32TO8_LITTLE(c + 60,x15);

    if (bytes <= 64) {
      if (bytes < 64) {
#if (LUOV_USE_MEMCPY == 1)
        memcpy(ctarget, c, bytes);
#else
        for (i = 0;i < bytes;++i) ctarget[i] = c[i];
#endif
      }
      x->input[12] = j12;
      x->input[13] = j13;
      return;
    }
    bytes -= 64;
    c += 64;
    m += 64;
  }
}
