#include <stdio.h>
#include <stdint.h>
#include "nbo.h"

// 숫자를 "십진수(0x헥스)" 형식으로 출력하는 헬퍼 함수
void printNumber(uint32_t val) {
    // 값이 16비트 이하인 경우 4자리 헥스(앞에 0 채움), 그 이상이면 기본 헥스 출력
    if (val < 0x10000)
         printf("%u(0x%04x)", val, val);
    else
         printf("%u(0x%x)", val, val);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [<file2>...]\n", argv[0]);
        return 1;
    }

    uint32_t sum = 0;
    bool first = true;

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (!fp) {
            fprintf(stderr, "Error: cannot open file %s\n", argv[i]);
            return 1;
        }

        uint32_t net_val;
        size_t bytesRead = fread(&net_val, 1, 4, fp);
        fclose(fp);

        if (bytesRead != 4) {
            fprintf(stderr, "Error: file %s is too small\n", argv[i]);
            return 1;
        }

        uint32_t host_val = nboToHbo(net_val);

        if (!first)
            printf(" + ");
        printNumber(host_val);

        sum += host_val;
        first = false;
    }

    printf(" = ");
    printNumber(sum);
    printf("\n");

    return 0;
}
