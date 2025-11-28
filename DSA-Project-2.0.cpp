/*      ----- Fucntionalities -----
    1. Maintain player scores using BST.
    2. Add/remove/update player scores.
    3. Display top players in descending order. (done)
    4. Search for a specific player by ID or name.
*/

#include <iostream>
#include <cstdlib>
using namespace std;

class Node
{
    int playerId;
    string playerName;
    int playerScore;

    Node *left;
    Node *right;

public:
    // default constructor
    Node()
    {
        left = NULL;
        right = NULL;
    }

    // setters
    void setPlayerId(int id)
    {
        playerId = id;
    }
    void setPlayerName(string name)
    {
        playerName = name;
    }
    void setPlayerScore(int score)
    {
        playerScore = score;
    }
    void setLeft(Node *left)
    {
        this->left = left;
    }
    void setRight(Node *right)
    {
        this->right = right;
    }

    // Getters
    int getPlayerId()
    {
        return playerId;
    }
    string getPlayerName()
    {
        return playerName;
    }
    int getPlayerScore()
    {
        return playerScore;
    }
    Node *getLeft()
    {
        return left;
    }
    Node *getRight()
    {
        return right;
    }
};

class BSTree
{
    Node *root;
    int noVal;

public:
    BSTree()
    { // default constructor
        root = NULL;
        noVal = 0;
    }
    ~BSTree()
    {
        cleanup(root);
    }

    // Helper function to recursively delete nodes
    void cleanup(Node *node)
    {
        if (node == NULL)
        {
            return;
        }

        // Recursively delete left and right subtrees
        cleanup(node->getLeft());
        cleanup(node->getRight());

        // Delete the current node
        delete node;
    }

    int getNoVal() {
        return noVal;
    }

    void insert(int id, string name, int score)
    {
        Node *newNode = new Node;
        newNode->setPlayerId(id);
        newNode->setPlayerName(name);
        newNode->setPlayerScore(score);
        // left and right are both set to NULL through the constructor

        if (root == NULL) // if there are no existing nodes
        {
            root = newNode;
        }
        else
        {
            Node *temp = root;
            Node *previous = root;

            while (temp)
            {
                previous = temp;
                if (score > temp->getPlayerScore() || (score == temp->getPlayerScore() && id > temp->getPlayerId())) {      // to avoid conflicts with duplicate scores
                    temp = temp->getRight();
                }
                else {
                    temp = temp->getLeft();
                }

            } // by the end of this while loop, temp is NULL where as previous is at the last node of the subtree

            if (score > previous->getPlayerScore())
            {
                previous->setRight(newNode);
            }
            else
            {
                previous->setLeft(newNode);
            }
        }
        noVal++;
        // cout << "\n\t------ Player added successfuly ------\n";
    } // end of insert func

    void deleteNode(int score)
    {
        Node *temp = root;
        Node *prev = NULL;

        while (temp && score != temp->getPlayerScore())
        {
            prev = temp;

            if (score > temp->getPlayerScore())
            {
                temp = temp->getRight();
            }
            else
            {
                temp = temp->getLeft();
            }
        } // when the while loop ends, we either have found the matching score, or we are at NULL

        if (!temp) // if temp is NULL, we haven't found the matching score
        {
            cout << "\n\tNo matching score found";
        }
        // if the node has no children  (case 1)
        else if (!temp->getRight() && !temp->getLeft())
        {
            if (!prev) // if previous node is NULL
            {
                root = NULL;
            }
            else if (prev->getLeft() == temp) { // score matched with temp,
                prev->setLeft(NULL);
            }
            else {
                prev->setRight(NULL);
            }

            delete temp;
        } // end of case 1

        // if the node has one child (case 2)
        else if (!temp->getLeft() || !temp->getRight())
        {
            // saving the value of child of the node to be deleted
            Node *child = (temp->getLeft()) ? temp->getLeft() : temp->getRight();

            // now replacing the child with the deleted node
            if (prev == NULL)
            {
                root = child;
            }
            else if (prev->getLeft() == temp) // if the node to be deleted is left child of prev
            {
                prev->setLeft(child);
            }
            else
            {
                prev->setRight(child);
            }

            delete temp;
        }
        // if node to be deleted has two children (case 3)
        // the smallest node in the RIGTH subtree of the node to be deleted
        else
        {
            Node *successor = temp->getRight();
            Node *successorParent = NULL;

            // Find the in-order successor (smallest node in right subtree)
            while (successor->getLeft())
            {
                successorParent = successor;
                successor = successor->getLeft();
            }

            // Copy successor's data into the current node
            temp->setPlayerId(successor->getPlayerId());
            temp->setPlayerName(successor->getPlayerName());
            temp->setPlayerScore(successor->getPlayerScore());

            // Delete the successor node
            if (successorParent == NULL)
            {
                // Successor is the immediate right child
                temp->setRight(successor->getRight());
            }
            else
            {
                successorParent->setLeft(successor->getRight());
            }

            delete successor;
        }
    }

