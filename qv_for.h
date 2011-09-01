#pragma once

class qFor : public qInstruction
{
public:
	qFor(qValue * pre, qValue * test, qValue * post, qValue * code)
	{
		insert(pre);
		insert(test);
		insert(post);
		insert(code);
	}
	qString print(int indent)
	{
		if (children.size() < 4) return "[error for]";

		return doIndent(indent) + "for (" + children[0]->print() + "; " + children[1]->print() + "; " + children[2]->print() + ")\n"+
			children[3]->print(indent+(children[3]->isBlock()?0:1));
	}
};
