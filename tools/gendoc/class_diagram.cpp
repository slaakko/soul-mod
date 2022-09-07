// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.class_diagram;

import util.code.formatter;
import soul.lexer.xml.parsing.log;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.specialization;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.modules;
import util.unicode;
import util.path;
import util.code.formatter;

namespace gendoc {

void GenerateClassDiagramCode(util::CodeFormatter& formatter)
{
    formatter.WriteLine("// JavaScript source code for drawing class inheritance diagrams");
    formatter.WriteLine();

    formatter.WriteLine("function pick(level, classes) {");
    formatter.IncIndent();
    formatter.WriteLine("var levelClasses = [];");
    formatter.WriteLine("var n = classes.length;");
    formatter.WriteLine("for (var i = 0; i < n; ++i) {");
    formatter.IncIndent();
    formatter.WriteLine("var c = classes[i];");
    formatter.WriteLine("if (c.level == level) {");
    formatter.IncIndent();
    formatter.WriteLine("levelClasses.push(c);");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("return levelClasses;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine("function createClassElements(levelClasses, maxTextWidth, maxTextHeight) {");
    formatter.IncIndent();
    formatter.WriteLine("var textDimensions = { width: maxTextWidth, height: maxTextHeight };");
    formatter.WriteLine("var n = levelClasses.length;");
    formatter.WriteLine("for (var i = 0; i < n; ++i) {");
    formatter.IncIndent();
    formatter.WriteLine("var levelClass = levelClasses[i];");
    formatter.WriteLine("var svg = document.getElementById(\"classDiagram\");");
    formatter.WriteLine("var rectElement = document.createElementNS('http://www.w3.org/2000/svg', 'rect');");
    formatter.WriteLine("rectElement.setAttribute(\"id\", levelClass.id + \"_rect\");");
    formatter.WriteLine("var linkElement = document.createElementNS('http://www.w3.org/2000/svg', 'a');");
    formatter.WriteLine("linkElement.setAttribute(\"href\", levelClass.link);");
    formatter.WriteLine("var textElement = document.createElementNS('http://www.w3.org/2000/svg', 'text');");
    formatter.WriteLine("linkElement.appendChild(textElement);");
    formatter.WriteLine("textElement.setAttribute(\"id\", levelClass.id + \"_text\");");
    formatter.WriteLine("textElement.innerHTML = levelClass.name;");
    formatter.WriteLine("svg.appendChild(rectElement);");
    formatter.WriteLine("svg.appendChild(linkElement);");
    formatter.WriteLine("var bb = textElement.getBBox();");
    formatter.WriteLine("var textWidth = bb.width;");
    formatter.WriteLine("var textHeight = bb.height;");
    formatter.WriteLine("levelClass.textWidth = textWidth;");
    formatter.WriteLine("levelClass.textHeight = textHeight;");
    formatter.WriteLine("if (textWidth > textDimensions.width) {");
    formatter.IncIndent();
    formatter.WriteLine("textDimensions.width = textWidth;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("if (textHeight > textDimensions.height) {");
    formatter.IncIndent();
    formatter.WriteLine("textDimensions.height = textHeight;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("return textDimensions;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine("function drawDiagram(classes) {");
    formatter.IncIndent();
    formatter.WriteLine("var cont = true;");
    formatter.WriteLine("var level = 0;");
    formatter.WriteLine("var yspace = 8;");
    formatter.WriteLine("var xspace = 8;");
    formatter.WriteLine("var minRectWidth = 100;");
    formatter.WriteLine("var minRectHeight = 40;");
    formatter.WriteLine("var maxTextWidth = 0;");
    formatter.WriteLine("var maxTextHeight = 0;");
    formatter.WriteLine("var triangleHeight = 20;");
    formatter.WriteLine("var triangleWidth = 20;");
    formatter.WriteLine("var targetHandleHeight = 20;");
    formatter.WriteLine("var sourceHandleHeight = 40;");
    formatter.WriteLine("var rectXSpace = 20;");
    formatter.WriteLine("var horizontalRectYSpace = triangleHeight + targetHandleHeight + sourceHandleHeight;");
    formatter.WriteLine("var verticalRectYSpace = 20;");
    formatter.WriteLine("var derivedTriangleHeight = 8;");
    formatter.WriteLine("var derivedTriangleWidth = 8;");
    formatter.WriteLine("var widthThreshold = 1800;");
    formatter.WriteLine("var allLevelClasses = [];");
    formatter.WriteLine("while (cont) {");
    formatter.IncIndent();
    formatter.WriteLine("var levelClasses = pick(level, classes);");
    formatter.WriteLine("var n = levelClasses.length;");
    formatter.WriteLine("cont = n > 0;");
    formatter.WriteLine("if (cont) {");
    formatter.IncIndent();
    formatter.WriteLine("var textDimensions = createClassElements(levelClasses, maxTextWidth, maxTextHeight);");
    formatter.WriteLine("if (textDimensions.width > maxTextWidth) {");
    formatter.IncIndent();
    formatter.WriteLine("maxTextWidth = textDimensions.width;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("if (textDimensions.height > maxTextHeight) {");
    formatter.IncIndent();
    formatter.WriteLine("maxTextHeight = textDimensions.height;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("allLevelClasses.push(levelClasses);");
    formatter.WriteLine("++level;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("var maxLevel = level;");
    formatter.WriteLine("var rectWidth = Math.max(minRectWidth, maxTextWidth + 2 * xspace);");
    formatter.WriteLine("var rectHeight = Math.max(minRectHeight, maxTextHeight + 2 * yspace);");
    formatter.WriteLine("var totalWidth = 0;");
    formatter.WriteLine("var totalHeight = 0;");
    formatter.WriteLine("var horizontalDirection = 0;");
    formatter.WriteLine("var verticalDirection = 1;");
    formatter.WriteLine("var levelDirection = [];");
    formatter.WriteLine("var levelHeight = [];");
    formatter.WriteLine("var prevW = 0;");
    formatter.WriteLine("for (level = 0; level < maxLevel; ++level) {");
    formatter.IncIndent();
    formatter.WriteLine("var levelClasses = allLevelClasses[level];");
    formatter.WriteLine("var n = levelClasses.length;");
    formatter.WriteLine("var w = n * (rectWidth + rectXSpace);");
    formatter.WriteLine("var h = rectHeight + horizontalRectYSpace;");
    formatter.WriteLine("if (w < widthThreshold) {");
    formatter.IncIndent();
    formatter.WriteLine("levelDirection.push(horizontalDirection);");
    formatter.WriteLine("if (w > totalWidth) {");
    formatter.IncIndent();
    formatter.WriteLine("totalWidth = w;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("else {");
    formatter.IncIndent();
    formatter.WriteLine("w = prevW + rectWidth + rectXSpace;");
    formatter.WriteLine("h = n * (rectHeight + verticalRectYSpace);");
    formatter.WriteLine("levelDirection.push(verticalDirection);");
    formatter.WriteLine("totalWidth += w;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("totalHeight += h;");
    formatter.WriteLine("levelHeight.push(h);");
    formatter.WriteLine("prevW = w;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("var svg = document.getElementById(\"classDiagram\");");
    formatter.WriteLine("svg.setAttribute(\"width\", totalWidth.toString());");
    formatter.WriteLine("svg.setAttribute(\"height\", totalHeight.toString());");
    formatter.WriteLine("var prevRectY = 0;");
    formatter.WriteLine("var prevRectX = 0;");
    formatter.WriteLine("var prevHandleX2 = -1;");
    formatter.WriteLine("var prevHandleY2 = -1;");
    formatter.WriteLine("var prevY = 0;");
    formatter.WriteLine("for (level = 0; level < maxLevel; ++level) {");
    formatter.IncIndent();
    formatter.WriteLine("var direction = levelDirection[level];");
    formatter.WriteLine("var levelClasses = allLevelClasses[level];");
    formatter.WriteLine("var n = levelClasses.length;");
    formatter.WriteLine("var rectY = prevY;");
    formatter.WriteLine("prevY += levelHeight[level];");
    formatter.WriteLine("var rectX = (totalWidth / n - rectWidth) / 2;");
    formatter.WriteLine("var minHandleX = Number.MAX_SAFE_INTEGER;");
    formatter.WriteLine("var maxHandleX = 0;");
    formatter.WriteLine("var handleY = 0;");
    formatter.WriteLine("for (var i = 0; i < n; ++i) {");
    formatter.IncIndent();
    formatter.WriteLine("var levelClass = levelClasses[i];");
    formatter.WriteLine("var textWidth = levelClass.textWidth;");
    formatter.WriteLine("var textHeight = levelClass.textHeight;");
    formatter.WriteLine("if (direction == horizontalDirection) {");
    formatter.IncIndent();
    formatter.WriteLine("rectX = (totalWidth / n - rectWidth) / 2 + i * (rectWidth + rectXSpace);");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("else if (direction == verticalDirection) {");
    formatter.IncIndent();
    formatter.WriteLine("rectX = prevRectX + (rectWidth + rectXSpace);");
    formatter.WriteLine("rectY = prevRectY + horizontalRectYSpace + i * (rectHeight + verticalRectYSpace);");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("var textX = rectX + (rectWidth - textWidth) / 2;");
    formatter.WriteLine("var textY = (rectY + rectHeight - yspace / 2) - (rectHeight - textHeight) / 2;");
    formatter.WriteLine("var rectElement = document.getElementById(levelClass.id + \"_rect\");");
    formatter.WriteLine("rectElement.setAttribute(\"x\", rectX.toString());");
    formatter.WriteLine("rectElement.setAttribute(\"y\", rectY.toString());");
    formatter.WriteLine("rectElement.setAttribute(\"width\", rectWidth.toString());");
    formatter.WriteLine("rectElement.setAttribute(\"height\", rectHeight.toString());");
    formatter.WriteLine("var fillColor = \"white\";");
    formatter.WriteLine("if (levelClass.subject) {");
    formatter.IncIndent();
    formatter.WriteLine("fillColor = \"floralWhite\";");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("rectElement.setAttribute(\"fill\", fillColor);");
    formatter.WriteLine("rectElement.setAttribute(\"stroke\", \"black\");");
    formatter.WriteLine("var textElement = document.getElementById(levelClass.id + \"_text\");");
    formatter.WriteLine("textElement.setAttribute(\"x\", textX.toString());");
    formatter.WriteLine("textElement.setAttribute(\"y\", textY.toString());");
    formatter.WriteLine("if (level < maxLevel - 1) {");
    formatter.IncIndent();
    formatter.WriteLine("var triangleElement = document.createElementNS('http://www.w3.org/2000/svg', 'polygon');");
    formatter.WriteLine("var tipX = rectX + rectWidth / 2;");
    formatter.WriteLine("var tipY = rectY + rectHeight;");
    formatter.WriteLine("var leftX = tipX - triangleWidth / 2;");
    formatter.WriteLine("var leftY = rectY + rectHeight + triangleHeight;");
    formatter.WriteLine("var rightX = tipX + triangleWidth / 2;");
    formatter.WriteLine("var rightY = rectY + rectHeight + triangleHeight;");
    formatter.WriteLine("triangleElement.setAttribute(\"points\",");
    formatter.IncIndent();
    formatter.WriteLine("tipX.toString() + \",\" + tipY.toString() + \" \" +");
    formatter.WriteLine("leftX.toString() + \",\" + leftY.toString() + \" \" +");
    formatter.WriteLine("rightX.toString() + \",\" + rightY.toString());");
    formatter.DecIndent();
    formatter.WriteLine("triangleElement.setAttribute(\"fill\", \"white\");");
    formatter.WriteLine("triangleElement.setAttribute(\"stroke\", \"black\");");
    formatter.WriteLine("svg.appendChild(triangleElement);");
    formatter.WriteLine("var targetHandleElement = document.createElementNS('http://www.w3.org/2000/svg', 'line');");
    formatter.WriteLine("var handleX1 = tipX;");
    formatter.WriteLine("var handleY1 = tipY + triangleHeight;");
    formatter.WriteLine("var handleX2 = tipX;");
    formatter.WriteLine("var handleY2 = tipY + triangleHeight + targetHandleHeight;");
    formatter.WriteLine("targetHandleElement.setAttribute(\"x1\", handleX1.toString());");
    formatter.WriteLine("targetHandleElement.setAttribute(\"y1\", handleY1.toString());");
    formatter.WriteLine("targetHandleElement.setAttribute(\"x2\", handleX2.toString());");
    formatter.WriteLine("targetHandleElement.setAttribute(\"y2\", handleY2.toString());");
    formatter.WriteLine("targetHandleElement.setAttribute(\"stroke\", \"black\");");
    formatter.WriteLine("svg.appendChild(targetHandleElement);");
    formatter.WriteLine("prevHandleX2 = handleX1;");
    formatter.WriteLine("prevHandleY2 = handleY1;");
    formatter.WriteLine("if (handleX1 < minHandleX) {");
    formatter.IncIndent();
    formatter.WriteLine("minHandleX = handleX1;");
    formatter.WriteLine("handleY = handleY2;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("if (handleX1 > maxHandleX) {");
    formatter.IncIndent();
    formatter.WriteLine("maxHandleX = handleX1;");
    formatter.WriteLine("handleY = handleY2;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.DecIndent();
    formatter.WriteLine("} else if (level == maxLevel - 1 && levelClass.hasDerivedClasses) {");
    formatter.IncIndent();
    formatter.WriteLine("var derivedTriangleElement = document.createElementNS('http://www.w3.org/2000/svg', 'polygon');");
    formatter.WriteLine("var cornerX = rectX + rectWidth;");
    formatter.WriteLine("var cornerY = rectY + rectHeight;");
    formatter.WriteLine("var verticalX = rectX + rectWidth;");
    formatter.WriteLine("var verticalY = rectY + rectHeight - derivedTriangleHeight;");
    formatter.WriteLine("var horizontalX = rectX + rectWidth - derivedTriangleWidth;");
    formatter.WriteLine("var horizontalY = rectY + rectHeight;");
    formatter.WriteLine("derivedTriangleElement.setAttribute(\"points\",");
    formatter.IncIndent();
    formatter.WriteLine("cornerX.toString() + \",\" + cornerY.toString() + \" \" +");
    formatter.WriteLine("verticalX.toString() + \",\" + verticalY.toString() + \" \" +");
    formatter.WriteLine("horizontalX.toString() + \",\" + horizontalY.toString());");
    formatter.DecIndent();
    formatter.WriteLine("derivedTriangleElement.setAttribute(\"fill\", \"black\");");
    formatter.WriteLine("svg.appendChild(derivedTriangleElement);");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("if (level > 0 && direction == horizontalDirection) {");
    formatter.IncIndent();
    formatter.WriteLine("var sourceHandleElement = document.createElementNS('http://www.w3.org/2000/svg', 'line');");
    formatter.WriteLine("var handleX1 = rectX + rectWidth / 2;");
    formatter.WriteLine("var handleY1 = rectY;");
    formatter.WriteLine("var handleX2 = rectX + rectWidth / 2;");
    formatter.WriteLine("var handleY2 = rectY - sourceHandleHeight;");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"x1\", handleX1.toString());");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"y1\", handleY1.toString());");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"x2\", handleX2.toString());");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"y2\", handleY2.toString());");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"stroke\", \"black\");");
    formatter.WriteLine("svg.appendChild(sourceHandleElement);");
    formatter.WriteLine("if (handleX1 < minHandleX) {");
    formatter.IncIndent();
    formatter.WriteLine("minHandleX = handleX1;");
    formatter.WriteLine("handleY = handleY2;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("if (handleX1 > maxHandleX) {");
    formatter.IncIndent();
    formatter.WriteLine("maxHandleX = handleX1;");
    formatter.WriteLine("handleY = handleY2;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("else if (level > 0 && direction == verticalDirection) {");
    formatter.IncIndent();
    formatter.WriteLine("var sourceHandleElement = document.createElementNS('http://www.w3.org/2000/svg', 'line');");
    formatter.WriteLine("var handleX1 = rectX;");
    formatter.WriteLine("var handleY1 = rectY + rectHeight / 2;");
    formatter.WriteLine("var handleX2 = rectX - rectWidth / 2 - rectXSpace;");
    formatter.WriteLine("var handleY2 = rectY + rectHeight / 2;");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"x1\", handleX1.toString());");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"y1\", handleY1.toString());");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"x2\", handleX2.toString());");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"y2\", handleY2.toString());");
    formatter.WriteLine("sourceHandleElement.setAttribute(\"stroke\", \"black\");");
    formatter.WriteLine("svg.appendChild(sourceHandleElement);");
    formatter.WriteLine("if (prevHandleX2 != -1 && prevHandleY2 != -1) {");
    formatter.IncIndent();
    formatter.WriteLine("var connectorHandleElement = document.createElementNS('http://www.w3.org/2000/svg', 'line');");
    formatter.WriteLine("connectorHandleElement.setAttribute(\"x1\", handleX2.toString());");
    formatter.WriteLine("connectorHandleElement.setAttribute(\"y1\", handleY2.toString());");
    formatter.WriteLine("connectorHandleElement.setAttribute(\"x2\", prevHandleX2.toString());");
    formatter.WriteLine("connectorHandleElement.setAttribute(\"y2\", prevHandleY2.toString());");
    formatter.WriteLine("connectorHandleElement.setAttribute(\"stroke\", \"black\");");
    formatter.WriteLine("svg.appendChild(connectorHandleElement);");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("prevHandleX2 = handleX2");
    formatter.WriteLine("prevHandleY2 = handleY2;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("if (minHandleX < maxHandleX && direction == horizontalDirection) {");
    formatter.IncIndent();
    formatter.WriteLine("var hlineElement = document.createElementNS('http://www.w3.org/2000/svg', 'line');");
    formatter.WriteLine("hlineElement.setAttribute(\"x1\", minHandleX.toString());");
    formatter.WriteLine("hlineElement.setAttribute(\"y1\", handleY.toString());");
    formatter.WriteLine("hlineElement.setAttribute(\"x2\", maxHandleX.toString());");
    formatter.WriteLine("hlineElement.setAttribute(\"y2\", handleY.toString());");
    formatter.WriteLine("hlineElement.setAttribute(\"stroke\", \"black\");");
    formatter.WriteLine("svg.appendChild(hlineElement);");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine("prevRectY = rectY;");
    formatter.WriteLine("prevRectX = rectX;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
}

struct DiagramClass
{
    DiagramClass(const std::string& name_, int index_, int level_, bool subject_, bool hasDerivedClasses_, const std::string& link_);
    void Write(util::CodeFormatter& formatter);
    std::string name;
    int index;
    int level;
    bool subject;
    bool hasDerivedClasses;
    std::string link;
};

DiagramClass::DiagramClass(const std::string& name_, int index_, int level_, bool subject_, bool hasDerivedClasses_, const std::string& link_) :
    name(name_), index(index_), level(level_), subject(subject_), hasDerivedClasses(hasDerivedClasses_), link(link_)
{
}

void DiagramClass::Write(util::CodeFormatter& formatter)
{
    formatter.Write("{ ");
    formatter.Write("name: \"");
    formatter.Write(soul::lexer::XmlEscape(name.c_str(), name.c_str() + name.length()));
    formatter.Write("\", ");
    formatter.Write("id: \"");
    formatter.Write("class_" + std::to_string(index));
    formatter.Write("\", ");
    formatter.Write("level: ");
    formatter.Write(std::to_string(level));
    formatter.Write(", ");
    formatter.Write("subject: ");
    formatter.Write(subject ? "true" : "false");
    formatter.Write(", ");
    formatter.Write("hasDerivedClasses: ");
    formatter.Write(hasDerivedClasses ? "true" : "false");
    formatter.Write(", ");
    formatter.Write("link: \"");
    formatter.Write(link);
    formatter.Write("\"");
    formatter.Write(" }");
}

std::string MakeLink(soul::cpp20::symbols::ClassTypeSymbol* cls)
{
    soul::cpp20::symbols::Module* module = cls->GetModule();
    return "../" + module->Name() + "/" + cls->DocName() + ".html";
}

std::vector<soul::cpp20::symbols::ClassTypeSymbol*> GetDerivedClasses(soul::cpp20::symbols::ClassTypeSymbol* cls)
{
    std::vector<soul::cpp20::symbols::ClassTypeSymbol*> derivedClasses;
    for (const auto& derivedClass : cls->DerivedClasses())
    {
        soul::cpp20::symbols::TypeSymbol* type = derivedClass;
        if (type->IsSpecializationSymbol())
        {
            type = static_cast<soul::cpp20::symbols::SpecializationSymbol*>(type)->ClassTemplate();
        }
        if (type && type->IsClassTypeSymbol())
        {
            derivedClasses.push_back(static_cast<soul::cpp20::symbols::ClassTypeSymbol*>(type));
        }
    }
    return derivedClasses;
}

void MakeDiagramClasses(std::vector<std::unique_ptr<DiagramClass>>& classes, soul::cpp20::symbols::SymbolTable* topLevelSymbolTable, soul::cpp20::symbols::ClassTypeSymbol* cls, int& depth, int& level)
{
    int numBaseClasses = 0;
    if (!cls->BaseClasses().empty())
    {
        ++depth;
        --level;
        for (int i = 0; i < cls->BaseClasses().size(); ++i)
        {
            soul::cpp20::symbols::TypeSymbol* baseClass = cls->BaseClasses()[i];
            if (baseClass->IsSpecializationSymbol())
            {
                baseClass = static_cast<soul::cpp20::symbols::SpecializationSymbol*>(baseClass)->ClassTemplate();
            }
            if (baseClass && baseClass->IsClassTypeSymbol())
            {
                MakeDiagramClasses(classes, topLevelSymbolTable, static_cast<soul::cpp20::symbols::ClassTypeSymbol*>(baseClass), depth, level);
                ++numBaseClasses;
            }
        }
        ++level;
    }
    std::vector<soul::cpp20::symbols::ClassTypeSymbol*> derivedClasses = GetDerivedClasses(cls);
    int numDerivedClasses = derivedClasses.size();
    if (level == 0)
    {
        if (numBaseClasses > 0 || numDerivedClasses > 0)
        {
            std::string link = MakeLink(cls);
            classes.push_back(std::unique_ptr<DiagramClass>(new DiagramClass(util::ToUtf8(cls->FullName()), classes.size(), level, true, numDerivedClasses > 0, link)));
            if (numDerivedClasses > 0)
            {
                ++level;
                for (int i = 0; i < numDerivedClasses; ++i)
                {
                    soul::cpp20::symbols::ClassTypeSymbol* derivedClass = derivedClasses[i];
                    std::string link = MakeLink(derivedClass);
                    bool hasDerivedClasses = false;
                    std::vector<soul::cpp20::symbols::ClassTypeSymbol*> descendantClasses = GetDerivedClasses(derivedClass);
                    if (!descendantClasses.empty())
                    {
                        hasDerivedClasses = true;
                    }
                    classes.push_back(std::unique_ptr<DiagramClass>(new DiagramClass(util::ToUtf8(derivedClass->FullName()), classes.size(), level, false, hasDerivedClasses, link)));
                }
            }
        }
    }
    else
    {
        std::string link = MakeLink(cls);
        classes.push_back(std::unique_ptr<DiagramClass>(new DiagramClass(util::ToUtf8(cls->FullName()), classes.size(), level, false, numDerivedClasses > 0, link)));;
    }
}

struct ByLevelAndIndex
{
    bool operator()(const std::unique_ptr<DiagramClass>& left, const std::unique_ptr<DiagramClass>& right) const
    {
        if (left->level < right->level) return true;
        if (left->level > right->level) return false;
        return left->index < right->index;
    }
};

bool GenerateClassDiagramFile(const std::string& modulePath, soul::cpp20::symbols::ClassTypeSymbol* cls, std::string& diagramFileName)
{
    int depth = 0;
    int level = 0;
    std::vector<std::unique_ptr<DiagramClass>> diagramClasses;
    MakeDiagramClasses(diagramClasses, cls->GetSymbolTable(), cls, depth, level);
    if (diagramClasses.empty())
    {
        return false;
    }
    for (auto& diagramClass : diagramClasses)
    {
        diagramClass->level += depth;
    }
    std::sort(diagramClasses.begin(), diagramClasses.end(), ByLevelAndIndex());
    diagramFileName = "class_diagram_" + cls->DocName() + ".js";
    std::string diagramFilePath = util::Path::Combine(modulePath, diagramFileName);
    std::ofstream diagramFile(diagramFilePath);
    util::CodeFormatter formatter(diagramFile);
    GenerateClassDiagramCode(formatter);
    formatter.WriteLine("function drawClassDiagram() {");
    formatter.IncIndent();
    formatter.WriteLine("var classes = [");
    formatter.IncIndent();
    bool first = true;
    for (const auto& diagramClass : diagramClasses)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.WriteLine(",");
        }
        diagramClass->Write(formatter);
    }
    formatter.WriteLine("];");
    formatter.DecIndent();
    formatter.WriteLine("drawDiagram(classes);");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    return true;
}

} // namespace gendoc
