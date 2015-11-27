static void md2fast_transform(MD2FAST_CTX * ctx)
{
    uint8_t *bx = s;

    uint16_t dx = 0, cx;
    uint8_t al = 0;
    uint8_t *di, *si;

    uint16_t *siw = (uint16_t *) ctx;
    uint16_t *diw = siw + 16;
    uint16_t ax;

    cx = 8;
    do {
        ax = *(siw);
        siw++;
        *(diw) = ax;
        *(diw + 8) = ax ^ *(diw - 8);
        diw++;
        cx--;
    } while (cx);

    do {
        di = ((uint8_t *) ctx) + 16;
        cx = 12;
        do {
            al = bx[al & 0xff];
            al ^= *di;
            *di = al;
            di++;
            al = bx[al & 0xff];
            al ^= *di;
            *di = al;
            di++;
            al = bx[al & 0xff];
            al ^= *di;
            *di = al;
            di++;
            al = bx[al & 0xff];
            al ^= *di;
            *di = al;
            di++;
            cx--;
        } while (cx);
        al += dx;
        dx++;
    } while (dx < 18);
    // this is a bit of a hack assuming all data fields are aligned
    al = *(di + 15);
    si = (uint8_t *) ctx;
    cx = 16;
    do {
        al = s[*si ^ al];
        al ^= *di;
        *di = al;
        di++;
        si++;
        cx--;
    } while (cx);
}
