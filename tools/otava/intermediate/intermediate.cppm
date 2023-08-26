// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate;

export import otava.intermediate.basic.block;
export import otava.intermediate.code;
export import otava.intermediate.code.generator;
export import otava.intermediate.compile.unit;
export import otava.intermediate.context;
export import otava.intermediate.data;
export import otava.intermediate.data_item_adder;
export import otava.intermediate.error;
export import otava.intermediate.function;
export import otava.intermediate.instruction;
export import otava.intermediate.lexer;
export import otava.intermediate.code.parser;
export import otava.intermediate.token;
export import otava.intermediate.spg.rules;
export import otava.intermediate.linear_scan_register_allocator;
export import otava.intermediate.metadata;
export import otava.intermediate.parser;
export import otava.intermediate.reference_resolver;
export import otava.intermediate.register_allocator;
export import otava.intermediate.simple.assembly.code.generator;
export import otava.intermediate.token_parser;
export import otava.intermediate.type;
export import otava.intermediate.util;
export import otava.intermediate.value;
export import otava.intermediate.verify;
export import otava.intermediate.visitor;
