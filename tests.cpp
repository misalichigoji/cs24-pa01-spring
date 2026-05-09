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

int valueOf(string cardText) {
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
    check(tree.insert("c a"), "insert into empty tree");
    check(!tree.insert("c a"), "insert duplicate returns false");
    check(tree.insert("h 10"), "insert larger card");
    check(tree.insert("d 3"), "insert middle card");
    check(tree.insert("c k"), "insert same suit different value");

    vector<string> expected = {"c a", "c k", "d 3", "h 10"};
    check(forwardCards(tree) == expected, "insert keeps BST in sorted order");
}

void testContains() {
    cardBST empty;
    check(!empty.contains(valueOf("c a")), "contains false on empty tree");

    cardBST tree;
    tree.insert("s 5");
    check(tree.contains(valueOf("s 5")), "contains single inserted card");
    check(!tree.contains(valueOf("s 6")), "contains false for missing card");

    tree.insert("c a");
    tree.insert("h k");
    check(tree.contains(valueOf("c a")), "contains left-side card");
    check(tree.contains(valueOf("h k")), "contains right-side card");
}

void testRemove() {
    cardBST empty;
    check(!empty.remove(valueOf("c a")), "remove false on empty tree");

    cardBST single;
    single.insert("d 7");
    check(single.remove(valueOf("d 7")), "remove only node");
    check(single.begin() == single.end(), "tree empty after removing only node");

    cardBST leaf;
    leaf.insert("d 7");
    leaf.insert("c 2");
    check(leaf.remove(valueOf("c 2")), "remove leaf node");
    check(!leaf.contains(valueOf("c 2")) && leaf.contains(valueOf("d 7")), "leaf removal preserves root");

    cardBST oneChild;
    oneChild.insert("d 7");
    oneChild.insert("c 2");
    check(oneChild.remove(valueOf("d 7")), "remove root with one child");
    check(forwardCards(oneChild) == vector<string>{"c 2"}, "one-child removal reconnects child");

    cardBST twoChildren;
    twoChildren.insert("d 7");
    twoChildren.insert("c 2");
    twoChildren.insert("h 9");
    twoChildren.insert("d 3");
    check(twoChildren.remove(valueOf("d 7")), "remove node with two children");
    check(!twoChildren.contains(valueOf("d 7")), "two-child removal deletes target value");
}

void testIterators() {
    cardBST empty;
    check(empty.begin() == empty.end(), "empty begin equals end");
    check(empty.rbegin() == empty.rend(), "empty rbegin equals rend");

    cardBST single;
    single.insert("s q");
    auto it = single.begin();
    check((*it)->get_string() == "s q", "single begin dereferences correctly");
    ++it;
    check(it == single.end(), "single increment reaches end");

    auto rit = single.rbegin();
    check((*rit)->get_string() == "s q", "single rbegin dereferences correctly");
    --rit;
    check(rit == single.rend(), "single decrement reaches rend");

    cardBST many;
    many.insert("h 3");
    many.insert("c a");
    many.insert("d 10");
    many.insert("s 2");

    vector<string> forwardExpected = {"c a", "d 10", "s 2", "h 3"};
    vector<string> reverseExpected = {"h 3", "s 2", "d 10", "c a"};
    check(forwardCards(many) == forwardExpected, "iterator forward traversal sorted");
    check(reverseCards(many) == reverseExpected, "iterator reverse traversal sorted");

    auto endIt = many.end();
    ++endIt;
    check(endIt == many.end(), "incrementing end stays safe");

    auto rendIt = many.rend();
    --rendIt;
    check(rendIt == many.rend(), "decrementing rend stays safe");
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
    check(aliceMatchText == "c 3", "game behavior finds Alice's first match");
    alice.remove(aliceMatch);
    bob.remove(aliceMatch);
    check(!alice.contains(aliceMatch) && !bob.contains(aliceMatch), "game behavior removes Alice match from both");

    int bobMatch = 0;
    string bobMatchText = "";
    for (auto bobit = bob.rbegin(); bobit != bob.rend(); --bobit) {
        if (alice.contains((*bobit)->get_value())) {
            bobMatch = (*bobit)->get_value();
            bobMatchText = (*bobit)->get_string();
            break;
        }
    }
    check(bobMatchText == "h 10", "game behavior finds Bob's first reverse match");
    bob.remove(bobMatch);
    alice.remove(bobMatch);
    check(!alice.contains(bobMatch) && !bob.contains(bobMatch), "game behavior removes Bob match from both");

    cardBST noCommonAlice;
    cardBST noCommonBob;
    noCommonAlice.insert("c a");
    noCommonBob.insert("h k");
    check(!noCommonBob.contains((*noCommonAlice.begin())->get_value()), "game behavior handles no common cards");
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
