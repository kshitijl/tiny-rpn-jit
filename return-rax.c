#include <sys/mman.h>
#include <unistd.h>

#include <stdio.h>

int main() {
    char *memory = (char *)mmap(0, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memory[0] = 0xc3;

    int (*func)(void);
    func = (int (*)(void))memory;

    int answer = func();
    printf("%d %d\n", answer, (int)(memory));
    return 0;
}
