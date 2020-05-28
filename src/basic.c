// #include "../include/basic.h"

// memory mem[100];
// int c1 = 0, c2 = 99, lc = 0, cc = 0;
// label leb[100];
// label constV[100];
// int v[26] = {0};

// int getVA(char c)
// {
//     if ((c >= 'A') && (c <= 'Z'))
//     {
//         if (v[c - 'A'] < 0)
//         {
//             v[c - 'A'] = c2;
//             mem[c2].operand = 0;
//             mem[c2].command = "=";
//             c2--;
//         }
//         return v[c - 'A'];
//     }
//     else
//         return -1;
// }

// void addAC(string command, int operand)
// {
//     mem[c1].command = command;
//     mem[c1].operand = operand;
//     c1++;
// }

// int getConst(string s)
// {
//     int a;
//     try
//     {
//         a = stoi(s);
//     }
//     catch (const exception &e)
//     {
//         e.what();
//         cout << "WRONG CONST";
//         exit(1);
//     }
//     for (int i = 0; i < cc; i++)
//     {
//         if (constV[i].lb == s)
//         {
//             return constV[i].pos;
//         }
//     }
//     constV[cc].lb = s;
//     constV[cc].pos = c2;
//     mem[c2].operand = a;
//     mem[c2].command = "=";
//     c2--;
//     cc++;
//     return c2 + 1;
// }

// void rpnTrans(string in, char c)
// {
//     int depth = 0;
//     string tmp = "";
//     string out = "";
//     for (unsigned int i = 0; i < in.size(); i++)
//     {
//         if ((in[i] >= 'A' && in[i] <= 'Z'))
//         {
//             addAC("LOAD", getVA(in[i]));
//             addAC("STORE", c2 - depth);
//             depth++;
//         }
//         else if (in[i] == '(')
//         {
//             i++;
//             while (in[i] != ')')
//             {
//                 tmp += in[i];
//                 i++;
//             }
//             addAC("LOAD", getConst(tmp));
//             addAC("STORE", c2 - depth);
//             depth++;
//         }
//         else
//         {
//             if (in[i] < 0)
//             {
//                 if (depth < 1)
//                 {
//                     cout << "ERROR";
//                     exit(1);
//                 }
//                 if (-in[i] == '-')
//                 {
//                     addAC("LOAD", getConst("0"));
//                     addAC("SUB", c2 - depth + 1);
//                     addAC("STORE", c2 - depth + 1);
//                 }
//             }
//             else
//             {
//                 if (depth < 2)
//                 {
//                     cout << "ERROR";
//                     exit(1);
//                 }
//                 int st2 = c2 - depth + 1;
//                 addAC("LOAD", c2 - depth + 2);
//                 switch (in[i])
//                 {
//                 case '+':
//                     addAC("ADD", st2);
//                     break;

//                 case '-':
//                     addAC("SUB", st2);
//                     break;

//                 case '/':
//                     addAC("DIVIDE", st2);
//                     break;

//                 case '*':
//                     addAC("MUL", st2);
//                     break;
//                 }
//                 addAC("STORE", c2 - depth + 2);
//                 depth--;
//             }
//         }
//     }
//     if (depth != 1)
//     {
//         cout << "ERROR";
//         exit(1);
//     }
//     addAC("LOAD", c2);
//     addAC("STORE", getVA(c));
// }

// void setLable(string str1)
// {
//     if (findLabel(str1) != -1)
//     {
//         cout << "ERROR";
//         exit(1);
//     }
//     if (leb[lc - 1].lb >= str1)
//     {
//         cout << "ERROR";
//         exit(1);
//     }
//     leb[lc].lb = str1;
//     leb[lc].pos = c1;
//     lc++;
//     c1++;
// }

// int findLabel(string str)
// {
//     for (int i = 0; i < lc; i++)
//     {
//         if (leb[i].lb == str)
//             return leb[i].pos;
//     }
//     return -1;
// }

// int regX(string buf)
// {
//     smatch sm;

