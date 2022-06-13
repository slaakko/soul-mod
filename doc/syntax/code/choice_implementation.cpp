// generated code for a 'choice':

template<typename Lexer>
soul::parser::Match StatementParser<Lexer>::Statement(Lexer& lexer)
{
	...
	int64_t save = lexer.GetPos();
	soul::parser::Match match(false);
	soul::parser::Match* parentMatch7 = &match;
	{
		int64_t save = lexer.GetPos();
		soul::parser::Match match(false);
		soul::parser::Match* parentMatch8 = &match;
		{
			int64_t pos = lexer.GetPos();
			soul::parser::Match match = StatementParser<Lexer>::LabeledStatement(lexer);
			labeledStatement.reset(static_cast<soul::ast::cpp::StatementNode*>(match.value));
			if (match.hit)
			{
				{
					...
					return soul::parser::Match(true, labeledStatement.release());
				}
			}
			*parentMatch8 = match;
		}
		*parentMatch7 = match;
		if (!match.hit)
		{
			soul::parser::Match match(false);
			soul::parser::Match* parentMatch9 = &match;
			lexer.SetPos(save);
			{
				soul::parser::Match match(false);
				soul::parser::Match* parentMatch10 = &match;
				{
					int64_t pos = lexer.GetPos();
					soul::parser::Match match = StatementParser<Lexer>::EmptyStatement(lexer);
					emptyStatement.reset(static_cast<soul::ast::cpp::StatementNode*>(match.value));
					if (match.hit)
					{
						{
							...
							return soul::parser::Match(true, emptyStatement.release());
						}
					}
					*parentMatch10 = match;
				}
				*parentMatch9 = match;
			}
			*parentMatch7 = match;
		}
	}
	....
}										
