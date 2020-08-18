#define E(p) (p + sizeof p)

int m[12] = {
    0110, 0145, 0154, 0154, 0157, 0040,
    0167, 0157, 0162, 0154, 0144, 0012
};

int main()
{
    int *p = m, *e = E(m);
    while (p < e)
        putchar(*p++);
}
