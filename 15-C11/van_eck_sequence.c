#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    size_t log = 1;
    const size_t N = 10;
    size_t last_visited[1024 * 1024];
    for (int i = 0; i < (1024 * 2); i++)
        last_visited[i] = 0;

    size_t input_puzzle[] = {1,3,2};
    size_t len = (sizeof(input_puzzle) / sizeof(input_puzzle[0]));
    for (size_t i = 0; i < len; ++i) {
        last_visited[input_puzzle[i]] = i;
        fprintf(stdout, "%lu,", input_puzzle[i]);
    }

    size_t last = input_puzzle[len - 1]; // start knowing nothing before

    for (size_t turn = len; turn < N; ++turn) {
        if (log)
            fprintf(stdout, "\n>>>>>turn: %lu | last: %lu | last_visited[%lu] = %lu\n", turn, last, last, last_visited[last]);
        if (last == 0) {
            if (input_puzzle[0] ==  0) {
                last = turn - last_visited[0] - 1;
                last_visited[0] = turn - 1; // update last seen of zero
            } else {
                last = turn - last_visited[0] - 1;
                last_visited[0] = turn - 1;
            }
        }
        else {
            if (last_visited[last] == 0) {
                last_visited[last] = turn - 1;
                last = 0;
            } else {
                if (turn > len ) {
                    if (log)
                        fprintf(stdout, "\n!!!!!!turn: %lu | last: %lu | last_visited[%lu] = %lu\n", turn, last, last, last_visited[last]);
                    {
                        size_t tmp = last;
                        last = turn - last_visited[last] - 1;
                        last_visited[tmp] = turn - 1;
                    }
                    if (log)
                        fprintf(stdout, "~~~~~turn: %lu | last: %lu | last_visited[%lu] = %lu\n", turn, last, last, last_visited[last]);

                } else {
                    last = 0;
                    last_visited[0] = turn;
                }
            }
        }

        if (log)
            fprintf(stdout, "<<<<<turn: %lu | last: %lu | last_visited[%lu] = %lu\n", turn, last, last, last_visited[last]);

        if (log)
            fprintf(stdout, "%lu,", last);
    }

    fprintf(stdout, "\nSolution: %lu,", last);

    return 0;
}
