int main() {
    char opcode = 0xc3;
    void (*func)(void);

    func = (void (*)(void))(&opcode);
    func();
    return 0;
}
