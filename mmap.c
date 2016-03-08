#include <sys/mman.h>
#include <unistd.h>

int main() {
    char *memory = (char *)mmap(0, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memory[0] = 0xc3;

    void (*func)(void);
    func = (void (*)(void))memory;

    func();
    return 0;
}
