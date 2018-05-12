//
// Created by mayfa on 8.5.18.
//

#include "response_parser.hpp"
#include <cstdlib>

namespace http {

/**
 *
 * @param buffer      ... buffer to be parsed
 * @param buffer_size ... size of the buffer
 * @param response    ... pointer to an object that will be filled
 * @return false if parsing failed, true on success.
 */
bool ResponseParser::parse(const char *buffer, const size_t buffer_size, Response *response)
{
	CharStream char_stream(buffer, buffer_size);
}

/**
 * Parses whole status line
 * @param char_stream
 * @return status code in int
 */
bool ResponseParser::parseStatusLine(CharStream &char_stream, int *status_code)
{
    bool ret_val = true;
    char status_line[3][20];
    char_stream.readLine(status_line);

    // Convert status code into int.
    *status_code = std::atoi(status_line[1]);
    if (*status_code == 0) {
        ret_val = false;
    }
    return ret_val;
}

/**
 * Parses whole header.
 * @param char_stream
 * @param header
 * @return
 */
bool ResponseParser::parseHeader(CharStream &char_stream, Header *header)
{
    while (!char_stream.atEmptyLine()) {

    }
}

/**
 * Parses one line
 * @param header_option
 * @return
 */
bool ResponseParser::parseOptionLine(CharStream &char_stream, HeaderOption *header_option)
{
    char words[MAX_OPTION_WORDS_COUNT][MAX_OPTION_WORD_LEN];
    char_stream.readLine(words);
}

} // namespace http
