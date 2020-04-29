// If there is no argument for the argument
if (input == "6")
{
    string arg = "--force-ipv4";
    CheckEraseString(arg);
}

// If there is an argument for the argument
if (input == "8")
{
    string arg = "--geo-verification-proxy";
    string URL;
    bool boolean = false;

    if (CheckString(arg))
    {
        EraseArgumentArg(arg);
    }
    else
    {
        while (!boolean)
        {
            cout << endl;

            cout << "--geo-verification-proxy URL" << endl;
            cout << "URL: ";
            getline(cin, URL);

            if (URL != "")
            {
                command = command + "--geo-verification-proxy " + URL;
            }
            else
                cout << "You did not enter a URL!" << endl;
        }
    }
}