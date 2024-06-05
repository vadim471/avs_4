#include <stdio.h>

int main() {
    char szMessage[100000] = "Madam, I\'m Adam";
    // Madam, I
    // adam, I'
    // dam, I'm
    // ...
    // I'm Adam
    // 'm Adam0
    // ...
    // m0000000
    __asm__(
            "pop %%rbx\n\t"
            "mov %0, %%rax\n\t" //from to
            "start_f_cycle:\n\t"
            "cmpb $0, (%0)\n\t"
            "je end_f_cycle\n\t"
            "push (%0)\n\t"
            "inc %0\n\t"
            "jmp start_f_cycle\n\t"
            "end_f_cycle:\n\t"


            "mov %%rax, %0\n\t"

            "start_s_cycle:\n\t"
            "cmpb $0, (%%rax)\n\t"
            "je end_s_cycle\n\t"
            "pop %%rbx\n\t"
            "movb %%bl, (%%rax)\n\t"
            "inc %%rax\n\t"
            "jmp start_s_cycle\n\t"
            "end_s_cycle:\n\t"
            "push %%rbx"
            :
            :"r"(szMessage)
            :"%rax", "%al", "%rbx"
            );
    printf("%s", szMessage);
    return 0;
}
