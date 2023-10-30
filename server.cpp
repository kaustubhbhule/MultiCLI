#include <bits/stdc++.h>
#include "socket.cpp"
using namespace std;

Server s;

void *recv(void *)
{
    string id = s.lc;
    while (true)
    {
        if (s.recv(id) == -1)
            break;
    }
    return 0;
}

void *accept(void *)
{
    while (true)
    {
        s.accept();
        string join_msg = BOLDGREEN + ("  " + s.lc + " joined") + RESET;
        s.send(join_msg.c_str());

        pthread_t t;
        pthread_create(&t, NULL, &recv, NULL);
        pthread_detach(t);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    s.bind(argv[1], stoi(argv[2]));
    s.listen(5);

    pthread_t t;
    pthread_create(&t, NULL, &accept, NULL);
    pthread_join(t, NULL);

    s.close();

    return 0;
}
