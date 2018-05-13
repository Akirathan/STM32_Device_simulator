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

bool CharStream::atEnd() const
{
    return bufferIdx >= bufferSize;
}

/**
 * Returns pointer to the rest of the buffer.
 * Used for getting body of HTTP message for example.
 *
 * @return pointer to the rest of the buffer
 */
const char * CharStream::getRestOfBuffer()
{
    return buffer + bufferIdx;
}

bool CharStream::atEmptyLine() const
{
    return atEndOfLine();
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

