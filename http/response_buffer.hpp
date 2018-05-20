//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTP_MESSAGE_PARSER_HPP
#define HTTP_COMMUNICATOR_HTTP_MESSAGE_PARSER_HPP

#include <cstdint>
#include "response.hpp"
#include "header_option.hpp"
#include "header.hpp"
#include "char_stream.hpp"

namespace http {

class ResponseBuffer {
public:
    static void init();
    static void buff(const uint8_t *part_buff, const size_t part_buff_size);
    static void awaitBody();
private:
    static const size_t MAX_OPTION_WORD_LEN = 50;
    static const size_t BUFF_LEN = 1500;

    static char buffer[BUFF_LEN];
    static size_t bufferIdx;
    /**
     * Awaiting body from server ie. message that contains just header is considered invalid.
     */
    static bool awaitBodyFlag;

    static bool parse(const char *buffer, const size_t buffer_size, Response *response);
    static bool parseStatusLine(CharStream &char_stream, int *status_code);
    static bool parseHeader(CharStream &char_stream, Header *header);
    static bool parseOptionLine(CharStream &char_stream, HeaderOption *header_option);
    static void resolveOptionType(const char *word, HeaderOption::Type *type);
    static char * trimWhiteSpaces(char *str);
    static void reset();
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTP_MESSAGE_PARSER_HPP