//     if (regex_search(buf, sm, regex("([0-9]+)\\s+REM\\s+(.*)\n")))
//     {
//         return 1;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+LET\\s+([A-Z])\\s+=([A-Z0-9\\-+/*\\(\\) ]*)\\s*\n")))
//     {
//         string rpnstr;
//         if (rpn(rpnstr, sm[3].str()) == -1)
//             cout << "ERROR";
//         rpnTrans(rpnstr, sm[2].str()[0]);
//         return 2;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+INPUT\\s+([A-Z])\\s*\n")))
//     {
//         addAC("READ", getVA(sm[2].str()[0]));
//         return 3;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+OUTPUT\\s+([A-Z]\\s*)\n")))
//     {
//         addAC("WRITE", getVA(sm[2].str()[0]));
//         return 4;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+IF\\s+([A-Z0-9])\\s*([<>=]{1,2})\\s*([A-Z0-9]+)\\s+GOTO\\s+([0-9]+)\n")))
//     {
//         string s1, s2, s3;
//         s1 = sm[2].str();
//         s2 = sm[3].str();
//         s3 = sm[4].str();
//         int st1 = 0, st2 = 0;
//         if (s1[0] >= 'A' && s1[0] <= 'Z')
//         {
//             if (s1.size() != 1)
//             {
//                 cout << "ERROR";
//                 exit(1);
//             }
//             st1 = getVA(s1[0]);
//         }
//         else
//         {
//             for (unsigned int i = 0; i < s1.size(); i++)
//             {
//                 if (!(s1[i] >= '0' && s1[i] <= '9'))
//                 {
//                     cout << "ERROR";
//                     exit(1);
//                 }
//             }
//             st1 = getConst(s1);
//         }
//         if (s3[0] >= 'A' && s3[0] <= 'Z')
//         {
//             if (s3.size() != 1)
//             {
//                 cout << "ERROR";
//                 exit(1);
//             }
//             st2 = getVA(s3[0]);
//         }
//         else
//         {
//             for (unsigned int i = 0; i < s3.size(); i++)
//             {
//                 if (!(s3[i] >= '0' && s3[i] <= '9'))
//                 {
//                     cout << "ERROR";
//                     exit(1);
//                 }
//             }
//             st2 = getConst(s3);
//         }
//         int d = -1;
//         if (s2 == ">")
//         {
//             addAC("LOAD", st2);
//             addAC("SUB", st1);
//             d = findLabel(sm[5].str());
//             if (d == -1)
//             {
//                 cout << "ERROR";
//                 exit(1);
//             }
//             addAC("JNEG", d);
//         }
//         else if (s2 == "<")
//         {
//             addAC("LOAD", st1);
//             addAC("SUB", st2);
//             d = findLabel(sm[5].str());
//             if (d == -1)
//             {
//                 cout << "ERROR";
//                 exit(1);
//             }
//             addAC("JNEG", d);
//         }
//         else if (s2 == "=")
//         {
//             addAC("LOAD", st2);
//             addAC("SUB", st1);
//             d = findLabel(sm[5].str());
//             if (d == -1)
//             {
//                 cout << "ERROR";
//                 exit(1);
//             }
//             addAC("JZ", d);
//         }
//         else if (s2 == ">=")
//         {
//             addAC("LOAD", st2);
//             addAC("SUB", st1);
//             d = findLabel(sm[5].str());
//             if (d == -1)
//             {
//                 cout << "ERROR";
//                 exit(1);
//             }
//             addAC("JNEG", d);
//             addAC("JZ", d);
//         }
//         else if (s2 == "<=")
//         {
//             addAC("LOAD", st1);
//             addAC("SUB", st2);
//             d = findLabel(sm[5].str());
//             if (d == -1)
//             {
//                 cout << "ERROR";
//                 exit(1);
//             }
//             addAC("JNEG", d);
//             addAC("JZ", d);
//         }
//         else
//         {
//             cout << "ERROR";
//             exit(1);
//         }
//         return 5;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+GOTO\\s+([0-9]+)\n")))
//     {
//         for (int i = 0; i < lc; i++)
//         {
//             if (leb[i].lb == sm[2].str())
//             {
//                 addAC("JUMP", leb[i].pos);
//                 return 6;
//             }
//         }
//         return -1;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+END\\s*\n")))
//     {
//         addAC("HALT", 0);
//         return 7;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+PRINT\\s+([A-Z]\\s*)\n")))
//     {
//         addAC("WRITE", getVA(sm[2].str()[0]));
//         return 4;
//     }
//     else
//         return -1;
//     return 0;
// }

