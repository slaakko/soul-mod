export module otava.ast.output;

import std;
import otava.ast.node;

export namespace otava::ast {

void PrintSource(Node& node, std::ostream& stream);
void PrintXml(Node& node, std::ostream& stream);

} // namespace otava::ast
