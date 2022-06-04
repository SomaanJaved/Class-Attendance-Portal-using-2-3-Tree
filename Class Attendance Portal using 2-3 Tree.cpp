#include<iostream>
using namespace std;
struct dataEl
{
        string name;
        int value;
        bool keyCheck;
        dataEl() : name("\0"), value(0), keyCheck(false) {}
        dataEl(const dataEl& obj) : name(obj.name), value(obj.value), keyCheck(obj.keyCheck) {}
        dataEl(const string& name, const int& val) : name(name), value(val), keyCheck(false) {}
        void copyContents(const dataEl& obj)
        {
                name = obj.name;
                value = obj.value;
                keyCheck = obj.keyCheck;
        }
};
struct tree23
{
        dataEl leftKey, rightKey, tempKey;
        tree23* parrent;
        tree23* left, *right, *middle, *tempNode;
        tree23() : leftKey(dataEl()), rightKey(dataEl()), tempKey(dataEl()), parrent(NULL), left(NULL), right(NULL), middle(NULL), tempNode(NULL) {}
        void copyLeftKey(const dataEl& infoObj)
        {
                leftKey.name = infoObj.name;
                leftKey.value = infoObj.value;
                leftKey.keyCheck = infoObj.keyCheck;
        }
        void copyrightKey(const dataEl& infoObj)
        {
                rightKey.name = infoObj.name;
                rightKey.value = infoObj.value;
                rightKey.keyCheck = infoObj.keyCheck;
        }
        void copytempKey(const dataEl& infoObj)
        {
                tempKey.name = infoObj.name;
                tempKey.value = infoObj.value;
                tempKey.keyCheck = infoObj.keyCheck;
        }
        void copyContents(tree23* ptrObj)
        {
                leftKey.copyContents(ptrObj->leftKey);
                rightKey.copyContents(ptrObj->rightKey);
                tempKey.copyContents(ptrObj->tempKey);
                parrent = ptrObj->parrent;
                left = ptrObj->left;
                right = ptrObj->right;
                middle = ptrObj->middle;
                tempNode = ptrObj->tempNode;
        }
};
tree23* treeRoot = NULL;
void display(tree23* node);
void putInNode(tree23* node, dataEl info)
{
        if (node->leftKey.keyCheck && node->rightKey.keyCheck)
        {
                if (info.value > node->leftKey.value && info.value < node->rightKey.value)
                {
                        info.keyCheck = true;
                        node->copytempKey(node->rightKey);
                        node->copyrightKey(info);
                }
                else if (info.value > node->rightKey.value)
                {
                        info.keyCheck = true;
                        node->copytempKey(info);
                }
                else if (info.value < node->leftKey.value)
                {
                        info.keyCheck = true;
                        node->copytempKey(node->rightKey);
                        node->copyrightKey(node->leftKey);
                        node->copyLeftKey(info);
                }
                
        }
        else if (info.value > node->leftKey.value)
        {
                info.keyCheck = true;
                node->copyrightKey(info);
        }
        else if (info.value < node->leftKey.value)
        {
                node->copyrightKey(node->leftKey);
                info.keyCheck = true;
                node->copyLeftKey(info);
        }
}
void split(tree23* node)
{
        if (node != NULL)
        {
                tree23* leftNode = new tree23();
                tree23* rightNode = new tree23();
                if (node->parrent == NULL && node->left == NULL)
                {
                        tree23* rootNode = new tree23();
                        rootNode->copyLeftKey(node->rightKey);
                        rootNode->left = leftNode;
                        rootNode->right = rightNode;
                        leftNode->copyLeftKey(node->leftKey);
                        rightNode->copyLeftKey(node->tempKey);
                        leftNode->parrent = rightNode->parrent = rootNode;
                        treeRoot = rootNode;
                }
                else if (node->parrent != NULL && node->left == NULL)
                {
                        putInNode(node->parrent, node->rightKey);
                        leftNode->copyLeftKey(node->leftKey);
                        rightNode->copyLeftKey(node->tempKey);
                        leftNode->parrent = rightNode->parrent = node->parrent;
                        if (node->parrent->left->leftKey.value == node->leftKey.value)
                        {
                                node->parrent->left = leftNode;
                                if (node->parrent->middle == NULL)
                                        node->parrent->middle = rightNode;
                                else
                                        node->parrent->tempNode = rightNode;
                        }
                        else if (node->parrent->right->leftKey.value == node->leftKey.value)
                        {
                                node->parrent->right = rightNode;
                                if (node->parrent->middle == NULL)
                                        node->parrent->middle = leftNode;
                                else
                                        node->parrent->tempNode = leftNode;
                        }
                        else if (node->parrent->middle->leftKey.value == node->leftKey.value)
                        {
                                node->parrent->middle = leftNode;
                                node->parrent->tempNode = rightNode;
                        }
                }
                else if (node->tempNode != NULL)
                {
                        if (node->parrent == NULL)
                        {
                                tree23* rootNode = new tree23();
                                rootNode->copyLeftKey(node->rightKey);
                                rootNode->left = leftNode;
                                rootNode->right = rightNode;
                                leftNode->parrent = rightNode->parrent = rootNode;
                                leftNode->copyLeftKey(node->leftKey);
                                rightNode->copyLeftKey(node->tempKey);
                                leftNode->left = node->left;
                                rightNode->right = node->right;
                                if (node->tempNode->leftKey.value > rootNode->leftKey.value && node->tempNode->leftKey.value < rightNode->leftKey.value)
                                {
                                        leftNode->right = node->middle;
                                        rightNode->left = node->tempNode;
                                }
                                else
                                {
                                        leftNode->right = node->tempNode;
                                        rightNode->left = node->middle;
                                }
                                treeRoot = rootNode;
                        }
                }
        }
}
void insert(dataEl info, tree23* root, tree23* parr)
{
        if (root == NULL)
        {
                if (parr == NULL)
                {
                        treeRoot = new tree23();
                        info.keyCheck = true;
                        treeRoot->copyLeftKey(info);
                }
                else
                        putInNode(parr, info);
        }
        else if (root->rightKey.keyCheck && info.value > root->rightKey.value)
                insert(info, root->right, root);
        else if (root->leftKey.keyCheck && info.value < root->leftKey.value)
                insert(info, root->left, root);
        else if (root->leftKey.keyCheck && root->rightKey.keyCheck && info.value > root->leftKey.value && info.value < root->rightKey.value)
                insert(info, root->middle, root);
        else if (info.value > root->leftKey.value)
                insert(info, root->right, root);
        //else if (info.value < root->leftKey.value)
                //insert(info, root->left, root);
        if (parr != NULL)
        {
                if (parr->tempKey.keyCheck)
                {
                        parr->tempKey.keyCheck = false;
                        split(parr);
                }
        }
}
void display(tree23* node)
{
        if (node != NULL)
        {
                cout << node->leftKey.name << " " << node->rightKey.name << 
                        " " << node->tempKey.name << endl;
                display(node->right);
                display(node->middle);
                display(node->left);
        }
}
int main()
{   string user,pass,temp;
    int strength;
    int presentCount =0;
    int absentCount = 0;
    string absenties[100];
  

    login:
    cout<<"Enter Username: ";
    cin>>user;
    cout<<"Enter Password: ";
    cin>>pass;
    if(user == "admin" && pass=="admin")
    {
        menu:
        system("CLS");
        cout<<"Welcome to Class Attendance Portal\n\n";
        cout<<"1) Mark Attendance\n";
        cout<<"2) Check Present Students\n";
        cout<<"3) Check Absent Studnents\n";
        int choice;
        cout<<"Enter Your Choice: ";
        cin>>choice;

        if(choice == 1)
        {
            cout<<"Enter class Strenght: ";
            cin>> strength;

            string name[strength];
            int roll[strength];
            string tempAttendance[strength];


            for (int i =0; i<strength; i++)
            {
                cout<<"Enter Student Name: ";
                cin>> name[i];

                cout<<"Enter Student Enrollment no. : ";
                cin>> roll[i];

                cout<<"Enter Student Attendance (present/absent): ";
                cin>> tempAttendance[i];

                if(tempAttendance[i] == "present")
                {
                    insert({ name[i], roll[i] }, treeRoot, NULL);
                    presentCount++;
                }
                else
                {
                    absenties[i] = name[i];
                    absentCount++;
                }
            }
                goto menu;

        }

        else if(choice == 2)
        {   
            cout<<"Total Present Students are: "<<presentCount<<endl;
            cout<<"Here is the list:\n";
            display(treeRoot);

            cout<<"Do you want to go to menu (y/n): ";
            cin>>temp;
            if (temp == "y")
            {
                goto menu;
            }
        }

        else if(choice == 3)
        {   
            cout<<"Total Absent Students are: "<<absentCount<<endl;
            cout<<"Here is the list:\n";
            for(int i =0;i<strength;i++)
            {
                cout<<absenties[i]<<" ";
            }

            cout<<"Do you want to go menu (y/n): ";
            cin>>temp;
            if (temp == "y")
            {
                goto menu;
            }
        }
    }

    else
    {
        cout<<"you entered wrong, try again: \n";
        goto login;
    }
        
        system("pause");
        return 0;
}