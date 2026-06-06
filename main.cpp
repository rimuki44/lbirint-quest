#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

class Puzzle {
public:
    virtual bool solve() = 0;
    virtual ~Puzzle() {}
};

class MathPuzzle : public Puzzle {
public:
    bool solve() {
        int a = rand() % 10 + 1;
        int b = rand() % 10 + 1;
        int ans;
        cout << "Skolko budet " << a << " + " << b << "? ";
        cin >> ans;
        return ans == a + b;
    }
};

class GuessPuzzle : public Puzzle {
public:
    bool solve() {
        int secret = rand() % 5 + 1;
        int guess;
        cout << "Ugaday chislo ot 1 do 5: ";
        cin >> guess;
        return guess == secret;
    }
};

class RiddlePuzzle : public Puzzle {
public:
    bool solve() {
        int ans;
        cout << "Zagadka: Chto vsegda idet, no nikogda ne prichodit? (1-vremya,2-dozhd,3-veter): ";
        cin >> ans;
        return ans == 1;
    }
};

class Location {
public:
    int id;
    vector<string> art;
    map<int,int> exits;
    bool open;
    Puzzle* puzzle;
    
    Location(int i, vector<string> a, map<int,int> e, bool o, Puzzle* p) {
        id = i;
        art = a;
        exits = e;
        open = o;
        puzzle = p;
    }
    
    ~Location() {
        delete puzzle;
    }
    
    void draw() {
        cout << "\n=== Lokacia " << id << " ===\n";
        for (int i = 0; i < art.size(); i++) {
            cout << art[i] << endl;
        }
    }
    
    bool tryOpen() {
        if (open) {
            cout << "Uze otkrita.\n";
            return true;
        }
        if (puzzle == NULL) {
            return false;
        }
        cout << "\nGolovolomka!\n";
        if (puzzle->solve()) {
            open = true;
            cout << "Otkrito!\n";
            return true;
        }
        cout << "Neverno!\n";
        return false;
    }
    
    bool canGoTo(int to) {
        for (auto& e : exits) {
            if (e.second == to) return true;
        }
        return false;
    }
};

int main() {
    srand(time(0));
    
    vector<string> art1;
    art1.push_back("[ START ]");
    art1.push_back("  |  ");
    art1.push_back("  V  ");
    
    vector<string> art2;
    art2.push_back("[ MATEMATIKA ]");
    
    vector<string> art3;
    art3.push_back("[ UGADAY ]");
    
    vector<string> art4;
    art4.push_back("[ POBEDA ]");
    
    map<int,int> e1;
    e1[1] = 2;
    
    map<int,int> e2;
    e2[2] = 3;
    
    map<int,int> e3;
    e3[3] = 4;
    
    map<int,int> e4;
    
    Location loc1(1, art1, e1, true, NULL);
    Location loc2(2, art2, e2, false, new MathPuzzle());
    Location loc3(3, art3, e3, false, new GuessPuzzle());
    Location loc4(4, art4, e4, false, new RiddlePuzzle());
    
    map<int, Location*> locs;
    locs[1] = &loc1;
    locs[2] = &loc2;
    locs[3] = &loc3;
    locs[4] = &loc4;
    
    Location* current = &loc1;
    string cmd;
    
    cout << "Igra Labirint\n";
    cout << "Komandy: osmotret, idti N, otkrit N, pomoc, vihod\n";
    
    while (true) {
        if (current->id == 4 && current->open) {
            cout << "\n*** POBEDA! ***\n";
            break;
        }
        
        cout << "\n> ";
        cin >> cmd;
        
        if (cmd == "osmotret") {
            current->draw();
        }
        else if (cmd == "idti") {
            int n;
            cin >> n;
            if (locs.find(n) != locs.end() && current->canGoTo(n) && locs[n]->open) {
                current = locs[n];
                cout << "Pereshli v " << n << endl;
            } else {
                cout << "Nelzya\n";
            }
        }
        else if (cmd == "otkrit") {
            int n;
            cin >> n;
            if (locs.find(n) != locs.end() && current->canGoTo(n)) {
                locs[n]->tryOpen();
            } else {
                cout << "Nelzya otkrit\n";
            }
        }
        else if (cmd == "pomoc") {
            cout << "osmotret, idti N, otkrit N, vihod\n";
        }
        else if (cmd == "vihod") {
            break;
        }
        else {
            cout << "Neizvestno\n";
        }
    }
    
    return 0;
}