    /// void updateScore(Node root, int oldScore, int newScore) {
    //     if (root == NULL) {
    //         // cout << "\n\tPlayer not found.\n";
    //         return;
    //     }

    //     if (oldScore == root -> getPlayerScore()) {
    //         root -> setPlayerScore(newScore);
    //         cout << "\n\t------ Score updated ------";
    //         return;
    //     }
    //     updateScore(root -> getRight(), oldScore, newScore);
    //     updateScore(root -> getLeft(), oldScore, newScore);
    // } */
    void Update(int oldScore, int newScore) {
        Node* temp = root;
        while (temp != NULL && temp->getPlayerScore() != oldScore) {
            temp = (oldScore > temp->getPlayerScore()) ? temp->getRight() : temp->getLeft();
        }

        if (temp == NULL) {
            cout << "\n\tPlayer with score " << oldScore << " not found.\n";
            return;
        }

        string name = temp->getPlayerName();
        int id = temp->getPlayerId();

        deleteNode(oldScore); // Remove old node
        insert(id, name, newScore); // Insert with updated score
        cout << "\n\t------ Score updated ------\n";
    }

    void searchById(Node* root, int id) {
        if (root == NULL) {
            // cout << "\n\tPlayer not found.\n";
            return;
        }
        if (id == root -> getPlayerId())
        {
            cout << "\n\tID: " << root -> getPlayerId()
                 << "\n\tName: " << root -> getPlayerName()
                 << "\n\tScore: " << root -> getPlayerScore() << endl;
            return;
        }
        searchById(root -> getRight(), id);
        searchById(root -> getLeft(), id);
        
    }
    void SearchId(int id) {
        if (root == NULL) {
            cout << "\n\t ------No nodes inserted yet------";
            return;
        }
        searchById(root, id);
        return;
    }

    void searchByName(Node* root, string name) {
        if (root == NULL) {
            // cout << "\n\tPlayer not found.\n";
            return;
        }
        if (name == root -> getPlayerName())
        {
            cout << "\n\tID: " << root -> getPlayerId()
                 << "\n\tName: " << root -> getPlayerName()
                 << "\n\tScore: " << root -> getPlayerScore() << endl;
            return;
        }
        searchByName(root -> getRight(), name);
        searchByName(root -> getLeft(), name);
    }
    void SearchName(string name) {
        if (root == NULL) {
            cout << "\n\t ------No nodes inserted yet------";
            return;
        }
        searchByName(root, name);
    }

    void decendingOrder(Node *root)
    { // L N R
        if (root != NULL)
        {
            decendingOrder(root->getRight());
            cout << "\n\nID: " << root->getPlayerId()
                 << "\nName: " << root->getPlayerName()
                 << "\nScore: " << root->getPlayerScore() << " ";
            decendingOrder(root->getLeft());
        }
    }
    void display()
    {
        //cout << (root) ? "\n\tDisplaying list..." : "\n\tNo nodes inserted";
        if (root == NULL) {
            cout << "\n\t ------No nodes inserted yet------";
            return;
        }
        decendingOrder(root);
        // system("pause");
    }
};

