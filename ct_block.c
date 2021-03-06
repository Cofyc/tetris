#include "ct_block.h"

int cur_x = 0;
int cur_y = 0;

struct block *cur_b = NULL;
int cur_type, cur_shape;
struct block *next_b = NULL;
int next_type, next_shape;

struct block blocks[7][4] = {
    /*
     * ----------
     * |        |
     * |  [][]  |
     * |  [][]  |
     * |        |
     * ----------
     */
    {
     {
      {
       {0, 0, 0, 0},
       {0, 0x81, 0x81, 0},
       {0, 0x81, 0x81, 0},
       {0, 0, 0, 0}
       },
      1,                        // x_min
      2,                        // x_max
      1,                        // y_min
      2},                       // y_max
     },
    /*
     * ----------
     * |        |
     * |[][][]  |
     * |  []    |
     * |        |
     * ----------
     */
    {
     {
      {
       {0, 0, 0, 0},
       {0x82, 0x82, 0x82, 0},
       {0, 0x82, 0, 0},
       {0, 0, 0, 0},
       },
      0,
      2,
      1,
      2},
     //
     },
    /*
     * ----------
     * |        |
     * |[][]    |
     * |  [][]  |
     * |        |
     * ----------
     */
    {
     {
      {
       {0, 0, 0, 0},
       {0x83, 0x83, 0, 0},
       {0, 0x83, 0x83, 0},
       {0, 0, 0, 0},
       },
      0,
      2,
      1,
      2},
     },
    /*
     * ----------
     * |        |
     * |  [][]  |
     * |[][]    |
     * |        |
     * ----------
     */
    {
     {
      {
       {0, 0, 0, 0},
       {0, 0x84, 0x84, 0},
       {0x84, 0x84, 0, 0},
       {0, 0, 0, 0},
       },
      0,
      2,
      1,
      2},
     },
    /*
     * ----------
     * |        |
     * |[][][]  |
     * |    []  |
     * |        |
     * ----------
     */
    {
     {
      {
       {0, 0, 0, 0},
       {0x85, 0x85, 0x85, 0},
       {0, 0, 0x85, 0},
       {0, 0, 0, 0},
       },
      0,
      2,
      1,
      2},
     },
    /*
     * ----------
     * |        |
     * |[][][]  |
     * |[]      |
     * |        |
     * ----------
     */
    {
     {
      {
       {0, 0, 0, 0},
       {0x86, 0x86, 0x86, 0},
       {0x86, 0, 0, 0},
       {0, 0, 0, 0},
       },
      0,
      2,
      1,
      2},
     },
    /*
     * ----------
     * |        |
     * |[][][][]|
     * |        |
     * |        |
     * ----------
     */
    {
     {
      {
       {0, 0, 0, 0},
       {0x87, 0x87, 0x87, 0x87},
       {0, 0, 0, 0},
       {0, 0, 0, 0},
       },
      0,
      3,
      1,
      1,
      }
     },
};

static void block_rotate(struct block *to, struct block *from);

int
ct_block_init()
{
    int i, j;

    for (i = 0; i < 7; i++) {
        for (j = 1; j < 4; j++) {
            block_rotate(&blocks[i][j], &blocks[i][j - 1]);
        }
    }
    return 0;
}

/**
 *
 * 90" clockwise rotator
 *
 * y axis -> x axis
 * x axis -> reverse of x axis
 */
static void
block_rotate(struct block *to, struct block *from)
{
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            to->show[i][j] = from->show[4 - 1 - j][i];
        }
    }

    to->x_min = 4 - 1 - from->y_max;

    to->x_max = 4 - 1 - from->y_min;
    to->y_min = from->x_min;
    to->y_max = from->x_max;
}

int
ct_rand()
{
    static int is_seeded = false;

    if (!is_seeded) {
        srand(((long)(time(0) * getpid())));
        is_seeded = true;
    }

    return rand();
}

struct block *
ct_block_get(int type, int shape)
{
    return &blocks[type][shape];
}
