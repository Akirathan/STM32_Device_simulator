//
// Created by mayfa on 11.5.18.
//

#include "char_stream.hpp"
#include <cstring>

CharStream::CharStream(const char *buffer, const size_t buffer_size) :
    buffer(buffer),
    bufferSize(buffer_size),
    bufferIdx(0)
{}

char CharStream::readChar()
{
    if (bufferIdx >= bufferSize) {
        return '\0';
    }
    return buffer[bufferIdx++];
}

/**
 * Reads one word
 * @param word     ... string where read word will be stored
 * @param word_len ... may be nullptr, otherwise length of read word is assigned.
 */
void CharStream::readWord(char *word, size_t *word_len)
{
    char c = '\0';
    unsigned long wordIdx = 0;
    while (!isWhiteSpace(c)) {
        c = readChar();
        word[wordIdx++] = c;
    }
    unreadChar();

    if (word_len != nullptr) {
        *word_len = wordIdx;
    }
}

void CharStream::readWhiteSpaces()
{
    char c = '\0';
    while (isWhiteSpace(c)) {
        c = readChar();
    }
    unreadChar();
}

/**
 * In case when there are more words on line than @param strings_len, fill whole
 * @param strings buffer and ignore rest of the line (just move the read head).
 *
 * @note line delimiter is \r\n
 * @param strings      ... buffer for words on line
 * @param strings_len  ... length of the @param strings buffer
 * @param max_word_len ... max length of a word in the line
 */
template<size_t strings_len, size_t max_word_len>
void CharStream::readLine(char (&strings)[strings_len][max_word_len])
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
            word_idx++;
        }
    }
    // Read "\r\n"
    bufferIdx += 2;
}

bool CharStream::atEnd() const
{
    return bufferIdx >= bufferSize;
}

bool CharStream::isWhiteSpace(char c) const
{
    return c == '\r' || c == '\n' || c == ' ' || c == '\t';
}

void CharStream::unreadChar()
{
    bufferIdx--;
}

bool CharStream::atEndOfLine() const
{
    return buffer[bufferIdx] == '\r' && buffer[bufferIdx + 1] == '\n';
}

