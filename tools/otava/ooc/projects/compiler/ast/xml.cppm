export module otava.ast.xml;

import std;

export namespace otava::ast {

class Node;
void WriteXml(Node* node, const std::string& filePath);

} // namespace otava::ast
