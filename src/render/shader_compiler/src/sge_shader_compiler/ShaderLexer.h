#pragma once

#include <./sge_shader_compiler.h>

namespace sge {

enum class TokenType {
	None,
	Operator,

};



class ShaderLexer : public NonCopyable {
public:

	static void loadFile(StrView filename);
	static void loadMem(Span<const u8> src);

private:
	void _londMem(Span<const u8> src);

	void _nextLine();
	void _nextToken();

	TokenType _token;
	String _tokenValue;

	int _lineNumber = 0;

};













}