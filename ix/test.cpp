#include <algorithm>
#include <random>

#include "IX_Handle.h"
#include "IX_Manager.h"

#define TEST 1e6

int main() {
    FileManager fm;
    BufPageManager bpm(&fm);
    IX_Manager im(&fm, &bpm);
    im.CreateIndex("1", 1, INTEGER, 4);
    int fID;
    im.OpenIndex("1", 1, fID);
    IX_Handle ih(&fm, &bpm, fID);
    vector<int> vec(TEST, 0);
    for (int i = 0; i < TEST; ++i) {
        vec[i] = rand();
    }
    // std::random_device rd;
    // std::mt19937 g(rd());
    // g.seed(1);
    // std::shuffle(vec.begin(), vec.end(), g);
    clock_t c1 = clock();
    for (int i : vec) {
        // cout << i << endl;
        RID rid = {i, i};
        ih.InsertEntry(&i, rid);
    }
    clock_t c2 = clock();

    cout << "finished insert in " << (double)(c2 - c1) / CLOCKS_PER_SEC << "s"
         << endl;
    clock_t c3 = clock();
    for (int i : vec) {
        RID ret = {-1, -1};
        if (ih.SearchEntry((void *)(&i), ret)) {
            assert(ret.page == ret.slot && ret.page == i);
            // cout << "found " << i << ' ' << ret.page << ' ' << ret.slot <<
            // endl;
        } else {
            cout << "search " << i << " failed " << endl;
        }
    }
    clock_t c4 = clock();

    cout << "finished search in " << (double)(c4 - c3) / CLOCKS_PER_SEC << "s"
         << endl;
    clock_t c5 = clock();
    for (int i : vec) {
        RID ret = {i, i};
        assert(ih.DeleteEntry((void *)(&i), ret));
        // if (ih.DeleteEntry((void *)(&i), ret))
        // {
        //     cout << "delete " << i << ' ' << ret.page << ' ' << ret.slot <<
        //     endl;
        // }
        // else
        // {
        //     cout << "delete " << i << " failed" << endl;
        // }
    }
    clock_t c6 = clock();
    cout << "finished delete in " << (double)(c6 - c5) / CLOCKS_PER_SEC << "s"
         << endl;
    bpm.close();
    im.DestroyIndex("1", 1);
}
