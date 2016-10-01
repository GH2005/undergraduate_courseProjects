using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Antlr4.Runtime;
using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;

namespace CppFuncDef
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader inputStream = new StreamReader(Console.OpenStandardInput());
            AntlrInputStream input = new AntlrInputStream(inputStream.ReadToEnd());
            CppFuncDefLexer lexer = new CppFuncDefLexer(input);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            CppFuncDefParser parser = new CppFuncDefParser(tokens);
            IParseTree tree = parser.cppFunction();
            Console.WriteLine(tree.ToStringTree(parser));
            Console.Read();
        }
    } 
}
