#include <cstddef>

template <size_t rows, size_t cols>
void fill_words(char (&words)[rows][cols])
{
    for (int i = 0; i < 5; ++i) {
        words[0][i] = 'a';
    }
    for (int i = 0; i < 5; ++i) {
        words[1][i] = 'b';
    }
    for (int i = 0; i < 5; ++i) {
        words[2][i] = 'c';
    }
}

int main()
{
    char words[3][5];
    fill_words(words);
}