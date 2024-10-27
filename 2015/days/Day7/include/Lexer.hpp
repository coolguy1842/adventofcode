#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <Includes.hpp>

#include <cctype>
#include <utils/StringUtils.hpp>

#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_set>
#include <vector>

enum TokenType {
    IDENTIFIER,
    KEYWORD,
    OPERATOR,
    LITERAL
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
private:
    bool isLiteral(std::string& str) {
        std::optional<DataType> result = AOCUtil::strtonumeric<DataType>(str.c_str(), true);
        return result.has_value();
    }

    bool isOperator(std::string& str) {
        std::unordered_set<std::string> operators = {
            "->",
            // gates
            "RSHIFT",
            "LSHIFT",
            "AND",
            "OR"
        };

        return operators.contains(str);
    }

    bool isKeyword(std::string& str) {
        std::unordered_set<std::string> keywords = {
            "NOT"
        };

        return keywords.contains(str);
    }

    bool isIdentifier(std::string& str) {
        for(char& c : str) {
            if(!std::isalpha(c)) {
                return false;
            }
        }

        return true;
    }

public:
    Lexer() {}

    std::optional<std::vector<Token>> analyse(std::string str) {
        std::vector<Token> out;

        for(std::string& str : AOCUtil::split(str, " ")) {
            if(isLiteral(str)) {
                out.push_back({ TokenType::LITERAL, str });
                continue;
            }

            if(isKeyword(str)) {
                out.push_back({ TokenType::KEYWORD, str });
                continue;
            }

            if(isOperator(str)) {
                out.push_back({ TokenType::OPERATOR, str });
                continue;
            }

            if(isIdentifier(str)) {
                out.push_back({ TokenType::IDENTIFIER, str });
                continue;
            }

            // unknown: invalid
            return std::nullopt;
        }

        return out;
    }
};

#endif