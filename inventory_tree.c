#include <stdio.h>
#include <stdlib.h>

// define a struct for a product with id, quantity, and pointers to left and right children
struct Product {
    int id;
    int quantity;
    struct Product *left, *right;
};

// function to create a new product node
struct Product* createNode(int productId, int productQuantity) {
    // allocate memory for the new node
    struct Product* newNode = (struct Product*)malloc(sizeof(struct Product));
    // assign values to the node's fields
    newNode->id = productId;
    newNode->quantity = productQuantity;
    // initialize left and right pointers to null
    newNode->left = newNode->right = NULL;
    // return the newly created node
    return newNode;
}

// function to insert a product into the binary search tree (bst)
struct Product* insertProduct(struct Product* root, int productId, int productQuantity) {
    // if the tree is empty, create a new node as the root
    if (root == NULL) {
        return createNode(productId, productQuantity);
    }

    // if the product id is less than the root's id, insert in the left subtree
    if (productId < root->id) {
        root->left = insertProduct(root->left, productId, productQuantity);
    }
    // if the product id is greater than the root's id, insert in the right subtree
    else if (productId > root->id) {
        root->right = insertProduct(root->right, productId, productQuantity);
    }

    // return the root of the updated tree
    return root;
}

// function to find the node with the minimum value (used for deletion)
struct Product* minValueNode(struct Product* node) {
    // traverse the left subtree to find the leftmost node
    struct Product* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    // return the node with the minimum value
    return current;
}

// function to delete a product from the bst
struct Product* deleteProduct(struct Product* root, int productId) {
    // if the tree is empty, return null
    if (root == NULL) {
        return root;
    }

    // if the product id is less than the root's id, delete from the left subtree
    if (productId < root->id) {
        root->left = deleteProduct(root->left, productId);
    }
    // if the product id is greater than the root's id, delete from the right subtree
    else if (productId > root->id) {
        root->right = deleteProduct(root->right, productId);
    }
    // if the product id matches the root's id, delete the node
    else {
        // if the node has no children, delete it
        if (root->left == NULL) {
            struct Product* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Product* temp = root->left;
            free(root);
            return temp;
        }

        // find the minimum value node in the right subtree
        struct Product* temp = minValueNode(root->right);
        // copy the minimum value node's data to the root
        root->id = temp->id;
        root->quantity = temp->quantity;
        // delete the minimum value node from the right subtree
        root->right = deleteProduct(root->right, temp->id);
    }
    // return the root of the updated tree
    return root;
}

// function to search for a product by id
struct Product* searchProduct(struct Product* root, int productId) {
    // if the tree is empty or the root's id matches the product id, return the root
    if (root == NULL || root->id == productId) {
        return root;
    }

    // if the product id is less than the root's id, search in the left subtree
    if (productId < root->id) {
        return searchProduct(root->left, productId);
    }

    // if the product id is greater than the root's id, search in the right subtree
    return searchProduct(root->right, productId);
}

// function to perform in-order traversal to print products in order of ids
void inOrder(struct Product* root) {
    // if the node is not null, recursively traverse the left subtree, print the node's data, and traverse the right subtree
    if (root != NULL) {
        inOrder(root->left);
        printf("Product ID: %d, Quantity: %d\n", root->id, root->quantity);
        inOrder(root->right);
    }
}

int main() {
    // create an empty bst
    struct Product* root = NULL;

    // insert sample products
    root = insertProduct(root, 101, 20);
    root = insertProduct(root, 202, 10);
    root = insertProduct(root, 150, 50);
    root = insertProduct(root, 130, 60);

    printf("Inventory in order:\n");
    inOrder(root);

    printf("\nAdding product with ID 125, Quantity 30\n");
    root = insertProduct(root, 125, 30);
    inOrder(root);

    printf("\nDeleting product with ID 202\n");
    root = deleteProduct(root, 202);
    inOrder(root);

    int searchId = 130;
    struct Product* found = searchProduct(root, searchId);
    if (found != NULL) {
        printf("\nProduct ID: %d found with quantity %d\n", found->id, found->quantity);
    } else {
        printf("\nProduct ID: %d not found\n", searchId);
    }

    return 0;
}