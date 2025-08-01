// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.processor.entity;

import std;
import soul_expected.ast.source.pos;

export namespace soul_expected::xml::processor {

enum class EntityKind
{
    internalEntity, externalEntity
};

class Entity
{
public:
    Entity(EntityKind kind_, const std::string& name_);
    virtual ~Entity();
    inline EntityKind Kind() const { return kind; }
    inline const std::string& Name() const { return name; }
    virtual const std::u32string& Value() const = 0;
    inline bool IsInternal() const { return kind == EntityKind::internalEntity; }
    inline bool IsExternal() const { return kind == EntityKind::externalEntity; }
private:
    EntityKind kind;
    std::string name;
};

class InternalEntity : public Entity
{
public:
    InternalEntity(const std::string& name_, const std::u32string& value_);
    virtual const std::u32string& Value() const override { return value; }
private:
    std::u32string value;
};

class Entities
{
public:
    static Entities& Instance();
    Entities();
    void AddEntity(Entity* entity);
    Entity* GetEntity(const std::string& entityName) const;
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::map<std::string, Entity*> entityMap;
};

} // namespace soul_expected::xml::processor
