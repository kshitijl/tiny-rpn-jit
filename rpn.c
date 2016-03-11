#include <sys/mman.h>
#include <unistd.h>

#include <stdio.h>

#include <assert.h>

int push_number(int number, char *m) {
    union Num {
        int x;
        char c[4];
    } num;
    assert(sizeof(num) == sizeof(int));
    
    num.x = number;

    int i = 0;
    m[i++] = 0x48;
    m[i++] = 0xc7;
    m[i++] = 0xc0;
    m[i++] = num.c[0];
    m[i++] = num.c[1];
    m[i++] = num.c[2];
    m[i++] = num.c[3]; // mov $num,%rax

    m[i++] = 0x50; // push %rax

    return i;
}

int return_top_of_stack(char *m) {
    int i = 0;
    m[i++] = 0x58;
    m[i++] = 0xc3;
}

int main() {
    char *m = (char *)mmap(0, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    char * original_m = m;
    
    m += push_number(200, m);
    m += return_top_of_stack(m);

    int (*func)(void);
    func = (int (*)(void))original_m;

    int answer = func();

    printf("%d\n", answer);

    return 0;
}
