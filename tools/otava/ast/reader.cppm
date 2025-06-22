// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.reader;

import std;
import util;
import soul.ast.source.pos;
import otava.ast.node;

export namespace otava::ast {

class NodeMap;

class Reader
{
public:
    Reader(const std::string& fileName);
    Reader(util::BinaryStreamReader* readerPtr_);
    util::BinaryStreamReader& GetBinaryStreamReader() { return *readerPtr; }
    soul::ast::SourcePos ReadSourcePos();
    NodeKind ReadNodeKind();
    std::u32string ReadStr();
    bool ReadBool();
    Node* ReadNode();
    void SetNodeMap(NodeMap* nodeMap_) { nodeMap = nodeMap_; }
    NodeMap* GetNodeMap() const { return nodeMap; }
private:
    std::unique_ptr<util::FileStream> fileStream;
    std::unique_ptr<util::BufferedStream> bufferedStream;
    std::unique_ptr<util::BinaryStreamReader> binaryStreamReader;
    util::BinaryStreamReader* readerPtr;
    NodeMap* nodeMap;
};

} // namespace otava::ast
