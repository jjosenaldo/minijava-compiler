def get(x):
	if x == "and": 
		return "TOK_AND"
	elif x == "or":
		return "TOK_OR"
	elif x == "less":
		return "'<'"
	elif x == "lesseq":
		return "TOK_LESS_EQ"
	elif x == "greatereq":
		return  "TOK_GREATER_EQ"
	elif x == "greater":
		return "'>'"
	elif x == "isequal":
		return "TOK_EQ"
	elif x == "isdiff":
		return "TOK_DIFF"
	elif x == "then":
		return "TOK_THEN"
	elif x == "rbracket":
		return "']'"
	elif x == "')'":
		return "')'"
	elif x == "comma":
		return "','"
	elif x == "id":
		return "TOK_ID"
	elif x == "lbrace":
		return "'{'"
	elif x == "while":
		return "TOK_WHILE"
	elif x == "system":
		return "TOK_SYSTEM"
	elif x == "continue":
		return "TOK_CONTINUE"
	elif x == "break":
		return "TOK_BREAK"
	elif x == "return":
		return "TOK_RETURN"
	elif x == "semicolon":
		return "';'"
	elif x == "if":
		return "TOK_IF"
	elif x == "boolean":
		return "TOK_BOOLEAN"
	elif x == "int":
		return "TOK_INT"
	elif x == "void":
		return "TOK_VOID"
	elif x == "rbrace":
		return "'}'"
	elif x == "plus":
		return "'+'"
	elif x == "minus":
		return "'-'"
	elif x == "excl":
		return "'!'"
	elif x == '(':
		return "'('"
	elif x == "times":
		return "'*'"
	elif x == "mod":
		return "'%'"
	elif x == "div":
		return "'/'"
	elif x == "dot":
		return "'.'"
	elif x == "lbracket":
		return "'['"
	elif x == "litint":
		return "TOK_LIT_INT"
	elif x == "true":
		return "TOK_TRUE"
	elif x == "false":
		return "TOK_FALSE"
	elif x == "litstr":
		return "TOK_LIT_STR"
	elif x == "this":
		return "TOK_THIS"
	elif x == "null":
		return  "TOK_NULL"
	else:
		print("ERROR: " + x)

def prnt(s):
	l = s.split(" ")
	res = "x == " + get(l[0])
	for i in l[1:]: res  += " || x == " + get(i)
	return res
	
