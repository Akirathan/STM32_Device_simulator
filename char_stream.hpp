//
// Created by mayfa on 11.5.18.
//

#ifndef DEVICE_SIMULATOR_CHAR_STREAM_HPP
#define DEVICE_SIMULATOR_CHAR_STREAM_HPP

#include <cstddef>
#include <cstring>

/**
 * This class is wrapper for C string and provides "stream" methods.
 *
 * @note line delimiter is considered to be \r\n (just like in HTTP).
 */
class CharStream {
public:
	CharStream(const char *buffer, const size_t buffer_size);
	char readChar();
	void readWord(char *word, size_t *word_len);
	void readWhiteSpaces();

    /**
     * In case when there are more words on line than strings_len, fill whole
     * strings buffer and ignore rest of the line (just move the read head).
     *
     * @note line delimiter is @code \r\n @endcode
     * @param strings      ... buffer for words on line
     * @param strings_len  ... length of the @param strings buffer
     * @param max_word_len ... max length of a word in the line
     * @param word_count   ... may be nullptr
     */
    template <size_t strings_len, size_t max_word_len>
    void readLine(char (&strings)[strings_len][max_word_len], size_t *word_count)
    {
        size_t word_idx = 0;
        while (!atEndOfLine()) {
            readWhiteSpaces();

            char word[max_word_len];
            size_t word_len = 0;
            readWord(word, &word_len);
            // Copy word into buffer when there is space.
            if (word_idx < strings_len) {
                std::memcpy(strings[word_idx], word, word_len);
            }
            word_idx++;
        }
        if (word_count != nullptr) {
            *word_count = word_idx;
        }
        // Read "\r\n"
        bufferIdx += 2;
    };

	const char * getRestOfBuffer();
	bool atEnd() const;
    bool atEmptyLine() const;

private:
	const char *buffer;
	const size_t bufferSize;
	unsigned long bufferIdx;
    bool isWhiteSpace(char c) const;
    void unreadChar();
    bool atEndOfLine() const;
};

#endif //DEVICE_SIMULATOR_CHAR_STREAM_HPP
