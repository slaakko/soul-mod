// 'sequence' implementation:

template<typename Lexer>
soul::parser::Match StatementParser<Lexer>::WhileStatement(Lexer& lexer)
{
	...
    std::unique_ptr<soul::ast::cpp::Node> cond;
    std::unique_ptr<soul::ast::cpp::StatementNode> stmt;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == WHILE)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == LPAREN)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch7 = match;
                                    }
                                    else
                                    {
                                        lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LPAREN));
                                    }
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch8 = &match;
                        {
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = StatementParser<Lexer>::Condition(lexer);
                                cond.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                if (match.hit)
                                {
                                    *parentMatch9 = match;
                                }
                                else
                                {
                                    lexer.ThrowExpectationFailure(pos, "Condition");
                                }
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
                    {
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch11 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == RPAREN)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                *parentMatch11 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RPAREN));
                            }
                        }
                        *parentMatch10 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch12 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch13 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = StatementParser<Lexer>::Statement(lexer);
                        stmt.reset(static_cast<soul::ast::cpp::StatementNode*>(match.value));
                        if (match.hit)
                        {
                            *parentMatch13 = match;
                        }
                        else
                        {
                            lexer.ThrowExpectationFailure(pos, "Statement");
                        }
                    }
                    *parentMatch12 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
				...
                return soul::parser::Match(true, new soul::ast::cpp::WhileStatementNode(lexer.GetSourcePos(pos), cond.release(), stmt.release()));
            }
        }
        *parentMatch0 = match;
    }
	...
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}
