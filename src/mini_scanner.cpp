#include <iostream>
#include <string>

#include "mini_scanner.h"

using std::cin;
using std::endl;
using std::cout;

Token::Token(): left_bound_(0), right_bound_(0), token_value_(""){}
Token::Token(int left_bound, int right_bound, const std::string& token):
        left_bound_(left_bound),
        right_bound_(right_bound),
        token_value_(token) {
}
const int Token::get_left_bound() {
    return left_bound_;
}
const int Token::get_right_bound() {
    return right_bound_;
}
const std::string& Token::token() {
    return token_value_;
}
bool Token::operator == (const Token& other) const {
    return
            left_bound_ == other.left_bound_ &&
            right_bound_ == other.right_bound_ &&
            token_value_ == other.token_value_;
}
const std::string Token::get_string_presentation_of_token() const {
    std::string ans =
            left_str_ + std::to_string(left_bound_) +
            right_str_ + std::to_string(right_bound_) +
            token_str_ + token_value_;
    return ans;
}
void Token::print() const {
    std::cout << get_string_presentation_of_token() <<"\n";
}
bool Token::operator == (const std::string& other) const {
    return get_string_presentation_of_token() == other;
}

// -------------------------------------------------------

int MiniScanner::handleToken(const std::string& token_value, int& curr_ind)
{
    int left = curr_ind;
    curr_ind += yyleng;
    if (token_value == "") {
        return 0;
    }
    Token curr_token(left, curr_ind, token_value);
    tokens.push_back(curr_token);
    return 0;
}

int MiniScanner::tokenize()
{
    yylex();
    for (const auto& token : tokens) {
        token.print();
    }
    return 0;
}