#pragma once

#include <string>
#include <memory>

#include <yyltype.hpp>
#include <visitors/visitable.hpp>
#include <visitors/ivisitor.hpp>

#include <handlers/var_declaration.hpp>
#include <handlers/statements.hpp>
#include <handlers/method_body.hpp>

namespace ast {

class MethodDeclaration : public IVisitable {
public:
    MethodDeclaration(const std::string &privacy,
                const PType &type,
                const std::string &identifier,
                const std::vector<std::pair<PType, std::string>>& args,
                const PMethodBody &method_body,
                MC::YYLTYPE pos) :
        identifier_(identifier), args_(args), type_(type), method_body_(method_body),  \
        privacy_(privacy)
    {
        setPos(pos);
    }

    const PType &getType() const {
        return type_;
    }

    const std::vector<std::pair<PType, std::string>>& getArgs() const {
        return args_;
    }

    const std::string& getPrivacy() const {
        return privacy_;
    }

    const std::string& getIdentifier() const {
        return identifier_;
    }

    const PMethodBody& getMethodBody() const {
        return method_body_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    std::string identifier_;
    std::vector<std::pair<PType, std::string>> args_;
    PType type_;
    PMethodBody method_body_;
    std::string privacy_;

    void setPos(const MC::YYLTYPE pos) { pos_ = pos; }
};

typedef std::shared_ptr<MethodDeclaration> PMethodDeclaration;
}