// int fillUP(string buf)
// {
//     smatch sm;
//     if (regex_search(buf, sm, regex("([0-9]+)\\s+REM\\s+(.*)\n")))
//     {
//         return 1;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+LET\\s+([A-Z])\\s+=([A-Z0-9\\-+/*\\(\\) ]*)\\s*\n")))
//     {
//         setLable(sm[1].str());
//         string rpnstr;
//         if (rpn(rpnstr, sm[3].str()) == -1)
//             cout << "ERROR";
//         for (unsigned int i = 0; i < rpnstr.size(); i++)
//         {
//             if (getVA(rpnstr[i]) != -1)
//                 c1 += 2;

//             if (rpnstr[i] == '(')
//             {
//                 string tmp = "";
//                 i++;
//                 while (rpnstr[i] != ')')
//                 {
//                     tmp += rpnstr[i];
//                     i++;
//                 }
//                 getConst(tmp);
//                 c1 += 2;
//             }
//             if (rpnstr[i] == '+' || rpnstr[i] == '-' || rpnstr[i] == '/' || rpnstr[i] == '*')
//                 c1 += 3;
//             if (rpnstr[i] == -'-')
//             {
//                 getConst("0");
//                 c1 += 3;
//             }
//         }
//         return 2;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+INPUT\\s+([A-Z])\\s*\n")))
//     {
//         if (sm[2].str().size() != 1)
//         {
//             cout << "ERROR WRONG INPUT_COMMAND";
//             exit(1);
//         }
//         getVA(sm[2].str()[0]);
//         setLable(sm[1].str());
//         return 3;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+OUTPUT\\s+([A-Z]\\s*)\n")))
//     {
//         if (sm[2].str().size() != 1)
//         {
//             cout << "ERROR WRONG OUTPUT_COMMAND";
//             exit(1);
//         }
//         getVA(sm[2].str()[0]);
//         setLable(sm[1].str());
//         return 4;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+IF\\s+([A-Z0-9])\\s*([<>=]{1,2})\\s*([A-Z0-9]+)\\s+GOTO\\s+([0-9]+)\n")))
//     {
//         setLable(sm[1].str());
//         string s1, s2;
//         s1 = sm[2].str();
//         s2 = sm[4].str();
//         if (s1[0] >= 'A' && s1[0] <= 'Z')
//         {
//             if (s1.size() != 1)
//             {
//                 cout << "ERROR";
//                 exit(1);
//             }
//             getVA(s1[0]);
//         }
//         else
//         {
//             for (unsigned int i = 0; i < s1.size(); i++)
//             {
//                 if (!(s1[i] >= '0' && s1[i] <= '9'))
//                 {
//                     cout << "ERROR";
//                     exit(1);
//                 }
//             }
//             getConst(s1);
//         }
//         if (s2[0] >= 'A' && s2[0] <= 'Z')
//         {
//             if (s2.size() != 1)
//             {
//                 cout << "ERROR";
//                 exit(1);
//             }
//             getVA(s2[0]);
//         }
//         else
//         {
//             for (unsigned int i = 0; i < s2.size(); i++)
//             {
//                 if (!(s2[i] >= '0' && s2[i] <= '9'))
//                 {
//                     cout << "ERROR";
//                     exit(1);
//                 }
//             }
//             getConst(s2);
//         }
//         if (sm[3].str().size() == 2)
//             c1++;
//         c1 += 3;
//         return 5;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+GOTO\\s+([0-9]+)\n")))
//     {
//         setLable(sm[1].str());
//         return -1;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+END\\s*\n")))
//     {
//         setLable(sm[1].str());
//         return 7;
//     }
//     else if (regex_search(buf, sm, regex("([0-9]+)\\s+PRINT\\s+([A-Z]\\s*)\n")))
//     {
//         if (sm[2].str().size() != 1)
//         {
//             cout << "ERROR WRONG PRINT_COMMAND";
//             exit(1);
//         }
//         getVA(sm[2].str()[0]);
//         setLable(sm[1].str());
//         return 4;
//     }
//     else
//         return -1;
// }

