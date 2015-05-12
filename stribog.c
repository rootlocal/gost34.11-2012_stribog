/*
 * Copyright (c) 2013 by sftp
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * There's ABSOLUTELY NO WARRANTY, express or implied.
 */

#include <stdio.h>
#include <string.h>

#include "types.h"
#include "stribog.h"

void print_hash(struct stribog_ctx_t *ctx)
{
	u8 i;

	for (i = 0; i < (ctx->size ? OUTPUT_SIZE_512 : OUTPUT_SIZE_256); i++)
		printf("%02x", ctx->h[i]);

	putchar('\n');
}

int main(int argc, char *argv[])
{
	struct stribog_ctx_t ctx;

	u8 message1[63] = {
		0x32, 0x31, 0x30, 0x39, 0x38, 0x37, 0x36, 0x35,
		0x34, 0x33, 0x32, 0x31, 0x30, 0x39, 0x38, 0x37,
		0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x39,
		0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31,
		0x30, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33,
		0x32, 0x31, 0x30, 0x39, 0x38, 0x37, 0x36, 0x35,
		0x34, 0x33, 0x32, 0x31, 0x30, 0x39, 0x38, 0x37,
		0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30
	};

	u8 message2[72] = {
		0xfb, 0xe2, 0xe5, 0xf0, 0xee, 0xe3, 0xc8, 0x20,
		0xfb, 0xea, 0xfa, 0xeb, 0xef, 0x20, 0xff, 0xfb,
		0xf0, 0xe1, 0xe0, 0xf0, 0xf5, 0x20, 0xe0, 0xed,
		0x20, 0xe8, 0xec, 0xe0, 0xeb, 0xe5, 0xf0, 0xf2,
		0xf1, 0x20, 0xff, 0xf0, 0xee, 0xec, 0x20, 0xf1,
		0x20, 0xfa, 0xf2, 0xfe, 0xe5, 0xe2, 0x20, 0x2c,
		0xe8, 0xf6, 0xf3, 0xed, 0xe2, 0x20, 0xe8, 0xe6,
		0xee, 0xe1, 0xe8, 0xf0, 0xf2, 0xd1, 0x20, 0x2c,
		0xe8, 0xf0, 0xf2, 0xe5, 0xe2, 0x20, 0xe5, 0xd1
	};

	printf("Message 1:\n");

	init(&ctx, HASH512);
	stribog(&ctx, message1, sizeof(message1));

	printf("H^{512}: ");
	print_hash(&ctx);

	init(&ctx, HASH256);
	stribog(&ctx, message1, sizeof(message1));

	printf("H^{256}: ");
	print_hash(&ctx);

	printf("\nMessage 2:\n");

	init(&ctx, HASH512);
	stribog(&ctx, message2, sizeof(message2));

	printf("H^{512}: ");
	print_hash(&ctx);

	init(&ctx, HASH256);
	stribog(&ctx, message2, sizeof(message2));

	printf("H^{256}: ");
	print_hash(&ctx);

	return 0;
}