int main()
{
    /*      ----- Fucntionalities -----
    1. Maintain player scores using BST.
    2. Add/remove/update player scores.
    3. Display top players in descending order. (done)
    4. Search for a specific player by ID or name.
    */

    int score, id; // player score and id
    string name;   // player name
    int choice;
    BSTree game;

    while (true)
    {
        system("cls");
        cout << "\n\t------ Welcome ------";
        cout << "\n\t1) Add Player";
        cout << "\n\t2) Update Player Score";
        cout << "\n\t3) Delete Player Score";
        cout << "\n\t4) Display Leaderboard";
        cout << "\n\t5) Search player by name";
        cout << "\n\t6) Search player by ID";
        cout << "\n\t7) Exit";
        cout << "\n\tEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // add player
            // cout << "\n\tEnter the ID of the player: ";
            // cin >> id;
            // while (id <= 0) {                        // validating the id
            //     cout << "\n\tInvalid ID\n\tEnter the ID again: ";
            //     cin >> id;
            // }
            
            // cout << "\n\tEnter the Name of the player: ";
            // cin >> name;
            // while (name == "") {                     // validating the name
            //     cout << "\n\tName is required\n\tEnter the name of the player: ";
            //     cin >> name;
            // }
            

            // cout << "\n\tEnter the Score of the player: ";
            // cin >> score;
            // while(score > 100 || score < 0) {       // validation check for score
            //     cout << "\n\tInvalid Score input\n\tEnter the score again: ";
            //     cin >> score;
            // }

            // player.insert(id, name, score);

            // sample input for testing
            game.insert(1, "Adam", 85);    //                                    85
            game.insert(2, "Bob", 45);     //                            45                      90
            game.insert(3, "Cyntheia", 70); //                     30           70         88            95
            game.insert(4, "David", 30);   //                 21        57   47       74              93         98
            game.insert(5, "Ethan", 90);    //                        32                                 93
            game.insert(6, "Frank", 88);    //                        32
            game.insert(7, "Gaberial", 95); //
            game.insert(8, "Hans", 57); //
            game.insert(9, "Ivan", 93); //
            game.insert(10, "Jack", 93);
            game.insert(11, "Kim", 74);
            game.insert(12, "Liam", 21);
            game.insert(13, "Musa", 98);
            game.insert(14, "Nethan", 32);
            game.insert(15, "Omar", 32);
            game.insert(16, "Peter", 47);

            cout << "\n\t----- Player added successfully -----\n";
            system("pause");
            break;

        case 2: // update score of player
            /* code */
            int newScore;
            cout << "\n\tEnter the score to be updated: ";
            cin >> choice;      // old score
            cout << "\n\tEnter the new score: ";
            cin >> newScore;
            game.Update(choice, newScore);
            system("pause");
            break;

        case 3: // delete score of player
            cout << "Enter the score you want to delete: ";
            cin >> choice;
            game.deleteNode(choice);
            cout << "\n\t----- Deleted successfully -----\n";
            system("pause");
            break;

        case 4: // display the leaderboard
            game.display();
            cout << endl;
            system("pause");
            break;

        case 5: // search by name
            cout << "\n\tEnter the Name; ";
            cin >> name;
            game.SearchName(name);
            system("pause");
            break;

        case 6: // search by id
            cout << "\n\tEnter the ID: ";
            cin >> choice;
            game.SearchId(choice);
            system("pause");
            break;

        case 7: // exit
            exit(0);
            break;

        default:
            cout << "\n\tEnter the correct choice\t";
            system("pause");
            break;
        }
    }

    return 0;
}

