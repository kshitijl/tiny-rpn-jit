#include <sys/mman.h>
#include <unistd.h>

int main() {
    char msg[] = "Hello, World!\n";

    union Address {
        void *xx;
        struct YY {
            char a,b,c,d;
        } yy;
    } address;
    address.xx = (void *)&(msg[0]);
    
    char *m = (char *)mmap(0, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    int i = 0;
    m[i++] = 0xb8;
    m[i++] = 0x01;
    m[i++] = 0x00;
    m[i++] = 0x00;
    m[i++] = 0x00; // mov $0x1 %eax

    m[i++] = 0xbb;
    m[i++] = 0x01;
    m[i++] = 0x00;
    m[i++] = 0x00;
    m[i++] = 0x00; // mov 0x1,%ebx

    m[i++] = 0xcd;
    m[i++] = 0x80; // int 0x80
    
    m[i++] = 0xc3;

    int (*func)(void);
    func = (int (*)(void))m;

    int answer = func();

    write(1, &answer, 4);
    
    return 0;
}
