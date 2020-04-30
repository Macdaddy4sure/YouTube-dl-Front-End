// YouTube-dl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// The goal of this program is to give a frontend app for YouTube-dl
// There will be a few options for creating the command for the program
//  1. Download a video from a selected URL
//  2. Download a playlist from a URL
//  3. Download an entire channel based on URL

// First we need to create settings for the ap, like where the files are to be stored
// Second would be to get the option from the user
// Third would be to create the command
// Fourth would be to get the title of the video and rename the video file after the download completes *Optional*

void Menu();
void Single_Video();
void Settings();
string EditCommand(string temp_cmd);
void CheckEraseString(string arg, string description);
bool CheckString(string arg);
string ParseFilename(string filename);
void EraseArgumentArg(string arg, string arg2, string description);
void AddArgumentArgument(string arg, string arg2, string description);
string OutputTemplate(string arg, string arg2, string description);
string AddTemplateArgs(string argument, string arg3);
string ParseTemplate(string out_template);

string command = "\"C:\\Program Files\\YouTube-dl\\youtube-dl.exe\" ";
string config;

int main()
{
    // Check if this is the first run of the program
    // Check the settings file for first run

    Menu();
}

// Create a main menu for the program
void Menu()
{
    string input;
    bool in = false;

    while (!in)
    {
        system("cls");

        cout << "====== Main Menu ======" << endl;
        cout << "|  1. Single Video     |" << endl;
        cout << "|----------------------|" << endl;
        cout << "|  0. Settings         |" << endl;
        cout << "========================" << endl;
        cout << endl;
        cout << "Your selection: ";
        getline(cin, input);

        switch (input[0])
        {
        case ('1'):
            // Send the flow to the single video function
            Single_Video();
            break;
        case ('0'):
            // Send the flow to the settings function
            Settings();
            break;
        default:
            // The input is not correct
            in = false;
            cout << "The input is not recognized..." << endl;
            break;
        }
    }
}

void Single_Video()
{
    string input;
    string temp_cmd = command;
    bool boolean = false;

    while (!boolean)
    {
        system("cls");

        cout << "======== Single Video =======" << endl;
        cout << "+--------Enter a url--------+" << endl;
        cout << "| 0. Go to Main Menu        |" << endl;
        cout << "+---------------------------+" << endl;
        cout << endl;
        cout << "Current Command: " << temp_cmd << endl;
        cout << endl;
        cout << "URL: ";
        getline(cin, input);

        if (input != "" && input != "0")
        {
            command = temp_cmd + input;
            system(command.c_str());

            // Remove the URL from the last used command
            command = temp_cmd;

            // Save the command to the first open space concatenating the previous argument file
            fstream previous_cmd;

            previous_cmd.open("previous_cmd.txt");

            if (previous_cmd.is_open())
            {
                previous_cmd << command;
            }

            cout << "Press any key to continue...";
            cin.get();
        }
        else if (input == "0")
        {
            boolean = true;
        }
        else
        {
            cout << "You have entered an invalid URL..." << endl;
        }
    }
}

void Settings()
{
    string input;
    string temp_cmd;
    bool boolean = false;

    while (!boolean)
    {
        system("cls");

        // Change the command for where to save videos
        cout << "+-----------Settiings-----------+" << endl;
        cout << "| 1. Check YouTube-dl version   |" << endl;
        cout << "| 2. Update YouTube-dl          |" << endl;
        cout << "| 3. Dump User Agent            |" << endl;
        cout << "| 4. List Extractors            |" << endl;
        cout << "| 5. List Thumbnails Formats    |" << endl;
        cout << "| 6. Add to YouTube-dl command  |" << endl;
        cout << "| 7. Print current command      |" << endl;
        cout << "| 8. Set YouTube-dl Install Loc |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << "| 0. Back to Main Menu          |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << endl;
        cout << "Your selection: ";
        getline(cin, input);

        if (input == "1")
        {
            temp_cmd = "youtube-dl --version";
            system(temp_cmd.c_str());
            cin.get();
        }
        else if (input == "2")
        {
            temp_cmd = "youtube-dl --update";
            system(temp_cmd.c_str());
            cin.get();
        }
        else if (input == "3")
        {
            temp_cmd = "youtube-dl --dump-user-agent";
            system(temp_cmd.c_str());
            cin.get();
        }
        else if (input == "4")
        {
            temp_cmd = "youtube-dl --list-extractors --extractors-description";
            system(temp_cmd.c_str());
            cin.get();
        }
        else if (input == "5")
        {
            temp_cmd = "youtube-dl --list-thumbnail";
            system(temp_cmd.c_str());
            cin.get();
        }
        else if (input == "6")
        {
            temp_cmd = "youtube-dl";
            temp_cmd = command;
            command = EditCommand(temp_cmd);
        }
        else if (input == "7")
        {
            cout << "Command: " << command << endl;
        }
        else if (input == "8")
        {
            string input2;
            bool boolean2 = false;

            cout << endl;
            cout << "Change YouTube-dl install location" << endl;
            cout << "Location: ";
            getline(cin, input2);

            if (input2 != "")
            {
                // Run the string through a function parsing the input
                command = ParseFilename(input2);
            }
            else
            {
                cout << "You did not specifiy an install location!" << endl;
            }
        }
        else if (input == "0")
        {
            boolean = true;
            return;
        }
    }
}

