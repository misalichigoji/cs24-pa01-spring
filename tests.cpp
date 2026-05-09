#include <iostream>
#include <string>
#include <vector>
#include "card.h"
#include "card_list.h"

using namespace std;

int testsRun = 0;
int testsPassed = 0;

void check(bool condition, string testName) {
    testsRun++;
    if (condition) {
        testsPassed++;
        cout << "PASS: " << testName << endl;
    } else {
        cout << "FAIL: " << testName << endl;
    }
}

int val(string cardText) {
    card c(cardText);
    return c.get_value();
}

vector<string> forwardCards(cardBST& tree) {
    vector<string> result;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        result.push_back((*it)->get_string());
    }
    return result;
}

vector<string> reverseCards(cardBST& tree) {
    vector<string> result;
    for (auto it = tree.rbegin(); it != tree.rend(); --it) {
        result.push_back((*it)->get_string());
    }
    return result;
}

void testInsert() {
    cardBST tree;
    check(tree.insert("c a"), "add first card");
    check(!tree.insert("c a"), "no doubles");
    check(tree.insert("h 10"), "add big card");
    check(tree.insert("d 3"), "add middle card");
    check(tree.insert("c k"), "same suit works");

    vector<string> expected = {"c a", "c k", "d 3", "h 10"};
    check(forwardCards(tree) == expected, "cards are sorted");
}

void testContains() {
    cardBST empty;
    check(!empty.contains(val("c a")), "empty has nothing");

    cardBST tree;
    tree.insert("s 5");
    check(tree.contains(val("s 5")), "find the one card");
    check(!tree.contains(val("s 6")), "miss missing card");

    tree.insert("c a");
    tree.insert("h k");
    check(tree.contains(val("c a")), "find low card");
    check(tree.contains(val("h k")), "find high card");
}

void testRemove() {
    cardBST empty;
    check(!empty.remove(val("c a")), "can't remove from empty");

    cardBST single;
    single.insert("d 7");
    check(single.remove(val("d 7")), "remove only card");
    check(single.begin() == single.end(), "now it's empty");

    cardBST leaf;
    leaf.insert("d 7");
    leaf.insert("c 2");
    check(leaf.remove(val("c 2")), "remove leaf");
    check(!leaf.contains(val("c 2")) && leaf.contains(val("d 7")), "root still there");

    cardBST oneChild;
    oneChild.insert("d 7");
    oneChild.insert("c 2");
    check(oneChild.remove(val("d 7")), "remove root w child");
    check(forwardCards(oneChild) == vector<string>{"c 2"}, "child moved up");

    cardBST twoChildren;
    twoChildren.insert("d 7");
    twoChildren.insert("c 2");
    twoChildren.insert("h 9");
    twoChildren.insert("d 3");
    check(twoChildren.remove(val("d 7")), "remove two-child node");
    check(!twoChildren.contains(val("d 7")), "old card is gone");
}

void testIterators() {
    cardBST empty;
    check(empty.begin() == empty.end(), "empty forward stops");
    check(empty.rbegin() == empty.rend(), "empty backward stops");

    cardBST single;
    single.insert("s q");
    auto it = single.begin();
    check((*it)->get_string() == "s q", "one card forward");
    ++it;
    check(it == single.end(), "one card then end");

    auto rit = single.rbegin();
    check((*rit)->get_string() == "s q", "one card backward");
    --rit;
    check(rit == single.rend(), "one card then rend");

    cardBST many;
    many.insert("h 3");
    many.insert("c a");
    many.insert("d 10");
    many.insert("s 2");

    vector<string> forwardExpected = {"c a", "d 10", "s 2", "h 3"};
    vector<string> reverseExpected = {"h 3", "s 2", "d 10", "c a"};
    check(forwardCards(many) == forwardExpected, "walk forward sorted");
    check(reverseCards(many) == reverseExpected, "walk backward sorted");

    auto endIt = many.end();
    ++endIt;
    check(endIt == many.end(), "end stays end");

    auto rendIt = many.rend();
    --rendIt;
    check(rendIt == many.rend(), "rend stays rend");
}

void testGameLikeBehavior() {
    cardBST alice;
    cardBST bob;
    alice.insert("h 3");
    alice.insert("s 10");
    alice.insert("c a");
    alice.insert("c 3");
    alice.insert("s 5");
    alice.insert("h 10");
    alice.insert("d a");

    bob.insert("c 2");
    bob.insert("d a");
    bob.insert("h 10");
    bob.insert("c 3");
    bob.insert("d j");
    bob.insert("s 10");
    bob.insert("h a");

    int aliceMatch = 0;
    string aliceMatchText = "";
    for (auto aliceit = alice.begin(); aliceit != alice.end(); ++aliceit) {
        if (bob.contains((*aliceit)->get_value())) {
            aliceMatch = (*aliceit)->get_value();
            aliceMatchText = (*aliceit)->get_string();
            break;
        }
    }
    check(aliceMatchText == "c 3", "alice finds first match");
    alice.remove(aliceMatch);
    bob.remove(aliceMatch);
    check(!alice.contains(aliceMatch) && !bob.contains(aliceMatch), "alice match removed");

    int bobMatch = 0;
    string bobMatchText = "";
    for (auto bobit = bob.rbegin(); bobit != bob.rend(); --bobit) {
        if (alice.contains((*bobit)->get_value())) {
            bobMatch = (*bobit)->get_value();
            bobMatchText = (*bobit)->get_string();
            break;
        }
    }
    check(bobMatchText == "h 10", "bob finds biggest match");
    bob.remove(bobMatch);
    alice.remove(bobMatch);
    check(!alice.contains(bobMatch) && !bob.contains(bobMatch), "bob match removed");

    cardBST noCommonAlice;
    cardBST noCommonBob;
    noCommonAlice.insert("c a");
    noCommonBob.insert("h k");
    check(!noCommonBob.contains((*noCommonAlice.begin())->get_value()), "no match is fine");
}

int main() {
    testInsert();
    testContains();
    testRemove();
    testIterators();
    testGameLikeBehavior();

    cout << endl << testsPassed << " of " << testsRun << " tests passed." << endl;
    return testsPassed == testsRun ? 0 : 1;
}
