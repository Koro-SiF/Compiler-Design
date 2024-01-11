#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <vector>

enum class TokenType {
    ID,        // "id"
    ASSIGN,    // ":="
    INTEGER,   // "integer"
    STAR,      // "*"
    SLASH,     // "/"
    SEMICOLON, // ";"
    END,
    INVALID
};

struct Token {
    TokenType type;
    std::string lexeme;
};

class Lexer {
private:
    std::string::const_iterator currentChar;
    const std::string::const_iterator end;
    std::string source;

    char getNextChar() {
        return currentChar != end ? *currentChar++ : '\0';
    }

    void putBackChar() {
        if (currentChar != end) --currentChar;
    }

    Token identifierOrKeyword() {
        std::string value;
        while (currentChar != end && (std::isalpha(*currentChar) || *currentChar == '_')) {
            value += *currentChar;
            ++currentChar;
        }

        if (value == "id") return {TokenType::ID, value};
        if (value == "integer") return {TokenType::INTEGER, value};

        return {TokenType::INVALID, value};
    }

public:
    explicit Lexer(const std::string &src) : source(src), currentChar(src.begin()), end(src.end()) {}

    Token getNextToken() {
        while (currentChar != end && std::isspace(*currentChar)) {
            ++currentChar; // Skip whitespace
        }

        if (currentChar == end) {
            return {TokenType::END, ""};
        }

        char ch = getNextChar();

        if (std::isalpha(ch)) {
            putBackChar();
            return identifierOrKeyword();
        }

        switch (ch) {
            case ':':
                if (getNextChar() == '=') {
                    return {TokenType::ASSIGN, ":="};
                }
                putBackChar();
                return {TokenType::INVALID, std::string(1, ch)};
            case '*':
                return {TokenType::STAR, "*"};
            case '/':
                return {TokenType::SLASH, "/"};
            case ';':
                return {TokenType::SEMICOLON, ";"};
        }

        return {TokenType::INVALID, std::string(1, ch)};
    }
};

class Parser {
private:
    Lexer lexer;
    Token currentToken;

    void consume(TokenType type) {
        if (currentToken.type == type) {
            currentToken = lexer.getNextToken();
        } else {
            throw std::runtime_error("Unexpected token: " + currentToken.lexeme);
        }
    }

    void P() {
        consume(TokenType::ID);
        consume(TokenType::ASSIGN);
        E();
        consume(TokenType::SEMICOLON);
    }

    void E() {
        T();
        E_prime();
    }

    void E_prime() {
        if (currentToken.type == TokenType::STAR || currentToken.type == TokenType::SLASH) {
            O();
            T();
            E_prime();
        }
        // If currentToken is not STAR or SLASH, it's epsilon transition, do nothing
    }

    void T() {
        if (currentToken.type == TokenType::ID || currentToken.type == TokenType::INTEGER) {
            if (currentToken.type == TokenType::ID) {
                consume(TokenType::ID);
            } else {
                consume(TokenType::INTEGER);
            }
        } else {
            throw std::runtime_error("Unexpected token: " + currentToken.lexeme);
        }
    }

    void O() {
        if (currentToken.type == TokenType::STAR) {
            consume(TokenType::STAR);
        } else if (currentToken.type == TokenType::SLASH) {
            consume(TokenType::SLASH);
        } else {
            throw std::runtime_error("Unexpected token: " + currentToken.lexeme);
        }
    }

public:
    explicit Parser(const std::string &source) : lexer(Lexer(source)) {
        currentToken = lexer.getNextToken();
    }

    void parse() {
        P();
        if (currentToken.type != TokenType::END) {
            throw std::runtime_error("Unexpected token at end: " + currentToken.lexeme);
        }
    }
};

int main() {
    std::string input;
    while(true) {
        std::cout << "Enter an expression to parse: ";
        std::getline(std::cin, input);

        if(input == "exit") return false;

        Parser parser(input);

        try {
            parser.parse();
            std::cout << "Accept" << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Parsing error: " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}