string EditCommand(string temp_cmd)
{
    bool boolean = false;
    string input;
    string cmd_input;
    int count;
    int temp;
    string previous[99];
    fstream previous_cmd;

    // Print the current comamnd
    while (!boolean)
    {
        system("cls");

        // Load the previously used commmands into memory
        previous_cmd.open("previous_cmd.txt");
        count = 0;

        if (previous_cmd.is_open())
        {
            // The file was opened successfully
            // Add the previous commands into memory
            while (getline(previous_cmd, cmd_input))
            {
                previous[count] = cmd_input;
                count++;
            }
        }

        cout << endl;
        cout << "+---------Edit Command----------+" << endl;
        cout << "|       General Options         |" << endl;
        cout << "| 1. Add Mark watched           |" << endl;
        cout << "| 2. Add No Mark Watched        |" << endl;
        cout << "|                               |" << endl;
        cout << "|       Network Options         |" << endl;
        cout << "| 3. Add Proxy                  |" << endl;
        cout << "| 4. Add Socket Timeout         |" << endl;
        cout << "| 5. Add Source IP Address      |" << endl;
        cout << "| 6. Add Force ipv4             |" << endl;
        cout << "| 7. Add Force ipv6             |" << endl;
        cout << "|                               |" << endl;
        cout << "|       Geo Restriction         |" << endl;
        cout << "| 8. Add geo-verification proxy |" << endl;
        cout << "| 9. Add Geo Bypass             |" << endl;
        cout << "| 10. Add Geo Bypass County Code|" << endl;
        cout << "| 11. Geo byapss ip block       |" << endl;
        cout << "|                               |" << endl;
        cout << "|       Video Selection         |" << endl;
        cout << "| 12. Add Playlist Start        |" << endl;
        cout << "| 13. Add Playlist End          |" << endl;
        cout << "| 14. Add Playlist Video Select |" << endl;
        cout << "| 15. Add match title           |" << endl;
        cout << "| 16. Reject Title              |" << endl;
        cout << "| 17. Add Max Downloads         |" << endl;
        cout << "| 18. Add Minimum File Size     |" << endl;
        cout << "| 19. Add Maximum File Size     |" << endl;
        cout << "| 20. Add Date                  |" << endl;
        cout << "| 21. Add Before Date           |" << endl;
        cout << "| 22. Add After Date            |" << endl;
        cout << "| 23. Add Minimum Views         |" << endl;
        cout << "| 24. Add Maximum Views         |" << endl;
        cout << "| 25. Add Match Filter          |" << endl;
        cout << "| 26. Add No Playlist           |" << endl;
        cout << "| 27. Add Yes Playlist          |" << endl;
        cout << "| 28. Add Age Limit             |" << endl;
        cout << "| 29. Add Download Archive      |" << endl;
        cout << "| 30. Add Include Ads           |" << endl;
        cout << "|                               |" << endl;
        cout << "|       Download Options        |" << endl;
        cout << "| 31. Add Downlaod Rate         |" << endl;
        cout << "| 32. Add number of retries     |" << endl;
        cout << "| 33. Add Fragment Retries      |" << endl;
        cout << "| 34. Add Skip N/A Fragments    |" << endl;
        cout << "| 35. Add Abort N/A Fragments   |" << endl;
        cout << "| 36. Add Keep Pragments        |" << endl;
        cout << "| 37. Add Buffer Size           |" << endl;
        cout << "| 38. Add No-Resize Buffer      |" << endl;
        cout << "| 39. Add HTTP Chunk Size       |" << endl;
        cout << "| 40. Add Playlist Reverse      |" << endl;
        cout << "| 41. Add Playlist Random       |" << endl;
        cout << "| 42. Add Xattr Set Filesize    |" << endl;
        cout << "| 43. Add HLS Prefer Native     |" << endl;
        cout << "| 44. ADD HLS Prefer-ffmpeg     |" << endl;
        cout << "| 45. ADD HLS Use Mpegts        |" << endl;
        cout << "| 46. Add External Downloader   |" << endl;
        cout << "| 47. Add External DL Arguments |" << endl;
        cout << "|                               |" << endl;
        cout << "|      Filesystem Options       |" << endl;
        cout << "| 48. Add Batch Download File   |" << endl;
        cout << "| 49. Use video ID Filename     |" << endl;
        cout << "| 50. Add Output Template       |" << endl;
        cout << "| 51. Add Autonumber            |" << endl;
        cout << "| 52. Add Restrict Filenames    |" << endl;
        cout << "| 53. Add No Overwrites         |" << endl;
        cout << "| 54. Add Force Continue        |" << endl;
        cout << "| 55. Add No-Continue           |" << endl;
        cout << "| 56. Add No .Part Files        |" << endl;
        cout << "| 57. Add No M Time             |" << endl;
        cout << "| 58. Add Write Description     |" << endl;
        cout << "| 59. Add Info to JSON          |" << endl;
        cout << "| 60. Add Write Annotations     |" << endl;
        cout << "| 61. Add Load info JSON File   |" << endl;
        cout << "| 62. Add Load Cookies          |" << endl;
        cout << "| 63. Add Cache Directory       |" << endl;
        cout << "| 64. Add No Cache Directory    |" << endl;
        cout << "| 65. Add Delete Cache          |" << endl;
        cout << "|                               |" << endl;
        cout << "|      Thumbnail Images         |" << endl;
        cout << "| 66. Add Write Thumbnail Img   |" << endl;
        cout << "| 67. Add Write All Thumbnails  |" << endl;
        cout << "|                               |" << endl;
        cout << "|      Verbosity / Sim Options  |" << endl;
        cout << "| 68. Add Quiet Mode            |" << endl;
        cout << "| 69. Add Ignore Warnings       |" << endl;
        cout << "| 70. Add Simulate Mode         |" << endl;
        cout << "| 71. Skip Download             |" << endl;
        cout << "| 72. Add Sim Mode but print URL|" << endl;
        cout << "| 73. Add Sim get Title         |" << endl;
        cout << "| 74. Add Sim get id            |" << endl;
        cout << "| 75. Add Sim get description   |" << endl;
        cout << "| 76. Add Sim get duration      |" << endl;
        cout << "| 77. Add Sim get filename      |" << endl;
        cout << "| 78. Add Sim get format        |" << endl;
        cout << "| 79. Add Sim dump JSON         |" << endl;
        cout << "| 80. Add Sim dump single JSON  |" << endl;
        cout << "| 81. Add Quiet dump JSON       |" << endl;
        cout << "| 82. Add progress bar newline  |" << endl;
        cout << "| 83. Add Do not print Progress |" << endl;
        cout << "| 84. Add Console Title Progress|" << endl;
        cout << "| 85. Add Print Debug Info      |" << endl;
        cout << "| 86. Add dump pages            |" << endl;
        cout << "| 87. Add write pages           |" << endl;
        cout << "| 88. Add Print Traffic         |" << endl;
        cout << "| 89. Add Call Home Debug       |" << endl;
        cout << "| 90. Add No Call Home Debug    |" << endl;
        cout << "|                               |" << endl;
        cout << "|      Workarounds              |" << endl;
        cout << "| 91. Add Force Encoding        |" << endl;
        cout << "| 92. Add No Check Certificate  |" << endl;
        cout << "| 93. Add Prefer Insecure       |" << endl;
        cout << "| 94. Add Specify User Agent    |" << endl;
        cout << "| 95. Add Referer URL           |" << endl;
        cout << "| 96. Add Custom HTTP Header    |" << endl;
        cout << "| 97. Add Bibi Workaround       |" << endl;
        cout << "| 98. Add Sleep Interval        |" << endl;
        cout << "| 99. Add Max Sleep Interval    |" << endl;
        cout << "|                               |" << endl;
        cout << "|      Video Format Options     |" << endl;
        cout << "| 100. Add Video Format Code    |" << endl;
        cout << "| 101. Download all formats     |" << endl;
        cout << "| 102. Prefer Free Formats      |" << endl;
        cout << "| 103. List formats for video   |" << endl;
        cout << "| 104. YouTube Skip Dash Manif  |" << endl;
        cout << "| 105. Merge Output Format      |" << endl;
        cout << "|                               |" << endl;
        cout << "|      Subtitle Options         |" << endl;
        cout << "| 106. List all subtitles       |" << endl;
        cout << "| 107. Write Subtitle File      |" << endl;
        cout << "| 108. Write Auto Subtitles     |" << endl;
        cout << "| 109. Download All Subtitles   |" << endl;
        cout << "| 110. Specify Subtitle Format  |" << endl;
        cout << "| 111. Specify Subtitle Language|" << endl;
        cout << "|                               |" << endl;
        cout << "|      Authentication Options   |" << endl;
        cout << "| 112. Set Username             |" << endl;
        cout << "| 113. Set Password             |" << endl;
        cout << "| 114. Set Two Factor Auth Code |" << endl;
        cout << "| 115. Use .netrc Auth Data     |" << endl;
        cout << "| 116. Add video password       |" << endl;
        cout << "|                               |" << endl;
        cout << "|     Post-Processing Options   |" << endl;
        cout << "| 117. Extract Audio            |" << endl;
        cout << "| 118. Specify Audio Format     |" << endl;
        cout << "| 119. Specify Audio Quality    |" << endl;
        cout << "| 120. Re-encode Video          |" << endl;
        cout << "| 121. Post Processor Arguments |" << endl;
        cout << "| 122. Keep Video File on Disk  |" << endl;
        cout << "| 123. No Post Overwrites       |" << endl;
        cout << "| 124. Embed Subtitles          |" << endl;
        cout << "| 125. Emded Thumbnail          |" << endl;
        cout << "| 126. Write Metadata to file   |" << endl;
        cout << "| 127. Add Metadata from title  |" << endl;
        cout << "| 128. Prefer avconv            |" << endl;
        cout << "| 129. Prefer ffmpeg            |" << endl;
        cout << "| 130. ffmpeg location path     |" << endl;
        cout << "| 131. Execute command on file  |" << endl;
        cout << "| 132. Convert Subtitles        |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << "| 0. Return To Main Menu        |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << endl;
        cout << "Use Previous Arguments" << endl;

        for (int i = 0; i < 99; i++)
        {
            temp = i + 132;

            if (previous[i] != "")
            {
                cout << temp << "." << "Use: " << previous[i] << endl;
            }
        }
        cout << endl;
        cout << "youtube-dl [OPTIONS] URL [URL...]" << endl;
        cout << "Current Command: " << command << endl;
        cout << endl;
        cout << "Your Selection: ";
        getline(cin, input);

        // For each argument apply the following
        //  1. Title of the argument
        //  2. Description of the argument
        //  3. Setting for argument (optional)

        if (input == "1")
        {
            // Search the command and search for the argument
            // If the argument exists, ask if they want to remove it

            string arg = "--mark-watched";
            string description = "Mark videos watched (YouTube only)";
            CheckEraseString(arg, description);
        }
        if (input == "2")
        {
            string arg = "--no-mark-watched";
            string description = "Do not mark videos watched (YouTube only)";
            CheckEraseString(arg, description);
        }
        if (input == "3")
        {
            string arg = "--proxy";
            string arg2 = "URL";
            string description = "Use the specified HTTP/HTTPS/SOCKS proxy. To enable SOCKS proxy, specify a proper scheme. For example socks5://127.0.0.1:1080/. Pass in an empty string (--proxy "") for direct connection";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "4")
        {
            string arg = "--socket-timeout";
            string arg2 = "SECONDS";
            string description = "Time to wait before giving up, in seconds";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "5")
        {
            string arg = "--source-address";
            string arg2 = "IP";
            string description = "Client-side IP address to bind to";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "6")
        {
            string arg = "--force-ipv4";
            string description = "Make all connections via IPv4";

            CheckEraseString(arg, description);
        }
        if (input == "7")
        {
            string arg = "--force-ipv6";
            string description = "Make all connections via IPv6";

            CheckEraseString(arg, description);
        }
        if (input == "8")
        {
            string arg = "--geo-verification-proxy";
            string arg2 = "URL";
            string description = "Use this proxy to verify the IP address for some geo-restricted sites. The default proxy specified by --proxy (or none, if the option is not present) is used for the actual downloading.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "9")
        {
            string arg = "--geo-bypass";
            string description = "Bypass geographic restriction via faking X-Forwarded-For HTTP header";

            CheckEraseString(arg, description);
        }
        if (input == "10")
        {
            string arg = "--geo-bypass-country";
            string arg2 = "CODE";
            string description = "Do not bypass geographic restriction via faking X-Forwarded-For HTTP header";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "11")
        {
            string arg = "--geo-bypass-ip-block";
            string arg2 = "IP_BLOCK";
            string description = "Force bypass geographic restriction with explicitly provided IP block in CIDR notation.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "12")
        {
            string arg = "--playlist-start";
            string arg2 = "NUMBER";
            string description = "Playlist video to start at (default is 1)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "13")
        {
            string arg = "--playlist-end";
            string arg2 = "NUMBER";
            string description = "Playlist video to end at (default is last)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "14")
        {
            string arg = "--playlist-items";
            string arg2 = "ITEM_SPEC";
            string description = "Playlist video items to download. Specify indices of the videos in the playlist separated by commas like: \"--playlist - items 1,2,5,8\" if you want to download videos indexed 1, 2, 5, 8 in the playlist. You can specify range: \"--playlist - items 1-3,7,10-13\", it will download the videos at index 1, 2, 3, 7, 10, 11, 12 and 13.";
        }
        if (input == "15")
        {
            string arg = "--match-title";
            string arg2 = "REGEX";
            string description = "Download only matching titles (regex or caseless sub-string)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "16")
        {
            string arg = "--reject-title";
            string arg2 = "REGEX";
            string description = "Skip download for matching titles (regex or caseless sub-string)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "17")
        {
            string arg = "--max-downloads";
            string arg2 = "NUMBER";
            string description = "Abort after downloading NUMBER files";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "18")
        {
            string arg = "--min-filesize";
            string arg2 = "SIZE";
            string description = "Do not download any videos smaller than SIZE (e.g. 50k or 44.6m)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "19")
        {
            string arg = "--max-filesize";
            string arg2 = "SIZE";
            string description = "Do not download any videos larger than SIZE (e.g. 50k or 44.6m)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "20")
        {
            string arg = "--date";
            string arg2 = "DATE";
            string description = "Download only videos uploaded in this date";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "21")
        {
            string arg = "--datebefore";
            string arg2 = "DATE";
            string description = "Download only videos uploaded on or before this date (i.e. inclusive)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "22")
        {
            string arg = "--dateafter";
            string arg2 = "DATE";
            string description = "Download only videos uploaded on or after this date (i.e. inclusive)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "23")
        {
            string arg = "--min-views";
            string arg2 = "COUNT";
            string description = "Do not download any videos with less than COUNT views";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "24")
        {
            string arg = "--max-views";
            string arg2 = "COUNT";
            string description = "Do not download any videos with more than COUNT views";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "25")
        {
            string arg = "--match-filter";
            string arg2 = "FILTER";
            string description = "Generic video filter. Specify any key (see the \"OUTPUT TEMPLATE\" for a list of available keys) to match if the key is present, !key to check if the key is not present, key > NUMBER (like \"comment_count > 12\", also works with >= , < , <= , != , =) to compare against a number, key = 'LITERAL' (like \"uploader = 'Mike Smith'\", also works with !=) to match against a string literal and & to require multiple matches. Values which are not known are excluded unless you put a question mark (?) after the operator. For example, to only match videos that have been liked more than 100 times and disliked less than 50 times (or the dislike functionality is not available at the given service), but who also have a description, use --match-filter \"like_count > 100 & dislike_count <? 50 & description\".";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "26")
        {
            string arg = "--no-playlist";
            string description = "Download only the video, if the URL refers to a video and a playlist.";

            CheckEraseString(arg, description);
        }
        if (input == "27")
        {
            string arg = "--yes-playlist";
            string description = "Download the playlist, if the URL refers to a video and a playlist.";

            CheckEraseString(arg, description);
        }
        if (input == "28")
        {
            string arg = "--age-limit";
            string arg2 = "YEARS";
            string description = "Download only videos suitable for the given age";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "29")
        {
            string arg = "--download-archive";
            string arg2 = "FILE";
            string description = "Download only videos not listed in the archive file. Record the IDs of all downloaded videos in it.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "30")
        {
            string arg = "--include-ads";
            string description = "Download advertisements as well (experimental)";

            CheckEraseString(arg, description);
        }
        if (input == "31")
        {
            string arg = "--limit-rate";
            string arg2 = "RATE";
            string description = "Maximum download rate in bytes per second (e.g. 50K or 4.2M)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "32")
        {
            string arg = "--retries";
            string arg2 = "RETRIES";
            string description = "Number of retries (default is 10), or \"infinite\".";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "33")
        {
            string arg = "--fragment-retries";
            string arg2 = "RETRIES";
            string description = "Number of retries for a fragment (default is 10), or \"infinite\" (DASH, hlsnative and ISM)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "34")
        {
            string arg = "--skip-unavailable-fragments";
            string description = "Skip unavailable fragments (DASH, hlsnative and ISM)";

            CheckEraseString(arg, description);
        }
        if (input == "35")
        {
            string arg = "--abort-on-unavailable-fragment";
            string description = "Abort downloading when some fragment is not available";

            CheckEraseString(arg, description);
        }
        if (input == "36")
        {
            string arg = "--keep-fragments";
            string description = "Keep downloaded fragments on disk after downloading is finished; fragments are erased by default";

            CheckEraseString(arg, description);
        }
        if (input == "37")
        {
            string arg = "--buffer-size";
            string arg2 = "SIZE";
            string description = "Size of download buffer (e.g. 1024 or 16K) (default is 1024)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "38")
        {
            string arg = "--no-resize-buffer";
            string description = "Do not automatically adjust the buffer size. By default, the buffer size is automatically resized from an initial value of SIZE.";

            CheckEraseString(arg, description);
        }
        if (input == "39")
        {
            string arg = "--http-chunk-size";
            string arg2 = "SIZE";
            string description = "Size of a chunk for chunk-based HTTP downloading (e.g. 10485760 or 10M) (default is disabled). May be useful for bypassing bandwidth throttling imposed by a webserver (experimental)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "40")
        {
            string arg = "--playlist-reverse";
            string description = "Download playlist videos in reverse order";

            CheckEraseString(arg, description);
        }
        if (input == "41")
        {
            string arg = "--playlist-random";
            string description = "Download playlist videos in random order";
            
            CheckEraseString(arg, description);
        }
        if (input == "42")
        {
            string arg = "--xattr-set-filesize";
            string description = "Set file xattribute ytdl.filesize with expected file size";

            CheckEraseString(arg, description);
        }
        if (input == "43")
        {
            string arg = "--hls-prefer-native";
            string description = "Use the native HLS downloader instead of ffmpeg";

            CheckEraseString(arg, description);
        }
        if (input == "44")
        {
            string arg = "--hls-prefer-ffmpeg";
            string description = "Use ffmpeg instead of the native HLS downloader";

            CheckEraseString(arg, description);
        }
        if (input == "45")
        {
            string arg = "--hls-use-mpegts";
            string description = "Use the mpegts container for HLS videos, allowing to play the video while downloading (some players may not be able to play it)";

            CheckEraseString(arg, description);
        }
        if (input == "46")
        {
            string arg = "--external-downloader";
            string arg2 = "COMMAND";
            string description = "Use the specified external downloader. Currently supports aria2c,avconv,axel,curl,ffmpeg,httpie,wget";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "47")
        {
            string arg = "--external-downloader-args";
            string arg2 = "ARGS";
            string description = "Give these arguments to the external downloader";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "48")
        {
            string arg = "--batch-file";
            string arg2 = "FILE";
            string description = "File containing URLs to download ('-' for stdin), one URL per line. Lines starting with '#', ';' or ']' are considered as comments and ignored.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "49")
        {
            string arg = "--id";
            string description = "Use only video ID in file name";

            CheckEraseString(arg, description);
        }
        if (input == "50")
        {
            string arg = "--output";
            string arg2 = "TEMPLATE";
            string description = "Output filename template, see the \"OUTPUT TEMPLATE\" for all the info";

            OutputTemplate(arg, arg2, description);
        }
        if (input == "51")
        {
            string arg = "--autonumber-start";
            string arg2 = "NUMBER";
            string description = "Specify the start value for %(autonumber)s (default is 1)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "52")
        {
            string arg = "--restrict-filenames";
            string description = "Restrict filenames to only ASCII characters, and avoid \" & \" and spaces in filenames";

            CheckEraseString(arg, description);
        }
        if (input == "53")
        {
            string arg = "--no-overwrites";
            string description = "Do not overwrite files";

            CheckEraseString(arg, description);
        }
        if (input == "54")
        {
            string arg = "--continue";
            string description = "Force resume of partially downloaded files. By default, youtube-dl will resume downloads if possible.";

            CheckEraseString(arg, description);
        }
        if (input == "55")
        {
            string arg = "--no-continue";
            string description = "Do not resume partially downloaded files (restart from beginning)";

            CheckEraseString(arg, description);
        }
        if (input == "56")
        {
            string arg = "--no-part";
            string description = "Do not use .part files - write directly into output file";
            
            CheckEraseString(arg, description);
        }
        if (input == "57")
        {
            string arg = "--no-mtime";
            string description = "Do not use the Last-modified header to set the file modification time";

            CheckEraseString(arg, description);
        }
        if (input == "58")
        {
            string arg = "--write-description";
            string description = "Write video description to a .description file";

            CheckEraseString(arg, description);
        }
        if (input == "59")
        {
            string arg = "--write-info-json";
            string description = "Write video metadata to a .info.json file";

            CheckEraseString(arg, description);
        }
        if (input == "60")
        {
            string arg = "--write-annotations";
            string description = "Write video annotations to a .annotations.xml file";

            CheckEraseString(arg, description);
        }
        if (input == "61")
        {
            string arg = "--load-info-json";
            string arg2 = "FILE";
            string description = "JSON file containing the video information (created with the \"--write - info - json\" option)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "62")
        {
            string arg = "--cookies";
            string arg2 = "FILE";
            string description = "File to read cookies from and dump cookie jar in";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "63")
        {
            string arg = "--cache-dir";
            string arg2 = "DIR";
            string description = "Location in the filesystem where youtube-dl can store some downloaded information permanently. By default $XDG_CACHE_HOME/youtube-dl or ~/.cache/youtube-dl . At the moment, only YouTube player files (for videos with obfuscated signatures) are cached, but that may change.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "64")
        {
            string arg = "--no-cache-dir";
            string description = "Disable filesystem caching";

            CheckEraseString(arg, description);
        }
        if (input == "65")
        {
            string arg = "--rm-cache-dir";
            string description = "Delete all filesystem cache files";
            
            CheckEraseString(arg, description);
        }
        if (input == "66")
        {
            string arg = "--write-thumbnail";
            string description = "Write thumbnail image to disk";

            CheckEraseString(arg, description);
        }
        if (input == "67")
        {
            string arg = "--write-all-thumbnails";
            string description = "Write all thumbnail image formats to disk";

            CheckEraseString(arg, description);
        }
        if (input == "68")
        {
            string arg = "--quiet";
            string description = "Activate quiet mode";

            CheckEraseString(arg, description);
        }
        if (input == "69")
        {
            string arg = "--no-warnings";
            string description = "Ignore warnings";

            CheckEraseString(arg, description);
        }
        if (input == "70")
        {
            string arg = "--simulate";
            string description = "Do not download the video and do not write anything to disk";

            CheckEraseString(arg, description);
        }
        if (input == "71")
        {
            string arg = "--skip-download";
            string description = "Do not download the video";

            CheckEraseString(arg, description);
        }
        if (input == "72")
        {
            string arg = "--get-url";
            string description = "Simulate, quiet but print URL";

            CheckEraseString(arg, description);
        }
        if (input == "73")
        {
            string arg = "--get-title";
            string description = "Simulate, quiet but print title";

            CheckEraseString(arg, description);
        }
        if (input == "74")
        {
            string arg = "--get-id";
            string description = "Simulate, quiet but print id";

            CheckEraseString(arg, description);
        }
        if (input == "75")
        {
            string arg = "--get-description";
            string description = "Simulate, quiet but print video description";

            CheckEraseString(arg, description);
        }
        if (input == "76")
        {
            string arg = "--get-duration";
            string description = "Simulate, quiet but print video length";

            CheckEraseString(arg, description);
        }
        if (input == "77")
        {
            string arg = "--get-filename";
            string description = "Simulate, quiet but print output filename";

            CheckEraseString(arg, description);
        }
        if (input == "78")
        {
            string arg = "--get-format";
            string description = "Simulate, quiet but print output format";

            CheckEraseString(arg, description);
        }
        if (input == "79")
        {
            string arg = "--dump-json";
            string description = "Simulate, quiet but print JSON information. See the \"OUTPUT TEMPLATE\" for a description of available keys.";

            CheckEraseString(arg, description);
        }
        if (input == "80")
        {
            string arg = "--dump-single-json";
            string description = "Simulate, quiet but print JSON information for each command-line argument. If the URL refers to a playlist, dump the whole playlist information in a single line.";
            
            CheckEraseString(arg, description);
        }
        if (input == "81")
        {
            string arg = "--print-json";
            string description = "Be quiet and print the video information as JSON (video is still being downloaded).";

            CheckEraseString(arg, description);
        }
        if (input == "82")
        {
            string arg = "--newline";
            string description = "Output progress bar as new lines";

            CheckEraseString(arg, description);
        }
        if (input == "83")
        {
            string arg = "--no-progress";
            string description = "Do not print progress bar";

            CheckEraseString(arg, description);
        }
        if (input == "84")
        {
            string arg = "--console-title";
            string description = "Display progress in console titlebar";

            CheckEraseString(arg, description);
        }
        if (input == "85")
        {
            string arg = "--verbose";
            string description = "Print various debugging information";

            CheckEraseString(arg, description);
        }
        if (input == "86")
        {
            string arg = "--dump-pages";
            string description = "Print downloaded pages encoded using base64 to debug problems (very verbose)";

            CheckEraseString(arg, description);
        }
        if (input == "87")
        {
            string arg = "--write-pages";
            string description = "Write downloaded intermediary pages to files in the current directory to debug problems";

            CheckEraseString(arg, description);
        }
        if (input == "88")
        {
            string arg = "--print-traffic";
            string description = "Display sent and read HTTP traffic";

            CheckEraseString(arg, description);
        }
        if (input == "89")
        {
            string arg = "--call-home";
            string description = "Contact the youtube-dl server for debugging";

            CheckEraseString(arg, description);
        }
        if (input == "90")
        {
            string arg = "--no-call-home";
            string description = "Do NOT contact the youtube-dl server for debugging";

            CheckEraseString(arg, description);
        }
        if (input == "91")
        {
            string arg = "--encoding";
            string arg2 = "ENCODING";
            string description = "Force the specified encoding (experimental)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "92")
        {
            string arg = "--no-check-certificate";
            string description = "Suppress HTTPS certificate validation";

            CheckEraseString(arg, description);
        }
        if (input == "93")
        {
            string arg = "--prefer-insecure";
            string description = "Use an unencrypted connection to retrieve information about the video. (Currently supported only for YouTube)";

            CheckEraseString(arg, description);
        }
        if (input == "94")
        {
            string arg = "--user-agent";
            string arg2 = "UA";
            string description = "Specify a custom user agent";


            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "95")
        {
            string arg = "--referer";
            string arg2 = "URL";
            string description = "Specify a custom referer, use if the video access is restricted to one domain";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "96")
        {
            string arg = "--add-header";
            string arg2 = "FIELD:VALUE";
            string description = "Specify a custom HTTP header and its value, separated by a colon ':'. You can use this option multiple times";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "97")
        {
            string arg = "--bidi-workaround";
            string description = "Work around terminals that lack bidirectional text support. Requires bidiv or fribidi executable in PATH";

            CheckEraseString(arg, description);
        }
        if (input == "98")
        {
            string arg = "--sleep-interval";
            string arg2 = "SECONDS";
            string description = "Number of seconds to sleep before each download when used alone or a lower bound of a range for randomized sleep before each download (minimum possible number of seconds to sleep) when used along with --max-sleep-interval.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "99")
        {
            string arg = "--max-sleep-interval";
            string arg2 = "SECONDS";
            string description = "Upper bound of a range for randomized sleep before each download (maximum possible number of seconds to sleep). Must only be used along with --min-sleep-interval.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "100")
        {
            string arg = "--format";
            string arg2 = "FORMAT";
            string description = "Video format code, see the \"FORMAT\" SELECTION\" for all the info.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "101")
        {
            string arg = "--all-formats";
            string description = "Download all available video formats";

            CheckEraseString(arg, description);
        }
        if (input == "102")
        {
            string arg = "--prefer-free-formats";
            string description = "Prefer free video formats unless a specific one is requested";

            CheckEraseString(arg, description);
        }
        if (input == "103")
        {
            string arg = "--list-formats";
            string description = "List all available formats of requested videos";

            CheckEraseString(arg, description);
        }
        if (input == "104")
        {
            string arg = "--youtube-skip-dash-manifest";
            string description = "Do not download the DASH manifests and related data on YouTube videos";

            CheckEraseString(arg, description);
        }
        if (input == "105")
        {
            string arg = "--merge-output-format";
            string arg2 = "FORMAT";
            string description = "If a merge is required (e.g. bestvideo+bestaudio), output to given container format. One of mkv, mp4, ogg, webm, flv. Ignored if no merge is required";


            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "106")
        {
            string arg = "--list-subs";
            string description = "List all available subtitles for the video";

            CheckEraseString(arg, description);
        }
        if (input == "107")
        {
            string arg = "--write-sub";
            string description = "Write subtitle file";

            CheckEraseString(arg, description);
        }
        if (input == "108")
        {
            string arg = "--write-auto-sub";
            string description = "Write automatically generated subtitle file (YouTube only)";

            CheckEraseString(arg, description);
        }
        if (input == "109")
        {
            string arg = "--all-subs";
            string description = "Download all the available subtitles of the video";

            CheckEraseString(arg, description);
        }
        if (input == "110")
        {
            string arg = "--sub-format";
            string arg2 = "FORMAT";
            string description = "Subtitle format, accepts formats preference, for example: \"srt\" or \"ass / srt / best\"";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "111")
        {
            string arg = "--sub-lang";
            string arg2 = "LANGS";
            string description = "Languages of the subtitles to download (optional) separated by commas, use --list-subs for available language tags";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "112")
        {
            string arg = "--username";
            string arg2 = "USERNAME";
            string description = "Login with this account ID";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "113")
        {
            string arg = "--password";
            string arg2 = "PASSWORD";
            string description = "Account password. If this option is left out, youtube-dl will ask interactively.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "114")
        {
            string arg = "--twofactor";
            string arg2 = "TWOFACTOR";
            string description = "Two-factor authentication code";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "115")
        {
            string arg = "--netrc";
            string description = "Use .netrc authentication data";

            CheckEraseString(arg, description);
        }
        if (input == "116")
        {
            string arg = "--video-password";
            string arg2 = "PASSWORD";
            string description = "Video password (vimeo, smotri, youku)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "117")
        {
            string arg = "--extract-audio";
            string description = "Convert video files to audio-only files (requires ffmpeg or avconv and ffprobe or avprobe)";

            CheckEraseString(arg, description);
        }
        if (input == "118")
        {
            string arg = "--audio-format";
            string arg2 = "FORMAT";
            string description = "Specify audio format: \"best\", \"aac\", \"flac\", \"mp3\", \"m4a\", \"opus\", \"vorbis\", or \"wav\"; \"best\" by default; No effect without -x";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "119")
        {
            string arg = "--audio-quality";
            string arg2 = "QUALITY";
            string description = "Specify ffmpeg/avconv audio quality, insert a value between 0 (better) and 9 (worse) for VBR or a specific bitrate like 128K (default 5)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "120")
        {
            string arg = "--recode-video";
            string arg2 = "FORMAT";
            string description = "Encode the video to another format if necessary (currently supported: mp4|flv|ogg|webm|mkv|avi)";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "121")
        {
            string arg = "--postprocessor-args";
            string arg2 = "ARGS";
            string description = "Give these arguments to the postprocessor";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "122")
        {
            string arg = "--keep-video";
            string description = "Keep the video file on disk after the post-processing; the video is erased by default";

            CheckEraseString(arg, description);
        }
        if (input == "123")
        {
            string arg = "--no-post-overwrites";
            string description = "Do not overwrite post-processed files; the post-processed files are overwritten by default";

            CheckEraseString(arg, description);
        }
        if (input == "124")
        {
            string arg = "--embed-subs";
            string description = "Embed subtitles in the video (only for mp4, webm and mkv videos)";

            CheckEraseString(arg, description);
        }
        if (input == "125")
        {
            string arg = "--embed-thumbnail";
            string description = "Embed thumbnail in the audio as cover art";

            CheckEraseString(arg, description);
        }
        if (input == "126")
        {
            string arg = "--add-metadata";
            string description = "Write metadata to the video file";

            CheckEraseString(arg, description);
        }
        if (input == "127")
        {
            string arg = "--metadata-from-title";
            string arg2 = "FORMAT";
            string description = "Parse additional metadata like song title / artist from the video title. The format syntax is the same as --output. Regular expression with named capture groups may also be used. The parsed parameters replace existing values. Example: --metadata-from-title \" % (artist)s - % (title)s\" matches a title like \"Coldplay - Paradise\". Example (regex): --metadata-from-title \"(? P<artist>. + ? ) - (? P<title>. + )\"";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "128")
        {
            string arg = "--prefer-avconv";
            string description = "Prefer avconv over ffmpeg for running the postprocessors";

            CheckEraseString(arg, description);
        }
        if (input == "129")
        {
            string arg = "--prefer-ffmpeg";
            string description = "Prefer ffmpeg over avconv for running the postprocessors (default)";

            CheckEraseString(arg, description);
        }
        if (input == "130")
        {
            string arg = "--ffmpeg-location";
            string arg2 = "PATH";
            string description = "Location of the ffmpeg/avconv binary; either the path to the binary or its containing directory.";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "131")
        {
            string arg = "--exec";
            string arg2 = "CMD";
            string description = "Execute a command on the file after downloading, similar to find's -exec syntax. Example: --exec 'adb push {} /sdcard/Music/ && rm {}'";

            AddArgumentArgument(arg, arg2, description);
        }
        if (input == "132")
        {
            string arg = "--convert-subs";
            string arg2 = "FORMAT";
            string description = "Convert the subtitles to other format (currently supported: srt|ass|vtt|lrc)";

            AddArgumentArgument(arg, arg2, description);
        }
        
        // Loop through possible previous commands up to 99 commands
        // Make command the previous command
        for (int x = 133; x < 232; x++)
        {
            int temp;
            temp = stoi(input);

            for (int y = 0; y < 99; y++)
            {
                if (previous[y] != "")
                {
                    if (temp == x)
                    {
                        command = previous[y];
                    }
                }
            }
        }

        if (input == "0")
        {
            boolean = true;
        }
    }
    
    return command;
}

void CheckEraseString(string arg, string description)
{
    bool boolean = false;
    string input;

    if (command.find(arg) != string::npos)
    {
        // The string has been found, ask the user if they want to remove it
        // Get the x position of the found string and the length of the string
        while (!boolean)
        {
            cout << "\"" << arg << "\"" << " has been found inside of the command" << endl;
            cout << description << endl;
            cout << endl;
            cout << "Remove it? (y/n): ";
            getline(cin, input);

            if (input == "y" || input == "Y")
            {
                command.erase(command.find(arg), command.find(arg) + arg.length());
                boolean = true;
                cout << "The string has been removed!" << endl;
                cout << "Press any key to continue...";
                cin.get();
            }
            else if (input == "n" || input == "N")
            {
                cout << "The string has not been removed..." << endl;
                cout << "Press any key to continue...";
                cin.get();
                boolean = true;
            }
            else
            {
                cout << "Invalid Input..." << endl;
                boolean = false;
            }
        }
    }
    else
    {
        // The string has not been found!
        // Add the string and return to the main menu
        cout << endl;
        command = command + arg + " ";
        cout << arg << " added!" << endl;
        cout << "Press any key to continue..." << endl;
        cin.get();
    }
}

bool CheckString(string arg)
{   
    if (command.find(arg) != string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void EraseArgumentArg(string arg, string arg2, string description)
{
    string input;
    int count;
    int count2;
    bool boolean = false;

    // The argument has been found in the command
    // Prompt the user if they want to remove the argument

    while (!boolean)
    {
        // Find the entire argument and ask the user if they would like to remove it
        size_t number = command.find(arg);

        count = 0;

        // Print all characters until the next space
        for (int x = number + 1; x < command.length(); x++)
        {
            if (!isspace(command[x]) || command[x] == '\"')
            {
                cout << command[x] << endl;
                count++;
            }
            else
            {
                break;
            }
        }

        cout << arg << " " << arg2 << endl;
        cout << description << endl;
        cout << "Would you like to remove the argument?" << endl;
        cout << "Selection (y/n): ";
        getline(cin, input);

        if (input == "y" || input == "Y")
        {
            size_t number = command.find(arg);
            count2 = 0;

            // Erase the first argument
            command.erase(number, number + arg.length());

            // Erase the space after the deleted argument
            command.erase(number + 1);

            // Find how many characters there are until there is a space?
            for (int x = number; x < command.length(); x++)
            {
                if (!isspace(command[x]))
                {
                    count2++;
                }
                else
                {
                    break;
                }
            }

            command.erase(number, number + count2);
            boolean = true;
        }
        else if (input == "n" || input == "N")
        {
            boolean = true;
        }
        else
        {
            boolean = false;
        }
    }
}

void AddArgumentArgument(string arg, string arg2, string description)
{
    string argumentArgument;
    string notepad_cmd;
    string out_template = "%(title)s-%(id)s.%(ext)s";
    string input;
    bool boolean = false;
    bool boolean2 = false;

    // Check if the argument is already part of the command string
    // If the arg is part of the command string, ask the user if they would like to remove it
    // If the arg has a setting after the arg, remove it

    if (CheckString(arg))
    {
        EraseArgumentArg(arg, arg2, description);
    }
    else
    {
        while (!boolean2)
        {
            cout << endl;
            cout << arg << " " << arg2 << endl;
            cout << description << endl;
            cout << arg2 << ": ";
            getline(cin, argumentArgument);

            if (arg2 == "FILE")
            {
                // Parse the filename
                argumentArgument = ParseFilename(argumentArgument);

                // Open notepad and scope to the document for batch file
                notepad_cmd = "notepad.exe " + argumentArgument;
                system(notepad_cmd.c_str());
            }
            if (argumentArgument != "")
            {
                command = command + arg + " " + argumentArgument;
                boolean = true;
            }
            else
            {
                cout << "The Argument field was left blank!" << endl;
                cin.get();
            }
        }
    }
}

string OutputTemplate(string arg, string arg2, string description)
{
    bool boolean = false;
    string input;
    string arg3;
    string out_template;
    string argument = "%(title)s-%(id)s.%(ext)s";

    while (!boolean)
    {
        cout << endl;
        cout << arg << " " << arg2 << endl;
        cout << description << endl;
        cout << "The basic usage is not to set any template arguments when downloading a single file, like in youtube-dl -o funny_video.flv \"https://some/video\". However, it may contain special sequences that will be replaced when downloading each video. The special sequences may be formatted according to python string formatting operations. For example, %(NAME)s or %(NAME)05d. To clarify, that is a percent symbol followed by a name in parentheses, followed by formatting operations. Allowed names along with sequence type are:" << endl;
        cout << "1. id (string): Video Identifier" << endl;
        cout << "2. title (string): Video Title" << endl;
        cout << "3. url (string): Video URL" << endl;
        cout << "4. ext (string): Video filename extension" << endl;
        cout << "5. alt_title (string): A secondary title for a video" << endl;
        cout << "6. display_id (string): An alternative identifier for a video" << endl;
        cout << "7. uploader (string): Full name of the video uploader" << endl;
        cout << "8. license (string): License name the video is licensed under" << endl;
        cout << "9. creator (string): The creator of the video" << endl;
        cout << "10. release_date (string): The date (YYYYMMDD) when the video was released" << endl;
        cout << "11. timestamp (numeric): UNIX timestamp of the moment the video became available" << endl;
        cout << "12. upload_date (string): Video upload date (YYYYMMDD)" << endl;
        cout << "13. upload_id (string): Nickname or id of the video uploader" << endl;
        cout << "14. channel (string): Full name of the channel the video is uploaded on" << endl;
        cout << "15. channel_id (string): Id of the channel" << endl;
        cout << "16. location (string): Physical location where the video was filmed" << endl;
        cout << "17. duration (numeric): Length of the video in seconds" << endl;
        cout << "18. view_count (numeric): How many users have watched the video on the platform" << endl;
        cout << "19. like_count (numeric): Number of positive ratings of the video" << endl;
        cout << "20. dislike_count (numeric): Number of negative ratings of the video" << endl;
        cout << "21. repost_count (numeric): Number of reposts of the video" << endl;
        cout << "22. average_rating (numeric): Average rating give by users, the scale used depends on the webpage" << endl;
        cout << "23. comment_count (numeric): Number of comments on the video" << endl;
        cout << "24. age_limit (numeric): Age restriction for the video (years)" << endl;
        cout << "25. is_live (boolean): Whether this video is a live stream or a fixed-length video" << endl;
        cout << "26. start_time (numeric): Time in seconds where the reproduction should start, as specified in the URL" << endl;
        cout << "27. end_time (numeric): Time in seconds where the reproduction should end, as specified in the URL" << endl;
        cout << "28. format (string): A human-readable description of the format" << endl;
        cout << "29. format_id (string): Format code specified by --format" << endl;
        cout << "30. format_note (string): Additional info about the format" << endl;
        cout << "31. width (numeric): Width of the video" << endl;
        cout << "32. height (numeric): Height of the video" << endl;
        cout << "33. resolution (string): Textual description of width and height" << endl;
        cout << "34. tbr Average bitrate of audio and video in KBit/s" << endl;
        cout << "35. abr Average audio bitrate in KBit/s" << endl;
        cout << "36. acodec (string): Name of the audio codec in use" << endl;
        cout << "37. asr (numeric): Audio sampling rate in Hertz" << endl;
        cout << "38. vbr (numeric): Average video bitrate in KBit/s" << endl;
        cout << "39. fps (numeric): Frame rate" << endl;
        cout << "40. vcodec (string): Name of the video codec in use" << endl;
        cout << "41. container (string): Name of the container format" << endl;
        cout << "42. filesize (numeric): The number of bytes, if known in advance" << endl;
        cout << "43. filesize_approx (numeric): An estimate for the number of bytes" << endl;
        cout << "44. protocol (string): The protocol that will be used for the actual download" << endl;
        cout << "45. extractor (string): Name of the extractor" << endl;
        cout << "46. extractor_key (string): Key name of the extractor" << endl;
        cout << "47. epoch (numeric): Unix epoch when creating the file" << endl;
        cout << "48. autonumber (numeric): Five-digit number that will be increased with each download, starting at zero" << endl;
        cout << "49. playlist (string): Name or id of the playlist that contains the video" << endl;
        cout << "50. playlist_index (numeric): Index of the video in the playlist padded with leading zeros according to the total length of the playlist" << endl;
        cout << "51. playlist_id (string): Playlist identifier" << endl;
        cout << "52. playlist_title (string): Playlist title" << endl;
        cout << "53. playlist_uploader (string): Full name of the playlist uploader" << endl;
        cout << "54. playlist_uploader_id (string): Nickname or id of the playlist uploader" << endl;
        cout << "Available for the video that belongs to some logical chapter or section:" << endl;
        cout << "55. chapter (string): Name or title of the chapter the video belongs to" << endl;
        cout << "56. chapter_number (numeric): Number of the chapter the video belongs to" << endl;
        cout << "57. chapter_id (string): Id of the chapter the video belongs to" << endl;
        cout << "Available for the video that is an episode of some series or programme:" << endl;
        cout << "58. series (string): Title of the series or programme the video episode belongs to" << endl;
        cout << "59. season (string): Title of the season the video episode belongs to" << endl;
        cout << "60. season_number (numeric): Number of the season the video episode belongs to" << endl;
        cout << "61. season_id (string): Id of the season the video episode belongs to" << endl;
        cout << "62. episode (string): Title of the video episode" << endl;
        cout << "63. episode_number (numeric): Number of the video episode within a season" << endl;
        cout << "64. episode_id (string): Id of the video episode" << endl;
        cout << "Available for the media that is a track or part of a music album:" << endl;
        cout << "65. track (string): Title of the track" << endl;
        cout << "66. track_number (numeric): Number of the track within an album or a disc" << endl;
        cout << "67. track_id (string): Id of the track" << endl;
        cout << "68. artist (string): Artist(s) of the track" << endl;
        cout << "69. genre (string): Genre(s) of the track" << endl;
        cout << "70. album (string): Title of the album the track belongs to" << endl;
        cout << "71. album_type (string): Type of the album" << endl;
        cout << "72. album_artist (string): List of all artists appeared on the album" << endl;
        cout << "73. disc_number (numeric): Number of the disc or other physical medium the track belongs to" << endl;
        cout << "74. release_year (numeric): Year (YYYY) when the album was released" << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        cout << "75. Insert Hierarchical Path Denotion (/)" << endl;
        cout << "76. Insert Hyphen (-)" << endl;
        cout << "77. Insert Period (.)" << endl;
        cout << "78. Insert Space ( )" << endl;
        cout << "79. Paste filename" << endl;
        cout << "80. Paste your template" << endl;
        cout << "81. Use Default Template" << endl;
        cout << "0. Back to main menu" << endl;
        cout << endl;
        cout << "For a guide on how to format strings for Python, copy and paste the following URL into your web browser:" << endl;
        cout << "https://docs.python.org/2/library/stdtypes.html#string-formatting" << endl;
        cout << endl;
        cout << "Default Template: " << argument << endl;
        cout << "Current Template: " << out_template << endl;
        cout << "By default, YouTube-dl writes the file to the current working directory of this application" << endl;
        cout << "This input is what you would like to add/remove from the output template" << endl;
        cout << "Make sure you remember the file extension: %(EXT)s" << endl;
        cout << endl;
        cout << "Your selection: ";
        getline(cin, input);

        if (input == "1")
        {
            arg3 = "%(ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "2")
        {
            arg3 = "%(TITLE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "3")
        {
            arg3 = "%(URL)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "4")
        {
            arg3 = "%(EXT)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "5")
        {
            arg3 = "%(ALT_TITLE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "6")
        {
            arg3 = "%(DISPLAY_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "7")
        {
            arg3 = "%(UPLOADER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "8")
        {
            arg3 = "%(LICENSE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "9")
        {
            arg3 = "%(CREATOR)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "10")
        {
            arg3 = "%(RELEASE_DATE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "11")
        {
            arg3 = "%(TIMESTAMP)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "12")
        {
            arg3 = "%(UPLOAD_DATE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "13")
        {
            arg3 = "%(UPLOAD_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "14")
        {
            arg3 = "%(CHANNEL)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "15")
        {
            arg3 = "%(CHANNEL_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "16")
        {
            arg3 = "%(LOCATION)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "17")
        {
            arg3 = "%(DURATION)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "18")
        {
            arg3 = "%(VIEW_COUNT)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "19")
        {
            arg3 = "%(LIKE_COUNT)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "20")
        {
            arg3 = "%(DISLIKE_COUNT)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "21")
        {
            arg3 = "%(REPOST_COUNT)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "22")
        {
            arg3 = "%(AVERAGE_RATING)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "23")
        {
            arg3 = "%(COMMENT_COUNT)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "24")
        {
            arg3 = "%(AGE_LIMIT)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "25")
        {
            arg3 = "%(IS_ALIVE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "26")
        {
            arg3 = "%(START_TIME)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "27")
        {
            arg3 = "%(END_TIME)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "28")
        {
            arg3 = "%(FORMAT)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "29")
        {
            arg3 = "%(FORMAT_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "30")
        {
            arg3 = "%(FORMAT_NOTE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "31")
        {
            arg3 = "%(WIDTH)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "32")
        {
            arg3 = "%(HEIGHT)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "33")
        {
            arg3 = "%(RESOLUTION)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "34")
        {
            arg3 = "%(TBR)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "35")
        {
            arg3 = "%(ABR)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "36")
        {
            arg3 = "%(ACODEC)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "37")
        {
            arg3 = "%(ASR)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "38")
        {
            arg3 = "%(VBR)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "39")
        {
            arg3 = "%(FPS)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "40")
        {
            arg3 = "%(VCODEC)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "41")
        {
            arg3 = "%(CONTAINER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "42")
        {
            arg3 = "%(FILESIZE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "43")
        {
            arg3 = "%(FILESIZE_APPROX)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "44")
        {
            arg3 = "%(PROTOCOL)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "45")
        {
            arg3 = "%(EXTRACTOR)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "46")
        {
            arg3 = "%(EXTRACTOR_KEY)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "47")
        {
            arg3 = "%(EPOCH)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "48")
        {
            arg3 = "%(AUTONUMBER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "49")
        {
            arg3 = "%(PLAYLIST)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "50")
        {
            arg3 = "%(PLAYLIST_INDEX)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "51")
        {
            arg3 = "%(PLAYLIST_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "52")
        {
            arg3 = "%(PLAYLIST_TITLE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "53")
        {
            arg3 = "%(PLAYLIST_UPLOADER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "54")
        {
            arg3 = "%(PLAYLIST_UPLOADER_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "55")
        {
            arg3 = "%(CHAPTER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "56")
        {
            arg3 = "%(CHAPTER_NUMBER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "57")
        {
            arg3 = "%(CHAPTER_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "58")
        {
            arg3 = "%(SERIES)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "59")
        {
            arg3 = "%(SEASON)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "60")
        {
            arg3 = "%(SEASON_NUMBER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "61")
        {
            arg3 = "%(SEASON_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "62")
        {
            arg3 = "%(EPISODE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "63")
        {
            arg3 = "%(EPISODE_NUMBER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "64")
        {
            arg3 = "%(EPISODE_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "65")
        {
            arg3 = "%(TRACK)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "66")
        {
            arg3 = "%(TRACK_NUMBER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "67")
        {
            arg3 = "%(TRACK_ID)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "68")
        {
            arg3 = "%(ARTIST)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "69")
        {
            arg3 = "%(GENRE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "70")
        {
            arg3 = "%(ALBUM)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "71")
        {
            arg3 = "%(ALBUM_TYPE)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "72")
        {
            arg3 = "%(ALBUM_ARTIST)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "73")
        {
            arg3 = "%(DISC_NUMBER)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "74")
        {
            arg3 = "%(RELEASE_YEAR)s";
            out_template = AddTemplateArgs(out_template, arg3);
        }
        if (input == "75")
        {
            arg3 = "\\";
            out_template += arg3;
        }
        if (input == "76")
        {
            arg3 = "-";
            out_template += arg3;
        }
        if (input == "77")
        {
            arg3 = ".";
            out_template += arg3;
        }
        if (input == "78")
        {
            arg3 = " ";
            out_template += arg3;
        }
        if (input == "79")
        {
            bool boolean2 = false;
            string input2;
            string filename;

            while (!boolean2)
            {
                cout << endl;
                cout << "Paste Filename: ";
                getline(cin, input2);

                if (input != "")
                {
                    boolean2 = true;

                    // Parse the pasted filename
                    filename = ParseFilename(input2);
                    out_template += " ";
                    out_template += filename;
                }
                else
                {
                    cout << "You need to paste a filename!" << endl;
                }
            }
        }
        if (input == "80")
        {
            bool boolean2 = false;
            string input2;

            while (!boolean2)
            {
                cout << endl;
                cout << "Default Template: %(title)s-%(id)s.%(ext)s" << endl;
                cout << "Paste your template: ";
                getline(cin, input2);

                if (input != "")
                {
                    boolean = true;
                    boolean2 = true;
                    ParseTemplate(input2);
                }
                else
                {
                    cout << "You need to paste the template!" << endl;
                }
            }
        }
        if (input == "81")
        {
            out_template = "%(title)s-%(id)s.%(ext)s";
            boolean = true;
            return out_template;
        }
        if (input == "0")
        {
            boolean = true;
            out_template = ParseTemplate(out_template);
            return out_template;
        }
    }
    return out_template;
}

string AddTemplateArgs(string argument, string arg3)
{
    // This function checks if there is a string in the template that matches the current string being added to the template
    // Check if the string is found in the argument
    bool boolean = false;
    bool boolean2 = false;
    string input;
    string input2;
    string temp = "";

    if (argument.find(arg3) != string::npos)
    {
        while (!boolean)
        {
            // The string has been found, ask the user if they would like to remove it
            cout << endl;
            cout << "The string has been found in the template, would you like to remove it?" << endl;
            cout << "Your response (y/n): ";
            getline(cin, input);

            if (input == "Y" || input == "y")
            {
                // Remove the string from the argument
                size_t number = argument.find(arg3);

                for (int x = 0; x < argument.length(); x++)
                {
                    if (x <= number && x >= number + arg3.length())
                    {
                        temp += argument[x];
                    }
                }

                return temp;
            }
            else if (input == "N" || input == "n")
            {
                while (!boolean2)
                {
                    cout << endl;
                    cout << "You have opted to keep the string, would you like to continue placing the duplicate string?" << endl;
                    cout << "Your response (y/n): ";
                    getline(cin, input2);

                    if (input2 == "Y" || input2 == "y")
                    {
                        argument += arg3;
                        boolean = true;
                        boolean2 = true;
                        return argument;
                    }
                    else if (input2 == "N" || input2 == "n")
                    {
                        return argument;
                    }
                    else
                    {
                        cout << "You have entered an invalid option! Select from y or n." << endl;
                    }
                }
            }
            else
            {
                cout << "You have entered an invalid option! Select from y or n." << endl;
            }
        }
    }
    else
    {
        // The string has not been found in the template
        argument += arg3;
        return argument;
    }
    return argument;
}

string ParseTemplate(string out_template)
{
    string temp = "";

    for (int i = 0; i < out_template.length(); i++)
    {
        if (out_template[i] == '%' && out_template[i - 1] != '%' && out_template[i + 1] != '%')
        {
            temp += out_template[i];
            temp += '%';
        }
        else
        {
            temp += out_template[i];
        }
    }

    return temp;
}

string ParseFilename(string filename)
{
    string temp_file;
    string temp_file2;
    bool space = false;

    for (int i = 0; i < filename.length(); i++)
    {
        if (filename[i] == '\"')
        {
            temp_file += "\\\"";
        }
        else if (filename[i] == '\\')
        {
            temp_file += "\\\\";
        }
        else if (filename[i] == '/')
        {
            temp_file += "\\\\";
        }
        else if (filename[i] == ' ')
        {
            space = true;
        }
        else
        {
            temp_file += filename[i];
        }
    }

    // If the filename contains a space, add quotes to the beginning and ending
    if (space)
    {
        for (int x = 0; x < temp_file.length(); x++)
        {
            if (x == 0 || x == temp_file.length())
            {
                temp_file2 += temp_file[x];
                temp_file2 += "\\\"";
            }
            else
            {
                temp_file2 += temp_file[x];
            }
        }

        return temp_file2;
    }
    else
    {
        return temp_file;
    }
}