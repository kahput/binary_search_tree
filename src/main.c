#include "bst.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	InitWindow(1280, 720, "BST");

	BST* bst = bst_init();

	srand(time(0));
	printf("VALUES: ");
	for (int i = 0; i < 5; i++) {
		uint32_t value = rand() % 10;
		bst_add(bst, value);
		printf("%d ", value);
	}
	printf("\n");
	bst_print(bst);

	while (!WindowShouldClose()) {
		ClearBackground(RAYWHITE);
		BeginDrawing();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
