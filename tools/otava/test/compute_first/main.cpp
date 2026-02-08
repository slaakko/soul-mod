import std;
import util;

class Token
{
public:
    Token(std::int64_t id_, const std::string& name_, const std::string& info_);
    Token(const std::string& name_, const std::string& info_);
    //inline void SetCollection(Collection* collection_) noexcept { collection = collection_; }
    //inline Collection* GetCollection() const noexcept { return collection; }
    inline std::int64_t Id() const noexcept { return id; }
    inline void SetId(std::int64_t id_) noexcept { id = id_; }
    inline const std::string& Name() const noexcept { return name; }
    inline const std::string& Info() const noexcept { return info; }
    inline bool IsAny() const noexcept { return id == -1; }
    inline bool IsEpsilon() const noexcept { return id == -2; }
    std::string FullName() const;
    std::string FullCppId() const;
    Token* Clone() const;
private:
    std::int64_t id;
    std::string name;
    std::string info;
    //Collection* collection;
};

Token::Token(std::int64_t id_, const std::string& name_, const std::string& info_) : id(id_), name(name_), info(info_)//, collection(nullptr)
{
}

Token::Token(const std::string& name_, const std::string& info_) : id(-1), name(name_), info(info_)//, collection(nullptr)
{
}

Token* Token::Clone() const
{
    Token* clone = new Token(id, name, info);
    return clone;
}

std::string Token::FullName() const
{
    //Collection* collection = GetCollection();
    //if (collection)
    //{
        //return collection->Name() + "." + Name();
    //}
    //else
    //{
        return Name();
    //}
}

std::string Token::FullCppId() const
{
    std::string fullCppId;
    std::vector<std::string> components = util::Split(FullName(), '.');
    bool first = true;
    for (const std::string& component : components)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            fullCppId.append("::");
        }
        fullCppId.append(component);
    }
    return fullCppId;
}

struct TokenIdLess
{
    inline bool operator()(const Token* left, const Token* right) const noexcept
    {
        return left->Id() < right->Id();
    }
};

class TokenSet
{
public:
    TokenSet();
    bool AddToken(const Token* token);
    bool Merge(const TokenSet& that);
    bool Contains(const Token* token) const noexcept;
    bool Intersects(const TokenSet& that) const noexcept;
    std::string ToString() const;
    inline const std::set<const Token*, TokenIdLess>& Tokens() const noexcept { return tokens; }
private:
    std::set<const Token*, TokenIdLess> tokens;
};

TokenSet::TokenSet()
{
}

bool TokenSet::AddToken(const Token* token)
{
    auto it = tokens.find(token);
    if (it != tokens.end())
    {
        return false;
    }
    else
    {
        tokens.insert(token);
        return true;
    }
}

bool TokenSet::Merge(const TokenSet& that)
{
    bool changed = false;
    for (const auto* token : that.tokens)
    {
        if (AddToken(token))
        {
            changed = true;
        }
    }
    return changed;
}

bool TokenSet::Contains(const Token* token) const noexcept
{
    return tokens.find(token) != tokens.end();
}

bool TokenSet::Intersects(const TokenSet& that) const noexcept
{
    for (const auto* token : that.tokens)
    {
        if (Contains(token))
        {
            return true;
        }
    }
    return false;
}

std::string TokenSet::ToString() const
{
    std::string set("{");
    bool first = true;
    for (const auto* token : tokens)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            set.append(", ");
        }
        set.append(token->Name());
    }
    set.append("}");
    return set;
}

class Parser
{
public:
    Parser();
    inline const TokenSet& First() const noexcept { return first; }
    inline TokenSet& First() noexcept { return first; }
    virtual void ComputeFirst(bool& changed, std::set<Parser*>& visited) = 0;
private:
    TokenSet first;
};

Parser::Parser()
{
}

class UnaryParser : public Parser
{
public:
    UnaryParser();
    void ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
private:
    std::unique_ptr<Parser> child;
};

UnaryParser::UnaryParser() : Parser()
{
}

void UnaryParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    visited.insert(this);
}

int main()
{
    std::set<Parser*> visited;
    Parser* parser = new UnaryParser();
    bool changed = false;
    parser->ComputeFirst(changed, visited);
}
