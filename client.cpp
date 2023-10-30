#include <bits/stdc++.h>
#include "socket.cpp"
using namespace std;

Client c;

void *recv(void *)
{
    while (true)
    {
        string msg = c.recv();
        if (msg[0] == '!')
            system(msg.substr(1, -1).c_str());
        else
            cout << msg << "\n"
                 << endl;
    }
}

int main(int argc, char *argv[])
{
    string name, msg;

    cout << "\n  Waiting for authentication ..." << endl;
    cin >> name;
    system("clear");
    
    c.connect(argv[1], stoi(argv[2]));
    c.send(name.c_str());

    pthread_t t;
    pthread_create(&t, NULL, &recv, NULL);
    pthread_detach(t);

    while (true)
    {
        getline(cin, msg);
        cout << endl;

        string exit_msg = name+": !exit";
        if (msg == exit_msg)
        {
            c.close();
            exit(0);
        }
        c.send(msg.c_str());
    }

    c.close();

    return 0;
}
