// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.component;

import std;

export namespace util {

class Container;

class Component
{
public:
    Component();
    virtual ~Component();
    inline Container* GetContainer() const { return container; }
    inline void SetContainer(Container* container_) { container = container_; }
    inline Component* NextSibling() const { return nextSibling; }
    inline void SetNextSibling(Component* nextSibling_) { nextSibling = nextSibling_; }
    inline Component* PrevSibling() const { return prevSibling; }
    inline void SetPrevSibling(Component* prevSibling_) { prevSibling = prevSibling_; }
    void LinkBefore(Component* component)
    {
        if (prevSibling)
        {
            prevSibling->nextSibling = component;
        }
        component->prevSibling = prevSibling;
        component->nextSibling = this;
        prevSibling = component;
    }
    void LinkAfter(Component* component)
    {
        if (nextSibling)
        {
            nextSibling->prevSibling = component;
        }
        component->prevSibling = this;
        component->nextSibling = nextSibling;
        nextSibling = component;
    }
    void Unlink()
    {
        if (prevSibling)
        {
            prevSibling->nextSibling = nextSibling;
        }
        if (nextSibling)
        {
            nextSibling->prevSibling = prevSibling;
        }
    }
private:
    Container* container;
    Component* nextSibling;
    Component* prevSibling;
};

class Container
{
public:
    Container(Component* parent_);
    virtual ~Container();
    inline bool IsEmpty() const { return firstChild == nullptr; }
    inline Component* Parent() const { return parent; }
    inline Component* FirstChild() const { return firstChild; }
    inline Component* LastChild() const { return lastChild; }
    void AddChild(Component* child);
    std::unique_ptr<Component> RemoveChild(Component* child);
    void InsertBefore(Component* child, Component* before);
    void InsertAfter(Component* child, Component* after);
private:
    Component* parent;
    Component* firstChild;
    Component* lastChild;
};

} // namespace util
