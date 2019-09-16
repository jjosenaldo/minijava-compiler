number [0-9]+

%%

[ ] 		{ /* skip blanks */ }
{number} 	{sscanf(yytext,"%d",&yylval); return NUMBER;}
\n|.		{return yytext[0];}

%%