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
    inline util::BinaryStreamReader& GetBinaryStreamReader() { return *readerPtr; }
    std::expected<soul::ast::SourcePos, int> ReadSourcePos();
    std::expected<NodeKind, int> ReadNodeKind();
    std::expected<std::u32string, int> ReadStr();
    std::expected<bool, int> ReadBool();
    std::expected<Node*, int> ReadNode();
    inline void SetNodeMap(NodeMap* nodeMap_) { nodeMap = nodeMap_; }
    inline NodeMap* GetNodeMap() const { return nodeMap; }
private:
    std::unique_ptr<util::FileStream> fileStream;
    std::unique_ptr<util::BufferedStream> bufferedStream;
    std::unique_ptr<util::BinaryStreamReader> binaryStreamReader;
    util::BinaryStreamReader* readerPtr;
    NodeMap* nodeMap;
};

} // namespace otava::ast
