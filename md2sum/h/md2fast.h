#define MD2_BLOCK_SIZE 16

typedef struct {
   uint8_t data[MD2_BLOCK_SIZE];
   uint8_t state[MD2_BLOCK_SIZE*3];
   uint8_t checksum[MD2_BLOCK_SIZE];
   int len;
} MD2FAST_CTX;

void md2fast_init(MD2FAST_CTX *ctx);
void md2fast_update(MD2FAST_CTX *ctx, const uint8_t data[], int len);
void md2fast_final(MD2FAST_CTX *ctx, uint8_t hash[MD2_BLOCK_SIZE]);

