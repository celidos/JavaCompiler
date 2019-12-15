#include <vector>
#include <string>

#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif // _!defined (yyFlexLexerOnce)


class Token {
private:
    const std::string left_str_ = "token: left_bound: ";
    const std::string right_str_ = ", right_bound: ";
    const std::string token_str_ = ", token: ";
    int left_bound_;
    int right_bound_;
    std::string token_value_;
public:
    Token();
    Token(int left_bound, int right_bound, const std::string& token);

    const int get_left_bound();
    const int get_right_bound();
    const std::string& token();
    bool operator == (const Token& other) const;
    const std::string get_string_presentation_of_token() const;
    void print() const;
    bool operator == (const std::string& other) const;
};


class MiniScanner : public yyFlexLexer {
private:
    std::vector<Token> tokens; // Координаты начала и конца токена в строке.
    virtual int yylex();
    int handleToken(const std::string &token, int& lexem_iterator); //Обработчик токена
public:
    int tokenize();
};