// int prior(char c)
// {
//     if (c < 0)
//         return 4;
//     switch (c)
//     {
//     case '*':
//     case '/':
//         return 3;
//     case '-':
//     case '+':
//         return 2;
//     case '(':
//         return 1;
//     }
//     return -1;
// }

// int rpn(string &out, string in)
// {
//     bool f1 = 0;
//     string opers = "";
//     char prev;
//     for (unsigned int i = 0; i < in.length(); i++)
//     {
//         if (in[i] == ' ')
//             continue;
//         if (in[i] == ')')
//         {
//             f1 = !f1;
//             if (opers.empty())
//                 return -1;
//             while (opers.back() != '(')
//             {
//                 out += opers.back();
//                 opers.pop_back();
//                 if (opers.empty())
//                     return -1;
//             }
//             opers.pop_back();
//         }
//         if (in[i] >= '0' && in[i] <= '9')
//         {
//             string tmp = "";
//             while (in[i] >= '0' && in[i] <= '9')
//             {
//                 tmp += in[i];
//                 i++;
//             }
//             i--;
//             int chs;
//             try
//             {
//                 chs = stoi(tmp);
//             }
//             catch (const exception &e)
//             {
//                 e.what();
//                 cout << "Wrong so big number in LET";
//                 exit(1);
//             }
//             out += "(" + to_string(chs) + ")";
//         }
//         if (in[i] >= 'A' && in[i] <= 'Z')
//         {
//             out += in[i];
//         }
//         if (in[i] == '(')
//         {
//             opers += "(";
//             f1 = !f1;
//         }
//         if ((in[i] == '+' || in[i] == '-') && (prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '('))
//         {
//             opers.push_back(-in[i]);
//         }
//         else if (in[i] == '/' || in[i] == '*' || in[i] == '+' || in[i] == '-')
//         {
//             if (opers.empty())
//             {
//                 opers += in[i];
//             }
//             else
//             {
//                 if (prior(opers.back()) < prior(in[i]))
//                 {
//                     opers += in[i];
//                 }
//                 else
//                 {
//                     while (!opers.empty() && (prior(opers.back()) >= prior(in[i])))
//                     {
//                         out += opers.back();
//                         opers.pop_back();
//                     }
//                     opers += in[i];
//                 }
//             }
//         }
//         prev = in[i];
//     }
//     if (f1)
//     {
//         cout << "ERROR";
//         exit(1);
//     }
//     while (!opers.empty())
//     {
//         out += opers.back();
//         opers.pop_back();
//     }
//     return 0;
// }

// int main(int argc, char *argv[])
// {
//     if (argc != 3)
//     {
//         cout << "2 arguments needed\nsat <inputFile.sb> <outputFile.sa>\n";
//         return -1;
//     }
//     if (!regex_match(argv[1], regex(".+\\.sb")))
//         cout << "FIRST ARG ERROR\n";
//     if (!regex_match(argv[2], regex(".+\\.sa")))
//         cout << "SECOND ARG ERROR\n";

//     ifstream in(argv[1]);
//     ofstream out(argv[2]);

//     if (!in)
//     {
//         cout << "CANNOT OPEN";
//         exit(1);
//     }
//     else
//     {
//         for (int i = 0; i < 26; i++)
//         {
//             v[i] = -1;
//         }
//         while (!in.eof())
//         {
//             string buf;
//             getline(in, buf);
//             buf += "\n";
//             fillUP(buf);
//         }
//         c1 = 0;
//         in.clear();
//         in.seekg(0);
//         while (!in.eof())
//         {
//             string buf;
//             getline(in, buf);
//             buf += "\n";
//             cout << regX(buf) << endl;
//         }
//     }

//     for (int i = 0; i < 100; i++)
//     {
//         if (leb[i].lb == "")
//             continue;
//         cout << leb[i].pos << " " << leb[i].lb << endl;
//     }

//     for (int i = 0; i < 100; i++)
//     {
//         if (mem[i].command == "")
//             continue;
//         if (mem[i].command == "=")
//             out << setfill('0') << setw(2) << i << " " << mem[i].command << " " << '+' << hex << uppercase << setfill('0') << setw(4) << mem[i].operand << dec << endl;
//         else
//             out << setfill('0') << setw(2) << i << " " << mem[i].command << " " << setfill('0') << setw(2) << mem[i].operand << endl;
//     }
//     return 0;
// }