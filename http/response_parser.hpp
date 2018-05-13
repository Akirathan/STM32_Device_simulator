//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_HTTP_MESSAGE_PARSER_HPP
#define HTTP_COMMUNICATOR_HTTP_MESSAGE_PARSER_HPP

#define HTTP_HEADER_MAX_OPTIONS    10

#include "response.hpp"
#include "header_option.hpp"
#include "header.hpp"
#include "char_stream.hpp"

namespace http {

class ResponseParser {
public:
    static bool parse(const char *buffer, const size_t buffer_size, Response *response);
private:
    static const size_t MAX_OPTION_WORD_LEN = 50;
    static bool parseStatusLine(CharStream &char_stream, int *status_code);
    static bool parseHeader(CharStream &char_stream, Header *header);
    static bool parseOptionLine(CharStream &char_stream, HeaderOption *header_option);
    static void resolveOptionType(const char *word, HeaderOption::Type *type);
    static char * trimWhiteSpaces(char *str);
};

} // namespace http

#endif //HTTP_COMMUNICATOR_HTTP_MESSAGE_PARSER_HPP
