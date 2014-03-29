#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

enum scTokenType
{
    TOKEN_IDENTIFIER,
    TOKEN_SEPARATOR,
    TOKEN_STRINGDATA
};

struct Token 
{
    scTokenType type_;
    string data_;
    unsigned int lineno_;
};

class scStream 
{
    vector<Token> program_;

    public:
    
    vector<Token> getStreamVector()
    {
        return program_;
    }

    void makeFromFile(string s)
    {
        ifstream example(s);

        if(!example.is_open()) exit(EXIT_FAILURE);

        string tokenBoundaries = "\n\"\'.,;:[]{}<>()+-*/^%$!= ";
        string line;
        unsigned int lno = 1;
        while(!example.eof())
        {
            char in;
            example.get(in);
            if(tokenBoundaries.find(in) != string::npos)
            {
                if(line.length() == 1 && line[0] == '\\')
                {
                    line += in;
                    Token nTok = {TOKEN_IDENTIFIER, line, lno};
                    program_.push_back(nTok);
                    line = "";
                }
                else if(line.length())
                {
                    Token nTok = {TOKEN_IDENTIFIER, line, lno};
                    program_.push_back(nTok);
                    line = "";

                    Token sTok = {TOKEN_SEPARATOR, string(1,in), lno};
                    program_.push_back(sTok);
                }
                else
                {
                    Token sTok = {TOKEN_SEPARATOR, string(1,in), lno};
                    program_.push_back(sTok);
                }

                if(in == '\n')
                {
                    ++lno;
                }
            }
            else
            {
                line += in;
            }

        }

        example.close();
   
    }
};

struct scSyntaxTree
{
    shared_ptr<Token> node_;
    vector<shared_ptr<scSyntaxTree> > children_;
};

class scStateMachine
{
    shared_ptr<scSyntaxTree> AST_;
    
    public:
    scStateMachine(){}

    scStateMachine(string f)
    {
        makeFromFile(f);
    }

    void makeFromFile(string f)
    {
        scStream prog_stream;
        prog_stream.makeFromFile(f);

        vector<Token> stream_vec = prog_stream.getStreamVector();
        
        vector<Token>::iterator it = stream_vec.begin();
        
        // Parse all string literals
        for(;it != stream_vec.end(); ++it)
        {
            if((*it).type_ == TOKEN_SEPARATOR && (*it).data_[0] == '\"')
            {
                vector<Token>::iterator next = it + 1;
                Token new_identifier = {TOKEN_STRINGDATA, "", (*it).lineno_};
                for(;;++next)
                {
                    if(next == stream_vec.end())
                    {
                        cerr << "Error matching \" on line " << (*it).lineno_ << endl;
                        exit(1);
                    }
                    else if((*next).type_ == TOKEN_SEPARATOR && (*next).data_ == "\"")
                    {
                        break;
                    }
                    else
                    {
                        new_identifier.data_ += (*next).data_;
                    }
                }
                it = stream_vec.erase(it,next);
                (*it) = new_identifier;
            }
        }

        int square_count = 0, curly_count = 0;
        vector<Token>::iterator last_bracket = stream_vec.begin();
        for(it = stream_vec.begin();it != stream_vec.end();++it)
        {
            if(square_count < 0 || curly_count < 0) break;

            if((*it).type_ == TOKEN_SEPARATOR && (*it).data_.length() > 0)
            {
                switch((*it).data_[0])
                {
                    case '{':
                        curly_count += 1;
                        last_bracket = it;
                        break;
                    case '}':
                        curly_count -= 1;
                        if(last_bracket == stream_vec.begin()) last_bracket = it;
                        break;
                    case '[':
                        square_count += 1;
                        last_bracket = it;
                        break;
                    case ']':
                        square_count -= 1;
                        if(last_bracket == stream_vec.begin()) last_bracket = it;
                        break;
                }
            }
        }
        if(square_count != 0 || curly_count != 0)
        {
            cerr << "Unmatched " << (*last_bracket).data_ << " on line " << (*last_bracket).lineno_ << endl;
            return;
        }

        cerr << "Square: " << square_count << " Curly: " << curly_count << endl;

        // Send info about current stream object to standard error
        for(it = stream_vec.begin();it != stream_vec.end();++it)
        {
            string type, val = (*it).data_;
            unsigned int lno = (*it).lineno_;
            switch ((*it).type_)
            {
                case TOKEN_SEPARATOR:
                    type = "SEPARATOR";
                    break;
                case TOKEN_IDENTIFIER:
                    type = "IDENTIFIER";
                    break;
                case TOKEN_STRINGDATA:
                    type = "STRING";
                    break;
            }

            if((*it).type_ == TOKEN_SEPARATOR)
            {
                switch ((*it).data_[0])
                {
                    case ' ':
                        val = "SPACE";
                        break;
                    case '\n':
                        val = "NEWLINE";
                        break;
                    default:
                        break;
                }
            }

            cerr << type << " => " << val << " Line " << lno << endl;
        }


    }
};

int main(int argc, char** argv) 
{
    if(argc < 2) return EXIT_FAILURE;

    scStateMachine our_program;
    our_program.makeFromFile(argv[1]);

    //  our_program.printProgramVector();

    return EXIT_SUCCESS;
}

