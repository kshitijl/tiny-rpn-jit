#include <sys/mman.h>
#include <unistd.h>

int main() {
    char *memory = (char *)mmap(0, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memory[0] = 0xb8;
    memory[1] = 0x70;
    memory[2] = 0x6f;
    memory[3] = 0x6f;
    memory[4] = 0x70;
    memory[5] = 0xc3;

    int (*func)(void);
    func = (int (*)(void))memory;

    int answer = func();

    write(1, &answer, 4);
    
    return 0;
}
