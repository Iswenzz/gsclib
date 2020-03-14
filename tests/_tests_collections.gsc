#include lib\_gsclib;

// Tests for gsclib/collections
test()
{
    comPrintF("\n[======{Collections}======]\n");
    it_list();
}

it_list()
{
    comPrintF("\n<-------[List]------->\n");
    arr = [];
    for (i = 0; i < 10; i++)
        arr[i] = i;

    tlist = ListNew();
    ListAdd(tlist, 600);
    ListAdd(tlist, 300);
    comPrintF("Get: " + ListGet(tlist, 0) + "\n");
    comPrintF("Length: " + ListLength(tlist) + "\n");
    //ListInsert(tlist, 400, 1);
    //comPrintF("Insert: " + ListGet(tlist, 1) + "\n");
    //ListRemove(tlist, 600);
    //comPrintF("Remove: " + ListGet(tlist, 0) + "\n");
}
