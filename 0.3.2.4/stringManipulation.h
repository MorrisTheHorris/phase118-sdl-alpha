std::string concadenatorBinary(std::string str, int num)
{
    std::ostringstream stream;
    stream << str << num;
    std::string f = stream.str();
    return f;
}

std::string concadenatorTrinary(std::string str, int num, std::string ext)
{
    std::ostringstream stream;
    stream << str << num << ext;
    std::string f = stream.str();
    return f;
}

std::string concadenatorTime(int a, int b )
{
    std::ostringstream d;
    d << a << "  :  " << b;
    return d.str();
}
