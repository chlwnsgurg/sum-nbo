#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h> 
#define PRINT(x) printf("%u(0x%08x)", (x), (x))

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [<file2>...]\n", argv[0]);
        return 1;
    }

    uint32_t sum = 0;
    bool flag = true;

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            fprintf(stderr, "Error: cannot open file %s\n", argv[i]);
            return 1;
        }

        uint32_t tmp;

        size_t res = fread(&tmp, 1, 4, fp); fclose(fp);
        if (res != 4 ) {
            fprintf(stderr, "Error: file %s is too small\n", argv[i]);
            return 1;
        }

        uint32_t val = ntohl(tmp);

        if (flag){
            PRINT(val);
            flag=false;
        } else{
            printf(" + ");
            PRINT(val);
        }
        sum += val;
    }

    printf(" = ");
    PRINT(sum);
    printf("\n");

    return 0;
}
