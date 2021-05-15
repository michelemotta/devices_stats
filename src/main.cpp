
#include "Node.h"
#include "Storage.h"

int main(int argc, char *argv[])
{
    Node node;
    Storage store;

    node.init(&store);
    node.run();

}