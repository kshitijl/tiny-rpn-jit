#include <sys/mman.h>
#include <unistd.h>

#include <stdio.h>

int main() {
    char *m = (char *)mmap(0, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    int i = 0;
    m[i++] = 0x89;
    m[i++] = 0xf8; // mov edi,eax

    //a:   83 c0 0a                add    $0xa,%eax
    m[i++] = 0x83;
    m[i++] = 0xc0;
    m[i++] = 0x0a;

    m[i++] = 0xc3;

    int (*func)(int);
    func = (int (*)(int))m;

    int answer = func(20);

    printf("%d\n", answer);

    return 0;
}
