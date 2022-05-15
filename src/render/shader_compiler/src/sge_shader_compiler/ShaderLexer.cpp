#include "ShaderLexer.h"

namespace sge {

//static func
void ShaderLexer::loadFile(StrView filename) {
	MemMapFile mm;
	mm.open(filename);
	loadMem(mm); //converted to spam u8 = loadMem(mm.span());
}

//static func
void ShaderLexer::loadMem(Span<const u8> src) {
	ShaderLexer inst;
	inst.loadMem(src);
}

void ShaderLexer::_londMem(Span<const u8> src) {
}

void ShaderLexer::_nextLine() {
}

void ShaderLexer::_nextToken() {
}

}