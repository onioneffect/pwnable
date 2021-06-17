#include <stdio.h>

void printer_func(char *buf) {
	int i = 0, l;
	FILE *fp = fopen("payload.bin", "wb");

	// 0xdeadbeef should become 0xcafebabe
	char substitutions[2][4] = {
		{0xde, 0xad, 0xbe, 0xef},
		{0xca, 0xfe, 0xba, 0xbe}
	};

	while(i < 128) {
		for(int j = 0; j < 4; j++) {
			if(substitutions[0][j] == buf[i] & 0xff) {
				*(buf + i) = substitutions[1][j];
			}
		}

		l = buf[i];

		if(i <= 0xf) {
			printf("[0x0%x] %x\t%c", i, l & 0xff, l);
		} else {
			printf("[0x%x] %x\t%c", i, l & 0xff, l);
		}

		putc(l, fp);
		putchar('\n');
		++i;
	}

	putc('\n', fp);
	putc('\n', fp);
	fclose(fp);
}

void buffer_func(char *start) {
	char payload_buffer[128];
	int i = 0;

	while(i < 128) {
		payload_buffer[i++] = *(start + i);
	}

	printer_func(payload_buffer);
}

void func(int key) {
	char overflowme[32];
	printf("overflow me : ");
	gets(overflowme);	// smash me!

	if(key == 0xcafebabe) {
		puts("Here's your flag!");
	} else {
		printf("Nah..\n");
	}

	buffer_func(overflowme);
}

int main(int argc, char **argv) {
	func(0xdeadbeef);
	return 0;
}

