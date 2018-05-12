//
// Created by mayfa on 11.5.18.
//

#ifndef DEVICE_SIMULATOR_CHAR_STREAM_HPP
#define DEVICE_SIMULATOR_CHAR_STREAM_HPP

#include <cstddef>

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
    template <size_t strings_len, size_t max_word_len>
    void readLine(char (&strings)[strings_len][max_word_len], size_t *word_count);
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
